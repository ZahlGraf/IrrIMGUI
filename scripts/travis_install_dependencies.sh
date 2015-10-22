#!/bin/bash
#set -ev

# setup dependency directory
mkdir -p temp

# install irrlicht
wget http://irrimgui.netzeband.eu/travis-dep/irrlicht-1.8.3.zip -O temp/irrlicht.zip
unzip temp/irrlicht.zip
rm temp/irrlicht.zip

# install cpputest
wget http://irrimgui.netzeband.eu/travis-dep/cpputest-3.7.1.zip -O temp/cpputest.zip
unzip temp/cpputest.zip
rm temp/cpputest.zip