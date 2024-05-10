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
***********************************************************************************************************************/

/***********************************************************************************************************************
* System Name  : RZ/T2M Motor Solution Kit
* File Name    : r_cg_mtu3.h
* Version      : 1.10
* Device       : RZ/T2M
* Tool-Chain   : IAR Embedded Workbench for ARM
*                Renesas e2studio
* OS           : Not use
* Description  : Header file of mtu3.  
***********************************************************************************************************************/
#ifndef MTU3_H
#define MTU3_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Timer Control Register (TCR) & (TCR2)
*/
/* Time Pre-scaler Select (TPSC[2:0]) & (TPSC2[2:0])*/
#define _MTU_PCLK_1                       (0x00U) /* Internal clock: counts on PCLK/1 */
#define _MTU_PCLK_2                       (0x01U) /* Internal clock: counts on PCLK/2 */
#define _MTU_PCLK_4                       (0x01U) /* Internal clock: counts on PCLK/4 */
#define _MTU_PCLK_8                       (0x02U) /* Internal clock: counts on PCLK/8 */
#define _MTU_PCLK_16                      (0x02U) /* Internal clock: counts on PCLK/16 */
#define _MTU_PCLK_32                      (0x03U) /* Internal clock: counts on PCLK/32 */
#define _MTU_PCLK_64                      (0x03U) /* Internal clock: counts on PCLK/64 */
#define _MTU_PCLK_256_04                  (0x04U) /* Internal clock: counts on PCLK/256 */
#define _MTU_PCLK_256_06                  (0x06U) /* Internal clock: counts on PCLK/256 */
#define _MTU_PCLK_1024_04                 (0x04U) /* Internal clock: counts on PCLK/1024 */
#define _MTU_PCLK_1024_05                 (0x05U) /* Internal clock: counts on PCLK/1024 */
#define _MTU_PCLK_1024_07                 (0x07U) /* Internal clock: counts on PCLK/1024 */
#define _MTU_COUNT                        (0x07U) /* Counts on MTU2.TCNT overflow/underflow */
#define _MTU_MTCLKA_04                    (0x04U) /* External clock: counts on MTCLKA pin input */
#define _MTU_MTCLKA_06                    (0x06U) /* External clock: counts on MTCLKA pin input */
#define _MTU_MTCLKB_05                    (0x05U) /* External clock: counts on MTCLKB pin input */
#define _MTU_MTCLKB_07                    (0x07U) /* External clock: counts on MTCLKB pin input */
#define _MTU_MTCLKC_06                    (0x06U) /* External clock: counts on MTCLKC pin input */
#define _MTU_MTCLKD_07                    (0x07U) /* External clock: counts on MTCLKD pin input */
#define _MTU_MTIOC1A                      (0x07U) /* External clock: counts on MTIOC1A pin output */
/* Clock Edge Select (CKEG[1:0]) */
#define _MTU_CKEG_RISE                    (0x00U) /* Count at rising edge */
#define _MTU_CKEG_FALL                    (0x08U) /* Count at falling edge */
#define _MTU_CKEG_BOTH                    (0x10U) /* Count at both edge */
/* Counter Clear Select (CCLR[2:0]) */
#define _MTU_CKCL_DIS                     (0x00U) /* TCNT clearing disabled */
#define _MTU_CKCL_A                       (0x20U) /* TCNT cleared by TGRA compare match/input capture */
#define _MTU_CKCL_B                       (0x40U) /* TCNT cleared by TGRB compare match/input capture */
#define _MTU_CKCL_SYN                     (0x60U) /* TCNT cleared by counter clearing in another synchronous channel */
#define _MTU_CKCL_C                       (0xA0U) /* TCNT cleared by TGRC compare match/input capture */
#define _MTU_CKCL_D                       (0xC0U) /* TCNT cleared by TGRD compare match/input capture */
/* Phase Counting Mode Function Expansion Control (PCB[1:0]) */
#define _MTU_PCB_00                       (0x00U) /* Count condition 1 of phase counting mode 2,3,5 */
#define _MTU_PCB_01                       (0x08U) /* Count condition 2 of phase counting mode 2,3 */
#define _MTU_PCB_10                       (0x10U) /* Count condition 2 of phase counting mode 5 */
#define _MTU_PCB_11                       (0x18U) /* Count condition 3 of phase counting mode 2,3 */

/*
    Timer Mode Register 1 (TMDR1)
*/
/* Mode Select (MD[3:0]) */
#define _MTU_NORMAL                       (0x00U) /* Normal mode */
#define _MTU_PWM1                         (0x02U) /* PWM mode 1 */
#define _MTU_PWM2                         (0x03U) /* PWM mode 2 */
#define _MTU_COT1                         (0x04U) /* Phase counting mode 1 */
#define _MTU_COT2                         (0x05U) /* Phase counting mode 2 */
#define _MTU_COT3                         (0x06U) /* Phase counting mode 3 */
#define _MTU_COT4                         (0x07U) /* Phase counting mode 4 */
#define _MTU_REST                         (0x08U) /* Reset-synchronized PWM mode */
#define _MTU_COT5                         (0x09U) /* Phase counting mode 5 */
#define _MTU_CMT1                         (0x0DU) /* Complementary PWM mode 1 (transfer at crest) */
#define _MTU_CMT2                         (0x0EU) /* Complementary PWM mode 2 (transfer at trough)) */
#define _MTU_CMT3                         (0x0FU) /* Complementary PWM mode 3 (transfer at crest and trough)) */
/* Buffer Operation A (BFA) */
#define _MTU_BFA_NORMAL                   (0x00U) /* TGRA and TGRC operate normally */
#define _MTU_BFA_BUFFER                   (0x10U) /* TGRA and TGRC used together for buffer operation */
/* Buffer Operation B (BFB) */
#define _MTU_BFB_NORMAL                   (0x00U) /* TGRB and TGRD operate normally */
#define _MTU_BFB_BUFFER                   (0x20U) /* TGRB and TGRD used together for buffer operation */
/* Buffer Operation E (BFE) */
#define _MTU_BFE_NORMAL                   (0x00U) /* MTU0.TGRE and MTU0.TGRF operate normally */
#define _MTU_BFE_BUFFER                   (0x40U) /* MTU0.TGRE and MTU0.TGRF used together for buffer operation */

