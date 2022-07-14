#include "pico/time.h"
#include "hardware/i2c.h"
#include <cstdint>
#ifndef ACCEL_H
#define ACCEL_H

class Accelerometer{
    public:
        Accelerometer(int i2c_port, int scl, int sda);
        int16_t acc_x;
        int16_t acc_y;
        int16_t acc_z;
        int16_t angle_x;
        int16_t angle_y;
        int16_t angle_z;
    private:
        bool update(repeating_timer_t *rt);
        repeating_timer_t acc_timer;
        i2c_inst *port;
};

#endif