#include <nvic.h>

/* Functions of NVIC */
void __NVIC_SetPriority (enum IRQn_TypeDef IRQn,uint8_t priority){
	if(IRQn >= 0){
		NVIC->IP[IRQn] = (uint8_t)((priority << 4));
	}
    else{
        // kprintf("SHPR STATE ___________ %d\n",(((uint32_t)IRQn) & 0xFUL)-4UL);
        SCB->SHPR[(((uint32_t)IRQn) & 0xFUL)-4UL] = (uint8_t)((priority << 4) & (uint32_t)0xFFUL);
    }
}

uint8_t __NVIC_GetPriority(enum IRQn_TypeDef IRQn){
	if(IRQn >= 0){
		return (uint8_t)(NVIC->IP[IRQn] >> 4);
	}else{
        return SCB->SHPR[(((uint32_t)IRQn) & 0xFUL)-4UL]  >> (8U - 4U) & (uint32_t)0xFFUL;
    }
}

void __NVIC_EnableIRQn(enum IRQn_TypeDef IRQn){
    if(IRQn >= 0){
        NVIC -> ISER[IRQn/32] |= (1 << (IRQn%32));
    }
}

void __NVIC_DisableIRQn(enum IRQn_TypeDef IRQn){
    if(IRQn >= 0){
        NVIC -> ICER[IRQn/32] |= (1 << (IRQn%32));
    }
}

uint32_t __NVIC_GetActive (enum IRQn_TypeDef IRQn)
{
    if(IRQn >= 0) {
        uint32_t index = IRQn / 32;
        uint32_t position = IRQn % 32;
        // returns active status of interrupt
        return (uint32_t) ( NVIC->IABR[index] & (uint32_t)( 1 << position ) );
    }
    return 0;
}

uint32_t __get_pending_IRQn(enum IRQn_TypeDef IRQn)
{
    if(IRQn >= 0) {
        uint32_t index = IRQn / 32;
        uint32_t position = IRQn % 32;        
        // returns the pending status of an interrupt, 1 = pending, 0 = not pending
        return (uint32_t) ( NVIC->ISPR[index] & (uint32_t)( 1 << position ) );
    }
    return 0;
}

void __clear_pending_IRQn(enum IRQn_TypeDef IRQn) 
{
    if(IRQn >= 0) {
        uint32_t index = IRQn / 32;
        uint32_t position = IRQn % 32;        
        // clears the interrupt pending bit
        NVIC->ICPR[index] &= ~( (uint32_t)(1u << position) );
    }
}

void __set_pending_IRQn(enum IRQn_TypeDef IRQn)
{
    if(IRQn >= 0) {
        uint32_t index = IRQn / 32;
        uint32_t position = IRQn % 32;        
        // clears the interrupt pending bit
        NVIC->ISPR[index] |= ( (uint32_t)(1u << position) );
    }

}

void __disable_irq(void)
{
    __asm volatile ("cpsid i" : : : "memory"); 
}


void __enable_irq()
{
    __asm volatile ("CPSIE i"); // clears primask == enables interrupts
}


void __set_BASEPRI(uint32_t basePri)
{
    basePri = basePri <<4;
    __asm volatile ("MSR basepri, %0" : : "r" (basePri) : "memory");
}

void __unset_BASEPRI(uint32_t value)
{
    // unmask interrupts greater or equal to the given argument/priority number
    __asm volatile ("MOVS R0, #0x0");
    __asm volatile ("MSR BASEPRI, R0");
    __set_BASEPRI(value);
}

void __set_PRIMASK(uint32_t priMask)
{
    __asm volatile ("MSR primask, %0" : : "r" (priMask) : "memory");
}

uint32_t __get_PRIMASK(void)
{
    uint32_t result;
    __asm volatile ("MRS %0, primask" : "=r" (result) );
    return (result);
}

void __enable_fault_irq(void)
{
    __asm volatile ("CPSIE f" : : : "memory");
}
void __set_FAULTMASK(uint32_t faultMask)
{
    __asm volatile ("MSR faultmask, %0" : : "r" (faultMask) : "memory");
}

void __disable_fault_irq(void)
{
    __asm volatile ("CPSID f" : : : "memory");  
}

uint32_t __get_FAULTMASK(void)
{
    uint32_t result;
    __asm volatile ("MRS %0, faultmask" : "=r" (result) );
    return (result);
}

uint32_t __get_BASEPRI(void)
{
    uint32_t result;
    __asm volatile ("MRS %0, basepri" : "=r" (result) );
    return (result>>4);
}



