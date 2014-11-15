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

* You can check if the XBee is ready to recieve commands by typing `+++` and not pressing return.
 * After a few moments the XBee should report back and say `OK`
* To exit screen press `control-a` then `control-\` then `y`.