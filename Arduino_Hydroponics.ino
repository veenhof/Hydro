/********************************************************************/
// First we include the libraries
#include <OneWire.h>
#include <DallasTemperature.h>
#include "DHT.h"
#include <EEPROM.h>
#include <GravityTDS.h>
/********************************************************************/
//sensors ATM
//1. PH  pin A2
//2. DHT pin D7       5v
//3. Waterflow sensor D2    5v
//4. WaterTemp sensor D3
//5. TDS Sensor A1
//6. 

#define ONE_WIRE_BUS 3        //WaterTemp sensor  D3
#define SensorPin A2          //pH meter Analog output to Arduino Analog Input 2
#define DHTPIN 7     // what digital pin we're connected to
#define TdsSensorPin A1   // TDS Sensor output on A1
#define Offset 0.08           //deviation compensate
#define LED 13
#define samplingInterval 20
#define printInterval 800
#define ArrayLenth  40    //times of collection
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
int pHArrayIndex=0;
OneWire oneWire(3);
DallasTemperature sensors(&oneWire);
DHT dht(DHTPIN, DHTTYPE);
GravityTDS gravityTds;
byte statusLed    = 13;
byte sensorInterrupt = 0;  // 0 = digital pin 2
byte sensorPin       = 2;

// The hall-effect flow sensor outputs approximately 4.5 pulses per second per
// litre/minute of flow.
float calibrationFactor = 4.5;
volatile byte pulseCount;  
float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;
unsigned long oldTime;

float temperature = 25,tdsValue = 0;  //Temp for TDS


void setup(void) {
  pinMode(LED,OUTPUT);
  Serial.begin(9600);
  sensors.requestTemperatures(); // Send the command to get temperature readings
  dht.begin();
    
// Waterflow sensor code
 // Set up the status LED line as an output
  pinMode(statusLed, OUTPUT);
  digitalWrite(statusLed, HIGH);  // We have an active-low LED attached
  
  pinMode(sensorPin, INPUT);
  digitalWrite(sensorPin, HIGH);

  pulseCount        = 0;
  flowRate          = 0.0;
  flowMilliLitres   = 0;
  totalMilliLitres  = 0;
  oldTime           = 0;

  attachInterrupt(sensorInterrupt, pulseCounter, FALLING);

//TDS
    gravityTds.setPin(TdsSensorPin);
    gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
    gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
    gravityTds.begin();  //initialization
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

        if(millis() - printTime > printInterval) {
        delay(1000);
        Serial.println();  
        Serial.print("Voltage:   ");
        Serial.print(voltage,2);
        delay(1000);
        Serial.println();
        delay(1000);
        Serial.print("pH:   ");
        Serial.println(pHValue,2);
        
        digitalWrite(LED,digitalRead(LED)^1);
        printTime=millis();

        }
//TDS sensor
 temperature = DallasTemperature.readTemperature();  //add your temperature sensor and read it
 //value, that is: TDS = EC / 2
    Serial.println();
    gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
    gravityTds.update();  //sample and calculate 
    tdsValue = gravityTds.getTdsValue();  // then get the value
    Serial.print("PPM : ");
    Serial.print(tdsValue,0);
    Serial.println(); 
     
  delay(1000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  delay(1000);
  Serial.print("Humidity:   ");
  Serial.print(h);

  delay(1000);
  Serial.println();
  Serial.print("Air_Temperature:   ");
  Serial.print(t,2);
  Serial.print(f);
  Serial.println();
  Serial.println();
  
  //DS18b20 Watertemp sensor
  sensors.requestTemperatures();
  Serial.print("Celsius temperature: ");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.println();
  
    if((millis() - oldTime) > 1000)
   {
// Disable the interrupt while calculating flow rate and sending the value to
    // the host
    detachInterrupt(sensorInterrupt);
        

    flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
    
    oldTime = millis();
    
    flowMilliLitres = (flowRate / 60) * 1000;
    
    // Add the millilitres passed in this second to the cumulative total
    totalMilliLitres += flowMilliLitres;
      
    unsigned int frac;
    
    // Print the F for this second in litres / minute
    delay(1000);
    Serial.println();
    Serial.print("Flow_rate:   ");
    Serial.print(int(flowRate));  // Print the integer part of the variable
    Serial.print("  L/min");
    Serial.print("\t");       // Print tab space

    // Reset the pulse counter so we can start incrementing again
    pulseCount = 0;
    
    // Enable the interrupt again now that we've finished sending output
    attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
  }
delay (10000); //10sec sleep
}

void pulseCounter()
{
  // Increment the pulse counter
  pulseCount++;
}
