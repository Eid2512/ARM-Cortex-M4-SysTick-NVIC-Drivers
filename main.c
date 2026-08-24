

#include "systick.h"
#include "nvic.h"

volatile uint32 tickCount = 0;

void SysTick_AppCallback(void)
{
    tickCount++;
}

int main(void)
{
    SysTick_SetCallBack(SysTick_AppCallback);
    SysTick_Init(1);

    NVIC_SetPriorityException(EXCEPTION_SYSTICK_TYPE, 2);

    while (1)
    {
        /* Application code */
    }
}