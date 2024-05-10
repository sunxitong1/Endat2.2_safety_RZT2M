
/***********************************************************************************************************************
* System Name  : RZ/T2M Motor Solution Kit
* File Name    : R_ADC.h
* Version      : 1.10
* Device       : RZ/T2M
* Tool-Chain   : IAR Embedded Workbench for ARM
*                Renesas e2studio
* OS           : Not use
* Description  : Header file of ADC.  
***********************************************************************************************************************/
#ifndef R_ADC_H
#define R_ADC_H


#include "bsp_api.h"

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/

/*
    A/D control register (ADCSR)
*/
/* Group B scan end interrupt enable (GBADIE) */
#define _AD_GBADI_DISABLE                   (0x0000U) /* Disable S12GBADI interrupt generation upon group B scan
                                                         completion */
#define _AD_GBADI_ENABLE                    (0x0040U) /* Enable S12GBADI interrupt generation upon group B scan
                                                          completion */
/* Double trigger mode select (DBLE) */
#define _AD_DBLTRIGGER_DISABLE              (0x0000U) /* Disable double trigger mode */
#define _AD_DBLTRIGGER_ENABLE               (0x0080U) /* Enable double trigger mode */
/* Trigger select (EXTRG) */
#define _AD_SYNC_TRIGGER                    (0x0000U) /* A/D conversion started by snychronous trigger */
#define _AD_ASYNC_TRIGGER                   (0x0100U) /* A/D conversion started by asynchronous trigger */
/* Trigger start enable (TRGE) */
#define _AD_SYNCASYNCTRG_DISABLE            (0x0000U) /* A/D conversion synchronous or asynchronous trigger disable */
#define _AD_SYNCASYNCTRG_ENABLE             (0x0200U) /* A/D conversion synchronous or asynchronous trigger enable */
/* Scan end interrupt enable (ADIE) */
#define _AD_SCAN_END_INTERRUPT_DISABLE      (0x0000U) /* Disable S12ADI0 interrupt generation upon scan completion */
#define _AD_SCAN_END_INTERRUPT_ENABLE       (0x1000U) /* Enable S12ADI0 interrupt generation upon scan completion */
/* Scan mode select (ADCS) */
#define _AD_SINGLE_SCAN_MODE                (0x0000U) /* Single scan mode */
#define _AD_GROUP_SCAN_MODE                 (0x2000U) /* Group scan mode */
#define _AD_CONTINUOUS_SCAN_MODE            (0x4000U) /* Continuous scan mode */
/* A/D conversion start (ADST) */
#define _AD_CONVERSION_STOP                 (0x0000U) /* Stop A/D conversion */
#define _AD_CONVERSION_START                (0x8000U) /* Start A/D conversion */

/*
    A/D converted value addition count select register (ADADC)
*/
/* Addition Count Select (ADC[1:0]) */
#define _AD_1_TIME_CONVERSION               (0x00U) /* 1-time conversion */
#define _AD_2_TIME_CONVERSION               (0x01U) /* 2-time conversion */
#define _AD_3_TIME_CONVERSION               (0x02U) /* 3-time conversion */
#define _AD_4_TIME_CONVERSION               (0x03U) /* 4-time conversion */
/* Average Mode Enable bit (AVEE) */
#define _AD_ADDITION_MODE                   (0x00U) /* Addition mode */
#define _AD_AVERAGE_MODE                    (0x80U) /* Average mode */

