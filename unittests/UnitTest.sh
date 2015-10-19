#!/bin/sh
export LD_LIBRARY_PATH=. && valgrind --tool=memcheck --leak-check=full --track-origins=yes ./UnitTests -v -c