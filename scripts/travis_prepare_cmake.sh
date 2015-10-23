#!/bin/bash

# goto build directory
cd ${TRAVIS_BUILD_DIR}

# setup build directory
mkdir -p travis-build
cd travis-build

# run cmake
cmake -version
cmake \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_INSTALL_PREFIX=${TRAVIS_BUILD_DIR}/travis-install \
  -DIRRIMGUI_STATIC_LIBRARY=On \
  -DIRRLICHT_INCLUDE_DIR=${TRAVIS_BUILD_DIR}/travis-dep/irrlicht/install/gcc-linux64/debug/static/includes/Irrlicht \
  -DIRRLICHT_LIB_DIR=${TRAVIS_BUILD_DIR}/travis-dep/irrlicht/install/gcc-linux64/debug/static/lib/libIrrlicht.a \
  -DIRRIMGUI_BUILD_UNITTESTS=On \
  -DIRRIMGUI_CPPUTEST_EXTENSION=${TRAVIS_BUILD_DIR}/travis-dep/cpputest/install/gcc-linux64/debug/static/lib/libCppUTestExt.a \
  -DIRRIMGUI_CPPUTEST_MAIN=${TRAVIS_BUILD_DIR}/travis-dep/cpputest/install/gcc-linux64/debug/static/lib/libCppUTest.a \
  -DIRRIMGUI_CPPUTEST_INCLUDE_DIR=${TRAVIS_BUILD_DIR}/travis-dep/cpputest/install/gcc-linux64/debug/static/include \
  ${TRAVIS_BUILD_DIR}


