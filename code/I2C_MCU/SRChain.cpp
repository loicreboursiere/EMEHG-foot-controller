#include "SRChain.h"
#include "Switch.h"
#include "Functions.h"

SRChain::SRChain( byte clkP, byte latP, byte datP, byte returnSigP, int nbSRP ){

    /**
     * @brief constructor of the class. init the attributes
     * 
     */

    
    this->clk = clkP;
    this->lat = latP;
    this->dat = datP;
    this->nbSR = nbSRP;
    this->returnSig = returnSigP;

    this->FSArray = 0;
    this->FSArray = new Switch[ this->nbSR * 8 ];

    pinMode( this->clk, OUTPUT );
    pinMode( this->lat, OUTPUT );
    pinMode( this->dat, OUTPUT );
    pinMode( this->returnSig, INPUT );

    digitalWrite( this->clk,LOW );
    digitalWrite( this->lat,LOW ); 
}


void SRChain::begin(){

    /**
     * @brief set all shift registers output to 0. init the array of Switch object.
     * 
     */
    this->turnOff();

    int index = 0;
    for(int i = 0; i < ( 8 * this->nbSR ); i++ )
    {
        if( ( i + 1 ) % 8 != 0 ) //skips the n*8th switch.. these are virtual switchs used to keep track of FSW Board responsiveness.
        {
            this->FSArray[ i ].setLEDIndex( ( byte ) index );
            this->FSArray[ i ].setState( loadState( index ) );
            this->FSArray[ i ].setRed( loadColor( index, 0 ) );
            this->FSArray[ i ].setGreen( loadColor( index, 1 ) );
            this->FSArray[ i ].setBlue( loadColor( index, 2 ) );
            index++;
        }
    }
}

void SRChain::turnOff(){

  /**
   * @brief sets all Shift Registers output to low
   * 
   */

  digitalWrite( this->dat , LOW );

  for( int i = 0; i < 8 * this->nbSR; i++ )
  {
    digitalWrite( this->clk, HIGH );
    digitalWrite( this->clk, LOW );
  }
  digitalWrite( this->lat,HIGH );
  digitalWrite( this->lat,LOW );

}


void SRChain::turnOn( int iP ){

  /**
   * @brief sets the i-th Shift Registers output to HIGH
   * @note this function is specifically designed to only allow one pin high at the time. This avoids hazard leading to potential IC destructions.
   * 
   */

  digitalWrite( this->dat, HIGH );
  
  digitalWrite( this->clk, HIGH );
  digitalWrite( this->clk, LOW );

  digitalWrite( this->dat, LOW );
  
  for( int i = 0; i < iP; i++ ){
  digitalWrite( this->clk, HIGH );
  digitalWrite( this->clk, LOW );
  }
  
  digitalWrite( this->lat, HIGH );
  digitalWrite( this->lat, LOW );
}


bool SRChain::ping()
{

  this->turnOff();
  for( int i = 0; i < this->nbSR; i++ )
  {
    this->turnOn( ( ( ( i + 1 ) * 8 ) - 1 ) ); ///< for i = 0 :  (((0+1)*8)-1) = 8-1 = 7; for i = 1 : 16-1 = 15 and so on.
    delay( 1 );
    /*if(!digitalRead(this->returnSig)){ ///<if the signal is low => !(low) = true, then we return false. As the ((n*8)-1)th chanel should always be <b>HIGH</b>.
      return false;
    }*/
    this->turnOff();
  }
  return true;
  /**
   * @todo return int instead of bool to know where the chain in corrupted
   * 
   */
}

int SRChain::scan(){

    /**
     * @brief make the SR sequence to send pulses inside switches and return wich switch has been pushed
     * 
     */

    int pushedButton = -1; ///<default value
 
  
  this->turnOff();

/**
 * @todo mettre le 8 en define
 * 
 * @param i 
 */

  for( int i = 0; i < this->nbSR * 8; i++ )
  {
    this->turnOn( i ); 
    //delay(200);    
   if( digitalRead( this->returnSig ) ) ///<if the signal is low => !(low) = true, it means the ith switch is pressed down
   { 

      if( ! ( ( i + 1 ) % 8 ) ) 
      {
        Serial.println( i / 8 );
        Serial.println( "board not dead !" );
        
      }else{
        pushedButton = i; //return pushed down switch.
      }

      
    }
    this->turnOff();
  }
  return pushedButton;///<no switch pushed down
}


Switch & SRChain::getSwitch( int i ) {

  /**
   * @brief returns the reference (pointer) to the i-th switch of the Switch array attribute.
   * @warning dont modify this function to return a simple Switch object. you will get a copy of the object. you need reference.
   * 
   */
    return this->FSArray[ i ];
}

void SRChain::setSRState( int i, bool stateP )
{

  /**
   * @brief sets the i-th of the Switch array attribute to true or false state.
   * 
   */
  this->FSArray[ i ].setState( stateP );

}

void SRChain::loadData(){
  /**
   * @brief loads the state of the switchs and their associated led colors from the i2c memory chip.
   * 
   */
  for( int i = 0; i < nbSR * 8; i++ )
  {  
      this->getSwitch( i ).setState( loadState( i ) ); 
      this->getSwitch( i ).setRed( loadColor( i, 0 ) );
      this->getSwitch( i ).setGreen( loadColor( i, 1 ) );
      this->getSwitch( i ).setBlue( loadColor( i, 2 ) );
    }
}
