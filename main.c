#include <gpio.h>
#include <stm32.h>
#include <delay.h>
#include <string.h>
#include "queue.h"
#include "button.h"
#include "configure.h"

Queue tx_buffer;
Button fire_button = {13, GPIOC, "P\r\n",  "F\r\n", 0};

#define RED_LED_GPIO GPIOA
#define RED_LED_PIN 6

#define RedLEDon() \
    RED_LED_GPIO->BSRR = 1 << (RED_LED_PIN + 16)
#define RedLEDoff() \
    RED_LED_GPIO->BSRR = 1 << RED_LED_PIN


char *tab[256] = {
    "0\r\n",   
"1\r\n",   
"2\r\n",   
"3\r\n",   
"4\r\n",   
"5\r\n",   
"6\r\n",   
"7\r\n",   
"8\r\n",   
"9\r\n",   
"10\r\n",   
"11\r\n",   
"12\r\n",   
"13\r\n",   
"14\r\n",   
"15\r\n",   
"16\r\n",   
"17\r\n",   
"18\r\n",   
"19\r\n",   
"20\r\n",   
"21\r\n",   
"22\r\n",   
"23\r\n",   
"24\r\n",   
"25\r\n",   
"26\r\n",   
"27\r\n",   
"28\r\n",   
"29\r\n",   
"30\r\n",   
"31\r\n",   
"32\r\n",   
"33\r\n",   
"34\r\n",   
"35\r\n",   
"36\r\n",   
"37\r\n",   
"38\r\n",   
"39\r\n",   
"40\r\n",   
"41\r\n",   
"42\r\n",   
"43\r\n",   
"44\r\n",   
"45\r\n",   
"46\r\n",   
"47\r\n",   
"48\r\n",   
"49\r\n",   
"50\r\n",   
"51\r\n",   
"52\r\n",   
"53\r\n",   
"54\r\n",   
"55\r\n",   
"56\r\n",   
"57\r\n",   
"58\r\n",   
"59\r\n",   
"60\r\n",   
"61\r\n",   
"62\r\n",   
"63\r\n",   
"64\r\n",   
"65\r\n",   
"66\r\n",   
"67\r\n",   
"68\r\n",   
"69\r\n",   
"70\r\n",   
"71\r\n",   
"72\r\n",   
"73\r\n",   
"74\r\n",   
"75\r\n",   
"76\r\n",   
"77\r\n",   
"78\r\n",   
"79\r\n",   
"80\r\n",   
"81\r\n",   
"82\r\n",   
"83\r\n",   
"84\r\n",   
"85\r\n",   
"86\r\n",   
"87\r\n",   
"88\r\n",   
"89\r\n",   
"90\r\n",   
"91\r\n",   
"92\r\n",   
"93\r\n",   
"94\r\n",   
"95\r\n",   
"96\r\n",   
"97\r\n",   
"98\r\n",   
"99\r\n",   
"100\r\n",   
"101\r\n",   
"102\r\n",   
"103\r\n",   
"104\r\n",   
"105\r\n",   
"106\r\n",   
"107\r\n",   
"108\r\n",   
"109\r\n",   
"110\r\n",   
"111\r\n",   
"112\r\n",   
"113\r\n",   
"114\r\n",   
"115\r\n",   
"116\r\n",   
"117\r\n",   
"118\r\n",   
"119\r\n",   
"120\r\n",   
"121\r\n",   
"122\r\n",   
"123\r\n",   
"124\r\n",   
"125\r\n",   
"126\r\n",   
"127\r\n",   
"128\r\n",   
"129\r\n",   
"130\r\n",   
"131\r\n",   
"132\r\n",   
"133\r\n",   
"134\r\n",   
"135\r\n",   
"136\r\n",   
"137\r\n",   
"138\r\n",   
"139\r\n",   
"140\r\n",   
"141\r\n",   
"142\r\n",   
"143\r\n",   
"144\r\n",   
"145\r\n",   
"146\r\n",   
"147\r\n",   
"148\r\n",   
"149\r\n",   
"150\r\n",   
"151\r\n",   
"152\r\n",   
"153\r\n",   
"154\r\n",   
"155\r\n",   
"156\r\n",   
"157\r\n",   
"158\r\n",   
"159\r\n",   
"160\r\n",   
"161\r\n",   
"162\r\n",   
"163\r\n",   
"164\r\n",   
"165\r\n",   
"166\r\n",   
"167\r\n",   
"168\r\n",   
"169\r\n",   
"170\r\n",   
"171\r\n",   
"172\r\n",   
"173\r\n",   
"174\r\n",   
"175\r\n",   
"176\r\n",   
"177\r\n",   
"178\r\n",   
"179\r\n",   
"180\r\n",   
"181\r\n",   
"182\r\n",   
"183\r\n",   
"184\r\n",   
"185\r\n",   
"186\r\n",   
"187\r\n",   
"188\r\n",   
"189\r\n",   
"190\r\n",   
"191\r\n",   
"192\r\n",   
"193\r\n",   
"194\r\n",   
"195\r\n",   
"196\r\n",   
"197\r\n",   
"198\r\n",   
"199\r\n",   
"200\r\n",   
"201\r\n",   
"202\r\n",   
"203\r\n",   
"204\r\n",   
"205\r\n",   
"206\r\n",   
"207\r\n",   
"208\r\n",   
"209\r\n",   
"210\r\n",   
"211\r\n",   
"212\r\n",   
"213\r\n",   
"214\r\n",   
"215\r\n",   
"216\r\n",   
"217\r\n",   
"218\r\n",   
"219\r\n",   
"220\r\n",   
"221\r\n",   
"222\r\n",   
"223\r\n",   
"224\r\n",   
"225\r\n",   
"226\r\n",   
"227\r\n",   
"228\r\n",   
"229\r\n",   
"230\r\n",   
"231\r\n",   
"232\r\n",   
"233\r\n",   
"234\r\n",   
"235\r\n",   
"236\r\n",   
"237\r\n",   
"238\r\n",   
"239\r\n",   
"240\r\n",   
"241\r\n",   
"242\r\n",   
"243\r\n",   
"244\r\n",   
"245\r\n",   
"246\r\n",   
"247\r\n",   
"248\r\n",   
"249\r\n",   
"250\r\n",   
"251\r\n",   
"252\r\n",   
"253\r\n",   
"254\r\n",  
"255\r\n"};

