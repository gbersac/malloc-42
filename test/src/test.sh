#! /bin/bash
#
# test.sh
# Copyright (C) 2015 gbersac <gbersac@e2r3p18.42.fr>
#
# Distributed under terms of the MIT license.
#

function get_page_claim()
{
	get_./run.sh /usr/bin/time -l ./bin/$1 | grep "page reclaims"

}

test_files=( test0.c test1.c test3.c test4.c test5.c )
inc="../../inc/"

#################################################################
# compilation
rm -rf bin
mkdir bin
for file in ${test_files[@]}
do
	echo ${file}
	gcc -o bin/${file} ${file} -I ${inc}
done

#################################################################
# test malloc

