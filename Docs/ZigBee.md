# Getting Started w/XBee Series 2

There are many different ways to connect to a XBee Radio. One that works with both OSX and Linux is screen. 

## screen

* First connect the XBee to a usb port using a adaptor, breakout board, or sheild. 
* Next find where it is attached in the terminal.

```
ls /dev/tty.*
```

* It should appear and look something like this ex: `
* /dev/tty.usbserial-FTH144JL`
* Then use screen and the baudrate to connect through terminal.

```
screen /dev/tty.usbserial-FTH144JL 9600
```

* You can enter command mode by typing `+++` and not pressing return.
 * After a few moments the XBee should report back and say `OK`.
 * In command mode the Xbee will be able to recieve commands.

Note: There are two modes for the XBee, command and transparent mode. In transparent mode the XBee sends all data through. Command mode is used to talk directly to the XBee. Transparent mode is the default state and an XBee will return to transparent mode after 10 seconds of inactivity while in command mode.  

* To exit screen press `control-a` then `control-\` then `y`.

## CoolTerm

* CoolTerm is another option. Edit the connection options to connect to the correct usb. 
* Once connected use `+++` to enter command mode. 
* You can use AT commands, "attention commands", to find out more. 

```
AT    >>  Asking "Are you there?". You should get the response "OK".
ATID  >>  Shows the Personal Area Network ID that is currently assigned.
          The PAN address defines the network the radio will connect to. 
          The number is in hex in the range 0x0 to 0xFFFF.
ATSH  >>  The high part of a 64-bit serial number that serves as a permanent address for the XBee.
ATSL  >>  The low part of a 64-bit serial number that serves as a permanent address for the XBee.
ATDH  >>  This shows the destination address for the radio to send information to.
ATDL  >>  This is used to assign the destination address for the radio to send information to.
ATCN  >>  This command instantly drops you out of command mode. 
ATWR  >>  This writes the complete configuration to firmware so it sticks through a powercycle.
          This is similar to a "save" command that saves the state before shutdown.
ATMY  >>  This shows the current 16-bit addresses. The coordinator assigns this address dynamically
          so it can be displayed but not set for Series 2 ZigBee radios. 
```

* The response from ATSH is the Coordinator address. That is always '0013A200'.
* The response from ATSL is the Router address. This is different for every radio. ex: `40B96CF2`. 
* Every network must have a coordinator radio and not multiple. 
* The coordinator must be configured. 

```
|Function|                    |Command|           |Parameter|
PAN ID                        ATID                2001 (anything from 0 to FFFF)
Destination address high      ATDH                0013A200
Destination address low       ATDL                <Router Address>
```

* Use the `ATWR` command to save the configuration

* The router must also be configured

```
|Function|                    |Command|           |Parameter|
PAN ID                        ATID                2001 (Same as all other radios in the network)
Destination address high      ATDH                0013A200
Destination address low       ATDL                <Coordinator Address>
```

* To check the edited values use the commands without parameters. 
* Remember to save before disconnecting. 

