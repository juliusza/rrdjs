
#include <string>
#include <vector>
#include "rrdjs.h"

namespace rrdjs {

	using std::string;
	using std::vector;

	struct CreateBoomerang {
		uv_work_t request;

		uint32_t step;
		uint32_t start;
		string filename;
		vector<string> args;
		NanCallback *callback;

		int status;
		string error;
	};

	void createWorker(uv_work_t *req) {
		CreateBoomerang &b = *static_cast<CreateBoomerang*>(req->data);

		vector<const char*> args(b.args.size());
		for (size_t i = 0; i < args.size(); ++i) args[i] = b.args[i].c_str();
		b.status = rrd_create_r(b.filename.c_str(), b.step, b.start, args.size(), &args[0]);
		if (b.status < 0) b.error = rrd_get_error();
		rrd_clear_error();
	}

	void createAfter(uv_work_t *req, int) {
		NanScope();
		CreateBoomerang &b = *static_cast<CreateBoomerang*>(req->data);
		Handle<Value> res[] = { b.status < 0 ? Exception::Error(NanNew<String>(b.error.c_str())) : Handle<Value>(NanNull()) };
		b.callback->Call(1, res);
		delete b.callback;
		delete &b;
	}

	NAN_METHOD(create) {
		NanScope();

		CreateBoomerang &b = *new CreateBoomerang;
		b.request.data = &b;

		b.filename = *String::Utf8Value(args[0]->ToString());
		b.step = args[1]->Uint32Value();
		b.start = args[2]->Uint32Value();

		Local<Array> aa = Local<Array>::Cast(args[3]);
		b.args.resize(aa->Length());
		for (size_t i = 0; i < b.args.size(); ++i)
			b.args[i] = *String::Utf8Value(aa->Get(i));

		b.callback = new NanCallback(args[4].As<Function>());

		uv_queue_work(uv_default_loop(), &b.request, createWorker, createAfter);

		NanReturnUndefined();
	}

}
