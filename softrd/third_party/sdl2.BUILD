cc_library(
  name = "SDL2",
  hdrs = glob(["include/SDL2/*.h"]),
  srcs = [
    "lib/libSDL2.a"
  ],
  linkopts = [
    "-ldl",
    "-lpthread",
  ],
  visibility = ["//visibility:public"],
)


cc_import(
  name = "SDL2impl",
  static_library = "lib/libSDL2.a",
  visibility = ["//visibility:private"],
)


cc_library(
  name = "SDL2main",
  hdrs = glob(["include/SDL2/*.h"]),
  visibility = ["//visibility:public"],
  deps = [
    ":SDL2mainimpl"
  ],
)


cc_import(
  name = "SDL2mainimpl",
  static_library = "lib/libSDL2main.a",
  visibility = ["//visibility:private"],
)


cc_library(
  name = "SDL2_ttf",
  hdrs = glob(["include/SDL2/*.h"]),
  srcs = [
    "lib/libSDL2_ttf.a",
    "lib/libSDL2_ttf.so",
    "lib/libSDL2_ttf-2.0.so.0",
    "lib/libSDL2_ttf-2.0.so.0.14.1",
  ],
  linkopts = [
  ],
  deps = [
    "@freetype2//:freetype2_lib",
  ],
  visibility = ["//visibility:public"],
)
