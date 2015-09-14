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
    {'0','1','2','3'},
    {'4','5','6','7'},
    {'8','9','A','B'},
    {'C','D','E','F'}
};
byte rowPins[ROWS] = {3, 2, 1, 0}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 6, 5, 4}; //connect to the column pinouts of the keypad
//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);


/*************transmitter***************/
const int transmit_pin = 12;
const int receive_pin = 11;
const int transmit_en_pin = 3;

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

byte count = 1;

void loop()
{
    char customKey = customKeypad.getKey();

    if(customKey)
    {
        char msg[10];
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
            break;
        case 'E':
            strcpy(msg,"RIGHT");
            break;
        case 'F':
            strcpy(msg,"RESTART");
            break;
        }
        int msglen=strlen(msg);
        vw_send((uint8_t *)msg, msglen+1);
        vw_wait_tx(); // Wait until the whole message is gone
    }

}

