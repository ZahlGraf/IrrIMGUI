#!/bin/bash

# goto build directory
cd ${TRAVIS_BUILD_DIR}

# remove temporary directories
rm -R travis-dep
rm -R travis-build
rm -R travis-install