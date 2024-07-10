/**
 * @author Trung Tran - Try Hard Team - VT2 - PTIT
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_BUF_SIZE 1024

int8_t write_buf[1024]; // Buffer for writing data
int8_t read_buf[1024]; // Buffer for reading data

int main()
{
    int fd; // File descriptor for the device file
    char option; // Option selected by the user
    
    // Open the device file
    printf("***********************\n");
    printf("*****DroneBoneVT21*****\n");

    fd = open("/dev/dronebonevt21_dev", O_RDWR);
    if (fd < 0) {
        printf("Open DroneBoneVT21 Device File Failed!\n");
        return 0;
    }

    // Main loop for user interaction
    while (1)
    {
        printf("*****Enter Your Option*****\n");
        printf("     1. Write     \n");
        printf("     2. Read      \n");
        printf("     3. Exit      \n");
        printf("***************************\n");
        scanf(" %c", &option);
        printf("Your Option = %c\n", option);

        // Handle user options
        switch (option)
        {
        case '1':
            printf("Enter the string to write into DroneBoneVT21 device file: ");
            scanf(" %[^\t\n]s", write_buf);
            printf("Data Writing...");
            write(fd, write_buf, strlen(write_buf) + 1);
            printf("Done!\n");
            break;

        case '2':
            printf("Data Reading...");
            read(fd, read_buf, MAX_BUF_SIZE);
            printf("Done!\n");
            printf("Data = %s\n", read_buf);
            break;

        case '3':
            close(fd);
            exit(1);
            break;
        default:
            printf("Choose option failed: %c\n", option);
            break;
        }
    }
    
    close(fd);
    return 0;
}