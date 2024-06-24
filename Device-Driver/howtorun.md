# Tools
## Cross-complie
$ make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
## SSH .ko file to BBB
$ sudo rsync -avz .ko debian@192.168.7.2:/home/debian
## Insert module
$ sudo insmod yours.ko
$ sudo rmmod yours
$ sudo dmesg
