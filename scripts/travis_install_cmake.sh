#!/bin/bash

# goto build directory
cd ${TRAVIS_BUILD_DIR}

# download cmake
mkdir -p travis-dep
wget http://www.cmake.org/files/v3.2/cmake-3.2.2-Linux-x86_64.tar.gz -O travis-dep/cmake.tar.gz

# unzip cmake
tar xf cmake-3.2.2-Linux-x86_64.tar.gz -C travis-dep

# install cmake on vm
sudo cp -r travis-dep/cmake-3.2.2-Linux-x86_64/* /usr/local

# clean up
rm travis-dep/cmake.tar.gz