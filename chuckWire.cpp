// For more compatibility with older version of arduino
// All compatibility conditional statements written using preproc to not increase size of compiled bin
#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "chuckWire.h"
// For now, this depends on Wire.h
#include <Wire.h>


