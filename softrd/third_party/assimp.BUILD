package(default_visibility = ["//visibility:public"])

cc_library(
    name = "assimp_lib",
    hdrs= glob([
        "include/assimp/*.h",
        "include/assimp/*.inl",
        "include/assimp/*.hpp",
        "include/assimp/Compiler/*.h",
    ]),
    srcs = [
        "lib/libassimp.so",
        "lib/libassimp.so.4",
        "lib/libassimp.so.4.1.0",
    ],
    linkopts = [
    ],
)