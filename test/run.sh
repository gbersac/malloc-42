#! /bin/sh
#
# run.sh
# Copyright (C) 2015 gbersac <gbersac@e2r3p18.42.fr>
#
# Distributed under terms of the MIT license.
#


#!/bin/sh 
export DYLD_LIBRARY_PATH=.
export DYLD_INSERT_LIBRARIES="libft_malloc.so" 
export DYLD_FORCE_FLAT_NAMESPACE=1 
$@

