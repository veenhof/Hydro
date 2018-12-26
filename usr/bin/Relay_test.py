#!/usr/bin/python
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)

GPIO | Relay
#--------------
#24   1
#23   2 
#18   3      
#22   4   
#27   5
#17   6
#25   7
#11   8

# initiate list with pin gpio pin numbers

gpioList = [24, 23, 18, 22, 27, 17, 25, 11]

for i in gpioList:
    GPIO.setup(i, GPIO.OUT)
    GPIO.output(i, GPIO.HIGH)

# Sleep time variables

sleepTimeShort = 0.2
sleepTimeLong = 0.1

# MAIN LOOP =====
# ===============

try:
    while True:
        for i in gpioList:
            GPIO.output(i, GPIO.LOW)
            time.sleep(sleepTimeShort);
            GPIO.output(i, GPIO.HIGH)
            time.sleep(sleepTimeLong);


# End program cleanly with keyboard
except KeyboardInterrupt:
    print " Quit"

    # Reset GPIO settings

    GPIO.cleanup()
