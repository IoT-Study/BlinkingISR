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

volatile bool gFlagTurnover = false;
CY_ISR(isr_1_isr){
    
    gFlagTurnover = true;
}

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    isr_1_StartEx(isr_1_isr);
    
    PWM_1_Start();
    PWM_2_Start();
    
    for(;;)
    {
        /* Place your application code here. */
        if(true == gFlagTurnover){
            PWM_2_WriteCompare1(~PWM_2_ReadCompare1());
            gFlagTurnover = false;
        }
    }
}

/* [] END OF FILE */
