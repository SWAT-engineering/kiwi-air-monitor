#pragma once
#include <Arduino.h>

template <typename T, size_t SIZE>
class Smoothed {
private:
    T raws[SIZE];
    size_t position;
    bool filled;
public:
    Smoothed() {
        position = 0;
        filled = false;
    }

    void put(T value) {
        raws[position] = value;
        position = (position + 1) % SIZE;
        filled = filled || position == 0;
    }

    bool enoughData() {
        return filled;
    }

    void markError() {
        filled = false;
    }

    double get() {
        if (!filled) {
            return NAN;
        }
        double result = 0;
        for(const T &r : raws) {
            result += r;
        }
        return result / SIZE;
    }
};