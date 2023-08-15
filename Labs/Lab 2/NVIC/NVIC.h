
/* Functions of NVIC */
void __NVIC_SetPriority (IRQn_TypeDef IRQn,uint32_t priority);
uint32_t __NVIC_GetPriority(IRQn_TypeDef IRQn);
void __NVIC_EnableIRQn(IRQn_TypeDef IRQn);
void __NVIC_DisableIRQn(IRQn_TypeDef IRQn);
void __disable_irq();
void __set_BASEPRI(uint32_t value);
void __enable_irq();
void __unset_BASEPRI(uint32_t value);
void __set_PRIMASK(uint32_t priMask);
uint32_t __get_PRIMASK(void);
void __enable_fault_irq(void);
void __set_FAULTMASK(uint32_t faultMask);
void __disable_fault_irq(void);
uint32_t __get_FAULTMASK(void);
void __clear_pending_IRQn(IRQn_TypeDef IRQn);
uint32_t __get_pending_IRQn(IRQn_TypeDef IRQn);
uint32_t __NVIC_GetActive (IRQn_TypeDef IRQn);


