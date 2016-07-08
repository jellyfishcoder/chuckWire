/*
 * chuckWire.h - One more Arduino library for wii nunchucks
 * Version: 0.0.1
 * Library by Alexander Pope
 *
 * You may modify and/or redistribute this Library under the terms of the attatched LICENSE
 * file. If you did not recieve this file, it is at https://raw.githubusercontent.com/jellyfishcoder/chuckWire/master/LICENSE
 * If this URL is not existant, because the github repository https://github.com/jellyfishcoder/chuckWire
 * has been deleted, than this Library, including this file, are licensed under the
 * Mozilla Public License Version 2.0
 */

// Ensure this file is only included once
#ifndef chuckWire_h
#define chuckWire_h

#include <inttypes.h>
#include <Wire.h>

typedef struct {
	uint8_t joyX;
	uint8_t joyY;
	uint8_t accelX;
	uint8_t accelY;
	uint8_t accelZ;
	bool buttonZ : 1;
	bool buttonC : 1;
	uint8_t lsbX : 2;
	uint8_t lsbY : 2;
	uint8_t lsbZ : 2;
} chuckWireData;

// chuck class
class chuck {
	// public stuff
	public:
		// constructors: (called when instanse of class created)
		chuck(unsigned int address, int powerPin, int groundPin);
		chuck(unsigned int address);
		chuck(int powerPin, int groundPin);
		chuck();

		// variables (joystick values):
		inline int joyX() { return (int)data.parsed.joyX - calib.joyX; }
		inline int joyY() { return (int)data.parsed.joyY - calib.joyY; }
		// variables (joystick posistion):
		inline bool joyLeft() { return ((int)data.parsed.joyX - calib.joyX) < 50; }
		inline bool joyRight() { return ((int)data.parsed.joyX - calib.joyX) > 200; }
		inline bool joyUp() { return ((int)data.parsed.joyY - calib.joyY) > 200; }
		inline bool joyDown() { return ((int)data.parsed.joyY - calib.joyY) < 60; }
		// variables (accelerometer values):
		inline int accelX() const {
			return (int)((data.parsed.accelX << 2) | data.parsed.lsbX) - ((calib.accelX << 2) | calib.lsbX);
		}
		inline int accelY() const {
			(int)((data.parsed.accelY << 2) | data.parsed.lsbY) - ((calib.accelY << 2) | calib.lsbY);
		}
		inline int accelZ() const {
			(int)((data.parsed.accelZ << 2) | data.parsed.lsbZ) - ((calib.accelZ << 2) | calib.lsbZ);
		}
		// variables (button states):
		inline bool buttonZ() const { return !data.parsed.buttonZ; }
		inline bool buttonC() const { return !data.parsed.buttonC; }

		// methods:
		void initialize();
		void calibrate(int joyX, int joyY, int accelX, int accelY, int accelZ, int lsbX, int lsbY, int lsbZ);
		void calibrate();

	// private stuff
	private:
		static int Address = 0x52;

		// Decode Nunchuck data
		static inline uint8_t decode(uint8_t b) { return (b ^ 0x17) + 0x17; }

		// Retrieved data
		union {
			uint8_t buffer[6];
			// Parsed data
			chuckWireData parsed;
		} data;

		chuckWireData calib;
};
#endif
