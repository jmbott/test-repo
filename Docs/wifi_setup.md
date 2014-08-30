# Instructions on how to setup wifi on a Pi

* Install Wicd-curses
```
sudo apt-get update
sudo apt-get install wicd-curses
```
* Open Wicd-curses
```
sudo wicd-curses
```
 * A list of found wireless networks will be displayed.
 
  i). If your WiFi dongle is not recognized, when you enter Wicd-curses `sudo wicd-curses`

  ii). Press P (meaning Preferences)

  iii). enter `wlan0` in the wireless interface field.

  iv). Press `F10` to save (Hint: You may have to use the `fn` key to avoid simply changing the volume)

  v). Back on the main screen press `R` to refresh and you should be connected
  
 * Use the arrow keys to select your wifi network
 * Press the right arrow key to edit its properties
 * Insert the WEP or WPA KEY and check auto connection
 * Press `F10` to save and your Pi should connect (Hint: You may have to use the `fn` key to avoid simply changing the volume)
 * Press `Q` to Exit and reboot
```
sudo reboot
```
