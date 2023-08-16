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

#include <cm4.h>
#include <gpio.h>
#include <kmain.h>
#include <kstdio.h>
#include <kstring.h>
#include <stdint.h>
#include <sys.h>
#include <sys_init.h>
#include <test_interrupt.h>
#include <usart.h>
// #include "../include/float.h"

static volatile uint32_t __mscount;

void SysTick_Handler(void) {
    // kprintf("S ");
    ++__mscount;
    SYSTICK->CTRL;
}

void ms_delay(int ms) {
    uint32_t start_time = __mscount;
    while ((__mscount - start_time) < ms);
}

#define kprintf(_1, ...) _Generic((_1), \
    int: kprintf_seven_segment_display, \
    char *: kprintf)(_1)

void __NVIC_SetPriority(IRQn_TypeDef IRQn, uint32_t priority) {
    if (IRQn >= 0) {
        NVIC->IP[IRQn] = (uint8_t)((priority << 4));
    } else {
        SCB->SHPR[(((uint32_t)IRQn) & 0xFUL) - 4UL] = (uint8_t)((priority << (8U - 4U)) & (uint32_t)0xFFUL);
    }
}

uint32_t __NVIC_GetPriority(IRQn_TypeDef IRQn) {
    if ((int32_t)(IRQn) >= 0) {
        return (((uint32_t)NVIC->IP[((uint32_t)IRQn)] >> (8U - 3U)));
    } else {
        return (((uint32_t)SCB->SHPR[(((uint32_t)IRQn) & 0xFUL) - 4UL] >> (8U - 3U)));
    }
}

void __NVIC_EnableIRQn(IRQn_TypeDef IRQn) {
    if (IRQn >= 0) {
        NVIC->ISER[IRQn / 32] |= (1 << (IRQn % 32));
    }
}

void __NVIC_DisableIRQn(IRQn_TypeDef IRQn) {
    if (IRQn >= 0) {
        kprintf("Disabling %d Number Interrupt", IRQn);
        NVIC->ICER[IRQn / 32] |= (1 << (IRQn % 32));
    }
}

void __disable_irq() {
    __asm volatile("mov r0,#1");
    __asm volatile("msr primask,r0;");
}

void __set_BASEPRI(uint32_t value) {
    __asm volatile("mov r0, %0"
                   : "=r"(value));
    __asm volatile("msr basepri, r0;");
}

void __enable_irq() {
    __asm volatile("mov r0,#0");
    __asm volatile("msr primask,r0;");
}

void __unset_BASEPRI(uint32_t value) {
    __asm volatile("mov r0,#0");
    __asm volatile("msr basepri,r0;");
}

void __set_PRIMASK(uint32_t priMask) {
    __asm volatile("mov r0, #1");
    __asm volatile("msr primask, r0");
}

uint32_t get_PRIMASK(void) {
    uint32_t value;
    __asm volatile("mrs r0,primask");
    __asm volatile("mov %0,r0"
                   : "=r"(value));
    return value;
}

void __enable_fault_irq(void) {
    __asm volatile("mov r0, #0");
    __asm volatile("msr primask, r0");
}

void __set_FAULTMASK(uint32_t faultMask) {
    __asm volatile("mov r0, #1");
    __asm volatile("msr primask, r0");
}

void __disable_fault_irq(void) {
    __asm volatile("mov r0, #1");
    __asm volatile("msr primask, r0");
}

uint32_t __get_FAULTMASK(void) {
    uint32_t value;
    __asm volatile("mrs r0,faultmask");
    __asm volatile("mov %0,r0"
                   : "=r"(value));
    return value;
}

void __clear_pending_IRQn(IRQn_TypeDef IRQn) {
    if (IRQn >= 0) {
        NVIC->ICPR[IRQn / 32] |= (1 << (IRQn % 32));
    }
}

uint32_t __get_pending_IRQn(IRQn_TypeDef IRQn) {
    uint32_t pendingState;
    if (IRQn >= 0) {
        int regNumber = IRQn / 32;
        int offset = IRQn % 32;
        pendingState = NVIC->ICPR[regNumber] & (1 << regNumber);
        pendingState = pendingState >> 5;
        return pendingState;
    }
}

uint32_t __NVIC_GetActive(IRQn_TypeDef IRQn) {
    uint32_t pendingState;
    if (IRQn >= 0) {
        int regNumber = IRQn / 32;
        int offset = IRQn % 32;
        pendingState = NVIC->IABR[regNumber] & (1 << regNumber);
        pendingState = pendingState >> 5;
        return pendingState;
    }
}

void test_hardfault() { 
    __asm("udf #1");
}

void systick_enable_disable() {
    for (int i = 0; i < 1e7; ++i);
    // SYSTICK->CTRL &= ~(1 << 1);
    __set_PRIMASK(1);
}

void set_systick_priority() {
    __NVIC_SetPriority(SysTick_IRQn, 1);
}

void reboot() {
    for (int i = 0; i < 1e8; ++i);
    Reset_Handler();
}

void systick_modify() {
    for (int i = 0; i < 1e7; ++i);

    __set_BASEPRI(-1);
}

void EXTI0_Handler(void) {
    if (EXTI->PR & (1 << 0)) { 
        kprintf("EXTI0 Interrupt\n");
        EXTI->PR |= (1 << 0);
    } 
}

void configure_external_interrupt(void) {
    RCC->APB2ENR |= (1 << 14);
    SYSCFG->EXTICR[0] |= 1;
    
    RCC->AHB1ENR |= (1 << 1); 
    GPIOB->MODER &= ~(0x3);
    GPIOB->PUPDR &= ~(0x3);
    GPIOB->PUPDR |= (0x1);

    int pin = 0;
    EXTI->IMR |= (1 << pin); 
    EXTI->EMR |= (1 << pin);
    EXTI->RTSR |= (1 << pin); 
    EXTI->FTSR |= (1 << pin);
    
    __NVIC_SetPriority(EXTI0_STM_IRQn, 0); 
    __NVIC_EnableIRQn(EXTI0_STM_IRQn);
}

void test_ext0_interrupt() {
    EXTI->SWIER |= (1 << 0);
    ms_delay(10);
    EXTI->SWIER &= ~(1 << 0);
}

void kmain(void) {
    __sys_init();
    __SysTick_init(1000000);
    configure_external_interrupt();

    // test_hardfault();
    // systick_enable_disable();
    // reboot();
    // systick_modify();
    // test_ext0_interrupt();

    while (1) {
        // kprintf("Hello\n");
    }
}
