# Getting Started w/XBee Series 2

There are many different ways to connect to a XBee Radio. One that works with both OSX and Linux is screen. 

* First connect the XBee to a usb port using a adaptor, breakout board, or sheild. 
* Next find where it is attached in the terminal.

```
ls /dev/tty.*
```

* It should appear and look something like this `ex: /dev/tty.usbserial-FTH144JL`
* Then use screen and the baudrate to connect through terminal.

```
screen /dev/tty.usbserial-FTH144JL 9600
```

* You can enter command mode by typing `+++` and not pressing return.
 * After a few moments the XBee should report back and say `OK`.
 * In command mode the Xbee will be able to recieve commands.

Note: There are two modes for the XBee, command and transparent mode. In transparent mode the XBee sends all data through. Command mode is used to talk directly to the XBee. Transparent mode is the default state and an XBee will return to transparent mode after 10 seconds of inactivity while in command mode.  

* To exit screen press `control-a` then `control-\` then `y`.
