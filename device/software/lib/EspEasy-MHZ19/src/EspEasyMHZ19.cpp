#include "EspEasyMHZ19.hpp"
#include "_P049_MHZ19.hpp"


void EspEasyMHZ19::init() {
    if (hardware != nullptr) {
        delete hardware;
    }
    hardware = new P049_data_struct();
    hardware->init(rx, tx, abcDisabled);
    initializing = true;
    lastReset = millis();
}

bool EspEasyMHZ19::isReady() {
    if (!initializing) {
        return true;
    }
    initializing = (millis() - lastReset) < (3 * 60 * 1000);
    return !initializing;
}

bool EspEasyMHZ19::calibrateZero() {
    if (isReady()) {
        hardware->send_mhzCmd(mhzCmdCalibrateZero);
        return true;
    }
    return false;
}
bool EspEasyMHZ19::reset() {
    if (isReady()) {
        hardware->send_mhzCmd(mhzCmdReset);
        init();
        return true;
    }
    return false;
}

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
uint16_t EspEasyMHZ19::readCO2() {
    bool expectReset = false;
    unsigned int ppm = 0;
    signed int temp = 0;
    unsigned int s = 0;
    float u = 0;
    if (hardware->read_ppm(ppm, temp, s, u)) {
        // During (and only ever at) sensor boot, 'u' is reported as 15000
        // We log but don't process readings during that time
        if (u == 15000) {
            if (hardware->ABC_Disable) {
                // After bootup of the sensor the ABC will be enabled.
                // Thus only actively disable after bootup.
                hardware->ABC_MustApply = true;
            }
            return 0;
            // Finally, stable readings are used for variables
        }
        else {
            String log = "";
            if (Plugin_049_Check_and_ApplyFilter(prevValue, ppm, s, filter, log)) {
                if (s == 0 || s == 64) {
                    // Reading is stable.
                    if (hardware->ABC_MustApply) {
                        // Send ABC enable/disable command based on the desired state.
                        if (hardware->ABC_Disable) {
                            hardware->send_mhzCmd(mhzCmdABCDisable);
                        }
                        else {
                            hardware->send_mhzCmd(mhzCmdABCEnable);
                        }
                        hardware->ABC_MustApply = false;
                    }
                }
            }
            else {
                return 0;
            }
        }
    }
    // Sensor responds with 0x99 whenever we send it a measurement range adjustment
    else if (hardware->receivedCommandAcknowledgement(expectReset)) {
        return 0;
    }
    else {
        // Check for stable reads and allow unstable reads the first 3 minutes after reset.
        if (hardware->nrUnknownResponses > 10 && hardware->initTimePassed) {
            init();
        }
        return 0;
    }
    if (expectReset) {
        init();
        return 0;
    }
    if (!isReady()) {
        return 0;
    }
    if (millis() - lastABCSet > (12 * 60 * 60 * 1000ul)) {
        // just be sure to send the ABC command every once in a while
        hardware->ABC_MustApply = true;
        lastABCSet = millis();
    }
    return ppm;
}
