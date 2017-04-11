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
* File Name    : timer_isr.c
* Version      : 1.00
* Device(s)    : 
* Tool-Chain   : 
* H/W Platform : 
* Description  : 
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 01.07.2015 1.00    First Release
******************************************************************************/
#pragma interrupt INTIT timer_isr


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_macro.h"  /* System macro and standard type definition */
#include "timer.h"    /* Timer driver interface */

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/
uint8_t g_time_update_flag;
/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/

/******************************************************************************
Private global variables and functions
******************************************************************************/

/******************************************************************************
* Function Name: timer_isr
* Description  : Interval timer interrupt service routine
*              : TODO: Complete the program
* Arguments    : none
* Return Value : none
******************************************************************************/
__interrupt void timer_isr(void)
{
	//EI();	
g_time_update_flag++;
}

/******************************************************************************
End of file
******************************************************************************/

