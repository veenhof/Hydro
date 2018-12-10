#The Circuits
#
#http://www.davidhunt.ie/water-droplet-photography-with-raspberry-pi/
#
#There’s a couple of (very) simple circuits to build, one for the solenoid, and one for the shutter release of the camera.  In both cases, a 1K resistor should be fine.
#
#First, the solenoid (revised after feedback to move the solenoid) (revised again to add the flywheel diode to protect the transistor against the inductive spike from the solenoid):
#
#!/usr/bin/env python
import wiringpi
from time import sleep
gpio = wiringpi.GPIO(wiringpi.GPIO.WPI_MODE_GPIO)  
shutterpin = 17
solenoidpin = 18
gpio.pinMode(shutterpin,gpio.OUTPUT)  
gpio.pinMode(solenoidpin,gpio.OUTPUT)
wiringpi.pinMode(shutterpin,1)
wiringpi.pinMode(solenoidpin,1)

gpio.digitalWrite(solenoidpin,gpio.HIGH)
sleep(0.06)
gpio.digitalWrite(solenoidpin,gpio.LOW)

sleep(0.1)

gpio.digitalWrite(solenoidpin,gpio.HIGH)
sleep(0.05)
gpio.digitalWrite(solenoidpin,gpio.LOW)

sleep(0.12)
gpio.digitalWrite(shutterpin,gpio.HIGH)
sleep(0.1)
gpio.digitalWrite(shutterpin,gpio.LOW)
