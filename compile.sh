#!/bin/bash
rm -r build/rp_pico_drivers
rm -r build/rp_pico_program
rm -r build/terminal

cmake \
    -S . \
    -B build/. \
    -DTARGET_GROUP=firmware

cd build
make

cd ..
read -p "Upload to "$1"?" -n 1 -r
echo    # (optional) move to a new line
if [[ $REPLY =~ ^[Yy]$ ]]
then
    sudo mount -o gid=users,fmask=113,dmask=002 $1 rp_pico_mount
    sudo cp build/rp_pico_program/rp_pico_program.uf2 rp_pico_mount
    sudo umount rp_pico_mount
fi

#openocd -f interface/raspberrypi-swd.cfg \
#-f target/rp2040.cfg \
#-c "program build/rp_pico_program/rp_pico_program.elf verify reset exit"

