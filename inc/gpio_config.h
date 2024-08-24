/**
 * @name: DroneBoneVT21
 * @version: 1.0
 * @file: gpio_config.h
 * @authors: Trung Tran
 * 
 * License: GPL
 * 
 */

#ifndef GPIO_CONFIG_H
#define GPIO_CONFIG_H

#include <stdio.h>

void gpio_export(int pin_num);
void gpio_direction(int pin_num, const char *direction);
void gpio_set_value(int pin_num, int value);
void gpio_unexport(int pin_num);

#endif /* GPIO_CONFIG_H */