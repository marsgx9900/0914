/*�ѦҦ�http://blog.xuite.net/chycahock/EDA/225365055-Android%E8%88%87Arduino%E7%9A%84%E8%97%8D%E8%8A%BD%E9%80%9A%E8%A8%8A*/
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>   // �ޥε{���w
#define MAX_BTCMDLEN 128
SoftwareSerial BT(11, 10); // RX,TX

byte cmd[MAX_BTCMDLEN]; // received 128 bytes from an Android system
int len = 0; // received command length

void setup()
{
    Serial.begin(9600);   // �P�q���ǦC��s�u
    Serial.println("BTSerial is ready!");
    //UART
    BT.begin(19200);
}

void loop()
{
    char str[MAX_BTCMDLEN];
    int insize, ii;

    int tick=0;
    while ( tick<MAX_BTCMDLEN )   //Android�e�L�Ӫ��r���i��Q�����ƥ�
    {
        if ( (insize=(BT.available()))>0 )   // Ū���Ť��T��
        {
            for ( ii=0; ii<insize; ii++ )
            {
                cmd[(len++)%MAX_BTCMDLEN]=char(BT.read());
            }
        }
        else
        {
            tick++;
        }
    }

    if ( len )
    {
        cmd[len]='\0';
        sprintf(str,"%s",cmd);
        Serial.println(str);
    }
    len = 0;
}
