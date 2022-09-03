#!/bin/bash
rm -r build/*
cmake -DCMAKE_BUILD_TYPE=Release -S src/. -B build/.
cd build
make
cd ..

read -p "Upload to "$1"?" -n 1 -r
echo    # (optional) move to a new line
if [[ $REPLY =~ ^[Yy]$ ]]
then
    # cp build/terminal.uf2 $1
    openocd -f interface/raspberrypi-swd.cfg \
    -f target/rp2040.cfg \
    -c "program build/terminal.elf verify reset exit"
fi

