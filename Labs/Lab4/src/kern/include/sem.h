#ifndef __SEM_H
#define __SEM_H
#include <stdint.h>
#include <kstdio.h>
#include <schedule.h>
#include <kstring.h>
#include <types.h>
#include <task_queue.h>

extern void sem_dec(uint32_t* semaphore);
extern void sem_inc(uint32_t* semaphore);
void wait(void);
void signal(void);
extern volatile int task_semaphore;
#endif