/******************************************************************************
* DISCLAIMER

* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized.

* This software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.

* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES 
* REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, 
* INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
* PARTICULAR PURPOSE AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY 
* DISCLAIMED.

* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES 
* FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS 
* AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

* Renesas reserves the right, without notice, to make changes to this 
* software and to discontinue the availability of this software.  
* By using this software, you agree to the additional terms and 
* conditions found by accessing the following link:
* http://www.renesas.com/disclaimer
******************************************************************************/
/* Copyright (C) 2015 Renesas Electronics Corporation. All rights reserved.  */
/******************************************************************************	
* File Name    : timer.c
* Version      : 1.00
* Device(s)    : 
* Tool-Chain   : 
* H/W Platform : 
* Description  : 
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 01.07.2015 1.00    First Release
******************************************************************************/


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_macro.h"
#include "timer.h"

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/
/******************************************************************************
* Function Name: timer_init
* Description  : Initialize interval timer driver
* Arguments    : none
* Return Value : none
******************************************************************************/
void timer_init(void)
{
	/* Supply clock to the interval timer */
    RTCEN = 1U;
	/* Disable interval timer operation */
    ITMC = 0x0000U;

	/* Disable interval timer interrupt */
    ITMK = 1U;
	/* Clear interval timer interrupt flag */
    ITIF = 0U;

    /* Set INTIT level 2 priority */
    ITPR1 = 1U;
    ITPR0 = 0U;

	/* Set interval timer compare value */
	/* The compare value is calculated for 100ms interval */
    ITMC = 0x0CCCU;
}

/******************************************************************************
* Function Name: timer_start
* Description  : Start interval timer
* Arguments    : none
* Return Value : none
******************************************************************************/
void timer_start(void)
{
	/* Clear interval timer interrupt flag */
    ITIF = 0U;
	/* Enable interval timer interrupt */
    ITMK = 0U;
	/* Enable interval timer operation */
    ITMC |= 0x8000U;
}

/******************************************************************************
* Function Name: timer_stop
* Description  : Stop interval timer
* Arguments    : none
* Return Value : none
******************************************************************************/
void timer_stop(void)
{
	/* Disable interval timer interrupt */
   ITMK = 1U;
	/* Clear interval timer interrupt flag */
    ITIF = 0U;
	/* Enable interval timer operation */
    ITMC &= 0x7FFFU;
}

/******************************************************************************
Private global variables and functions
******************************************************************************/

/******************************************************************************
End of file
******************************************************************************/

