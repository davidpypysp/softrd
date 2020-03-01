#!/bin/bash

if [ "$(uname)" == "Darwin" ]; then
    script_path=$(dirname $(realpath "$0"))
elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then 
    script_path=$(dirname $(readlink -f "$0"))
fi

echo "script_path = " $script_path

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
