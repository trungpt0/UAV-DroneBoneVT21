/**
 * @author Trung Tran - Try Hard Team - VT2 - PTIT
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdint.h>

#include "/home/bbb/UAV-Projects/DroneBoneVT21/Driver/MotorSystem/motor.h"
#include "/home/bbb/UAV-Projects/DroneBoneVT21/Driver/SensorSystem/mpu9250.h"
#include "/home/bbb/UAV-Projects/DroneBoneVT21/Driver/GPSSystem/neo6mv2.h"

int main()
{
	/* Motor System */
	int motor_pin1 = 17;
	int motor_pin2 = 18;

	printf("Motor is moving ahead...\n");
	control_motor(motor_pin1, motor_pin2, 1);
	sleep(1);

	printf("Motor stoped!\n");
	control_motor(motor_pin1, motor_pin2, 0);

	/* Sensor System */
	int16_t ax, ay, az, gx, gy, gz;

	if (mpu9250_init() == -1) {
		return 1;
	}

	/* GPS System */
	int fd;
	char buffer[256];

	fd = openGPS(); // Open GPS
	if (fd == -1) {
		perror("Cannot open UART device!\n");
		return 1;
	}

	configureUART(fd); // Config UART

	while (1)
	{
		/* Get data from MPU9250*/
		if (mpu9250_read_all(&ax, &ay, &az, &gx, &gy, &gz) == -1) {
			return 1;
		}
		printf("Acceleration: x = %d y = %d z = %d\n", ax, ay, az);
		printf("Gyroscope: x = %d y = %d z = %d\n", gx, gy, gz);
		sleep(1/100000);

		/* Get data from GPS */
		memset(buffer, 0, sizeof(buffer));
		if (readGPS(fd, buffer, sizeof(buffer)) != -1) {
			printf("GPS: %s\n", buffer);
		} else {
			perror("Cannot read data from GPS!\n");
			closeGPS(fd); // Close GPS
			return 1;
		}
	}

	closeGPS(fd); // Close GPS
	return 0;
}