/**
 * @authors Trung Tran | Nguyen Truong Giang - Try Hard Team - VT2 - PTIT
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#include "/home/bbb/UAV-Projects/DroneBoneVT21/Driver/SensorSystem/mpu9250.h"

#define I2C_DEVICE "/dev/i2c-1" // I2C Device path

int fd;

/**
 * Function init I2C with MPU9250
*/
int mpu9250_init()
{
    if ((fd = open(I2C_DEVICE, O_RDWR)) < 0) {
        perror("Failed to open the I2C bus!\n");
        return -1;
    }
    if (ioctl(fd, I2C_SLAVE, MPU9250_I2C_ADDRESS) < 0) {
        perror("Failed to acquire bus access and/or talk to slave!\n");
        return -1;
    }
    return 0;
}

/**
 * Function read acceleration from MPU9250
*/
int mpu9250_read_acceleration(int16_t *ax, int16_t *ay, int16_t *az)
{
    uint8_t data[6];
    if (read(fd, data, 6) != 6) {
        perror("Failed to read acceleration from MPU9250!\n");
        return -1;
    }
    *ax = (data[0] << 8) | data[1];
    *ay = (data[2] << 8) | data[3];
    *az = (data[4] << 8) | data[5];
    
    return 0;
}

/**
 * Function read gyro from MPU9250
*/
int mpu9250_read_gyro(int16_t *gx, int16_t *gy, int16_t *gz)
{
    uint8_t data[6];
    if (read(fd, data, 6) != 6) {
        perror("Failed to read gyro from MPU9250!\n");
        return -1;
    }
    *gx = (data[0] << 8) | data[1];
    *gy = (data[2] << 8) | data[3];
    *gz = (data[4] << 8) | data[5];

    return 0;
}

/**
 * Function read acceleration and gyro from MPU9250
*/
int mpu9250_read_all(int16_t *ax, int16_t *ay, int16_t *az, int16_t *gx, int16_t *gy, int16_t *gz)
{
    uint8_t data[14];
    if (read(fd, data, 14) != 14) {
        perror("Failed to read acceleration and gyro from MPU9250!\n");
        return -1;
    }
    *ax = (data[0] << 8) | data[1];
    *ay = (data[2] << 8) | data[3];
    *az = (data[4] << 8) | data[5];
    *gx = (data[8] << 8) | data[9];
    *gy = (data[10] << 8) | data[11];
    *gz = (data[12] << 8) | data[13];

    return 0;
}