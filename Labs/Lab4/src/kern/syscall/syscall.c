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




#include <syscall.h>

void syscall(uint32_t* svc_args)
{
	/* The SVC_Handler calls this function to evaluate and execute the actual function */
	/* Take care of return value or code */

	uint16_t callno = ((char*)svc_args[6])[-2];
	switch (callno)
	{
		/* Write your code to call actual function (kunistd.h/c or times.h/c and handle the return value(s) */
	case SYS_open:
	{
		kprintf("Will call __sys_open\n");
		char* device_name = (char*)svc_args[0];
		uint8_t t_access = (uint8_t)svc_args[1];
		uint32_t* op_addr = (uint32_t*)svc_args[2];
		__sys_open(device_name, t_access, op_addr);
		break;
	}
	case SYS_close:
	{
		kprintf("Will call __sys_close\n");
		uint32_t* op_addr = (uint32_t*)svc_args[0];
		__sys_close(op_addr);
		break;
	}
	case SYS_sem_dec:
	{
		uint32_t* semaphore = (uint32_t*)svc_args[0];
		__sem_dec(semaphore);
		break;
	}
	case SYS_sem_inc:
	{
		uint32_t* semaphore = (uint32_t*)svc_args[0];
		__sem_inc(semaphore);
		break;
	}
	case SYS_set_pending:
	{
		uint8_t value = (uint8_t)svc_args[0];
		__set_pending(value);
		break;
	}
	case SYS_read:
		kprintf("Will call __sys_read\n");
		uint8_t fd = (uint8_t)svc_args[0];
		char** data = (char**)svc_args[1];
		uint32_t size = (uint32_t)svc_args[2];
		__sys_read(fd, data, size);
		break;
	case SYS_write:
		fd = (uint8_t)svc_args[0];
		char* toWrite = (char*)svc_args[1];
		__sys_write(fd, toWrite);
		break;
	case SYS_start:
		uint32_t psp = (uint32_t)svc_args[0];
		__sys_start_task(psp);
		break;
	case SYS_yield:
		SCB->ICSR |= (1 << 28); // set PendSV bit
		break;
	case SYS__exit:
		TCB_TypeDef* task = svc_args[16];
		task->status = KILLED;
		break;
	case SYS_getpid:
		uint32_t pid = svc_args[10];
		task = svc_args[16];
		__sys_getpid((unsigned int*)pid, task->task_id);
		break;
	case SYS_reboot:
		kprintf("Will call __sys_reboot\n");
		__sys_reboot();
		break;
	case SYS___time:
		uint32_t time = svc_args[0];
		__sys_get_time((uint32_t*)time);
		break;
	default:;
	}
	/* Handle SVC return here */
}



void SVC_Tester(void) {
	// test scanf
	// char *data = "temp a ja e thakuk";
	// read_user(0,&data,5);
	// kprintf("data(main) = %s\n",data);

	init_dev_table();

	//test fopen and fclose
	char* device_name = "GPIOA";
	uint8_t t_access = 0;
	uint32_t* op_addr = (uint32_t*)GPIOA;
	fopen(device_name, t_access, op_addr);
	print_device_list();

	fclose(op_addr);
	print_device_list();

	//test reboot
	kprintf("Do you want to reboot the OS? (y : 1 /n : 0)\n");
	int if_reboot;
	kscanf("%d", &if_reboot);
	if (if_reboot == 1) {
		reboot();
	}
}
