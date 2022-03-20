#Development Log

Short notes on things I have done in this project. 

## 2022-03-19 Testing USB-Host
I have been playing around with example code that turns the Raspberry Pi Pico into a USB-host, able to communicate with a USB-Human Interface Device, i.e. in my case a keyboard. The example code included in the Pico SDK uses TinyUSB and it worked right out of the box! However, if I unplug the keyboard it will unfortenately not enumerate correctly when plugged in again. It fails when the host queries for the first HID-report. I looked around trying to find what was the cause but did not comprehend enough of TinyUSB to be able to do anything about it. The problem is not a deal breaker so will just ignore it for now. Perhaps I can come back to it at a later point in time. Now I will aim to strip down the USB-example code to its bare minimum so I understand how the keyboard input it treated.

## 2022-03-20 Battling the ILI9341
Connecting the TFT-screen, 240x320 was not difficult. I got it working on Arduino a while ago, both with SPI and 8-bit interface, IIRC. For a long time I had no luck getting anything on the screen. I made sure I got output on my data lines with a LED-bar graph. There where data, and the bits were in correct order. After studying other drivers for the ILI9341, the most easy to follow was the Linux/RPi-driver from [sammyizimmy](https://github.com/sammyizimmy/ili9341/blob/master/). Without his code I would have given up. I've read some datasheets before, including one for a display, but found the ILI-one a bit confusing, and it mostly lacked examples. I realized it might be that I needed to initialize the screen properly for it to listen to anything else. Lo and behold, after doing so it did light up! Now I made a quite ugly color-testing function to get familiar with writing to the screen.

Started to look for fonts. It's a whole new world opening... There are many old [low-res fonts](https://int10h.org/oldschool-pc-fonts/) from the passed.
