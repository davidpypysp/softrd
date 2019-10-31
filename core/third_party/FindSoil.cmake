find_library(GL_LIB GL)

add_library(soil_lib STATIC IMPORTED)
set_target_properties(soil_lib PROPERTIES
    IMPORTED_LOCATION "${CMAKE_MODULE_PATH}/soil/lib/libsoil.a"
    IMPORTED_LINK_INTERFACE_LIBRARIES "${GL_LIB}"
)