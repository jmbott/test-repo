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

## Updating XBee Firmware

Before you can connect your XBee radios you have to update the firmware appropriately. 

Unfortunately you have to use a seperate program to update the XBee firmware. This will allow you to conv=figure your device as a coordinator or a router. Fortunately it is now available for OSX. 

* Download and install X-CTU
* Open the program and go to the Radio Configuration Tab
* Add the device attached to the serial port, ex: usbserial*
* Once the device is found select it and select update firmware. 
* Update to the latest firmware
 * One device must be a coordinator and so on to form your mesh network
* Once the update is complete you can exit the software.

## XBee I/O Features

The XBee radios can be used alone or with an additional microcomputer. When used alone they have limited capabilities. They have no PWM outputs but have a few pins that can be used as digintal inputs, digital outputs, and analog inputs. 

* Some configurable pins have other hardware applications for optional duties. 

```
|Pin name|          |Physical pin #|    |AT command|        |Other functions|
DIO0,AD0            20                  D0                  Analog input, Commissioning Button
DIO1,AD1            19                  D1                  Analog input
DIO2,AD2            18                  D2                  Analog input
DIO3,AD3            17                  D3                  Analog input
DIO4                11                  D4                  
DIO5                15                  D5                  Association indicator
DIO6                16                  D6                  RTS
DIO7                12                  D7                  CTS
(DIO8)              9                   None                Pin sleep control,DTR
(DIO9)              13                  None                On/Sleep indicator
DIO10               6                   P0                  Received Signal Strength Indicator (RSSI)
DIO11               7                   P1                  
DIO12               4                   P2                  
```

* To configure the XBee for direct input(s) and output(s) you must use AT commands. 

```
|Command Sets|      |Purpose|
ATD0 to ATD7        Configures pins 0-7 (8 and 9 not supported currently)
ATP0 to ATP1        Configures pins 10-11 (12 is not currently supported)
ATIR                Sets I/O sample rate (miliseconds in hex)
                    ex: 10 times/second = every 100ms = 0x64 = ATIR64
                    To disable periodic sampling set ATIR to zero.
ATWR                Saves configuration
```

* Each command set needs a setting code directly following it for something to be set. 
 * for ATIR that setting code is a hex number. For ATDx or ATPx it is as follows

```
|Setting Code|      |Purpose|
0                   Disables I/O on selected pin
1                   Built in function, if available on that pin
2                   Analog input, only on pins D0-D3
3                   Digital input
4                   Digital output, low (0 volts)
5                   Digital output, high (3.3 volts)
```

Note: Analog inputs top out at 1.2V. All inputs higher than 1.2 volts will be read as a 1.2 volt signal.

* There are a few other advanced commands. 

```
|Command|           |Purpose|
AT%V                Returns current supply voltage (Useful to monitor battery status)
ATPR                Configures the 30K pullup resistors (binary value sets) (By default all enabled)
ATIC                Configures digital I/O pins to monitor for changes in state.
```

