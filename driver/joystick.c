#include<linux/kernel.h>
#include<linux/errno.h>
#include<linux/init.h>
#include<linux/slab.h>
#include<linux/module.h>
#include<linux/kref.h>
#include<linux/uaccess.h>
#include<linux/mutex.h>
//need crtl endpoint, to get info from devive, get dev status, send cmd to dev
//intertupt endpoint, transform small data
#define USB_JOY_VENDOR_ID 0x8380
#define USB_JOY_PRODUCT_ID 0x0003
static struct usb_device_id joy_table[] = {
	{ USB_DEVICE(USB_JOY_VENDOR_ID, USB_JOY_PRODUCT_ID)},
	{ }
}
MODULE_DEVICE_TABLE(usb, joy_table);
//usb_interface
//usb_device *id
struct joy_dev {
	
};
static int joy_probe (struct usb_interface *interface, const struct usb_device_id *id){
	printk("joy_probe called\n");
	struct joy_dev *dev;
	struct usb_host_interface *iface_desc;
	size_t buffer_size;
	int i;
	int retval = -ENOMEM;
	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev) {
		err("Out of memory");
		goto error;
	}
	kref_init(&dev->kref);//counter initlize
	sema_init(&dev->limit_sem, WRITES_IN_FLIGHT);
	mutex_init(&dev->io_mutex);
	spin_lock_init(&dev->err_lock);
//	init_usb_anchs can be called to have access to URBs which are to be executed without bothering to track themor(&dev->submitted);	
	init_usb_anchor(&dev->submitted);
	init_completion(&dev->bulk_in_completion);
	dev->udev = usb_get_dev(interface_to_usbdev(interface));
	dev->interface = interface;
	iface_desc = interface->cur_altsetting;	
}

static void joy_delete(struct kref *kref){
}

static void joy_disconnect(struct usb_interface *interface){
	struct joy_dev *dev;
	int minor = interface->minor;//minor number
	dev = usb_get_intfdata(interface);//device->data = interface->dev->devive->data
	usb_set_intfdata(interface, NULL);//save pointer of data to interface, interface->dev->device->data = NULL
	usb_deregister_dev(interface, &joy_class);//deregister joy_class to interface
	mutex_lock(&dev->io_mutex);
	dev->interface = NULL;
	mutex_unlock(&dev->io_mutex);
	usb_kill_anchored_urbs(&dev->submitted);//free unused urbs
	kref_put(&dev->kref, joy_delete);//minus the referance of dev->kref
	dev_info(&interface->dev, "USB Skeleton #%d now disconnected", minor);
}

static struct usb_driver joy_driver = {//where 's  usb_driver
	.name = "joystick",
	.probe = joy_probe, //for connect
	.disconnect = joy_disconnect,// for disconnect
	.id_table = joy_table,
};
static int __init joy_init(void){
	int result;
	result = usb_register(&joy_driver);//not include header file
	if (result)
		err("joy_register failed. error num %d\n",result);

	printk("joy_register success\n");
	return result;
}
static int __exit joy_exit(void){
	usb_deregister(&joy_driver);
}
module_init(joy_init);
module_exit(joy_exit);
