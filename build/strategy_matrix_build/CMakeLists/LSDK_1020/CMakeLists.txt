cmake_minimum_required(VERSION 2.6)
PROJECT(STRATEGY)
SET(CROSS_PATH "/home/haoran/work/apsdk/LSDK/build/gcc-4.3.3/build_mips/staging_dir")

SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_C_COMPILER "${CROSS_PATH}/usr/bin/mips-linux-gcc")
SET(CMAKE_CXX_COMPILER "${CROSS_PATH}/usr/bin/mips-linux-g++")
LINK_DIRECTORIES("${CROSS_PATH}/lib" "${CROSS_PATH}/usr/lib")
INCLUDE_DIRECTORIES("${CROSS_PATH}/usr/include" "${CROSS_PATH}/usr/mips-linux-uclibc/include")

SET(CROSS_ARCHITECTURE "LSDK_1020")
ADD_SUBDIRECTORY(src)
