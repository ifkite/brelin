/*
 * USB Skeleton driver - 2.2
 *
 * Copyright (C) 2001-2004 Greg Kroah-Hartman (greg@kroah.com)
 *
 *	This program is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU General Public License as
 *	published by the Free Software Foundation, version 2.
 *
 * This driver is based on the 2.6.3 version of drivers/usb/usb-skeleton.c
 * but has been rewritten to be easier to read and use.
 *
 */

#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/kref.h>
#include <linux/uaccess.h>
#include <linux/usb.h>
#include <linux/mutex.h>


/* Define these values to match your devices */
#define USB_SKEL_VENDOR_ID	0x8380
#define USB_SKEL_PRODUCT_ID	0x0003
#define	KEYMASK_UP		0x00
#define	KEYMASK_DOWN	0xFF
#define	KEYMASK_LEFT	0x00
#define	KEYMASK_RIGHT	0xFF
#define KEYMASK_L1		0x01
#define KEYMASK_L2		0x04
#define KEYMASK_R1		0x02
#define KEYMASK_R2		0x08
#define	KEYMASK_Y		0x1F
#define	KEYMASK_A		0x4F
#define	KEYMASK_X		0x8F
#define	KEYMASK_B		0x2F
#define	KEYMASK_SELECT	0x10
#define	KEYMASK_START	0x20
#define INTERV_MILLI(ms)	(ms*HZ/1000)

/* table of devices that work with this driver */
static struct usb_device_id skel_table[] = {
	{ USB_DEVICE(USB_SKEL_VENDOR_ID, USB_SKEL_PRODUCT_ID) },
	{ }					/* Terminating entry */
};
MODULE_DEVICE_TABLE(usb, skel_table);


/* Get a minor range for your devices from the usb maintainer */
#define USB_SKEL_MINOR_BASE	192

/* our private defines. if this grows any larger, use your own .h file */
#define MAX_TRANSFER		(PAGE_SIZE - 512)
/* MAX_TRANSFER is chosen so that the VM is not stressed by
   allocations > PAGE_SIZE and the number of packets in a page
   is an integer 512 is the largest possible packet on EHCI */
#define WRITES_IN_FLIGHT	8
/* arbitrarily chosen */

static struct fasync_struct *fasync_queue;
static char *gb_data;

/* Structure to hold all of our device specific stuff */
struct usb_skel {
	struct usb_device	*udev;			/* the usb device for this device */
	struct usb_interface	*interface;		/* the interface for this device */
	struct semaphore	limit_sem;		/* limiting the number of writes in progress */
	struct usb_anchor	submitted;		/* in case we need to retract our submissions */
	struct urb		*bulk_in_urb;		/* the urb to read data with */
	unsigned char           *bulk_in_buffer;	/* the buffer to receive data */
	size_t			bulk_in_size;		/* the size of the receive buffer */
	size_t			bulk_in_filled;		/* number of bytes in the buffer */
	size_t			bulk_in_copied;		/* already copied to user space */
	char					*data;
	dma_addr_t				data_dma;
	__u8			bulk_in_endpointAddr;	/* the address of the bulk in endpoint */
	__u8			bulk_out_endpointAddr;	/* the address of the bulk out endpoint */
	int			errors;			/* the last request tanked */
	int			open_count;		/* count the number of openers */
	bool			ongoing_read;		/* a read is going on */
	bool			processed_urb;		/* indicates we haven't processed the urb */
	spinlock_t		err_lock;		/* lock for errors */
	struct kref		kref;
	struct mutex		io_mutex;		/* synchronize I/O with disconnect */
	struct completion	bulk_in_completion;	/* to wait for an ongoing read */
};
#define to_skel_dev(d) container_of(d, struct usb_skel, kref)
static int joystick_fasync(int fd, struct file *file, int on);
static struct usb_driver skel_driver;

static void skel_delete(struct kref *kref)
{
	struct usb_skel *dev = to_skel_dev(kref);

	usb_free_urb(dev->bulk_in_urb);
	usb_put_dev(dev->udev);
	kfree(dev->bulk_in_buffer);
	kfree(dev);
}

static int skel_open(struct inode *inode, struct file *file)
{
	printk("open called\n");
	return 0;
}

static int skel_release(struct inode *inode, struct file *file)
{
	printk("release called\n");
	joystick_fasync(-1, file, 0);
	return 0;
}

static ssize_t skel_read(struct file *file, char *buffer, size_t count,
			 loff_t *ppos)
{
	copy_to_user(buffer, gb_data, 8);
	return 0;
}

static ssize_t skel_write(struct file *file, const char *user_buffer,
			  size_t count, loff_t *ppos)
{
	printk("write called\n");
}

