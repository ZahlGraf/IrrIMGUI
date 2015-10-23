#!/bin/bash

# download server
SERVER=http://irrimgui.netzeband.eu/travis-dep

# dependency versions
echo "Looking for dependencies:"
echo " - ${IMGUI_VER}"
echo " - ${IRRLICHT_VER}"
echo " - ${CPPUTEST_VER}"

# goto build directory
cd ${TRAVIS_BUILD_DIR}

# setup dependency directory
mkdir -p travis-dep
mkdir -p ${HOME}/.cache

# install imgui
if [ ! -f ${HOME}/.cache/${IMGUI_VER}.zip ]; then  
  wget ${SERVER}/${IMGUI_VER}.zip -O ${HOME}/.cache/${IMGUI_VER}.zip 
else
  echo "Found ${IMGUI_VER}.zip in cache. Skip download..."
fi
cp ${HOME}/.cache/${IMGUI_VER}.zip travis-dep/imgui.zip
unzip travis-dep/imgui.zip -d travis-dep
rm -v travis-dep/imgui.zip
cp -fRv travis-dep/${IMGUI_VER}/* ${TRAVIS_BUILD_DIR}/dependency/IMGUI
rm -Rv travis-dep/${IMGUI_VER}

# install irrlicht
if [ ! -f ${HOME}/.cache/${IRRLICHT_VER}.zip ]; then  
  wget ${SERVER}/${IRRLICHT_VER}.zip -O ${HOME}/.cache/${IRRLICHT_VER}.zip 
else
  echo "Found ${IMGUI_VER}.zip in cache. Skip download..."
fi
cp ${HOME}/.cache/${IRRLICHT_VER}.zip travis-dep/irrlicht.zip
unzip travis-dep/irrlicht.zip -d travis-dep
rm -v travis-dep/irrlicht.zip
cp -fRv travis-dep/${IRRLICHT_VER} travis-dep/irrlicht
rm -Rv travis-dep/${IRRLICHT_VER}

# install cpputest
if [ ! -f ${HOME}/.cache/${CPPUTEST_VER}.zip ]; then  
  wget ${SERVER}/${CPPUTEST_VER}.zip -O ${HOME}/.cache/${CPPUTEST_VER}.zip 
else
  echo "Found ${IMGUI_VER}.zip in cache. Skip download..."
fi
cp ${HOME}/.cache/${CPPUTEST_VER}.zip travis-dep/cpputest.zip
unzip travis-dep/cpputest.zip -d travis-dep
rm -v travis-dep/cpputest.zip
cp -fRv travis-dep/${CPPUTEST_VER} travis-dep/cpputest
rm -Rv travis-dep/${CPPUTEST_VER}