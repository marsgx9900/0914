可調天線方向之雙頻中繼器
----------


簡介
----------
運用arduino與MIT inventory製作程式，結合手機APP藉以實踐改變天線方向。


開發軟體
----------
* [Arduino 1.6.5] (https://www.arduino.cc/en/Main/Software)
* [Codeblocks Arduino IDE (Release 20140626)] (http://arduinodev.com/codeblocks/)
* [EAGLE 7.4.0] (http://www.cadsoftusa.com/)  
  * 使用到的元件庫:[EAGLE Library-RBBB](https://moderndevice.com/RBBB.lbr.zip)、[ncue_ee](Layout\eagle-lbr\ncue_ee.lbr)
* [MIT inventory 2] (http://ai2.appinventor.mit.edu/)



需求
----------
* 主體使用雙玻版。[佈線圖] (Layout/main/schPic.png)、[PCB-TOP Layer] (Layout/main/top.pdf)、 [PCB-Bottom Layer] (Layout/main/bottom.pdf)  
	* 正面  
	![main1](Picture/forward.jpg)
	* 反面  
	![main2](Picture/backward.jpg)
	* 實際運作  
	![main3](Picture/running.jpg)

* Bluetooth module (HC-05):與手機溝通，160NTD/個  
	![bt](Picture/bt.jpg)

* FT232 module:與PC溝通(Serial Commucation)、用來燒錄ATmega328的程式、供應5V給ATmega328，180/個  
	* 正面  
	![bt1](Picture/ft232_1.jpg)
	* 反面  
	![bt2](Picture/ft232_2.jpg)

* 12V 2A電源供應器:120NTD/個  

* ST-30 步進馬達 X2。260NTD/個；圓盤是跟實驗室借的，木板額外請人裁切  
	![motor](Picture/motor.jpg)

* ATmega328P裡的[程式] (Code/)  

* [手機APP](APP/version1.0.0.apk):與Station上的藍芽模組溝通  
	![app](Picture/app.jpg)