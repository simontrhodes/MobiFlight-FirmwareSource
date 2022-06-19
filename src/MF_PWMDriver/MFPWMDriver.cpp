//
// MFPWMDriver.cpp
//
// (C) MobiFlight Project 2022
//

#include "mobiflight.h"
#include "MFPWMDriver.h"

MFPWMDriver::MFPWMDriver()
{
    _initialized = false;
}

void MFPWMDriver::attach(uint8_t addr, uint16_t moduleNumber)
{
    _pwmDriver = Adafruit_PWMServoDriver(addr);
    _pwmDriver.begin();
    _pwmDriver.setOscillatorFrequency(OSC_FREQ);
    _pwmDriver.setPWMFreq(SERVO_FREQ); // Analog servos run at ~50 Hz updates
    _initialized  = true;
    _moduleNumber = moduleNumber;
}

void MFPWMDriver::detach()
{
    _pwmDriver.reset();
    _initialized = false;
}

void MFPWMDriver::moveTo(uint8_t PWMpin, uint16_t newValue)
{
    if (_currentValue[PWMpin] != newValue) {
        _pwmDriver.writeMicroseconds(PWMpin, newValue);
        _currentValue[PWMpin] = newValue;
    }
}

// MFPWMDriver.cpp
