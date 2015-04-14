{
  "targets": [
    {
      "target_name": "rrdjs_bindings",
      "sources": [
        "src/rrdjs.cc",
        "src/rrdjs_info.cc",
        "src/rrdjs_fetch.cc",
        "src/rrdjs_create.cc",
        "src/rrdjs_update.cc",
      ],
      'defines': [
        'HAVE_CONFIG_H'
      ],
      'cflags': [
      ],
      'ldflags': [
      ],
      'include_dirs': [
        "<!(node -e \"require('nan')\")"
      ],
      'libraries': [
        "-lrrd"
      ],
      'xcode_settings': {
      },
    }
  ]
}
