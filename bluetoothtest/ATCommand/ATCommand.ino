/*�ѦҦ�http://swf.com.tw/?p=712*/
#include <Arduino.h>
#include <SoftwareSerial.h>   // �ޥε{���w

// �w�q�s���Ť��Ҳժ��ǦC��
SoftwareSerial BT(11, 10); // RX,TX
char val;  // �x�s������ƪ��ܼ�

void setup() {
  Serial.begin(9600);   // �P�q���ǦC��s�u
  Serial.println("BT is ready!");

  // �]�w�Ť��Ҳժ��s�u�t�v
  // �p�G�OHC-05�A�Ч令38400
  BT.begin(38400);
}

void loop() {
  // �Y����u�ǦC��ʱ������v����ơA�h�e���Ť��Ҳ�
  if (Serial.available()) {
    val = Serial.read();
    BT.print(val);
  }

  // �Y�����Ť��Ҳժ���ơA�h�e��u�ǦC��ʱ������v
  if (BT.available()) {
    val = BT.read();
    Serial.print(val);
  }
}
