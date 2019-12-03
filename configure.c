#include <delay.h>
#include <stm32.h>
#include "configure.h"

void configureUSART()
{
    GPIOafConfigure(GPIOA, 2, GPIO_OType_PP, GPIO_Fast_Speed, GPIO_PuPd_NOPULL, GPIO_AF_USART2);
    GPIOafConfigure(GPIOA, 3, GPIO_OType_PP, GPIO_Fast_Speed, GPIO_PuPd_UP, GPIO_AF_USART2);

    USART2->CR1 = USART_CR1_TE;
    USART2->CR2 = 0;
    uint32_t const baudrate = 9600U;
    USART2->BRR = (PCLK1_HZ + (baudrate / 2U)) / baudrate;
    USART2->CR3 = USART_CR3_DMAT;

    // USART Enabling
    USART2->CR1 |= USART_CR1_UE;
}

void configureNVIC()
{
    NVIC_EnableIRQ(EXTI15_10_IRQn);

    NVIC_EnableIRQ(DMA1_Stream6_IRQn);

    NVIC_EnableIRQ(I2C1_EV_IRQn);
    NVIC_EnableIRQ(I2C1_ER_IRQn);
}

void configureDMA()
{
    DMA1_Stream6->CR = 4U << 25 |
        DMA_SxCR_PL_1 |
        DMA_SxCR_MINC |
        DMA_SxCR_DIR_0 |
        DMA_SxCR_TCIE;
    DMA1_Stream6->PAR = (uint32_t)&USART2->DR;

    DMA1->HIFCR = DMA_HIFCR_CTCIF6;
}

void configureI2C() {
    GPIOafConfigure(GPIOB, 8, GPIO_OType_OD, GPIO_Low_Speed, GPIO_PuPd_NOPULL, GPIO_AF_I2C1);
    GPIOafConfigure(GPIOB, 9, GPIO_OType_OD, GPIO_Low_Speed, GPIO_PuPd_NOPULL, GPIO_AF_I2C1);

    I2C1->CR1 = 0;

    I2C1->CR2 = PCLK1_MHZ;

    I2C1->CR1 |= I2C_CR1_PE;

    // CTRL_REG1 0
    {
        I2C1->CR1 |= I2C_CR1_START;
        
        while (!(I2C1->SR1 & I2C_SR1_SB))
        {
            continue;
        }


        while (!(I2C1->SR1 & I2C_SR1_ADDR))
        {
            continue;
        }
        I2C1->SR2;

        uint8_t reg = 0x20;
        I2C1->DR = reg;

        while (!(I2C1->SR1 & I2C_SR1_TXE))
        {
            continue;
        }

        // ENABLED uint8_t value = 0b01000111; // ENABLED 
        uint8_t value = 0b00000000;
        I2C1->DR = value;

        while (!(I2C1->SR1 & I2C_SR1_BTF))
        {
            continue;
        }
        I2C1->CR1 |= I2C_CR1_STOP;
    }

    Delay(10000);

    // CTRL_REG3 0
    {
        I2C1->CR1 |= I2C_CR1_START;
        
        while (!(I2C1->SR1 & I2C_SR1_SB))
        {
            continue;
        }


        while (!(I2C1->SR1 & I2C_SR1_ADDR))
        {
            continue;
        }
        I2C1->SR2;

        uint8_t reg = 0x22;
        I2C1->DR = reg;

        while (!(I2C1->SR1 & I2C_SR1_TXE))
        {
            continue;
        }

        // ENABLED uint8_t value = 0b01000111; // ENABLED 
        uint8_t value = 0b00000000;
        I2C1->DR = value;

        while (!(I2C1->SR1 & I2C_SR1_BTF))
        {
            continue;
        }
        I2C1->CR1 |= I2C_CR1_STOP;
    }

    Delay(10000);

    // CTRL_REG1 0
    {
        I2C1->CR1 |= I2C_CR1_START;
        
        while (!(I2C1->SR1 & I2C_SR1_SB))
        {
            continue;
        }


        while (!(I2C1->SR1 & I2C_SR1_ADDR))
        {
            continue;
        }
        I2C1->SR2;

        uint8_t reg = 0x20;
        I2C1->DR = reg;

        while (!(I2C1->SR1 & I2C_SR1_TXE))
        {
            continue;
        }

        uint8_t value = 0b01000111; // ENABLED 
        I2C1->DR = value;

        while (!(I2C1->SR1 & I2C_SR1_BTF))
        {
            continue;
        }
        I2C1->CR1 |= I2C_CR1_STOP;
    }

    Delay(10000);

    // CTRL_REG3 0
    {
        I2C1->CR1 |= I2C_CR1_START;
        
        while (!(I2C1->SR1 & I2C_SR1_SB))
        {
            continue;
        }


        while (!(I2C1->SR1 & I2C_SR1_ADDR))
        {
            continue;
        }
        I2C1->SR2;

        uint8_t reg = 0x22;
        I2C1->DR = reg;

        while (!(I2C1->SR1 & I2C_SR1_TXE))
        {
            continue;
        }

        // ENABLED uint8_t value = 0b01000111; // ENABLED 
        uint8_t value = 0b00000100;
        I2C1->DR = value;

        while (!(I2C1->SR1 & I2C_SR1_BTF))
        {
            continue;
        }
        I2C1->CR1 |= I2C_CR1_STOP;
    }
}