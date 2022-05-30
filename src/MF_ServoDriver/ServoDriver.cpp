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
    MFServoDriver *servoDrivers[MAX_MFServoDriver];
    uint8_t        servoDriversRegistered = 0;

    void Add(uint8_t addr)
    {

                if (servoDriversRegistered == MAX_MFServoDriver) {
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
        servoDrivers[servoDriversRegistered]->attach(addr);

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
        int servo  = cmdMessenger.readInt16Arg();
        int newPos = cmdMessenger.readInt16Arg();

        if (servo >= servoDriversRegistered)
            return;
        servo = 0;
        servoDrivers[servo]->moveTo(newPos);

        setLastCommandMillis();
    }

    void update()
    {
        for (uint8_t i = 0; i < servoDriversRegistered; i++) {
            servoDrivers[i]->update();
        }
    }
} // namespace

// ServoDriver.cpp
