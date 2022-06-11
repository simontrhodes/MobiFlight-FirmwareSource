//
// MFServoDriver.h
//
// (C) MobiFlight Project 2022
//

#pragma once

#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>

#define OSC_FREQ   27000000
#define SERVO_FREQ 50

class MFServoDriver
{
public:
    MFServoDriver();
    void attach(uint8_t addr, uint8_t moduleCount);
    void detach();
    void setExternalRange(int min, int max);
    void setInternalRange(int min, int max);
    void update();
    void reset();
    void moveTo(uint8_t PWMpin, uint16_t absolute);

private:
    int                     _mapRange[4];
    bool                    _initialized;
    uint8_t                 _moduleCount; // Number of modules
    Adafruit_PWMServoDriver _servoDriver;
    long                    _targetPos;
};

// MFServoDriver.h