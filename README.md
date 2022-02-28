# Character-Device-Driver
实现一个简单的字符设备驱动程序，以内核空间模拟字符设备，完成对该设备的各类操作，并编写了一个聊天程序实现对该设备的同步和互斥操作。

## 字符设备驱动

### **1.** **编写模块程序**

首先设计内核程序模块，这里以下文设计的字符设备驱动程序为例。完成设计后，将文件保存为globalvar.c 。

### **2.** **在模块源程序的相同目录下创建Makefile文件**

为了方便对上述设备驱动程序进行编译，建立Makefile文件，文件内容如下：

```makefile
ifneq ($(KERNELRELEASE),) 
obj-m := globalvar.o 
else 
KERNELDIR := /lib/modules/$(**shell** uname -r)/build 
PWD := $(**shell** pwd) 
modules: 
    $(MAKE) -C $(KERNELDIR) M=$(PWD) modules 
endif 
clean: 
    $(MAKE) -C $(KERNELDIR) M=$(PWD) clean
```

### **3.** **编译内核模块程序**

获取root权限后切换至内核动态模块程序所在的目录执行命令： #make
![image-1](https://github.com/Bright-Hsu/Character-Device-Driver/blob/main/pictures/image-1.png)

执行完命令后可以看到目录下生成了很多文件，列表如下（其中.ko文件就是编译产生的模块文件）：

![image-2](https://github.com/Bright-Hsu/Character-Device-Driver/blob/main/pictures/image-2.png)

 

### **4.** **加载内核动态模块**

当需要使用内核模块中的相关函数时，可加载相应的模块，执行如下命令：

```
#insmod globalvar.ko
```

此时可以使用 `lsmod` 命令来查看系统内的模块列表，以观察新设计的模块加载情况。

![image-3](https://github.com/Bright-Hsu/Character-Device-Driver/blob/main/pictures/image-3.png)

然后查看内核日志信息，执行命令：`#dmesg -c`

可以看到下图是我使用printk打印的内核日志消息：

![image-4](https://github.com/Bright-Hsu/Character-Device-Driver/blob/main/pictures/image-4.png)

**5.** **卸载内核动态模块**

模块使用完毕后，为了释放模块文件所占用的系统资源，可以对模块予以卸载。执行的

命令是：  `#rmmod globalvar`

此时可以使用 `lsmod` 命令查看系统内的模块列表，以观察新设计的模块卸载情况。可以看到该模块已经不存在。

![image-5](https://github.com/Bright-Hsu/Character-Device-Driver/blob/main/pictures/image-5.png)

## 聊天的同步与互斥实现

字符驱动设备模块的编写、编译、加载，已经在上面动态模块说过了，下面直接从编写测试程序和聊天程序开始进行字符设备驱动实验。

为了验证字符设备驱动程序 globalvar.c 的可用性，我编写了用户程序write.c，该程序可以作为用户的消息输入栏输入消息，又编写了接收消息的程序read.c，该程序互相配合可以测试对字符设备的读与写。

为了体现程序的健壮性，我开启了三个write写进程，代表三个用户，每个人都可以向聊天群中发消息，read程序就代表聊天群，用来接收每个人的消息。三个人按顺序介绍自己，又分别按顺序发了一句话。如下图：

![image-1](https://github.com/Bright-Hsu/Character-Device-Driver/blob/main/pictures/image-6.png)

![image-1](https://github.com/Bright-Hsu/Character-Device-Driver/blob/main/pictures/image-7.png)

![image-1](https://github.com/Bright-Hsu/Character-Device-Driver/blob/main/pictures/image-8.png)

然后运行read进程，可以读取到每个进程向设备发送的消息，且顺序并没有错乱，说明驱动程序的读写进程实现了同步与互斥。如下图：

![image-1](https://github.com/Bright-Hsu/Character-Device-Driver/blob/main/pictures/image-9.png)

 

**上述实现了多人聊天的程序，但有一定不足，也就是没有把消息输入框和消息输出框放在一个进程当中，更加人性化。因此，后面我又实现了更实际的聊天程序chat.c。**

chat.c利用读写进程之间的同步与互斥，实现了将读和写功能假如在一个程序当中，运行程序，打开两个进程代表两个用户进行聊天。如下图，进程4774和4776实验字符驱动设备进行聊天：

![image-1](https://github.com/Bright-Hsu/Character-Device-Driver/blob/main/pictures/image-10.png)

![image-1](https://github.com/Bright-Hsu/Character-Device-Driver/blob/main/pictures/image-11.png)

可以看到两个进程可以成功地通过字符驱动程序聊天，聊天程序设计正确。
