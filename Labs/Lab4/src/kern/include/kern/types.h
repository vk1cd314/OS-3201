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

#ifndef __TYPES_H
#define __TYPES_H
/*
 * Task, thread or process header
 */
#include <stdint.h>
typedef struct dev_t
{
	char name[32];	   // Device name or symbol
	uint32_t t_ref;	   // Number of open count
	uint8_t t_access;  // open type O_RDONLY, O_WRDONLY, O_APPEND
	uint32_t *op_addr; // Address of the datastructure operations
} dev_table;
typedef struct task_tcb
{
	uint32_t magic_number;	   // here it is 0xFECABAA0
	uint32_t digital_sinature; // current value is 0x00000001
	uint16_t task_id;		   // a unsigned 16 bit integer starting from 1000
	uint16_t status;		   // task status: running, waiting, ready, killed, or terminated
	uint32_t start_time_t;	   // process creation time
	uint32_t response_time_t;   // first time CPU allocation (execution) time
	uint32_t execution_time;   // total execution time (in ms)
	uint32_t waiting_time;	   // total waiting time (in ms)
	uint32_t priority;		   // task priority
	uint32_t *psp;			   // task stack pointer or stackframe address
} TCB_TypeDef;


#endif
