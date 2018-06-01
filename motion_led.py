import time
import picamera
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM)
GPIO.setup(23, GPIO.IN)
GPIO.setup(18, GPIO.OUT)

while True:
  if(GPIO.input(23) == 1):
    print "motion"
    GPIO.output(18, True)
  elif(GPIO.input(23) == 0):
    print "no motion"
    GPIO.output(18, False)
