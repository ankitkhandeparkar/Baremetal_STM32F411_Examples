#include "UART.h"
#include "stm32f4xx.h"
#include <stdint.h>

void UART2_Init(uint32_t clock, uint32_t baudrate)
{
    /********** PORT A *********/
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Enable clock
    GPIOA->MODER |= 0x00A0;              // Set Mode to Alternate Function (Pin 2 and 3)
    GPIOA->AFR[0] |= 0x7700;             // Set AF7 (0b0111) to AFRL2 and AFRL3 ( AFR[0] => AFR Low Register )

    /********** UART 2 *********/
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;               // Enable clock
    uint16_t brr = (clock + (baudrate / 2)) / baudrate; // Calulate baudrate
    USART2->BRR = brr;                                  // Set Baud rate

    //   ENABLE      RECIEVE        TRANSMIT      UART
    USART2->CR1 = USART_CR1_RE | USART_CR1_TE | USART_CR1_UE;
}

void UART_read_write(void)
{
    // Polling on status register to check if we recieve data
    if (USART2->SR & USART_SR_RXNE)
    {
        char ch = USART2->DR;               // Storing the recieved data in a variable
        USART2->DR = (ch & 0xFF);           // Sending (Printing) the recieved data to the data register
        while (!(USART2->SR & USART_SR_TC)) // Waiting while the UART transmission is completed
            ;
    }
}

void UART_write(int ch)
{
    USART2->DR = (ch & 0xFF);           // Printing the data
    while (!(USART2->SR & USART_SR_TC)) // Waiting while the UART transmission is completed
        ;
}