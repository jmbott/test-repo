#!/bin/bash

# script to find all IPs on network that respond to pings
# to run $ sudo bash find_ip.bash

time (
    s=192.168.1;
    for i in $(seq 1 254);
    do (ping -n -c 1 -w 1 $s.$i 1>/dev/null 2>&1 && printf "%-16s %s\n" $s.$i responded) & done;
    wait;
    echo
)
