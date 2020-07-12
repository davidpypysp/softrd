# build docker image
```
# In repo root dir

# docker-compose start dev container
docker-compose run --service-ports softrd-dev bash

# docker into current container
docker exec -it {CONTAINER_ID} bash

# build dev image
docker build -t davidpy1992/softrd-dev -f docker/softrd-dev.dockerfile .

# build dist image
docker build -t davidpy1992/softrd-dist -f docker/softrd-dist.dockerfile .
```

# emscripten build

linux
```
source ~/emsdk/emsdk_env.sh

cd core
mkdir build-wasm
emcmake cmake ..
emmake make -j
emmake make install
```

windows

```
~/emsdk/emsdk.ps1 activate latest

cd core
mkdir build-wasm
emcmake cmake ..
emmake make -j

em++ --bind  ..\embind\embind_renderer_api.cc -I../ -I..\wasm_libs\assimp-wasm\assimp-es-dyn\include\ -I..\wasm_libs\SOIL-wasm\include\ -lSoftrdAPIStatic -L. -o embind_renderer_api.js

emrun --no_browser --port 8080 .

```



# Third party libraries installation

vcpkg install
```
# in vcpkg repo path
vcpkg install abseil gtest glog soil assimp
```

build cmake with vcpkg
```
cmake -DCMAKE_TOOLCHAIN_FILE=[vcpkg root]\scripts\buildsystems\vcpkg.cmake ..
```

## Linux

install SDL2
```
sudo apt-get install libsdl2-dev
```

install SDL2_ttf
```
sudo apt-get install libsdl2-ttf-dev
```

install assimp
```
sudo apt-get install libassimp-dev
```

install soil
```
sudo apt-get install libsoil-dev
```

For building SOIL from source code, need to install GL library.
```
sudo apt install mesa-common-dev
```

## Mac

install SDL2
```
brew install SDL2
```

## install SDL2_ttf
```
brew install SDL2_ttf
```

# install assimp
```
brew install assimp
```


libSOIL need to build from source: https://github.com/littlstar/soil
```
git clone https://github.com/childhood/libSOIL.git
cd libSOIL-master
make 
sudo make install
```

## Windows

In windows we use PowerShell

vcpkg install dependencies
```
# Windows
./vcpkg.exe --triplet x64-windows install assimp abseil gtest glog soil 

# Linux
./vcpkg install assimp abseil gtest glog soil 
```

CMake process:
```
cd core
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=C:/Users/david/working/vcpkg/scripts/buildsystems/vcpkg.cmake    
```

MSBuild process:
```
 # by using cmake 
 cmake --build . --config Release -v -j8

 # by using msbuild
 & 'C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\MSBuild\Current\Bin\MSBuild.exe' softrd.sln /m /property:Configuration=Release
```

Install process:
```
# in build directory
cmake --install .
```

## Middleware build process
```
# configure CMakeLists.txt and build code
yarn cmake build  

# install library and dependencies
cmake --install build    

```


To run main program, need to copy core/resource/ -> cmake-build/src/
