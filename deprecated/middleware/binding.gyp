{
  "targets": [
    {
      "target_name": "SoftrdJs",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [ "src/addon_init.cc", "src/renderer_api_addon.cc" ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")",
        "<!(pwd)/../core/",
        "<!(pwd)/../core/third_party/abseil-cpp",
        "<!(pwd)/../core/third_party/soil/inc",
        "<!(pwd)/../core/third_party/assimp/include",
        "<!(pwd)/../core/build/third_party/assimp/include",
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
      'link_settings': {
        "libraries": [ 
          "-L<!(pwd)/../core/build/src/interface/ -lSoftrdAPI", 
        ],
        "ldflags": [
          "-Wl,-rpath,<!(pwd)/../core/build/src/interface/",
        ]
      },
    }
  ]
}