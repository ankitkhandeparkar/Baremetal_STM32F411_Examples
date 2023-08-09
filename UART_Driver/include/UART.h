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

#define BAUD9600 9600
#define BAUD115200 115200
#define BAUD256000 256000

uint8_t uart_active_flag;

void uart_init(uint8_t uart, uint32_t baud, uint8_t txe, uint8_t rxe);
void send(int c);
char recieve(void);
void uart_rx_tx(void);

#endif /* UART_H */
