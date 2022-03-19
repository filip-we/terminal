#Development Log

Short notes on things I have done in this project. 

## 2022-03-19 Testing USB-Host
I have been playing around with example code that turns the Raspberry Pi Pico into a USB-host, able to communicate with a USB-Human Interface Device, i.e. in my case a keyboard. The example code included in the Pico SDK uses TinyUSB and it worked right out of the box! However, if I unplug the keyboard it will unfortenately not enumerate correctly when plugged in again. It fails when the host queries for the first HID-report. I looked around trying to find what was the cause but did not comprehend enough of TinyUSB to be able to do anything about it. The problem is not a deal breaker so will just ignore it for now. Perhaps I can come back to it at a later point in time. Now I will aim to strip down the USB-example code to its bare minimum so I understand how the keyboard input it treated.
