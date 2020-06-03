function(add_gtest_exe)
    cmake_parse_arguments(
        PARSED_ARGS
        ""
        "NAME"
        "SRCS;DEPS" 
        ${ARGN} 
    )
    add_executable(${PARSED_ARGS_NAME} ${PARSED_ARGS_SRCS})
    target_link_libraries(${PARSED_ARGS_NAME} GTest::gtest ${PARSED_ARGS_DEPS})
    if(EMSCRIPTEN)
        add_test(NAME ${PARSED_ARGS_NAME} COMMAND node ${PARSED_ARGS_NAME}.js)
    endif()
endfunction(add_gtest_exe)


add_subdirectory(common)
add_subdirectory(modules)
add_subdirectory(renderer)
add_subdirectory(interface)
add_subdirectory(math)
add_subdirectory(scene)