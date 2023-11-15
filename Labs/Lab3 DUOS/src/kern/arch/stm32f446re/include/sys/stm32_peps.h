/*
 * Copyright (c) 2022 
 * Computer Science and Engineering, University of Dhaka
 * Credit: CSE Batch 25 (starter) and Prof. Mosaddek Tushar
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE UNIVERSITY OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
 
#ifndef __STM32_PEPS_H
#define __STM32_PEPS_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#define PWR	    ((PWR_TypeDef *)0x40007000)
#define FLASH	((FLASH_TypeDef *)0x40023C00)
#define RCC 	((RCC_TypeDef *)0x40023800)
#define SYSCFG  ((SYSCFG_TypeDef *)0x40013800)
#define EXTI    ((EXTI_TypeDef *)0x40013C00)
/**
* Define GPIOx Port
**/
#define GPIOA 	((GPIO_TypeDef *)0x40020000)
#define GPIOB 	((GPIO_TypeDef *)0x40020400)
#define GPIOC 	((GPIO_TypeDef *)0x40020800)
#define GPIOD 	((GPIO_TypeDef *)0x40020C00)
#define GPIOE 	((GPIO_TypeDef *)0x40021000)
#define GPIOF 	((GPIO_TypeDef *)0x40021400)
#define GPIOG 	((GPIO_TypeDef *)0x40021800)
#define GPIOH 	((GPIO_TypeDef *)0x40021C00)
/**
* Define USARTx
**/
#define USART1 	((USART_TypeDef *)0x40011000) 
#define USART2 	((USART_TypeDef *)0x40004400)
#define USART3 	((USART_TypeDef *)0x40004800)
#define USART4 	((USART_TypeDef *)0x40004C00)
#define USART5 	((USART_TypeDef *)0x40005000)
#define USART6 	((USART_TypeDef *)0x40011400)
/**
* Define TIMERx
**/
#define TIM1 	((TIM_TypeDef *)0x40010000)
#define TIM2 	((TIM_TypeDef *)0x40000000)
#define TIM3 	((TIM_TypeDef *)0x40000400)
#define TIM4 	((TIM_TypeDef *)0x40000800)
#define TIM5 	((TIM_TypeDef *)0x40000C00)
#define TIM6 	((TIM_TypeDef *)0x40001000)
#define TIM7 	((TIM_TypeDef *)0x40001400)
#define TIM8 	((TIM_TypeDef *)0x40010400)
#define TIM9 	((TIM_TypeDef *)0x40014000)
#define TIM10 	((TIM_TypeDef *)0x40014400)
#define TIM11 	((TIM_TypeDef *)0x40014800)
#define TIM12 	((TIM_TypeDef *)0x40001800)
#define TIM13 	((TIM_TypeDef *)0x40001C00)
#define TIM14 	((TIM_TypeDef *)0x40002000)

/**
*
* Data Structure for FLASH control Register
**/
typedef struct
{
uint32_t volatile ACR;
uint32_t volatile KEYR;
uint32_t volatile OPTKEYR;
uint32_t volatile SR;
uint32_t volatile CR;
uint32_t volatile OPTCR;
}FLASH_TypeDef;
/*
* Data Structure for Power control, Address Range: 0x4000 7000 - 0x4000 73FF */
typedef struct
{
uint32_t volatile CR;
uint32_t volatile CSR;
}PWR_TypeDef;

