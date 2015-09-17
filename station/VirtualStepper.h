#ifndef VIRTUALSTEPPER_H_INCLUDED
#define VIRTUALSTEPPER_H_INCLUDED
#include <Arduino.h>
static uint8_t vs_map[8]= {0x08,0x0C,0x04,0x06,0x02,0x03,0x01,0x09};

class VirtualSteper
{
private:
    uint8_t vs_a_pin,vs_b_pin,vs_c_pin,vs_d_pin;
    uint8_t vs_Rotate_flag;
public:
    VirtualSteper(uint8_t s0,uint8_t s1,uint8_t s2,uint8_t s3);
    void setup();
    void Rotate(float degree);
    void Forward(uint16_t s);
    void Reverse(uint16_t s);
};

#endif // VIRTUALSTEPPER_H_INCLUDED
