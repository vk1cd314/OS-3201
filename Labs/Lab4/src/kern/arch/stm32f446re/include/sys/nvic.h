#ifndef __NVIC_H
#define __NVIC_H

#include <cm4.h>
#include <stdint.h>

/* Functions of NVIC */

void __NVIC_SetPriority (enum IRQn_TypeDef IRQn,uint8_t priority);
uint8_t __NVIC_GetPriority(enum IRQn_TypeDef IRQn);
void __NVIC_EnableIRQn(enum IRQn_TypeDef IRQn);
void __NVIC_DisableIRQn(enum IRQn_TypeDef IRQn);
uint32_t __NVIC_GetActive (enum IRQn_TypeDef IRQn);                  /*!< Returns the pending status of an interrupt              */ 
uint32_t __get_pending_IRQn(enum IRQn_TypeDef IRQn);                 /*!< Returns active status of the interrupt                  */ 
void __clear_pending_IRQn(enum IRQn_TypeDef IRQn);                   /*!< Clear interrupt pending bit                             */
void __set_pending_IRQn(enum IRQn_TypeDef IRQn);
void __disable_irq();                    /*!< Masks all interrupts (except NMI, HardFault)            */
void __enable_irq();                     /*!< Enables / Unmasks all interrupts (except NMI, HardFault)*/
uint32_t __get_BASEPRI(void);
void __set_BASEPRI(uint32_t value);      /*!< Masks interrupts with priority level >= value           */
void __unset_BASEPRI(uint32_t value);    /*!< Unmasks interrupts with priority level >= value         */
void __set_PRIMASK(uint32_t priMask);    //Prevent all interrupt without non-maskable interrupt and hardfault.
uint32_t __get_PRIMASK(void);            //Return value of the PRIMASK register
void __enable_fault_irq(void);           //Enable all interrupt including FaultMask.
void __set_FAULTMASK(uint32_t faultMask);//Prevent all interrupt without non-maskable interrupt
uint32_t __get_FAULTMASK(void);          //Return the status of the masking value of FaultMask register
void __enable_fault_irq(void);           //Enable all interrupt including FaultMask
void __disable_fault_irq(void);          //Disable or prevent all interrupt including FaultMask

void __enable_fpu(void);
void set_task_pending(int value);

#endif