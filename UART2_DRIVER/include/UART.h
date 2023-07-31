#ifndef UART_H
#define UART_H

#include <stdint.h>

void UART2_Init(uint32_t clock, uint32_t baudrate);
void UART_read_write(void);
void UART_write(int ch);

#endif