/*
* Data Structure for Reset and Clock Control Registers (RCC), Address Range: 0x4002 3800 - 0x4002 3BFF */
typedef struct
{
uint32_t volatile CR; /* Offset: 0x00 (R/W) Clock Control Register */
uint32_t volatile PLLCFGR; /* Offset: 0x04 (R/W) PLL Configuration Register */
uint32_t volatile CFGR; /* Offset: 0x08 (R/W) Clock Configuration Register */
uint32_t volatile CIR; /* Offset: 0x0C (R/W) Clock Interrupt Register */
uint32_t volatile AHB1RSTR; /* Offset: 0x10 (R/W) AHB1 Peripheral Reset Register */
uint32_t volatile AHB2RSTR; /* Offset: 0x14 (R/W) AHB2 Peripheral Reset Register */
uint32_t volatile AHB3RSTR; /* Offset: 0x18 (R/W) AHB3 Peripheral Reset Register */
uint32_t volatile reserved0;
uint32_t volatile APB1RSTR; /* Offset: 0x20 (R/W) APB1 Peripheral Reset Register */
uint32_t volatile APB2RSTR; /* Offset: 0x24 (R/W) APB2 Peripheral Reset Register */
uint32_t reserved1[2];
uint32_t volatile AHB1ENR; /* Offset: 0x30 (R/W) AHB1 Peripheral Clock Enable Register */
uint32_t volatile AHB2ENR; /* Offset: 0x34 (R/W) AHB2 Peripheral Clock Enable Register */
uint32_t volatile AHB3ENR; /* Offset: 0x38 (R/W) AHB3 Peripheral Clock Enable Register */
uint32_t reserved2;
uint32_t volatile APB1ENR; /* Offset: 0x40 (R/W) APB1 Peripheral Clock Enable Register */
uint32_t volatile APB2ENR; /* Offset: 0x44 (R/W) APB1 Peripheral Clock Enable Register */
uint32_t reserved3[2];
uint32_t volatile AHB1LPENR; /* Offset: 0x50 (R/W) AHB1 Peripheral Clock Enable Lower Power Mode Register */
uint32_t volatile AHB2LPENR; /* Offset: 0x54 (R/W) AHB2 Peripheral Clock Enable Lower Power Mode Register */
uint32_t volatile AHB3LPENR; /* Offset: 0x58 (R/W) AHB3 Peripheral Clock Enable Lower Power Mode Register */
uint32_t reserved4;
uint32_t volatile APB1LPENR; /* Offset: 0x60 (R/W) APB1 Peripheral Clock Enable Lower Power Mode Register */
uint32_t volatile APB2LPENR; /* Offset: 0x64 (R/W) APB2 Peripheral Clock Enable Lower Power Mode Register */
uint32_t reserved5[2];
uint32_t volatile BDCR; /* Offset: 0x70 (R/W) Backup Domain Control Register */
uint32_t volatile CSR; /* Offset: 0x74 (R/W) Clock Control & Status Register */
uint32_t reserved6[2];
uint32_t volatile SSCGR; /* Offset: 0x80 (R/W) Spread Spectrum Clock Generation Register */
uint32_t volatile PLLI2SCFGR; /* Offset: 0x84 (R/W) PLLI2S Configuration Register */
uint32_t volatile PLLSAICFGR; /* Offset: 0x88 (R/W) PLLSAI Configuration Register */
uint32_t volatile DCKCFGR; /* Offset: 0x8C (R/W) Dedicated Clocks Configuration Register */
uint32_t volatile CKGATENR; /* Offset: 0x90 (R/W) Clocks Gated Enabled Register */
uint32_t volatile DCKCFGR2; /* Offset: 0x94 (R/W) Dedicated Clocks Configuration Register 2 */
} RCC_TypeDef;

