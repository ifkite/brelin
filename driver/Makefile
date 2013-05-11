ifneq ($(KERNELRELEASE),) 
obj-m:= joystick.o#usb-dongle.o 
else 
KDIR:= /lib/modules/$(shell uname -r)/build
BDIR:= $(shell pwd) 
default: 
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules 
.PHONY: clean 
clean: 
	make -C $(KDIR) M=$(BDIR) clean 
endif
