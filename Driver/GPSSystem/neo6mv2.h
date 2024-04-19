/**
 * @authors Trung Tran | Nguyen Ngoc Tri - Try Hard Team - VT2 - PTIT
*/

#ifndef NEO_H
#define NEO_H

#include <unistd.h>

#define GPS_DEVICE "/dev/ttyS1" // Path to the GPS UART device

/**
 * Prototypes in neo6mv2.c
*/
int openGPS();
void closeGPS(int fd);
void configureUART(int fd);
int readGPS(int fd, char *buffer, size_t size);

#endif /* NEO_H */