typedef struct
{
 uint32_t volatile TR;      /*!< RTC time register,                                        Address offset: 0x00 */
 uint32_t volatile DR;      /*!< RTC date register,                                        Address offset: 0x04 */
 uint32_t volatile CR;      /*!< RTC control register,                                     Address offset: 0x08 */
 uint32_t volatile ISR;     /*!< RTC initialization and status register,                   Address offset: 0x0C */
 uint32_t volatile PRER;    /*!< RTC prescaler register,                                   Address offset: 0x10 */
 uint32_t volatile WUTR;    /*!< RTC wakeup timer register,                                Address offset: 0x14 */
 uint32_t volatile CALIBR;  /*!< RTC calibration register,                                 Address offset: 0x18 */
 uint32_t volatile ALRMAR;  /*!< RTC alarm A register,                                     Address offset: 0x1C */
 uint32_t volatile ALRMBR;  /*!< RTC alarm B register,                                     Address offset: 0x20 */
 uint32_t volatile WPR;     /*!< RTC write protection register,                            Address offset: 0x24 */
 uint32_t volatile SSR;     /*!< RTC sub second register,                                  Address offset: 0x28 */
 uint32_t volatile SHIFTR;  /*!< RTC shift control register,                               Address offset: 0x2C */
 uint32_t volatile TSTR;    /*!< RTC time stamp time register,                             Address offset: 0x30 */
 uint32_t volatile TSDR;    /*!< RTC time stamp date register,                             Address offset: 0x34 */
 uint32_t volatile TSSSR;   /*!< RTC time-stamp sub second register,                       Address offset: 0x38 */
 uint32_t volatile CALR;    /*!< RTC calibration register,                                 Address offset: 0x3C */
 uint32_t volatile TAFCR;   /*!< RTC tamper and alternate function configuration register, Address offset: 0x40 */
 uint32_t volatile ALRMASSR;/*!< RTC alarm A sub second register,                          Address offset: 0x44 */
 uint32_t volatile ALRMBSSR;/*!< RTC alarm B sub second register,                          Address offset: 0x48 */
 uint32_t reserved7;    /*!< Reserved, 0x4C                                                                 */
 uint32_t volatile BKP0R;   /*!< RTC backup register 1,                                    Address offset: 0x50 */
 uint32_t volatile BKP1R;   /*!< RTC backup register 1,                                    Address offset: 0x54 */
 uint32_t volatile BKP2R;   /*!< RTC backup register 2,                                    Address offset: 0x58 */
 uint32_t volatile BKP3R;   /*!< RTC backup register 3,                                    Address offset: 0x5C */
 uint32_t volatile BKP4R;   /*!< RTC backup register 4,                                    Address offset: 0x60 */
 uint32_t volatile BKP5R;   /*!< RTC backup register 5,                                    Address offset: 0x64 */
 uint32_t volatile BKP6R;   /*!< RTC backup register 6,                                    Address offset: 0x68 */
 uint32_t volatile BKP7R;   /*!< RTC backup register 7,                                    Address offset: 0x6C */
 uint32_t volatile BKP8R;   /*!< RTC backup register 8,                                    Address offset: 0x70 */
 uint32_t volatile BKP9R;   /*!< RTC backup register 9,                                    Address offset: 0x74 */
 uint32_t volatile BKP10R;  /*!< RTC backup register 10,                                   Address offset: 0x78 */
 uint32_t volatile BKP11R;  /*!< RTC backup register 11,                                   Address offset: 0x7C */
 uint32_t volatile BKP12R;  /*!< RTC backup register 12,                                   Address offset: 0x80 */
 uint32_t volatile BKP13R;  /*!< RTC backup register 13,                                   Address offset: 0x84 */
 uint32_t volatile BKP14R;  /*!< RTC backup register 14,                                   Address offset: 0x88 */
 uint32_t volatile BKP15R;  /*!< RTC backup register 15,                                   Address offset: 0x8C */
 uint32_t volatile BKP16R;  /*!< RTC backup register 16,                                   Address offset: 0x90 */
 uint32_t volatile BKP17R;  /*!< RTC backup register 17,                                   Address offset: 0x94 */
 uint32_t volatile BKP18R;  /*!< RTC backup register 18,                                   Address offset: 0x98 */
 uint32_t volatile BKP19R;  /*!< RTC backup register 19,                                   Address offset: 0x9C */
} RTC_TypeDef;

/*
* Data Structure for GPIO port
*/
typedef struct
{
uint32_t volatile MODER; /* Offset: 0x00 (R/W) Mode Register */
uint32_t volatile OTYPER; /* Offset: 0x04 (R/W) Output Type Register */
uint32_t volatile OSPEEDR; /* Offset: 0x08 (R/W) Output Speed Register */
uint32_t volatile PUPDR; /* Offset: 0x0C (R/W) Pull-up/Pull-down Register */
uint32_t volatile IDR; /* Offset: 0x10 (R/W) Input Data Register */
uint32_t volatile ODR; /* Offset: 0x14 (R/W) Output Data Register */
uint32_t volatile BSRR; /* Offset: 0x18 (R/W) Bit Set/Reset Register */
uint32_t volatile LCKR; /* Offset: 0x1C (R/W) Configuration Lock Register */
uint32_t volatile AFR[2]; /* Offset: 0x20 (R/W) Alternate Function Low Register */
//uint32_t volatile AFRH; /* Offset: 0x24 (R/W) Alternate Function High Register */
} GPIO_TypeDef;

/*
* Data Structure for USART
*/
typedef struct
{
uint32_t volatile SR; /* Offset: 0x00 (R) Status Register */
uint32_t volatile DR; /* Offset: 0x04 (R/W) Data Register */
uint32_t volatile BRR; /* Offset: 0x08 (R/W) Baud Rate Register */
uint32_t volatile CR1; /* Offset: 0x0C (R/W) Control Register 1 */
uint32_t volatile CR2; /* Offset: 0x10 (R/W) Control Register 2 */ 
uint32_t volatile CR3; /* Offset: 0x14 (R/W) Control Register 3 */ 
uint32_t volatile GTPR; /* Offset: 0x18 (R/W) Guard time and prescaler register */
} USART_TypeDef;

