# Server documentation & setup for Kiwi

The Kiwi Air Monitor can optionally send measurments to an MQTT server. This allows for building management and remote updates of settings & firmware.

This directory contains:

- `demo-config`: a docker-compose configuration for mqtt, influx, our own forwarder from mqtt to influx, and grafana for dashboards
- `mqtt-2-influx`: a small forwarder that takes kiwi sensor messages, optionally adds extra tags (such as building specific meta data) and inserts it into the `kiwi` database on influx
- `generator`: a small program that can fake one or more kiwi sensors. This is useful for testing and developing the server side.
- `doc`: documentation about the mqtt messages, and several setup related documentation and advice