/*
    Timer I/O Control Register (TIOR)
*/
/* I/O Control A (IOA[3:0]) */
#define _MTU_IOA_DISABLE                  (0x00U) /* Output prohibited */
#define _MTU_IOA_LL                       (0x01U) /* Initial output is low. Low output at compare match */
#define _MTU_IOA_LH                       (0x02U) /* Initial output is low. High output at compare match */
#define _MTU_IOA_LT                       (0x03U) /* Initial output is low. Toggle output at compare match */
#define _MTU_IOA_HL                       (0x05U) /* Initial output is high. Low output at compare match */
#define _MTU_IOA_HH                       (0x06U) /* Initial output is high. High output at compare match */
#define _MTU_IOA_HT                       (0x07U) /* Initial output is high. Toggle output at compare match */
#define _MTU_IOA_IR                       (0x08U) /* Input capture at rising edge. */
#define _MTU_IOA_IF                       (0x09U) /* Input capture at falling edge */
#define _MTU_IOA_IB                       (0x0AU) /* Input capture at both edges */
#define _MTU_IOA_EX                       (0x0CU) /* Input capture at MTU1.TCNT up-count/down-count */
#define _MTU_IOA_TGRA                     (0x0DU) /* Input capture at MTU0.TGRA compare match/input capture */
#define _MTU_IOA_TGRC                     (0x0EU) /* Input capture at MTU8.TGRC compare match */
/* I/O Control B (IOB[3:0]) */
#define _MTU_IOB_DISABLE                  (0x00U) /* Output prohibited */
#define _MTU_IOB_LL                       (0x10U) /* Initial output is low. Low output at compare match */
#define _MTU_IOB_LH                       (0x20U) /* Initial output is low. High output at compare match */
#define _MTU_IOB_LT                       (0x30U) /* Initial output is low. Toggle output at compare match */
#define _MTU_IOB_HL                       (0x50U) /* Initial output is high. Low output at compare match */
#define _MTU_IOB_HH                       (0x60U) /* Initial output is high. High output at compare match */
#define _MTU_IOB_HT                       (0x70U) /* Initial output is high. Toggle output at compare match */
#define _MTU_IOB_IR                       (0x80U) /* Input capture at rising edge */
#define _MTU_IOB_IF                       (0x90U) /* Input capture at falling edge */
#define _MTU_IOB_IB                       (0xA0U) /* Input capture at both edges. */
#define _MTU_IOB_EX                       (0xC0U) /* Input capture at MTU1.TCNT up-count/down-count */
#define _MTU_IOB_TGRC0                    (0xC0U) /* Input capture at MTU0.TGRC compare match/input capture */
#define _MTU_IOB_TGRC8                    (0xE0U) /* Input capture at MTU8.TGRC compare match */
/* I/O Control C (IOC[3:0]) for MTU0.TIORL, MTU3.TIORL, MTU4.TIORL, MTU6.TIORL, MTU7.TIORL, MTU8.TIORL */
#define _MTU_IOC_DISABLE                  (0x00U) /* Output prohibited */
#define _MTU_IOC_LL                       (0x01U) /* Initial output is low. Low output at compare match */
#define _MTU_IOC_LH                       (0x02U) /* Initial output is low. High output at compare match */
#define _MTU_IOC_LT                       (0x03U) /* Initial output is low. Toggle output at compare match */
#define _MTU_IOC_HL                       (0x05U) /* Initial output is high. Low output at compare match. */
#define _MTU_IOC_HH                       (0x06U) /* Initial output is high. High output at compare match. */
#define _MTU_IOC_HT                       (0x07U) /* Initial output is high. Toggle output at compare match. */
#define _MTU_IOC_IR                       (0x08U) /* Input capture at rising edge. */
#define _MTU_IOC_IF                       (0x09U) /* Input capture at falling edge. */
#define _MTU_IOC_IB                       (0x0AU) /* Input capture at both edges. */
#define _MTU_IOC_EX                       (0x0CU) /* Input capture at MTU1.TCNT up-count/down-count. */
/* I/O Control C (IOC[4:0]) for MTU5.TIORU, MTU5.TIORV, MTU5.TIORW */
#define _MTU5_IOC_CP                      (0x00U) /* No function */
#define _MTU5_IOC_R                       (0x11U) /* Input capture at rising edge */
#define _MTU5_IOC_F                       (0x12U) /* Input capture at falling edge */
#define _MTU5_IOC_B                       (0x13U) /* Input capture at both edges */
#define _MTU5_IOC_TGRC                    (0x14U) /* Input capture at MTU8.TGRC compare match */
#define _MTU5_IOC_T                       (0x19U) /* Capture at trough in complementary PWM mode */
#define _MTU5_IOC_C                       (0x1AU) /* Capture at crest of complementary PWM mode */
#define _MTU5_IOC_CT                      (0x1BU) /* Capture at crest and trough of complementary PWM mode */
/* I/O Control D (IOD[3:0]) for MTU0.TIORL, MTU3.TIORL, MTU4.TIORL, MTU6.TIORL, MTU7.TIORL, MTU8.TIORL */
#define _MTU_IOD_DISABLE                  (0x00U) /* Output prohibited */
#define _MTU_IOD_LL                       (0x10U) /* Initial output is low. Low output at compare match */
#define _MTU_IOD_LH                       (0x20U) /* Initial output is low. High output at compare match */
#define _MTU_IOD_LT                       (0x30U) /* Initial output is low. Toggle output at compare match */
#define _MTU_IOD_HL                       (0x50U) /* Initial output is high. Low output at compare match. */
#define _MTU_IOD_HH                       (0x60U) /* Initial output is high. High output at compare match. */
#define _MTU_IOD_HT                       (0x70U) /* Initial output is high. Toggle output at compare match. */
#define _MTU_IOD_IR                       (0x80U) /* Input capture at rising edge. */
#define _MTU_IOD_IF                       (0x90U) /* Input capture at falling edge. */
#define _MTU_IOD_IB                       (0xA0U) /* Input capture at both edges. */
#define _MTU_IOD_EX                       (0xC0U) /* Input capture at MTU1.TCNT up-count/down-count. */

