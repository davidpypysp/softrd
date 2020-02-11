#!/bin/bash

script_path=$(dirname $(readlink -f "$0"))

function build() {
    if [ ! -d "$script_path/build-cmake" ]; then
        mkdir "$script_path/build-cmake"
    fi

    cd "$script_path/build-cmake"
    echo 'build_cmake in ' $PWD

    cmake "$script_path"
    make -j8
}

function main() {
    local cmd=$1

    case $cmd in
    build)
        build $@
        ;;
    *) ;;
    esac
}

main $@
