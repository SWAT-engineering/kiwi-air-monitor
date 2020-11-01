#pragma once
#include <Arduino.h>
#include <PolledTimeout.h>
#include <arduino-timer.h>

using KiwiTimer = Timer<32, millis, void *>;

#define EVERY(__timer, __ms, __type, __call) \
    __timer.every(__ms, [](void * self) -> bool { \
        return static_cast<__type *>(self)->__call(); \
    }, static_cast<void *>(this)); 

