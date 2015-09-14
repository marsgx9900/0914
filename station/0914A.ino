#include <Arduino.h>
#include <VirtualWire.h>
#include <string.h>
//RECEIVER

const int transmit_pin = 12;
const int receive_pin = 11;
const int transmit_en_pin = 3;


void setup()
{
    delay(1000);
    Serial.begin(9600);	// Debugging only
    Serial.println("Reveiver setup");

    // Initialise the IO and ISR
    vw_set_tx_pin(transmit_pin);
    vw_set_rx_pin(receive_pin);
    vw_set_ptt_pin(transmit_en_pin);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);	 // Bits per sec

    vw_rx_start();       // Start the receiver PLL running

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

        /*convert raw data to string//doesn't
        char receiveStr[10];
        for (int i = 0; i < buflen; i++)
        {
            receiveStr[i]=buf[i];
        }
        receiveStr[buflen]=0;*/


        //compare with customed string
        if(!strcmp(receiveStr,"CHANNEL1"));
        if(!strcmp(receiveStr,"CHANNEL2"));
        if(!strcmp(receiveStr,"CHANNEL3"));
        if(!strcmp(receiveStr,"LEFT"));
        if(!strcmp(receiveStr,"RIGHT"));
        if(!strcmp(receiveStr,"RESTART"));

    }

}