/*
* Data Structure for Timer 1 & 8
* Alert Timer data structure is not 100% correct, see datasheet and reference manual for currection
*/
typedef struct
{
uint32_t volatile CR1; /* Offset: 0x00 (R/W) TIM1&TIM8 control register 1 */
uint32_t volatile CR2; /* Offset: 0x04 (R/W) TIM1&TIM8 control register 2 */
uint32_t volatile SMCR; /* Offset: 0x08 (R/W) TIM1&TIM8 slave mode control register */
uint32_t volatile DIER; /* Offset: 0x0C (R/W) TIM1&TIM8 DMA/interrupt enable register */
uint32_t volatile SR; /* Offset: 0x10 TIM1&TIM8 status register */
uint32_t volatile EGR; /* Offset: 0x14 (R/W) TIM1&TIM8 event generation register */ 
uint32_t volatile CCMR1; /* Offset: 0x18 (R/W) TIM1&TIM8 capture/compare mode register 1 */
uint32_t volatile CCMR2; /* Offset: 0x1C (R/W) TIM1&TIM8 capture/compare mode register 2 */
uint32_t volatile CCER; /* Offset: 0x20 (R/W) TIM1&TIM8 capture/compare enable register  */
uint32_t volatile CNT; /* Offset: 0x24 (R/W) TIM1&TIM8 counter */
uint32_t volatile PSC; /* Offset: 0x28 (R/W) TIM1&TIM8 prescaler */
uint32_t volatile ARR; /* Offset: 0x2C (R/W) TIM1&TIM8 auto-reload register */
uint32_t volatile RCR; /* Offset: 0x30 (R/W) TIM1&TIM8 repetition counter register */
uint32_t volatile CCR1; /* Offset: 0x34 (R/W) TIM1&TIM8 capture/compare register 1 */
uint32_t volatile CCR2; /* Offset: 0x38 (R/W) TIM1&TIM8 capture/compare register 2 */
uint32_t volatile CCR3; /* Offset: 0x3C (R/W) TIM1&TIM8 capture/compare register 3 */
uint32_t volatile CCR4; /* Offset: 0x40 (R/W) TIM1&TIM8 capture/compare register 4 */
uint32_t volatile BDTR; /* Offset: 0x44 (R/W) TIM1&TIM8 break and dead-time register */
uint32_t volatile DCR; /* Offset: 0x48 (R/W) TIM1&TIM8 DMA control register */
uint32_t volatile DMAR; /* Offset: 0x4C (R/W) TIM1&TIM8 DMA address for full transfer */
uint32_t volatile OR;   /*!< TIM option register, Address offset: 0x50 */
} TIM_TypeDef;

typedef struct
{
 uint32_t volatile MEMRMP;       /*!< SYSCFG memory remap register,                      Address offset: 0x00      */
 uint32_t volatile PMC;          /*!< SYSCFG peripheral mode configuration register,     Address offset: 0x04      */
 uint32_t volatile EXTICR[4];    /*!< SYSCFG external interrupt configuration registers, Address offset: 0x08-0x14 */
 uint32_t      RESERVED[2];      /*!< Reserved, 0x18-0x1C                                                          */
 uint32_t volatile CMPCR;        /*!< SYSCFG Compensation cell control register,         Address offset: 0x20      */
 uint32_t      RESERVED1[2];     /*!< Reserved, 0x24-0x28                                                          */
 uint32_t volatile CFGR;         /*!< SYSCFG Configuration register,                     Address offset: 0x2C      */
} SYSCFG_TypeDef;

typedef struct
{
 uint32_t volatile IMR;    /*!< EXTI Interrupt mask register,            Address offset: 0x00 */
 uint32_t volatile EMR;    /*!< EXTI Event mask register,                Address offset: 0x04 */
 uint32_t volatile RTSR;   /*!< EXTI Rising trigger selection register,  Address offset: 0x08 */
 uint32_t volatile FTSR;   /*!< EXTI Falling trigger selection register, Address offset: 0x0C */
 uint32_t volatile SWIER;  /*!< EXTI Software interrupt event register,  Address offset: 0x10 */
 uint32_t volatile PR;     /*!< EXTI Pending register,                   Address offset: 0x14 */
} EXTI_TypeDef;

#ifdef __cplusplus
}
#endif

#endif

