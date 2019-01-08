/********************************************************************/
// First we include the libraries
#include <OneWire.h>
#include <DallasTemperature.h>
#include "DHT.h"
/********************************************************************/
// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2        //Temp sensor D2
#define SensorPin A0          //pH meter Analog output to Arduino Analog Input 2
#define Offset 0.08           //deviation compensate
#define LED 13
#define samplingInterval 20
#define printInterval 800
#define ArrayLenth  40    //times of collection
int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
int pHArrayIndex=0;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

#define DHTPIN 7     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);

void setup(void) {
  pinMode(LED,OUTPUT);
  Serial.begin(9600);
  sensors.requestTemperatures(); // Send the command to get temperature readings
  dht.begin();
}

void loop(void)  {

  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue,voltage;
  if(millis()-samplingTime > samplingInterval)

      pHArray[pHArrayIndex++]=analogRead(SensorPin);
      if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
      //voltage = avergearray(pHArray, ArrayLenth)*5.0/1024;
      pHValue = 3.5*voltage+Offset;
      samplingTime=millis();

        if(millis() - printTime > printInterval)        {
  //      Serial.print("Voltage:");
        Serial.print(voltage,2);
        Serial.println();
        Serial.print("pH:");
        Serial.println(pHValue,2);
        digitalWrite(LED,digitalRead(LED)^1);
        printTime=millis();


  delay(200);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidity:");
  Serial.print(h);

  Serial.println();
  Serial.print("Temperature:");
  Serial.print(t,2);
  Serial.print(f);
  //Serial.println();
  
   }
}
