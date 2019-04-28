import time
from time import sleep
# import automationhat
from gpiozero import MCP3008

adc = MCP3008(channel=0)
adc_ref = 3.3
voltage = adc_ref * adc.value
f = open('output.txt',"w")

# print("channel 0 voltage is: ", voltage)
while True:
    try:
        # Read sensor value
        sensor_value = MCP3008(channel=0)
        # Calculate PH
        ph = 7 - 1000 * (float)(voltage) * adc_ref / 59.16 / 1023
        s = str(ph)
        f.write(s)
        sleep(10)
        break
    except ValueError:
        print "Oops!  That was not a valid number. Try again..."
    finally:
        print 'all done, bye'
