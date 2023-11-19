#ifndef __TASK_QUEUE_H
#define __TASK_QUEUE_H

#include <types.h>
#include <schedule.h>
typedef struct ready_queue{
	int size;
	int max;
	int st;
	int ed;
	int q_type; // 0 for ready queue, 1 for waiting queue
	TCB_TypeDef *q[30];
	TCB_TypeDef *current_task;
	TCB_TypeDef sleep;
} TaskQueue_TypeDef;

typedef struct waiting_queue{
	int size;
	int max;
	int st;
	int ed;
	int q_type; // 0 for ready queue, 1 for waiting queue
	TCB_TypeDef *q[30];
} WaitingQueue_TypeDef;



extern volatile TaskQueue_TypeDef tcb_queue;
extern volatile WaitingQueue_TypeDef sem_queue;

void init_queue(void);
void push_task(TCB_TypeDef *task);
void push_sem(TCB_TypeDef *task);
TCB_TypeDef *pop_task(void);
TCB_TypeDef *pop_sem(void);
int is_sem_empty(void);
#endif