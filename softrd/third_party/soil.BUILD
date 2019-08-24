
cc_library(
  name = "soil_lib",
  hdrs = glob(["include/SOIL/*.h"]),
  visibility = ["//visibility:public"],
  deps = [
    ":soil_lib_impl"
  ],
)

cc_import(
  name = "soil_lib_impl",
  static_library = "lib/libsoil.a",
  visibility = ["//visibility:private"],
)

