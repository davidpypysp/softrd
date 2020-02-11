#!/bin/bash

script_path=$(dirname $(readlink -f "$0"))

function rebuild_middleware() {
    echo 'node-gyp rebuild middleware addon modules'
    cd "$script_path/../middleware"
    ./middleware.sh rebuild

}

function install_addon() {
    echo 'copy middleware addon modules middleware/build -> ./'
    cd $script_path
    cp -r $script_path/../middleware/build $script_path/
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
    reinstall)
        reinstall $@
        ;;
    *) ;;

    esac
}

main $@
