#!/bin/bash
echo "If this command fails, run once: docker buildx create --use"
docker buildx build --load --tag swatengineering/mqtt-2-influx .