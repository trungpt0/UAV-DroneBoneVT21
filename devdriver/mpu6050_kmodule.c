#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/i2c.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>

#define MPU6050_ADDRESS 0x68

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Trung Tran");
MODULE_DESCRIPTION("MPU6050 Driver");
MODULE_VERSION("1.0");

static struct i2c_client *mpu6050_client;

/**
 * This function was called when we open mpu6050 device file
 */
static int mpu6050_open(struct inode *inode, struct file *filp)
{
	pr_info("MPU6050 Devive File Opened!\n");
	return 0;
}

/**
 * This function was called when we close mpu6050 device file
 */
static int mpu6050_release(struct inode *inode, struct file *filp)
{
	pr_info("MPU6050 Device File Closed!\n");
	return 0;
}

/**
 * This function was called when we open mpu6050 device file
 */
static ssize_t mpu6050_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
	char data[14];
	int ret;

	mpu6050_client->addr = MPU6050_ADDRESS;

	ret = i2c_master_recv(mpu6050_client, data, 14);
	if (ret < 0)
		return ret;

	if(copy_to_user(buf, data, 14))
		return -EFAULT;

	return 14;
}

static struct file_operations fops = {
	.open = mpu6050_open,
	.release = mpu6050_release,
	.read = mpu6050_read,
};

static int mpu6050_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	int ret;
	char config[2];

	mpu6050_client = client;

	config[0] = 0x6B;
	config[1] = 0x00;

	ret = i2c_master_send(client, config, 2);
	if (ret < 0)
		return ret;

	pr_info("MPU6050 device probed at address 0x%02x\n", client->addr);
	return 0;
}

static int mpu6050_remove(struct i2c_client *client)
{
	pr_info("MPU6050 Removed!\n");
	return 0;
}

static const struct i2c_device_id mpu6050_id[] = {
	{ "mpu6050", 0 },
	{ }
};

MODULE_DEVICE_TABLE(i2c, mpu6050_id);

static struct i2c_driver mpu6050_driver = {
	.driver = {
		.name = "mpu6050",
	},
	.probe = mpu6050_probe,
	.remove = mpu6050_remove,
	.id_table = mpu6050_id,
};

static int __init mpu6050_init(void)
{
	int ret;

	ret = register_chrdev(235, "mpu6050", &fops);
	if (ret < 0)
		return ret;

	ret = i2c_add_driver(&mpu6050_driver);
	if (ret < 0)
		unregister_chrdev(235, "mpu6050");

	pr_info("MPU6050 Driver Inserted!");
	return ret;
}

static void __exit mpu6050_exit(void)
{
	i2c_del_driver(&mpu6050_driver);
	unregister_chrdev(235, "mpu6050");
	pr_info("MPU6050 Driver Removed!\n");
}

module_init(mpu6050_init);
module_exit(mpu6050_exit);
