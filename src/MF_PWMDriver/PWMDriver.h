//
// PWMDriver.h
//
// (C) MobiFlight Project 2022
//

#pragma once

#include <Arduino.h>

namespace PWMDriver
{
    void Add(uint8_t addr, uint16_t pwmModules = 0);
    void Clear();
    void OnSet();
}

// PWMDriver.h