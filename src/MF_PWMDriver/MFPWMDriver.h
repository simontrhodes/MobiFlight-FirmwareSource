//
// MFPWMDriver.h
//
// (C) MobiFlight Project 2022
//

#pragma once

#include <Arduino.h>

#include <Adafruit_PWMServoDriver.h>

#define OSC_FREQ   27000000
#define SERVO_FREQ 50

class MFPWMDriver
{
public:
    MFPWMDriver();
    void attach(uint8_t addr, uint16_t moduleNumber);
    void detach();
    void moveTo(uint8_t PWMpin, uint16_t newValue);

private:
    bool                    _initialized;
    Adafruit_PWMServoDriver _pwmDriver;
    uint16_t                _currentValue[16] = {0}; // Current value of each pwm of the module, initilzed to 0
};

// MFPWMDriver.h