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
    //  u = micros  m = Millis s = seconds 
    //  t = Tenths of a second h = Hundreds of a second
    bool begin(char timeUnits = 'm')
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
      //  update duration of last value first.
      uint32_t now = getTime();
      _times[_index] += (now - _lastTime);
      _lastTime = now;
      //  do we have a new value?
      if (value == _lastValue) 
      {
        return;
      }
      _lastValue = value;
      //  buffer the new value in next free slot.
      //  TODO handle circular here
      _index++;
      if (_index >= _size) _index = 0;
      _buffer[_index] = value;
      _times[_index] = 0;
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

    bool empty()
    {
      return (_count == 0);
    }

    bool full()
    {
      return (_count == _size);
    }

    char getTimeUnit()
    {
      return _timeUnits;
    }

  private:
    uint32_t * _buffer = NULL;
    uint32_t * _times = NULL;
    uint32_t _size    = 0;
    uint32_t _index   = 0;
    uint32_t _count   = 0;
    char     _timeUnits = 'm';
    uint32_t _lastTime  = 0;
    uint32_t _lastValue = 0;
    
    uint32_t getTime()
    {
      if (_timeUnits == 'm') return millis();
      if (_timeUnits == 'u') return micros();
      if (_timeUnits == 's') return millis() / 1000;
      if (_timeUnits == 'h') return millis() / 10;
      if (_timeUnits == 't') return millis() / 100;
      //  default.
      return millis();
    }
};



//  -- END OF FILE --





