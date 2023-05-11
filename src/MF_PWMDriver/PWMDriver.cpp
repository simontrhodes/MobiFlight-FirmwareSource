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
    MFPWMDriver *pwmDrivers[MAX_PWM_DRIVERS];
    uint8_t      pwmDriversRegistered = 0;

    void Add(uint8_t addr, uint16_t pwmModules)
    {

        if (pwmDriversRegistered == MAX_PWM_DRIVERS) {
#ifdef DEBUG2CMDMESSENGER
            // Debug Error Message to Connector
            cmdMessenger.sendCmd(kStatus, F("Reached maximum PWM driver boards"));
#endif
            return;
        }

        if (!FitInMemory(sizeof(MFPWMDriver))) {
#ifdef DEBUG2CMDMESSENGER
            // Debug Error Message to Connector
            cmdMessenger.sendCmd(kStatus, F("PWM Driver Board does not fit in Memory!"));
#endif
            return;
        }
        pwmDrivers[pwmDriversRegistered] = new (allocateMemory(sizeof(MFPWMDriver))) MFPWMDriver();
        pwmDrivers[pwmDriversRegistered]->attach(addr, pwmModules);

        // all set
        pwmDriversRegistered++;

#ifdef DEBUG2CMDMESSENGER
        cmdMessenger.sendCmd(kStatus, F("Added PWM Driver"));
#endif
    }

    void Clear()
    {
        for (uint8_t i = 0; i < pwmDriversRegistered; i++) {
            pwmDrivers[i]->detach();
        }
        pwmDriversRegistered = 0;
#ifdef DEBUG2CMDMESSENGER
        cmdMessenger.sendCmd(kStatus, F("Cleared PWM driver boards"));
#endif
    }

    void OnSet()
    {
        int pwmModule = cmdMessenger.readInt16Arg();
        int pwmPin    = cmdMessenger.readInt16Arg();
        int newPos    = cmdMessenger.readInt16Arg();

        if (pwmModule >= pwmDriversRegistered)
            return;
        pwmDrivers[pwmModule]->moveTo(pwmPin, newPos);
    }

} // namespace

// PWMDriver.cpp
