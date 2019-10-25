package(default_visibility = ["//visibility:public"])

cc_library(
  name = "soil_lib",
  hdrs = glob(["include/SOIL/*.h"]),
  srcs = [
    "lib/libsoil.a",
  ],
  linkopts = [
      "-lGL",
  ]
)
