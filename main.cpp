#include "pico/time.h"
#include "hardware/spi.h"
#include "accel.hpp"

int main() {
    auto acc = new Accelerometer(0, 16, 17);
    while(1) {

    }
}