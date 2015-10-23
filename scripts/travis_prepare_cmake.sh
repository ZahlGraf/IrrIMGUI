#!/bin/bash

# print build configuration
echo "Build configuration:"
echo " - Library mode:  ${LIBRARY_MODE}"
echo " - Build Type:    ${BUILD_TYPE}"
echo " - Native OpenGl: ${NATIVE_OPENGL}"

# get irrlicht version number
IRRLICHT_VER_NUMBER=`echo ${IRRLICHT_VER} | sed -s "s/irrlicht-\([0-9.]\+\)/\1/g"`
echo "Using Irrlicht Version: ${IRRLICHT_VER_NUMBER}"

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
  -DIRRLICHT_BIN_DIR=${TRAVIS_BUILD_DIR}/travis-dep/irrlicht/install/gcc-linux64/debug/static/lib/libIrrlicht.so.${IRRLICHT_VER_NUMBER} \
  -DIRRIMGUI_BUILD_UNITTESTS=On \
  -DIRRIMGUI_CPPUTEST_EXTENSION=${TRAVIS_BUILD_DIR}/travis-dep/cpputest/install/gcc-linux64/debug/static/lib/libCppUTestExt.a \
  -DIRRIMGUI_CPPUTEST_MAIN=${TRAVIS_BUILD_DIR}/travis-dep/cpputest/install/gcc-linux64/debug/static/lib/libCppUTest.a \
  -DIRRIMGUI_CPPUTEST_INCLUDE_DIR=${TRAVIS_BUILD_DIR}/travis-dep/cpputest/install/gcc-linux64/debug/static/include \
  ${TRAVIS_BUILD_DIR}


