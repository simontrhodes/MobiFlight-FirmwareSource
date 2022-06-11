//
// ServoDriver.cpp
//
// (C) MobiFlight Project 2022
//

#include "mobiflight.h"
#include "MFServoDriver.h"
#include "ServoDriver.h"

namespace ServoDriver
{
    MFServoDriver *servoDrivers[MAX_MFSERVODRIVERS];
    uint8_t        servoDriversRegistered = 0;

    void Add(uint8_t addr, uint8_t modules)
    {

        if (servoDriversRegistered == MAX_MFSERVODRIVERS) {
#ifdef DEBUG2CMDMESSENGER
            // Debug Error Message to Connector
            cmdMessenger.sendCmd(kStatus, F("Reached maximum servo driver boards"));
#endif
            return;
        }

        if (!FitInMemory(sizeof(MFServoDriver))) {
            // Error Message to Connector
            cmdMessenger.sendCmd(kStatus, F("Servo Driver Board does not fit in Memory!"));
            return;
        }
        servoDrivers[servoDriversRegistered] = new (allocateMemory(sizeof(MFServoDriver))) MFServoDriver();
        servoDrivers[servoDriversRegistered]->attach(addr, modules);

        // all set
        servoDriversRegistered++;

#ifdef DEBUG2CMDMESSENGER
        cmdMessenger.sendCmd(kStatus, F("Added Servo Driver"));
#endif
    }

    void Clear()
    {
        for (uint8_t i = 0; i < servoDriversRegistered; i++) {
            servoDrivers[i]->detach();
        }
        servoDriversRegistered = 0;
#ifdef DEBUG2CMDMESSENGER
        cmdMessenger.sendCmd(kStatus, F("Cleared servo driver boards"));
#endif
    }

    void OnSet()
    {
        int module = cmdMessenger.readInt16Arg();
        int pwmpin = cmdMessenger.readInt16Arg();
        int newPos = cmdMessenger.readInt16Arg();

        if (module >= servoDriversRegistered)
            return;
        servoDrivers[module]->moveTo(pwmpin, newPos);

        // setLastCommandMillis();
    }

} // namespace

// ServoDriver.cpp
