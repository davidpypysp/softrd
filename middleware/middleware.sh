#!/bin/bash

script_path=$PWD

function build_core() {

    if [ ! -d "$PWD/build-core" ]; then
        mkdir "$PWD/build-core"
    fi

    cd "$PWD/build-core"
    echo 'build_core in ' $PWD

    cmake "$PWD/../../core"
    make -j8
}

function build_node() {
    echo 'build_node in ' $PWD
    cd $script_path
    node-gyp rebuild

}

function rebuild() {
    rm -rf "$PWD/build-core"
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
