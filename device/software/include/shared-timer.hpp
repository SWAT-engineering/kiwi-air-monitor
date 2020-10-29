#pragma once
#include <Arduino.h>
#include <PolledTimeout.h>
#include "arduino-timer.hpp"

using KiwiTimer = Timer<32, millis, void *>;