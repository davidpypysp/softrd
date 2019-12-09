#!/bin/bash

script_path=$PWD

function build_core() {
    if [ ! -d "$script_path/build-core" ]; then
        mkdir "$script_path/build-core"
    fi

    cd "$script_path/build-core"
    echo 'build_core in ' $PWD

    cmake "$script_path/../core"
    make -j8

    cp $script_path/build-core/src/interface/libSoftrdAPI.so /usr/lib
}

function build_node() {
    echo 'build_node in ' $PWD
    cd $script_path
    node-gyp rebuild

}

function rebuild() {
    rm -rf "$script_path/build-core"
    build_core
    build_node
}

function main() {
    local cmd=$1

    case $cmd in
    build_core)
        build_core $@
        ;;
    build_node)
        build_node $@
        ;;
    rebuild)
        rebuild $@
        ;;
    *) ;;

    esac
}

main $@