/*
    A/D control extended register (ADCER)
*/
/* A/D Conversion Accuracy Specify (ADPRC) */
#define _AD_RESOLUTION_12BIT                (0x0000U) /* 12 bit resolution */
#define _AD_RESOLUTION_10BIT                (0x0002U) /* 10 bit resolution */
#define _AD_RESOLUTION_8BIT                 (0x0004U) /* 8 bit resolution */
/* Automatic clearing enable (ACE) */
#define _AD_AUTO_CLEARING_DISABLE           (0x0000U) /* Disable auto clearing */
#define _AD_AUTO_CLEARING_ENABLE            (0x0020U) /* Enable auto clearing */
/* A/D Self-diagnosis selection (DIAGVAL) */
#define _AD_SELFTDIAGST_DISABLE             (0x0000U) /* Disable self-diagnosis */
#define _AD_SELFTDIAGST_VREFH0_0            (0x0100U) /* Self-diagnosis using a voltage of 0V */
#define _AD_SELFTDIAGST_VREFH0_HALF         (0x0200U) /* Self-diagnosis using a voltage of VREFH0_1/2*/
#define _AD_SELFTDIAGST_VREFH0              (0x0300U) /* Self-diagnosis using a voltage of VREFH0_1*/
#define _AD_SELFTDIAGST_VREFH1_0            (0x0100U) /* Self-diagnosis using a voltage of 0V */
#define _AD_SELFTDIAGST_VREFH1_HALF         (0x0200U) /* Self-diagnosis using a voltage of VREFH1_1/2*/
#define _AD_SELFTDIAGST_VREFH1              (0x0300U) /* Self-diagnosis using a voltage of VREFH1_1*/
/* A/D Self-diagnostic mode selection (DIAGLD) */
#define _AD_SELFTDIAGST_ROTATION            (0x0000U) /* Rotation mode for self-diagnosis voltage */
#define _AD_SELFTDIAGST_FIX                 (0x0400U) /* Fixed mode for self-diagnosis voltage */
/* A/D Self-diagnostic enable (DIAGM) */
#define _AD_SELFTDIAGST_DISABLE             (0x0000U) /* 12bit self-diagnosis disable */
#define _AD_SELFTDIAGST_ENABLE              (0x0800U) /* 12bit self-diagnosis enable */
/* A/D data register format selection (ADRFMT) */
#define _AD_RIGHT_ALIGNMENT                 (0x0000U) /* Right-alignment for data register format */
#define _AD_LEFT_ALIGNMENT                  (0x8000U) /* Left-alignment for data register format */

/*
    A/D start trigger select register (ADSTRGR)
*/
/* A/D conversion start trigger select for group B (TRSB) */
#define _AD_TRSB_TRGA0N                     (0x0001U) /* Compare match with or input capture to MTU0.TGRA */
#define _AD_TRSB_TRGA1N                     (0x0002U) /* Compare match with or input capture to MTU1.TGRA */
#define _AD_TRSB_TRGA2N                     (0x0003U) /* Compare match with or input capture to MTU2.TGRA */
#define _AD_TRSB_TRGA3N                     (0x0004U) /* Compare match with or input capture to MTU3.TGRA */
#define _AD_TRSB_TRGA4N                     (0x0005U) /* Compare match with or input capture to MTU4.TGRA,or an
                                                            underflow of MTU4.TCNT (in the trough) in complementary
                                                            PWM mode */
#define _AD_TRSB_TRGA6N                     (0x0006U) /* Compare match with or input capture to MTU6.TGRA */
#define _AD_TRSB_TRGA7N                     (0x0007U) /* Compare match with or input capture to MTU7.TGRA,or an
                                                            underflow of MTU7.TCNT (in the trough) in complementary
                                                            PWM mode */
#define _AD_TRSB_TRG0N                      (0x0008U) /* Compare match with MTU0.TGRE */
#define _AD_TRSB_TRG4AN                     (0x0009U) /* Compare match between MTU4.TADCORA and MTU4.TCNT */
#define _AD_TRSB_TRG4BN                     (0x000AU) /* Compare match between MTU4.TADCORB and MTU4.TCNT */
#define _AD_TRSB_TRG4BN_TRG4AN              (0x000BU) /* Compare match between MTU4.TADCORA and MTU4.TCNT, or
                                                            between MTU4.TADCORB and MTU4.TCNT */
#define _AD_TRSB_TRG4ABN                    (0x000CU) /* Compare match between MTU4.TADCORA and MTU4.TCNT, and
                                                            between MTU4.TADCORB and MTU4.TCNT (when interrupt skipping
                                                            function 2 is in use) */
