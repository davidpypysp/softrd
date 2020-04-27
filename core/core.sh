#!/bin/bash

if [ "$(uname)" == "Darwin" ]; then
    script_path=$(dirname $(realpath "$0"))
elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
    script_path=$(dirname $(readlink -f "$0"))
fi

build_dir=build-cmake

function build() {
    if [ ! -d "$script_path/$build_dir" ]; then
        mkdir "$script_path/$build_dir"
    fi

    cd "$script_path/$build_dir"
    echo 'build dir: ' $PWD

    cmake "$script_path"
    make -j8
}

function test() {
    cd "$script_path/$build_dir/src"
    GTEST_COLOR=1 ctest -C Debug -V
}

function main() {
    local cmd=$1

    case $cmd in
    build)
        build $@
        ;;
    test)
        test $@
        ;;
    *) ;;
    esac
}

main $@
