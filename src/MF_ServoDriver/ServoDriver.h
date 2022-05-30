//
// ServoDriver.h
//
// (C) MobiFlight Project 2022
//

#pragma once

#include <Arduino.h>

namespace ServoDriver
{
    void Add(uint8_t addr = 0x40);
    void Clear();
    void OnSet();
    void OnReset();
    void update();

}

// ServoDriver.h