#define _AD_TRSB_TRG7AN                     (0x000DU) /* Compare match between MTU7.TADCORA and MTU7.TCNT */
#define _AD_TRSB_TRG7BN                     (0x000EU) /* Compare match between MTU7.TADCORB and MTU7.TCNT */
#define _AD_TRSB_TRG7AN_TRG7BN              (0x000FU) /* Compare match between MTU7.TADCORA and MTU7.TCNT, or between
                                                            MTU7.TADCORB and MTU7.TCNT */
#define _AD_TRSB_TRG7ABN                    (0x0010U) /* Compare match between MTU7.TADCORA and MTU7.TCNT, and between
                                                            MTU7.TADCORB and MTU7.TCNT (when interrupt skipping function
                                                            2 is in use) */
#define _AD_TRSB_ELCAD0                     (0x1100U) /* Input from ELC (ADCn A) */
#define _AD_TRSB_ELCAD1                     (0x1200U) /* Input from ELC (ADCn B) */

/* A/D conversion start trigger select for group A (TRSA) */
#define _AD_TRSA_ADTRG                      (0x0000U) /* Input pin for the trigger */
#define _AD_TRSA_TRGA0N                     (0x0100U) /* Compare match with or input capture to MTU0.TGRA */
#define _AD_TRSA_TRGA1N                     (0x0200U) /* Compare match with or input capture to MTU1.TGRA */
#define _AD_TRSA_TRGA2N                     (0x0300U) /* Compare match with or input capture to MTU2.TGRA */
#define _AD_TRSA_TRGA3N                     (0x0400U) /* Compare match with or input capture to MTU3.TGRA */
#define _AD_TRSA_TRGA4N                     (0x0500U) /* Compare match with or input capture to MTU4.TGRA or, in
                                                            complementary PWM mode,an underflow of MTU4.TCNT
                                                            (in the trough)*/
#define _AD_TRSA_TRGA6N                     (0x0600U) /* Compare match with or input capture to MTU6.TGRA */
#define _AD_TRSA_TRGA7N                     (0x0700U) /* Compare match with or input capture to MTU7.TGRA or, in
                                                            complementary PWM mode,an underflow of MTU7.TCNT
                                                            (in the trough)*/
#define _AD_TRSA_TRG0N                      (0x0800U) /* Compare match with MTU0.TGRE */
#define _AD_TRSA_TRG4AN                     (0x0900U) /* Compare match between MTU4.TADCORA and MTU4.TCNT */
#define _AD_TRSA_TRG4BN                     (0x0A00U) /* Compare match between MTU4.TADCORB and MTU4.TCNT */
#define _AD_TRSA_TRG4BN_TRG4AN              (0x0B00U) /* Compare match between MTU4.TADCORA and MTU4.TCNT, or between
                                                            MTU4.TADCORB and MTU4.TCNT */
#define _AD_TRSA_TRG4ABN                    (0x0C00U) /* Compare match between MTU4.TADCORA and MTU4.TCNT, and between
                                                            MTU4.TADCORB and MTU4.TCNT (when interrupt skipping function
                                                            2 is in use) */
#define _AD_TRSA_TRG7AN                     (0x0D00U) /* Compare match between MTU7.TADCORA and MTU7.TCNT */
#define _AD_TRSA_TRG7BN                     (0x0E00U) /* Compare match between MTU7.TADCORB and MTU7.TCNT */
#define _AD_TRSA_TRG7AN_TRG7BN              (0x0F00U) /* Compare match between MTU7.TADCORA and MTU7.TCNT, or between
                                                            MTU7.TADCORB and MTU7.TCNT */
#define _AD_TRSA_TRG7ABN                    (0x1000U) /* Compare match between MTU7.TADCORA and MTU7.TCNT, and between
                                                            MTU7.TADCORB and MTU7.TCNT (when interrupt skipping function
                                                            2 is in use) */
#define _AD_TRSA_ELCAD0                     (0x1100U) /* Input from ELC (ADCn A) */
#define _AD_TRSA_ELCAD1                     (0x1200U) /* Input from ELC (ADCn B) */

