/*
 # This sample code is used to test the pH meter V1.1.
 # Editor : YouYou
 # Date   : 2014.06.23
 # Ver    : 1.1
 # Product: analog pH meter V1.1
 # SKU    : SEN0161
*/
/********************************************************************/
// First we include the libraries
#include <OneWire.h>
#include <DallasTemperature.h>
#include "DHT.h"
/********************************************************************/

#define DHTPIN 7     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

DHT dht(DHTPIN, DHTTYPE);

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
DHT dht(DHTPIN, DHTTYPE);

void setup(void)
{
  dht.begin();
  pinMode(LED,OUTPUT);
  Serial.begin(9600);
  sensors.requestTemperatures(); // Send the command to get temperature readings
}
void loop(void)
{     //begin of dht22
   float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidity: ");
  Serial.print("  ");
  Serial.print(h);
  Serial.print("  ");
  Serial.print("Temperature: ");
  Serial.print("  ");
  Serial.print(t);
  Serial.print("  ");
  Serial.print(f);
  Serial.print("  ");
  Serial.print("Heat index: ");
  Serial.print("  ");
  Serial.print(hic);
  Serial.print("  ");
  Serial.print(hif);
  Serial.println("  ");
}
//end for DHT
{^//begin voor PH sensor
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue,voltage;
  if(millis()-samplingTime > samplingInterval)
  {
      pHArray[pHArrayIndex++]=analogRead(SensorPin);
      if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
      //voltage = avergearray(pHArray, ArrayLenth)*5.0/1024;
      pHValue = 3.5*voltage+Offset;
      samplingTime=millis();
  }
  if(millis() - printTime > printInterval)
  {
        Serial.print("Voltage:");
        Serial.print(voltage,2);
        Serial.print("pH:");
        Serial.println(pHValue,2);
        digitalWrite(LED,digitalRead(LED)^1);
        printTime=millis();
  }
}
double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;
}
// einde van PH?   geen idee
float Celcius=0;

