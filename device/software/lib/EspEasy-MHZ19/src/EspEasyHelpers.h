// Extracted from ESPeasy
/****************************************************************************************************************************\
 * Arduino project "ESP Easy" © Copyright www.esp8266.nu
 *
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 * You received a copy of the GNU General Public License along with this program in file 'License.txt'.
 *
 * Additional information about licensing can be found at : http://www.gnu.org/licenses
\*************************************************************************************************************************/

#pragma once

#include <Arduino.h>

inline int32_t timeDiff(const unsigned long prev, const unsigned long next) {
  return ((int32_t) (next - prev));
}

long timePassedSince(unsigned long timestamp) {
  return timeDiff(timestamp, millis());
}

// Check if a certain timeout has been reached.
bool timeOutReached(unsigned long timer) {
  const long passed = timePassedSince(timer);

  return passed >= 0;
}