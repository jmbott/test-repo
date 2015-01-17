# Burning a bootloader with an Arduino Mega 2560

* First open the Arduino environment
 * Go to File, Examples, ArduinoISP
* Select the correct Serial Port and Board for the programming arduino
 * Tools, Board, Arduino Mega 2560
 * Tools, Serial Port, /dev/tty.usbmodem* or /dev/tty.usbserial*
* Verify and Upload the ArduinoISP sketch to the programming Arduino
* Next wire the programming board to the target board as follows,

```
Mega                Slave

5V                  5V
GND                 GND
slave reset(53)     reset
MOSI(51)            MOSI
MISO(50)            MISO
SCK(52)             SCK

Also wire a 100nF Cap (104 Cap) from the mega reset to 5V
```

For reference:
```
pin name:    not-mega:         mega(1280 and 2560)
slave reset: 10:               53 
MOSI:        11:               51 
MISO:        12:               50 
SCK:         13:               52 
```

* Then select Tools, Board, (Board being programmed)

Note: The Serial Port will remain the same

* Select Tools, Programmer, Arduino as ISP
* Finally Tools, Burn Bootloader

This will take a few minutes and then your set

## Possible problems:

 1. Wiring the reset pin on the mega to the 100nF cap while trying to Upload the ArduinoISP sketch
 2. Not wireing the reset pin on the mega to the 100nF cap while attempting to burn the bootloader
 3. Using the non-mega pins while using a mega, using the mega pins while not using a mega
 4. Attempting to use the programee's Serial port
 
Note: this is possible for many other configurations with slight changes. 
