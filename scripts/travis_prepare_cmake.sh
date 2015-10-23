#!/bin/bash

# print build configuration
echo "Build configuration:"
echo " - Compiler:      ${COMPILER}"
echo " - Library mode:  ${LIBRARY_MODE}"
echo " - Build Type:    ${BUILD_TYPE}"
echo " - Native OpenGl: ${NATIVE_OPENGL}"

SMALL_BUILDTYPE=`echo ${BUILD_TYPE} | tr '[:upper:]' '[:lower:]'`

IRRLICHT_LIBRARY=libIrrlicht.so
BUILD_STATIC=Off
if [ "${LIBRARY_MODE}" == "static" ]; then
  BUILD_STATIC=On
  IRRLICHT_LIBRARY=libIrrlicht.a
fi

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
cmake -LH \
  -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
  -DCMAKE_INSTALL_PREFIX=${TRAVIS_BUILD_DIR}/travis-install \
  -DIRRIMGUI_STATIC_LIBRARY=${BUILD_STATIC} \
  -DIRRLICHT_INCLUDE_DIR=${TRAVIS_BUILD_DIR}/travis-dep/irrlicht/install/${COMPILER}/${SMALL_BUILDTYPE}/${LIBRARY_MODE}/includes/Irrlicht \
  -DIRRLICHT_LIB_DIR=${TRAVIS_BUILD_DIR}/travis-dep/irrlicht/install/${COMPILER}/${SMALL_BUILDTYPE}/${LIBRARY_MODE}/lib/${IRRLICHT_LIBRARY} \
  -DIRRLICHT_BIN_DIR=${TRAVIS_BUILD_DIR}/travis-dep/irrlicht/install/${COMPILER}/${SMALL_BUILDTYPE}/${LIBRARY_MODE}/lib/libIrrlicht.so.${IRRLICHT_VER_NUMBER} \
  -DIRRIMGUI_BUILD_UNITTESTS=On \
  -DIRRIMGUI_CPPUTEST_EXTENSION=${TRAVIS_BUILD_DIR}/travis-dep/cpputest/install/${COMPILER}/${SMALL_BUILDTYPE}/static/lib/libCppUTestExt.a \
  -DIRRIMGUI_CPPUTEST_MAIN=${TRAVIS_BUILD_DIR}/travis-dep/cpputest/install/${COMPILER}/${SMALL_BUILDTYPE}/static/lib/libCppUTest.a \
  -DIRRIMGUI_CPPUTEST_INCLUDE_DIR=${TRAVIS_BUILD_DIR}/travis-dep/cpputest/install/${COMPILER}/${SMALL_BUILDTYPE}/static/include \
  -DIRRIMGUI_NATIVE_OPENGL=${NATIVE_OPENGL} \
  -DIRRIMGUI_FAST_OPENGL_TEXTURE_CREATION=${NATIVE_OPENGL} \
  ${TRAVIS_BUILD_DIR}


