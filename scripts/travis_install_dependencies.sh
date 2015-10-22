#!/bin/bash
set -ev

# setup dependency directory
mkdir travis-dep

# install irrlicht
wget http://irrimgui.netzeband.eu/travis-dep/irrlicht-1.8.3.zip -O /travis-dep/irrlicht.zip
unzip /travis-dep/irrlicht.zip
rm /travis-dep/irrlicht.zip

# install cpputest
wget http://irrimgui.netzeband.eu/travis-dep/cpputest-3.7.1.zip -O /travis-dep/cpputest.zip
unzip /travis-dep/cpputest.zip
rm /travis-dep/cpputest.zip