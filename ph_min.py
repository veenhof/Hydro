#!/usr/bin/python
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)

# init list with pin numbers

#Some Info
#GPIO | Relay   |   Function   5V  / 12V Relais
#---------------|
#17    1        | 1ste pomp PH -
#27    2        | 2de  Pomp PH +
#22    3        | 2x Feeding Pumps
#25    4        | Waterpomp MAIN
#24    5        | Waterpomp naar Koelvat
#23    6        | Fans "In & Uit"
#NVT   7        |
#NVT   8        |
#
#GPIO | Relay   |   Function  220V RELAIS!
#---------------|
#21      1      |
#20      2      | Cyclops Watermenger
#16      3      | COB LEDJES
#NVT     4      |


pinList = [17]

# loop through pins and set mode and state to 'low'

for i in pinList:
  GPIO.setup(i, GPIO.OUT)
  GPIO.output(i, GPIO.HIGH)

# time to sleep between operations in the main loop

SleepTimeL = 2 # 2 sec

# main loop

try:
  GPIO.output(17, GPIO.LOW)
  time.sleep(SleepTimeL);
#  GPIO.output(27, GPIO.LOW)
#  print("TWO")
#  time.sleep(SleepTimeL);
  GPIO.cleanup()

# End program cleanly with keyboard
except KeyboardInterrupt:
  print(" Quit")

 # Reset GPIO settings
  GPIO.cleanup()
