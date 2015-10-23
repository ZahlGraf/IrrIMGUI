#!/bin/bash

# goto build directory
cd ${TRAVIS_BUILD_DIR}

# setup dependency directory
mkdir -p travis-dep
mkdir -p ${HOME}/.cache

# install imgui
if [ ! -f ${HOME}/.cache/imgui-1.4.6.zip ]; then  
  wget http://irrimgui.netzeband.eu/travis-dep/imgui-1.4.6.zip -O ${HOME}/.cache/imgui-1.4.6.zip 
fi
cp ${HOME}/.cache/imgui-1.4.6.zip travis-dep/imgui.zip
unzip travis-dep/imgui.zip -d travis-dep
rm travis-dep/imgui.zip
cp -fR travis-dep/imgui-1.4.6/* ${TRAVIS_BUILD_DIR}/dependency/IMGUI

# install irrlicht
if [ ! -f ${HOME}/.cache/irrlicht-1.8.3.zip ]; then  
  wget http://irrimgui.netzeband.eu/travis-dep/irrlicht-1.8.3.zip -O ${HOME}/.cache/irrlicht-1.8.3.zip 
fi
cp ${HOME}/.cache/irrlicht-1.8.3.zip travis-dep/irrlicht.zip
unzip travis-dep/irrlicht.zip -d travis-dep
rm travis-dep/irrlicht.zip

# install cpputest
if [ ! -f ${HOME}/.cache/cpputest-3.7.1.zip ]; then  
  wget http://irrimgui.netzeband.eu/travis-dep/cpputest-3.7.1.zip -O ${HOME}/.cache/cpputest-3.7.1.zip 
fi
cp ${HOME}/.cache/cpputest-3.7.1.zip travis-dep/cpputest.zip
unzip travis-dep/cpputest.zip -d travis-dep
rm travis-dep/cpputest.zip