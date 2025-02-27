/*
 * nvic.c
 *
 *  Created on: Dec 12, 2024
 *      Author: Eid
 */

#include "nvic.h"


/*********************************************************************
 * Service Name: NVIC_EnableIRQ
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to enable Interrupt request for specific IRQ
**********************************************************************/
void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num){
    NVIC_IRQType IRQ_Num_final;
    if(IRQ_Num < 32 ){
        IRQ_Num_final = IRQ_Num;
        NVIC_EN0_REG |= (1 << IRQ_Num_final);
    }
    else if( 32 < IRQ_Num < 64 ){
        IRQ_Num_final = IRQ_Num - 32;
        NVIC_EN1_REG |= (1 << IRQ_Num_final);

    }
    else if( 64 < IRQ_Num < 96 ){
        IRQ_Num_final = IRQ_Num - 64;
        NVIC_EN2_REG |= (1 << IRQ_Num_final);
    }
    else if( 96 < IRQ_Num < 128 ){
        IRQ_Num_final = IRQ_Num - 96;
        NVIC_EN3_REG |= (1 << IRQ_Num_final);
    }
    else if(IRQ_Num > 128 ){
        IRQ_Num_final = IRQ_Num - 128;
        NVIC_EN4_REG |= (1 << IRQ_Num_final);
    }
}


/*********************************************************************
 * Service Name: NVIC_DisableIRQ
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to disable Interrupt request for specific IRQ
**********************************************************************/
void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num){
    NVIC_IRQType IRQ_Num_final;
    if(IRQ_Num < 32 ){
        IRQ_Num_final = IRQ_Num;
        NVIC_DIS0_REG |= (1 << IRQ_Num_final);
    }
    else if( 32 < IRQ_Num < 64 ){
        IRQ_Num_final = IRQ_Num - 32;
        NVIC_DIS1_REG |= (1 << IRQ_Num_final);

    }
    else if( 64 < IRQ_Num < 96 ){
        IRQ_Num_final = IRQ_Num - 64;
        NVIC_DIS2_REG |= (1 << IRQ_Num_final);
    }
    else if( 96 < IRQ_Num < 128 ){
        IRQ_Num_final = IRQ_Num - 96;
        NVIC_DIS3_REG |= (1 << IRQ_Num_final);
    }
    else if(IRQ_Num > 128 ){
        IRQ_Num_final = IRQ_Num - 128;
        NVIC_DIS4_REG |= (1 << IRQ_Num_final);
    }
}

/*********************************************************************
 * Service Name: NVIC_SetPriorityIRQ
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in):
 *  * IRQ_Num - Number of the IRQ from the target vector table
 *  * IRQ_Priority - Priority level to be assigned to the IRQ
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to set the priority for specific IRQ
**********************************************************************/
void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num, NVIC_IRQPriorityType IRQ_Priority){

    uint8 regIndex = IRQ_Num / 4; // to get the index of register
    // each interrupt priority register contains 4 interrupts from vector table
    // regIndex acts as offset to define the address of the required register


    uint8 priorityField = (IRQ_Num % 4) * 8 + 5; // the position of IRQ
    // %4 --> to select the position between the enable registers
    // *8 --> because each register 8 bits
    // +5 --> usage of the top three bits

    volatile uint32 *priorityReg = &NVIC_PRI0_REG + regIndex; // regIndex acts as offset to define the required enable register

    *priorityReg = (*priorityReg & ~(0xFF << priorityField ) ) | (IRQ_Priority << priorityField);// assign the priority level to the required IRQ
}



/*********************************************************************
 * Service Name: NVIC_EnableException
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Exception_Num - The number of the system exception to enable
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Enable a specific fault or system exception
**********************************************************************/

void NVIC_EnableException(NVIC_ExceptionType Exception_Num){
    Enable_Exceptions();
    Enable_Faults();
    if(Exception_Num == EXCEPTION_MEM_FAULT_TYPE){
        //NVIC_SYSTEM_SYSHNDCTRL |= MEM_FAULT_ENABLE_MASK;
        NVIC_SYSTEM_SYSHNDCTRL |= (1 <<MEM_FAULT_BIT_POS);
    }
    else if(Exception_Num == EXCEPTION_BUS_FAULT_TYPE){

        //NVIC_SYSTEM_SYSHNDCTRL |= BUS_FAULT_ENABLE_MASK;
        NVIC_SYSTEM_SYSHNDCTRL |= (1 <<BUS_FAULT_BIT_POS);
    }
    else if(Exception_Num == EXCEPTION_USAGE_FAULT_TYPE){
        //NVIC_SYSTEM_SYSHNDCTRL |= USAGE_FAULT_ENABLE_MASK;
        NVIC_SYSTEM_SYSHNDCTRL |= (1 <<USAGE_FAULT_BIT_POS);
    }
    else if(Exception_Num ==  EXCEPTION_SYSTICK_TYPE){
        SYSTICK_CTRL_REG   |= 0x02;
    }
    else if(Exception_Num == EXCEPTION_SVC_TYPE){
        NVIC_SYSTEM_SYSHNDCTRL |= (1 <<SVC_BIT_POS);
    }
    else if(Exception_Num == EXCEPTION_PEND_SV_TYPE){
        NVIC_SYSTEM_SYSHNDCTRL |= (1 <<PENDSV_BIT_POS);
    }

}