/*
    Timer Buffer Operation Transfer Mode Register (TBTM)
*/
/* Timing Select A (TTSA) */
#define _MTU_TTSA_CMMA                    (0x00U) /* When compare match A occurs in each channel, data is transferred */
#define _MTU_TTSA_TCNT                    (0x01U) /* When TCNT is cleared in each channel, data is transferred */
/* Timing Select B (TTSB) */
#define _MTU_TTSB_CMMB                    (0x00U) /* When compare match B occurs in each channel, data is transferred */
#define _MTU_TTSB_TCNT                    (0x02U) /* When TCNT is cleared in each channel, data is transferred */
/* Timing Select E (TTSE) */
#define _MTU_TTSE_CMME                    (0x00U) /* When compare match E occurs in MTU0, data is transferred */
#define _MTU_TTSE_TCNT                    (0x04U) /* When MTU0.TCNT is cleared in MTU0, data is transferred */

/*
    Timer Input Capture Control Register (TICCR)
*/
/* Input Capture Enable (I1AE) */
#define _MTU_I1AE_DISABLE                 (0x00U) /* Does not include MTIOC1A pin in MTU3.TGRA input capture condition */
#define _MTU_I1AE_ENABLE                  (0x01U) /* Includes MTIOC1A pin in MTU3.TGRA input capture condition */
/* Input Capture Enable (I1BE) */
#define _MTU_I1BE_DISABLE                 (0x00U) /* Does not include TMTIOC1B pin in MTU3.TGRB input capture condition */
#define _MTU_I1BE_ENABLE                  (0x02U) /* Includes MTIOC1B pin in MTU3.TGRB input capture condition */
/* Input Capture Enable (I2AE) */
#define _MTU_I2AE_DISABLE                 (0x00U) /* Does not include MTIOC2A pin in MTU1.TGRA input capture condition */
#define _MTU_I2AE_ENABLE                  (0x04U) /* Includes MTIOC2A pin in MTU1.TGRA input capture condition */
/* Input Capture Enable (I2BE) */
#define _MTU_I2BE_DISABLE                 (0x00U) /* Does not include MTIOC2B pin in MTU1.TGRB input capture condition */
#define _MTU_I2BE_ENABLE                  (0x08U) /* Includes MTIOC2B pin in MTU1.TGRB input capture condition */

/*
    Timer A/D Converter Start Request Control Register (TADCR)
*/
/* TCIV4 Interrupt Skipping Link Enable (ITB4VE) */
#define _MTU_ITB4VE_DISABLE               (0x0000U) /* TCI4V interrupt skipping is not linked */
#define _MTU_ITB4VE_ENABLE                (0x0001U) /* TCI4V interrupt skipping is linked */
/* TGIA3 Interrupt Skipping Link Enable (ITB3AE) */
#define _MTU_ITB3AE_DISABLE               (0x0000U) /* TGI3A interrupt skipping is not linked */
#define _MTU_ITB3AE_ENABLE                (0x0002U) /* TGI3A interrupt skipping is linked */
/* TCIV4 Interrupt Skipping Link Enable (ITA4VE) */
#define _MTU_ITA4VE_DISABLE               (0x0000U) /* TCI4V interrupt skipping is not linked */
#define _MTU_ITA4VE_ENABLE                (0x0004U) /* TCI4V interrupt skipping is linked */
/* TGIA3 Interrupt Skipping Link Enable (ITA3AE) */
#define _MTU_ITA3AE_DISABLE               (0x0000U) /* TGI3A interrupt skipping is not linked */
#define _MTU_ITA3AE_ENABLE                (0x0008U) /* TGI3A interrupt skipping is linked */
/* Down-Count TRG4BN Enable (DT4BE) */
#define _MTU_DT4BE_DISABLE                (0x0000U) /* A/D converter start request disabled during MTU4.TCNT down-count */
#define _MTU_DT4BE_ENABLE                 (0x0010U) /* A/D converter start request enabled during MTU4.TCNT down-count */
/* Up-Count TRG4BN Enable (UT4BE) */
#define _MTU_UT4BE_DISABLE                (0x0000U) /* A/D converter start requests disabled during MTU4.TCNT up-count */
#define _MTU_UT4BE_ENABLE                 (0x0020U) /* A/D converter start requests enabled during MTU4.TCNT up-count */
/* Down-Count TRG4AN Enable (DT4AE) */
#define _MTU_DT4AE_DISABLE                (0x0000U) /* A/D converter start request disabled during MTU4.TCNT down-count */
#define _MTU_DT4AE_ENABLE                 (0x0040U) /* A/D converter start request enabled during MTU4.TCNT down-count */
/* Up-Count TRG4AN Enable (UT4AE) */
#define _MTU_UT4AE_DISABLE                (0x0000U) /* A/D converter start requests disabled during MTU4.TCNT up-count */
#define _MTU_UT4AE_ENABLE                 (0x0080U) /* A/D converter start requests enabled during MTU4.TCNT up-count */
/* MTU4.TADCOBRA/B Transfer Timing Select (BF[1:0]) */
#define _MTU_BF_DISABLE                   (0x0000U) /* Transfers data from buffer register is disabled */
#define _MTU_BF_TOP                       (0x4000U) /* Transfers data at the crest of the MTU4.TCNT count */
#define _MTU_BF_LOW                       (0x8000U) /* Transfers data at the trough of the MTU4.TCNT count */
#define _MTU_BF_BOTH                      (0xC000U) /* Transfers data at the crest and trough of the MTU4.TCNT count */

