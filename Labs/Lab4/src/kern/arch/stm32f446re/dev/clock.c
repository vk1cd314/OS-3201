/*
 * Copyright (c) 2022 
 * 			Computer Science and Engineering, University of Dhaka
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
 * ARE DISCLAIMED. IN NO EVENT SHALL THE UNIVERSITY OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#include <clock.h>
void DRV_CLOCK_INIT()
{
RCC->CR |= 1<<16; // set CR bit 16 
/** Check if clock is ready RCC CR register 17th bit set*/ 
while(!(RCC->CR & 1<<17)); //wait for the clock is enabled See RCC CR bit-17; HSE crystal is On
/* Set the POWER enable CLOCK and VOLTAGE REGULATOR */
RCC->APB1ENR |= 1<<28; //power enable for APB1
PWR->CR |= 3<<14; // PWR_CR_VOS; //VOS always correspond to reset value 

/*3. Configure the FLASH PREFETCH and the LATENCY Related Settings */
FLASH->ACR |= 1<<9 | 1<<10 | 1<<8 | 5<<0; //ICEN -- instruction cache, DCEN -- Data Cache, PRFTEN -- prefetch and LAtency;

/* 4. Configure the PRESCALERS HCLK, PCLK1, PCLK2 */
//AHB prescaler 
RCC->CFGR |= 0<<4;
//APB1 prescaler
RCC->CFGR |= 5<<10;
//APB2 prescaler
RCC->CFGR |= 4<<13;
//5. Configugure the main PLL
RCC->PLLCFGR = (PLL_M<<0) | (PLL_N<<6) | (PLL_P<<16) | (1<<22); 
//6. Enable PLL and wait for it to become ready
RCC->CR |= 1<<24;
//Check if PLL clock is ready
while(!(RCC->CR & 1<<25))
	; //wait for PLL ready
//7. Select clock source and wait for it to be set
RCC->CFGR |= 2<<0;
while((RCC->CFGR & 2<<2) != 2<<2);
}


