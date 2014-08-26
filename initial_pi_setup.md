# Setting up the Raspberry Pi

## Create Bootable SD Card

Download <tt>Raspbian</tt> from the Raspberry Pi website: [http://www.raspberrypi.org/downloads/](http://www.raspberrypi.org/downloads/)

 - Unzip said file and cd to the directory it is in
 - Check that the .img file is where you are:
   ```sh 
ls
```

* On Linux:

  - Before inserting SD card:

      ```sh
df -h
```

  - Then again after inserting SD card:
	
      ```sh
df -h
```

  - Find the difference, should be similar to <tt>/dev/sdb1</tt>
	
  - Unmount that device
      ```sh
umount /dev/sdb1
```

  - It could have multiple partitions, unmount them all. i.e. /dev/sdb1, /dev/sdb2

  - Use dd or dcfldd to write to the SD, dcfldd will give status updates but is likely not installed. The line should be of the form below,

      ```sh 
dd bs=4M if=2014-06-20-wheezy-raspbian.img of=/dev/sdd
```

		* Replace the .img name and the /dev/sdd with your own

		* To check on the status after using dd, in another terminal window
      ```sh 
pkill -USR1 -n -x dd
```

		* The terminal may appear to be frozen, it is probably not.

  - Once completed run
      ```sh 
sync
```
		This will verify all writing processes have finished
		
  - Remove the SD card

## Boot the Pi for the first time

 * w/an HDMI monitor and keyboard the config screen will simply appear

 * w/an ethernet cord and a terminal window you must look up the ip on the router. It will be under attached devices. ssh into the pi,
   ```sh
ssh pi@192.168.1.6
```
	- Replace IP with your own.
	
	- Default Login:
	
	```sh
		User		-	pi
		Password	-	raspberry
```
		
 * Once logged in to enter the config screen
   ```sh
sudo raspi-config
```

	- Expand the filesystem and set the date, time, and timezone
	
	- You can also edit the password here
	
	- Exit the config

	* To change the host name edit the following files
   ```sh 
sudo nano /etc/hosts
sudo nano /etc/hostname
```

	- Then run
   ```sh
sudo /etc/init.d/hostname.sh
```

	- Dont mind the output
	
	- Then reboot,
   ```sh
sudo reboot
```

	Set up a GitHub ssh key if you like and you're ready to go. 
