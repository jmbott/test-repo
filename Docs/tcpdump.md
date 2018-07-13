# tcpdump on [Netgear Nighthawk R7000 router](https://www.netgear.com/home/products/networking/wifi-routers/R7000.aspx)

* tcpdump [reference sheet](http://packetlife.net/media/library/12/tcpdump.pdf) from packetlife.net

tcpdump is a network sniffing tool like wireshark. Its relatively small and works
on the command line. Can be used on a router given enough storage to check transmissions
by and to clients. This is useful particularly for devices you cant run wireshark
on like an arduino.

* if there is a package manager or you can get one you can use that to install.
[Optware](https://en.wikipedia.org/wiki/Optware) is one example common on routers.

* if there is no package manager you can download the source with `wget` or
download to your computer and `scp` it to your router.

* currently using [AdvancedTomato](https://advancedtomato.com/downloads/router/r7000)
based on [Tomato](http://tomato.groov.pl/) with `ssh` and `telnet` capability.
Once logged in you can get and install tcpdump

* files and description for creating `tcpdump`, `iperf`, and `rsync` binaries by
Fab Five Freddy [here](http://www.linksysinfo.org/index.php?threads/tomato-arm-utilities-tcpdump-iperf-rsync.70648/). These are for ARM, most [other](http://www.dslreports.com/r0/download/1376456~0df06f4164393e0fdd2aa2eede183328/tcpdump.zip) available are for MIPS routers.

* the general process is `wget` or `unzip` or `tar -xvzf` then `chmod +x file`
and `rm compressed_file` before running, `./tcpdump` or `tcpdump`

## Usage:

* check interfaces, `tcpdump -D`
* get packets on specific interface, `tcpdump -i eth0`
* in verbose mode, `tcpdump -v -i eth0`
* `-n` removes names and shows IPs
* specify a host, `tcpdump -v -i br0 -n host 10.0.0.170`, destination or source
* `-c` can be used for a number of packets
* `-w 0001.pcap` can be used to store information in a file for later, can be
read with `tcpdump` or `wireshark`
* specify a port with `port 80`
