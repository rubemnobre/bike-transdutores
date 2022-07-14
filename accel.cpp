#include "accel.hpp"
#include "pico/time.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "pico/stdio.h"
#include <cstdint>
#include <stdio.h>
#define LED 25

const uint8_t init_accel[] = { 0x6B, 0 };
const uint8_t data_request[] = { 0x3B, 0 };
const size_t init_size = 2;
const size_t request_size = 1;
const size_t response_size = 14;
const uint8_t addr = 0x68;
uint8_t buffer[response_size];

Accelerometer::Accelerometer(int i2c_port, int scl, int sda){
    this->sda = sda;
    // Inicialização do LED
    gpio_init(LED);
    gpio_init(scl);
    gpio_init(sda);
    gpio_set_dir(LED, 1);
    gpio_set_function(scl, GPIO_FUNC_I2C);
    gpio_set_function(sda, GPIO_FUNC_I2C);
    gpio_pull_up(scl);
    gpio_pull_up(sda);

    // Ativa a interrupção por timer para a atualização do acelerômetro
    add_repeating_timer_ms(1000, (repeating_timer_callback_t)&Accelerometer::update, this, &acc_timer);

    // Inicializa a porta I2C
    port = i2c0;
    i2c_init(port, 1e5);
    gpio_put(LED, 1);
    i2c_write_timeout_us(port, addr, init_accel, init_size, true, 1000);
    gpio_put(LED, 0);

    for(int i = 0; i < response_size; i++){
        buffer[i] = (int16_t)0;
    }

    printf("done init\n");
}

bool Accelerometer::update(repeating_timer_t *rt){
    auto self = (Accelerometer *) rt->user_data;
    gpio_put(LED, 1);
    i2c_write_timeout_us(self->port, addr, data_request, request_size, true, 10000);
    i2c_read_timeout_us(self->port, addr, buffer, response_size, false, 10000);

    self->acc_x = (uint16_t)buffer[0]<<8 | buffer[1];
    self->acc_y = (uint16_t)buffer[2]<<8 | buffer[3];
    self->acc_z = (uint16_t)buffer[4]<<8 | buffer[5];
    self->angle_x = (uint16_t)buffer[8]<<8 | buffer[9];
    self->angle_y = (uint16_t)buffer[10]<<8 | buffer[11];
    self->angle_z = (uint16_t)buffer[12]<<8 | buffer[13];

    gpio_put(LED, 0);
    return true;
}