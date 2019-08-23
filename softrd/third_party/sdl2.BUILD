cc_library(
  name = "SDL2",
  hdrs = glob(["include/SDL2/*.h"]),
#   strip_include_prefix = "include/SDL/",
  visibility = ["//visibility:public"],
  deps = [
    ":SDL2impl"
  ],
)


cc_import(
  name = "SDL2impl",
  static_library = "lib/libSDL2.a",
  visibility = ["//visibility:private"],
)


cc_library(
  name = "SDL2main",
  hdrs = glob(["include/SDL2/*.h"]),
#   strip_include_prefix = "include/SDL/",
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
#   strip_include_prefix = "include/SDL/",
  visibility = ["//visibility:public"],
  deps = [
    ":SDL2_ttf_impl"
  ],
)

cc_import(
  name = "SDL2_ttf_impl",
  static_library = "lib/libSDL2_ttf.a",
  visibility = ["//visibility:private"],
)

