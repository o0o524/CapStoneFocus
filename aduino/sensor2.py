import RPi.GPIO as GPIO
import time
import Adafruit_DHT

GPIO.setmode(GPIO.BCM)

GPIO.setup(18, GPIO.IN)
GPIO.setup(23, GPIO.IN)
GPIO.setup(24, GPIO.IN)

Temp_Sensor = Adafruit_DHT.DHT11

print "Test Start"


try:

        while True:

		fire = '0'
		kiulki = '0'
		jindong = '0'

                if GPIO.input(18) == 0:

                        kiulki = '1'
                        time.sleep(1)

                if GPIO.input(23) == 0:

                        fire = '1'
                        time.sleep(1)

                if GPIO.input(24) == 1:

                        jindong = '1'
                        time.sleep(1)

                humidity, temperature = Adafruit_DHT.read_retry(Temp_Sensor, 25)
                if humidity is not None and temperature is not None:
                        print fire + " " +  kiulki + " " +  jindong + " " + "{0:0.1f} {1:0.1f}".format(temperature, humidity)
                else:
                        print fire + " " +  kiulki + " " +  jindong + " " + "Failed to get Temperature."

                time.sleep(1)


except KeyboardInterrupt:
        GPIO.cleanup()


