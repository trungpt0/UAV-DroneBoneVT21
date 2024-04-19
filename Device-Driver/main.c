#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/string.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>

/**
 * Module Information
*/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Trung Tran - Try Hard Team - VT2 - PTIT");
MODULE_DESCRIPTION("UAV DroneBoneVT21");
MODULE_VERSION("1.0");

#define BUTTON_GPIO_PIN 60
#define LED_GPIO_PIN 20

dev_t dev_num = 0;
static struct class *dev_class;
static struct cdev dronebonevt21_cdev;
static unsigned int irq_number;
static int led_status = 0;

/**
 * Interrupt Handle Fuction
*/
static irqreturn_t button_irs(int irq, void *dev_id)
{
    led_status = !led_status;
    gpio_set_value(LED_GPIO_PIN, led_status);
    return IRQ_HANDLED;
}

/**
 * Function Prototypes
*/
static int  __init dronebonevt21_init(void);
static void __exit dronebonevt21_exit(void);
static int     dronebonevt21_open(struct inode *inode, struct file *file);
static int     dronebonevt21_release(struct inode *inode, struct file *file);
static ssize_t dronebonevt21_read(struct file *filp, char __user *buf, size_t len, loff_t *off);
static ssize_t dronebonevt21_write(struct file *filp, const char __user *buf, size_t len, loff_t *off);

/**
 * File Operations structure
*/
static struct file_operations fops =
{
    .owner = THIS_MODULE,
    .read = dronebonevt21_read,
    .write = dronebonevt21_write,
    .open = dronebonevt21_open,
    .release = dronebonevt21_release
};

/**
 * This function will be called when we open the Device File
*/
static int dronebonevt21_open(struct inode *inode, struct file *file)
{
    pr_info("Device File Opened!\n");
    return 0;
}

/**
 * This function will be called when we close the Device File
*/
static int dronebonevt21_release(struct inode *inode, struct file *file)
{
    pr_info("Device File Released!\n");
    return 0;
}

/**
 * This function will be called when we read the Device File
*/
static ssize_t dronebonevt21_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
    int ret;
    char status_buf[2];

    snprintf(status_buf, sizeof(status_buf), "%d", led_status);
    ret = copy_to_user(buf, status_buf, sizeof(status_buf));
    if (ret) {
        return -EFAULT;
    }

    pr_info("Device File Read!\n");
    return 0;
}

/**
 * This function will be called when we write the Device File
*/
static ssize_t dronebonevt21_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
    pr_info("Device File Written!\n");
    return len;
}

/**
 * Module initialization function
*/
static int __init dronebonevt21_init(void)
{
    int ret;
 
    // Allocating Major number device
    ret = alloc_chrdev_region(&dev_num, 0, 1, "dronebonevt21");
    if (ret < 0) {
        pr_alert("Failed to allocate Major number for device: %d\n", ret);
        return ret;
    }
    pr_info("Device registered: Major = %d Minor = %d\n", MAJOR(dev_num), MINOR(dev_num));

    // Initializing cdev structure
    cdev_init(&dronebonevt21_cdev, &fops);
    ret = cdev_add(&dronebonevt21_cdev, dev_num, 1);
    if (ret < 0) {
        pr_alert("Cannot add the device to the system!\n");
        goto cdev_err;
    }

    // Create struct class
    dev_class = class_create(THIS_MODULE, "dronebonevt21_class");
    if (IS_ERR(dev_class)) {
        pr_alert("Failed to create device class\n");
        ret = PTR_ERR(dev_class);
        goto class_err;
    }

    // Create device node
    if (IS_ERR(device_create(dev_class, NULL, dev_num, NULL, "dronebonevt21_dev"))) {
        pr_alert("Failed to create device\n");
        ret = -EFAULT;
        goto device_err;
    }

    /* Request button */
    ret = gpio_request(BUTTON_GPIO_PIN, "button_gpio");
    if (ret) {
        pr_err("Failed to request GPIO for button!\n");
        goto fail_gpio_request;
    }

    /* Set direction button */
    ret = gpio_direction_input(BUTTON_GPIO_PIN);
    if (ret) {
        pr_err("Failed to set button GPIO direction!\n");
        goto fail_gpio_direction;
    }

    /* Request led */
    ret = gpio_request(LED_GPIO_PIN, "led_gpio");
    if (ret) {
        pr_err("Failed to request GPIO for led!\n");
        goto fail_gpio_request;
    }

    /* Set direction led */
    ret = gpio_direction_output(LED_GPIO_PIN, 0);
    if (ret) {
        pr_err("Failed to set led GPIO direction!\n");
        goto fail_gpio_direction;
    }

    /* Register a interrupt number for button */
    irq_number = gpio_to_irq(BUTTON_GPIO_PIN);
    ret = request_irq(irq_number, button_irs, IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING, "button_irq", NULL);
    if (ret) {
        pr_err("Failed request to IRQ!\n");
        goto fail_irq_request;
    }

    pr_info("DroneBoneVT21 Module Inserted Successfully\n");
    return 0;

fail_irq_request:
    gpio_free(LED_GPIO_PIN);
    gpio_free(BUTTON_GPIO_PIN);
fail_gpio_direction:
    gpio_free(LED_GPIO_PIN);
    gpio_free(BUTTON_GPIO_PIN);
fail_gpio_request:
    device_destroy(dev_class, dev_num);
device_err:
    class_destroy(dev_class);
class_err:
    cdev_del(&dronebonevt21_cdev);
cdev_err:
    unregister_chrdev_region(dev_num, 1);
    return ret;
}

/**
 * Module exit function
*/
static void __exit dronebonevt21_exit(void)
{
    free_irq(irq_number, NULL);
    gpio_free(LED_GPIO_PIN);
    gpio_free(BUTTON_GPIO_PIN);
    device_destroy(dev_class, dev_num);
    class_destroy(dev_class);
    cdev_del(&dronebonevt21_cdev);
    unregister_chrdev_region(dev_num, 1);
    pr_info("DroneBoneVT21 Module Removed Successfully\n");
}

/**
 * Register initialization and exit functions of the module
*/
module_init(dronebonevt21_init);
module_exit(dronebonevt21_exit);