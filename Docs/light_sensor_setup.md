# ReadMe file for Pyranometer setup

## Enable Hardware SPI on Pi
```
sudo nano /etc/modprobe.d/raspi-blacklist.conf
```
- Add # in front of spi-bcm2708
- save & reboot
```
sudo reboot
```
- After reboot check that changes took effect;
```
lsmod
```
- You should see spi_bcm2708 in the output

## Install Python SPI Wrapper (py-spidev and python-dev)
```
sudo apt-get install python2.7-dev
mkdir py-spidev
cd py-spidev
wget https://raw.github.com/doceme/py-spidev/master/setup.py
wget https://raw.github.com/doceme/py-spidev/master/spidev_module.c
sudo python setup.py install
```

## Wiring Setup w/Hardware SPI on Pi and MCP3008 Chip
```
VDD   -  	3.3V
VREF  -   3.3V
AGND  -   GND
CLK		-   SCLK
DOUT  -   MISO
DIN   -	  MOSI
CS 		-	  CE0
DGND     -  	GND
```

## Wiring Setup Apogee Pyranometer to the MCP3008 Chip
```
Clear Wire	 -	GND
Black Wire	 -	Negative Signal (GND)
Red Wire	   -	Positive Signal (CH0)
```