/*********************************************************************
 * Service Name: NVIC_DisableException
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Exception_Num - The number of the system exception to enable
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Disable a specific fault or system exception
**********************************************************************/
void NVIC_DisableException(NVIC_ExceptionType Exception_Num){
    if(Exception_Num == EXCEPTION_MEM_FAULT_TYPE){
        NVIC_SYSTEM_SYSHNDCTRL &= ~MEM_FAULT_ENABLE_MASK ;
    }
    else if(Exception_Num ==  EXCEPTION_BUS_FAULT_TYPE){
        NVIC_SYSTEM_SYSHNDCTRL &= ~BUS_FAULT_ENABLE_MASK;
    }
    else if(Exception_Num ==  EXCEPTION_USAGE_FAULT_TYPE){
        NVIC_SYSTEM_SYSHNDCTRL &= ~USAGE_FAULT_ENABLE_MASK;
    }
    else if(Exception_Num ==  EXCEPTION_SVC_TYPE){
        NVIC_SYSTEM_SYSHNDCTRL &= ~(1 <<SVC_BIT_POS);
    }
    else if(Exception_Num ==  EXCEPTION_PEND_SV_TYPE){
        NVIC_SYSTEM_SYSHNDCTRL &= ~(1 <<PENDSV_BIT_POS);
    }
    else if(Exception_Num ==  EXCEPTION_SYSTICK_TYPE){
        SYSTICK_CTRL_REG   &= ~0x02;
    }
}


/*********************************************************************
 * Service Name: NVIC_SetPriorityException
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in):
 *  * Exception_Num - Number of the exception from the target vector table
 *  * Exception_Priority - Priority level to be assigned to the exception
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to set the priority for specific exception or fault
**********************************************************************/
void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num, NVIC_ExceptionPriorityType Exception_Priority){

    if (Exception_Num == EXCEPTION_MEM_FAULT_TYPE) {
        NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & ~MEM_FAULT_PRIORITY_MASK) | (Exception_Priority << MEM_FAULT_PRIORITY_BITS_POS);
    }
    else if (Exception_Num == EXCEPTION_BUS_FAULT_TYPE) {
        NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & ~BUS_FAULT_PRIORITY_MASK) | (Exception_Priority << BUS_FAULT_PRIORITY_BITS_POS);
    }
    else if (Exception_Num == EXCEPTION_USAGE_FAULT_TYPE) {
        NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & ~USAGE_FAULT_PRIORITY_MASK) | (Exception_Priority << USAGE_FAULT_PRIORITY_BITS_POS);
    }
    else if (Exception_Num == EXCEPTION_SVC_TYPE) {
        NVIC_SYSTEM_PRI2_REG = (NVIC_SYSTEM_PRI2_REG & ~SVC_PRIORITY_MASK) | (Exception_Priority << SVC_PRIORITY_BITS_POS);
    }
    else if (Exception_Num == EXCEPTION_DEBUG_MONITOR_TYPE) {
        NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG & ~DEBUG_MONITOR_PRIORITY_MASK) | (Exception_Priority << DEBUG_MONITOR_PRIORITY_BITS_POS);
    }
    else if (Exception_Num == EXCEPTION_PEND_SV_TYPE) {
        NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG & ~PENDSV_PRIORITY_MASK) | (Exception_Priority << PEND_SV_PRIORITY_BITS_POS);
    }
    else if (Exception_Num == EXCEPTION_SYSTICK_TYPE) {
        NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG & ~SYSTICK_PRIORITY_MASK) | (Exception_Priority << SYSTICK_PRIORITY_BITS_POS);
    }
    /*
    uint8_t regIndex = Exception_Num / 4; // to get the index of register
    uint8_t priorityField = (Exception_Num % 4) * 8 + 5; // the position of Exception
    // %4 --> to select the position between the enable registers
    // *8 --> because each register 8 bits
    // +5 --> usage of the top three bits

    volatile uint32_t *priorityReg = &NVIC_SYSTEM_PRI1_REG + regIndex; // regIndex acts as offset to define the required enable register

    *priorityReg = (*priorityReg & ~(0xFF << priorityField ) ) | (Exception_Priority << priorityField);// assign the priority level to the required Exception
    */
}





