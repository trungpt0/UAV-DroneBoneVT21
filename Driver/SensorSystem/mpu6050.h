/**
 * @authors Trung Tran | Nguyen Truong Giang - Try Hard Team - VT2 - PTIT
*/

#ifndef MPU6050_H
#define MPU6050_H

#include <stdio.h>
#include <stdint.h>

/* Define MPU-6050 register addresses */
#define MPU6050_REG_GYRO_CONFIG			0x1B
#define MPU6050_REG_ACCEL_CONFIG		0x1C
#define MPU6050_REG_POWER_PWR_MGMT_1	0x6B

/* Define MPU-6050 accelerometer register addresses */
#define MPU6050_REG_ACCEL_XOUT_H		0x3B
#define MPU6050_REG_ACCEL_XOUT_L		0x3C
#define MPU6050_REG_ACCEL_YOUT_H		0x3D
#define MPU6050_REG_ACCEL_YOUT_L		0x3E
#define MPU6050_REG_ACCEL_ZOUT_H		0x3F
#define MPU6050_REG_ACCEL_ZOUT_L		0x40

/* Define MPU-6050 gyroscope register addresses */
#define MPU6050_REG_GYRO_XOUT_H			0x43
#define MPU6050_REG_GYRO_XOUT_L			0x44
#define MPU6050_REG_GYRO_YOUT_H			0x45
#define MPU6050_REG_GYRO_YOUT_L			0x46
#define MPU6050_REG_GYRO_ZOUT_H			0x47
#define MPU6050_REG_GYRO_ZOUT_L			0x48

/* Define accelerometer sensitivity options */
#define AFS_SEL_0 16384
#define AFS_SEL_1 8192
#define AFS_SEL_2 4096
#define AFS_SEL_3 2048

/* Define gyroscope sensitivity options */
#define GFS_SEL_0 131
#define GFS_SEL_1 65.5
#define GFS_SEL_2 32.8
#define GFS_SEL_3 16.4

/* Define I2C slave address of MPU6050 sensor */
#define MPU6050_SLAVE_ADDR 0x68

#endif /* MPU6050_H */