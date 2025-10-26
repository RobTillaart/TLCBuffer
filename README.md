
[![Arduino CI](https://github.com/RobTillaart/TLCBuffer/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/TLCBuffer/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/TLCBuffer/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/TLCBuffer/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/TLCBuffer/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/TLCBuffer.svg)](https://github.com/RobTillaart/TLCBuffer/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/TLCBuffer/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/TLCBuffer.svg?maxAge=3600)](https://github.com/RobTillaart/TLCBuffer/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/TLCBuffer.svg)](https://registry.platformio.org/libraries/robtillaart/TLCBuffer)


# TLCBuffer

Arduino library for a Time Length Compressed Circular Buffer.

TODO RLEBuffer()
- full()
- empty()
- readValue() reads oldest.


## Description

**Experimental**

This library is to store data in a circular buffer with Time Length Compression.

The library is a spin of of the LogicAnalyzer library as it needs to store as much
data as possible.

One can have a measurement and that measurement stays stable for long time and then
has some short fluctuations. Instead of storing many the same values in the buffer
it is stored how long the data stayed the same.

An example

```
TLCBuffer = { (10000, 15), (200, 20),  ...
```
The value stays 10000 millis the value 15 and then for 200 millis the value 20.



### Related

- https://github.com/RobTillaart/LogicAnalyzer
  - logicAnalyzer_4_channel_buffer.ino
- https://github.com/RobTillaart/RLEBuffer (todo)
- https://github.com/RobTillaart/TLCBuffer


### Tested

Tested on Arduino UNO R3


### Performance

TODO: create + run performance sketch on hardware.


## Interface

```cpp
#include "TLCBuffer.h"
```

### Constructor

- **TLCBuffer(uint32_t size)** create a circular buffer of size.
- **void reset()** reset the circular buffer (todo really clear?)
- **uint32_t size()** return size set in constructor.

### Read Write

- **void writeValue(uint32_t value)**
- **uint32_t readValue(uint32_t index)**
- **uint32_t readDuration(uint32_t index)**


## Future

#### Must

- improve documentation
- test
- keep it simple
- add counter 


#### Should

- need bool begin(size) if allocate fails.
- investigate template version, first get one static version working.
- switch between micros / millis (default) / seconds ?
- handle period of 0 properly (any unit)


#### Could

- add unit tests

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