int main() {
    clear(&tx_buffer);

    // Initializations
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_DMA1EN;
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN | RCC_APB1ENR_I2C1EN;
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    RedLEDoff();

    __NOP();
    GPIOoutConfigure(RED_LED_GPIO,
        RED_LED_PIN,
        GPIO_OType_PP,
        GPIO_Low_Speed,
        GPIO_PuPd_NOPULL);

    // Buttons configuration
    configure(&fire_button);
    configureUSART();
    configureDMA();
    configureNVIC();
    configureI2C();

    __NOP();

    // POWER ON IMU
    {
        I2C1->CR1 |= I2C_CR1_START;
        
        while (!(I2C1->SR1 & I2C_SR1_SB))
        {
            continue;
        }

        I2C1->DR = LIS35DE_ADDR << 1;

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

        uint8_t value = 0b01000111;
        I2C1->DR = value;

        while (!(I2C1->SR1 & I2C_SR1_BTF))
        {
            continue;
        }
        I2C1->CR1 |= I2C_CR1_STOP;
    }

    // Main loop
    for (;;) {
        // Odbior jednej osi
        I2C1->CR1 |= I2C_CR1_START;
        
        while (!(I2C1->SR1 & I2C_SR1_SB))
        {
            continue;
        }

        I2C1->DR = LIS35DE_ADDR << 1;

        while (!(I2C1->SR1 & I2C_SR1_ADDR))
        {
            continue;
        }
        I2C1->SR2;

        uint8_t reg = 0x2D; // TUTAJ ZMIEN WARTOSC NA ODCZYT JEDNEJ Z OSI
        I2C1->DR = reg;
        while (!(I2C1->SR1 & I2C_SR1_BTF))
        {
            continue;
        }
        
        I2C1->CR1 |= I2C_CR1_START;
        
        while (!(I2C1->SR1 & I2C_SR1_SB))
        {
            continue;
        }

        I2C1->DR = (LIS35DE_ADDR << 1) | 1U; // Master Receive
        I2C1->CR1 &= ~I2C_CR1_ACK;
        while (!(I2C1->SR1 & I2C_SR1_ADDR))
        {
            continue;
        }
        I2C1->SR2;

        I2C1->CR1 |= I2C_CR1_STOP;
        while (!(I2C1->SR1 & I2C_SR1_RXNE))
        {
            continue;
        }
        
        uint8_t value = I2C1->DR;

        char *text = "0\n";

        text[1] = (char)value;

        char *end_of_line = "\r\n";
        if ((DMA1_Stream6->CR & DMA_SxCR_EN) == 0 &&
            (DMA1->HISR & DMA_HISR_TCIF6) == 0)
        {
            DMASend(tab[value]);
        }
        else
        {
            enqueue(&tx_buffer, tab[value]);
        }

        Delay(100000);
    }

    return 0;
}
void DMASend(char *text) {
    DMA1_Stream6->M0AR = (uint32_t)text;
    DMA1_Stream6->NDTR = strlen(text);
    DMA1_Stream6->CR |= DMA_SxCR_EN;
}

void interrupt(uint16_t interr, uint16_t exti_line, Button *button)
{
    if (interr & exti_line)
    {
        uint8_t is_released = ((button->gpio->IDR >> button->pin) & 1) ^ button->is_reverse_logic;
        char *text = is_released ? button->released_str : button->pressed_str;

        if ((DMA1_Stream6->CR & DMA_SxCR_EN) == 0 &&
            (DMA1->HISR & DMA_HISR_TCIF6) == 0)
        {
            DMASend(text);
        }
        else
        {
            enqueue(&tx_buffer, text);
        }

        EXTI->PR = exti_line;
    }
}

void DMA1_Stream6_IRQHandler() {
    uint32_t isr = DMA1->HISR;
    if (isr & DMA_HISR_TCIF6)
    {
        DMA1->HIFCR = DMA_HIFCR_CTCIF6;

        if (!empty(&tx_buffer))
        {
            char *text = dequeue(&tx_buffer);
            DMASend(text);

            resetIfNeeded(&tx_buffer);
        }
    }
}

void EXTI15_10_IRQHandler(void)
{
    uint16_t interr = EXTI->PR;
    interrupt(interr, EXTI_PR_PR13, &fire_button);
}
