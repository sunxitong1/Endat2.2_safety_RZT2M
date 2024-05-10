
/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2021 Renesas Electronics Corporation. All rights reserved.
**********************************************************************************************************************
	*/
/*********************************************************************************************************************
	**
* System Name  : RZ/T2M Motor Solution Kit
* File Name    : r_cg_mtu3.c
* Version	   : 1.10
* Device	   : RZ/T2M
* Tool-Chain   : IAR Embedded Workbench for ARM
*				 Renesas e2studio
* OS		   : Not use
* Description  : source file of mtu3.
**********************************************************************************************************************
	*/
/*********************************************************************************************************************
	**
Pragma directive
**********************************************************************************************************************
	*/
/*********************************************************************************************************************
	**
Includes
**********************************************************************************************************************
	*/
#include "r_cg_mtu3.h"
#include "bsp_api.h"

/*********************************************************************************************************************
	**
Global variables and functions
**********************************************************************************************************************
	*/
volatile uint16_t flag_tgra = 0;
volatile uint16_t flag_tgrb = 0;


/*********************************************************************************************************************
	**
* Function Name: R_MTU3_Create
* Description  : This function initializes the MTU3 Unit0 module.
* Arguments    : None
* Return Value : None
**********************************************************************************************************************
	*/
void R_MTU3_Create(void)
{
	volatile unsigned long dummy;

	/* Cancel MTU stop state in LPC */
	dummy = 1u;
	R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_RESET);
	R_BSP_MODULE_START(FSP_IP_MTU3,dummy);
	dummy = BSP_MSTP_REG_FSP_IP_MTU3(dummy);
	dummy = R_MTU5->TSTR;						/* Dummy-read for the module-stop state(2) */
	R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_RESET);

	/* Enable read/write to MTU registers */
	R_MTU->TRWERA_b.RWE = 1U;
	R_MTU->TRWERB_b.RWE = 1U;

	/* Stop all channels */
	R_MTU->TSTRA = 0x00;
	R_MTU5->TSTR = 0x00;
	R_MTU->TSTRB = 0x00;

	/* Set external clock noise filter */
	R_MTU_NF->NFCRC = 0x33; 					/* disable */
	/* -Stop count operation- */
	R_MTU->TSTRA_b.CST3 = 0;
	R_MTU->TSTRA_b.CST4 = 0;
	/* -Counter clock, counter clear source selection- */
	R_MTU3->TCR = 0x00; 						/* counts on PCLKH/1, Count at rising edge, TCNT clearing disabled */
	R_MTU3->TCR2 = 0x00;						/* counts on PCLKH/1 */
	R_MTU4->TCR = 0x00; 						/* counts on PCLKH/1, Count at rising edge, TCNT clearing disabled */
	R_MTU4->TCR2 = 0x00;						/* counts on PCLKH/1 */
	/* -TCNT setting- */
	R_MTU3->TCNT = MTR_TDEAD_CNT_NUM;
	R_MTU4->TCNT = 0x0000;
	/* -Inter-channel synchronization setting- */
	R_MTU->TSYRA |= 0x00;						/* MTU3.TCNT and MTU4.TCNT operates independently */
	/* -TGR setting- */
	R_MTU3->TGRB = MTR_TC_4_CNT_NUM + MTR_TDEAD_CNT_NUM / 2; /* U-phase output compare register */
	R_MTU4->TGRA = MTR_TC_4_CNT_NUM + MTR_TDEAD_CNT_NUM / 2; /* V-phase output compare register */
	R_MTU4->TGRB = MTR_TC_4_CNT_NUM + MTR_TDEAD_CNT_NUM / 2; /* W-phase output compare register */
	R_MTU3->TGRD = MTR_TC_4_CNT_NUM + MTR_TDEAD_CNT_NUM / 2; /* U-phase output buffer register */
	R_MTU4->TGRC = MTR_TC_4_CNT_NUM + MTR_TDEAD_CNT_NUM / 2; /* V-phase output buffer register */
	R_MTU4->TGRD = MTR_TC_4_CNT_NUM + MTR_TDEAD_CNT_NUM / 2; /* W-phase output buffer register */

	/* -Dead time, carrier cycle setting- */
	R_MTU->TDDRA = MTR_TDEAD_CNT_NUM;
	R_MTU->TCDRA = MTR_TC_HALF_CNT_NUM;
	R_MTU3->TGRA = MTR_TC_HALF_CNT_NUM + MTR_TDEAD_CNT_NUM;
	R_MTU3->TGRC = MTR_TC_HALF_CNT_NUM + MTR_TDEAD_CNT_NUM;
	
	/* -Enable PWM cyclic output, set PWM output level- */
	R_MTU->TOCR1A_b.TOCL = 0;					/* Write access to the TOCS, OLSN, and OLSP bits is enabled */
	R_MTU->TOCR1A_b.PSYE = 0;					/* Toggle output is disabled */
	R_MTU->TOCR1A_b.TOCS = 0;					/* TOCR1 setting is selected */
	R_MTU->TOCR1A_b.OLSP = 1;					/* Initial output:H, Active level:L */
	R_MTU->TOCR1A_b.OLSN = 1;					/* Initial output:H, Active level:L */
	/* -Complementary PWM mode setting- */
	R_MTU3->TMDR1_b.MD = 0xE;					/* Complementary PWM mode 2 (transfer at trough) */
	R_MTU3->TMDR1_b.BFA = 1;					/* TGRA and TGRC used together for buffer operation */
	R_MTU3->TMDR1_b.BFB = 1;					/* TGRB and TGRD used together for buffer operation */
	/* A/D converter start request setting */
	R_MTU4->TIER_b.TTGE2 = 1;					/* A/D converter start request generation by MTU4.TCNT underflow (trough) enabled */
	R_MTU3->TIER_b.TTGE = 1;					/* A/D converter start request generation by MTU3 TGRA interrupt (trough) enabled */
	__asm volatile("cpsie i");
	__asm volatile("isb");

}



/***********************************************************************************************************************
* Function Name: R_MTU3_C3_4_6_7_Start
* Description  : This function starts MTU3-4, MTU6-7 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MTU3_C3_4_Start(void)
{
    /* Synchronous Start */
    R_MTU->TCSYSTR |= 0x18;

}

/***********************************************************************************************************************
* Function Name: R_MTU3_C3_4_6_7_Stop
* Description  : This function stops MTU3-4, MTU6-7 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MTU3_C3_4_Stop(void)
{
    R_MTU->TSTRA_b.CST3 = 0u;
    R_MTU->TSTRA_b.CST4 = 0u;
//    R_MTU->TSTRB_b.CST6 = 0u;
//    R_MTU->TSTRB_b.CST7 = 0u;
}



