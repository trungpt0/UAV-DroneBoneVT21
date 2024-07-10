obj-m += mpu6050.o

ifdef ARCH
	KDIR = /home/bbb/BBB/image-builder/BBB/tmp/lib/modules/5.10.168/build
else
	KDIR = /lib/modules/$(shell name -r)/build
endif

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean
