ifneq ($(KERNELRELEASE),) 
obj-m := globalvar.o 
else 
KERNELDIR := /lib/modules/$(shell uname -r)/build 
PWD := $(shell pwd) 
modules: 
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules 
endif 
clean: 
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean