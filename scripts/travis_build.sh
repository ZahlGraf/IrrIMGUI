#!/bin/bash

# print build configuration
echo "Build configuration:"
echo " - Compiler:      ${COMPILER}"
echo " - Library mode:  ${LIBRARY_MODE}"
echo " - Build Type:    ${BUILD_TYPE}"
echo " - Native OpenGl: ${NATIVE_OPENGL}"

SMALL_BUILDTYPE=`echo ${BUILD_TYPE} | tr '[:upper:]' '[:lower:]'`

if [ "${NATIVE_OPENGL}" == "On" ]; then
  COMPILER=${COMPILER}-opengl
fi

# goto build directory
cd ${TRAVIS_BUILD_DIR}/travis-build/${COMPILER}/${SMALL_BUILDTYPE}/${LIBRARY_MODE}

# run build
make install
cd ${TRAVIS_BUILD_DIR}/travis-install/${COMPILER}/${SMALL_BUILDTYPE}/${LIBRARY_MODE}/tests/UnitTests
chmod ugo+x UnitTest.sh
./UnitTest.sh


