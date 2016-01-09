# 可調天線方向之雙頻中繼器



## 簡介
運用arduino與MIT inventory製作程式，結合手機APP藉以實踐改變天線方向。


## 開發軟體
### 控制板
* [Arduino 1.6.7](https://www.arduino.cc/en/Main/Software)
* [Codeblocks Arduino IDE (Release 20140626)](http://arduinodev.com/codeblocks/)
* [EAGLE 7.4.0](http://www.cadsoftusa.com/)  
  * 使用到的元件庫:[EAGLE Library-RBBB](https://moderndevice.com/RBBB.lbr.zip)
* [MIT inventory 2](http://ai2.appinventor.mit.edu/)
### LNA控制電路
* [EAGLE 7.4.0](http://www.cadsoftusa.com/)  
  * 使用到的元件庫:[自訂元件庫](https://github.com/93i7xo2/Custom-Eagle-Library)
### LNA匹配電路
* Ansoft_HFSS_15
* CorelDraw
```
用來將hfss產生的dxf轉換成pdf
```
### 5V轉3.3V變壓器
* [EAGLE 7.4.0](http://www.cadsoftusa.com/)  
  * 使用到的元件庫:[自訂元件庫](https://github.com/93i7xo2/Custom-Eagle-Library)

## 展示
### 控制板
* 使用雙玻版。[佈線圖](Layout/main/schPic.png)、[PCB-TOP Layer](Layout/main/top.pdf)、 [PCB-Bottom Layer](Layout/main/bottom.pdf)  
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

### LNA控制電路
* 將LNA匹配電路上的四個LNA腳為拉出來，加上供電腳位、1MHz震盪頻率產生器
* 使用雙玻版。[佈線圖](Layout/LNA控制電路/schPic.png)、[PCB-TOP Layer](Layout/LNA控制電路/top.pdf)、 [PCB-Bottom Layer](Layout/LNA控制電路/bottom.pdf) 
    * 正面  
    * 反面  

### LNA匹配電路
* 使用雙玻版，[電路](Layout/LNA匹配電路/匹配電路.pdf)
    * 正面  
    * 反面  

### 5V轉3.3V變壓器
* 使用雙玻版，[電路](Layout/5Vto3V3_VoltageConverter/psu_sch.png)、[PCB-TOP Layer](Layout/5Vto3V3_VoltageConverter/top.pdf)、 [PCB-Bottom Layer](Layout/5Vto3V3_VoltageConverter/bottom.pdf) 
* LDO晶片:RT9187GSV   

## 上電成果
Failed，結果跟小專的時候一樣:DET固定出來XXHz/0.3V的方波，理論上應該隨著訊號源遠近，DET出來的電壓有所波動。懷疑是LNA焊接時溫度過高損毀。
展示時就說四周都有2.4G訊號源，馬達轉不到固定的位置好惹= =

## 致謝
