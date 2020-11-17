#!/bin/bash
echo "If this command fails, run once: docker buildx create --use"
docker buildx build --push --platform=linux/amd64,linux/arm64,linux/arm/v7,linux/arm/v6,linux/386 --tag swatengineering/mqtt-2-influx:latest .