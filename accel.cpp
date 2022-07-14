#include "accel.hpp"
#include "pico/time.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include <cstdint>
#define LED 25

static uint8_t init_accel[] = { 0x6B, 0 };
static uint8_t data_request[] = { 0x3B };
static size_t init_size = 2;
static size_t request_size = 1;
static size_t response_size = 14;
static uint8_t addr = 0x68;

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
    port = i2c_port?i2c1:i2c0;
    i2c_init(port, 1e5);
    i2c_write_blocking(port, addr, init_accel, init_size, false);
}

bool Accelerometer::update(repeating_timer_t *rt){
    uint8_t buffer[response_size];
    gpio_put(25, 1);

    i2c_write_blocking(port, addr, data_request, request_size, false);
    i2c_read_blocking(port, addr, buffer, response_size, false);

    acc_x = buffer[0]<<8 | buffer[1];
    acc_y = buffer[2]<<8 | buffer[3];
    acc_z = buffer[4]<<8 | buffer[5];
    angle_x = buffer[8]<<8 | buffer[9];
    angle_y = buffer[10]<<8 | buffer[11];
    angle_z = buffer[12]<<8 | buffer[13];

    gpio_put(25, 0);
    return true;
}