static int joystick_fasync(int fd, struct file *file, int on)
{
	int retval;
	printk("joystick fasynchronize.\n");
	retval = fasync_helper(fd, file, on, &fasync_queue);
	return retval;
}

static const struct file_operations skel_fops = {
	.read =		skel_read,
	.write =	skel_write,
	.open =		skel_open,
	.release =	skel_release,
	.fasync = joystick_fasync,
};

/*
 * usb class driver info in order to get a minor number from the usb core,
 * and to have the device registered with the driver core
 */
static struct usb_class_driver skel_class = {
	.name =		"skel%d",
	.fops =		&skel_fops,
	.minor_base =	USB_SKEL_MINOR_BASE,
};
static void joystick_irq(struct urb *urb)
{
	struct usb_joystick *js_dev = urb->context;
	char *data;
	static unsigned long jiff_UP = 0;
	static unsigned long jiff_DOWN = 0;
	static unsigned long jiff_LEFT = 0;
	static unsigned long jiff_RIGHT = 0;
	static unsigned long jiff_Y = 0;
	static unsigned long jiff_A = 0;
	static unsigned long jiff_X = 0;
	static unsigned long jiff_B = 0;
	static unsigned long jiff_L1 = 0;
	static unsigned long jiff_L2 = 0;
	static unsigned long jiff_R1 = 0;
	static unsigned long jiff_R2 = 0;
	static unsigned long jiff_SELECT = 0;
	static unsigned long jiff_START = 0;
	switch(urb->status)
	{
	case 0:
		data = js_dev->data;
		if((data[0] != (char)0x7F) || (data[1] != (char)0x7F) || (data[2] != (char)0x7F) || (data[3] != (char)0x7F) || 
		   (data[4] != (char)0xFF) || (data[5] != (char)0x0F) || (data[6] != (char)0x00) || (data[7] != (char)0x00))
		{
			switch(data[2])
			{
			case KEYMASK_LEFT:
				if(jiffies > (jiff_LEFT + INTERV_MILLI(200)))
				{
					jiff_LEFT = jiffies;
					goto signal_app;
				}
				break;
			case KEYMASK_RIGHT:
				if(jiffies > (jiff_RIGHT + INTERV_MILLI(200)))
				{
					jiff_RIGHT = jiffies;
					goto signal_app;
				}
				break;
			}
			switch(data[3])
			{
			case KEYMASK_UP:
				if(jiffies > (jiff_UP + INTERV_MILLI(200)))
				{
					jiff_UP = jiffies;
					goto signal_app;
				}
				break;
			case KEYMASK_DOWN:
				if(jiffies > (jiff_DOWN + INTERV_MILLI(200)))
				{
					jiff_DOWN = jiffies;
					goto signal_app;
				}
				break;
			}
			switch(data[5])
			{
			case KEYMASK_Y:
				if(jiffies > (jiff_Y + INTERV_MILLI(200)))
				{
					jiff_Y = jiffies;
					goto signal_app;
				}
				break;
			case KEYMASK_A:
				if(jiffies > (jiff_A + INTERV_MILLI(200)))
				{
					jiff_A = jiffies;
					goto signal_app;
				}
				break;
			case KEYMASK_X:
				if(jiffies > (jiff_X + INTERV_MILLI(200)))
				{
					jiff_X = jiffies;
					goto signal_app;
				}
				break;
			case KEYMASK_B:
				if(jiffies > (jiff_B + INTERV_MILLI(200)))
				{
					jiff_B = jiffies;
					goto signal_app;
				}
				break;
			}
			switch(data[6])
			{
			case KEYMASK_L1:
				if(jiffies > (jiff_L1 + INTERV_MILLI(200)))
				{
					jiff_L1 = jiffies;
					goto signal_app;
				}
				break;
			case KEYMASK_L2:
				if(jiffies > (jiff_L2 + INTERV_MILLI(200)))
				{
					jiff_L2 = jiffies;
					goto signal_app;
				}
				break;
			case KEYMASK_R1:
				if(jiffies > (jiff_R1 + INTERV_MILLI(200)))
				{
					jiff_R1 = jiffies;
					goto signal_app;
				}
				break;
			case KEYMASK_R2:
				if(jiffies > (jiff_R2 + INTERV_MILLI(200)))
				{
					jiff_R2 = jiffies;
					goto signal_app;
				}
				break;
			case KEYMASK_SELECT:
				if(jiffies > (jiff_SELECT + INTERV_MILLI(200)))
				{
					jiff_SELECT = jiffies;
					goto signal_app;
				}
				break;
			case KEYMASK_START:
				if(jiffies > (jiff_START + INTERV_MILLI(200)))
				{
					jiff_START = jiffies;
					goto signal_app;
				}
				break;
			}
		}
		break;
	default:
		break;
	}
	goto submit_urb;
signal_app:
	if(fasync_queue)
		kill_fasync(&fasync_queue, SIGIO, POLL_IN);
submit_urb:
	usb_submit_urb(urb, GFP_ATOMIC);
};