/*
    Timer Start Registers (TSTR)
*/
/* Counter Start 0 (CST0) */
#define _MTU_CST0_OFF                     (0x00U) /* MTU0.TCNT performs count stop */
#define _MTU_CST0_ON                      (0x01U) /* MTU0.TCNT performs count operation */
/* Counter Start 1 (CST1) */            
#define _MTU_CST1_OFF                     (0x00U) /* MTU1.TCNT performs count stop */
#define _MTU_CST1_ON                      (0x02U) /* MTU1.TCNT performs count operation */
/* Counter Start 2 (CST2) */            
#define _MTU_CST2_OFF                     (0x00U) /* MTU2.TCNT performs count stop */
#define _MTU_CST2_ON                      (0x04U) /* MTU2.TCNT performs count operation */
/* Counter Start 3 (CST3) */            
#define _MTU_CST3_OFF                     (0x00U) /* MTU3.TCNT performs count stop */
#define _MTU_CST3_ON                      (0x40U) /* MTU3.TCNT performs count operation */
/* Counter Start 4 (CST4) */            
#define _MTU_CST4_OFF                     (0x00U) /* MTU4.TCNT performs count stop */
#define _MTU_CST4_ON                      (0x80U) /* MTU4.TCNT performs count operation */
/* Counter Start W5 (CSTW5) */          
#define _MTU_CSTW5_OFF                    (0x00U) /* MTU5.TCNTW count operation is stopped */
#define _MTU_CSTW5_ON                     (0x01U) /* MTU5.TCNTW performs count operation */
/* Counter Start V5 (CSTV5) */          
#define _MTU_CSTV5_OFF                    (0x00U) /* MTU5.TCNTV count operation is stopped */
#define _MTU_CSTV5_ON                     (0x02U) /* MTU5.TCNTV performs count operation */
/* Counter Start U5 (CSTU5) */         
#define _MTU_CSTU5_OFF                    (0x00U) /* MTU5.TCNTU count operation is stopped */
#define _MTU_CSTU5_ON                     (0x04U) /* MTU5.TCNTU performs count operation */
/* Counter Start 6 (CST6) */            
#define _MTU_CST6_OFF                     (0x00U) /* MTU6.TCNT performs count stop */
#define _MTU_CST6_ON                      (0x40U) /* MTU6.TCNT performs count operation */
/* Counter Start 7 (CST7) */            
#define _MTU_CST7_OFF                     (0x00U) /* MTU7.TCNT performs count stop */
#define _MTU_CST7_ON                      (0x80U) /* MTU7.TCNT performs count operation */
/* Counter Start 8 (CST8) */            
#define _MTU_CST8_OFF                     (0x00U) /* MTU8.TCNT performs count stop */
#define _MTU_CST8_ON                      (0x08U) /* MTU8.TCNT performs count operation */

/*
    Timer Synchronous Clear Register (TSYCR)
*/
#define _MTU6_SYNC_OFF                    (0x00U) /* Disables counter synchronous clearing */
#define _MTU6_CL2B_ON                     (0x01U) /* Enables counter clearing by the TGFB flag setting in MTU2.TSR */
#define _MTU6_CL2A_ON                     (0x02U) /* Enables counter clearing by the TGFA flag setting in MTU2.TSR */
#define _MTU6_CL1B_ON                     (0x04U) /* Enables counter clearing by the TGFB flag setting in MTU1.TSR */
#define _MTU6_CL1A_ON                     (0x08U) /* Enables counter clearing by the TGFA flag setting in MTU1.TSR */
#define _MTU6_CL0D_ON                     (0x10U) /* Enables counter clearing by the TGFD flag setting in MTU0.TSR */
#define _MTU6_CL0C_ON                     (0x20U) /* Enables counter clearing by the TGFC flag setting in MTU0.TSR */
#define _MTU6_CL0B_ON                     (0x40U) /* Enables counter clearing by the TGFB flag setting in MTU0.TSR */
#define _MTU6_CL0A_ON                     (0x80U) /* Enables counter clearing by the TGFA flag setting in MTU0.TSR */

/*
    Timer Synchronous Registers (TSYRA, TSYRB)
*/
/* Timer Synchronous Operation 0 (SYNC0) */
#define _MTU_SYNC0_OFF                    (0x00U) /* MTU0.TCNT operates independently */
#define _MTU_SYNC0_ON                     (0x01U) /* MTU0.TCNT performs synchronous operation */
/* Timer Synchronous Operation 1 (SYNC1) */
#define _MTU_SYNC1_OFF                    (0x00U) /* MTU1.TCNT operates independently */
#define _MTU_SYNC1_ON                     (0x02U) /* MTU1.TCNT performs synchronous operation */
/* Timer Synchronous Operation 2 (SYNC2) */
#define _MTU_SYNC2_OFF                    (0x00U) /* MTU3.TCNT operates independently */
#define _MTU_SYNC2_ON                     (0x04U) /* MTU3.TCNT performs synchronous operation */
/* Timer Synchronous Operation 3 (SYNC3) */
#define _MTU_SYNC3_OFF                    (0x00U) /* MTU3.TCNT operates independently */
#define _MTU_SYNC3_ON                     (0x40U) /* MTU3.TCNT performs synchronous operation */
/* Timer Synchronous Operation 4 (SYNC4) */
#define _MTU_SYNC4_OFF                    (0x00U) /* MTU4.TCNT operates independently */
#define _MTU_SYNC4_ON                     (0x80U) /* MTU4.TCNT performs synchronous operation */
/* Timer Synchronous Operation 6 (SYNC6) */
#define _MTU_SYNC6_OFF                    (0x00U) /* MTU6.TCNT operates independently */
#define _MTU_SYNC6_ON                     (0x40U) /* MTU6.TCNT performs synchronous operation */
/* Timer Synchronous Operation 7 (SYNC7) */
#define _MTU_SYNC7_OFF                    (0x00U) /* MTU7.TCNT operates independently */
#define _MTU_SYNC7_ON                     (0x80U) /* MTU7.TCNT performs synchronous operation */

/*
    Timer Read/Write Enable Registers (TRWERA and TRWERB)
*/
/* Read/Write Enable (RWE) */
#define _MTU_RWE_DISABLE                  (0x00U) /* Read/write access to the registers is disabled */
#define _MTU_RWE_ENABLE                   (0x01U) /* Read/write access to the registers is enabled */

/*
    Timer Output Master Enable Registers (TOERA)
*/
/* Master Enable MTIOC3B (OE3B) */
#define _MTU_OE3B_DISABLE                 (0xC0U) /* MTU output is disabled (inactive level) */
#define _MTU_OE3B_ENABLE                  (0xC1U) /* MTU output is enabled */
/* Master Enable MTIOC4A (OE4A) */
#define _MTU_OE4A_DISABLE                 (0xC0U) /* MTU output is disabled (inactive level) */
#define _MTU_OE4A_ENABLE                  (0xC2U) /* MTU output is enabled */
/* Master Enable MTIOC4B (OE4B) */
#define _MTU_OE4B_DISABLE                 (0xC0U) /* MTU output is disabled (inactive level) */
#define _MTU_OE4B_ENABLE                  (0xC4U) /* MTU output is enabled */
/* Master Enable MTIOC3D (OE3D) */
#define _MTU_OE3D_DISABLE                 (0xC0U) /* MTU output is disabled (inactive level) */
#define _MTU_OE3D_ENABLE                  (0xC8U) /* MTU output is enabled */
/* Master Enable MTIOC4C (OE4C) */
#define _MTU_OE4C_DISABLE                 (0xC0U) /* MTU output is disabled (inactive level) */
#define _MTU_OE4C_ENABLE                  (0xD0U) /* MTU output is enabled */
/* Master Enable MTIOC4D (OE4D) */
#define _MTU_OE4D_DISABLE                 (0xC0U) /* MTU output is disabled (inactive level) */
#define _MTU_OE4D_ENABLE                  (0xE0U) /* MTU output is enabled */

