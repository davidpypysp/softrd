FROM trzeci/emscripten:latest

# set a directory for the app
WORKDIR /softrd

# install cmake 3.18
ADD https://cmake.org/files/v3.18/cmake-3.18.0-rc1-Linux-x86_64.sh /home/cmake-3.18.0-rc1-Linux-x86_64.sh
RUN sh /home/cmake-3.18.0-rc1-Linux-x86_64.sh --prefix=/opt/cmake --skip-license
RUN rm -f /usr/local/bin/cmake
RUN ln -s /opt/cmake/bin/cmake /usr/local/bin/cmake
RUN rm -f /home/cmake-3.18.0-rc1-Linux-x86_64.sh
RUN cmake --version

# install yarn
RUN npm install -g yarn

