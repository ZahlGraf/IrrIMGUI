#!/bin/bash

# download server
SERVER=http://irrimgui.netzeband.eu/travis-dep

# dependency versions
IMGUI_VER=imgui-1.4.6
IRRLICHT_VER=irrlicht-1.8.3
CPPUTEST_VER=cpputest-3.7.1

# goto build directory
cd ${TRAVIS_BUILD_DIR}

# setup dependency directory
mkdir -p travis-dep
mkdir -p ${HOME}/.cache

# install imgui
if [ ! -f ${HOME}/.cache/${IMGUI_VER}.zip ]; then  
  wget ${SERVER}/${IMGUI_VER}.zip -O ${HOME}/.cache/${IMGUI_VER}.zip 
fi
cp ${HOME}/.cache/${IMGUI_VER}.zip travis-dep/imgui.zip
unzip travis-dep/imgui.zip -d travis-dep
rm travis-dep/imgui.zip
cp -fR travis-dep/${IMGUI_VER}/* ${TRAVIS_BUILD_DIR}/dependency/IMGUI
rm -R travis-dep/${IMGUI_VER}

# install irrlicht
if [ ! -f ${HOME}/.cache/${IRRLICHT_VER}.zip ]; then  
  wget ${SERVER}/${IRRLICHT_VER}.zip -O ${HOME}/.cache/${IRRLICHT_VER}.zip 
fi
cp ${HOME}/.cache/${IRRLICHT_VER}.zip travis-dep/irrlicht.zip
unzip travis-dep/irrlicht.zip -d travis-dep
rm travis-dep/irrlicht.zip
cp -fR travis-dep/${IRRLICHT_VER} travis-dep/irrlicht
rm -R travis-dep/${IRRLICHT_VER}

# install cpputest
if [ ! -f ${HOME}/.cache/${CPPUTEST_VER}.zip ]; then  
  wget ${SERVER}/${CPPUTEST_VER}.zip -O ${HOME}/.cache/${CPPUTEST_VER}.zip 
fi
cp ${HOME}/.cache/${CPPUTEST_VER}.zip travis-dep/cpputest.zip
unzip travis-dep/cpputest.zip -d travis-dep
rm travis-dep/cpputest.zip
cp -fR travis-dep/${CPPUTEST_VER} travis-dep/cpputest
rm -R travis-dep/${CPPUTEST_VER}