/*
    Timer Output Master Enable Registers (TOERB)
*/
/* Master Enable MTIOC6B (OE6B) */
#define _MTU_OE6B_DISABLE                 (0xC0U) /* MTU output is disabled (inactive level) */
#define _MTU_OE6B_ENABLE                  (0xC1U) /* MTU output is enabled */
/* Master Enable MTIOC7A (OE7A) */
#define _MTU_OE7A_DISABLE                 (0xC0U) /* MTU output is disabled (inactive level) */
#define _MTU_OE7A_ENABLE                  (0xC2U) /* MTU output is enabled */
/* Master Enable MTIOC7B (OE7B) */
#define _MTU_OE7B_DISABLE                 (0xC0U) /* MTU output is disabled (inactive level) */
#define _MTU_OE7B_ENABLE                  (0xC4U) /* MTU output is enabled */
/* Master Enable MTIOC6D (OE6D) */
#define _MTU_OE6D_DISABLE                 (0xC0U) /* MTU output is disabled (inactive level) */
#define _MTU_OE6D_ENABLE                  (0xC8U) /* MTU output is enabled */
/* Master Enable MTIOC7C (OE7C) */
#define _MTU_OE7C_DISABLE                 (0xC0U) /* MTU output is disabled (inactive level) */
#define _MTU_OE7C_ENABLE                  (0xD0U) /* MTU output is enabled */
/* Master Enable MTIOC7D (OE7D) */
#define _MTU_OE7D_DISABLE                 (0xC0U) /* MTU output is disabled (inactive level) */
#define _MTU_OE7D_ENABLE                  (0xE0U) /* MTU output is enabled */

/*
    Timer Gate Control Registers (TGCRA)
*/
/* External Feedback Signal Enable (FB) */
#define _MTU_FB_EXIN                      (0x00U) /* Output is switched by external input */
#define _MTU_FB_SW                        (0x08U) /* Output is switched by software */
/* Positive-Phase Output Control (P) */
#define _MTU_P_LEVEL                      (0x00U) /* Level output */
#define _MTU_P_PWM                        (0x10U) /* Reset-synchronized PWM or complementary PWM output */
/* Negative-Phase Output Control (N) */
#define _MTU_N_LEVEL                      (0x00U) /* Level output */
#define _MTU_N_PWM                        (0x20U) /* Reset-synchronized PWM or complementary PWM output */
/* Brushless DC Motor (BDC) */
#define _MTU_BDC_OUT                      (0x00U) /* Ordinary output */
#define _MTU_BDC_FUN                      (0x40U) /* Functions of this register are made effective */

/*
    Timer Interrupt Skipping Set Registers (TITCR1A, TITCR1B)
*/
/* TCIV4 or TCIV7 Interrupt Skipping Count Setting (T4VCOR[2:0], T7VCOR[2:0]) */
#define _MTU_TVCOR_4_7_SKIP_COUNT_0       (0x00U) /* Does not skip TCIV4 or TCIV7 interrupts */
#define _MTU_TVCOR_4_7_SKIP_COUNT_1       (0x01U) /* Sets the TCIV4 or TCIV7 interrupt skipping count to 1 */
#define _MTU_TVCOR_4_7_SKIP_COUNT_2       (0x02U) /* Sets the TCIV4 or TCIV7 interrupt skipping count to 2 */
#define _MTU_TVCOR_4_7_SKIP_COUNT_3       (0x03U) /* Sets the TCIV4 or TCIV7 interrupt skipping count to 3 */
#define _MTU_TVCOR_4_7_SKIP_COUNT_4       (0x04U) /* Sets the TCIV4 or TCIV7 interrupt skipping count to 4 */
#define _MTU_TVCOR_4_7_SKIP_COUNT_5       (0x05U) /* Sets the TCIV4 or TCIV7 interrupt skipping count to 5 */
#define _MTU_TVCOR_4_7_SKIP_COUNT_6       (0x06U) /* Sets the TCIV4 or TCIV7 interrupt skipping count to 6 */
#define _MTU_TVCOR_4_7_SKIP_COUNT_7       (0x07U) /* Sets the TCIV4 or TCIV7 interrupt skipping count to 7 */
/* TGIA3 or TGIA6 Interrupt Skipping Count Setting (T3ACOR[2:0], T6ACOR[2:0]) */
#define _MTU_TACOR_3_6_SKIP_COUNT_0       (0x00U) /* Does not skip TGIA3 or TGIA6 interrupts */
#define _MTU_TACOR_3_6_SKIP_COUNT_1       (0x10U) /* Sets the TGIA3 or TGIA6 interrupt skipping count to 1 */
#define _MTU_TACOR_3_6_SKIP_COUNT_2       (0x20U) /* Sets the TGIA3 or TGIA6 interrupt skipping count to 2 */
#define _MTU_TACOR_3_6_SKIP_COUNT_3       (0x30U) /* Sets the TGIA3 or TGIA6 interrupt skipping count to 3 */
#define _MTU_TACOR_3_6_SKIP_COUNT_4       (0x40U) /* Sets the TGIA3 or TGIA6 interrupt skipping count to 4 */
#define _MTU_TACOR_3_6_SKIP_COUNT_5       (0x50U) /* Sets the TGIA3 or TGIA6 interrupt skipping count to 5 */
#define _MTU_TACOR_3_6_SKIP_COUNT_6       (0x60U) /* Sets the TGIA3 or TGIA6 interrupt skipping count to 6 */
#define _MTU_TACOR_3_6_SKIP_COUNT_7       (0x70U) /* Sets the TGIA3 or TGIA6 interrupt skipping count to 7 */
/* T4VEN or T7VEN */                   
#define _MTU_T4_7VEN_DISABLE              (0x00U) /* TCIV4 or TCIV7 interrupt skipping disabled */
#define _MTU_T4_7VEN_ENABLE               (0x08U) /* TCIV4 or TCIV7 interrupt skipping enabled */
/* T3AEN or T6AEN */                   
#define _MTU_T3_6AEN_DISABLE              (0x00U) /* TGIA3 or TGIA6 interrupt skipping disabled */
#define _MTU_T3_6AEN_ENABLE               (0x80U) /* TGIA3 or TGIA6 interrupt skipping enabled */

