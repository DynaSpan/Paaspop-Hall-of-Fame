# @author Milan Drossaerts (m.drossaerts@gmail.com)
#
# Python script for Raspberry Pi for Paaspop '10 seconds of fame'

import RPi.GPIO as GPIO
import time
import os

# Set the button GPIO pin, in this case GPIO pin 18 (pin 12 on layout)
# See this image for more info: http://www.raspberrypi-spy.co.uk/wp-content/uploads/2014/07/Raspberry-Pi-GPIO-Layout-Model-B-Plus.png
int buttonPin = 18;

# The GPIO pin that we use to send the start signal to the Arduino
int arduinoPin = 17;

# How long the video should be recorded (in milliseconds) (e.g. 10 seconds is 10000)
int recordTime = 10000;

# Mounts the USB stick automatically
os.system("sudo mount /dev/sda1 /mnt/exthdd")

# Set the GPIO mode
GPIO.setmode(GPIO.BCM)

# Set the button pin as input pin
GPIO.setup(buttonPin, GPIO.IN, pull_up_down=GPIO.PUD_UP)

# Set the arduino pin as output pin
GPIO.setup(arduinoPin, GPIO.OUT)

# Start a never ending loop waiting for input
while True:
	input_state = GPIO.input(buttonPin)
    
    # If the button is pressed, start recording
	if input_state == False:
    
        # Notify the Arduino
		GPIO.output(arduinoPin, 1)
        
        # Get current timestamp
		timestamp = str(time.time())
        
		GPIO.output(arduinoPin, 0)
        
        # Record the video to the USB stick for 10 seconds
		os.system("raspivid -o /mnt/exthdd/" + timestamp + ".h264 -t " + recordTime)
        
        # Format the .h264 video to .mp4
        # NOTE: this line may give some warnings about stereo sound not being present
        # This is normal because the camera doesn't record audio
		os.system("avconv -r 30 -i /mnt/exthdd/" + timestamp + ".h264 -vcodec copy /mnt/exthdd/" + timestamp + ".mp4") 
        
        # Remove the old .h264 file
		os.system("rm /mnt/exthdd/" + timestamp + ".h264")
        
		time.sleep(0.2)