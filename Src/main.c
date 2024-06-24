/**
 * @name: DroneBoneVT21
 * @version: 1.0
 * @file: main.c
 * @authors: Trung Tran | Bao Huynh | Giang Nguyen | Tien Tran | Tri Nguyen - ETPC - VT2 - PTIT
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>

#include "/home/bbb/UAV-DroneBoneVT21/Driver/mpu6050.h"

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