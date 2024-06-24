/**
 * @name: DroneBoneVT21
 * @version: 1.0
 * @file: mpu6050.c
 * @authors: Trung Tran | Giang Nguyen
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#include "/home/bbb/UAV-DroneBoneVT21/Driver/mpu6050.h"

int fd;

/* Function to write data to MPU6050 */
int mpu6050_write(uint8_t addr, uint8_t data)
{
	int ret;
	char buf[2];
	buf[0] = addr;
	buf[1] = data;
	ret = write(fd, buf, 2);
	if (ret != 2) {
		perror("Write failed!\n");
		return -1;
	}
	return 0;
}

/* Function to read data from MPU6050 */
int mpu6050_read(uint8_t base_addr, char *pbuffer, int len)
{
	int ret;
	char buf[2];
	buf[0] = base_addr;
	ret = write(fd, buf, 1);
	if (ret != 1) {
		perror("Write failed!\n");
		return -1;
	}

	ret = read(fd, pbuffer, len);
	if (ret != len) {
		perror("Read failed!\n");
		return -1;
	}
	return 0;
}

/* Function to initialize MPU6050 */
void mpu6050_init()
{
	mpu6050_write(MPU6050_REG_POWER_PWR_MGMT_1, 0x00);
	usleep(500);
	mpu6050_write(MPU6050_REG_ACCEL_CONFIG, 0x00);
	usleep(500);
	mpu6050_write(MPU6050_REG_GYRO_CONFIG, 0x00);
	usleep(500);
}

/* Function to read accelerometer data */
void mpu6050_read_acc(short int *pbuffer)
{
	char acc_buffer[6];
	mpu6050_read(MPU6050_REG_ACCEL_XOUT_H, acc_buffer, 6);

	pbuffer[0] = (int) ((acc_buffer[0] << 8) + acc_buffer[1]);
	pbuffer[1] = (int) ((acc_buffer[2] << 8) + acc_buffer[3]);
	pbuffer[2] = (int) ((acc_buffer[4] << 8) + acc_buffer[5]);
}

/* Function to read gyroscope data */
void mpu6050_read_gyr(short int *pbuffer)
{
	char gyr_buffer[6];
	mpu6050_read(MPU6050_REG_GYRO_XOUT_H, gyr_buffer, 6);

	pbuffer[0] = (int) ((gyr_buffer[0] << 8) + gyr_buffer[1]);
	pbuffer[1] = (int) ((gyr_buffer[2] << 8) + gyr_buffer[3]);
	pbuffer[2] = (int) ((gyr_buffer[4] << 8) + gyr_buffer[5]);
}