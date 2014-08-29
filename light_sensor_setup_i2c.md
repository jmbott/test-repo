# Setup for Pyranometer I2C Chip

* Configure I2C on the Pi
 * Edit `/etc/modules`
 ```
sudo nano /etc/modules
```
 * Add the following lines at the end of the opened file,
 ```
i2c-bcm2708
i2c-dev
```
 * Reboot so changes can take effect,
 ```
sudo reboot
```
 * Log back in. 
 * If you have problems with I2C consider updating your version of Raspbian
 * Install the i2c-tools utility,
 ```
sudo apt-get install python-smbus
sudo apt-get install i2c-tools
```
 * Check if you have a `/etc/modprobe.d/raspi-blacklist.conf` file. If not skip the next step.
  * If you have said file open it, 
  ```
sudo nano /etc/modprobe.d/raspi-blacklist.conf
```
  * Add a # in front of `blacklist spi-bcm2708` and `blacklist i2c-bcm2708`
 * Then reboot again,
 ```
sudo reboot
```
 * Log back in and check the connected devices with the following line,
 ```
sudo i2cdetect -y 1
```
  * If this does not work try `sudo i2cdetect -y 0`
 * You should see a grid of numbers, those that are not zero are the I2C addresses in use. 