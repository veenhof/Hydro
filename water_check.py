#!/usr/bin/env python

import time
import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BCM)

Low = 23
High = 16
Solenoid =27

GPIO.setup(Low, GPIO.OUT)
GPIO.setup(High, GPIO.OUT)
GPIO.setup(Solenoid, GPIO.OUT) # Solenoid Valve

GPIO.output(Solenoid, GPIO.LOW) # Solenoid Valve
GPIO.output(Low, GPIO.LOW)
GPIO.output(High, GPIO.LOW)

while True:
    if low_is_on == 1:
        print("low watersensor is ON")
        #GPIO.output(Solenoid, GPIO.HIGH)
        time.sleep(5)
        continue
    else:
        print("low watersensor is OFF")
        time.sleep(5)
        continue

while True:
    if high_is_on == 1:
        print("high watersensor is ON")
        time.sleep(5)
    else:
        print("high watersensor is OFF")
        time.sleep(5)

GPIO.cleanup()
