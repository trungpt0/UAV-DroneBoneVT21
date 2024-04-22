/**
 * @name: DroneBoneVT21
 * @authors: Trung Tran | Bao Huynh | Giang Nguyen | Tien Tran | Tri Nguyen - Try Hard Team - VT2 - PTIT
 * @version: 1.0
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "/home/bbb/UAV-DroneBoneVT21/Driver/MotorSystem/motor.h"
#include "/home/bbb/UAV-DroneBoneVT21/Driver/SensorSystem/mpu6050.h"
#include "/home/bbb/UAV-DroneBoneVT21/Driver/GPSSystem/neo6mv2.h"

#define MAX_VALUE 50

#define I2C_DEVICE_FILE "/dev/i2c-2"

int fd;

/* The MPU6050 processing functions */
int mpu6050_write(uint8_t addr, uint8_t data);
int mpu6050_read(uint8_t base_addr, char *pbuffer, int len);
void mpu6050_init();
void mpu6050_read_acc(short int *pbuffer);
void mpu6050_read_gyr(short int *pbuffer);

int main()
{
	short acc_value[3];
	short gyr_value[3];
	double accx, accy, accz, gyrx, gyry, gyrz;

	/* Open I2C device file */
	if ((fd = open(I2C_DEVICE_FILE, O_RDWR)) < 0) {
		perror("Failed to open I2C device file.\n");
    	return -1;
	}

	/* Set I2C slave address */
	if (ioctl(fd, I2C_SLAVE, MPU6050_SLAVE_ADDR) < 0) {
		perror("Failed to set I2C slave address.\n");
		close(fd);
		return -1;
	}

	/* Initialize MPU6050 */
	mpu6050_init();

	while (1)
	{
		/* Read accelerometer and gyroscope data */
		mpu6050_read_acc(acc_value);
		mpu6050_read_gyr(gyr_value);

		/* Convert raw data to actual values */
		accx = (double) acc_value[0]/AFS_SEL_0;
		accy = (double) acc_value[1]/AFS_SEL_0;
		accz = (double) acc_value[2]/AFS_SEL_0;

		gyrx = (double) gyr_value[0]/GFS_SEL_0;
		gyry = (double) gyr_value[1]/GFS_SEL_0;
		gyrz = (double) gyr_value[2]/GFS_SEL_0;

		printf("Acc(raw) = X:%d   Y:%d   Z:%d, Gyr(raw) = X:%d   Y:%d   Z:%d\n", 
			acc_value[0], acc_value[1], acc_value[2],
			gyr_value[0], gyr_value[1], gyr_value[2]
		);

		printf("Acc(g) = X:%.2f   Y:%.2f   Z:%.2f, Gyr(g) = X:%.2f   Y:%.2f   Z:%.2f\n", 
			accx, accy, accz,
			gyrx, gyry, gyrz
		);

		usleep(50 * 1000);
	}
	return 0;
}

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