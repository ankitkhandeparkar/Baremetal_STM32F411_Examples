/***********************************
 *
 *   Author : Ankit Khandeparkar
 *
 ***********************************/

#include "UART.h"
#include "stdarg.h"
#include "stdlib.h"
#include "stm32f4xx.h"
#include "string.h"

void uart_init(uint8_t uart, uint32_t clock, uint32_t baud, uint8_t txe, uint8_t rxe)
{
    // Select the baud rate in hex
    uint32_t br = (clock + (baud / 2)) / baud;

    // Enable clock for the UART and corresponding GPIO
    if (uart == UART1)
    {
        // GPIO clock
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
        // GPIO alternation function
        GPIOA->MODER |= (GPIO_MODER_MODER9_1 | GPIO_MODER_MODER10_1);
        GPIOA->MODER &= ~(GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0);
        GPIOA->AFR[1] |= 0X0770;

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
        // GPIO alternation function
        GPIOA->MODER |= (GPIO_MODER_MODER2_1 | GPIO_MODER_MODER3_1);
        GPIOA->MODER &= ~(GPIO_MODER_MODER2_0 | GPIO_MODER_MODE3_0);
        GPIOA->AFR[0] |= 0X7700;
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
        // GPIO alternation function
        GPIOA->MODER |= (GPIO_MODER_MODER11_1 | GPIO_MODER_MODER12_1);
        GPIOA->MODER &= ~(GPIO_MODER_MODER11_0 | GPIO_MODER_MODE12_0);
        GPIOA->AFR[1] |= 0X00088000;
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
        USART1->DR = (c & 0xFF);
        while (!(USART1->SR & USART_SR_TC))
            ;
        break;

    case UART2:
        USART2->DR = (c & 0xFF);
        while (!(USART2->SR & USART_SR_TC))
            ;
        break;

    case UART6:
        USART6->DR = (c & 0xFF);
        while (!(USART6->SR & USART_SR_TC))
            ;
        break;
    default:
        USART1->DR = (c & 0xFF);
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

void LOG(char *msg, ...) // pointer to char (msg) and "..." means undefined amount of arguments that user can pass
{
    // buffer to hold the message to be printted
    char buffer[250];

    va_list args;
    va_start(args, msg);         // extract all the arguments (eg: %d, %f) and re-format the msg
    vsprintf(buffer, msg, args); // put the re-formatted msg into the buffer

    // print the buffer character by character
    for (int i = 0; i < strlen(buffer); i++)
    {
        switch (uart_active_flag)
        {
        case UART1:
            USART1->DR = (buffer[i] & 0xFF);
            while (!(USART1->SR & USART_SR_TC))
                ;
            break;

        case UART2:
            USART2->DR = (buffer[i] & 0xFF);
            while (!(USART2->SR & USART_SR_TC))
                ;
            break;

        case UART6:
            USART6->DR = (buffer[i] & 0xFF);
            while (!(USART6->SR & USART_SR_TC))
                ;
            break;
        default:
            USART1->DR = (buffer[i] & 0xFF);
            while (!(USART1->SR & USART_SR_TC))
                ;
            break;
        }
    }
}