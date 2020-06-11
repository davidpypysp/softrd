FROM trzeci/emscripten-ubuntu:latest

# set a directory for the app
WORKDIR /softrd

#install latest cmake
ADD https://cmake.org/files/v3.18/cmake-3.18.0-rc1-Linux-x86_64.sh /home/cmake-3.18.0-rc1-Linux-x86_64.sh
RUN mkdir /opt/cmake
RUN sh /home/cmake-3.18.0-rc1-Linux-x86_64.sh --prefix=/opt/cmake --skip-license
RUN ln -s /opt/cmake/bin/cmake /usr/local/bin/cmake
RUN rm -f /home/cmake-3.18.0-rc1-Linux-x86_64.sh
RUN cmake --version

# define the port number the container should expose
EXPOSE 9000