/*
    A/D converted extended input control register (ADEXICR)
*/
/* Temperature sensor output A/D conversion value addition mode selection (TSSAD) */
#define _AD_TEMP_ADDITION_DISABLE           (0x0000U) /* Temperature sensor output A/D converted value addition/average
                                                            mode disabled */
#define _AD_TEMP_ADDITION_ENABLE            (0x0001U) /* Temperature sensor output A/D converted value addition/average
                                                            mode enabled */
/* Temperature sensor output A/D conversion select (TSSA) */
#define _AD_TEMP_GROUPA_DISABLE             (0x0000U) /* A/D conversion of temperature sensor output is disabled in 
                                                            group A  */
#define _AD_TEMP_GROUPA_ENABLE              (0x0100U) /* A/D conversion of temperature sensor output is enabled in 
                                                            group A  */
/* Temperature sensor output A/D conversion select (TSSB) */
#define _AD_TEMP_GROUPB_DISABLE             (0x0000U) /* A/D conversion of temperature sensor output is disabled in 
                                                            group B  */
#define _AD_TEMP_GROUPB_ENABLE              (0x0400U) /* A/D conversion of temperature sensor output is enabled in 
                                                            group B  */
/* Extended analog input selection (EXSEL) */
#define _AD_EXTNANEX1_IN_DISABLE            (0x0000U) /* Extended analog input disable */
#define _AD_EXTNANEX1_IN_ENABLE             (0x2000U) /* Extended analog input enable */
/* Extended analog output control (EXOEN) */
#define _AD_EXTNANEX0_OUT_DISABLE           (0x0000U) /* Extended analog output disable */
#define _AD_EXTNANEX0_IN_ENABLE             (0x8000U) /* Extended analog output enable */

/*
    A/D Group Scan Priority Control Register (ADGSPCR)
*/
/* Group-A Priority Control Setting (PGS) */
#define _AD_GPAPRIORITY_DISABLE             (0x0000U) /* Operation is without group A priority control */
#define _AD_GPAPRIORITY_ENABLE              (0x0001U) /* Operation is with group A priority control */
/* Group B Restart Setting (GBRSCN) */
#define _AD_GPBRESTART_DISABLE              (0x0000U) /* Group B is not restarted after discontinued due to Group A
                                                     priority */
#define _AD_GPBRESTART_ENABLE               (0x0002U) /* Group B is restarted after discontinued due to Group A priority */
/* Group B Single Cycle Scan Continuous Start (GBRP) */
#define _AD_GPBSCSCS_DISABLE                (0x0000U) /* Single cycle scan for group B is not continuously activated */
#define _AD_GPBSCSCS_ENABLE                 (0x8000U) /* Single cycle scan for group B is continuously activated */

/* 
    A/D Compare Control Register (ADCMPCR)
*/
/* Window A/B Complex Conditions Setting (CMPAB) */
#define _AD_COMPLEX_CONDITION_OR            (0x0000U) /* Window A comparison condition matched OR window B
                                                          comparison condition matched */
#define _AD_COMPLEX_CONDITION_EXOR          (0x0001U) /* Window A comparison condition matched EXOR window B
                                                          comparison condition matched */
#define _AD_COMPLEX_CONDITION_AND           (0x0002U) /* Window A comparison condition matched AND window B
                                                          comparison condition matched */
/* Comparison Window B Enable (CMPBE) */
#define _AD_WINDOWB_DISABLE                 (0x0000U) /* Comparison window B disabled */
#define _AD_WINDOWB_ENABLE                  (0x0200U) /* Comparison window B enabled */
/* Comparison Window A Enable (CMPAE) */
#define _AD_WINDOWA_DISABLE                 (0x0000U) /* Comparison window A disabled */
#define _AD_WINDOWA_ENABLE                  (0x0800U) /* Comparison window A enabled */
/* Comparison B Interrupt Enable (CMPBIE) */
#define _AD_COMPAREB_INTERRUPT_DISABLE      (0x0000U) /* Comparison interrupt by a match with the comparison condition
                                                          (window B) is disabled */
