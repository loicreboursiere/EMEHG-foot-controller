//TEENSY
#include <Wire.h>


volatile byte registerAddr = 0x0;
volatile bool newMidiMessage = false;

volatile int FSWid = 0;
volatile bool FSWstate = false;

volatile bool newUpdate = false;


byte data[ 255 ] = { 0 };

void setup() {
  // put your setup code here, to run once:
  Serial.begin( 9600 );
  Wire.begin( 4 );
  Wire.onReceive( receiveEvent );
  Wire.onRequest( requestEvent );
}



void loop() {
//doing stuff
//delay(2000);

  if( newMidiMessage )
  {
    Serial.println( "FSW pressed !" ); 
    Serial.println( FSWid );
    Serial.println( FSWstate );
    Serial.println( "-------" );
    newMidiMessage = false;  

    usbMIDI.sendControlChange( FSWid, FSWstate * 127, 1 );
  }

}


void receiveEvent( int howMany )
{ 
  byte buff = 0;
 
  while( Wire.available() ) 
  { 
    buff = ( byte )Wire.read();
  }  

  if( registerAddr == 0xA1 )
  {
    FSWid = buff;
    registerAddr = 0x0;
    return;
  }

  if( registerAddr == 0xA2 )
  {
    FSWstate = buff;
    newMidiMessage = true;
    registerAddr = 0x0;
    return;
  }

  registerAddr = buff;
}

void requestEvent() {
        if( registerAddr >= 0x01 && registerAddr <= 0x07 ) //if requested data has an address between 0x01 0x07 (boundaries included) it's from the data array
        {
          for( int i = 0 + ( ( registerAddr - 1 ) * 32 ); i < 32 + ( ( registerAddr - 1 ) * 32 ); i++ )
          {
            
            if( i % 3 == 0 )
            {
              Wire.write( 128 );
            }
            else
            {
              Wire.write( 0 );
            }
          }
        }

        if( registerAddr == 0xC1 ) 
        {
          Wire.write( ( byte ) newUpdate );
        }
}