/*
    Timer Interrupt Skipping Set Registers 2 (TITCR2A, TITCR2B)
*/
/* Setting of Interrupt Skipping Count by TRG4COR[2:0], TRG7COR[2:0] (n= 4,7) */
#define _MTU_TRGCOR_4_7_SKIP_COUNT_0      (0x00U) /* Does not skip TRGnAN and TRGnBN interrupts */
#define _MTU_TRGCOR_4_7_SKIP_COUNT_1      (0x01U) /* Sets the TRGnAN and TRGnBN interrupt skipping count to 1 */
#define _MTU_TRGCOR_4_7_SKIP_COUNT_2      (0x02U) /* Sets the TRGnAN and TRGnBN interrupt skipping count to 2 */
#define _MTU_TRGCOR_4_7_SKIP_COUNT_3      (0x03U) /* Sets the TRGnAN and TRGnBN interrupt skipping count to 3 */
#define _MTU_TRGCOR_4_7_SKIP_COUNT_4      (0x04U) /* Sets the TRGnAN and TRGnBN interrupt skipping count to 4 */
#define _MTU_TRGCOR_4_7_SKIP_COUNT_5      (0x05U) /* Sets the TRGnAN and TRGnBN interrupt skipping count to 5 */
#define _MTU_TRGCOR_4_7_SKIP_COUNT_6      (0x06U) /* Sets the TRGnAN and TRGnBN interrupt skipping count to 6 */
#define _MTU_TRGCOR_4_7_SKIP_COUNT_7      (0x07U) /* Sets the TRGnAN and TRGnBN interrupt skipping count to 7 */

/*
    Timer Buffer Transfer Set Registers (TBTERA, TBTERB)
*/
/* Buffer Transfer Disable and Interrupt Skipping Link Setting (BTE[1:0]) */
#define _MTU_TF_NO_INT                    (0x00U) /* Enables transfer, does not link with interrupt skipping operation */
#define _MTU_TF_DISABLE                   (0x01U) /* Disables transfer from buffer registers to the temporary registers */
#define _MTU_TF_WITH_INT                  (0x02U) /* Links transfer with interrupt skipping operation */

/*
    Timer Dead Time Enable Registers (TDERA, TDERB)
*/
/* Dead Time Enable (TDER) */
#define _MTU_TDER_DISABLE                 (0x00U) /* No dead time is generated */
#define _MTU_TDER_ENABLE                  (0x01U) /* Dead time is generated */


/*
    Noise Filter Control Registers (NFCRn)
*/
/* Noise Filter U Enable Bit (NFUEN) */
#define _MTU_NFUEN_DISABLE                (0x00U) /* The noise filter for the MTIC5U pin is disabled */
#define _MTU_NFUEN_ENABLE                 (0x01U) /* The noise filter for the MTIC5U pin is enabled */
/* Noise Filter V Enable Bit (NFVEN) */
#define _MTU_NFVEN_DISABLE                (0x00U) /* The noise filter for the MTIC5V pin is disabled */
#define _MTU_NFVEN_ENABLE                 (0x02U) /* The noise filter for the MTIC5V pin is enabled */
/* Noise Filter W Enable Bit (NFWEN) */
#define _MTU_NFWEN_DISABLE                (0x00U) /* The noise filter for the MTIC5W pin is disabled */
#define _MTU_NFWEN_ENABLE                 (0x04U) /* The noise filter for the MTIC5W pin is enabled */
/* Noise Filter A Enable Bit (NFAEN) */
#define _MTU_NFAEN_DISABLE                (0x00U) /* The noise filter for the MTIOCnA pin is disabled */
#define _MTU_NFAEN_ENABLE                 (0x01U) /* The noise filter for the MTIOCnA pin is enabled */
/* Noise Filter B Enable Bit (NFBEN) */
#define _MTU_NFBEN_DISABLE                (0x00U) /* The noise filter for the MTIOCnB pin is disabled */
#define _MTU_NFBEN_ENABLE                 (0x02U) /* The noise filter for the MTIOCnB pin is enabled */
/* Noise Filter C Enable Bit (NFCEN) */
#define _MTU_NFCEN_DISABLE                (0x00U) /* The noise filter for the MTIOCnC pin is disabled */
#define _MTU_NFCEN_ENABLE                 (0x04U) /* The noise filter for the MTIOCnC pin is enabled */
/* Noise Filter D Enable Bit (NFDEN) */
#define _MTU_NFDEN_DISABLE                (0x00U) /* The noise filter for the MTIOCnD pin is disabled */
#define _MTU_NFDEN_ENABLE                 (0x08U) /* The noise filter for the MTIOCnD pin is enabled */
/* Noise Filter Clock Select (NFCS[1:0]) */
#define _MTU_NFCS_PCLK_1                  (0x00U) /* PCLK/1 */
#define _MTU_NFCS_PCLK_8                  (0x10U) /* PCLK/8 */
#define _MTU_NFCS_PCLK_32                 (0x20U) /* PCLK/32 */
#define _MTU_NFCS_EXCLK                   (0x30U) /* The clock source for counting is the external clock */

/*
    Noise Filter Control Register (NFCRC)
*/
#define _MTU_NFCRC_NFAEN_DISABLE          (0x00U) /* The noise filter for the MTCLKA pin is disabled */
#define _MTU_NFCRC_NFBEN_DISABLE          (0x00U) /* The noise filter for the MTCLKB pin is disabled */
#define _MTU_NFCRC_NFCEN_DISABLE          (0x00U) /* The noise filter for the MTCLKC pin is disabled */
#define _MTU_NFCRC_NFDEN_DISABLE          (0x00U) /* The noise filter for the MTCLKD pin is disabled */
#define _MTU_NFCRC_NFAEN_ENABLE           (0x01U) /* The noise filter for the MTCLKA pin is enabled */
#define _MTU_NFCRC_NFBEN_ENABLE           (0x02U) /* The noise filter for the MTCLKB pin is enabled */
#define _MTU_NFCRC_NFCEN_ENABLE           (0x04U) /* The noise filter for the MTCLKC pin is enabled */
#define _MTU_NFCRC_NFDEN_ENABLE           (0x08U) /* The noise filter for the MTCLKD pin is enabled */
/* Noise Filter Clock Select (NFCSC[1:0]) */
#define _MTU_NFCSC_PCLK_1                 (0x00U) /* PCLK/1 */
#define _MTU_NFCSC_PCLK_2                 (0x10U) /* PCLK/2 */
#define _MTU_NFCSC_PCLK_8                 (0x20U) /* PCLK/8 */
#define _MTU_NFCSC_PCLK_32                (0x30U) /* PCLK/32 */

