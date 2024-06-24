/**
 * @authors Trung Tran | Huynh Gia Bao - Try Hard Team - VT2 - PTIT
*/

#ifndef MOTOR_H
#define MOTOR_H

/**
 * Prototypes in motor.c 
*/
void export_gpio(int gpio_pin);
void set_direction(int gpio_pin, char *direction);
void write_gpio(int gpio_pin, int value);
void control_motor(int gpio_pin1, int gpio_pin2, int value);

#endif /* MOTOR_H */