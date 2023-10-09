/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    hk32f030m_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
*/
/******************************************************************************/
/*           Cortex-M0 Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void) {
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void) {
  while (1) {}
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void) {
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void) {
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void) {
}

/************************ (C) COPYRIGHT HKMicroChip *****END OF FILE****/
