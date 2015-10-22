#!/bin/bash
set -ev

# install irrlicht
wget http://irrimgui.netzeband.eu/travis-dep/irrlicht-1.8.3.zip -O /tmp/irrlicht.zip
unzip /tmp/irrlicht.zip
rm /tmp/irrlicht.zip

# install cpputest
wget http://irrimgui.netzeband.eu/travis-dep/cpputest-3.7.1.zip -O /tmp/cpputest.zip
unzip /tmp/cpputest.zip
rm /tmp/cpputest.zip