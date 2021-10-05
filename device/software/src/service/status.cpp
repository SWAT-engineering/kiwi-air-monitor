#include "service/status.hpp"

static const char* DISPLAY_OFF = "off";
static const char* DISPLAY_ON = "on";

static bool showDisplay = true;

Status::Status(WifiConnection *wifi, MqttConnection *mqtt, KiwiTimer &timer): wifi(wifi), mqtt(mqtt) {
    EVERY(timer, 60*1000, Status, update);

    mqtt->subscribe("kiwi/all/display", [](char* buf, uint16_t len) -> void {
        if (2 <= len && len <= 5) {
            if (memcmp(buf, DISPLAY_OFF, strlen(DISPLAY_OFF)) == 0) {
                showDisplay = false;
            }
            else if (memcmp(buf, DISPLAY_ON, strlen(DISPLAY_ON)) == 0) {
                showDisplay = true;
            }
        }
    });
}

bool Status::mqttConnected() {
    return mqtt->isConnected();
}

bool Status::wifiConnected() {
    return wifi->isConnected();
}

bool Status::shouldShowScreen() {
    return showDisplay;
}

bool Status::update() {
    mqtt->publish("state/Active", "true");
    mqtt->publish("state/Memory", ESP.getFreeHeap());
    mqtt->publish("state/Voltage", ESP.getVcc() / 1024.0);
    return true;
}
