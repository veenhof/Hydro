//#include <ECSalinity.h>

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

// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS); 
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
/********************************************************************/ 

void setup(void)
{
  pinMode(LED,OUTPUT);  
  Serial.begin(9600);  
//Serial.println("pH meter experiment!");    //Test the serial monitor
//  Serial.print(" Requesting temperatures..."); 
  sensors.requestTemperatures(); // Send the command to get temperature readings 
  //Serial.println("DONE"); 
}
void loop(void)
{
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue,voltage;
  if(millis()-samplingTime > samplingInterval)
  {
      pHArray[pHArrayIndex++]=analogRead(SensorPin);
      if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
      voltage = avergearray(pHArray, ArrayLenth)*5.0/1024;
      pHValue = 3.5*voltage+Offset;
      samplingTime=millis();
  }
  
 float Celcius=0;
 float Fahrenheit=0;

sensors.requestTemperatures(); 
  Celcius=sensors.getTempCByIndex(0);
  Fahrenheit=sensors.toFahrenheit(Celcius);
 
 
  if(millis() - printTime > printInterval)   //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
  {
  Serial.print("Voltage");
        Serial.print(voltage,2);
        Serial.print("pH");
  Serial.println(pH,2);
        digitalWrite(LED,digitalRead(LED)^1);
        printTime=millis();
        Serial.print(Temperature,2); 
        Serial.print(Celcius);
   
  //  Serial.print(" C  ");
  
  //Serial.print(" F  ");
  //Serial.println(Fahrenheit);
  delay(1000); // Why "byIndex"?  
   // You can have more than one DS18B20 on the same bus.  
   // 0 refers to the first IC on the wire 
 // loop through and take continous measurements
  /*
  ec.measureEC();
  Serial.print("mS/cm: ");
  Serial.println(ec.mS);
  Serial.print("TDS: ");
  Serial.println(ec.PPM_500);
  Serial.println("-----");
  delay(1000); 
        delay(1000); 
        
  */      
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
