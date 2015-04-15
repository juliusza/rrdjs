
var binding = require('./build/Release/rrdjs_bindings');

exports.create = function(fn, step, start, args, next) {
	start = parseInt(start);
    step = parseInt(step);
	if (isNaN(start)) {
        throw new Error("expected numeric start in rrdjs#create");
    }
	if (isNaN(step) || step <= 0) {
        throw new Error("expected positive step in rrdjs#create");
    }
	if (!Array.isArray(args)) {
        throw new Error("expected args array in rrdjs#create");
    }
	if (typeof next !== 'function') {
        throw new Error("expected callback function in rrdjs#create");
    }
	return binding.create(fn, step, start, args, next);
};

exports.info = function(fn, next) {
	if (typeof next !== 'function') {
        throw new Error("expected callback function in rrdjs#update");
    }
	return binding.info(fn, next);
};

exports.update = function(fn, tmpl, args, next) {
	if (!Array.isArray(args)) {
        throw new Error("expected args array in rrdjs#update");
    }
	if (typeof next !== 'function') {
        throw new Error("expected callback function in rrdjs#update");
    }
	return binding.update(fn, tmpl, args, next);
};

exports.fetch = function(fn, cf, start, end, step, next) {
    start = parseInt(start);
    end = parseInt(end);
    step = parseInt(step);
	if (isNaN(start)) {
        throw new Error("expected numeric start in rrdjs#fetch");
    }
	if (isNaN(end)) {
        throw new Error("expected numeric end in rrdjs#fetch");
    }
	if (isNaN(step) || step <= 0) {
        throw new Error("expected positive step in rrdjs#fetch");
    }
    if (typeof next !== 'function') {
        throw new Error("expected callback function in rrdjs#fetch");
    }
    if (start > end) {
        throw new Error("expected end > start in rrdjs#fetch");
    }
	return binding.fetch(fn, cf, start, end, step, next);
};
