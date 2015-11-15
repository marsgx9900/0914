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
    vs_Rotate_flag=0x00;
    uint8_t newmap=vs_map[vs_Rotate_flag];
    digitalWrite(vs_a_pin,(newmap&0x01)>0);
    digitalWrite(vs_b_pin,(newmap&0x02)>0);
    digitalWrite(vs_c_pin,(newmap&0x04)>0);
    digitalWrite(vs_d_pin,(newmap&0x08)>0);
}

void VirtualSteper::Rotate(float degree)
{
    /*Deg to step*/
    int step=(abs(degree/0.08765));
    /*Rotate by step*/
    if(degree>=0)
    {
        Forward(step);
    }
    else
    {
        Reverse(step);
    }
}

void VirtualSteper::Forward(uint16_t s)
{
    for(int i=0; i<s; i++)
    {
        /*set next step flag,
        if flag reach to limit,reset it.*/
        if (!(vs_Rotate_flag^0x07))
        {
            vs_Rotate_flag=0x00;
        }
        else
        {
            vs_Rotate_flag++;
        }
        /*set pin*/
        uint8_t newmap=vs_map[vs_Rotate_flag];
        digitalWrite(vs_a_pin,(newmap&0x01)>0);
        digitalWrite(vs_b_pin,(newmap&0x02)>0);
        digitalWrite(vs_c_pin,(newmap&0x04)>0);
        digitalWrite(vs_d_pin,(newmap&0x08)>0);
        delayMicroseconds(3000);
    }
}

void VirtualSteper::Reverse(uint16_t s)
{
    for(int i=0; i<s; i++)
    {
        /*set next step flag,
        if flag reach to limit,reset it.*/
        if (!(vs_Rotate_flag^0x00))
        {
            vs_Rotate_flag=0x07;
        }
        else
        {
            vs_Rotate_flag--;
        }
        /*set pin*/
        uint8_t newmap=vs_map[vs_Rotate_flag];
        digitalWrite(vs_a_pin,(newmap&0x01)>0);
        digitalWrite(vs_b_pin,(newmap&0x02)>0);
        digitalWrite(vs_c_pin,(newmap&0x04)>0);
        digitalWrite(vs_d_pin,(newmap&0x08)>0);
        delayMicroseconds(3000);
    }
}
