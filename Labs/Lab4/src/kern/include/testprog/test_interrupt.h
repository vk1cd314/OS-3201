#ifndef __TEST_INTERRUPT_H
#define __TEST_INTERRUPT_H

#include <gpio.h>
#include <cm4.h>
#include <sys.h>
#include <gpio.h>
#include <stm32_peps.h>
#include <sys.h> // EXTI Config
#include <nvic.h>

void blinky_test_code(void);
void test_set_get_priority(void);
void test_masking(void);
void test_hardfault(void);
void test_sys_tick(void);
void test_all(void);
#endif