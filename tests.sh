#!/bin/bash
rm -r build/tests
cmake \
    -S . \
    -B build/. \
    -DTARGET_GROUP=tests

cd build
make

echo "=== Running Tests ==="
./tests/tests
