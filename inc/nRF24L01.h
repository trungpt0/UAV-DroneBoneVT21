/**
 * @name: DroneBoneVT21
 * @version: 1.0
 * @file: nRF24L01.h
 * @authors: Trung Tran
 */

#ifndef NRF24L01_H
#define NRF24L01_H

#include <stdint.h>
#include <stdbool.h>

// Define the SPI commands for the nRF24L01
#define NRF24L01_R_REGISTER    0x00
#define NRF24L01_W_REGISTER    0x20
#define NRF24L01_R_RX_PAYLOAD  0x61
#define NRF24L01_W_TX_PAYLOAD  0xA0
#define NRF24L01_FLUSH_TX      0xE1
#define NRF24L01_FLUSH_RX      0xE2
#define NRF24L01_REUSE_TX_PL   0xE3
#define NRF24L01_NOP           0xFF

/* nRF24L01 Memory Map */
#define NRF24L01_CONFIG              0x00
#define NRF24L01_EN_AA               0x01
#define NRF24L01_EN_RXADDR           0x02
#define NRF24L01_SETUP_AW            0x03
#define NRF24L01_SETUP_RETR          0x04
#define NRF24L01_RF_CH               0x05
#define NRF24L01_RF_SETUP            0x06
#define NRF24L01_STATUS              0x07
#define NRF24L01_OBSERVE_TX          0x08
#define NRF24L01_CD                  0x09
#define NRF24L01_RX_ADDR_P0          0x0A
#define NRF24L01_RX_ADDR_P1          0x0B
#define NRF24L01_RX_ADDR_P2          0x0C
#define NRF24L01_RX_ADDR_P3          0x0D
#define NRF24L01_RX_ADDR_P4          0x0E
#define NRF24L01_RX_ADDR_P5          0x0F
#define NRF24L01_TX_ADDR             0x10
#define NRF24L01_RX_PW_P0            0x11
#define NRF24L01_RX_PW_P1            0x12
#define NRF24L01_RX_PW_P2            0x13
#define NRF24L01_RX_PW_P3            0x14
#define NRF24L01_RX_PW_P4            0x15
#define NRF24L01_RX_PW_P5            0x16
#define NRF24L01_FIFO_STATUS         0x17
#define NRF24L01_DYNPDc              0x1C
#define NRF24L01_FEATUREc            0x1D

// Function prototypes
void nRF24L01_init(void);
void nRF24L01_write_register(uint8_t reg, uint8_t value);
uint8_t nRF24L01_read_register(uint8_t reg);
void nRF24L01_write_payload(uint8_t* data, uint8_t length);
void nRF24L01_read_payload(uint8_t* data, uint8_t length);
void nRF24L01_receiver_mode(void);
void nRF24L01_receive_payload(uint8_t* data, uint8_t length);
void nRF24L01_transmitter_mode(void);
void nRF24L01_send_payload(uint8_t* data, uint8_t length);
void nRF24L01_flush_tx(void);
void nRF24L01_flush_rx(void);
void nRF24L01_send_command(uint8_t command);
void nRF24L01_close(void);

#endif // NRF24L01_H