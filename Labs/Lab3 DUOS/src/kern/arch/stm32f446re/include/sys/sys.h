#ifndef __SYS_H
#define __SYS_H

#include <cm4.h>
#include <kstdio.h>
#include <stdint.h>
#include <usart.h>
#include <gpio.h>
#include <stm32_peps.h>


/* Functions of NVIC */
void EXTI_GPIO_Config(GPIO_TypeDef* gpio,uint16_t pin);
void EXTI0_Init(void);
void EXTI1_Init(void);



#endif