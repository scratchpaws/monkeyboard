# Monkeyboard - yet another monkey keyboard  
A board project that simulates a USB keyboard and mouse, and automatically types walls of meaningless text, simulating user activity.  
Typing words periodically with the keyboard, separating words with spaces, and starting new sentences with a capital letter. In the course of work, the input is carried out at the typing speed of an ordinary user, with arbitrary intervals both between the input of characters and between the input of words. Periodically moves the mouse cursor over a limited distance and clicks with the left mouse button.  
![a demo gif](https://raw.githubusercontent.com/scratchpaws/monkeyboard/main/demo.gif)  

## Resources and materials used  
This project uses an Attiny85 based [Digispark USB development board](http://digistump.com/products/1) and [TrinketHidCombo](https://github.com/adafruit/Adafruit-Trinket-USB/tree/master/TrinketHidCombo) from [Adafruit-Trinket-USB](https://github.com/adafruit/Adafruit-Trinket-USB) project by [adafruit](https://github.com/adafruit).  
But practically any Arduino-compatible board based on the AVR microcontroller that has a USB port should be suitable.  
![Image of board](https://s3.amazonaws.com/digistump-resources/images/l/2520dcf84a0a3bf2257c2559d7a187db.jpg)  

## How to build
1. First of all, need the development board. Digispark USB is preferable due to its compactness, but another Arduino-compatible board based on the AVR controller is suitable, which has a USB connector, 6 kilobytes of flash memory, 256 or more bytes of RAM, and 64 bytes or more EEPROM. Further steps will be described specifically for Digispark USB.  
3. Follow [the instructions for installing Arduino IDE and connecting the DigiSpark board](http://digistump.com/wiki/digispark/tutorials/connecting) from the official wiki of this board.
4. Be sure to create and upload the flashing LED test firmware, which is described on this wiki page, to verify that the settings are correct and to get an idea of how to upload the sketch to the board.
5. If you would prefer to use another compatible card, follow its own instructions to set it up. Also, be sure to upload your test project to get an idea of how to upload your sketch.  
6. Download this project to your computer.    
7. Copy the contents of the `Arduino\libraries` directory to the `Arduino\libraries` directory in the your `Documents` folder. Alternatively, you can download the library from the original [Adafruit-Trinket-USB repository](https://github.com/adafruit/Adafruit-Trinket-USB). In this case, you will need to copy the `Adafruit-Trinket-USB\TrinketHidCombo` directory to the `Arduino\libraries` directory in the your `Documents` folder.   
8. Copy directory **EEPROM** with all contents from:  
`C:\Program Files (x86)\Arduino\hardware\arduino\avr\libraries`  
to:  
`C:\Users\{your.user.name}\AppData\Local\Arduino15\packages\digistump\hardware\avr\1.6.7\libraries`  
7. Now you can open the Arduino project (\*.ino-file) and upload the sketch to the board.  
