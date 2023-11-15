#ifndef __DEV_TABLE_H
#define __DEV_TABLE_H
#include <stdint.h>
#include <kstdio.h>
#include <kstring.h>
#include <stm32_peps.h>
#include <types.h>
#define O_RDONLY 0
#define O_WRONLY 1
#define O_APPEND 2

extern dev_table device_list[64];
extern uint32_t device_count;

void __init_dev_table(void);
#endif 

