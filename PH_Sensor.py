import time
import automationhat

from gpiozero import MCP3008
adc = MCP3008(channel=0)
adc_ref = 3.3
voltage = adc_ref * adc.value
print("channel 0 voltage is: ", voltage)

while True:
    try:
        # Read sensor value
        sensor_value = MCP3008(channel=0).read()

        # Calculate PH
        ph = 7 - 1000 * (float)(sensor_value) * adc_ref / 59.16 / 1023

        print("sensor_value =", sensor_value, " ph =", ph)
        time.sleep(10)
    except IOError:
        print ("Error")


###
#onderstaande is voor automationhat

# Connect the Grove PH Sensor to analog port A0
# SIG,NC,VCC,GND
#sensor = automationhat.analog.one.read()
#print(value)

#time.sleep(1)

# Reference voltage of ADC is 5v
#adc_ref = 5

#while True:
#    try:
        # Read sensor value
 #       sensor_value = automationhat.analog.one.read()

        # Calculate PH
#        ph = 7 - 1000 * (float)(sensor_value) * adc_ref / 59.16 / 1023

        print("sensor_value =", sensor_value, " ph =", ph)
        time.sleep(10)
    except IOError:
        print ("Error")
