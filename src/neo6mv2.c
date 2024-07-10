/**
 * @name: DroneBoneVT21
 * @version: 1.0
 * @file: neo6mv2.c
 * @authors: Trung Tran | Tri Nguyen
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <errno.h>

#include "/home/bbb/UAV-DroneBoneVT21/inc/neo6mv2.h"

int gps_init()
{
    int uart_fd = open(UART_DEVICE, O_RDWR | O_NOCTTY | O_NDELAY);
    if (uart_fd == -1) {
        perror("Unable to open UART");
        return -1;
    }

    struct termios options;
    tcgetattr(uart_fd, &options);
    options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart_fd, TCIFLUSH);
    tcsetattr(uart_fd, TCSANOW, &options);

    return uart_fd;
}

void gps_close(int uart_fd)
{
    close(uart_fd);
}

int gps_read(int uart_fd, char *buffer, size_t buffer_size)
{
    int bytes_read = read(uart_fd, buffer, buffer_size);
    if (bytes_read < 0) {
        perror("Failed to read from the UART");
        return -1;
    }
    return bytes_read;
}