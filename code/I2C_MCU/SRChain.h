#ifndef SR_CHAIN
#define SR_CHAIN

#include "Arduino.h"
#include "Switch.h"

class SRChain
{

  public : 
    SRChain(byte clkP, byte latP, byte datP, byte returnSigP, int nbSRP);///<constructor

    void begin();
    
    void turnOff(); ///<turn all off
    void turnOn(int i); ///< turn on the given pin @todo rename in SR_something
        
    
    bool ping(); ///<check presence of boards
    int scan(); ///scan the switchs 

    void setSRState(int i, bool stateP);
    
    void loadDatas();

    Switch & getSwitch(int i);


  private :
  
    Switch* FSArray; ///<Switch pointer, useful to create an array when constructor being called
    byte clk; ///<clock pin
    byte lat; ///<latch pin
    byte dat; ///<data pin
    
  
    int nbSR; ///<number of shift register in a chain
    int returnSig; ///<pin that check return signal
};


#endif
