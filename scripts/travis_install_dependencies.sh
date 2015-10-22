#!/bin/bash
#set -ev

# goto build directory
cd ${TRAVIS_BUILD_DIR}

# setup dependency directory
mkdir -p travis-dep

# install irrlicht
wget http://irrimgui.netzeband.eu/travis-dep/irrlicht-1.8.3.zip -O travis-dep/irrlicht.zip
unzip travis-dep/irrlicht.zip -d travis-dep
rm travis-dep/irrlicht.zip

# install cpputest
wget http://irrimgui.netzeband.eu/travis-dep/cpputest-3.7.1.zip -O travis-dep/cpputest.zip
unzip travis-dep/cpputest.zip -d travis-dep
rm travis-dep/cpputest.zip