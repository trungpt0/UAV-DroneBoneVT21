/**
 * @name: DroneBoneVT21
 * @version: 1.0
 * @file: neo6mv2.h
 * @authors: Trung Tran | Tri Nguyen
 */

#ifndef NEO6MV2_H
#define NEO6MV2_H

#include <unistd.h>

#define UART_DEVICE "/dev/tty01" // UART1 on BeagleBone Black

int gps_init();
void gps_close(int uart_fd);
int gps_read(int uart_fd, char *buffer, size_t buffer_size);

#endif /* NEO6MV2_H */