#ifndef __NVIC_H
#define __NVIC_H

#include <cm4.h>
#include <stdint.h>

/* Functions of NVIC */

void __NVIC_SetPriority (enum IRQn_TypeDef IRQn,uint8_t priority);
uint8_t __NVIC_GetPriority(enum IRQn_TypeDef IRQn);
void __NVIC_EnableIRQn(enum IRQn_TypeDef IRQn);
void __NVIC_DisableIRQn(enum IRQn_TypeDef IRQn);
void __disable_irq(void);
void __set_BASEPRI(uint32_t value);
void __enable_irq(void);
void __unset_BASEPRI(void);
void __set_PRIMASK(uint32_t priMask);
uint32_t __get_PRIMASK(void);
void __enable_fault_irq(void);
void __set_FAULTMASK(void);
void __clear_FAULTMASK(void);
void __disable_fault_irq(void);
uint32_t __get_FAULTMASK(void);
void __clear_pending_IRQn(enum IRQn_TypeDef IRQn);
uint32_t __get_pending_IRQn(enum IRQn_TypeDef IRQn);
uint32_t __NVIC_GetActive (enum IRQn_TypeDef IRQn);
void __set_SysTick_Priority(uint8_t priority);
uint32_t __get_SysTick_Priority(void);

#endif