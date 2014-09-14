# Pi Bluetooth Speaker Instructions

## Upgrade and install bluez

```
sudo apt-get upgrade
sudo apt-get install bluez pulseaudio-module-bluetooth python-gobject python-gobject-2 bluez-tools
```

## Configure Environment

* Add Pi user to pulse audio group

```
sudo usermod -a -G lp pi
```

* Enable A2DP

```
sudo nano /etc/bluetooth/audio.conf
```

 * In the text editor add the following line under `[General]`

 ```
Enable=Source,Sink,Media,Socket
```

 * Save and exit, `ctrl-o`, `enter`, `ctrl-x`

* Modify pulse daemon config file

 ```
sudo nano /etc/pulse/daemon.conf
```
 
 * Add a `;` in front of the line `resample-method = speex-float-3` if it is not there already
 * Add `resample-method = trivial` after edited line

* Rename bluetooth device
 
 ```
 sudo nano /etc/bluetooth/main.conf
```

 * Edit `Name =` to your prefered name
 * Change the device's Class parameter `Class 0x20041C` or `Class 0x64041c`
 
 * Next modify config of specific device
  * Find the MAC address `hciconfig` under BD Address

  ```
sudo nano /var/lib/bluetooth/<bluetooth mac address>/config
```

  * Edit the `name` and `class`
  * Save and Exit

## Setup a script that runs when Bluetooth connects

```
sudo nano /etc/udev/rules.d/99-input.rules
```

* Underneath the line of the form `SUBSYSTEM=="input", GROUP="input", MODE="0660"` add the following,

```
KERNEL=="input[0-9]*", RUN+="/usr/lib/udev/bluetooth"
```

* Save and exit
* Check that `udev/` directory exists

```
sudo ls -la /usr/lib/udev
```

* If it doesnt exist create it

```
mkdir /usr/lib/udev/bluetooth
```

* Edit it

```
sudo nano /usr/lib/udev/bluetooth
```

* Add the following:

```
#!/bin/bash
#change if you don't use default analog audio out.
#THIS DIDN'T WORK FOR MY PI SO I ADDED A amixer COMMAND BELOW
AUDIOSINK="alsa_output.platform-bcm2835_AUD0.0.analog-stereo"
echo "Executing bluetooth script...|$ACTION|" >> /var/log/bluetooth_dev

ACTION=$(expr "$ACTION" : "\([a-zA-Z]\+\).*")
if [ "$ACTION" = "add" ]
then

# Turn off BT discover mode before connecting existing BT device to audio
hciconfig hci0 noscan

# set the audio output to the analog
# COMMENT THIS LINE OUT IF YOU WANT TO OUTPUT AUDIO THROUGH HDMI
amixer cset numid=3 1

# Set volume level to 100 percent
amixer set Master 100%
pacmd set-sink-volume 0 65537

   for dev in $(find /sys/devices/virtual/input/ -name input*)
   do
      if [ -f "$dev/name" ]
      then
         mac=$(cat "$dev/name" | sed 's/:/_/g')
         bluez_dev=bluez_source.$mac

         sleep 1

         CONFIRM=`sudo -u pi pactl list short | grep $bluez_dev`
         if [ ! -z "$CONFIRM" ]
         then
            echo "Setting bluez_source to:  $bluez_dev" >> /var/log/bluetooth_dev
            echo pactl load-module module-loopback source=$bluez_dev sink=$AUDIOSINK rate=44100 adjust_time=0 >> /var/log/bluetooth_dev
            sudo -u pi pactl load-module module-loopback source=$bluez_dev sink=$AUDIOSINK rate=44100 adjust_time=0 >> /var/log/bluetooth_dev
         fi
      fi
   done
fi

if [ "$ACTION" = "remove" ]
then
# Turn on bluetooth discovery if device disconnects
sudo hciconfig hci0 piscan
fi
```

* Save and exit
* Make the file executable

```
sudo chmod 774 /usr/lib/udev/bluetooth
```

# Automate Bluetooth connection

* Create init script

```
sudo nano /etc/init.d/bluetooth-agent
```

* Add the following

```
### BEGIN INIT INFO
# Provides: bluetooth-agent
# Required-Start: $remote_fs $syslog bluetooth pulseaudio
# Required-Stop: $remote_fs $syslog
# Default-Start: 2 3 4 5
# Default-Stop: 0 1 6
# Short-Description: Makes Bluetooth discoverable and connectable to 0000
# Description: Start Bluetooth-Agent at boot time.
### END INIT INFO
#! /bin/sh
# /etc/init.d/bluetooth-agent
USER=root
HOME=/root
export USER HOME
case "$1" in
start)
echo "setting bluetooth discoverable"
sudo hciconfig hci0 piscan
start-stop-daemon -S -x /usr/bin/bluetooth-agent -c pi -b -- 0000
echo "bluetooth-agent startet pw: 0000"
;;
stop)
echo "Stopping bluetooth-agent"
start-stop-daemon -K -x /usr/bin/bluetooth-agent
;;
*)
echo "Usage: /etc/init.d/bluetooth-agent {start|stop}"
exit 1
;;
esac
exit 0
```

* Save and Exit
* Make the script executable and add it to startup list

```
sudo chmod 755 /etc/init.d/bluetooth-agent
sudo update-rc.d bluetooth-agent defaults
```

## Configure auto-login

* Edit inittab

```
sudo nano /etc/inittab
```

* Comment out the line `1:2345:respawn:/sbin/getty 115200 tty1` by adding a `#` in front of it
* Add the following below,

```
1:2345:respawn:/bin/login -f pi tty1 </dev/tty1 >/dev/tty1 2>&1
```

* Save and exit nano, then reboot Pi

```
sudo reboot
```

* Try it all out








