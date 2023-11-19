#include <task_queue.h>


void init_queue(void){
	//init ready queue
	tcb_queue.size = 0;
	tcb_queue.max = MAX_TASKS;
	tcb_queue.st = 0;
	tcb_queue.ed = -1;
	//init waiting queue
	sem_queue.size = 0;
	sem_queue.max = MAX_TASKS;
	sem_queue.st = 0;
	sem_queue.ed = -1;
}

void push_task(TCB_TypeDef *task){
	if (tcb_queue.size == tcb_queue.max){
		return;
	}
	tcb_queue.ed = (tcb_queue.ed + 1) % tcb_queue.max;
	tcb_queue.q[tcb_queue.ed] = task;
	tcb_queue.size++;
}
TCB_TypeDef* pop_task(){
	if (tcb_queue.size == 0){
		push_task(&tcb_queue.sleep);
	}

	TCB_TypeDef *task = tcb_queue.q[tcb_queue.st];
	tcb_queue.st = (tcb_queue.st + 1) % tcb_queue.max;
	tcb_queue.size--;
	return task;
}


void push_sem(TCB_TypeDef *task){
	if (sem_queue.size == sem_queue.max){
		return;
	}
	sem_queue.ed = (sem_queue.ed + 1) % sem_queue.max;
	sem_queue.q[sem_queue.ed] = task;
	sem_queue.size++;
}

TCB_TypeDef *pop_sem(void){
	if (sem_queue.size == 0){
		return;
	}
	TCB_TypeDef *task = sem_queue.q[sem_queue.st];
	sem_queue.st = (sem_queue.st + 1) % sem_queue.max;
	sem_queue.size--;
	return task;
}

int is_sem_empty(void){
	return sem_queue.size == 0;
}