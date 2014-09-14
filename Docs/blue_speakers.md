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
