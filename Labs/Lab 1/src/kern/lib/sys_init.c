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
#include <gpio.h>
#include <kstdio.h>
#include <sys_init.h>
#include <usart.h>
void __sys_init(void) {
    DRV_CLOCK_INIT();        // configure system clock 180 MHz
    DRV_GPIO_INIT(GPIOA);    // Initialize GPIO
    DRV_USART_INIT(USART2);  // configure as standard input and output
    __enable_fpu();          // enable FPU single precision floating point unit
    __SysTick_init(10000);   // enable systick for 10ms
    kprintf("\n************************************\r\n");
    kprintf("Booting DUOS .....\r\n");
    kprintf("Copyright (c) 2022, CSE, DU\r\n");
    kprintf("Credit: Third Year 2022\r\n");
    kprintf("CPUID %x\n", SCB->CPUID);
    kprintf("OS Version: 1.0\n");
    kprintf("Time Elapse %d ms\n", __getTime());
    kprintf("Welcome ....\r\n");
    kprintf("*************************************\r\n");
    kprintf("# ");
}
