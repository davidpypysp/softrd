package(default_visibility = ["//visibility:public"])

cc_import(
  name = "assimp_lib",
  hdrs= glob([
    "include/assimp/*.h",
    "include/assimp/*.inl",
    "include/assimp/*.hpp",
    "include/assimp/Compiler/*.h",
  ]),
  shared_library = "lib/libassimp.so",
)