/*
    Timer Compare Match Clear Register (TCNTCMPCLR)
*/
/* TCNT Compare Clear 5W (CMPCLR5W) */
#define _MTU_CMPCLR5W_DISABLE             (0x00U) /* Disables MTU5.TCNTW to be cleared */
#define _MTU_CMPCLR5W_ENABLE              (0x01U) /* Enables MTU5.TCNTW to be cleared */
/* TCNT Compare Clear 5V (CMPCLR5V) */
#define _MTU_CMPCLR5V_DISABLE             (0x00U) /* Disables MTU5.TCNTV to be cleared */
#define _MTU_CMPCLR5V_ENABLE              (0x02U) /* Enables MTU5.TCNTV to be cleared */
/* TCNT Compare Clear 5U (CMPCLR5U) */
#define _MTU_CMPCLR5U_DISABLE             (0x00U) /* Disables MTU5.TCNTU to be cleared */
#define _MTU_CMPCLR5U_ENABLE              (0x04U) /* Enables MTU5.TCNTU to be cleared */

/*
    Timer Output Control Registers 1 (TOCR1)
*/
/* Output Level Select P (OLSP) */
#define _MTU_OLSP_HL                      (0x00U) /* Initial output:H, Active level:L */
#define _MTU_OLSP_LH                      (0x01U) /* Initial output:L, Active level:H */
/* Output Level Select N (OLSN) */
#define _MTU_OLSN_HL                      (0x00U) /* Initial output:H, Active level:L */
#define _MTU_OLSN_LH                      (0x02U) /* Initial output:L, Active level:H */
/* TOC Select (TOCS) */                
#define _MTU_TOCS_TOCR1                   (0x00U) /* TOCR1 setting is selected */
#define _MTU_TOCS_TOCR2                   (0x04U) /* TOCR2 setting is selected */
/* TOC Register Write Protection (TOCL) */
#define _MTU_TOCL_ENABLE                  (0x00U) /* Write access to the TOCS, OLSN, and OLSP bits is enabled */
#define _MTU_TOCL_DISABLE                 (0x08U) /* Write access to the TOCS, OLSN, and OLSP bits is disabled */
/* PWM Synchronous Output Enable (PSYE) */
#define _MTU_PSYE_DISABLE                 (0x00U) /* Toggle output is disabled */
#define _MTU_PSYE_ENABLE                  (0x40U) /* Toggle output is enabled */

/*
    Timer Output Control Registers 2 (TOCR2)
*/
/* Output Level Select 1P (OLS1P) */
#define _MTU_OLS1P_HL                     (0x00U) /* Initial output:H, Active level:L */
#define _MTU_OLS1P_LH                     (0x01U) /* Initial output:L, Active level:H */
/* Output Level Select 1N (OLS1N) */   
#define _MTU_OLS1N_HL                     (0x00U) /* Initial output:H, Active level:L */
#define _MTU_OLS1N_LH                     (0x02U) /* Initial output:L, Active level:H */
/* Output Level Select 1N (OLS2P) */   
#define _MTU_OLS2P_HL                     (0x00U) /* Initial output:H, Active level:L */
#define _MTU_OLS2P_LH                     (0x04U) /* Initial output:L, Active level:H */
/* Output Level Select 1N (OLS2N) */   
#define _MTU_OLS2N_HL                     (0x00U) /* Initial output:H, Active level:L */
#define _MTU_OLS2N_LH                     (0x08U) /* Initial output:L, Active level:H */
/* Output Level Select 1N (OLS3P) */   
#define _MTU_OLS3P_HL                     (0x00U) /* Initial output:H, Active level:L */
#define _MTU_OLS3P_LH                     (0x10U) /* Initial output:L, Active level:H */
/* Output Level Select 1N (OLS3N) */   
#define _MTU_OLS3N_HL                     (0x00U) /* Initial output:H, Active level:L */
#define _MTU_OLS3N_LH                     (0x20U) /* Initial output:L, Active level:H */
/* TOLBR Buffer Transfer Timing Select (BF[1:0]) */
#define _MTU_TOLBR_DIS                    (0x00U) /* Does not transfer data from the buffer register (TOLBR)to TOCR2 */
#define _MTU_TOLBR_C                      (0x40U) /* Transfers at the crest of the MTU4.TCNT count */
#define _MTU_TOLBR_T                      (0x80U) /* Transfers at the trough of the MTU4.TCNT count */
#define _MTU_TOLBR_CT                     (0xC0U) /* Transfers at crest and trough of the MTU4.TCNT count */

