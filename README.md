# InteractiveGadgets
**CS 207- Building Interactive Gadgets Project**

Project name: WAIFU Timer
Objective: Build a creative timer using 7-segment displays, an led matrix, buttons, and a piezo speaker
---

**ABSTRACT**
WAIFU Timer is an Arduino-based timer that counts minutes and seconds. When a user sets the timer, the clock starts counting until the set time and then turns on an alarm. This project uses the Arduino TIME library to keep track of the time, three buttons for setting up the alarm, a piezo speaker that plays a melody when the alarm goes off, and an LED matrix display that turns on different patterns of lights as the music is playing.

Youtube video of working project: https://www.youtube.com/watch?v=g2EHhpU4nSY

**CONTENTS**

This repository contains the main program for WAIFU Timer and some files that require to be installed in order for it to run properly.
In order to use this code you need an assembled circuit with the following configuration:

![Circuit Diagram](http://41.media.tumblr.com/06e87693569d048489fe0325bf053026/tumblr_nz0wa3muqY1qbngy8o1_500.jpg)


*2 common cathode 7-segment displays connected to two daisy chained 595 shift registers. The first one should be connected on pins 2,4,3 of the arduino (Data,Latch,Clock)
*2 common anode 7-segment displays connected to two daisy chained 595 shift registers. The first one should be connected on pins 5,6,7 of the arduino (Data,Latch,Clock)
*1 LED matrix display connected to two daisy chained 595 shift registers.The first one should be connected on pins A0, A2, A1 of the arduino (Data,Latch,Clock)
*3 buttons, connected to pins 10,11,12 of the Arduino
*1 LED connected to pin 13 of the Arduino
*1 piezo speaker connected to pin 8 of the Arduino
   
**Project Files**

* _7segment2displays.ino
* license.txt
* README.md

**How to run the project**

First you need to install Arduino IDE

To install the Arduino IDE go to the following link and select download for your operating system:
https://www.arduino.cc/en/Main/Software

Then you need to install the TIME library, which can be downloaded from here:

http://playground.arduino.cc/code/time

To install the library you need to do one of the following:

1. Open Arduino IDE and follow this instructions:

Go to Sketch -> Include Library -> Manage Libraries... -> (look for TIME) -> Install

2. Manually install the library

You can manually extract the folder TIME included in this repository into the "Libraries" folder of your Arduino IDE. (Rememver Arduino IDE must be closed to do this)

**_You're almost good to go._**

To run the project you need to download the folder _7segment2displays from this repository directly into your Arduino folder.

After that is done, open the .ino file contained in the folder, allow Arduino IDE to load and then click on build.


**CURRENT STATUS OF THE PROJECT**

A full working timer that has a time set by the user and turns on an alarm when the time is met. It includes an LED matrix display that lights up to the beat of a melody.
The current alarm melody is named Imperial March, from the series Star Wars. It was obtained from Forum.arduino.cc,. (2015). Star Wars Imperial March With Piezo. Retrieved 8 December 2015, from http://forum.arduino.cc/index.php?topic=259450.0


**LICENSE**

WTFPL License - Official Text included in this repo under _license.txt_

![WTFPL License](http://www.wtfpl.net/wp-content/uploads/2012/12/logo-220x1601.png)




