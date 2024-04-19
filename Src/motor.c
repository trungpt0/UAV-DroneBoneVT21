/**
 * @authors Trung Tran | Huynh Gia Bao - Try Hard Team - VT2 - PTIT
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "/home/bbb/UAV-DroneBoneVT21/Driver/MotorSystem/motor.h"

#define GPIO_PATH "/sys/class/gpio/"

/**
 * Function export a GPIO pin
*/
void export_gpio(int gpio_pin)
{
    char buffer[1024];
    int file_handle;

    snprintf(buffer, sizeof(buffer), "%sexport", GPIO_PATH);
    file_handle = open(buffer, O_WRONLY);
    if (file_handle < 0) {
        printf("Export GPIO%d failed!\n", gpio_pin);
        return;
    }
    snprintf(buffer, sizeof(buffer), "%d", gpio_pin);
    write(file_handle, buffer, strlen(buffer));
    close(file_handle);
}

/**
 * Function set direction for a GPIO pin
*/
void set_direction(int gpio_pin, char *direction)
{
    char buffer[1024];
    int file_handle;

    snprintf(buffer, sizeof(buffer), "%sgpio%d/direction", GPIO_PATH, gpio_pin);
    file_handle = open(buffer, O_WRONLY);
    if (file_handle < 0) {
        printf("Set direction for GPIO%d failed!\n", gpio_pin);
        return;
    }
    write(file_handle, direction, strlen(direction));
    close(file_handle);
}

/**
 * Function write value into a GPIO pin
*/
void write_gpio(int gpio_pin, int value)
{
    char buffer[1024];
    int file_handle;

    snprintf(buffer, sizeof(buffer), "%sgpio%d/value", GPIO_PATH, gpio_pin);
    file_handle = open(buffer, O_WRONLY);
    if (file_handle < 0) {
        printf("Write value into GPIO%d failed!\n", gpio_pin);
        return;
    }
    snprintf(buffer, sizeof(buffer), "%d", value);
    write(file_handle, buffer, strlen(buffer));
    close(file_handle);
}

/**
 * Function control motor: direction and speed control
*/
void control_motor(int gpio_pin1, int gpio_pin2, int value)
{
    export_gpio(gpio_pin1);
    export_gpio(gpio_pin2);
    set_direction(gpio_pin1, "out");
    set_direction(gpio_pin2, "out");
    if (value == 1) {
        write_gpio(gpio_pin1, 1);
        write_gpio(gpio_pin2, 1);
    } else {
        write_gpio(gpio_pin1, 0);
        write_gpio(gpio_pin1, 0);
    }
}