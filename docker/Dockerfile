FROM robertaboukhalil/emsdk:1.39.1

# set a directory for the app
WORKDIR /softrd

# install cmake 3.18
ADD https://cmake.org/files/v3.18/cmake-3.18.0-rc1-Linux-x86_64.sh /home/cmake-3.18.0-rc1-Linux-x86_64.sh
RUN mkdir /opt/cmake
RUN sh /home/cmake-3.18.0-rc1-Linux-x86_64.sh --prefix=/opt/cmake --skip-license
RUN rm -f /usr/local/bin/cmake
RUN ln -s /opt/cmake/bin/cmake /usr/local/bin/cmake
RUN rm -f /home/cmake-3.18.0-rc1-Linux-x86_64.sh
RUN cmake --version

RUN apt-get update && apt-get install -y --no-install-recommends apt-utils

# install yarn
RUN curl -sL https://deb.nodesource.com/setup_4.x | bash 
RUN apt-get install -yq nodejs build-essential
RUN npm install -g yarn

