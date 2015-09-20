#include <Arduino.h>
#include <VirtualStepper.h>
#include <string.h>
#include <Wire.h>
#include <SoftwareSerial.h>


//Reference to ATmega 168/328 (Arduino function PinMapping)
int ad_convertor_pin; //A0~A2
/*ULN2803¥Ñ¤W©¹¤UB'A'BA*/
/*motor constructor¶¶§Ç:ABA'B'*/
VirtualSteper m1(9,10,11,12),m2(5,6,7,8);
const int limit_pin=A3;

//BT Setting
#define MAX_BTCMDLEN 128
SoftwareSerial BT(2,3); // RX,TX
byte cmd[MAX_BTCMDLEN]; // received 128 bytes from an Android system
int len = 0; // received command length


//function prototype
void func1();
int* c_max(int*,int*);
int* c_min(int*,int*);
int* c_find(int*,int*,int);
void usercommand(char *);


void setup()
{
    Serial.begin(9600);	// Debugging only
    Serial.println("Station setup!");

    //Initialize the stepper
    m1.setup();
    m2.setup();

    //Initialize AD convertor
    pinMode(A0,INPUT);
    pinMode(A1,INPUT);
    pinMode(A2,INPUT);

    //Initialize BT
    BT.begin(19200);
    Serial.println("BTSerial is ready!");
}


void loop()
{
    //BT VAR
    char str[MAX_BTCMDLEN];
    int insize, ii;
    int tick=0;

    //從藍芽讀取資料
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

    if ( len ) //從藍芽有收到資料
    {
        cmd[len]='\0';
        sprintf(str,"%s",cmd);
        Serial.print("Data from BT=");
        Serial.println(str);
        usercommand(str);
    }

    len = 0;
}

void usercommand(char * input)
{
    Serial.print("Usercommand data=");
    Serial.println(input);
    //compare with customed string
    if(!strcmp(input,"CHANNEL1"))
    {
        ad_convertor_pin=A0;
        func1();
    }
    if(!strcmp(input,"CHANNEL2"))
    {
        ad_convertor_pin=A1;
        func1();
    }
    if(!strcmp(input,"CHANNEL3"))
    {
        ad_convertor_pin=A2;
        func1();
    }
    if(!strcmp(input,"LEFT"))
    {
        Serial.println("LEFT");
        m2.Rotate(-3);
    }
    if(!strcmp(input,"RIGHT"))
    {
        Serial.println("RIGHT");
        m2.Rotate(3);
    }
}


void func1()
{
    /*Rotate to one side*/
    Serial.println("Wait for rotating to left side...");
    while(analogRead(limit_pin)>100)
    {
        m1.Rotate(-0.1);
    }
    /*Rotate by 180 degree ,and recode ad value every 1 degree*/
    int ad_value_array[181];
    int i;
    for(i=0; i<180; i++)
    {
        ad_value_array[i]=analogRead(ad_convertor_pin);
        Serial.print(i);
        Serial.print("=");
        Serial.println(ad_value_array[i]);
        m1.Rotate(1);
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
    Serial.print("Index:");
    Serial.println(ad_max_index-ad_value_array);
    Serial.print("Min:");
    Serial.println(*ad_min_value);
    Serial.print("Index:");
    Serial.println(ad_min_index-ad_value_array);
    /*Rotate to ad_max_position*/
    int temp;
    temp=-(180-(ad_max_index-ad_value_array));
    Serial.print("Rotate angle:");
    Serial.println(temp);
    Serial.println("Please wait...");
    m1.Rotate((float)temp);
    Serial.println("Finish!");
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
