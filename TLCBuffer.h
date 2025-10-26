#pragma once
//
//    FILE: TLCBuffer.h
//  AUTHOR: Rob Tillaart
//    DATE: 2025-10-26
// VERSION: 0.1.0
// PURPOSE: Arduino library for a Time Length Compressed circular buffer.
//     URL: https://github.com/RobTillaart/TLCBuffer
//


#include "Arduino.h"


#define TLCBUFFER_LIB_VERSION         (F("0.1.0 Work in progress"))

//  ERROR CODES
//  values <> 0 are errors.
#define TLCBUFFER_OK                  0x00


class TLCBuffer
{
  public:
    TLCBuffer(uint32_t size)
    {
      _size = size;
      if (_size < 4) _size = 4;
      //  allocate dynamic buffer..
      _buffer = (uint32_t *) malloc(_size * 4);
      _times = (uint32_t *) malloc(_size * 4);
    }
    
    ~TLCBuffer()
    {
      if (_buffer != NULL) free(_buffer);
      if (_times != NULL) free(_times);
    }

    //  time units  
    //  U = micros  M = Millis S = seconds T = Tenths of a second H = Hundreds of a second
    bool begin(char timeUnits = 'M')
    {
      if ((_buffer == NULL) || (_times == NULL))
      {
        free(_buffer);
        free(_times);
        return false;
      }
       
      _index = 0;
      _count = 0;
      _timeUnits = timeUnits;
      _lastTime = 0;
      _lastValue = 0;
      return true;
    }

    void writeValue(uint32_t value)
    {
      //  do we have a new value?
      if (value == _lastValue) return;
      _lastValue = value;
      //  write duration of previous value first.
      uint32_t now = millis();
      _times[_index++] = now - _lastTime;
      _lastTime = now;
      //  buffer the next value in next free slot.
      if (_index >= _size) _index = 0;
      _buffer[_index] = value;
      if (_count < _size) _count++;
    }

    uint32_t readValue(uint32_t index)
    {
      //  no check on index
      return _buffer[index];
    }

    uint32_t readDuration(uint32_t index)
    {
      //  no check on index
      return _times[index];
    }

    uint32_t size()
    {
      return _size;
    }

    uint32_t count()
    {
      return _count;
    }

  private:
    uint32_t * _buffer;
    uint32_t * _times;
    uint32_t _size;
    uint32_t _index;
    uint32_t _count;
    char     _timeUnits;
    uint32_t _lastTime;
    uint32_t _lastValue;
};



//  -- END OF FILE --





