REPRO_DIR=..
INSTALL_DIR=${REPRO_DIR}/install
INSTALL_DIRS =

#####################################################
## Visual C++ 2015 (Windows7 64bit)
#####################################################
msvc2015-win64_NAME=Visual C++ 2015 (64bit)
MSVC2015WIN64_DEBUG_STATIC=${INSTALL_DIR}/msvc2015-win64/debug/static
MSVC2015WIN64_DEBUG_SHARED=${INSTALL_DIR}/msvc2015-win64/debug/shared
MSVC2015WIN64_RELEASE_STATIC=${INSTALL_DIR}/msvc2015-win64/release/static
MSVC2015WIN64_RELEASE_SHARED=${INSTALL_DIR}/msvc2015-win64/release/shared

#####################################################
## Visual C++ 2015 (Windows7 32bit)
#####################################################
msvc2015-win32_NAME=Visual C++ 2015 (32bit)
MSVC2015WIN32_DEBUG_STATIC=${INSTALL_DIR}/msvc2015-win32/debug/static
MSVC2015WIN32_DEBUG_SHARED=${INSTALL_DIR}/msvc2015-win32/debug/shared
MSVC2015WIN32_RELEASE_STATIC=${INSTALL_DIR}/msvc2015-win32/release/static
MSVC2015WIN32_RELEASE_SHARED=${INSTALL_DIR}/msvc2015-win32/release/shared

#####################################################
## MinGW (Windows7 32bit)
#####################################################
mingw-win32_NAME=MinGW (32bit)
MINGWWIN32_DEBUG_STATIC=${INSTALL_DIR}/mingw-win32/debug/static
MINGWWIN32_DEBUG_SHARED=${INSTALL_DIR}/mingw-win32/debug/shared
MINGWWIN32_RELEASE_STATIC=${INSTALL_DIR}/mingw-win32/release/static
MINGWWIN32_RELEASE_SHARED=${INSTALL_DIR}/mingw-win32/release/shared

#####################################################
## MinGW (Windows7 64bit)
#####################################################
mingw-win64_NAME=MinGW (64bit)
MINGWWIN64_DEBUG_STATIC=${INSTALL_DIR}/mingw-win64/debug/static
MINGWWIN64_DEBUG_SHARED=${INSTALL_DIR}/mingw-win64/debug/shared
MINGWWIN64_RELEASE_STATIC=${INSTALL_DIR}/mingw-win64/release/static
MINGWWIN64_RELEASE_SHARED=${INSTALL_DIR}/mingw-win64/release/shared

#####################################################
## Intel 16.0 (Windows7 64bit)
#####################################################
intel-win64_NAME=Intel 16.0 (with MSVC 2015) (64bit, Win7)
INTELWIN64_DEBUG_STATIC=${INSTALL_DIR}/intel-win64/debug/static
INTELWIN64_DEBUG_SHARED=${INSTALL_DIR}/intel-win64/debug/shared
INTELWIN64_RELEASE_STATIC=${INSTALL_DIR}/intel-win64/release/static
INTELWIN64_RELEASE_SHARED=${INSTALL_DIR}/intel-win64/release/shared

#####################################################
## GCC (64bit)
#####################################################
gcc-linux64_NAME=GCC (64bit, Linux)
GCCLINUX64_DEBUG_STATIC=${INSTALL_DIR}/gcc-linux64/debug/static
GCCLINUX64_DEBUG_SHARED=${INSTALL_DIR}/gcc-linux64/debug/shared
GCCLINUX64_RELEASE_STATIC=${INSTALL_DIR}/gcc-linux64/release/static
GCCLINUX64_RELEASE_SHARED=${INSTALL_DIR}/gcc-linux64/release/shared

#####################################################
## Native OpenGL renderer versions
#####################################################
msvc2015-win64-opengl_NAME=Visual C++ 2015 (64bit - native OpenGL GUI renderer)
MSVC2015WIN64_RELEASE_SHARED_OGL=${INSTALL_DIR}/msvc2015-win64-opengl/debug/shared

mingw-win32_NAME=MinGW (32bit - native OpenGL GUI renderer)
MINGWWIN32_RELEASE_SHARED_OGL=${INSTALL_DIR}/mingw-win32-opengl/release/static

gcc-linux64_NAME=GCC (64bit, Linux - native OpenGL GUI renderer)
GCCLINUX64_DEBUG_SHARED_OGL=${INSTALL_DIR}/gcc-linux64-opengl/debug/shared

INSTALL_DIRS += ${MSVC2015WIN64_DEBUG_STATIC}
INSTALL_DIRS += ${MSVC2015WIN64_DEBUG_SHARED}
INSTALL_DIRS += ${MSVC2015WIN64_RELEASE_STATIC}
INSTALL_DIRS += ${MSVC2015WIN64_RELEASE_SHARED}

INSTALL_DIRS += ${MSVC2015WIN32_DEBUG_STATIC}
INSTALL_DIRS += ${MSVC2015WIN32_DEBUG_SHARED}
INSTALL_DIRS += ${MSVC2015WIN32_RELEASE_STATIC}
INSTALL_DIRS += ${MSVC2015WIN32_RELEASE_SHARED}

INSTALL_DIRS += ${MINGWWIN32_DEBUG_STATIC}
INSTALL_DIRS += ${MINGWWIN32_DEBUG_SHARED}
INSTALL_DIRS += ${MINGWWIN32_RELEASE_STATIC}
INSTALL_DIRS += ${MINGWWIN32_RELEASE_SHARED}

INSTALL_DIRS += ${MINGWWIN64_DEBUG_STATIC}
INSTALL_DIRS += ${MINGWWIN64_DEBUG_SHARED}
INSTALL_DIRS += ${MINGWWIN64_RELEASE_STATIC}
INSTALL_DIRS += ${MINGWWIN64_RELEASE_SHARED}

INSTALL_DIRS += ${INTELWIN64_DEBUG_STATIC}
INSTALL_DIRS += ${INTELWIN64_DEBUG_SHARED}
INSTALL_DIRS += ${INTELWIN64_RELEASE_STATIC}
INSTALL_DIRS += ${INTELWIN64_RELEASE_SHARED}

INSTALL_DIRS += ${GCCLINUX64_DEBUG_STATIC}
INSTALL_DIRS += ${GCCLINUX64_DEBUG_SHARED}
INSTALL_DIRS += ${GCCLINUX64_RELEASE_STATIC}
INSTALL_DIRS += ${GCCLINUX64_RELEASE_SHARED}

INSTALL_DIRS += ${MSVC2015WIN64_RELEASE_SHARED_OGL}
INSTALL_DIRS += ${MINGWWIN32_RELEASE_SHARED_OGL}
INSTALL_DIRS += ${GCCLINUX64_DEBUG_SHARED_OGL}

EXAMPLES_DIR =
EXAMPLES_DIR += ${MSVC2015WIN32_RELEASE_STATIC}
EXAMPLES_DIR += ${GCCLINUX64_RELEASE_STATIC}

MEDIA_DIR = ${MSVC2015WIN32_RELEASE_STATIC}

DOXYGEN_INSTALL=${MSVC2015WIN64_DEBUG_STATIC}
INCLUDE_INSTALL=${MSVC2015WIN64_DEBUG_STATIC}
