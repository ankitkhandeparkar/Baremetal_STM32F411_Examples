/***********************************
 *
 *   Author : Ankit Khandeparkar
 *
 ***********************************/

#ifndef UART_H
#define UART_H

#include "stm32f4xx.h"

#define UART1 0x01
#define UART2 0x02
#define UART6 0x03

#define TX_ENABLE 1
#define RX_ENABLE 1

#define TX_DISABLE 0
#define RX_DISABLE 0

#define BAUD9600 9600UL
#define BAUD115200 115200UL
#define BAUD256000 256000UL

#define INTERNAL_CLOCK 16000000UL
#define EXTERNAL_CLOCK 96000000UL

uint8_t uart_active_flag;

void uart_init(uint8_t uart, uint32_t clock, uint32_t baud, uint8_t txe, uint8_t rxe);
void send(int c);
char recieve(void);
void uart_rx_tx(void);
void LOG(char *msg, ...);

#endif /* UART_H */
