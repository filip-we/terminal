#!/bin/bash
rm -r build/*
cmake \
    -S . \
    -B build/.

cd build
make

cd ..
read -p "Upload to "$1"?" -n 1 -r
echo    # (optional) move to a new line
if [[ $REPLY =~ ^[Yy]$ ]]
then
    cp build/rp_pico_program/rp_pico_program.uf2 $1
fi

#openocd -f interface/raspberrypi-swd.cfg \
#-f target/rp2040.cfg \
#-c "program build/rp_pico_program/rp_pico_program.elf verify reset exit"

