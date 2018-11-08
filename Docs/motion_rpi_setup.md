sudo apt-get install motion

sudo nano /etc/motion/motion.conf

  width 640
  height 480
  threshold 3000
  framerate 1
  quality = 100
  ffmpeg_video_codec mpeg4
  daemon on (allows motion to run as a service)
  webcam_localhost off (allows you to connect to live webcam feed using browser)
  webcam_port 8081
  control_localhost off (allows you to connect to remote control via localhost)

sudo service motion restart

sudo nano /etc/default/motion

  start_motion_daemon=yes

sudo service motion start

example config file:
https://www.raspberrypi.org/forums/viewtopic.php?f=43&t=44966&start=350
https://embeddedday.com/projects/raspberry-pi/a-step-further/install-motion-mmal/

https://www.raspberrypi.org/forums/viewtopic.php?f=43&t=44966&start=100

installing:
http://www.opsactive.com/install-motion-on-a-raspberry-pi/
http://www.codeproject.com/Articles/665518/Raspberry-Pi-as-low-cost-HD-surveillance-camera
https://medium.com/@Cvrsor/how-to-make-a-diy-home-alarm-system-with-a-raspberry-pi-and-a-webcam-2d5a2d61da3d#.pdqsh3cf4
https://www.maketecheasier.com/raspberry-pi-as-surveillance-camera/

https://www.dropbox.com/s/xdfcxm5hu71s97d/motion-mmal.tar.gz
