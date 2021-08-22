/**@file UMons_arduino_custom.ino */

// +------------------------------------------------------------------------------------------------+
// | Code written by Pierre Paque : M1 Student (prom. 62) @ ISEN Lille (59) France.                 |
// | For Loic Reboursiere PhD Thesis during volunteer internship @ UMons Mons (BE-WHT) Belgium.     |
// | This code is meant to run on the footswitch controller aka the "Arduino Custom Board"          |
// | June 2020                                                                                      |
// +------------------------------------------------------------------------------------------------+

#include <Wire.h>  
#include <Adafruit_NeoPixel.h>
#include "SRChain.h"

#include "defines.h"
#include "Functions.h"

//objects  and vars.
Adafruit_NeoPixel RGBChainOne = Adafruit_NeoPixel( RGB_CH1_NB, RGB_CH1, NEO_GRB + NEO_KHZ800 );
Adafruit_NeoPixel RGBChainTwo = Adafruit_NeoPixel( RGB_CH2_NB, RGB_CH2, NEO_GRB + NEO_KHZ800 );

SRChain chain[ NUMBER_OF_CHAIN ] = { SRChain( CLK1_SR, LAT1_SR, DAT1_SR, ISR_PIN, CH1_NB_ELT ),
                                   SRChain( CLK2_SR, LAT2_SR, DAT2_SR, ISR_PIN, CH2_NB_ELT ) };

int pushedButton = -1;
bool update = false;


void setup() {
    Serial.begin( 9600 );
    //pinModes
    pinMode( ISR_PIN, INPUT );
    pinMode( DBG_LED,OUTPUT );
    pinMode( MEM_WP, OUTPUT );

    digitalWrite( DBG_LED, LOW );//turn debug led off
    digitalWrite( MEM_WP, HIGH );//enable write protection on the memory chip

    RGBChainOne.begin();
    RGBChainTwo.begin();

    for( int i = 0; i < RGB_CH1_NB; i++ ) { RGBChainOne.setPixelColor( i, 0, 0, 0 ); }
    for( int i = 0; i < RGB_CH2_NB; i++ ) { RGBChainTwo.setPixelColor( i, 0, 0, 0); }

    RGBChainOne.show();
    RGBChainTwo.show();

    Wire.begin();//no adress since the arduino custom is the master

    //init SR Chains
    chain[ 0 ].begin();
    chain[ 1 ].begin(); 

    chain[ 0 ].loadData();
    chain[ 1 ].loadData();

    blinkDebugLED();//blink the activity/debug led when init is complete.
}


void loop() {

    //check if  the teensy has new parameters to send
    update = loadFromTeensy();
    if( update )
    {
        chain[ 0 ].loadData();
        chain[1].loadData();
        update = false;
    }

    for( int i = 0; i < CH1_NB_ELT * 8; i++ )
    {
        chain[ 0 ].turnOff();
        chain[ 0 ].turnOn( i );// check the i-th switch in the SRCHAIN.

        Switch sw = chain[ 0 ].getSwitch( i ); //load a copy of the i-th switch
                
        if( chain[ 0 ].getSwitch( i ).getState() == true ) //if a switch is "enabled"
        { 
            
            RGBChainOne.setPixelColor( sw.getLEDIndex(), sw.getRed(), sw.getGreen(), sw.getBlue() );
            RGBChainOne.show();//display it's "enabled" color

            if( !digitalRead( ISR_PIN ) ) //if switch pushed down
            {
                chain[ 0 ].setSRState( i,false );//set the i-th element of the chain to false
                RGBChainOne.setPixelColor( chain[ 0 ].getSwitch( i ).getLEDIndex(), 0, 0, 0 );
                RGBChainOne.show(); //turn off led
                saveState( i, false ); //save the new switch value
                writeTeensy( i, false );//send it to the PC through the Teensy
                }
        }
        else{
            
            RGBChainOne.setPixelColor( chain[ 0 ].getSwitch( i ).getLEDIndex(), 0, 0, 0 );
            RGBChainOne.show();//if switch is disabled keep it's associated LED off

            if( !digitalRead( ISR_PIN ) ) //if switch pushed down
            {
                chain[ 0 ].setSRState( i, true );//set the i-th element of the chain to true
                RGBChainOne.setPixelColor( sw.getLEDIndex(), sw.getRed(), sw.getGreen(), sw.getBlue() );
                RGBChainOne.show();
                saveState( i, true );
                writeTeensy( i, true );
                }
        }

            while( !digitalRead( ISR_PIN ) );//freeze the system while a button is pressed down
    }


    if( CH2_ENABLE )
    {
        
    }
}
