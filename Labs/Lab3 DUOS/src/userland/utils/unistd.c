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
 
#include <unistd.h>
#include <syscall_def.h>
#include <kstdio.h>
void fopen(char *name,uint8_t t_access, uint32_t *op_addr) {
	__asm volatile (
		"mov r0, %[x]\n"
		"mov r1, %[y]\n"
		: 
		: [x] "r" (name), [y] "r" (t_access)
	);
	__asm volatile(
		"mov r2, %[x]\n"
		:
		: [x] "r" (op_addr)
	);

	__asm volatile ("PUSH {r4-r11, ip, lr}");
	__asm volatile("svc %0" : : "i" (SYS_open));

	__asm volatile ("POP {r4-r11, ip, lr}");
}

void fclose(uint32_t *op_addr){
	__asm volatile (
		"mov r0, %[x]\n"
		:
		: [x] "r" (op_addr)
	);
	__asm volatile ("PUSH {r4-r11, ip, lr}");
	__asm volatile("svc %0" : : "i" (SYS_close));

	__asm volatile ("POP {r4-r11, ip, lr}");
}

void reboot(void){
	__asm volatile ("PUSH {r4-r11, ip, lr}");
	__asm volatile("svc %0" : : "i" (SYS_reboot));

	__asm volatile ("POP {r4-r11, ip, lr}");
}

void read_user(uint8_t fd,char **data,uint32_t size){
	__asm volatile (
		"mov r0, %[x]\n"
		"mov r1, %[y]\n"
		:
		: [x] "r" (fd), [y] "r" (data)
	);
	__asm volatile (
		"mov r2, %[x]\n"
		:
		: [x] "r" (size)
	);
	__asm volatile ("PUSH {r4-r11, ip, lr}");
	__asm volatile("svc %0" : : "i" (SYS_read));

	__asm volatile ("POP {r4-r11, ip, lr}");
}

void write_user(uint8_t fd,char *data){
	__asm volatile (
		"mov r0, %[x]\n"
		"mov r1, %[y]\n"
		:
		: [x] "r" (fd), [y] "r" (data)
	);
    __asm volatile("stmdb r13!, {r5}");

	__asm volatile ("PUSH {r4-r11, ip, lr}");
	__asm volatile("svc %0" : : "i" (SYS_write));
	__asm volatile ("POP {r4-r11, ip, lr}");
}

void yeild(void){
	__asm volatile("svc %0" : : "i" (SYS_yield));

}

void task_exit(void){
    __asm volatile("PUSH {r5}");
    __asm volatile ("PUSH {r4-r11, ip, lr}");
	__asm volatile("svc %0" : : "i" (SYS__exit));
	__asm volatile ("POP {r4-r11, ip, lr}");
    yeild();
}

uint32_t getpid(void){
    unsigned int pid = 0;
    __asm volatile("mov r5, %[v]": : [v] "r" (&pid));
    __asm volatile("PUSH {r5}");

    __asm volatile ("PUSH {r4-r11, ip, lr}");
	__asm volatile("svc %0" : : "i" (SYS_getpid));

	__asm volatile ("POP {r4-r11, ip, lr}");
    return (uint16_t) pid;
}

void start_task(uint32_t psp){
	__asm volatile ("MOV R0, %0"
		:
		:"r" (psp)
	);
	__asm volatile ("PUSH {r4-r11, ip, lr}");
	__asm volatile("svc %0" : : "i" (SYS_start));
	__asm volatile ("POP {r4-r11, ip, lr}");

}

uint32_t get_time(void){
    uint32_t time = 0;
	__asm volatile("mov r0, %[x]": : [x] "r" (&time));
	__asm volatile ("PUSH {r4-r11, ip, lr}");
	__asm volatile("svc %0" : : "i" (SYS___time));
	__asm volatile ("POP {r4-r11, ip, lr}");
	return time;
}