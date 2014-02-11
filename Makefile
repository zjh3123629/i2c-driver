obj-m := i2c_dev.o i2c_drv.o

KDIR := /home/zhouzuoyu/work/code/my_code/linux-3.10.28/linux-3.10.28/
PWD := $(shell pwd)

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	rm -rf .i2c_* *.o *.ko modules.order Module.symvers i2c_dev.mod.c i2c_drv.mod.c .tmp_versions
