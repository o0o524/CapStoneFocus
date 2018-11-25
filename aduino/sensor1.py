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

		humidity, temperature = Adafruit_DHT.read_retry(Temp_Sensor, 25)
		if humidity is not None and temperature is not None:
			print "Temp={0:0.1f}*C Humidity={1:0.1f}%".format(temperature, humidity)
		else:
			print "Failed to get Temperature."

		time.sleep(1)

		if GPIO.input(18) == 0:

			print "DETECT KIULKI"
			time.sleep(1)

		if GPIO.input(23) == 0:

                        print "DETECT FIRE"
			time.sleep(1)

 		if GPIO.input(24) == 1:

                        print "DETECT JINDONG"
                        time.sleep(1)


except KeyboardInterrupt:
	GPIO.cleanup()

