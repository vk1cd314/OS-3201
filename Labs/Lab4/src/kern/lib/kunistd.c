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
#include <kunistd.h>
#include <cm4.h>
/* Add your functions here */
extern uint32_t device_count;

void __sys_start_task(uint32_t psp){
	asm volatile ("MOV R0, %0"
		:
		:"r" (psp)
	);
	asm volatile ("LDMIA R0!,{R4-R11}");
	asm volatile ("MSR PSP, R0");
	asm volatile ("ISB 0xf" ::: "memory");
	asm volatile ("MOV LR, 0xFFFFFFFD");
	asm volatile ("BX LR");
}

void __sys_open(char *name,uint8_t t_access, uint32_t *op_addr){
    __strcpy(device_list[device_count].name,name);
    device_list[device_count].t_ref++;
    device_list[device_count].t_access = t_access;
    device_list[device_count].op_addr = op_addr;
    device_count++;
}

void __sys_close(uint32_t *op_addr){
    uint32_t delete_index = -1;
    for (int i = 0; i < device_count; i++){
        if (device_list[i].op_addr == op_addr){
            device_list[i].t_ref--;
            if (device_list[i].t_ref == 0){
                delete_index = i;
            }
        }
    }
    if (delete_index != -1){
        for (int i = delete_index; i < device_count - 1; i++){
            device_list[i] = device_list[i+1];
        }
        device_count--;
    }
}

void __sys_reboot(void){
	SCB->AIRCR = 0x05FA0004;
}

void __sys_read(uint8_t fd,char **data,uint32_t size){
    switch(fd)
    {
        case STDIN_FILENO:
            char temp[size];
            uint8_t *buff;
            _USART_READ(USART2,buff,size);
            __strcpy(temp,&buff);
            *data = temp;
            break;
    }
}
void __sys_write(uint8_t fd,char *data){
    switch(fd)
    {
        case STDOUT_FILENO:
            _USART_WRITE(USART2,data);
            break;
    }
}

void __sys_getpid(unsigned int *val,uint16_t value)
{
	*val = value;
	return ;
}

void __sys_get_time(uint32_t *time){
    *time = __getTime();
    // TODO
}



// sem_dec
// Declare for use from C as extern void sem_dec(void * semaphore);
void __sem_dec(uint32_t* semaphore) {
    asm volatile(
        ".macro WAIT_FOR_UPDATE         \n"
        "   WFI                         \n"
        ".endm                          \n"
        );
    
    asm volatile (
        "1: LDREX   r1, [r0]            \n"
        "   CMP	    r1, #0              \n"   // ; Test if semaphore holds the value 0
        "   BEQ     2f                  \n"   // ; If it does, block before retrying
        "   SUB     r1, #1              \n"   // ; If not, decrement temporary copy
        "   STREX   r2, r1, [r0]        \n"   // ; Attempt Store-Exclusive
        "   CMP     r2, #0              \n"   // ; Check if Store-Exclusive succeeded
        "   BNE     1b                  \n"   // ; If Store-Exclusive failed, retry from start
        "   DMB                         \n"   // ; Required before accessing protected resource
        "   BX      lr                  \n"
        "2:                             \n"   // ; Take appropriate action while waiting for semaphore to be incremented
        "   WAIT_FOR_UPDATE             \n"
        "   B       1b                  \n"
        : [r0] "=r" (semaphore));
}

// sem_inc
// Declare for use from C as extern void sem_inc(void * semaphore);
void __sem_inc(uint32_t* semaphore) {
    // kprintf("semaphore %d\n",*semaphore);
    asm volatile(
        ".macro SIGNAL_UPDATE           \n"
        ".endm                          \n"
        );
    asm volatile (
        "1:  LDREX   r1, [r0]           \n"
        "    ADD     r1, #1             \n"   // ; Increment temporary copy
        "    STREX   r2, r1, [r0]       \n"   // ; Attempt Store-Exclusive
        "    CMP     r2, #0             \n"   // ; Check if Store-Exclusive succeeded
        "    BNE     1b                 \n"   // ; Store failed - retry immediately
        "    CMP     r0, #1             \n"   // ; Store successful - test if incremented from zero
        "    DMB                        \n"   // ; Required before releasing protected resource
        "    BGE     2f                 \n"   // ; If initial value was 0, signal update
        "    BX      lr                 \n"
        "2:                             \n"   // ; Signal waiting processors or processes
        "    SIGNAL_UPDATE              \n"
        : [r0] "=r" (semaphore) : );
}


