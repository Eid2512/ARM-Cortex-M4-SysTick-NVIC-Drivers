/*
 * systick.h
 *
 *  Created on: Dec 12, 2024
 *      Author: Eid
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "tm4c123gh6pm_registers.h"

#define clockSpeed 16000000
#define SYSTICK_RELOAD_VALUE ((clockSpeed / 1000) - 1) // Assuming 1ms time base

void SysTick_Init(uint16 a_TimeInMilliSeconds);
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds);
void SysTick_Handler(void);
void SysTick_SetCallBack(volatile void (*Ptr2Func) (void));
void SysTick_Stop(void);
void SysTick_Start(void);
void SysTick_DeInit(void);


#endif /* SYSTICK_H_ */
