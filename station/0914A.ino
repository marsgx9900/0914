#include <Arduino.h>
#include <VirtualWire.h>
#include <VirtualStepper.h>
#include <SoftReset.h>
#include <string.h>
//RECEIVER

//Reference to ATmega 168/328 (Arduino function PinMapping)
const int transmit_pin = 2;
const int receive_pin = 3;
const int transmit_en_pin = 4;
int ad_convertor_pin; //A0~A2
VirtualSteper m1(5,6,7,8),m2(9,10,11,12);
const int limit_pin=A3;
int previous_dir;

//function prototype
void func1();
int* c_max(int*,int*);
int* c_min(int*,int*);
int* c_find(int*,int*,int);


void setup()
{
    Serial.begin(9600);	// Debugging only
    Serial.println("Station setup finished");

    // Initialise the IO and ISR
    vw_set_tx_pin(transmit_pin);
    vw_set_rx_pin(receive_pin);
    vw_set_ptt_pin(transmit_en_pin);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);	 // Bits per sec
    vw_rx_start();       // Start the receiver PLL running

    //Initialize the stepper
    m1.setup();
    m2.setup();

}

void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    vw_wait_rx();
    if (vw_get_message(buf, &buflen)) // Non-blocking
    {

        // Message with a good checksum received, dump it.
        /*
        Serial.print("Got: ");
        for (int i = 0; i < buflen; i++)
        {
        Serial.print(buf[i], HEX);
        Serial.print(' ');
        }
        Serial.println();
        */
        //compare with customed string
        if(!strcmp(reinterpret_cast<char *>(buf),"CHANNEL1"))
        {
            ad_convertor_pin=A0;
            func1();
        }
        if(!strcmp(reinterpret_cast<char *>(buf),"CHANNEL2"))
        {
            ad_convertor_pin=A1;
            func1();
        }
        if(!strcmp(reinterpret_cast<char *>(buf),"CHANNEL3"))
        {
            ad_convertor_pin=A2;
            func1();
        }
        if(!strcmp(reinterpret_cast<char *>(buf),"LEFT"))
        {
            m2.rotate(-0.1);
            previous_dir=-1;
        }
        if(!strcmp(reinterpret_cast<char *>(buf),"RIGHT"))
        {
            m2.rotate(0.1);
            previous_dir=1;
        }
        if(!strcmp(reinterpret_cast<char *>(buf),"RESTART"))
        {
            soft_restart();
        }
        if(!strcmp(reinterpret_cast<char *>(buf),""))
        {
            if(previous_dir=-1)
            {
                m2.rotate(-0.1);
            }
            else
            {
                m2.rotate(0.1);
            }
        }
    }

}

void func1()
{
    /*rotate to one side*/
    if(analogRead(limit_pin)<100)
    {
        m1.rotate(0.1);
    }
    /*rotate by 180 degree ,and recode ad value every 1 degree*/
    int ad_value_array[181];
    int i;
    for(i=0; i<180; i++)
    {
        ad_value_array[i]=analogRead(ad_convertor_pin);
        Serial.print(i);
        Serial.print("=");
        Serial.println(ad_value_array[i]);
        m1.rotate(1);
    }
    ad_value_array[i]=analogRead(ad_convertor_pin);
    Serial.print(i);
    Serial.print("=");
    Serial.println(ad_value_array[i]);
    /*find max value by used binary tree method*/
    int* ad_max_value=c_max(ad_value_array,ad_value_array+181);
    int* ad_min_value=c_min(ad_value_array,ad_value_array+181);
    int* ad_max_index=c_find(ad_value_array,ad_value_array+181,*ad_max_value);
    int* ad_min_index=c_find(ad_value_array,ad_value_array+181,*ad_min_value);
    Serial.print("Max:");
    Serial.println(*ad_max_value);
    Serial.println(ad_max_index-ad_value_array);
    Serial.print("Min:");
    Serial.println(*ad_min_value);
    Serial.println(ad_min_index-ad_value_array);
    /*rotate to ad_max_position*/
    int temp;
    temp=-(180-(ad_max_index-ad_value_array));
    Serial.print("Rotate angle:");
    Serial.println(temp);
    m1.rotate(temp);
    Serial.println("Finish");
}

int* c_max(int * first,int * last)
{
    if (first==last) return last;
    int* largest = first;

    while (++first!=last)
        if (*largest<*first)
            largest=first;
    return largest;
}
int* c_min(int * first,int * last)
{
    if (first==last) return last;
    int* smallest = first;

    while (++first!=last)
        if (*first<*smallest)    // or: if (comp(*first,*smallest)) for version (2)
            smallest=first;
    return smallest;
}
int* c_find(int * first,int * last,int val)
{
    while (first!=last)
    {
        if (*first==val) return first;
        ++first;
    }
    return last;
}
