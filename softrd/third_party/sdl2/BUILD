package(default_visibility = ["//visibility:public"])

cc_import(
  name = "sdl2lib",
  hdrs = ["include/SDL2/SDL.h"],
  static_library = "lib/libSDL2.a",
  # If alwayslink is turned on,
  # libmylib.a will be forcely linked into any binary that depends on it.
  # alwayslink = 1,
)

cc_binary(
  name = "sdl2",
  deps = [":sdl2lib"],
  linkstatic = 1, # default value
)