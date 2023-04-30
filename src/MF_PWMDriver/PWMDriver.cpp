//
// PWMDriver.cpp
//
// (C) MobiFlight Project 2022
//

#include "mobiflight.h"
#include "MFPWMDriver.h"
#include "PWMDriver.h"

namespace PWMDriver
{
    MFPWMDriver *servoDrivers[MAX_PWM_DRIVERS];
    uint8_t      servoDriversRegistered = 0;

    void Add(uint8_t addr, uint16_t pwmModules)
    {

        if (servoDriversRegistered == MAX_PWM_DRIVERS) {
#ifdef DEBUG2CMDMESSENGER
            // Debug Error Message to Connector
            cmdMessenger.sendCmd(kStatus, F("Reached maximum servo driver boards"));
#endif
            return;
        }

        if (!FitInMemory(sizeof(MFPWMDriver))) {
#ifdef DEBUG2CMDMESSENGER
            // Debug Error Message to Connector
            cmdMessenger.sendCmd(kStatus, F("Servo Driver Board does not fit in Memory!"));
#endif
            return;
        }
        servoDrivers[servoDriversRegistered] = new (allocateMemory(sizeof(MFPWMDriver))) MFPWMDriver();
        servoDrivers[servoDriversRegistered]->attach(addr, pwmModules);

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
        int pwmModule = cmdMessenger.readInt16Arg();
        int pwmPin    = cmdMessenger.readInt16Arg();
        int newPos    = cmdMessenger.readInt16Arg();

        if (pwmModule >= servoDriversRegistered)
            return;
        servoDrivers[pwmModule]->moveTo(pwmPin, newPos);
    }

} // namespace

// PWMDriver.cpp