#define _AD_COMPAREB_INTERRUPT_ENABLE       (0x2000U) /* Comparison interrupt by a match with the comparison condition
                                                          (window B) is enable */
/* Window Function Setting (WCMPE) */
#define _AD_WINDOWFUNCTION_DISABLE          (0x0000U) /* Window function disabled */
#define _AD_WINDOWFUNCTION_ENABLE           (0x4000U) /* Window function enabled */
/* Comparison A Interrupt Enable (CMPAIE) */
#define _AD_COMPAREA_INTERRUPT_DISABLE      (0x0000U) /* Comparison interrupt by a match with the comparison condition
                                                          (window A) is disabled */
#define _AD_COMPAREA_INTERRUPT_ENABLE       (0x8000U) /* Comparison interrupt by a match with the comparison condition
                                                          (window A) is enable */

/* 
    A/D Compare Channel Select Extended Register (ADCMPANSER)
*/
/* Temperature Sensor Output Compare Select(CMPSTS) */
#define _AD_TEMP_COMPARE_DISABLE            (0x00U) /* Temperature sensor output is not a target for comparison. */ 
#define _AD_TEMP_COMPARE_ENABLE             (0x01U) /* Temperature sensor output is a target for comparison. */

/* 
    A/D Compare Level Extended Register (ADCMPLER)
*/
/* Temperature Sensor Output Compare Level Select(CMPLTS) */
#define _AD_TEMP0_COMPARELEVEL              (0x00U) /* AD-converted value < ADCMPDR0 register value or A/D-converted
                                                            value > ADCMPDR1 register value */ 
#define _AD_TEMP1_COMPARELEVEL              (0x01U) /* ADCMPDR0 register value < A/D-converted value < ADCMPDR1
                                                            register value */

/* 
    A/D Pin-Level Self-Diagnosis Control Register (ADTDCR)
*/
/* Pin-level Self-diagnosis Level Select (TDLV[1:0]) */
#define _AD_EVEN_AVSS0                      (0x00U) /* Input channels with even numbers are discharged to AVSS, 
                                                            and input channels with odd numbers are charged to AVCC. */
#define _AD_EVEN_AVCC0                      (0x01U) /* Input channels with even numbers are charged to AVCC, 
                                                            and input channels with odd numbers are discharged to AVSS. */
#define _AD_ODD_AVCC0_HALF                  (0x02U) /* Input channels with even numbers are discharged to AVSS, 
                                                            and input channels with odd numbers are charged to AVCx1/2. */
#define _AD_EVEN_AVCC0_HALF                 (0x03U) /* Input channels with even numbers are charged to AVCCx1/2, 
                                                            and input channels with odd numbers are discharged to AVSS. */
#define _AD_EVEN_AVSS1                      (0x00U) /* Input channels with even numbers are discharged to AVSS, 
                                                            and input channels with odd numbers are charged to AVCC. */
#define _AD_EVEN_AVCC1                      (0x01U) /* Input channels with even numbers are charged to AVCC, 
                                                            and input channels with odd numbers are discharged to AVSS. */
#define _AD_ODD_AVCC1_HALF                  (0x02U) /* Input channels with even numbers are discharged to AVSS, 
                                                            and input channels with odd numbers are charged to AVCx1/2. */
#define _AD_EVEN_AVCC1_HALF                 (0x03U) /* Input channels with even numbers are charged to AVCCx1/2, 
                                                            and input channels with odd numbers are discharged to AVSS. */
/* Pin-level Self-diagnosis Enable (TDE) */
#define _AD_PINLVL_ENABLE                   (0x00U) /* Enable pin-level self-diagnosis. */
#define _AD_PINLVL_DISABLE                  (0x80U) /* Disable pin-level self-diagnosis. */


/* 
    A/D Error Control Register (ADERCR)
*/
/* Overwrite Error Interrupt Enable (OWEIE) */
#define _AD_ERROR_INT_REQUEST_DISABLE       (0x00U) /* Disable interrupt generation when an overwrite error is detected. */
#define _AD_ERROR_INT_REQUEST_ENABLE        (0x04U) /* Enable interrupt generation when an overwrite error is detected. */

