/**
 * @file  
 * @brief Contains all the custom functions required to give life to the Foot Switch Controller Board.
 * @author  Pierre Paque ISEN (PROM. 62) Lille France.
 * @version June_2020
 * 
 * 
 */


#include "Functions.h"
#include "defines.h"



void writeEEPROM( int deviceaddress, unsigned int eeaddress, byte data ) 
{
  digitalWrite( DBG_LED,HIGH);//activity
  digitalWrite( MEM_WP,LOW);
  delay( 5 );
  Wire.beginTransmission( deviceaddress);
  Wire.write( ( int )( eeaddress >> 8 ) );   // MSB
  Wire.write( ( int )( eeaddress & 0xFF ) ); // LSB
  Wire.write( data );
  Wire.endTransmission();
  delay( 5 );
  digitalWrite( MEM_WP, HIGH );
  digitalWrite( DBG_LED, LOW );//activity
}
 
void writeTeensy( int btnID, bool btnState ){
  
  Wire.beginTransmission( TEENSY_ADDR );  
  Wire.write( 0xA1 );  //sw id register                 
  Wire.endTransmission();

  Wire.beginTransmission( TEENSY_ADDR );  
  Wire.write( btnID );//fsw id                   
  Wire.endTransmission();

  Wire.beginTransmission( TEENSY_ADDR );  
  Wire.write( 0xA2 );//sw state register             
  Wire.endTransmission();

  Wire.beginTransmission( TEENSY_ADDR );  
  Wire.write( ( int ) btnState );//fsw state                   
  Wire.endTransmission();

}


byte readEEPROM( int deviceaddress, unsigned int eeaddress ) 
{
  digitalWrite( DBG_LED, HIGH );//activity
  byte rdata = 0xFF;
  Wire.beginTransmission( deviceaddress );
  Wire.write( ( int )( eeaddress >> 8 ) );   // MSB
  Wire.write( ( int )( eeaddress & 0xFF ) ); // LSB
  Wire.endTransmission();
  Wire.requestFrom( deviceaddress, 1 );
  if ( Wire.available() ) rdata = Wire.read();
  digitalWrite( DBG_LED, LOW );
  return rdata;
}

void updateFSWboard( int index, int bank, bool pressedButtonP, Switch FSW, Adafruit_NeoPixel chain ) 
{
  if( pressedButtonP == true)
  {
    if( FSW.getLEDIndex() != -1 )
    {
      
      FSW.invertState();
      bool state = FSW.getState();
      int i = ( int )FSW.getLEDIndex();

      int r = 0;
      int g = 0;
      int b = 0;
        
      if( state == true )
      {  
        int r = ( int )FSW.getRed();
        int g = ( int )FSW.getGreen();
        int b = ( int )FSW.getBlue();
      }

      //update led
      chain.setPixelColor( i, r, g, b );
      chain.show();

      //tell the change to teensy
      
      
      //save the change to memory
      int offset = bank * ( 8 * CH1_NB_ELT + MEM_BLOCK );
      saveState( index + offset, FSW.getState() );
      
    }
    else{
      //board detected !
    }

    
    
    }
    //check memory, possibly change it's content
    //send i2c  stuff
  }

bool loadState( int  index )
{
  
  return ( bool )readEEPROM( MEM_ADDR, index * MEM_BLOCK + 16 );
}

byte loadColor( int index, int chanel )
{
  //if(chanel<0 && chanel>2) return 0;

  return readEEPROM( MEM_ADDR, index * MEM_BLOCK + chanel );
}

void saveState( int  index, bool state )
{
  writeEEPROM( MEM_ADDR, index * MEM_BLOCK + 16,( byte ) state );
}

void saveColor( int index, int chanel, byte component )
{
  if( chanel >= 0 && chanel <= 2 )
  {
    writeEEPROM( MEM_ADDR, index * MEM_BLOCK + chanel,component );
  }
}

void blinkDebugLED(){
   
   digitalWrite( DBG_LED, HIGH );
   delay( BLINK_DELAY_DBG );
   digitalWrite( DBG_LED, LOW );
   delay( BLINK_DELAY_DBG );
   digitalWrite( DBG_LED, HIGH );
   delay( BLINK_DELAY_DBG );
   digitalWrite( DBG_LED, LOW );
}

bool loadFromTeensy(){
  int datas[ 256 ]; //buffer that stores the requested data from the teensy
  int v = 0; //index, useful to store the requested data
  int j = 0;
 
  int timeOut = 0;

  while( true ){
    if( timeOut >= I2C_TIME_OUT){ return false; }
    delay( 250 );
    Wire.beginTransmission( TEENSY_ADDR );
    if( Wire.endTransmission() == 0 ){
        break;
    }
    timeOut++;
  }
  
    //requesting update flag
    Wire.beginTransmission( TEENSY_ADDR );  
    Wire.write( 0xC1 );  //ask the update flag register               
    Wire.endTransmission(); 
    delay( 50 ); 
    Wire.requestFrom( TEENSY_ADDR, 1 );
    while( Wire.available() ) {  
      if( ( bool )Wire.read() == false ){ return false; }
    }
  
  blinkDebugLED();

  for( int i = 0; i < 8; i++ ) //covers the 8 data 32bytes chunks
  {
    Wire.beginTransmission( TEENSY_ADDR );  
    Wire.write( i + 1 );                   
    Wire.endTransmission(); 
    delay( 50 ); 
    Wire.requestFrom( TEENSY_ADDR, 32 );
    while( Wire.available() ) 
    {  
      datas[ v ] = ( int )Wire.read();
      v++;
    }
  }

  //write these data into memory
  for( int i = 0; i < 8 * CH1_NB_ELT; i++ )
  {
    saveColor( i, 0, ( byte ) datas[ j ] );//red
    j++;
    saveColor( i, 1, ( byte ) datas[ j ] );//green
    j++;
    saveColor( i, 2, ( byte ) datas[ j ] );//blue
    j++;
  }

  return true;
}

//make a boot function to check integrity of the circuit (with the 8th channel of the shift registers.)

//make the function to save stuff in the mem chip
