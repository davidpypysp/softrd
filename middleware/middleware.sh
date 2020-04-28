#!/bin/bash

if [ "$(uname)" == "Darwin" ]; then
    script_path=$(dirname $(realpath "$0"))
    core_path=$(realpath "${script_path}/../core/")
elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
    script_path=$(dirname $(readlink -f "$0"))
    core_path=$(readlink -f "${script_path}/../core/")
fi

function build_core() {
    ${core_path}/core.sh build
}

function build_node() {
    echo 'build_node in ' $script_path
    cd $script_path
    node-gyp rebuild
}

function build() {
    build_core
    build_node
}

function rebuild() {
    rm -rf "$core_path/build"
    rm -rf "$script_path/build"
    build
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
    build)
        build $@
        ;;
    rebuild)
        rebuild $@
        ;;
    *) ;;

    esac
}

main $@
