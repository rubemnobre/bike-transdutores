#include "display.hpp"
#include "hardware/gpio.h"
#include "pico/time.h"
#include <cmath>

const uint8_t decode[] = { 0x03, 0x9F, 0x25, 0x0D, 0x99, 0x49, 0x41, 0x1F, 0x01, 0x09 };

Display::Display(int sd_pin, int sclk_pin, int load_pin){
    ser = sd_pin;
    rclk = load_pin;
    srclk = sclk_pin;

    gpio_init(ser);
    gpio_init(rclk);
    gpio_init(srclk);
    gpio_set_dir(ser, 1);
    gpio_set_dir(rclk, 1);
    gpio_set_dir(srclk, 1);
    gpio_pull_up(ser);
    gpio_pull_up(rclk);
    gpio_pull_up(srclk);
}

void Display::update(int n){
    int lsd = abs(n) % 10;
    int msd = (abs(n) / 10) % 10;
    update(msd, lsd);
}

void Display::update(int msd, int lsd){
    a = msd;
    b = lsd;
    int bit = 0;
    for(int i = 0; i < 8; i++){
        gpio_put(srclk, 0);
        gpio_put(ser, 0x01 & (decode[lsd] >> i));
        gpio_put(srclk, 1);
        gpio_put(srclk, 0);
        gpio_put(rclk, 0);
        gpio_put(rclk, 1);
    }
    for(int i = 0; i < 8; i++){
        gpio_put(srclk, 0);
        gpio_put(ser, 0x01 & (decode[msd] >> i));
        gpio_put(srclk, 1);
        gpio_put(srclk, 0);
        gpio_put(rclk, 0);
        gpio_put(rclk, 1);
    }
}