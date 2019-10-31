find_package(Assimp)
find_package(Soil)
# find_package(ThirdParty)

add_library (components model.cc)

target_link_libraries(components assimp_lib)
target_link_libraries(components soil_lib)
