add_library(texture texture.cc)
target_link_libraries(texture math soil GL)

add_library(common model.cc)
target_link_libraries(common math texture assimp)