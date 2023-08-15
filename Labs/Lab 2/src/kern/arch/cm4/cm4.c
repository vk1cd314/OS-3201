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

#include <clock.h>
#include <cm4.h>
#include <syscall.h>
volatile static uint32_t __mscount;
/************************************************************************************
 * __SysTick_init(uint32_t reload)
 * Function initialize the SysTick clock. The function with a weak attribute enables
 * redefining the function to change its characteristics whenever necessary.
 **************************************************************************************/

__attribute__((weak)) void __SysTick_init(uint32_t reload) {
    SYSTICK->CTRL &= ~(1 << 0);  // disable systick timer
    SYSTICK->VAL = 0;            // initialize the counter
    __mscount = 0;
    SYSTICK->LOAD = PLL_N * reload;
    SYSTICK->CTRL |= 1 << 1 | 1 << 2;  // enable interrupt and internal clock source
    SYSTICK->CTRL |= 1 << 0;           // enable systick counter
}

/************************************************************************************
 * __sysTick_enable(void)
 * The function enables the SysTick clock if already not enabled.
 * redefining the function to change its characteristics whenever necessary.
 **************************************************************************************/
__attribute__((weak)) void __sysTick_enable(void) {
    if (SYSTICK->CTRL & ~(1 << 0)) SYSTICK->CTRL |= 1 << 0;
}
__attribute__((weak)) void __sysTick_disable(void) {
    if (!(SYSTICK->CTRL & ~(1 << 0))) SYSTICK->CTRL &= ~(1 << 0);
}
__attribute__((weak)) uint32_t __getSysTickCount(void) {
    return SYSTICK->VAL;
}
/************************************************************************************
 * __updateSysTick(uint32_t count)
 * Function reinitialize the SysTick clock. The function with a weak attribute enables
 * redefining the function to change its characteristics whenever necessary.
 **************************************************************************************/

__attribute__((weak)) void __updateSysTick(uint32_t count) {
    SYSTICK->CTRL &= ~(1 << 0);  // disable systick timer
    SYSTICK->VAL = 0;            // initialize the counter
    __mscount = 0;
    SYSTICK->CTRL |= 1 << 1 | 1 << 2;  // enable interrupt and internal clock source
    SYSTICK->LOAD = PLL_N * count;
    SYSTICK->CTRL |= 1 << 0;  // enable systick counter
}

/************************************************************************************
 * __getTime(void)
 * Function return the SysTick elapsed time from the begining or reinitialing. The function with a weak attribute enables
 * redefining the function to change its characteristics whenever necessary.
 **************************************************************************************/

__attribute__((weak)) uint32_t __getTime(void) {
    return (__mscount + (SYSTICK->LOAD - SYSTICK->VAL) / (PLL_N * 1000));
}
__attribute__((weak)) void SysTick_Handler() {
    __mscount += (SYSTICK->LOAD) / (PLL_N * 1000);
}

void __enable_fpu() {
    SCB->CPACR |= ((0xF << 20));
}
