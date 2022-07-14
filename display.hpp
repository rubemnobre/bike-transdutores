#include <cstdint>

#ifndef DISPLAY_H
#define DISPLAY_H

class Display{
    public:
        Display(int sd_pin, int sclk_pin, int load_pin);
        void update(int n);
        void update(int msd, int lsd);
    private:
        uint8_t a = 0;
        uint8_t b = 0;
        uint8_t ser = 0;
        uint8_t rclk = 0;
        uint8_t srclk = 0;
};

#endif