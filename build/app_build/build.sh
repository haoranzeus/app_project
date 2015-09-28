#!/bin/bash

usage() {
	echo "Usage: build.sh [architecture]"
	echo "	architecture is a directory name in CMakeLists path. defalute is x86."
}

if [ $# -gt 1 ]; then
	usage
	exit -1
fi

cd `dirname $0`

if [ $# -eq 0 ]; then
	architecture=x86
else
	for name in `ls CMakeLists`; do
		if [ $name = $1 ]; then
			architecture=$1
		fi
	done
fi

if [ -z $architecture ]; then
	usage
	exit -1
fi


buildpath=`pwd`
installpath=$buildpath/binary

#rm -rf `ls | grep -v build.sh`
cd buildtmp
rm -rf *
cp ../CMakeLists/$architecture/CMakeLists.txt ../../../source/app
cmake -DCMAKE_INSTALL_PREFIX=$installpath ../../../source/app

make
make install
