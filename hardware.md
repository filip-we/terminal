# Hardware

## BOM
- Raspberry Pi Pico.
- 2.4 inch TFT-screen, ILI9341-compatible.
- USB to serial converter.

## Description
- The screen is interfaced in parallell with the Pico on pins 19, 20, 21, 22, 24, 25, 26 and 27.
- Ground and +3.3 V is connected to the screen.
- Ground is connected to the USB-to-serial-converter.
- +5 V from the the USB-to-serial-converter is connected to the VSYS-pin nr 39 on the Pico.
- Tx and Rx on the Pico and the converter are connected (Tx to Rx, Rx to Tx as usual).

## Features
1. The setup can be USB-powered by connecting the USB-to-serial-converter to a PC (or a USB-power-brick).
2. The Pico can utilize debug-prints which can be read on a PC.
3. A keyboard is connected to the Pico on its build in Micro-USB-port. This requires a USB-OTG-cable.
4. When not using the keyboard you can connect the pico to your computer for uploading firmware, as usual.


## Alternative to serial-converter
Connect the UART of the Pico to a Raspberry Pi 400 (or 4).
