#include "pico/time.h"
#ifndef ACCEL_H
#define ACCEL_H

class Accelerometer{
    public:
        Accelerometer(int i2c_port, int scl, int sda);
        float acc_x;
        float acc_y;
        float acc_z;
        float angle_x;
        float angle_y;
        float angle_z;
    private:
        bool update(repeating_timer_t *rt);
        repeating_timer_t acc_timer;
        int led = 1;
};

#endif