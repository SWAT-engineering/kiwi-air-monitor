#include "service/ota-updates.hpp"

OTAUpdates::OTAUpdates(WifiConnection *wifi, MqttConnection *mqtt, KiwiTimer &timer): wifi{wifi}, mqtt{mqtt} {

}
