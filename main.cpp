#include "pico/time.h"
#include "hardware/spi.h"
#include "accel.hpp"
#include "pico/stdio.h"
#include <stdio.h>

int main() {
    stdio_init_all();
    auto acc = new Accelerometer(0, 16, 17);
    while(1) {
        sleep_ms(1000);
        printf("%d %d %d\n", acc->acc_x, acc->acc_y, acc->acc_z);
    }
}