/*參考自http://blog.xuite.net/chycahock/EDA/225365055-Android%E8%88%87Arduino%E7%9A%84%E8%97%8D%E8%8A%BD%E9%80%9A%E8%A8%8A*/
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>   // 引用程式庫
#define MAX_BTCMDLEN 128
SoftwareSerial BT(11, 10); // RX,TX

byte cmd[MAX_BTCMDLEN]; // received 128 bytes from an Android system
int len = 0; // received command length

void setup()
{
    Serial.begin(9600);   // 與電腦序列埠連線
    Serial.println("BTSerial is ready!");
    //UART
    BT.begin(19200);
}

void loop()
{
    char str[MAX_BTCMDLEN];
    int insize, ii;

    int tick=0;
    while ( tick<MAX_BTCMDLEN )   //Android送過來的字元可能被切成數份
    {
        if ( (insize=(BT.available()))>0 )   // 讀取藍牙訊息
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
