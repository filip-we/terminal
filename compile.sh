#!/bin/bash
rm -r build/*
cmake -S src/. -B build/.
cd build
make
cd ..

read -p "Upload to "$1"?" -n 1 -r
echo    # (optional) move to a new line
if [[ $REPLY =~ ^[Yy]$ ]]
then
    cp build/terminal.uf2 $1
fi

