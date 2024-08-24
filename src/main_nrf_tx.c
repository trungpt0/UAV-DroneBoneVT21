#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "/home/bbb/UAV-DroneBoneVT21/inc/nRF24L01.h"

int main() {
    nRF24L01_init();
    nRF24L01_transmitter_mode();

    char user_input[3];

    while (1) {
        scanf("%3s", user_input);
        nRF24L01_send_payload((uint8_t*)user_input, 3);
        printf("%s send ok\n", user_input);

        usleep(100000);
    }

    nRF24L01_close();
    return 0;
}