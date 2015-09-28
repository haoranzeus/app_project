#!/bin/bash

usage() {
	echo "Usage: build.sh [architecture] <matrix_element>"
	echo "	architecture:	A directory name in CMakeLists path. default is x86."
	echo "	matrix_element:	A directory name below source/strategy_matrix/<matrix_row>/"	
}

check_matrix() {
	row=$1
	for name in `ls ../../source/strategy_matrix`; do
		if [ $name = ${row%_*} ]; then
			row=$name
		fi
	done
}

if [ $# -gt 2 ]; then
	usage
	exit -1
fi

cd `dirname $0`

if [ $# -eq 1 ]; then
	architecture=x86
	cloumn=$1
	check_matrix $1
else
	for name in `ls CMakeLists`; do
		if [ $name = $1 ]; then
			architecture=$1
			cloumn=$2
			check_matrix $2
		fi
	done
fi

if [ -z $architecture ] || [ -z $row ]; then
	usage
	exit -1
fi

buildpath=`pwd`
installpath=$buildpath/binary/$row/$cloumn

cd $buildpath/buildtmp
rm -rf *
cp ../CMakeLists/$architecture/CMakeLists.txt ../../../source/strategy_matrix/$row/$cloumn
cmake -DCMAKE_INSTALL_PREFIX=$installpath ../../../source/strategy_matrix/$row/$cloumn

make
make install
