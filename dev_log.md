# Development Log

Short notes on things I have done in this project. 

## 2022-03-19 Testing USB-Host
I have been playing around with example code that turns the Raspberry Pi Pico into a USB-host, able to communicate with a USB-Human Interface Device, i.e. in my case a keyboard. The example code included in the Pico SDK uses TinyUSB and it worked right out of the box! However, if I unplug the keyboard it will unfortenately not enumerate correctly when plugged in again. It fails when the host queries for the first HID-report. I looked around trying to find what was the cause but did not comprehend enough of TinyUSB to be able to do anything about it. The problem is not a deal breaker so will just ignore it for now. Perhaps I can come back to it at a later point in time. Now I will aim to strip down the USB-example code to its bare minimum so I understand how the keyboard input it treated.

## 2022-03-20 Battling the ILI9341
Connecting the TFT-screen, 240x320 was not difficult. I got it working on Arduino a while ago, both with SPI and 8-bit interface, IIRC. For a long time I had no luck getting anything on the screen. I made sure I got output on my data lines with a LED-bar graph. There where data, and the bits were in correct order. After studying other drivers for the ILI9341, the most easy to follow was the Linux/RPi-driver from [sammyizimmy](https://github.com/sammyizimmy/ili9341/blob/master/). Without his code I would have given up. I've read some datasheets before, including one for a display, but found the ILI-one a bit confusing, and it mostly lacked examples. I realized it might be that I needed to initialize the screen properly for it to listen to anything else. Lo and behold, after doing so it did light up! Now I made a quite ugly color-testing function to get familiar with writing to the screen.

Started to look for fonts. It's a whole new world opening... There are many old [low-res fonts](https://int10h.org/oldschool-pc-fonts/) from the passed.

## 2022-03-24 Parsing a PNG
Since i could not wrap my mind around how to convert a .ttf file I settled on using some random font that was already in picture form. Reading a picture with Python was rather straight forward. Then i needed to understand that the pixel list I then got was listing the pixels in the same order as one would read a book. This caused for some quirky offsets in order to read out one single character. I wanted the characters read one by one so all the data for one characted could be continuosly one after the other.

When that was in place I could make a script that would read one character from my binary-dump-file and print it to the terminal, just so I was sure all was working as intended.

## 2022-03-26 Including a binary file in your C-program
Now for the task of including a binary file in your C-program. I am familiar on how that works in (older) Assembly: you just have line saying "dear compiler, put these bytes here". Simple to know whats going on at least. I searched for a similar approach for C but ended up converting the data to a C-array instead since that seems to be the go-to method. To convert the binary file to a variable parasable by C there is this little command called `xxd` which seems to be included in Debian. 

Now I can print a character on the screen! It required a lot of tweaking to understan what was going on with the display. Now it can print one character with only a single set of calls to tell the display what area is being used. I also discovered a beautiful collection of old pixel-fonts ready to be [imported directly in C](https://github.com/spacerace/romfont).

## 2022-08-15
Documented the hardware. Managed to setup debug prints from the Pico via the USB-to-serial-chip.

## 2022-08-28
Now the debug-prints where not working. I tried to connect to a Raspberry Pi 400 instead of the USB-serial-converter. After hours of debugging and trying all combinations of TX+RX pins with uart0 and uart1 I am pretty sure something is off with the Pico. I could only get STDIO working on GPIO12 and 13. Next step should be to get the SWD, Serial Wire Debug, which should be fairly simple on the Raspberry Pi 400.

## 2023-08-06
I installed the toolchain on my "new" computer, running Arch Linux. No trouble whatsoever getting the Pico examples to run. Compiling this project, however, gave several `multiple definitions` errors, despite those variables not being used in `main.c`. After help by ChatGPT I could determine some variables needed a `static` to fix the issue.

I also tried scripting tests of my device. The test would send a series of bytes, simply. This would allow me to test that all escape-codes are handeled properly. When trying this with a simple "hello, world"-message only the first letter was displayed. This makes me believe the USB-tasks takes too long for my terminal to keep up with the incomming data from the PC.

# 2023-08-09
I want to be able to write unit-tests in C. This requires me to be able to compile another target than the Termina-executable itself. After some searching I found [this guide](http://www.throwtheswitch.org/build/cmake). I've already implemented the switch for selecting compiling the program or the tests.

