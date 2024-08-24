obj-m += test_kmodule.o

ifdef ARCH
	KDIR = /home/bbb/UAV-DroneBoneVT21/image/5.10.168/build
else
	KDIR = /lib/modules/$(shell uname -r)/build
endif

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean
