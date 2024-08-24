/**
 * @name: DroneBoneVT21
 * @version: 1.0
 * @file: mpu6050.c
 * @authors: Trung Tran | Giang Nguyen
 * 
 * License: GPL
 * 
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#include "/home/bbb/UAV-DroneBoneVT21/inc/nRF24L01.h"
#include "/home/bbb/UAV-DroneBoneVT21/inc/gpio_config.h"
//#include "gpio_config.c"

#define NRF24L01_CE_PIN     15
#define NRF24L01_CSN_PIN    14

#define SPI_DEV "/dev/spidev1.0"

#define NRF24L01_CE_HIGH() gpio_set_value(NRF24L01_CE_PIN, 1)
#define NRF24L01_CE_LOW() gpio_set_value(NRF24L01_CE_PIN, 0)
#define NRF24L01_CSN_HIGH() gpio_set_value(NRF24L01_CSN_PIN, 1)
#define NRF24L01_CSN_LOW() gpio_set_value(NRF24L01_CSN_PIN, 0)

int spi_fd;

void spi_init(int *spi_fd, const char *device)
{
    *spi_fd = open(device, O_RDWR);
    if (*spi_fd < 0) {
        perror("open spi device failed\n");
    }

    uint8_t mode = SPI_MODE_0;
    ioctl(*spi_fd, SPI_IOC_WR_MODE, &mode);
    uint32_t speed = 500000;
    ioctl(*spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
}

uint8_t spi_transfer(int spi_fd, uint8_t data)
{
    uint8_t rx;
    struct spi_ioc_transfer sit = {
        .tx_buf = (unsigned long)&data,
        .rx_buf = (unsigned long)&rx,
        .len = 1,
        .speed_hz = 500000,
        .bits_per_word = 8,
    };
    ioctl(spi_fd, SPI_IOC_MESSAGE(1), &sit);
    return rx;
}

void spi_close(int spi_fd)
{
    close(spi_fd);
}

void nRF24L01_init(void)
{
    gpio_export(NRF24L01_CE_PIN);
    gpio_direction(NRF24L01_CE_PIN, "out");
    gpio_export(NRF24L01_CSN_PIN);
    gpio_direction(NRF24L01_CSN_PIN, "out");

    NRF24L01_CE_LOW();
    NRF24L01_CSN_HIGH();

    spi_init(&spi_fd, SPI_DEV);
}

void nRF24L01_write_register(uint8_t reg, uint8_t value)
{
    NRF24L01_CSN_LOW();
    spi_transfer(spi_fd, NRF24L01_W_REGISTER | (reg & 0x1F));
    spi_transfer(spi_fd, value);
    NRF24L01_CSN_HIGH();
}

uint8_t nRF24L01_read_register(uint8_t reg)
{
    uint8_t res;
    NRF24L01_CSN_LOW();
    spi_transfer(spi_fd, NRF24L01_R_REGISTER | (reg & 0x1F));
    res = spi_transfer(spi_fd, NRF24L01_NOP);
    NRF24L01_CSN_HIGH();
    return res;
}

void nRF24L01_write_payload(uint8_t* data, uint8_t length)
{
    NRF24L01_CSN_LOW();
    spi_transfer(spi_fd, NRF24L01_W_TX_PAYLOAD);
    for (uint8_t i = 0; i < length; i++) {
        spi_transfer(spi_fd, data[i]);
    }
    NRF24L01_CSN_HIGH();
}

void nRF24L01_read_payload(uint8_t* data, uint8_t length)
{
    NRF24L01_CSN_LOW();
    spi_transfer(spi_fd, NRF24L01_W_TX_PAYLOAD);
    for (uint8_t i = 0; i < length; i++) {
        data[i] = spi_transfer(spi_fd, NRF24L01_NOP);
    }
    NRF24L01_CSN_HIGH();
}

void nRF24L01_receiver_mode(void)
{
    nRF24L01_write_register(0x00, (nRF24L01_read_register(0x00) | NRF24L01_EN_AA));

    uint8_t rx_address[5] = { 0xE7, 0xE7, 0xE7, 0xE7, 0xE7 };
    NRF24L01_CSN_LOW();
    spi_transfer(spi_fd, NRF24L01_W_REGISTER | NRF24L01_RX_ADDR_P0);
    for (uint8_t i = 0; i < 5; i++) {
        spi_transfer(spi_fd, rx_address[i]);
    }
    NRF24L01_CSN_HIGH();
    NRF24L01_CE_HIGH();
}

void nRF24L01_receive_payload(uint8_t* data, uint8_t length)
{
    uint8_t status;
    do {
        status = nRF24L01_read_register(NRF24L01_STATUS);
    } while (!(status & 0x40));

    nRF24L01_read_payload(data, length);
    nRF24L01_write_register(NRF24L01_STATUS, 0x40);
}

void nRF24L01_transmitter_mode(void)
{
    nRF24L01_write_register(0x00, (nRF24L01_read_register(0x00) | NRF24L01_EN_RXADDR));
    uint8_t tx_address[5] = { 0xE7, 0xE7, 0xE7, 0xE7, 0xE7 };
    NRF24L01_CSN_LOW();
    spi_transfer(spi_fd, NRF24L01_W_REGISTER | NRF24L01_TX_ADDR);
    for (uint8_t i = 0; i < 5; i++) {
        spi_transfer(spi_fd, tx_address[i]);
    }
    NRF24L01_CSN_HIGH();
    NRF24L01_CE_LOW();
}

void nRF24L01_send_payload(uint8_t* data, uint8_t length)
{
    NRF24L01_CE_LOW();
    nRF24L01_flush_tx();
    nRF24L01_write_payload(data, length);
    NRF24L01_CE_HIGH();
    usleep(10);
    NRF24L01_CE_LOW();
}

void nRF24L01_send_command(uint8_t command)
{
    NRF24L01_CSN_LOW();
    spi_transfer(spi_fd, command);
    NRF24L01_CSN_HIGH();
}

void nRF24L01_flush_tx(void)
{
    nRF24L01_send_command(NRF24L01_FLUSH_TX);
}

void nRF24L01_flush_rx(void)
{
    nRF24L01_send_command(NRF24L01_FLUSH_RX);
}

void nRF24L01_close(void)
{
    spi_close(spi_fd);
}