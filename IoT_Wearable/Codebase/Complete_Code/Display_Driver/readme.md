This is the the display driver for the IoT Wearable device.
The driver was developed using the PlatformIO extension in VSCode. 

To get started on development, follow these steps:
- Install the PlatformIO extension in VSCode
- Create a PlatformIO project using the extension
- In PlatformIO, install the following libraries:
    1. Adafruit_ST7789
    2. Adafruit_GFX
    3. SPI
    (The ST7789 library will be installed along with the Adafruit_GFX and SPI libraries since it is dependent on these two libraries.)
- Navigate to src in platformIO, you will find the main.cpp file which you can paste the DisplayDriver code in.

(Note that this code can also be used in arduino IDE, however it is recommended to use PlatformIO)
