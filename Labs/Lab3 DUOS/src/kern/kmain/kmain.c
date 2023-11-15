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
 
#include <sys_init.h>
#include <cm4.h>
#include <kmain.h>
#include <kstdio.h>
#include <kstring.h>
#include <stdint.h>
#include <usart.h>
#include <gpio.h>
#include <stm32_peps.h>
#include <dev_table.h>
#include <sys.h> 
#include <nvic.h>
#include <test_interrupt.h> 
#include <unistd.h>
#include <ustdio.h>

#include <syscall.h>
#include <syscall_def.h>

void SVC_Handler_Main(uint32_t *svc_args) {
	syscall(svc_args);
}

void print_device_list() {
	kprintf("\n\n______________________\n\n");
	for (int i = 0;i < device_count;i++){
		kprintf("device name = %s\n",device_list[i].name);
		kprintf("device t_ref = %d\n",device_list[i].t_ref);
		kprintf("device t_access = %d\n",device_list[i].t_access);
		kprintf("device op_addr = %x\n",device_list[i].op_addr);
		kprintf("\n");
	}
}

void __move_to_user(void) {
	uint32_t psp_stack[1024];
    PSP_Init(psp_stack + 1024);
	__asm volatile (
		".global PSP_Init\n"
		"PSP_Init:\n"
			"msr psp, r0\n"
			"mov r0, #3\n"
			"msr control, r0\n"
			"isb\n"
	);
}

void SVC_Tester(void) {
	char *data = "this is temp";
	read_user(0,&data,5);
	kprintf("The data is %s\n",data);

	char *device_name = "GPIOA";
	uint8_t t_access = 0;
	uint32_t* op_addr = (uint32_t *)GPIOA;
	fopen(device_name,t_access,op_addr);
	print_device_list();

	fclose(op_addr);
	print_device_list();

	kprintf("Rebooting");
	for (int i = 0; i < 1e8; ++i);
	reboot();
}

#define STOP 		1000000
#define TASK_COUNT 	10
TCB_TypeDef __task[MAX_TASKS], __sleep;

uint32_t GLOBAL_COUNT = 0;
void task_1(void) {
	uint32_t value;
	uint32_t inc_count=0;
	uint32_t pid = getpid();
	kprintf("___________________Task %d___________________\n",pid);
	while(1){
		value = GLOBAL_COUNT;
		value++;
		if (value != GLOBAL_COUNT+1) { 
			kprintf("Error %d != %d\n\r",value,GLOBAL_COUNT+1);
		} else {
			GLOBAL_COUNT=value;
			inc_count++;
		}
		if (GLOBAL_COUNT >= STOP) {
			kprintf("Total increment done by task %d is: %d\n\r",pid,inc_count);
			break;
		}
	}
	task_exit();
}

void sleep_state(void){
	kprintf("Sleeping\n");
	while(1);
}

void do_taskswitch() {
	init_queue();
	
	for(int i = 0;i < TASK_COUNT;i++){
		__create_task(__task + i,task_1,(uint32_t*)TASK_STACK_START - i * TASK_STACK_SIZE);
		queue_add(__task + i);
	}
	
	__create_task(&__sleep,sleep_state,(uint32_t*)TASK_STACK_START - TASK_COUNT * TASK_STACK_SIZE);
	__set_sleep(&__sleep);

	__set_pending(1);
	start_exec();
}

void kmain(void){
	__sys_init();

	__NVIC_SetPriority(SVCall_IRQn, 1);
	__NVIC_SetPriority(SysTick_IRQn, 0xFF);
	__NVIC_SetPriority(PendSV_IRQn, 0xFF);
	__move_to_user();

	// SVC_Tester();
	do_taskswitch();

	kprintf("___________END MAIN___________\n");
	while(1);
}