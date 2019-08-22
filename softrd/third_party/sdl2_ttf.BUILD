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
  static_library = "lib/ttf.a",
  visibility = ["//visibility:private"],
)

