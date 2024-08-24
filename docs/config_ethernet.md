# ---------Shared Ethernet from Host to BBB---------
## Config BBB
- $ vi /etc/resolv.conf
- ~nameserver 8.8.8.8
- ~nameserver 8.8.4.4
- $ sudo route add default gw 192.168.7.1 usb0
## Config Host Ubuntu
- $ sudo su
- $ echo 1 > /proc/sys/net/ipv4/ip_forward
- $ iptables --table nat --append POSTROUTING --out-interface 'host wifi name' -j MASQUERADE
- $ iptables --append FORWARD --in-interface 'ethernet BBB name' -j ACCEPT
# --------------------------------------------------