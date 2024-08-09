#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>

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

#define MPU6050_DEVICE_FILE "/dev/mpu6050_dev"

int main()
{
    int fd;
    int acc_value[3], gyr_value[3];
    char data[14];
    double acc_x, acc_y, acc_z, gyr_x, gyr_y, gyr_z;

    if (fd = open(MPU6050_DEVICE_FILE, O_RDWR) < 0) {
        printf("Failed to open MPU6050 device file!\n");
        return -1;
    }

    while (1) {
        if (read(fd, data, 14) != 14) {
            perror("Failed to read data from the device!\n");
            close(fd);
            return 1;
        }

        acc_value[0] = (int) ((data[0] << 8) + data[1]);
        acc_value[1] = (int) ((data[2] << 8) + data[3]);
        acc_value[2] = (int) ((data[4] << 8) + data[5]);

        gyr_value[0] = (int) ((data[8] << 8) + data[8]);
        gyr_value[1] = (int) ((data[10] << 8) + data[11]);
        gyr_value[2] = (int) ((data[12] << 8) + data[13]);

        acc_x = (double) acc_value[0] / AFS_SEL_0;
        acc_y = (double) acc_value[1] / AFS_SEL_0;
        acc_z = (double) acc_value[2] / AFS_SEL_0;

        gyr_x = (double) gyr_value[0] / GFS_SEL_0;
        gyr_y = (double) gyr_value[1] / GFS_SEL_0;
        gyr_z = (double) gyr_value[2] / GFS_SEL_0;

	    printf("Acceleration X: %.2f   Acceleration Y: %.2f   Acceleration Z: %.2f\n", acc_x, acc_y, acc_z);
        printf("Gyroscope X: %.2f   Gyroscope Y: %.2f   Gyroscope Z: %.2f\n", gyr_x, gyr_y, gyr_z);

        usleep(100 * 1000);
    }

    close(fd);
    return 0;
}
