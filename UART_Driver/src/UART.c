/***********************************
 *
 *   Author : Ankit Khandeparkar
 *
 ***********************************/

#include "UART.h"
#include "stm32f4xx.h"

void uart_init(uint8_t uart, uint32_t baud, uint8_t txe, uint8_t rxe)
{
    // Select the baud rate in hex
    uint32_t br;
    switch (baud)
    {
    case BAUD9600:
        br = 0x0683;
        break;
    case BAUD115200:
        br = 0x008B;
        break;
    case BAUD256000:
        br = 0x0045;
        break;

    default:
        br = 0x0683;
        break;
    }

    // Enable clock for the UART and corresponding GPIO
    if (uart == UART1)
    {
        // GPIO clock
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
        // UART clock
        RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
        // Set baud rate
        USART1->BRR = br;
        // Enable / Disable TX and RX
        if (txe | rxe)
            USART1->CR1 |= (USART_CR1_TE | USART_CR1_RE);
        if (!txe)
            USART1->CR1 &= ~USART_CR1_TE;
        if (!rxe)
            USART1->CR1 &= ~USART_CR1_RE;
        // Enable UART
        USART1->CR1 |= USART_CR1_UE;
        // Set uart active flag
        uart_active_flag = UART1;
    }

    if (uart == UART2)
    {
        // GPIO clock
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
        // UART clock
        RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
        // Set baud rate
        USART2->BRR = br;
        // Enable / Disable TX and RX
        if (txe | rxe)
            USART2->CR1 |= (USART_CR1_TE | USART_CR1_RE);
        if (!txe)
            USART2->CR1 &= ~USART_CR1_TE;
        if (!rxe)
            USART2->CR1 &= ~USART_CR1_RE;
        // Enable UART
        USART2->CR1 |= USART_CR1_UE;
        // Set uart active flag
        uart_active_flag = UART2;
    }

    if (uart == UART6)
    {
        // GPIO clock
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
        // UART clock
        RCC->APB2ENR |= RCC_APB2ENR_USART6EN;
        // Set baud rate
        USART6->BRR = br;
        // Enable / Disable TX and RX
        if (txe | rxe)
            USART6->CR1 |= (USART_CR1_TE | USART_CR1_RE);
        if (!txe)
            USART6->CR1 &= ~USART_CR1_TE;
        if (!rxe)
            USART6->CR1 &= ~USART_CR1_RE;
        // Enable UART
        USART6->CR1 |= USART_CR1_UE;
        // Set uart active flag
        uart_active_flag = UART6;
    }
}

void send(int c)
{
    switch (uart_active_flag)
    {
    case UART1:
        USART1->DR = (c && 0xFF);
        while (!(USART1->SR & USART_SR_TC))
            ;
        break;

    case UART2:
        USART2->DR = (c && 0xFF);
        while (!(USART2->SR & USART_SR_TC))
            ;
        break;

    case UART6:
        USART6->DR = (c && 0xFF);
        while (!(USART6->SR & USART_SR_TC))
            ;
        break;
    default:
        USART1->DR = (c && 0xFF);
        while (!(USART1->SR & USART_SR_TC))
            ;
        break;
    }
}

char recieve(void)
{
    char c;
    switch (uart_active_flag)
    {
    case UART1:
        while (!(USART1->SR & USART_SR_RXNE))
            ;
        c = USART1->DR;
        return c;
        break;

    case UART2:
        while (!(USART2->SR & USART_SR_RXNE))
            ;
        c = USART2->DR;
        return c;
        break;

    case UART6:
        while (!(USART6->SR & USART_SR_RXNE))
            ;
        c = USART6->DR;
        return c;
        break;
    default:
        while (!(USART1->SR & USART_SR_RXNE))
            ;
        c = USART1->DR;
        return c;
        break;
    }
}

void uart_rx_tx(void)
{
    char c;
    switch (uart_active_flag)
    {
    case UART1:
        while (!(USART1->SR & USART_SR_RXNE))
            ;
        c = USART1->DR;
        USART1->DR = c;
        while (!(USART1->SR & USART_SR_TC))
            ;
        break;

    case UART2:
        while (!(USART2->SR & USART_SR_RXNE))
            ;
        c = USART2->DR;
        USART2->DR = c;
        while (!(USART2->SR & USART_SR_TC))
            ;
        break;

    case UART6:
        while (!(USART6->SR & USART_SR_RXNE))
            ;
        c = USART6->DR;
        USART6->DR = c;
        while (!(USART6->SR & USART_SR_TC))
            ;
        break;
    default:
        while (!(USART1->SR & USART_SR_RXNE))
            ;
        c = USART1->DR;
        USART1->DR = c;
        while (!(USART1->SR & USART_SR_TC))
            ;
        break;
    }
}