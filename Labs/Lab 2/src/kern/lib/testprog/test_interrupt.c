#include <test_interrupt.h>

void test_hardfault(void) {
    __asm("udf #1");
}