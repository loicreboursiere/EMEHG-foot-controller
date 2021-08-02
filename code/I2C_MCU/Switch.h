/**
 * @file  
 * @brief Contains the structure (i.e. method prototypes and other attributes) of the Switch class.
 * @author  Pierre Paque ISEN (PROM. 62) Lille France.
 * @version June_2020
 * 
 * 
 */


#ifndef SWITCH_H
#define SWITCH_H
#include "Arduino.h" 


///This class keeps the LED color and the Switch states in the SRAM in a simple object. As result we get a clear and snappy code.

class Switch
{
  public :
    /**
     * @brief Construct a new Switch object
     * 
     * @param LedIndexP associate an rgb led to the freshly created Switch object
     */
    Switch(int LedIndexP);
    /**
     * @brief Construct a new Switch object with a LED index of -1
     * 
     */
    Switch();

    /**
     * @brief return the state of the switch i.e. engaged or not
     * 
     * @return true 
     * @return false 
     */
    bool getState();

    /**
     * @brief Set the State object
     * 
     * @param newState 
     */
    void setState(bool newState);
    /**
     * @brief Invert the State object. e.g. if it was true it becomes false
     * 
     */
    void invertState();

    /**
     * @brief Get the Red component of the associated rgb led
     * 
     * @return byte 
     */
    byte getRed();

    /**
     * @brief Get the Green component of the associated rgb led
     * 
     * @return byte 
     */
    byte getGreen();

    /**
     * @brief Get the Blue component of the associated rgb led
     * 
     * @return byte 
     */
    byte getBlue();


    /**
     * @brief Set the Red component of the associated rgb led
     * 
     * @param newRed 
     */
    void setRed(byte newRed);

    /**
     * @brief Set the Green component of the associated rgb led
     * 
     * @param newGreen 
     */
    void setGreen(byte newGreen);

    /**
     * @brief Set the Blue component of the associated rgb led
     * 
     * @param newBlue 
     */
    void setBlue(byte newBlue);

    /**
     * @brief Get the index of the associated rgb led
     * 
     * @return byte 
     * 
     * @warning if the return index is -1, the Switch objet has either not been initialised with the proper constructor <b>OR</b> it is a virtual Switch. In fact the 8th channel of the shit register is used to check the presence of a FSWboard.
     */
    byte getLEDIndex();

    /**
     * @brief Set the index of the associated rgb led
     * 
     * @param LEDIndexP 
     * 
     * @warning LEDinxP is a byte, it can only go up to 255. You can change it to an int but be really carefull about RAM usage on MCUs like Atmega 328P with only 2kbyte of SRAM.
     * 
     */
    void setLEDIndex(byte LEDIndexP);

    //void setBankID(byte ID);
    //byte getBankID();
    
  
  private :
    //byte bankID;
    
    bool FSWState;
    byte LEDIndex; 
    //bool aliveIndicator;
    byte red;
    byte green;
    byte blue;

  
};

#endif
