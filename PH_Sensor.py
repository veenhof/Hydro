root@raspberrypi:/home/pi/Pimoroni/automationhat/examples# cat ph_test.py

import time
import automationhat

# Connect the Grove PH Sensor to analog port A0
# SIG,NC,VCC,GND
sensor = automationhat.analog.one.read()
#print(value)

time.sleep(1)

# Reference voltage of ADC is 5v
adc_ref = 5

while True:
    try:
        # Read sensor value
        sensor_value = automationhat.analog.one.read()

        # Calculate PH
        ph = 7 - 1000 * (float)(sensor_value) * adc_ref / 59.16 / 1023

        print("sensor_value =", sensor_value, " ph =", ph)
        time.sleep(10)
    except IOError:
        print ("Error")
