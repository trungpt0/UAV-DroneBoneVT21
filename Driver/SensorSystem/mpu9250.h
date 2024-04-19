/**
 * @authors Trung Tran | Nguyen Truong Giang - Try Hard Team - VT2 - PTIT
*/

#ifndef MPU9250_H
#define MPU9250_H

#include <stdint.h>

#define MPU9250_I2C_ADDRESS 0x68 // MPU9250 address on I2C bus

/**
 * Prototypes in mpu9250.c 
*/
int mpu9250_init(); // Function init I2C with MPU9250
int mpu9250_read_acceleration(int16_t *ax, int16_t *ay, int16_t *az); // Function read acceleration from MPU9250
int mpu9250_read_gyro(int16_t *gx, int16_t *gy, int16_t *gz); // Function read gyro from MPU9250
int mpu9250_read_all(int16_t *ax, int16_t *ay, int16_t *az, int16_t *gx, int16_t *gy, int16_t *gz); // Function read acceleration and gyro from MPU9250

#endif /* MPU9250_H */