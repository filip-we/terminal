# terminal

The aim of this project is to build a terminal that can be used in conjuction with a Linux PC. It includes both custom hardware and software. The physical components are a RaspberryPi Pico as the controller and a 2.4 inch TFT-screen. Coding will need to inculde the major components of reading from a USB-keyboard, keeping track of a screen buffer, reacting on IO from the host PC and of course print to the TFT-screen.

## Tests
You can run a test with `minicom -D /dev/[device-name-of-uart] -S tests/test_01_hello_world.minicom`. The verification is done by manually looking at the screen! :D


## Requiremnts
On Arch you might need drivers for FAT-discs so you can write to the Pico: `sudo pacman -Sy dosfstools`

