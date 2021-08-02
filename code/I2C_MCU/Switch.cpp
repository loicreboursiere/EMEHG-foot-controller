/**
 * @file  
 * @brief Contains the methods of the Switch class.
 * @author  Pierre Paque ISEN (PROM. 62) Lille France.
 * @version June_2020
 * 
 * 
 */

#include "Switch.h"

Switch::Switch(int LEDIndexP){
  /**
   * @brief Switch constructor, init attributes and set the led ID.
   * 
   */
  this->LEDIndex = LEDIndexP;
  this->FSWState = false;
  this->red = 0;
  this->green = 0;
  this->blue = 0;
}

Switch::Switch(){
   /**
   * @brief Switch constructor, init attributes without associating an LED.
   * 
   */
  this->LEDIndex = -1; ///< -1 value means "no associated LED"
  this->FSWState = false;
  this->red = 0;
  this->green = 0;
  this->blue = 0;
}


//state getters
bool Switch::getState(){
  return this->FSWState;
}

//state setters
void Switch::setState(bool newState){
  this->FSWState = newState;
}

void Switch::invertState(){
  this->FSWState = !this->FSWState;
}

//color getters
byte Switch::getRed(){
  return this->red;
}

byte Switch::getGreen(){
  return this->green;
}

byte Switch::getBlue(){
  return this->blue;
}

//color setters
void Switch::setRed(byte newRed){
   this->red = newRed;
}

void Switch::setGreen(byte newGreen){
   this->green = newGreen;
}

void Switch::setBlue(byte newBlue){
   this->blue = newBlue;
}

//index getter
byte Switch::getLEDIndex(){
  return this->LEDIndex;
}

//index setter
void Switch::setLEDIndex(byte LEDIndexP){
  this->LEDIndex = LEDIndexP;
}



