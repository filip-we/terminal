#!/bin/bash
rm -r build/*

cmake \
    -DTARGET_GROUP=test \
    -S . \
    -B build/.

cd build
make

build/test_runner
