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


To run main program, need to copy core/resource/ -> cmake-build/src/
