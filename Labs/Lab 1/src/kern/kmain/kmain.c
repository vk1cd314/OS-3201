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
#include <sys_init.h>
#include <usart.h>
// #include "../include/float.h"

static volatile uint32_t __mscount;

void SysTick_Handler(void) { __mscount++; }

void ms_delay(int ms) {
    uint32_t start_time = __mscount;
    while ((__mscount - start_time) < ms);
}

lul what[7];

#define kprintf(_1,...) _Generic((_1), \
                            int: kprintf_seven_segment_display,    \
                            char *: kprintf) \
                        (_1)

void kmain(void) {
    __sys_init();
    __SysTick_init(1000);
    RCC->AHB1ENR |= (1 << 0);
    RCC->AHB1ENR |= (1 << 1);
    RCC->AHB1ENR |= (1 << 2);

    what[0].GPIOx = GPIOA;
    what[0].led = 7;

    what[1].GPIOx = GPIOA;
    what[1].led = 4;

    what[2].GPIOx = GPIOA;
    what[2].led = 6;

    what[3].GPIOx = GPIOA;
    what[3].led = 8;

    what[4].GPIOx = GPIOC;
    what[4].led = 7;

    what[5].GPIOx = GPIOB;
    what[5].led = 6;

    what[6].GPIOx = GPIOB;
    what[6].led = 10;

    for (int i = 0; i < 7; ++i) gpio_init1(what[i], 1);

    while (1) {
        int cur;
        kscanf("%d", &cur);
        kprintf(cur);
    }
}