/*
    Timer Interrupt Enable Register (TIER & TIER2)
*/
/* TGR Interrupt Enable A (TGIEA) */
#define _MTU_TGIEA_DISABLE                (0x00U) /* Interrupt requests TGIA disabled */
#define _MTU_TGIEA_ENABLE                 (0x01U) /* Interrupt requests TGIA enabled */
/* TGR Interrupt Enable B (TGIEB) */   
#define _MTU_TGIEB_DISABLE                (0x00U) /* Interrupt requests TGIB disabled */
#define _MTU_TGIEB_ENABLE                 (0x02U) /* Interrupt requests TGIB enabled */
/* TGR Interrupt Enable C (TGIEC) */   
#define _MTU_TGIEC_DISABLE                (0x00U) /* Interrupt requests TGIC disabled */
#define _MTU_TGIEC_ENABLE                 (0x04U) /* Interrupt requests TGIC enabled */
/* TGR Interrupt Enable D (TGIED) */   
#define _MTU_TGIED_DISABLE                (0x00U) /* Interrupt requests TGID disabled */
#define _MTU_TGIED_ENABLE                 (0x08U) /* Interrupt requests TGID enabled */
/* Overflow Interrupt Enable (TCIEV) */
#define _MTU_TCIEV_DISABLE                (0x00U) /* Interrupt requests TCIV disabled */
#define _MTU_TCIEV_ENABLE                 (0x10U) /* Interrupt requests TCIV enabled */
/* Underflow Interrupt Enable (TCIEU) */
#define _MTU_TCIEU_DISABLE                (0x00U) /* Interrupt requests TCIU disabled */
#define _MTU_TCIEU_ENABLE                 (0x20U) /* Interrupt requests TCIU enabled */
/* A/D Converter Start Request Enable 2 (TTGE2) */
#define _MTU_TIER_TTGE2_DISABLE           (0x00U) /* A/D converter start request by MTU4.TCNT(MTU7.TCNT) disabled */
#define _MTU_TIER_TTGE2_ENABLE            (0x40U) /* A/D converter start request by MTU4.TCNT(MTU7.TCNT) enabled */
/* A/D Converter Start Request Enable 2 (TTGE2) */
#define _MTU_TIER2_TTGE2_DISABLE          (0x00U) /* A/D converter start request by MTU0.TCNT disabled */
#define _MTU_TIER2_TTGE2_ENABLE           (0x80U) /* A/D converter start request by MTU0.TCNT enabled */
/* A/D Converter Start Request Enable (TTGE) */
#define _MTU_TTGE_DISABLE                 (0x00U) /* A/D converter start request generation disabled */
#define _MTU_TTGE_ENABLE                  (0x80U) /* A/D converter start request generation enabled */
/* TGR Interrupt Enable E (TGIEE) */
#define _MTU_TGIEE_DISABLE                (0x00U) /* Interrupt requests TGIE disabled */
#define _MTU_TGIEE_ENABLE                 (0x01U) /* Interrupt requests TGIE enabled */
/* TGR Interrupt Enable F (TGIEF) */
#define _MTU_TGIEF_DISABLE                (0x00U) /* Interrupt requests TGIF disabled */
#define _MTU_TGIEF_ENABLE                 (0x02U) /* Interrupt requests TGIF enabled */
/* TGR Interrupt Enable 5W (TGIE5W) */
#define _MTU_TGIE5W_DISABLE               (0x00U) /* Interrupt requests TGI5W disabled */
#define _MTU_TGIE5W_ENABLE                (0x01U) /* Interrupt requests TGI5W enabled */
/* TGR Interrupt Enable 5V (TGIE5V) */
#define _MTU_TGIE5V_DISABLE               (0x00U) /* Interrupt requests TCI5V disabled */
#define _MTU_TGIE5V_ENABLE                (0x02U) /* Interrupt requests TCI5V enabled */
/* TGR Interrupt Enable 5U (TGIE5U) */
#define _MTU_TGIE5U_DISABLE               (0x00U) /* Interrupt requests TCI5U disabled */
#define _MTU_TGIE5U_ENABLE                (0x04U) /* Interrupt requests TCI5U enabled */

/*
    Interrupt Source Priority Register n (PRLn)
*/
/* Interrupt Priority Level Select (PRL[3:0]) */
#define _MTU_PRIORITY_LEVEL0              (0x00000000UL) /* Level 0 (highest) */
#define _MTU_PRIORITY_LEVEL1              (0x00000001UL) /* Level 1 */
#define _MTU_PRIORITY_LEVEL2              (0x00000002UL) /* Level 2 */
#define _MTU_PRIORITY_LEVEL3              (0x00000003UL) /* Level 3 */
#define _MTU_PRIORITY_LEVEL4              (0x00000004UL) /* Level 4 */
#define _MTU_PRIORITY_LEVEL5              (0x00000005UL) /* Level 5 */
#define _MTU_PRIORITY_LEVEL6              (0x00000006UL) /* Level 6 */
#define _MTU_PRIORITY_LEVEL7              (0x00000007UL) /* Level 7 */
#define _MTU_PRIORITY_LEVEL8              (0x00000008UL) /* Level 8 */
#define _MTU_PRIORITY_LEVEL9              (0x00000009UL) /* Level 9 */
#define _MTU_PRIORITY_LEVEL10             (0x0000000AUL) /* Level 10 */
#define _MTU_PRIORITY_LEVEL11             (0x0000000BUL) /* Level 11 */
#define _MTU_PRIORITY_LEVEL12             (0x0000000CUL) /* Level 12 */
#define _MTU_PRIORITY_LEVEL13             (0x0000000DUL) /* Level 13 */
#define _MTU_PRIORITY_LEVEL14             (0x0000000EUL) /* Level 14 */
#define _MTU_PRIORITY_LEVEL15             (0x0000000FUL) /* Level 15 */


/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Timer Clock is 200[MHz] */
//#define MTR_TC_CNT_NUM          (12500) /* isr_freq = 16k */
//#define MTR_TC_HALF_CNT_NUM     (6250)//
//#define MTR_TC_4_CNT_NUM        (3125)
//#define MTR_TDEAD_CNT_NUM       (300)   /* Dead Time 1[us] */

#define MTR_TC_CNT_NUM          (25000) /* isr_freq = 8k */
#define MTR_TC_HALF_CNT_NUM     (10000)//
#define MTR_TC_4_CNT_NUM        (5000)
#define MTR_TDEAD_CNT_NUM       (300)   /* Dead Time 1[us] */


#define MTU_TGIV3_PRIORITY_LEVEL    (1) /* The lower the value, the higher the priority of the corresponding interrupt(0-31) */



/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_MTU3_Create(void);

void R_MTU3_C3_4_Start(void);
void R_MTU3_C3_4_Stop(void);


//void R_MTU3_C1_Start(void);
//void R_MTU3_C1_Stop(void);
//void R_MTU3_C2_Start(void);
//void R_MTU3_C2_Stop(void);
//void R_MTU3_C3_4_Start(void);
//void R_MTU3_C3_4_6_7_Stop(void);
//void R_MTU3_C3_4_Enable_Output(void);
//void R_MTU3_C3_4_Disable_Output(void);
//void R_MTU3_C6_7_Enable_Output(void);
//void R_MTU3_C6_7_Disable_Output(void);
//void R_MTU3_IO_int(void);

////#pragma type_attribute=__irq __arm
//void r_mtu_tgiv3_interrupt(void);


/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
