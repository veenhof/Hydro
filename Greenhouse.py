import RPi.GPIO as GPIO
import Adafruit_DHT
import time

##################################################################
##################### CUSTOMIZEABLE SETTINGS #####################
##################################################################
SETTINGS = {
    "LIGHT_GPIO":       17,                     # GPIO Number (BCM) for the Relay
#    "LIGHT_FROM":       10,                     # from which time the light can be turned on (hour)
#    "LIGHT_UNTIL":      20,                     # until which time (hour)
#    "LIGHT_CHANNEL":    0,                      # of MCP3008
#    "LIGHT_THRESHOLD":  500,                    # if the analog Threshold is below any of those, the light will turn on
    "DHT_GPIO":         27,                     # GPIO Number (BCM) of the DHT Sensor
    "DHT_SENSOR":       Adafruit_DHT.DHT22,     # DHT11 or DHT22
    "TEMP_THRESHOLD":   23.0,                   # in Celcius. Above this value, the window will be opened by the servo
#    "SERVO_GPIO":       22,                     # GPIO Number (BCM), which opens the window
    "FAN_GPIO":         ??,                        # degree, how much the servo will open the window
    "PLANTS": [
        {
            "NAME":                 "Aardbeien",
            "PH_LOW_THRESHOLD":    5.3,
            "PH_HIGH_THRESHOLD":   6.5,        # if the average analog value of all sensors is above of this threshold, the Pump will turn on
            "PH_MIN_PUMP_GPIO":      23,         # GPIO Number (BCM) for the Relais
            "PH_PLUS_PUMP_GPIO":        10,         # Seconds, how long the pump should be turned on
            "FEEDING_A_PUMP_GPIO":      23,         # GPIO Number (BCM) for the Relais
            "FEEDING_B_PUMP_GPIO":        10,         # Seconds, how long the pump should be turned on

        },
        {
            "NAME":                 "Salat",
            "MOISTURE_CHANNELS":    [3, 4],
            "MOISTURE_THRESHOLD":   450,
            "WATER_PUMP_GPIO":      24,
            "WATERING_TIME":        12,
        },
    ]
}

#26 = Relay 7 =
#19 = Relay 5 =
#13 = Relay 6 =
#06 = Relay 8 =
#12 = Relay 3 =
#16 = Relay 4 =
#20 = Relay 1 =
#21 = Relay 2 =
##################################################################
################# END OF CUSTOMIZEABLE SETTINGS ##################
##################################################################

#WHAT IS THE TIME?

def readTime():
   # try:
   #     ds1307 = SDL_DS1307.SDL_DS1307(1, 0x68)
   #     return ds1307.read_datetime()
   # except:
        # alternative: return the system-time:
        return datetime.datetime.utcnow()


def checkWindow():
    # read remperature
    humidity, temperature = Adafruit_DHT.read_retry(SETTINGS["DHT_SENSOR"], SETTINGS["DHT_GPIO"])

    GPIO.setup(SETTINGS["FAN_GPIO"], GPIO.OUT)
    pwm = GPIO.PWM(SETTINGS["FAN_GPIO"], 50)

    if temperature > SETTINGS["TEMP_THRESHOLD"]:
        # FAN AANZETTEN
#        angle = float(SETTINGS["SERVO_OPEN_ANGLE"]) / 20.0 + 2.5
#        pwm.start(angle)
    else:

        # close window
        pwm.start(2.5)
    # save current
    time.sleep(2)
    pwm.ChangeDutyCycle(0)
