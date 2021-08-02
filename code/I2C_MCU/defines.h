/**
 * @file  
 * @brief Contains all #define of the project.
 * @author  Pierre Paque ISEN (PROM. 62) Lille France.
 * @version June_2020
 * 
 * 
 */

#ifndef DEFINES_H
#define DEFINES

//I2C addresses
#define TEENSY_ADDR 4 ///< i2c address of the Teensy on the bus
#define FSW_CTRL_ADDR 8 ///< i2c address of the Arduino Custom on the bus @warning do not use if Arduino is bus master
#define MEM_ADDR 0x50 ///< i2c address of the Memory Chip on the bus

//shift registers

#define CLK1_SR 5 ///< Clock Pin of the <b>first</b> chain of shift register @warning if you want to change something here, be aware that clock and latch are inverted on the PCB labelling
#define CLK1_SR 5 ///< Clock Pin of the <b>first</b> chain of shift register 
#define LAT1_SR 4 ///< Latch Pin of the <b>first</b> chain of shift register
#define DAT1_SR 3 ///< Data Pin of the <b>first</b> chain of shift register

#define CLK2_SR 8 ///< Clock Pin of the <b>second</b> chain of shift register @warning if you want to change something here, be aware that clock and latch are inverted on the PCB labelling
#define LAT2_SR 7 ///< Latch Pin of the <b>second</b> chain of shift register
#define DAT2_SR 6 ///< Data Pin of the <b>second</b> chain of shift register

//RGB LEDs

#define RGB_CH1 A1 ///< Data Pin of the <b>first</b> RGB WS2811 (Neopixel) LED chain
#define RGB_CH2 A2 ///< Data Pin of the <b>second</b> RGB WS2811 (Neopixel) LED chain

//general purpose

#define DBG_LED 9 ///< debug LED Pin
#define ISR_PIN 2 ///< return signal  interrupt pin
#define MEM_WP 10 ///< i2c memory write protection pin

#define I2C_TIME_OUT 150

#define MEM_BLOCK 32 ///< each switch will have a n bytes memory block allocated. to get an idea of the ranges, the mem chip 24LC256 has 32K byte of memory. e.g. 1000 blocks of 32bytes

#define NUMBER_OF_CHAIN 2 ///< set the number of shift register chains


//user parameters
#define CH1_NB_ELT 7///<number of elements in the <b>first</b> Shift Register chain
#define CH2_ENABLE false ///< enable the <b>second</b> Shift Register chain
#define CH2_NB_ELT 0 ///<number of elements in the <b>second</b> Shift Register chain

#define RGB_CH1_NB 49 ///<Number of RGB WS2811 (Neopixel) LED in the <b>first</b> chain .max 255 change the Switch class with index as an int instead of a byte to get (2^16)-1 led
#define RGB_CH2_ENABLE false ///<enable the <b>second</b> RGB WS2811 (Neopixel) LED chain 
#define RGB_CH2_NB 0 ///<Number of RGB WS2811 (Neopixel) LED in the <b>second</b> chain .max 255 change the Switch class with index as an int instead of a byte to get (2^16)-1 led


#define BLINK_DELAY_DBG 100 ///<blink period in ms for debug LED blinking

#endif
