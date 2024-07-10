# ---------CROSS COMPILE BBB---------
## Cross Compile
- $ make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
## Transfer file to BBB via ethernet
- $ sudo rsync -avz .ko debian@192.168.7.2:/home/debian
## Insert and Remove Module
- $ sudo insmod yours.ko
- $ sudo rmmod yours
- $ sudo dmesg
# -----------------------------------