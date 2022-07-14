#include "pico/time.h"
#include "hardware/spi.h"
#include "accel.hpp"
#include "display.hpp"
#include "pico/stdio.h"
#include <stdio.h>
#include <cmath>

int main() {
    stdio_init_all();
    auto acc = new Accelerometer(0, 16, 17);
    auto disp = new Display(15, 14, 13);
    disp->update(0, 0);
    int i = 0;
    while(1) {
        auto angles = acc->get_current_angle();
        // printf("%.3f %.3f %.3f -> %.3f %.3f %.3f\n", acc->acc_x, acc->acc_y, acc->acc_z, angles.theta, angles.psi, angles.phi);
        printf("%d\n", angles.psi *180.0/3.14159);
        disp->update(angles.psi *180.0/3.14159);
        i++;
        i %= 100;
        sleep_ms(100);
    }
}