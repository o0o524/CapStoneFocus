import picamera
import time

with picamera.PiCamera() as picam:

	picam.start_preview()
	time.sleep(5)
	picam.capture('Home.jpg')
	picam.stop_preview()
	picam.close()

