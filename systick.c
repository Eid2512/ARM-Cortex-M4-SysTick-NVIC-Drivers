/*
 * systick.c
 *
 *  Created on: Dec 12, 2024
 *      Author: Eid
 */
#include "systick.h"



static volatile void (*SysTick_Callback)(void) = NULL;


/*********************************************************************
 * Service Name: SysTick_Init
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): a_TimeInMilliSeconds - Time in milliseconds to set the SysTick timer
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description:
 * This function initializes the SysTick timer by setting up the reload value
 * based on the provided time in milliseconds. It configures the clock source
 * to be the system clock and enables the SysTick timer.
 **********************************************************************/
void SysTick_Init(uint16 a_TimeInMilliSeconds){
    /* Enable clock for PORTF and wait for clock to start */
    SYSCTL_RCGCGPIO_REG |= 0x20;
    while(!(SYSCTL_PRGPIO_REG & 0x20));


    uint32 reloadValue =
    ((SYSTEM_CLOCK_HZ / 1000UL) * a_TimeInMilliSeconds) - 1UL;

    if (reloadValue > 0xFFFFFF) { // Check for maximum reload value
        reloadValue = 0xFFFFFF;
    }

    SYSTICK_CTRL_REG = 0;              /* Disable the SysTick Timer by Clear the ENABLE Bit */
    SYSTICK_RELOAD_REG  = reloadValue;        /* Set the Reload value */
    SYSTICK_CURRENT_REG = 0;              /* Clear the Current Register value */
    /* Configure the SysTick Control Register
     * Enable the SysTick Timer (ENABLE = 1)
     * Enable SysTick Interrupt (INTEN = 1)
     * Choose the clock source to be System Clock (CLK_SRC = 1) */
    SYSTICK_CTRL_REG   |= 0x07;
}

/*********************************************************************
 * Service Name: SysTick_StartBusyWait
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): a_TimeInMilliSeconds - Time in milliseconds to wait
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description:
 * This function configures the SysTick timer to create a busy-wait delay for
 * the specified number of milliseconds. The function waits for the timer to
 * reach zero before returning.
 **********************************************************************/
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds){
    /* Enable clock for PORTF and wait for clock to start */
    SYSCTL_RCGCGPIO_REG |= 0x20;
    while(!(SYSCTL_PRGPIO_REG & 0x20));

    uint32 reloadValue = SYSTICK_RELOAD_VALUE * a_TimeInMilliSeconds;

    if (reloadValue > 0xFFFFFF) { // Check for maximum reload value
        reloadValue = 0xFFFFFF;
    }

    SYSTICK_CTRL_REG = 0;              /* Disable the SysTick Timer by Clear the ENABLE Bit */
    SYSTICK_RELOAD_REG  = reloadValue;        /* Set the Reload value */
    SYSTICK_CURRENT_REG = 0;              /* Clear the Current Register value */
    /* Configure the SysTick Control Register
     * Enable the SysTick Timer (ENABLE = 1)
     * Disable SysTick Interrupt (INTEN = 0)
     * Choose the clock source to be System Clock (CLK_SRC = 1) */
    SYSTICK_CTRL_REG   |= 0x05;

    while ((SYSTICK_CTRL_REG & (1 << 16)) == 0) {
        // Wait for flag to be set
    }
    SYSTICK_CTRL_REG    = 0;
}



/*********************************************************************
 * Service Name: SysTick_Handler
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description:
 * This function is the SysTick interrupt handler. It is called automatically
 * when the SysTick timer reaches zero.
 **********************************************************************/
void SysTick_Handler(void){
    if (SysTick_Callback != NULL) {
        SysTick_Callback();
    }
}


/*********************************************************************
 * Service Name: SysTick_SetCallBack
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Ptr2Func - A pointer to the callback function
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: This function sets a callback function that will be called when the SysTick
 **********************************************************************/
void SysTick_SetCallBack(volatile void (*Ptr2Func) (void)){
    SysTick_Callback = Ptr2Func;
}


/*********************************************************************
 * Service Name: SysTick_Stop
 * Sync/Async: Synchronous
 * Reentrancy: Non-reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: This function stops the SysTick timer by clearing the ENABLE bit in the SysTick control register.
 **********************************************************************/
void SysTick_Stop(void){
    SYSTICK_CTRL_REG &= ~0x01; // Clear the ENABLE bit
}

/*********************************************************************
 * Service Name: SysTick_Start
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: This function starts the SysTick timer by setting the ENABLE bit in the SysTick control register.
 **********************************************************************/
void SysTick_Start(void){
    SYSTICK_CTRL_REG |= 0x01; // Set the ENABLE bit
}

/*********************************************************************
 * Service Name: SysTick_DeInit
 * Sync/Async: Synchronous
 * Reentrancy: Non-reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: This function deinitializes the SysTick timer by disabling the timer,
 *              clearing the reload value, resetting the current value, and clearing the callback.
 **********************************************************************/
void SysTick_DeInit(void){
    SYSTICK_CTRL_REG = 0;             // Disable SysTick
    SYSTICK_RELOAD_REG = 0;           // Reset reload value
    SYSTICK_CURRENT_REG = 0;          // Reset current value
    SysTick_Callback = NULL;          // Clear callback
}


