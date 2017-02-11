/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include <stdbool.h>

#define COUNT_PERIOD_BLINK 500

volatile uint32 gTick = 0;
volatile bool gFlagTurnover = false;

// SysTick Interrupt Handler
CY_ISR(SysTick_Handler)
{
    gTick++;
    if (gTick >= COUNT_PERIOD_BLINK)
    {
        gFlagTurnover = true;
        gTick = 0;
    }
}

int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    // Set the SysTick Interrupt Vector (=15) in Vector Table in RAM
    // see around L740 in CyLib.h 
    CyIntSetSysVector(CY_INT_SYSTICK_IRQN, (cyisraddress)SysTick_Handler);
    // Start SysTick Periodic Interrupt
    SysTick_Config(CYDEV_BCLK__SYSCLK__HZ/1000); // SysTick=1000Hz(1ms)
    // Enable Interrupt Detection
    CyGlobalIntEnable;  // uncomment
    for(;;)
    {
        /* Place your application code here. */
        if (true == gFlagTurnover)
        {
            PO_LED_R_Write(~PO_LED_R_Read()); // Toggle LED Terminal
            gFlagTurnover = false;
        }
    }
}


/* [] END OF FILE */
