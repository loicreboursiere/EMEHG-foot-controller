/**
 * @file  
 * @brief Contains all the function prototypes for the Functions.cpp file.
 * @author  Pierre Paque ISEN (PROM. 62) Lille France.
 * @version June_2020
 * 
 * 
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Arduino.h"
#include "Switch.h"
#include <Wire.h> 
#include <Adafruit_NeoPixel.h>

/**
 * @brief Writing into the i2c memory chip
 * 
 * @param deviceaddress i2c address of the memory chip on the bus
 * @param eeaddress Address of the byte you want to write inside the memory chip
 * @param data byte Data you want to write
 */
void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data );

void writeTeensy(int btnID,bool btnState);

/**
 * @brief Read from the i2c memory chip
 * 
 * @param deviceaddress i2c address of the memory chip on the bus
 * @param eeaddress Address of the byte you want to read inside the memory chip
 * @return byte Data returned as a byte
 */
byte readEEPROM(int deviceaddress, unsigned int eeaddress );


/**
 * @brief check if a switch is pushed
 * 
 * @param index is the index of the switch being checked
 * @param bank is an indication representing the array the switch belongs to
 * @param pressedButtonP interrupt flag
 * @param FSWP Switch object
 * @param chain Adafruit_NeoPixel object.
 */
void updateFSWboard(int index, int bank, bool pressedButtonP, Switch FSWP, Adafruit_NeoPixel chain);

/**
 * @brief load state a given switch
 * 
 * @param index of the Switch object in its Array
 * @return true 
 * @return false 
 */
bool loadState(int  index);

/**
 * @brief load color chanel of a given switch
 * 
 * @param index index of the Switch object in its Array. <b>Not the LED index <b>
 * @param chanel <ul><li>0:=R chanel</li><li>1:=G chanel</li><li>2:=B chanel</li></ul>
 * @return byte 
 */
byte loadColor(int index, int chanel);

/**
 * @brief save the state of a given switch.
 * 
 * @param index index of the Switch object in its Array.
 * @param state true : switch is engaged. false : switch isnt engaged
 * 
 */
void saveState(int  index, bool state);

/**
 * @brief 
 * 
 * @param index index of the Switch object in its Array.
 * @param chanel <ul><li>0:=R chanel</li><li>1:=G chanel</li><li>2:=B chanel</li></ul>
 * @param color value of the component
 */
void saveColor(int index, int chanel, byte component);

/**
 * @brief when called it blinks the debug LED on the board.
 * 
 */
void blinkDebugLED();

/**
 * @brief loads presets datas from teensy
 * 
 * @todo WRITE THE BLOODY FUNCTION
 * 
 */
bool loadFromTeensy();

#endif
