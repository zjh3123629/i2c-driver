#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/i2c.h>
#include <linux/errno.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>

static ssize_t at24xx_read(struct file *file, char __user *buf, 
						size_t count, loff_t *ppos)
{
	return 0;
}

static ssize_t at24xx_write(struct file *file, const char __user *buf,
						size_t count, loff_t *ppos)
{
	return 0;
}

static long at24xx_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	return 0;
}

static int at24xx_open(struct inode *inode, struct file *file)
{
	return 0;
}

static int at24xx_close(struct inode *inode, struct file *file)
{
	return 0;
}

static const struct file_operations at24xx_fops = {
	.owner		= THIS_MODULE,
	.read		= at24xx_read,
	.write		= at24xx_write,
	.unlocked_ioctl	= at24xx_ioctl,
	.open		= at24xx_open,
	.release	= at24xx_close,
};
static struct miscdevice at24xx_miscdev = {
	.minor	= MISC_DYNAMIC_MINOR,
	.name	= "at24lc04",
	.fops	= &at24xx_fops,
};

static int at24cxx_probe(struct i2c_client *client,
				  const struct i2c_device_id *id)
{
	printk("zjh: %s\n", __func__);

	/* create miscdevice */
	if (misc_register(&at24xx_miscdev)) {
		printk("cannot register miscdev\n");
		goto err_misc_register;
	}
	
	return 0;

err_misc_register:
	return -1;
}

static int at24cxx_remove(struct i2c_client *client)
{
	printk("zjh: %s\n", __func__);

	if (misc_deregister(&at24xx_miscdev)) {
		printk("cannot deregister miscdev\n");
		goto err_misc_deregister;
	}

	return 0;

err_misc_deregister:
	return -1;
}

static const struct i2c_device_id at24cxx_id_table[] = {
	{ "at24lc04", 0 },
	{}
};
MODULE_DEVICE_TABLE(i2c, at24cxx_id_table);

static struct i2c_driver at24cxx_driver = {
	.driver	= {
		.name	= "smart210",
		.owner	= THIS_MODULE,
	},
	.probe		= at24cxx_probe,
	.remove		= at24cxx_remove,
	.id_table	= at24cxx_id_table,
};

static int __init at24cxx_i2c_init(void)
{
	int ret;

	ret = i2c_add_driver(&at24cxx_driver);
	if (ret != 0)
		pr_err("Failed to register AT24CXX I2C driver: %d\n", ret);
	
	return ret;
}
module_init(at24cxx_i2c_init);

static void __exit at24cxx_i2c_exit(void)
{
	i2c_del_driver(&at24cxx_driver);
}
module_exit(at24cxx_i2c_exit);


MODULE_DESCRIPTION("I2C Driver for AT24CXX");
MODULE_AUTHOR("zjh <zjh3123629@163.com>");
MODULE_LICENSE("GPL");

