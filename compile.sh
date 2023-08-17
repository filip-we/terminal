#!/bin/bash
rm -r build/rp_pico_drivers
rm -r build/rp_pico_program
rm -r build/terminal

cmake \
    -S . \
    -B build/. \
    -DTARGET_GROUP=$2

cd build
make

cd ..
read -p "Upload to "$1"?" -n 1 -r
echo    # (optional) move to a new line
if [[ $REPLY =~ ^[Yy]$ ]]
then
    sudo mount -o gid=users,fmask=113,dmask=002 $1 .rpi-rp2
    sudo cp build/rp_pico_program/rp_pico_program.uf2 .rpi-rp2
    sudo umount .rpi-rp2
fi

#openocd -f interface/raspberrypi-swd.cfg \
#-f target/rp2040.cfg \
#-c "program build/rp_pico_program/rp_pico_program.elf verify reset exit"

