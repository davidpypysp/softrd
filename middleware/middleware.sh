#!/bin/bash

script_path=$PWD

function build_core() {
    if [ ! -d "$PWD/build-core" ]; then
        mkdir "$PWD/build-core"
    fi

    cd "$PWD/build-core"
    cmake "$PWD/../../core"
    make -j8
}

function build_node() {

    node-gyp rebuild

}

function rebuild() {
    rm -rf "$PWD/build-core"
    build_core

    cd $script_path
    build_node
}

function main() {
    local cmd=$1

    case $cmd in
    build_core)
        build_core $@
        ;;
    rebuild)
        rebuild $@
        ;;
    *) ;;

    esac
}

main $@
