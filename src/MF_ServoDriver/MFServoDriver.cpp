//
// MFServoDriver.cpp
//
// (C) MobiFlight Project 2022
//

#include "mobiflight.h"
#include "MFServoDriver.h"

MFServoDriver::MFServoDriver()
{
    _initialized = false;
}

void MFServoDriver::attach(uint8_t addr, uint8_t moduleCount)
{
    _servoDriver = Adafruit_PWMServoDriver(addr);
    _servoDriver.begin();
    _servoDriver.setOscillatorFrequency(OSC_FREQ);
    _servoDriver.setPWMFreq(SERVO_FREQ); // Analog servos run at ~50 Hz updates
    _initialized = true;
    _moduleCount = moduleCount;

    setExternalRange(0, 4095);
    setInternalRange(0, 4095); // Servo min and max in micro seconds
}

void MFServoDriver::detach()
{
    _initialized = false;
}

void MFServoDriver::moveTo(uint8_t PWMpin, uint16_t absolute)
{
    int newValue = map(absolute, _mapRange[0], _mapRange[1], _mapRange[2], _mapRange[3]);
    if (_targetPos != newValue) {
        _targetPos = newValue;
        _servoDriver.writeMicroseconds(PWMpin, _targetPos);
    }
}

void MFServoDriver::update()
{
    return;
}

void MFServoDriver::setExternalRange(int min, int max)
{
    _mapRange[0] = min;
    _mapRange[1] = max;
}

void MFServoDriver::setInternalRange(int min, int max)
{
    _mapRange[2] = min;
    _mapRange[3] = max;
}

// MFServoDriver.cpp
