/**
 * @name: DroneBoneVT21
 * @version: 1.0
 * @file: gpio_config.c
 * @authors: Trung Tran
 * 
 * License: GPL
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "/home/bbb/UAV-DroneBoneVT21/inc/gpio_config.h"

/* export a gpio */
void gpio_export(int pin_num)
{
    FILE *f = fopen("/sys/class/gpio/export", "w");
    if (f == NULL) {
        perror("export GPIO error\n");
        return;
    }
    fprintf(f, "%d", pin_num);
    fclose(f);
}

/* config direction of gpio */
void gpio_direction(int pin_num, const char *direction)
{
    char path[64];
    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/direction", pin_num);
    FILE *f = fopen(path, "w");
    if (f == NULL) {
        perror("set direction gpio error\n");
        return;
    }
    fprintf(f, "%s", direction);
    fclose(f);
}

/* set value of gpio */
void gpio_set_value(int pin_num, int value)
{
    char path[64];
    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", pin_num);
    FILE *f = fopen(path, "w");
    if (f == NULL) {
        perror("set value gpio error\n");
        return;
    }
    fprintf(f, "%d", value);
    fclose(f);
}

/* unexport a gpio */
void gpio_unexport(int pin_num)
{
    FILE *f = fopen("/sys/class/gpio/unexport", "w");
    if (f == NULL) {
        perror("unexport gpio error\n");
        return;
    }
    fprintf(f, "%d", pin_num);
    fclose(f);
}