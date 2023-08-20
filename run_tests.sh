#!/bin/bash
rm -r build/*

cmake \
    -DTARGET_GROUP=tests \
    -S . \
    -B build/.

cd build
make

tests/tests