/*
    Interrupt Source Priority Register n (PRLn)
*/
/* Interrupt Priority Level Select (PRL[3:0]) */
#define _AD_PRIORITY_LEVEL0                 (0x00000000UL) /* Level 0 (highest) */
#define _AD_PRIORITY_LEVEL1                 (0x00000001UL) /* Level 1 */
#define _AD_PRIORITY_LEVEL2                 (0x00000002UL) /* Level 2 */
#define _AD_PRIORITY_LEVEL3                 (0x00000003UL) /* Level 3 */
#define _AD_PRIORITY_LEVEL4                 (0x00000004UL) /* Level 4 */
#define _AD_PRIORITY_LEVEL5                 (0x00000005UL) /* Level 5 */
#define _AD_PRIORITY_LEVEL6                 (0x00000006UL) /* Level 6 */
#define _AD_PRIORITY_LEVEL7                 (0x00000007UL) /* Level 7 */
#define _AD_PRIORITY_LEVEL8                 (0x00000008UL) /* Level 8 */
#define _AD_PRIORITY_LEVEL9                 (0x00000009UL) /* Level 9 */
#define _AD_PRIORITY_LEVEL10                (0x0000000AUL) /* Level 10 */
#define _AD_PRIORITY_LEVEL11                (0x0000000BUL) /* Level 11 */
#define _AD_PRIORITY_LEVEL12                (0x0000000CUL) /* Level 12 */
#define _AD_PRIORITY_LEVEL13                (0x0000000DUL) /* Level 13 */
#define _AD_PRIORITY_LEVEL14                (0x0000000EUL) /* Level 14 */
#define _AD_PRIORITY_LEVEL15                (0x0000000FUL) /* Level 15 */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define _AD0_CHANNEL_SELECT_A               (0x0005U)//Channel 0/1
#define _AD0_ADDAVG_CHANNEL_SELECT          (0x0000U)
#define _AD0_DISCONECT_SETTING              (0x00U)
#define _AD0_COMPARECHANNEL_SELECT          (0x0000U)
#define _AD0_COMPARELEVEL_SELECT            (0x0000U)
#define _AD0_SAMPLING_STATE_0               (0x0bU)
#define _AD0_SAMPLING_STATE_1               (0x0bU)
#define _AD0_SAMPLING_STATE_2               (0x0bU)
#define _AD0_SAMPLING_STATE_3               (0x0bU)
#define _AD0_DSH_SAMPLING_STATE             (0x0018U)
#define _AD0_DSH_CHANNEL_SELECT             (0x0700U)

#define _AD1_CHANNEL_SELECT_A               (0x8000U)
#define _AD1_ADDAVG_CHANNEL_SELECT          (0x1800U)
#define _AD1_DISCONECT_SETTING              (0x00U)
#define _AD1_COMPARECHANNEL_SELECT          (0x0000U)
#define _AD1_COMPARELEVEL_SELECT            (0x0000U)
#define _AD1_SAMPLING_STATE_L               (0x16U)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum
{
    ADCHANNEL0, ADCHANNEL1, ADCHANNEL2, ADCHANNEL3, ADCHANNEL4, ADCHANNEL5, ADCHANNEL6,
    ADCHANNEL7, ADCHANNEL8, ADCHANNEL9, ADCHANNEL10, ADCHANNEL11, ADCHANNEL12,
    ADCHANNEL13, ADCHANNEL14, ADCHANNEL15
} ad_channel_t;

void R_S12AD0_Create(void);
void R_S12AD0_Start(void);
void R_S12AD0_Stop(void);
void R_S12AD0_Get_ValueResult(ad_channel_t channel, uint16_t * const buffer);

void R_S12AD1_Create(void);
void R_S12AD1_Start(void);
void R_S12AD1_Stop(void);
void R_S12AD1_Get_ValueResult(ad_channel_t channel, uint16_t * const buffer);

//void adc_scan_end_isr(void);


#endif
