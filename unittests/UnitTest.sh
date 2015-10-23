#!/bin/sh

IRRLICHT_SO_LIB=libIrrlicht.so
IRRIMGUI_SO_LIB=libIrrIMGUI.so

IRRLICHT_SO_LIB_LONG=`ls ${IRRLICHT_SO_LIB}.*.*.* 2> /dev/null`
if [ "${IRRLICHT_SO_LIB_LONG}" != "" ]; then
  IRRLICHT_SO_LIB_SHORT=`ls ${IRRLICHT_SO_LIB}.*.*.* | sed -e "s/\(${IRRLICHT_SO_LIB}\).\([0-9]\+\).\([0-9]\+\).\([0-9]\+\)/\1.\2.\3/g"`

  if [ ! -f "${IRRLICHT_SO_LIB_SHORT}" ]; then
    cp -v ${IRRLICHT_SO_LIB_LONG} ${IRRLICHT_SO_LIB_SHORT}
  fi
fi

IRRIMGUI_SO_LIB_LONG=`ls ${IRRIMGUI_SO_LIB}.*.*.* 2> /dev/null`
if [ "${IRRIMGUI_SO_LIB_LONG}" != "" ]; then
  IRRIMGUI_SO_LIB_SHORT=`ls ${IRRIMGUI_SO_LIB}.*.*.* | sed -e "s/\(${IRRIMGUI_SO_LIB}\).\([0-9]\+\).\([0-9]\+\).\([0-9]\+\)/\1.\2.\3/g"`

  if [ ! -f "${IRRIMGUI_SO_LIB_SHORT}" ]; then
    cp -v ${IRRIMGUI_SO_LIB_LONG} ${IRRIMGUI_SO_LIB_SHORT}
  fi
fi

export LD_LIBRARY_PATH=. && valgrind --tool=memcheck --leak-check=full --track-origins=yes ./UnitTests -v -c