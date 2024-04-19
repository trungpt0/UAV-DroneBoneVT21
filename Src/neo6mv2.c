/**
 * @authors Trung Tran | Nguyen Ngoc Tri - Try Hard Team - VT2 - PTIT
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>

#include "/home/bbb/UAV-DroneBoneVT21/Driver/GPSSystem/neo6mv2.h"

/**
 * Open UART for GPS
*/
int openGPS()
{
    return open(GPS_DEVICE, O_RDWR);
}

/**
 * Close UART for GPS
*/
void closeGPS(int fd)
{
    close(fd);
}

/**
 * Function to configure UART settings
*/
void configureUART(int fd)
{
    struct termios options;
    tcgetattr(fd, &options);
    options.c_cflag = B9600 | CS8 | CREAD | CLOCAL;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(fd, TCIFLUSH);
    tcsetattr(fd, TCSANOW, &options);
}

/**
 * Read UART for GPS
*/
int readGPS(int fd, char *buffer, size_t size)
{
    return read(fd, buffer, size);
}