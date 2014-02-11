#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/errno.h>

static struct i2c_client * at24cxx_i2c_client = NULL;
static const unsigned short at24cxx_i2c[] = { 0x50, I2C_CLIENT_END };

static int __init at24cxx_i2c_init(void)
{
	struct i2c_adapter *i2c_adap;
	struct i2c_board_info i2c_info;

	i2c_adap = i2c_get_adapter(0);
	
	memset(&i2c_info, 0, sizeof(struct i2c_board_info));
	strlcpy(i2c_info.type, "at24lc04", I2C_NAME_SIZE);	/* i2c_board_info.type == i2c_driver.id_table.name */
	at24cxx_i2c_client = i2c_new_probed_device(i2c_adap, &i2c_info, at24cxx_i2c, NULL);
	if (NULL == at24cxx_i2c_client) {
		printk("i2c_new_probed_device failed\n");
		goto err_i2c_new_probed_device;
	}
	
	i2c_put_adapter(i2c_adap);

	return 0;

err_i2c_new_probed_device:
	i2c_put_adapter(i2c_adap);
	return -ENODEV;
}
module_init(at24cxx_i2c_init);

static void __exit at24cxx_i2c_exit(void)
{
	i2c_unregister_device(at24cxx_i2c_client);
}
module_exit(at24cxx_i2c_exit);


MODULE_DESCRIPTION("I2C Device for AT24CXX");
MODULE_AUTHOR("zjh <zjh3123629@163.com>");
MODULE_LICENSE("GPL");

