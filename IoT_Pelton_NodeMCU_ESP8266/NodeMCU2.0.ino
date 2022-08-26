#define BLYNK_TEMPLATE_ID "TMPLboCpe63N"
#define BLYNK_DEVICE_NAME "IOT"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
#include<SoftwareSerial.h>
SoftwareSerial mySerial (D1,D2); //Rx,Tx
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI
int slider;

#include "BlynkEdgent.h"
int ledpin=14;
BLYNK_WRITE(V10){
  int pinvalue =param.asInt();
  digitalWrite(ledpin,pinvalue);  
}

BLYNK_WRITE(V8){
  int pinvalue =param.asInt();
    slider =pinvalue;
}

void setup()
{
  pinMode(14,OUTPUT) ; 
  Serial.begin(9600);  
  mySerial.begin(9600);

  pinMode(ledpin,OUTPUT);
  BlynkEdgent.begin();
}


void loop(){
  BlynkEdgent.run();
  String pot =mySerial.readStringUntil(';');
  String diff =mySerial.readStringUntil(';');
  String flow =mySerial.readStringUntil(';');
  String p1 =mySerial.readStringUntil(';');
  String rpm =mySerial.readStringUntil(';');
  String eff =mySerial.readStringUntil('\r');
  int effe = eff.toInt();
  float final_eff = effe*((slider*9.81)+14.715)*0.231;
  
  Serial.println(pot);
  Serial.println(diff);
  Serial.println(flow);
  Serial.println(p1);
  Serial.println(rpm);
  Serial.println(final_eff);

 
  int pot1 = pot.toInt();
  int diff1 = diff.toInt();
  int flow1 = flow.toInt();
  int p11 = p1.toInt();
  int rpm1 = rpm.toInt();
  


  Blynk.virtualWrite(V3, pot1);
  Blynk.virtualWrite(V5, diff1);
  Blynk.virtualWrite(V6, flow1);
  Blynk.virtualWrite(V7, p11);
  Blynk.virtualWrite(V4, rpm1);
  
  if(final_eff<=100 and final_eff>=0){
  Blynk.virtualWrite(V9, final_eff);
  }
  else{
  Blynk.virtualWrite(V9, 0);  
  }


}
