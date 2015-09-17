#include <Arduino.h>
#include <VirtualWire.h>
#include <string.h>
#include "Keypad.h"
/*************keypad***************/
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] =
{
    {'F','E','D','C'},
    {'B','3','6','9'},
    {'A','2','5','8'},
    {'0','1','4','7'}
};
byte rowPins[ROWS] = {A3, A2, A1, A0}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {A7, A6, A5, A4}; //connect to the column pinouts of the keypad
//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
unsigned long endTime,startTime;

/*************transmitter***************/
const int transmit_pin = 2;
const int receive_pin = 3;
const int transmit_en_pin = 4;

byte last_press_rl;

void setup()
{
    Serial.begin(9600);

    // Initialise the IO and ISR
    vw_set_tx_pin(transmit_pin);
    vw_set_rx_pin(receive_pin);
    vw_set_ptt_pin(transmit_en_pin);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);       // Bits per sec
}


void loop()
{
    char msg[10];
    char customKey = customKeypad.getKey_custom_pressed();
    char _keystate = customKeypad.getState();
    if(customKey)
    {

        switch (customKey)
        {
        case 'A':
            strcpy(msg,"CHANNEL1");
            break;
        case 'B':
            strcpy(msg,"CHANNEL2");
            break;
        case 'C':
            strcpy(msg,"CHANNEL3");
            break;
        case 'D':
            strcpy(msg,"LEFT");
            startTime=millis();
            last_press_rl=0x01;
            break;
        case 'E':
            strcpy(msg,"RIGHT");
            startTime=millis();
            last_press_rl=0x01;
            break;
        case 'F':
            strcpy(msg,"RESTART");
            break;
        default:
            strcpy(msg,"NONE");
            break;
        }
        //catch excepted case
        if(strcmp(msg,"NONE"))
        {
            int msglen=strlen(msg);
            vw_send((uint8_t *)msg, msglen+1);
            vw_wait_tx(); // Wait until the whole message is gone
        }
    }

    if ((_keystate==2)&&(last_press_rl)) //hold & lastpress=left || right
    {
        endTime=millis();
        if ((endTime-startTime)>100)
        {
            vw_send((uint8_t *)"", 1);
            vw_wait_tx(); // Wait until the whole message is gone
            startTime=endTime;
        }
    }

    if(_keystate==3)
    {
        last_press_rl=0x00;
    }

}

