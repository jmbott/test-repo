import time
import picamera
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM)
GPIO.setup(23, GPIO.IN)
GPIO.setup(18, GPIO.OUT)

GPIO.output(18, False)

while True:
    if(GPIO.input(23) == 1):
        print "motion"
        GPIO.output(18, True)
        with picamera.PiCamera() as camera:
            # Turn the camera's LED off
            camera.led = False
            # Take video
            camera.resolution = (1280, 720)
            filename = 'video%02d.h264' % i
            camera.start_recording(filename)
            while(GPIO.input(23) == 1):
                camera.wait_recording(5)
            camera.stop_recording()
            i = i + 1
    elif(GPIO.input(23) == 0):
        print "no motion"
        GPIO.output(18, False)

#
#
# import time
# import picamera
# import RPi.GPIO as GPIO
#
# GPIO.setmode(GPIO.BCM)
# GPIO.setup(23, GPIO.IN)
# GPIO.setup(18, GPIO.OUT)
#
# while True:
#   if(GPIO.input(23) == 1):
#     print "motion"
#     GPIO.output(18, True)
#   elif(GPIO.input(23) == 0):
#     print "no motion"
#     GPIO.output(18, False)
#
#
