#include "pico/time.h"
#include "hardware/i2c.h"
#include <cstdint>
#ifndef ACCEL_H
#define ACCEL_H

typedef struct angle_result angle_result_t;

struct angle_result{
    float theta = 0; // Ângulo no eixo theta em radianos
    float psi = 0; // Ângulo no eixo psi em radianos
    float phi = 0; // Ângulo no eixo phi em radianos
};

class Accelerometer{
    public:
        Accelerometer(int i2c_port, int scl, int sda); // Construtor
        angle_result_t get_current_angle();
        void reset_angle();
        float acc_x; // Aceleração no eixo X em m/s^2
        float acc_y; // Aceleração no eixo Y em m/s^2
        float acc_z; // Aceleração no eixo Z em m/s^2
    private:
        static bool update(repeating_timer_t *rt);
        repeating_timer_t acc_timer;
        i2c_inst_t *port;
        int sda;
        angle_result_t angle_zero;
};

#endif