#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/kref.h>
#include <linux/uaccess.h>
#include <linux/usb.h>
#include <linux/mutex.h>

#define USB_JOYSTICK_VENDOR_ID 0x8380
#define USB_JOYSTICK_PRODUCT_ID 0x0003
static struct usb_device_id joystick_ids[] = {
	//将vendor 和 product id 记录到模块镜像中,一旦有卡插入,驱动模块将被加载到内核运行.
	{USB_DEVICE(USB_JOYSTICK_VENDOR_ID, USB_JOYSTICK_PRODUCT_ID)},
	{	}//termiante
};

MODULE_DEVICE_TABLE(usb, joystick_ids);

typedef struct {
	struct usb_device        *usbdev;
	struct usb_interface     *interface;
	struct urb			     *ctrl_urb;
	struct usb_ctrlrequest   ctrl_req;
	unsigned char            *irq_in_buf;//通过它获取手柄数据
	size_t                   irq_in_len;
	__u8                     irq_in_addr;
}joystick_device_t;

//need to know
#define JOYSTICK_MINOR_BASE 192

static ssize_t joystick_read(struct file *file, char *buffer, size_t count, loff_t *ppos){
	printk("joystick read called\n");
	return 0;
}

static ssize_t joystick_write(struct file *file, const char *user_buffer, size_t count, loff_t *ppos){
	printk("joystick write called\n");
	return 0;
}

static int joystick_open(struct inode *inode, struct file *file ){
	printk("joystick open called\n");
	return 0;
}
static int joystick_release(struct inode *inode, struct file *file){
	printk("joystick release called\n");
	return 0;
}

static struct file_operations joystick_fops = {
	.owner = THIS_MODULE,
	.read = joystick_read,
	.write = joystick_write,
	//.ioctl = joystick_ioctl,
	.open = joystick_open,
	.release = joystick_release,
};

static struct usb_class_driver joystick_class = {
	.name = "joystick",
	.fops = &joystick_fops,
	.minor_base = JOYSTICK_MINOR_BASE,//从设备号 开始
};

static int joystick_probe(struct usb_interface *interface, const struct usb_device_id *id){
	printk("joystick probe called\n");
	/*
	struct usb_host_interface *iface_desc;
	struct usb_endpoint_descriptor *endpoint;
	joystick_device_t *joy_dev;
	int retval = -ENOMEM;
	//1.为joystick_device_t 分配内存, what is GFP_KERNEL
	joy_dev = kzalloc(sizeof(joystick_device_t), GFP_KERNEL);
	//2初始化joystick_device_t 的相关变量
	joy_dev->usbdev = usb_get_dev(interface_to_usbdev(interface));
	joy_dev->interface = interface;
	//获得结点数据,数据由枚举过程提供 
	iface_desc = interface->cur_altsetting;
	
	usb_set_intfdata(interface, joy_dev);
	
	//retval = usb_register_dev(interface, &joystick_class);
	//if(retval){
	//	usb_set_intfdata(interface, NULL);
	//	return retval;
	//}
	
	retval = usb_register_dev(interface, NULL);
	return retval;
	printk("now joystick device attached to /dev/joystick \n");
	*/
	return 0;	
	//3.将字符设备/dev/joystick 倒给用户空间
}

static void joystick_disconnect(struct usb_interface *interface){
	/*
	joystick_device_t *joy_dev;
	joy_dev = usb_get_intfdata(interface);
	usb_set_intfdata(interface, NULL);
	usb_deregister_dev(interface, &joystick_class);
	*/
}

static struct usb_driver joystick_driver = {
	.name = "joystick",
	.probe = joystick_probe,
	.disconnect = joystick_disconnect,
	.id_table = joystick_ids,
};

static int __init usb_joystick_init(void){
	printk("McDolphin joystick initlized\n");
	int result;
	result = usb_register(&joystick_driver);
	return 0;
}

static void __exit usb_joystick_exit(void){
	//usb_deregister(&joystick_driver);
	printk("McDolphin joystick exit\n");
	return;
}

module_init(usb_joystick_init);
module_exit(usb_joystick_exit);
MODULE_LICENSE("GPL");
