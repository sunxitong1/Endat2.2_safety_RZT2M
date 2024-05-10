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
* Copyright (C) 2022 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* System Name  : Encoder I/F
* File Name    : r_endat_rzt2_dat.h
* Version      :
* Device       : RZ
* Abstract     : Header file of EnDat configuration data.
* Tool-Chain   : IAR Embedded Workbench for ARM
*                Renesas e2studio
* OS           : Not use
* H/W Platform : RZ/T2
* Description  : Header file for using EnDat configuration data.
* Limitation   : None
*******************************************************************************/
/*******************************************************************************
* History      : History is managed by Revision Control System.
*******************************************************************************/

#ifndef R_ENDAT_RZT2_DAT_H
#define R_ENDAT_RZT2_DAT_H

/*******************************************************************************
Includes <System Includes> , "Project Includes"
*******************************************************************************/
#include "r_ecl_rzt2_if.h"
/*******************************************************************************
Macro definitions
*******************************************************************************/
#define R_ENDAT0_ID     (R_ECL_CH_0)
#define R_ENDAT1_ID     (R_ECL_CH_1)
#define R_ENDAT_FREQ    (16670UL) // 16.67MHz

/*******************************************************************************
Typedef definitions
*******************************************************************************/

/*******************************************************************************
Public Functions
*******************************************************************************/

#endif /* R_ENDAT_RZT2_DAT_H */
