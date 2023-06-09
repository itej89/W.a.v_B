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




mkdir buildv7


export OLD_CC=$CC 
export OLD_CXX=$CXX

export CC=/home/tej/Android/Sdk/ndk-bundle/toolchains/llvm/prebuilt/linux-x86_64/bin/armv7a-linux-androideabi28-clang
export CXX=/home/tej/Android/Sdk/ndk-bundle/toolchains/llvm/prebuilt/linux-x86_64/bin/armv7a-linux-androideabi28-clang++



cd ./buildv7

cmake ..

make -j128


export CC=$OLD_CC 
export CXX=$OLD_CXX


BUILD_DIR=./

walk_dir "$BUILD_DIR"