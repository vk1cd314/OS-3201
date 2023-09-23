#include <sys.h>

/* Functions of NVIC */
// void __NVIC_SetPriority(IRQn_TypeDef IRQn, uint32_t priority) {
//     if (IRQn >= 0) {
//         NVIC->IP[IRQn] = (uint8_t)((priority << 4));
//     }
// }

// uint32_t __NVIC_GetPriority(IRQn_TypeDef IRQn) {
//     if (IRQn >= 0) {
//         return (NVIC->IP[IRQn] >> 4);
//     }
// }

// void __NVIC_EnableIRQn(IRQn_TypeDef IRQn) {
//     if (IRQn >= 0) {
//         NVIC->ISER[IRQn / 32] |= (1 << (IRQn % 32));
//     }
// }

// void __NVIC_DisableIRQn(IRQn_TypeDef IRQn) {
//     if (IRQn >= 0) {
//         NVIC->ICER[IRQn / 32] |= (1 << (IRQn % 32));
//     }
// }

// void __disable_irq() {
//     __asm volatile("mov r0,#1");
//     __asm volatile("msr primask,r0;");
// }

// void __set_BASEPRI(uint32_t value) {
//     __asm volatile("mov r0, %0" : "=r"(value));
//     __asm volatile("msr basepri, r0;");
// }

// void __enable_irq() {
//     __asm volatile("mov r0,#0");
//     __asm volatile("msr primask,r0;");
// }

// void __unset_BASEPRI(uint32_t value) {
//     __asm volatile("mov r0,#0");
//     __asm volatile("msr basepri,r0;");
// }

// void __set_PRIMASK(uint32_t priMask) {
//     __asm volatile("mov r0, #1");
//     __asm volatile("msr primask, r0");
// }

// uint32_t get_PRIMASK(void) {
//     uint32_t value;
//     __asm volatile("mrs r0,primask");
//     __asm volatile("mov %0,r0"
//         : "=r"(value));
//     return value;
// }

// void __enable_fault_irq(void) {
//     __asm volatile("mov r0, #0");
//     __asm volatile("msr primask, r0");
// }

// void __set_FAULTMASK(uint32_t faultMask) {
//     __asm volatile("mov r0, #1");
//     __asm volatile("msr primask, r0");
// }

// void __disable_fault_irq(void) {
//     __asm volatile("mov r0, #1");
//     __asm volatile("msr primask, r0");
// }

// uint32_t __get_FAULTMASK(void) {
//     uint32_t value;
//     __asm volatile("mrs r0,faultmask");
//     __asm volatile("mov %0,r0"
//         : "=r"(value));
//     return value;
// }

// void __clear_pending_IRQn(IRQn_TypeDef IRQn) {
//     if (IRQn >= 0) {
//         NVIC->ICPR[IRQn / 32] |= (1 << (IRQn % 32));
//     }
// }

// uint32_t __get_pending_IRQn(IRQn_TypeDef IRQn) {
//     uint32_t pendingState;
//     if (IRQn >= 0) {
//         int regNumber = IRQn / 32;
//         int offset = IRQn % 32;
//         pendingState = NVIC->ICPR[regNumber] & (1 << regNumber);
//         pendingState = pendingState >> 5;
//         return pendingState;
//     }
// }

// uint32_t __NVIC_GetActive(IRQn_TypeDef IRQn) {
//     uint32_t pendingState;
//     if (IRQn >= 0) {
//         int regNumber = IRQn / 32;
//         int offset = IRQn % 32;
//         pendingState = NVIC->IABR[regNumber] & (1 << regNumber);
//         pendingState = pendingState >> 5;
//         return pendingState;
//     }
// }
