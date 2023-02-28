obj-m += hello.o
K_PATH = /lib/modules/$(shell uname -r)/build

all:
	make -C $(K_PATH) M=$(shell pwd) modules

clean:
	make -C $(K_PATH) M=$(shell pwd) clean

