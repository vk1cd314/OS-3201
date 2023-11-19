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
 
#ifndef __SCHEDULE_H
#define __SCHEDULE_H
#define DUMMY_XPSR  0x01000000U
#include <types.h>
#include <stdint.h>
#include <cm4.h>
#include <kmain.h>
#include <kstdio.h>
#include <unistd.h>
#include <types.h>
#include <task_queue.h>
#include <kstring.h>
#include <schedule_fcfs.h>
#define READY 1
#define RUNNING 2
#define TERMINATED 3
#define KILLED 4
#define SLEEPING 5
#define MAX_TASK 20

#define STOP 		200000
#define TASK_COUNT 	10
#define PER_TASK_TIME 10 //10 ms for each task

extern volatile uint8_t scheduling_algo; //0 for round robin, 1 for fcfs

void schedule_next(void);
void create_tcb(TCB_TypeDef *, void(*task)(void), uint32_t *stack_start);
void start_exec(void);
void scheduling_tester_without_semaphore(void);
void scheduling_tester_fcfs_with_semaphore(void);

#endif


