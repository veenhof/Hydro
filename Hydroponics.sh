#!/bin/bash
#### read Sensors values from Arduino

# Onderstaande weer aanzetten als alles klaar is
#cat /dev/ttyUSB0|head -n 50|tail -n 50 > formatting.txt
#cat formatting.txt | sort |uniq -w 10 > Get_Numbers_arduino.txt

## Variables

PH=5.70         #`cat Get_Numbers_arduino.txt | grep pH| awk '{print $2}'`
PH_LOW=5.50
PH_HIGH=6.50

EC=             #`cat Get_Numbers_arduino.txt | grep ?????| awk '{print $2}'`
EC_LOW=
WATER_TEMP=
FLOW_RATE=      `cat Get_Numbers_arduino.txt | grep ?????| awk '{print $2}'`
AIR_TEMP=
AIR_HUMIDITY=
VALVE_IN=
VALVE_OUT=

## DB VARIABLES
user="root"
dbname="Hydroponics"
password="VerySecret"
#### Insert PH data in Database  ######
#mysql -u $user -D $dbname -p $password -e INSERT INTO Hydroponics
#            values(CURRENT_DATE() - INTERVAL 1 DAY, NOW(), 'kitchen', 21.7)


#### calculate with PH Floating Number

if expr $PH '<' $PH_LOW>/dev/null; then
    echo "TE LAAG!, PH+ erin aub!"

#PH+ motor aan
#Cyclone Pump aan


elif expr $PH '>' $PH_HIGH>/dev/null; then
    echo "PH te HOOG!   PH- BIJGOOIEN AUB"

#PH- motor aan
#Cyclone Pump aan

else
    echo "PH $PH is goed!"
fi
