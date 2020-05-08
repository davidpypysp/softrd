#!/bin/bash

if [ "$(uname)" == "Darwin" ]; then
    script_path=$(dirname $(realpath "$0"))
elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
    script_path=$(dirname $(readlink -f "$0"))
fi

function rebuild_middleware() {
    echo 'node-gyp rebuild middleware addon modules'
    cd "$script_path/../middleware"
    ./middleware.sh rebuild
}

function install_addon() {
    rm -rf "$script_path/build"
    echo 'copy middleware addon modules middleware/build -> ./'
    cp -r $script_path/../middleware/build $script_path/
}

function build() {
    cd "$script_path/../middleware"
    ./middleware.sh build
    install_addon
}

function dev() {
    build
    cd "$script_path"
    yarn electron_dev
}

function reinstall() {
    rebuild_middleware
    install_addon
}

function main() {
    local cmd=$1

    case $cmd in
    rebuild_middleware)
        rebuild_middleware $@
        ;;
    install_addon)
        install_addon $@
        ;;
    build)
        build $@
        ;;
    dev)
        dev $@
        ;;
    reinstall)
        reinstall $@
        ;;
    *) ;;

    esac
}

main $@
