# EMEHG-foot-controller

This repository gathers all elements needed to build and run EMEHG-foot-controller.
This device is a 7x7 footswitches matrix with 7x7 NeoPixels.
It aims at controlling hexaphonic effects individual bypasses. 
As it sends out MIDI commands, this controller can be use for any kind of control operation.
 This project is a part of the developments made for Loïc Reboursière Phd Thesis : 
    "Organology, genealogy and practice of hexaphonic guitar : from independent string effects to instrumental control of other sounds." 
 
This version is based on a Teensy 3.2
 
 The folder is organized as follows : 
 ```
 EMEHG-fx-controller.
 └───code
 └───img
 └───pcb
 ```
- code : contains the code to be uploaded on the microcontroller. Depending on the version you're using, the structure of this folder can change (Arduino sketch or Platform IO (through VS) code).
- img : pictures of the different versions of the controller.
- pcb : files needed to build pcb of the project
