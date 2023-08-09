#!/bin/bash
rm -r build/*
TARGET_GROUP=$2
TARGET_GROUP="${TARGET_GROUP:-default}"
cmake \
    -DTARGET_GROUP=$TARGET_GROUP \
    -S . \
    -B build/.

cd build
make

cd ..
read -p "Upload to "$1"?" -n 1 -r
echo    # (optional) move to a new line
if [[ $REPLY =~ ^[Yy]$ ]]
then
    cp build/terminal.uf2 $1
fi

#openocd -f interface/raspberrypi-swd.cfg \
#-f target/rp2040.cfg \
#-c "program build/terminal.elf verify reset exit"

