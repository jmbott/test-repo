# Setting up the Wifi access point

## Installing Host apd
```
sudo apt-get install hostapd
sudo nano /etc/hostapd.conf
```
- Add the following and save:
```
interface=wlan0
ssid=PiPiPi
channel=1
wmm_enabled=0
wpa=1
wpa_passphrase=raspberry1
wpa_key_mgmt=WPA-PSK
wpa_pairwise=TKIP
rsn_pairwise=CCMP
auth_algs=1
macaddr_acl=0
```
- Test run:
```
sudo hostapd -dd /etc/hostapd/hostapd.conf
```
- Get it to run on boot:
```
sudo nano /etc/default/hostapd
```
- Add this line and save:
```
DAEMON_CONF="/etc/hostapd/hostapd.conf"
```

## Installing Dnsmasq
```
sudo apt-get install dnsmasq
sudo service dnsmasq stop
sudo mv /etc/dnsmasq.conf /etc/dnsmasq.conf.bak
sudo nano /etc/dnsmasq.conf
```
- Add the following and save:
```
interface=wlan0
expand-hosts
domain=local
dhcp-range=10.0.0.10,10.0.0.20,24h
dhcp-option=3,10.0.0.1
```

## Edit Network interfaces
```
sudo nano /etc/network/interfaces
```
- Add the following and save:
```
iface wlan0 inet static
address 10.0.0.1
network 10.0.0.0
netmask 255.255.255.0
broadcast 10.0.0.255
```

## Forward connections to local server
```
sudo iptables -t nat -A PREROUTING -i wlan0 -p tcp --dport 80 -j DNAT --to-destination 10.0.0.1:80
sudo iptables -t nat -A PREROUTING -i wlan0 -p tcp --dport 443 -j DNAT --to-destination 10.0.0.1:80
```

## Quick test server on Pi
```
sudo python -m SimpleHTTPServer 80
```

## Useful links

- http://stackoverflow.com/questions/19380924/create-captive-portal-on-raspbian
- http://www.daveconroy.com/turn-your-raspberry-pi-into-a-wifi-hotspot-with-edimax-nano-usb-ew-7811un-rtl8188cus-chipset/
- http://unix.stackexchange.com/questions/125296/redirecting-request-on-device-in-access-point-mode
- http://forums.adafruit.com/viewtopic.php?f=19&t=47716
