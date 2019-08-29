cc_library(
  name = "freetype2_lib",
  hdrs = glob([
      "include/freetype2/*.h",
      "include/freetype2/freetype/*.h",
      "include/freetype2/freetype/config/*.h",
  ]),
  srcs = [
    "lib/libfreetype.a",
  ],
  linkopts = [
  ],
  deps = [
      "@zlib//:zlib",
  ],
  visibility = ["//visibility:public"],
)

