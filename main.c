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
* File Name    : main.c
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
#include "r_macro.h"  /* System macro and standard type definition */
#include "r_spi_if.h" /* SPI driver interface */
#include "lcd.h"      /* LCD driver interface */
#include "intp.h"     /* External Interrupt interface */
#include "timer.h"    /* Timer driver interface */
#include "stdio.h"    /* Standard IO library: sprintf */

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Macro definitions

******************************************************************************/
#define SETTING 1 // Setting...
#define COUNTING 2 // Counting...
#define PAUSED 3 // Paused...
int time=0;
char * string_shown_on_lcd[10];
int flag=SETTING;
int swt=0;
int i=0;
g_time.minute=0;
g_time.second=0;
int prev=0;
int output=0;
int match_times;

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/

/******************************************************************************
Private global variables and functions
******************************************************************************/
void r_main_userinit(void);
void ClearChattering(){
	if(prev!=swt){
		match_times=0;
		prev=swt;
	}
	else{
		match_times=match_times+1;
		if(match_times>2){
			match_times=0
			output=swt;
		}
	}
}

/******************************************************************************
* Function Name: main
* Description  : Main program
* Arguments    : none
* Return Value : none
******************************************************************************/
void main(void)
{
	/* Local time structure to temporary store the global time */
	time_t p_time;

	/* Initialize user system */
	r_main_userinit();
	
	/* Clear LCD display */
	ClearLCD();
	DisplayLCD(LCD_LINE1, (uint8_t *)"Setting");
	sprintf(string_shown_on_lcd,"%0.2d:%0.2d ",g_time.minute, g_time.second);
	DisplayLCD(LCD_LINE2,string_shown_on_lcd);
	/* Initialize external interrupt for switches */
	intp_init();
	
	/* Main loop - Infinite loop */
	
	while (1) 
	{
		ClearChattering();
		if(output==1){
			if(flag==SETTING){
				g_time.second=g_time.second+1;
				if(g_time.second>59){
					g_time.second=0;
					g_time.minute=g_time.minute+1;
				}
			}
			DisplayLCD(LCD_LINE1, (uint8_t *)"Setting");
			sprintf(string_shown_on_lcd,"%0.2d:%0.2d ",g_time.minute, g_time.second);
			DisplayLCD(LCD_LINE2,string_shown_on_lcd);
		}
		
		if(output==2){
			if(flag==SETTING){
				g_time.minute=g_time.minute+1;
				DisplayLCD(LCD_LINE1, (uint8_t *)"Setting");
				
			}
			if(flag==PAUSED){ 
				g_time.minute=0;
				g_time.second=0;
				DisplayLCD(LCD_LINE1, (uint8_t *)"Setting");
				flag=SETTING;
			}
			sprintf(string_shown_on_lcd,"%0.2d:%0.2d ",g_time.minute, g_time.second);
			DisplayLCD(LCD_LINE2,string_shown_on_lcd);
		}
		if(output==3){
			if(flag==SETTING){
				flag=COUNTING;
				DisplayLCD(LCD_LINE1, (uint8_t *)"Counting");
			}
			if(flag==PAUSED){
				DisplayLCD(LCD_LINE1, (uint8_t *)"Counting");
				flag=COUNTING;
			}
			if(flag==COUNTING){
				flag=PAUSED;
				DisplayLCD(LCD_LINE1,(uint8_t *)"Paused");
			}
			
		}
		if ( (flag==COUNTING) && ((g_time.minute!=0) || (g_time.second!=0))) {
				g_time.second--;
				if(g_time.second==0){
					if(g_time.minute!=0) {
						g_time.second=59;
						g_time.minute=g_time.minute-1;
					}
					else {
						output=1;
						flag=SETTING;
						DisplayLCD(LCD_LINE1, (uint8_t *)"Setting");
						//sprintf(string_shown_on_lcd,"%0.2d:%0.2d ",g_time.minute, g_time.second);
						//DisplayLCD(LCD_LINE2,string_shown_on_lcd);
					}
				}
				if(g_time.minute==255){
					g_time.minute=0;
				}
				if(g_time.second==255){
					g_time.second=0;
				}
				DisplayLCD(LCD_LINE1, (uint8_t *)"Counting");
				sprintf(string_shown_on_lcd,"%0.2d:%0.2d ",g_time.minute, g_time.second);
				DisplayLCD(LCD_LINE2,string_shown_on_lcd);
				for(i=0; i<=100; i++){
					Wait1CentiSecond();
				}
			}
			
		
	}
}	

/******************************************************************************
* Function Name: r_main_userinit
* Description  : User initialization routine
* Arguments    : none
* Return Value : none
******************************************************************************/
void r_main_userinit(void)
{
	uint16_t i;

	/* Enable interrupt */
	EI();

	/* Output a logic LOW level to external reset pin*/
	P13_bit.no0 = 0;
	for (i = 0; i < 1000; i++)
	{
		NOP();
	}

	/* Generate a raising edge by ouput HIGH logic level to external reset pin */
	P13_bit.no0 = 1;
	for (i = 0; i < 1000; i++)
	{
		NOP();
	}

	/* Output a logic LOW level to external reset pin, the reset is completed */
	P13_bit.no0 = 0;
	
	/* Initialize SPI channel used for LCD */
	R_SPI_Init(SPI_LCD_CHANNEL);
	
	/* Initialize Chip-Select pin for LCD-SPI: P145 (Port 14, pin 5) */
	R_SPI_SslInit(
		SPI_SSL_LCD,             /* SPI_SSL_LCD is the index defined in lcd.h */
		(unsigned char *)&P14,   /* Select Port register */
		(unsigned char *)&PM14,  /* Select Port mode register */
		5,                       /* Select pin index in the port */
		0,                       /* Configure CS pin active state, 0 means active LOW level  */
		0                        /* Configure CS pin active mode, 0 means active per transfer */
	);
	
	/* Initialize LCD driver */
	InitialiseLCD();	
}

/******************************************************************************
End of file
******************************************************************************/

