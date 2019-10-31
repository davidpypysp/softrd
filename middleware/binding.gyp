{
  "targets": [
    {
      "target_name": "hello",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [ "src/hello.cc" ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      'dependencies': ["<!(node -p \"require('node-addon-api').gyp\")"],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
    },
    {
      "target_name": "SoftrdJs",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [ "src/addon_init.cc", "src/renderer_api_addon.cc" ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")",
        "<!(pwd)/../core/"
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
      'library_dirs': [
          '<!(pwd)/build-core/src/interface',
      ],
      "libraries": [ "<!(pwd)/build-core/src/interface/libSoftrdAPI.so" ]
      # "libraries": [ "-L<!(pwd)/../core/build-cmake/src", "-lSoftrdAPI" ]
      # "libraries": [ "<!(pwd)/../core/bazel-bin/src/interface/libSoftrdAPI.so" ],
    }
  ]
}