static int skel_probe(struct usb_interface *interface,
		      const struct usb_device_id *id)
{
	struct usb_skel *dev;
	struct usb_host_interface *iface_desc;
	struct usb_endpoint_descriptor *endpoint;
	size_t buffer_size;
	int i;
	int retval = -ENOMEM;

	/* allocate memory for our device state and initialize it */
	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev) {
		err("Out of memory");
		goto error;
	}
	kref_init(&dev->kref);
	sema_init(&dev->limit_sem, WRITES_IN_FLIGHT);
	mutex_init(&dev->io_mutex);
	spin_lock_init(&dev->err_lock);
	init_usb_anchor(&dev->submitted);
	init_completion(&dev->bulk_in_completion);

	dev->udev = usb_get_dev(interface_to_usbdev(interface));
	dev->interface = interface;

	/* set up the endpoint information */
	/* use only the first bulk-in and bulk-out endpoints */
	iface_desc = interface->cur_altsetting;
	for (i = 0; i < iface_desc->desc.bNumEndpoints; ++i) {
		endpoint = &iface_desc->endpoint[i].desc;

		if (!dev->bulk_in_endpointAddr &&
		    usb_endpoint_is_bulk_in(endpoint)) {
			/* we found a bulk in endpoint */
			buffer_size = le16_to_cpu(endpoint->wMaxPacketSize);
			dev->bulk_in_size = buffer_size;
			dev->bulk_in_endpointAddr = endpoint->bEndpointAddress;
			dev->bulk_in_buffer = kmalloc(buffer_size, GFP_KERNEL);
			if (!dev->bulk_in_buffer) {
				err("Could not allocate bulk_in_buffer");
				goto error;
			}
			dev->bulk_in_urb = usb_alloc_urb(0, GFP_KERNEL);
			if (!dev->bulk_in_urb) {
				err("Could not allocate bulk_in_urb");
				goto error;
			}
		}

		if (!dev->bulk_out_endpointAddr &&
		    usb_endpoint_is_bulk_out(endpoint)) {
			/* we found a bulk out endpoint */
			dev->bulk_out_endpointAddr = endpoint->bEndpointAddress;
		}
	}
	if (!(dev->bulk_in_endpointAddr && dev->bulk_out_endpointAddr)) {
		err("Could not find both bulk-in and bulk-out endpoints");
		goto error;
	}

	/* save our data pointer in this interface device */
	usb_set_intfdata(interface, dev);

	/* we can register the device now, as it is ready */
	retval = usb_register_dev(interface, &skel_class);
	if (retval) {
		/* something prevented us from registering this driver */
		err("Not able to get a minor for this device.");
		usb_set_intfdata(interface, NULL);
		goto error;
	}

	/* let the user know what node this device is now attached to */
	dev_info(&interface->dev,
		 "USB Skeleton device now attached to USBSkel-%d",
		 interface->minor);
	return 0;

error:
	if (dev)
		/* this frees allocated memory */
		kref_put(&dev->kref, skel_delete);
	return retval;
}

static void skel_disconnect(struct usb_interface *interface)
{
	struct usb_skel *dev;
	int minor = interface->minor;

	dev = usb_get_intfdata(interface);
	usb_set_intfdata(interface, NULL);

	usb_deregister_dev(interface, &skel_class);

	mutex_lock(&dev->io_mutex);
	dev->interface = NULL;
	mutex_unlock(&dev->io_mutex);

	usb_kill_anchored_urbs(&dev->submitted);

	kref_put(&dev->kref, skel_delete);

	dev_info(&interface->dev, "USB Skeleton #%d now disconnected", minor);
}

static struct usb_driver skel_driver = {
	.name =		"skeleton",
	.probe =	skel_probe,
	.disconnect =	skel_disconnect,
	.id_table =	skel_table,
};

static int __init usb_skel_init(void)
{
	int result;

	/* register this driver with the USB subsystem */
	result = usb_register(&skel_driver);
	if (result)
		err("usb_register failed. Error number %d", result);

	return result;
}

static void __exit usb_skel_exit(void)
{
	/* deregister this driver with the USB subsystem */
	usb_deregister(&skel_driver);
}

module_init(usb_skel_init);
module_exit(usb_skel_exit);

MODULE_LICENSE("GPL");
