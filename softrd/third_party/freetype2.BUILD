cc_library(
  name = "freetype2_lib",
  hdrs = glob([
      "include/freetype2/*.h",
      "include/freetype2/freetype/*.h",
      "include/freetype2/freetype/config/*.h",
  ]),
  srcs = [
    "lib/libfreetype.a",
    "lib/libfreetype.so",
    "lib/libfreetype.so.6",
    "lib/libfreetype.so.6.17.0",
  ],
  linkopts = [
  ],
  deps = [
      "@zlib//:zlib",
  ],
  visibility = ["//visibility:public"],
)

