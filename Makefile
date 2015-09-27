# The MIT License (MIT)
#
# Copyright (c) 2015 André Netzeband
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

#########################################################################################
#
# This Makefile is a tool for creating releases. It will not build the library.
# Use CMake to build the library!
#
#########################################################################################

include Settings.mk

GREEN=\033[00;32m
LGREEN=\033[01;32m
RED=\033[03;31m
NORMAL=\033[03;0m
BLUE=\033[01;34m
VIOLET=\033[01;35m

VERSION ?= ${shell cat version.txt}
VERSION_MAJOR=`echo x${VERSION}x | sed -e "s/x\([0-9]\+\)\.\([0-9]\+\)\.\([0-9]\+\)x/\\1/g"`
VERSION_MINOR=`echo x${VERSION}x | sed -e "s/x\([0-9]\+\)\.\([0-9]\+\)\.\([0-9]\+\)x/\\2/g"`
VERSION_STABILIZATION=`echo x${VERSION}x | sed -e "s/x\([0-9]\+\)\.\([0-9]\+\)\.\([0-9]\+\)x/\\3/g"`
VERSION_TAG=v${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_STABILIZATION}

VERSION_FILE=${REPRO_DIR}/CMake/Version.cmake
VERSION_FILE_TEMPLATE=Version.cmake.in
RELEASE_NOTES_TAMPLATE=release_notes.in

DOXYGEN_DIR=${DOXYGEN_INSTALL}/Doxygen/html
DOXYGEN_FILE=${DOXYGEN_DIR}/index.html
DOXYGEN_OUT_DIR=${REPRO_DIR}/Doxygen/html

RELEASE_DIR=Binary

.PHONY: help
help:
	@echo ""
	@echo " This makefile is a tool for creating releases, not for building the library!"
	@echo ""
	@echo " Workflow:"
	@echo "  1. prepare_release = prepares a new release, set VERSION=x.y.z"
	@echo "  2. release         = releases binaries, examples and doxygen"
	@echo "  3. tag_all         = creates a version tag for all branches"
	@echo "  4. push_release    = pushes the release to the server"
	@echo ""
	@echo " Available sub-targets:"
	@echo "   release_doxygen   = releases the doxygen documentation"
	@echo "   release_bin       = releases all available library binaries"
	@echo "   release_includes  = releases the include directory"
	@echo "   release_examples  = releases two versions of examples (linux and windows)"
	@echo "   release_notes     = merges the release notes into README.md"
	@echo "   create_binary_zip = creates a binary zip"
	@echo "   tag_doxygen       = creates a version tag for doxygen"
	@echo "   tag_source        = creates a version tag for the sources"
	@echo "   tag_tools         = creates a version tag for the release tools"
	@echo ""
	
.PHONY: release_doxygen
release_doxygen: check_version_number
	@echo ""
	@echo "Release doxygen documentation..."
	@make --no-print-directory test_if_doxygen_is_uptodate 
	@rm -fR ${DOXYGEN_OUT_DIR}/*
	@cp -vR ${DOXYGEN_DIR}/* ${DOXYGEN_OUT_DIR}
	@echo -e "${LGREEN}Doxygen ready...${NORMAL}"

.PHONY: release_bin
release_bin: 
	@echo ""
	@echo "Release library binaries..."
	@-rm -Rv ${RELEASE_DIR}/lib	
	@-rm -Rv ${RELEASE_DIR}/bin
	@echo "#### Tested Build Variants" > binaries.txt
	@for DIR in ${INSTALL_DIRS} ; do \
		make --no-print-directory release_bin_dir INSTALL_DIR="$$DIR" ; \
		if [ "$$?" -ne 0 ]; then echo -e "${BLUE}Skip uncompiled version${NORMAL}"; fi; \
	done

_NAME=Unknown
INSTALL_DIR_LIBTYPE=${shell basename ${INSTALL_DIR}}
INSTALL_DIR_PREV=${shell dirname ${INSTALL_DIR}}
INSTALL_DIR_DEBUGTYPE=${shell basename ${INSTALL_DIR_PREV}}
INSTALL_DIR_PREV_PREV=${shell dirname ${INSTALL_DIR_PREV}}
INSTALL_DIR_COMPILER=${shell basename ${INSTALL_DIR_PREV_PREV}}
INSTALL_DIR_VERSION=${shell cat ${INSTALL_DIR}/version.txt}
.PHONY: release_bin_dir
release_bin_dir: check_version_number
	@echo Release installation from: ${INSTALL_DIR}
	@echo -e "${VIOLET}Compiler: ${INSTALL_DIR_COMPILER}; Target: ${INSTALL_DIR_DEBUGTYPE}; Library: ${INSTALL_DIR_LIBTYPE}${NORMAL}"
	@echo Installation version: ${INSTALL_DIR_VERSION}
	@if [ "${INSTALL_DIR_VERSION}" != "${VERSION}" ]; then echo -e "${RED}ERROR:${NORMAL} Wrong version, cannot install binary!"; exit -1; fi
	@make --no-print-directory release_bin_static_lib ; 
	@if [ "${INSTALL_DIR_LIBTYPE}" == "shared" ]; then make --no-print-directory release_bin_shared_lib ; fi
	@echo "* $($(INSTALL_DIR_COMPILER)_NAME): ${INSTALL_DIR_DEBUGTYPE}, ${INSTALL_DIR_LIBTYPE} library" >> binaries.txt
	@echo -e "${LGREEN}Binary for this compiler is ready...${NORMAL}"

RELEASE_DIR_STATIC_LIB=${RELEASE_DIR}/lib/${INSTALL_DIR_COMPILER}/${INSTALL_DIR_DEBUGTYPE}-${INSTALL_DIR_LIBTYPE}
.PHONY: release_bin_static_lib
release_bin_static_lib:
	@-rm -Rv ${RELEASE_DIR_STATIC_LIB}
	@mkdir -p ${RELEASE_DIR_STATIC_LIB}
	@cp -v ${INSTALL_DIR}/lib/* ${RELEASE_DIR_STATIC_LIB}

RELEASE_DIR_SHARED_LIB=${RELEASE_DIR}/bin/${INSTALL_DIR_COMPILER}/${INSTALL_DIR_DEBUGTYPE}-${INSTALL_DIR_LIBTYPE}
.PHONY: release_bin_shared_lib
release_bin_shared_lib:
	@if [ -d ${INSTALL_DIR}/bin ]; then   \
	  rm -Rv ${RELEASE_DIR_SHARED_LIB};   \
	  mkdir -p ${RELEASE_DIR_SHARED_LIB}; \
	  cp -v ${INSTALL_DIR}/bin/* ${RELEASE_DIR_SHARED_LIB}; \
	fi
	
INCLUDE_OUT_DIR=${RELEASE_DIR}/includes
INCLUDES_VERSION=${shell cat ${INCLUDE_INSTALL}/version.txt}
.PHONY: release_includes
release_includes: check_version_number
	@echo ""
	@echo "Release include files..."
	@echo Installation version: ${INCLUDES_VERSION}
	@if [ "${INCLUDES_VERSION}" != "${VERSION}" ]; then echo -e "${RED}ERROR:${NORMAL} Wrong version, cannot install includes!"; exit -1; fi
	@-rm -fR ${INCLUDE_OUT_DIR}/*
	@mkdir -p ${INCLUDE_OUT_DIR}
	@cp -vR ${INCLUDE_INSTALL}/includes/* ${INCLUDE_OUT_DIR}
	@echo -e "${LGREEN}Includes ready...${NORMAL}"

.PHONY: release_examples
release_examples: 
	@echo ""
	@echo "Release examples..."
	@-rm -Rv ${RELEASE_DIR}/examples
	@mkdir -p ${RELEASE_DIR}/examples
	@cp -vR ${MEDIA_DIR}/media ${RELEASE_DIR}/examples/
	@for DIR in ${EXAMPLES_DIR} ; do \
		make --no-print-directory release_example_dir EXAMPLE_DIR="$$DIR" ; \
		if [ "$$?" -ne 0 ]; then exit -1; fi; \
	done
	
EXAMPLE_DIR_LIBTYPE=${shell basename ${EXAMPLE_DIR}}
EXAMPLE_DIR_PREV=${shell dirname ${EXAMPLE_DIR}}
EXAMPLE_DIR_DEBUGTYPE=${shell basename ${EXAMPLE_DIR_PREV}}
EXAMPLE_DIR_PREV_PREV=${shell dirname ${EXAMPLE_DIR_PREV}}
EXAMPLE_DIR_COMPILER=${shell basename ${EXAMPLE_DIR_PREV_PREV}}
EXAMPLE_DIR_VERSION=${shell cat ${EXAMPLE_DIR}/version.txt}
RELEASE_DIR_EXAMPLE=${RELEASE_DIR}/examples/${EXAMPLE_DIR_COMPILER}
.PHONY: release_example_dir
release_example_dir: check_version_number
	@echo Release examples from: ${EXAMPLE_DIR}
	@echo -e "${VIOLET}Compiler: ${EXAMPLE_DIR_COMPILER}; Target: ${EXAMPLE_DIR_DEBUGTYPE}; Library: ${EXAMPLE_DIR_LIBTYPE}${NORMAL}"
	@echo Installation version: ${EXAMPLE_DIR_VERSION}
	@if [ "${EXAMPLE_DIR_VERSION}" != "${VERSION}" ]; then echo -e "${RED}ERROR:${NORMAL} Wrong version, cannot install examples!"; exit -1; fi
	@mkdir -p ${RELEASE_DIR_EXAMPLE}
	@cp -vR ${EXAMPLE_DIR}/example/* ${RELEASE_DIR_EXAMPLE}/
	@echo -e "${LGREEN}Example for this compiler is ready...${NORMAL}"	

.PHONY: release_notes
release_notes: check_version_number
	@echo "Start mergin release notes from binaries.txt and extra_release_notes.txt"
	@echo "into ${REPRO_DIR}/README.md..."
	@python merge_release_notes.py -b binaries.txt -e extra_release_notes.txt -o ${REPRO_DIR}/README.md
	@cp -fv README.md ${REPRO_DIR}/README.md
	@echo -e "${LGREEN}Merged release notes...${NORMAL}"	
	
.PHONY: create_binary_zip	
create_binary_zip: check_version_number
	@echo "Create ZIP file..."
	@-rm -Rv irrimgui-${VERSION_TAG}.zip
	@7z a -r -tzip irrimgui-${VERSION_TAG}.zip Binary
	@echo -e "${LGREEN}Created ZIP file...${NORMAL}"	

.PHONY: release	
release: check_version_number
	@echo -e "${VIOLET} Release doxygen documentation ${NORMAL}"
	@make --no-print-directory release_doxygen
	@echo -e "${VIOLET} Release library binary ${NORMAL}"
	@make --no-print-directory release_bin
	@echo -e "${VIOLET} Release library includes ${NORMAL}"
	@make --no-print-directory release_includes
	@echo -e "${VIOLET} Release library examples ${NORMAL}"
	@make --no-print-directory release_examples
	@echo -e "${VIOLET} Create release notes ${NORMAL}"
	@make --no-print-directory release_notes
	@echo -e "${VIOLET} Create binary archive ${NORMAL}"
	@make --no-print-directory create_binary_zip
	
.PHONY: tag_doxygen	
tag_doxygen: check_version_number
	@cd ${DOXYGEN_OUT_DIR} && git add .
	@-cd ${DOXYGEN_OUT_DIR} && git commit -a -m "Release ${VERSION}"
	@cd ${DOXYGEN_OUT_DIR} && git tag ${VERSION_TAG}-doxygen
	
.PHONY: tag_source
tag_source: check_version_number
	@make --no-print-directory test_if_no_changed_files 
	@cd ${REPRO_DIR} && git tag -a ${VERSION_TAG} -m "Release ${VERSION}"
	
.PHONY: tag_tools
tag_tools: check_version_number
	@make --no-print-directory test_if_no_changed_files_here 
	@git tag ${VERSION_TAG}-tools

.PHONY: tag_all
tag_all: check_version_number
	@echo -e "${VIOLET} Create tag for Tools ${NORMAL}"
	@make --no-print-directory tag_tools
	@echo -e "${VIOLET} Create tag for Source ${NORMAL}"
	@make --no-print-directory tag_source
	@echo -e "${VIOLET} Create tag for Doxygen ${NORMAL}"
	@make --no-print-directory tag_doxygen 
	
.PHONY: push_release
push_release: check_version_number
	@echo -e "${VIOLET} Push to doxygen branch ${NORMAL}"
	@cd ${DOXYGEN_OUT_DIR} && git push origin
	@cd ${DOXYGEN_OUT_DIR} && git push origin ${VERSION_TAG}-doxygen
	@echo -e "${VIOLET} Push to tools branch ${NORMAL}"
	@git push origin
	@git push origin ${VERSION_TAG}-tools
	@echo -e "${VIOLET} Push to source branch ${NORMAL}"
	@cd ${REPRO_DIR} && git push origin
	@cd ${REPRO_DIR} && git push origin ${VERSION_TAG}
	
.PHONY: prepare_release
prepare_release: check_version_number
	@echo ""
	@echo "***************************************************************************"
	@echo "** Prepare new release                                                   "
	@echo "** Version:  ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_STABILIZATION}   "
	@echo "** Tag:     ${VERSION_TAG}                                               "
	@echo "***************************************************************************"
	@echo ""
	@read -r -p "Is this version number correct? (yes) " SURE; \
	if [ "$$SURE" != "yes" ]; then echo -e "${RED}ERROR:${NORMAL} User canceled release preparation!"; exit -1; fi
	@make --no-print-directory test_if_version_exists 
	@make --no-print-directory test_if_no_changed_files 
	@echo -n "Clean-up last release... "
	@-rm -R ${RELEASE_DIR}
	@-rm version.txt
	@-rm binaries.txt
	@cat ${RELEASE_NOTES_TAMPLATE} > extra_release_notes.txt
	@echo -e "${GREEN}done${NORMAL}"
	@echo -n "Write version related files... "
	@echo "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_STABILIZATION}" > version.txt
	@echo "# edit the following three version numbers" > ${VERSION_FILE}
	@echo "SET(VERSION_MAJOR ${VERSION_MAJOR})" >> ${VERSION_FILE}
	@echo "SET(VERSION_MINOR ${VERSION_MINOR})" >> ${VERSION_FILE}
	@echo "SET(VERSION_RELEASE ${VERSION_STABILIZATION})" >> ${VERSION_FILE}
	@echo "" >> ${VERSION_FILE}
	@cat ${VERSION_FILE_TEMPLATE} >> ${VERSION_FILE}
	@echo -e "${GREEN}done${NORMAL}"

	
.PHONY: check_version_number
check_version_number:
	@if [ "${VERSION_MAJOR}" == "${VERSION}" ]; then echo -e "${RED}ERROR:${NORMAL} Please specify version number!"; exit -1; fi
	@if [ "${VERSION_MINOR}" == "${VERSION}" ]; then echo -e "${RED}ERROR:${NORMAL} Please specify version number!"; exit -1; fi
	@if [ "${VERSION_STABILIZATION}" == "${VERSION}" ]; then echo -e "${RED}ERROR:${NORMAL} Please specify version number!"; exit -1; fi	
	@if [ "${VERSION_MAJOR}" == "xx" ]; then echo -e "${RED}ERROR:${NORMAL} Please specify version number!"; exit -1; fi
	@if [ "${VERSION_MINOR}" == "xx" ]; then echo -e "${RED}ERROR:${NORMAL} Please specify version number!"; exit -1; fi
	@if [ "${VERSION_STABILIZATION}" == "xx" ]; then echo -e "${RED}ERROR:${NORMAL} Please specify version number!"; exit -1; fi		
	
NUMBER_OF_TAGS=${shell cd ${REPRO_DIR} && git tag | grep ${VERSION_TAG} | wc -l}	
.PHONY: test_if_version_exists
test_if_version_exists:
#	@echo ${NUMBER_OF_TAGS}
	@echo -n "Git: Check for version tag ${VERSION_TAG}... "
	@if [ "${NUMBER_OF_TAGS}" "-gt" "0" ]; then echo -e "${RED}fail${NORMAL}"; echo -e "${RED}ERROR:${NORMAL} Version already exists on git!"; exit -1; fi
	@echo -e "${GREEN}done${NORMAL}"
	
CHANGED_FILES=${shell cd ${REPRO_DIR} && git status --porcelain | wc -l}
.PHONY: test_if_no_changed_files
test_if_no_changed_files:
	@echo -n "Check how many files are changed... "
	@if [ "${CHANGED_FILES}" -gt "0" ]; then echo -e "${RED}fail${NORMAL}"; echo -e "${RED}ERROR:${NORMAL} ${CHANGED_FILES} changed files. Please commit first!"; exit -1; fi
	@echo -e "${GREEN}done${NORMAL}"

CHANGED_FILES_HERE=${shell git status --porcelain | wc -l}
.PHONY: test_if_no_changed_files_here
test_if_no_changed_files_here:
	@echo -n "Check how many files are changed... "
	@if [ "${CHANGED_FILES_HERE}" -gt "0" ]; then echo -e "${RED}fail${NORMAL}"; echo -e "${RED}ERROR:${NORMAL} ${CHANGED_FILES_HERE} changed files. Please commit first!"; exit -1; fi
	@echo -e "${GREEN}done${NORMAL}"
	
CHECK_DOXYGEN_VERSION=${shell cat ${DOXYGEN_FILE} | grep "<span id=\"projectnumber\">" | sed -s "s/.*<span id=\"projectnumber\">\([0-9]\+\).\([0-9]\+\).\([0-9]\+\)<\/span>/\1.\2.\3/g"}
.PHONY: test_if_doxygen_is_uptodate
test_if_doxygen_is_uptodate:
	@echo -n "Check version of doxygen file... "
	@if [ ! -e "${DOXYGEN_FILE}" ]; then echo -e "${RED}fail${NORMAL}"; echo -e "${RED}ERROR:${NORMAL} Doxygen file ${DOXYGEN_FILE} does not exist!"; exit -1; fi
	@if [ "${CHECK_DOXYGEN_VERSION}" != "${VERSION}" ]; then echo -e "${RED}fail${NORMAL}"; echo -e "${RED}ERROR:${NORMAL} Found doxygen version ${CHECK_DOXYGEN_VERSION} but expected version ${VERSION}!"; exit -1; fi
	@echo -e "${GREEN}done${NORMAL}"
