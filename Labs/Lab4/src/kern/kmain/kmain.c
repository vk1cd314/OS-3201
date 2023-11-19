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
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, W OTHERWISE) ARISIHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE ORNG IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
 
// libraries and headers
#include <stm32_peps.h>
#include <kmain.h>
#include <sys_init.h>
#include <cm4.h>
#include <kstdio.h>
#include <kstring.h>
#include <stdint.h>

//device drivers
#include <usart.h>
#include <gpio.h>


//new includes for assignment 2
#include <sys.h> // EXTI Config
#include <nvic.h> //NVIC functions
#include <unistd.h>
#include <ustdio.h>

//includes for svc and pendsvc
#include <syscall.h>
#include <syscall_def.h>
#include <schedule.h>
#include <schedule_fcfs.h>
#include <sem.h>

void __move_to_user(void){
	uint32_t psp_stack[1024];
    PSP_Init(psp_stack + 1024);
   asm volatile (
		".global PSP_Init\n"
		"PSP_Init:\n"
			"msr psp, r0\n"
			"mov r0, #3\n"
			"msr control, r0\n"
			"isb\n"
	);
}

volatile uint32_t var = 0;

void kmain(void){
	__sys_init();

	__NVIC_SetPriority(SVCall_IRQn, 0x1);
	__NVIC_SetPriority(SysTick_IRQn, 0x2);
	__NVIC_SetPriority(PendSV_IRQn, 0xFF); 
	
	__move_to_user();

	// scheduling_tester_without_semaphore();
	scheduling_tester();
	// scheduling_tester_fcfs();
	// scheduling_tester_fcfs_with_semaphore();
	
	while(1);
}

