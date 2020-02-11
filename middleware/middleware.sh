#!/bin/bash

script_path=$(dirname $(readlink -f "$0"))
core_path=$(readlink -f "${script_path}/../core/")

function build_core() {
    ${core_path}/core.sh build
    echo "copy ${core_path}/build-cmake/src/interface/libSoftrdAPI.so -> /usr/lib"
    cp ${core_path}/build-cmake/src/interface/libSoftrdAPI.so /usr/lib
}

function build_node() {
    echo 'build_node in ' $script_path
    cd $script_path
    node-gyp rebuild
}

function rebuild() {
    rm -rf "$core_path/build-cmake"
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
