#!/bin/bash

function build_core() {
    if [ ! -d "$PWD/build-core" ]; then
        mkdir "$PWD/build-core"
    fi

    cd "$PWD/build-core"
    cmake "$PWD/../../core"
    make -j8
}

function rebuild() {
    rm -rf "$PWD/build-core"
    build_core
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
