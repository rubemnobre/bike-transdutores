#include "accel.hpp"
#include "pico/time.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#define LED 25

Accelerometer::Accelerometer(int i2c_port, int scl, int sda){
    // Inicialização do LED
    gpio_init(LED);
    gpio_init(scl);
    gpio_init(sda);
    gpio_set_dir(LED, 1);
    gpio_set_function(scl, GPIO_FUNC_I2C);
    gpio_set_function(sda, GPIO_FUNC_I2C);

    // Ativa a interrupção por timer para a atualização do acelerômetro
    add_repeating_timer_ms(1000, (repeating_timer_callback_t)&Accelerometer::update, NULL, &acc_timer);

    // Inicializa a porta I2C
    auto port = i2c_port?i2c1:i2c0;
    i2c_init(port, 1e5);
}

bool Accelerometer::update(repeating_timer_t *rt){
    gpio_put(25, 1);
    gpio_put(25, 0);
    return true;
}