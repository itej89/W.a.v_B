#!/bin/sh

walk_dir () {
    for pathname in "$1"/*; do
        if [ -d "$pathname" ]; then
            walk_dir "$pathname"
        elif [ -e "$pathname" ]; then
            case "$pathname" in
                *.a|*.doc)
                  cp $pathname ../lib 
            esac
        fi
    done
}



mkdir build

cd ./build

cmake ..

make -j128



BUILD_DIR=./

walk_dir "$BUILD_DIR"