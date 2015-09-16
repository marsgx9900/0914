#include <VirtualStepper.h>

VirtualSteper::VirtualSteper(uint8_t s0,uint8_t s1,uint8_t s2,uint8_t s3)
{
    vs_a_pin=s0;
    vs_b_pin=s1;
    vs_c_pin=s2;
    vs_d_pin=s3;
}

void VirtualSteper::setup()
{
    pinMode(vs_a_pin, OUTPUT);
    pinMode(vs_b_pin, OUTPUT);
    pinMode(vs_c_pin, OUTPUT);
    pinMode(vs_d_pin, OUTPUT);
    vs_rotate_flag=0x00;
    uint8_t newmap=vs_map[vs_rotate_flag];
    digitalWrite(vs_a_pin,(newmap&0x01)>0);
    digitalWrite(vs_b_pin,(newmap&0x02)>0);
    digitalWrite(vs_c_pin,(newmap&0x04)>0);
    digitalWrite(vs_d_pin,(newmap&0x08)>0);
}

void VirtualSteper::rotate(float degree)
{
    /*Deg to step*/
    uint16_t step=abs(degree/0.08765);
    /*rotate by step*/
    if(degree>=0)
    {
        forward(step);
    }
    else
    {
        reverse(step);
    }
}

void VirtualSteper::forward(uint16_t s)
{
    for(int i=0; i<s; i++)
    {
        /*set next step flag,
        if flag reach to limit,reset it.*/
        if (!(vs_rotate_flag^0x07))
        {
            vs_rotate_flag=0x00;
        }
        else
        {
            vs_rotate_flag++;
        }
        /*set pin*/
        uint8_t newmap=vs_map[vs_rotate_flag];
        digitalWrite(vs_a_pin,(newmap&0x01)>0);
        digitalWrite(vs_b_pin,(newmap&0x02)>0);
        digitalWrite(vs_c_pin,(newmap&0x04)>0);
        digitalWrite(vs_d_pin,(newmap&0x08)>0);
        delayMicroseconds(2000);
    }
}

void VirtualSteper::reverse(uint16_t s)
{
    for(int i=0; i<s; i++)
    {
        /*set next step flag,
        if flag reach to limit,reset it.*/
        if (!(vs_rotate_flag^0x00))
        {
            vs_rotate_flag=0x07;
        }
        else
        {
            vs_rotate_flag--;
        }
        /*set pin*/
        uint8_t newmap=vs_map[vs_rotate_flag];
        digitalWrite(vs_a_pin,(newmap&0x01)>0);
        digitalWrite(vs_b_pin,(newmap&0x02)>0);
        digitalWrite(vs_c_pin,(newmap&0x04)>0);
        digitalWrite(vs_d_pin,(newmap&0x08)>0);
        delayMicroseconds(2000);
    }
}
