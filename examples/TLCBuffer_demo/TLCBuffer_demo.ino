//
//    FILE: TLCBuffer_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/TLCBuffer


#include "TLCBuffer.h"


TLCBuffer TLCB;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("TLCBUFFER_LIB_VERSION: ");
  Serial.println(TLCBUFFER_LIB_VERSION);
  Serial.println();

  TLCB.begin();
}


void loop()
{

  delay(2000);
}


//  -- END OF FILE --
