#define USB_JOYSTICK_VENDOR_ID 0x8380
#define USB_JOYSTICK_PRODUCT_ID 0x0003

static struct usb_device_id joystick_ids[] = {
	//将vendor 和 product id 记录到模块镜像中,一旦有卡插入,驱动模块将被加载到内核运行.
	{USB_DEVICE(USB_JOYSTICK_VENDOR_ID, USB_JOYSTICK_PRODUCT_ID)},
	{	}//termiante
};

MODULE_DEVICE_TABLE(usb, joystick_ids);

static struct usb_driver joystick_driver{
	.name = "joystick",
	.probe = joystick_probe,
	.disconnect = joystick_disconnect,
	.id_table = joystick_ids,
};

static int __init usb_joystick_init(void){
	int result;
	result = usb_register(&joystick_driver);
	printk("McDolphin joystick initlized\n");
	return 0;
}
static int __exit usb_joystick_exit(void){
	usb_deregister(&joystick_driver);
	return 0;
}
module_init(usb_joystick_init);
module_exit(usb_joystick_exit);
