//Time Module
//Relay Module
//DHT22

#include <MyRealTimeClock.h>
#include "DHT.h"
#include <OneWire.h> 
#include <DallasTemperature.h>
/********************************************************************/
#define DHTPIN 4     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
#define ONE_WIRE_BUS 2 // ds18b20   water temperature
#define Relay_One 11
#define Relay_Two 12

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

MyRealTimeClock myRTC(6, 7, 8); // Assign Digital Pins 

int maxHum = 70;
int maxTemp = 30;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(Relay_One, OUTPUT);
  Serial.begin(9600); 
  dht.begin();
  sensors.begin(); 

/* To set the current time and date in specific format 
| Second 00 | Minute 59 | Hour 10 | Day 12 |  Month 07 | Year 2015 |
*/

myRTC.setDS1302Time(00, 05, 00, 28, 01, 07, 2019);
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;

//TIMEZZ

// Allow the update of variables for time / accessing the individual element. 
myRTC.updateTime();

Serial.print("Current Date / Time: "); 
Serial.print(myRTC.dayofmonth); // Element 1
Serial.print("/"); 
Serial.print(myRTC.month); // Element 2
Serial.print("/");
Serial.print(myRTC.year); // Element 3
Serial.print(" ");
Serial.print(myRTC.hours); // Element 4
Serial.print(":");
Serial.print(myRTC.minutes); // Element 5
Serial.print(":");
Serial.println(myRTC.seconds); // Element 6
delay( 5000);
 
  //ds18b20
//   Serial.print(" Requesting temperatures..."); 
// sensors.requestTemperatures(); // Send the command to get temperature readings 
// Serial.println("DONE"); 
/********************************************************************/
// Serial.print("Temperature is: "); 
// Serial.print(sensors.getTempCByIndex(0)); // Why "byIndex"?  
//   // You can have more than one DS18B20 on the same bus.  
   // 0 refers to the first IC on the wire 
//   delay(1000); 
  }
 
  if(h > maxHum || t > maxTemp) {
      digitalWrite(Relay_One, HIGH);
      Serial.print("Relay aan, temp of Humidity hoger dan gewild");
      Serial.println("");
  } else {
     digitalWrite(Relay_One, LOW); 
  }


  Serial.print(sensors.getTempCByIndex(0));  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.println(" *C ");

}
