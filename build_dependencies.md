# Third party libraries installation

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

In windows we use PowerSheel

Windows use vcpkg to build gflag dependency

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


To run main program, need to copy core/resource/ -> cmake-build/src/
