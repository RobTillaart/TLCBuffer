#pragma once
//
//    FILE: TLCBuffer.h
//  AUTHOR: Rob Tillaart
//    DATE: 2025-10-26
// VERSION: 0.1.0
// PURPOSE: Arduino library for Time Length Compressed circular buffer.
//     URL: https://github.com/RobTillaart/TLCBuffer
//


#include "Arduino.h"


#define TLCBUFFER_LIB_VERSION         (F("0.1.0"))

//  ERROR CODES
//  values <> 0 are errors.
#define TLCBuffer_OK                  0x00


class TLCBuffer
{
  public:
    TLCBuffer()
    {
      //  TODO allocate dynamic buffer...
      reset();
    }

    void reset()
    {
      _lastTime = 0;
      _lastValue = 0;
      _index = 0;
      _buffer[0] = 0;
      _times[0] = 0;
    }

    void writeValue(uint32_t value)
    {
      //  do we have a new value?
      if (value == _lastValue) return;
      _lastValue = value;
      //  write duration of previous value first.
      _times[_index++] = millis() - _lastTime;
      _lastTime = millis();
      //  buffer the next value.
      _buffer[_index] = value;
    }

    uint32_t readValue(uint32_t index)
    {
      return _buffer[index];
    }

    uint32_t readDuration(uint32_t index)
    {
      return _times[index];
    }

    uint32_t size()
    {
      return _index;
    }

  private:
    //  1024 bytes in total
    uint32_t _buffer[128];
    uint32_t _times[128];
    uint32_t _index;
    uint32_t _lastTime;
    uint32_t _lastValue;
};



//  -- END OF FILE --





