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
* Copyright (C) 2023 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* System Name  : EnDat driver
* File Name    : r_endat_rzt2.c
* Version      :
* Device       : RZ
* Abstract     : EnDat driver source file.
* Tool-Chain   : IAR Embedded Workbench for ARM
*                Renesas e2studio
* OS           : Not use
* H/W Platform : RZ/T2
* Description  : Source file of EnDat driver on RZ devices.
* Limitation   : None
*******************************************************************************/
/*******************************************************************************
* History      : History is managed by Revision Control System.
*******************************************************************************/
/*******************************************************************************
Includes <System Includes> , "Project Includes"
*******************************************************************************/
#include "bsp_api.h"
#include <stdio.h>
#include "iodefine_endat.h"
#include "r_ecl_rzt2_if.h"
#include "r_endat_rzt2_if.h"
#include "r_endat_rzt2_config.h"

/*******************************************************************************
Macro definitions
*******************************************************************************/
/* Version of EnDat driver */
#define ENDAT_VERSION           (0x00010001u)

/* EnDat base address */
#define ENDAT(addr)             (*(volatile struct st_endat *)(addr))
#define ENDAT_BASE_ADDR0        (0xA011C100)
#define ENDAT_BASE_ADDR1        (0xA031C100)

#define ENDAT_FDAT_DR(ch)       (*(volatile ENDAT_FDAT *)((ch)==0 ? BASE_FDAT_ADDR_CH0 :\
                                                                    BASE_FDAT_ADDR_CH1))
#define BASE_FDAT_ADDR_CH0      (0xA0FD3000u)
#define BASE_FDAT_ADDR_CH1      (0xA0FD3200u)

#define ENDAT_NF_DR(ch)         (*(volatile ENDAT_NF *)((ch)==0 ? BASE_NF_ADDR_CH0 :\
                                                                  BASE_NF_ADDR_CH1))
#define BASE_NF_ADDR_CH0        (0xA0FD5003u)
#define BASE_NF_ADDR_CH1        (0xA0FD5017u)

/* EnDat ID of Encoder I/F */
#define ENDAT_ID0               (R_ECL_CH_0)
#define ENDAT_ID1               (R_ECL_CH_1)

/* EnDat channel */
#define ENDAT_CH0               (0u)
#define ENDAT_CH1               (1u)
#define ENDAT_CH_NUM            (2u)

/* Number of commands of R_ENDAT_Control function */
#define ENDAT_CMD_NUM           (2)

/* Interrupt mask of EnDat sample driver */
/* Enable MBERR, WDG, RXEND, RDSTC       */
#define ENDAT_INT_MASK          (0x003A0000uL)

/* Encoder initialization constant */
#define ENDAT_CLR_ALM_ADDR      (0x00u)
#define ENDAT_CLR_ALM_PRAM      (0x0000u)
#define ENDAT_CLR_WARN_ADDR     (0x01u)
#define ENDAT_CLR_WARN_PRAM     (0x0000u)
#define ENDAT_STAT_ERR          (0x00161C7EuL)
#define ENDAT_STAT_NORMAL_CHECK (0x00000000uL)
#define ENDAT_DWL_ADDR          (0x0Du)
#define ENDAT_DWL_NVM_MASK      (0x003Fu)

/* Register of the reset value */
#define ENDAT_SEND_RST_VAL      (0x0uL)
#define ENDAT_CFG1_RST_VAL      (0x0uL)
#define ENDAT_CFG2_RST_VAL      (0x0uL)
#define ENDAT_INTE_RST_VAL      (0x0uL)
#define ENDAT_CPTL_RST_VAL      (0x0001u)
#define ENDAT_STAT_RST_VAL      (0x003FFF3FuL)
#define ENDAT_NF_RST_VAL        (0x0010u)

/* Check of STAT register */
#define ENDAT_STAT_ERR1_BIT     (0x00000002u)
#define ENDAT_STAT_CRC1_BIT     (0x00000004u)
#define ENDAT_STAT_FTYPE1_BIT   (0x00000008u)
#define ENDAT_STAT_FTYPE2_BIT   (0x00000010u)
#define ENDAT_STAT_MRSADR_BIT   (0x00000020u)
#define ENDAT_STAT_FIFOERR_BIT  (0x00000040u)
#define ENDAT_STAT_ERR2_BIT     (0x00000400u)
#define ENDAT_STAT_CRC3_BIT     (0x00000800u)
#define ENDAT_STAT_CRC2_BIT     (0x00001000u)
#define ENDAT_STAT_BUSY_BIT     (0x00002000u)
#define ENDAT_STAT_RM_BIT       (0x00004000u)
#define ENDAT_STAT_WRN_BIT      (0x00008000u)
#define ENDAT_STAT_RTCNT_BIT    (0x00010000u)
#define ENDAT_STAT_WDG_BIT      (0x00020000u)
#define ENDAT_STAT_FTYPE3_BIT   (0x00040000u)
#define ENDAT_STAT_RXEND_BIT    (0x00080000u)
#define ENDAT_STAT_MBERR_BIT    (0x00100000u)
#define ENDAT_STAT_RDSTC_BIT    (0x00200000u)
#define ENDAT_STAT_XOR_CLR      (0x00000400u)

/* info parameters check */
#define ENDAT_WATCHDOG_TIME_MAX (127u)

/* Macro of the cable propagation delay measurement */
#define ENDAT_FTCLK_NUM         (8u)
#define ENDAT_CAL_5             (5u)
#define ENDAT_CAL_1             (1u)
#define ENDAT_16670_CYC         (60u)
#define ENDAT_8330_CYC          (120u)
#define ENDAT_4160_CYC          (240u)
#define ENDAT_4000_CYC          (250u)
#define ENDAT_2000_CYC          (500u)
#define ENDAT_1000_CYC          (1000u)
#define ENDAT_200_CYC           (5000u)
#define ENDAT_100_CYC           (10000u)
#define ENDAT_NFINTV0_16670     (0u)
#define ENDAT_NFINTV0_8330      (0u)
#define ENDAT_NFINTV0_4160      (0u)
#define ENDAT_NFINTV0_4000      (0u)
#define ENDAT_NFINTV0_2000      (0u)
#define ENDAT_NFINTV0_1000      (1u)
#define ENDAT_NFINTV0_200       (3u)
#define ENDAT_NFINTV0_100       (4u)
#define ENDAT_NFSCNT0_16670     (0u)
#define ENDAT_NFSCNT0_8330      (1u)
#define ENDAT_NFSCNT0_4160      (4u)
#define ENDAT_NFSCNT0_4000      (4u)
#define ENDAT_NFSCNT0_2000      (9u)
#define ENDAT_NFSCNT0_1000      (9u)
#define ENDAT_NFSCNT0_200       (11u)
#define ENDAT_NFSCNT0_100       (11u)

/* Bit manipulation */
#define ENDAT_BIT_SET           (1u)
#define ENDAT_MSB16_MASK        (0x0000FFFFuL)
#define ENDAT_32_SHIFT          (32u)
#define ENDAT_SET_PI(send,v)    (((send)&~ENDAT_PI_MASK) | ((uint32_t)(v)&ENDAT_PI_MASK))
#define ENDAT_SET_MAP(send,v)   (((send)&~ENDAT_MAP_MASK) | (((uint32_t)(v)<<ENDAT_MAP_SHIFT)&ENDAT_MAP_MASK))
#define ENDAT_SET_MB(send,v)    (((send)&~ENDAT_MB_MASK) | (((uint32_t)(v)<<ENDAT_MB_SHIFT)&ENDAT_MB_MASK))
#define ENDAT_PI_MASK           (0x0000FFFFuL)
#define ENDAT_MAP_MASK          (0x00FF0000uL)
#define ENDAT_MB_MASK           (0x3F000000uL)
#define ENDAT_RTCNTEN_MASK      (0x40000000uL)
#define ENDAT_MAP_SHIFT         (16u)
#define ENDAT_MB_SHIFT          (24u)
#define ENDAT_SET_FTCLK(cfg1,v) (((cfg1)&~ENDAT_FTCLK_MASK) | (((uint32_t)(v)<<ENDAT_FTCLK_SHIFT)&ENDAT_FTCLK_MASK))
#define ENDAT_SET_DWL(cfg1,v)   (((cfg1)&~ENDAT_DWL_MASK) | (((uint32_t)(v)<<ENDAT_DWL_SHIFT)&ENDAT_DWL_MASK))
#define ENDAT_SET_CPTU(cfg1,v)  (((cfg1)&~ENDAT_CPTU_MASK) | (((uint32_t)(v)<<ENDAT_CPTU_SHIFT)&ENDAT_CPTU_MASK))
#define ENDAT_DU_BIT            (0x00000002uL)
#define ENDAT_DT_BIT            (0x00000004uL)
#define ENDAT_FTCLK_MASK        (0x000000F0uL)
#define ENDAT_DWL_MASK          (0x00003F00uL)
#define ENDAT_RWIN_BIT          (0x00004000uL)
#define ENDAT_ARST_BIT          (0x00008000uL)
#define ENDAT_CPTU_MASK         (0x00FF0000uL)
#define ENDAT_DLY_BIT           (0x01000000uL)
#define ENDAT_RST_BIT           (0x20000000uL)
#define ENDAT_FTCLK_SHIFT       (4u)
#define ENDAT_DWL_SHIFT         (8u)
#define ENDAT_CPTU_SHIFT        (16u)
#define ENDAT_SET_WDG(cfg2,v)   (((cfg2)&~ENDAT_WDG_MASK) | (((uint32_t)(v)<<ENDAT_WDG_SHIFT)&ENDAT_WDG_MASK))
#define ENDAT_SET_TST(cfg2,v)   (((cfg2)&~ENDAT_TST_MASK) | (((uint32_t)(v)<<ENDAT_TST_SHIFT)&ENDAT_TST_MASK))
#define ENDAT_WDG_MASK          (0x0000FF00uL)
#define ENDAT_TST_MASK          (0x00070000uL)
#define ENDAT_WDG_SHIFT         (8u)
#define ENDAT_TST_SHIFT         (16u)
#define ENDAT_SET_ELC0(mode,v)  ((uint8_t)(((mode)&~ENDAT_ELC0_MASK) | ((v)&ENDAT_ELC0_MASK)))
#define ENDAT_SET_FIFOE(mode,v) ((uint8_t)(((mode)&~ENDAT_FIFOE_MASK) \
                                | (((v)<<ENDAT_FIFOE_SHIFT)&(uint8_t)ENDAT_FIFOE_MASK)))
#define ENDAT_SET_FIFOE2(mode,v) ((uint8_t)(((reg)&~ENDAT_FIFOE2_MASK) \
                                | (((v)<<ENDAT_FIFOE2_SHIFT)&(uint8_t)ENDAT_FIFOE2_MASK)))
#define ENDAT_ELC0_MASK         (0x01u)
#define ENDAT_FIFOE_MASK        (0x02u)
#define ENDAT_FIFOE2_MASK       (0x04u)
#define ENDAT_FIFOE_SHIFT       (1u)
#define ENDAT_FIFOE2_SHIFT      (2u)

#define ENDAT_CPTU_POS          (1u)
#define ENDAT_CPTU_PARAM        (24u)
#define ENDAT_CPTU_ADD          (R_ENDAT_ADD_NUM * 30 + 3)

#define PARAMETER_NOT_USED(p)       (void) ((p))

/*******************************************************************************
Typedef definitions
*******************************************************************************/
typedef r_endat_err_t(*control_func_t)(uint8_t ch, void *const pbuf);

/* Status of EnDat driver */
typedef enum
{
    ENDAT_STATE_STOP,
    ENDAT_STATE_IDLE,
    ENDAT_STATE_TRANS,
    ENDAT_STATE_CONTINUE,
    ENDAT_STATE_ELCTIMER,
} endat_state_t;

/*******************************************************************************
Imported global variables and functions (from other files)
*******************************************************************************/

/*******************************************************************************
Exported global variables and functions (to be accessed by other files)
*******************************************************************************/

/*******************************************************************************
Private variables and functions
*******************************************************************************/
/* Prototype declaration of the interrupt function */
void endat0_rx_int_isr(void);
void endat1_rx_int_isr(void);
void endat0_fifo_int_isr(void);
void endat1_fifo_int_isr(void);

/* Prototype declaration of private functions */
static r_endat_err_t endat_send_req(uint8_t ch, void *const pbuf);
static r_endat_err_t endat_conti_stop(uint8_t ch,void *const pbuf);
static r_endat_err_t endat_enc_init(uint8_t ch, r_endat_info_t* pinfo);
static void endat_enc_init_reset(uint8_t ch, r_endat_wait_cb_t penc_init_reset_wait);
static r_endat_err_t endat_enc_init_clr_alm(uint8_t ch,
                                            r_endat_wait_cb_t penc_init_mem_wait,
                                            r_endat_wait_cb_t penc_init_pram_wait);
static r_endat_err_t endat_enc_init_clr_warn(uint8_t ch,
                                             r_endat_wait_cb_t penc_init_mem_wait,
                                             r_endat_wait_cb_t penc_init_pram_wait);
static r_endat_err_t endat_enc_init_dwl_check(uint8_t ch,
                                             r_endat_wait_cb_t penc_init_mem_wait,
                                             r_endat_wait_cb_t penc_init_pram_wait);
static r_endat_err_t endat_cable_propagation(uint8_t ch,
                                             uint8_t ftclk,
                                             r_endat_wait_cb_t penc_init_cable_wait);
static void endat_noise_filter(uint8_t ch, uint8_t ftclk);
static r_endat_err_t endat_info_check(r_endat_info_t* pinfo);
static void endat_reg_init(uint8_t ch, r_endat_info_t* pinfo);
static void endat_reg_clr(uint8_t ch);
static void endat_check_send_pram(uint8_t ch, r_endat_req_t* req);
static void endat_send_cmd(uint8_t ch,
                           uint8_t mode_cmd,
                           uint8_t mrs_addr_paddr,
                           uint16_t param_instruction,
                           bool rtcnt_enable);
static void endat_set_pos_cmd(uint8_t ch, bool rtcnt_enable);
static void endat_int_common(uint8_t ch);
static void endat_fifo_int_common(uint8_t ch);

/* Array of the EnDat base address */
static void* const pendat_base_addr_tbl[ENDAT_CH_NUM] =
{
    (void *)ENDAT_BASE_ADDR0,
    (void *)ENDAT_BASE_ADDR1
};

/* Array of the commands of R_ENDAT_Control function */
static const r_endat_cmd_t endat_cmd_tbl[ENDAT_CMD_NUM] =
{
    ENDAT_CMD_REQ,
    ENDAT_CMD_POS_STOP
};

/* Array of the transmission frequency */
static const uint8_t endat_cable_ftclk_tbl[ENDAT_FTCLK_NUM] =
{
    R_ENDAT_FTCLK_16670,
    R_ENDAT_FTCLK_8330,
    R_ENDAT_FTCLK_4160,
    R_ENDAT_FTCLK_4000,
    R_ENDAT_FTCLK_2000,
    R_ENDAT_FTCLK_1000,
    R_ENDAT_FTCLK_200,
    R_ENDAT_FTCLK_100
};

/* Array of the cycle of transmission frequency */
static const uint16_t endat_ftclk_cyc_tbl[ENDAT_FTCLK_NUM] =
{
    ENDAT_16670_CYC,
    ENDAT_8330_CYC,
    ENDAT_4160_CYC,
    ENDAT_4000_CYC,
    ENDAT_2000_CYC,
    ENDAT_1000_CYC,
    ENDAT_200_CYC,
    ENDAT_100_CYC
};

/* Array of setting value of NFINTV0 */
static const uint8_t endat_cable_nfintv_tbl[ENDAT_FTCLK_NUM] =
{
    ENDAT_NFINTV0_16670,
    ENDAT_NFINTV0_8330,
    ENDAT_NFINTV0_4160,
    ENDAT_NFINTV0_4000,
    ENDAT_NFINTV0_2000,
    ENDAT_NFINTV0_1000,
    ENDAT_NFINTV0_200,
    ENDAT_NFINTV0_100
};

/* Array of setting value of NFSCNT0 */
static const uint8_t endat_cable_nfscnt_tbl[ENDAT_FTCLK_NUM] =
{
    ENDAT_NFSCNT0_16670,
    ENDAT_NFSCNT0_8330,
    ENDAT_NFSCNT0_4160,
    ENDAT_NFSCNT0_4000,
    ENDAT_NFSCNT0_2000,
    ENDAT_NFSCNT0_1000,
    ENDAT_NFSCNT0_200,
    ENDAT_NFSCNT0_100
};

/* Array of functions of R_ENDAT_Control commands */
static const control_func_t control_func_tbl[ENDAT_CMD_NUM] =
{
    &endat_send_req,
    &endat_conti_stop
};

/* Array of the status of EnDat sample driver */
static endat_state_t endat_state[ENDAT_CH_NUM] =
{
    ENDAT_STATE_STOP,
    ENDAT_STATE_STOP
};

/* Array of the address of R_ENDAT_ResultCb function */
static r_endat_isr_result_cb_t pendat_isr_result_cb[ENDAT_CH_NUM] =
{
    NULL,
    NULL
};

/* Array of the address of R_ENDAT_FifodtCb function */
static r_endat_isr_fifodt_cb_t pendat_isr_fifodt_cb[ENDAT_CH_NUM] =
{
    NULL,
    NULL
};

/* Array of the address of R_ENDAT_RdstCb function */
static r_endat_isr_rdst_cb_t pendat_isr_rdst_cb[ENDAT_CH_NUM] =
{
    NULL,
    NULL
};

/* Array of the results of the request */
static r_endat_result_t endat_result[ENDAT_CH_NUM];

/* Array of the request error */
static r_endat_protocol_err_t endat_err[ENDAT_CH_NUM];

/* raw data from EnDat Safety Encoder */
static r_endat_fifodt_t fifo_result[ENDAT_CH_NUM];

/* Receive data length */
static uint8_t endat_dwl[ENDAT_CH_NUM];

/*******************************************************************************
* Function Name: R_ENDAT_GetVersion
* Description  : Get version of EnDat driver.
* Arguments    : None.
* Return Value : Driver version.
*******************************************************************************/
uint32_t R_ENDAT_GetVersion(void)
{
    return ENDAT_VERSION;
}
/*******************************************************************************
End of function R_ENDAT_GetVersion
*******************************************************************************/

/*******************************************************************************
* Function Name: R_ENDAT_Open
* Description  : Start EnDat driver.
* Arguments    : id    - ID of Encoder I/F.
*                pinfo - Address of information.
* Return Value : Error code.
*******************************************************************************/
r_endat_err_t R_ENDAT_Open(const int32_t id, r_endat_info_t* pinfo)
{
    r_endat_err_t result = ENDAT_SUCCESS;
    uint8_t endat_ch;

    /* Check id */
    if (ENDAT_ID0 == id)
    {
        endat_ch = ENDAT_CH0;
    }
    else if (ENDAT_ID1 == id)
    {
        endat_ch = ENDAT_CH1;
    }
    else
    {
        goto error_arg;
    }

    /* NULL check pinfo */
    if (NULL == pinfo)
    {
        goto error_arg;
    }

    /* Check the parameters */
    result = endat_info_check(pinfo);
    if (ENDAT_SUCCESS != result)
    {
        goto func_end;
    }

    /* Check status  of the EnDat Sample Driver */
    if (ENDAT_STATE_STOP != endat_state[endat_ch])
    {
        goto error_not_start;
    }

    /* Set of noise filter */
    if (false != pinfo->filter)
    {
        endat_noise_filter(endat_ch, pinfo->ftclk);
    }
    

    /* Initialization of the encoder. */
    result = endat_enc_init(endat_ch, pinfo);
    if (ENDAT_SUCCESS != result)
    {
        goto error_drv;
    }

    /* Propagation delay measurement */
    if (false != pinfo->delay_comp)
    {
        
        result = endat_cable_propagation(endat_ch, pinfo->ftclk, pinfo->penc_init_cable_wait);
        if (ENDAT_SUCCESS != result)
        {
            goto error_drv;
        }
    }

    /* Initialization of EnDat */
    endat_reg_init(endat_ch, pinfo);

    /* Interrupt settings */
    if(endat_ch == 0){
      R_BSP_IrqDisable(VECTOR_NUMBER_ENCIF_INT0);
      R_BSP_IrqCfg(VECTOR_NUMBER_ENCIF_INT0, 11, NULL);
      R_BSP_IrqEnable(VECTOR_NUMBER_ENCIF_INT0);
      R_BSP_IrqDisable(VECTOR_NUMBER_ENCIF_INT2);
      R_BSP_IrqCfg(VECTOR_NUMBER_ENCIF_INT2, 11, NULL);
      R_BSP_IrqEnable(VECTOR_NUMBER_ENCIF_INT2);
    }else{
      R_BSP_IrqDisable(VECTOR_NUMBER_ENCIF_INT4);
      R_BSP_IrqCfg(VECTOR_NUMBER_ENCIF_INT4, 11, NULL);
      R_BSP_IrqEnable(VECTOR_NUMBER_ENCIF_INT4);    
      R_BSP_IrqDisable(VECTOR_NUMBER_ENCIF_INT6);
      R_BSP_IrqCfg(VECTOR_NUMBER_ENCIF_INT6, 11, NULL);
      R_BSP_IrqEnable(VECTOR_NUMBER_ENCIF_INT6);
    }
    
    ENDAT(pendat_base_addr_tbl[endat_ch]).INTE.LONG = ENDAT_INT_MASK;

    /* Change status of EnDat Sample Driver */
    endat_state[endat_ch] = ENDAT_STATE_IDLE;

    goto func_end;

error_arg:
    result = ENDAT_ERR_INVALID_ARG;
    goto func_end;

error_not_start:
    result = ENDAT_ERR_ACCESS;
    goto func_end;

error_drv:
    endat_reg_clr(endat_ch);
    goto func_end;

func_end:
    return result;
}
/*******************************************************************************
End of function R_ENDAT_Open
*******************************************************************************/

/*******************************************************************************
* Function Name: R_ENDAT_Control
* Description  : Control command for encode IF.
* Arguments    : id   - ID of Encoder I/F.
*                cmd  - Command.
*                pbuf - Address of buffer.
* Return Value : Error code.
*******************************************************************************/
r_endat_err_t R_ENDAT_Control(const int32_t id, const r_endat_cmd_t cmd, void *const pbuf)
{
    r_endat_err_t result = ENDAT_SUCCESS;
    uint8_t endat_ch;
    uint32_t index;

    /* Check id */
    if (ENDAT_ID0 == id)
    {
        endat_ch = ENDAT_CH0;
    }
    else if (ENDAT_ID1 == id)
    {
        endat_ch = ENDAT_CH1;
    }
    else
    {
        goto error_arg;
    }

    for (index = 0u; index < ENDAT_CMD_NUM; index++)
    {
        if (cmd == endat_cmd_tbl[index])
        {
            break;
        }
    }

    if (ENDAT_CMD_NUM <= index)
    {
        goto error_arg;
    }

    /* Execute command. */
    result = control_func_tbl[index](endat_ch, pbuf);

    goto func_end;

error_arg:
    result = ENDAT_ERR_INVALID_ARG;
    goto func_end;

func_end:
    return result;
}
/*******************************************************************************
End of function R_ENDAT_Control
*******************************************************************************/

/*******************************************************************************
* Function Name: R_ENDAT_Close
* Description  : Stop EnDat driver.
* Arguments    : id - ID of Encoder I/F.
* Return Value : Error code.
*******************************************************************************/
r_endat_err_t R_ENDAT_Close(const int32_t id)
{
    r_endat_err_t result = ENDAT_SUCCESS;
    uint8_t endat_ch;

    /* Check id */
    if (ENDAT_ID0 == id)
    {
        endat_ch = ENDAT_CH0;
    }
    else if (ENDAT_ID1 == id)
    {
        endat_ch = ENDAT_CH1;
    }
    else
    {
        goto error_arg;
    }

    /* Check status of EnDat Sample Driver */
    if ((ENDAT_STATE_TRANS == endat_state[endat_ch]) || (ENDAT_STATE_CONTINUE == endat_state[endat_ch]))
    {
        goto error_not_start;
    }

    if (ENDAT_STATE_IDLE == endat_state[endat_ch])
    {
        // R_ICU_Disable(endat_isr_id_tbl[endat_ch]);
        endat_reg_clr(endat_ch);

        /* Change status of EnDat Sample Driver */
        endat_state[endat_ch] = ENDAT_STATE_STOP;
    }

    goto func_end;

error_arg:
    result = ENDAT_ERR_INVALID_ARG;
    goto func_end;

error_not_start:
    result = ENDAT_ERR_ACCESS;
    goto func_end;

func_end:
    return result;
}
/*******************************************************************************
End of function R_ENDAT_Close
*******************************************************************************/

/*******************************************************************************
* Function Name: endat_send_req
* Description  : Send request to EnDat driver.
* Arguments    : ch   - EnDat channel.
*                pbuf - Buffer address.
* Return Value : Error code.
*******************************************************************************/
static r_endat_err_t endat_send_req(uint8_t ch, void *const pbuf)
{
    r_endat_err_t result = ENDAT_SUCCESS;
    r_endat_req_t * pendat_req = pbuf;
    uint8_t mode_byte;

    /* Check NULL of Arguments. */
    if (NULL == pendat_req)
    {
        goto error_arg;
    }

    if ((R_ENDAT_WD_RANGE_US != pendat_req->watchdog.range) &&
        (R_ENDAT_WD_RANGE_MS != pendat_req->watchdog.range))
    {
        goto error_arg;
    }

    if (ENDAT_WATCHDOG_TIME_MAX < pendat_req->watchdog.time)
    {
        goto error_arg;
    }

    /* Check NULL of Address of the callback function */
    if ((NULL == pendat_req->pisr_result) || (NULL == pendat_req->pisr_rdst))
    {
        goto error_arg;
    }

    /* Check status  of the EnDat Sample Driver */
    if (ENDAT_STATE_STOP == endat_state[ch])
    {
        goto error_access;
    }
    if ((ENDAT_STATE_TRANS == endat_state[ch]) ||
        (ENDAT_STATE_CONTINUE == endat_state[ch]) ||
        (ENDAT_STATE_ELCTIMER == endat_state[ch]))
    {
        goto error_busy;
    }

    /* Check the RDST bit */
    if (0u == ENDAT(pendat_base_addr_tbl[ch]).STAT.BIT.RDST)
    {
        goto error_busy;
    }

    /* Change status of EnDat Sample Driver */
    if (false != pendat_req->dt)
    {
        endat_state[ch] = ENDAT_STATE_CONTINUE;

        /* Enable the Continuous mode */
        ENDAT(pendat_base_addr_tbl[ch]).CFG1.BIT.DT = ENDAT_BIT_SET;
        mode_byte = ENDAT(pendat_base_addr_tbl[ch]).MODE.BYTE;
        mode_byte = ENDAT_SET_ELC0(mode_byte, 0);
        mode_byte = ENDAT_SET_FIFOE(mode_byte, pendat_req->fifo_enable);
        ENDAT(pendat_base_addr_tbl[ch]).MODE.BYTE = mode_byte;;
    }
    else if (false != pendat_req->elc)
    {
        endat_state[ch] = ENDAT_STATE_ELCTIMER;

        /* Enable ELC mode */
        ENDAT(pendat_base_addr_tbl[ch]).CFG1.BIT.DT = 0u;
        mode_byte = ENDAT(pendat_base_addr_tbl[ch]).MODE.BYTE;
        mode_byte = ENDAT_SET_ELC0(mode_byte, ENDAT_BIT_SET);
        mode_byte = ENDAT_SET_FIFOE(mode_byte, pendat_req->fifo_enable);
        ENDAT(pendat_base_addr_tbl[ch]).MODE.BYTE = mode_byte;;
    }
    else
    {
        endat_state[ch] = ENDAT_STATE_TRANS;

        ENDAT(pendat_base_addr_tbl[ch]).CFG1.BIT.DT = 0u;
        mode_byte = ENDAT(pendat_base_addr_tbl[ch]).MODE.BYTE;
        mode_byte = ENDAT_SET_ELC0(mode_byte, 0);
        mode_byte = ENDAT_SET_FIFOE(mode_byte, pendat_req->fifo_enable);
        ENDAT(pendat_base_addr_tbl[ch]).MODE.BYTE = mode_byte;;
    }

    /* FIFO soft reset */
    ENDAT(pendat_base_addr_tbl[ch]).FIFOSRST.LONG = 1;
    ENDAT(pendat_base_addr_tbl[ch]).FIFOSRST.LONG = 0;

    /* set FIFO threshold */
    if(R_ENDAT_POS == pendat_req->mode_cmd)
    {
        ENDAT(pendat_base_addr_tbl[ch]).FIFOTH.BIT.PAETH = R_ENDAT_FIFO_POS_PAETH;
    }
    else
    {
        ENDAT(pendat_base_addr_tbl[ch]).FIFOTH.BIT.PAETH = R_ENDAT_FIFO_PAETH;
    }
    fifo_result[ch].mode_cmd = pendat_req->mode_cmd;
    fifo_result[ch].rtcnt_pre = ENDAT(pendat_base_addr_tbl[ch]).RTCNT.WORD;

    /* Register the callback function */
    pendat_isr_result_cb[ch] = pendat_req->pisr_result;
    pendat_isr_fifodt_cb[ch] = pendat_req->pisr_fifodt;
    pendat_isr_rdst_cb[ch]   = pendat_req->pisr_rdst;

    /* Setting of watchdog timer */
    ENDAT(pendat_base_addr_tbl[ch]).CFG2.LONG
        = ENDAT_SET_WDG(ENDAT(pendat_base_addr_tbl[ch]).CFG2.LONG, (pendat_req->watchdog.range |
                                                                    pendat_req->watchdog.time));

    /* Send mode command */
    if(endat_state[ch] != ENDAT_STATE_ELCTIMER)
    {
        endat_check_send_pram(ch, pendat_req);
    }
    else if (R_ENDAT_POS == pendat_req->mode_cmd)
    {
        endat_set_pos_cmd(ch, pendat_req->rtcnt_enable);  /* set command without strobe */
    }
    else
    {
        goto error_arg;
    }

    goto func_end;

error_arg:
    result = ENDAT_ERR_INVALID_ARG;
    goto func_end;

error_busy:
    result = ENDAT_ERR_BUSY;
    goto func_end;

error_access:
    result = ENDAT_ERR_ACCESS;
    goto func_end;

func_end:
    return result;
}
/*******************************************************************************
End of function endat_send_req
*******************************************************************************/

/*******************************************************************************
* Function Name: endat_conti_stop
* Description  : Send request to EnDat driver.
* Arguments    : ch   - EnDat channel.
*                pbuf - Buffer address.
* Return Value : Error code.
*******************************************************************************/
static r_endat_err_t endat_conti_stop(uint8_t ch, void *const pbuf)
{
    PARAMETER_NOT_USED(pbuf);
    r_endat_err_t result = ENDAT_SUCCESS;
    uint8_t mode_byte;

    /* Check status of the EnDat Sample Driver */
    if (ENDAT_STATE_CONTINUE == endat_state[ch])
    {
        /* Disable the Continuous mode */
        ENDAT(pendat_base_addr_tbl[ch]).CFG1.BIT.DT = 0u;
    }
    else if (ENDAT_STATE_ELCTIMER == endat_state[ch])
    {
        /* Disable ELC mode */
        mode_byte = ENDAT(pendat_base_addr_tbl[ch]).MODE.BYTE;
        mode_byte = ENDAT_SET_ELC0(mode_byte, 0);
        ENDAT(pendat_base_addr_tbl[ch]).MODE.BYTE = mode_byte;;
    }
    else
    {
        goto error_access;
    }
    endat_state[ch] = ENDAT_STATE_IDLE;

    goto func_end;

error_access:
    result = ENDAT_ERR_ACCESS;
    goto func_end;

func_end:
    return result;
}
/*******************************************************************************
End of function endat_conti_stop
*******************************************************************************/

/*******************************************************************************
* Function Name: endat_enc_init
* Description  : Reset of the encoder.
* Arguments    : ch    - EnDat channel.
*                pinfo - Address of information.
* Return Value : Error code.
*******************************************************************************/
static r_endat_err_t endat_enc_init(uint8_t ch, r_endat_info_t* pinfo)
{
    r_endat_err_t result = ENDAT_SUCCESS;

    /* Setting of the transmission clock(100KHz) */
    ENDAT(pendat_base_addr_tbl[ch]).CFG1.LONG
        = ENDAT_SET_FTCLK(ENDAT(pendat_base_addr_tbl[ch]).CFG1.LONG, R_ENDAT_FTCLK_100);

    /* Reset of the encoder. */
    endat_enc_init_reset(ch, pinfo->penc_init_reset_wait);
    
    /* Confirmation of receipt data length. */
    result = endat_enc_init_dwl_check(ch,
                                      pinfo->penc_init_mem_wait,
                                      pinfo->penc_init_pram_wait);
    if (ENDAT_SUCCESS != result)
    {
        goto func_end;
    }

    /* Clear the alarm of the encoder. */
    result = endat_enc_init_clr_alm(ch,
                                    pinfo->penc_init_mem_wait,
                                    pinfo->penc_init_pram_wait);
    if (ENDAT_SUCCESS != result)
    {
        goto func_end;
    }

    /* Clear the warning of the encoder. */
    result = endat_enc_init_clr_warn(ch,
                                    pinfo->penc_init_mem_wait,
                                    pinfo->penc_init_pram_wait);
    if (ENDAT_SUCCESS != result)
    {
        goto func_end;
    }

    /* Reset of the encoder. */
    endat_enc_init_reset(ch, pinfo->penc_init_reset_wait);

func_end:
    return result;
}
/*******************************************************************************
End of function endat_enc_init
*******************************************************************************/

/*******************************************************************************
* Function Name: endat_enc_init_reset
* Description  : Reset the encoder.
* Arguments    : ch                   - EnDat channel.
*                penc_init_reset_wait - Wait callback function.
* Return Value : None.
*******************************************************************************/
static void endat_enc_init_reset(uint8_t ch, r_endat_wait_cb_t penc_init_reset_wait)
{
    /* Encoder receives a reset. */
    endat_send_cmd(ch, R_ENDAT_RESET, 0u, 0u, false);

    if (NULL != penc_init_reset_wait)
    {
        penc_init_reset_wait();
    }

    ENDAT(pendat_base_addr_tbl[ch]).STAT.BIT.RX1   = ENDAT_BIT_SET;
    ENDAT(pendat_base_addr_tbl[ch]).STAT.BIT.RXEND = ENDAT_BIT_SET;
    ENDAT(pendat_base_addr_tbl[ch]).STAT.BIT.RDSTC = ENDAT_BIT_SET;

    return;
}
/*******************************************************************************
End of function endat_enc_init_reset
*******************************************************************************/

/*******************************************************************************
* Function Name: endat_enc_init_clr_alm
* Description  : Reset the alarm of the encoder.
* Arguments    : ch                  - EnDat channel.
*                penc_init_mem_wait  - Wait callback function.
*                penc_init_pram_wait - Wait callback function.
* Return Value : Error code.
*******************************************************************************/
static r_endat_err_t endat_enc_init_clr_alm(uint8_t ch,
                                            r_endat_wait_cb_t penc_init_mem_wait,
                                            r_endat_wait_cb_t penc_init_pram_wait)
{
    r_endat_err_t result = ENDAT_SUCCESS;
    uint32_t reg_val;

    /* Selection of the memory area. */
    endat_send_cmd(ch, R_ENDAT_MEM, R_ENDAT_MRS_OPE_STAT, 0u, false);

    if (NULL != penc_init_mem_wait)
    {
        penc_init_mem_wait();
    }

    if (ENDAT_BIT_SET != ENDAT(pendat_base_addr_tbl[ch]).STAT.BIT.RDST)
    {
        goto error_drv;
    }

    reg_val = ENDAT(pendat_base_addr_tbl[ch]).STAT.LONG & ENDAT_STAT_ERR;
    if (ENDAT_STAT_NORMAL_CHECK != reg_val)
    {
        goto error_drv;
    }

    ENDAT(pendat_base_addr_tbl[ch]).STAT.BIT.RX1   = ENDAT_BIT_SET;
    ENDAT(pendat_base_addr_tbl[ch]).STAT.BIT.RXEND = ENDAT_BIT_SET;
    ENDAT(pendat_base_addr_tbl[ch]).STAT.BIT.RDSTC = ENDAT_BIT_SET;

    /* Encoder receives the parameters. */
    endat_send_cmd(ch, R_ENDAT_RX_PARAM, ENDAT_CLR_ALM_ADDR, ENDAT_CLR_ALM_PRAM, false);

    if (NULL != penc_init_pram_wait)
    {
        penc_init_pram_wait();
    }

    if (ENDAT_BIT_SET != ENDAT(pendat_base_addr_tbl[ch]).STAT.BIT.RDST)
    {
        goto error_drv;
    }

    reg_val = ENDAT(pendat_base_addr_tbl[ch]).STAT.LONG & ENDAT_STAT_ERR;
    if (ENDAT_STAT_NORMAL_CHECK != reg_val)
    {
        goto error_drv;
    }

    ENDAT(pendat_base_addr_tbl[ch]).STAT.BIT.RX1   = ENDAT_BIT_SET;
    ENDAT(pendat_base_addr_tbl[ch]).STAT.BIT.RXEND = ENDAT_BIT_SET;
    ENDAT(pendat_base_addr_tbl[ch]).STAT.BIT.RDSTC = ENDAT_BIT_SET;

    goto func_end;

error_drv:
    result = ENDAT_ERR_DRV;
    goto func_end;

func_end:
    return result;
}
/*******************************************************************************
End of function endat_enc_init_clr_alm
*******************************************************************************/

/*******************************************************************************
* Function Name: endat_enc_init_clr_warn          
* Description  : Reset the warning of the encoder.
* Arguments    : ch                  - EnDat channel.         
*                penc_init_mem_wait  - Wait callback function.
*                penc_init_pram_wait - Wait callback function.
* Return Value : Error code.
*******************************************************************************/
static r_endat_err_t endat_enc_init_clr_warn(uint8_t ch,
                                             r_endat_wait_cb_t penc_init_mem_wait,
                                             r_endat_wait_cb_t penc_init_pram_wait)
{
    r_endat_err_t result = ENDAT_SUCCESS;
    uint32_t reg_val;

    /* Selection of the memory area. */
    endat_send_cmd(ch, R_ENDAT_MEM, R_ENDAT_MRS_OPE_STAT, 0u, false);

    if (NULL != penc_init_mem_wait)
    {
        penc_init_mem_wait();
    }

    if (ENDAT_BIT_SET != ENDAT(pendat_base_addr_tbl[ch]).STAT.BIT.RDST)
    {
        goto error_drv;
    }

    reg_val = ENDAT(pendat_base_addr_tbl[ch]).STAT.LONG & ENDAT_STAT_ERR;
    if (ENDAT_STAT_NORMAL_CHECK != reg_val)
    {
        goto error_drv;
    }

    ENDAT(pendat_base_addr_tbl[ch]).STAT.BIT.RX1   = ENDAT_BIT_SET;
    ENDAT(pendat_base_addr_tbl[ch]).STAT.BIT.RXEND = ENDAT_BIT_SET;
    ENDAT(pendat_base_addr_tbl[ch]).STAT.BIT.RDSTC = ENDAT_BIT_SET;

    /* Encoder receives the parameters. */
    endat_send_cmd(ch, R_ENDAT_RX_PARAM, ENDAT_CLR_WARN_ADDR, ENDAT_CLR_WARN_PRAM, false);

    if (NULL != penc_init_pram_wait)
    {
        penc_init_pram_wait();
    }

    if (ENDAT_BIT_SET != ENDAT(pendat_base_addr_tbl[ch]).STAT.BIT.RDST)
    {
        goto error_drv;
    }

    reg_val = ENDAT(pendat_base_addr_tbl[ch]).STAT.LONG & ENDAT_STAT_ERR;
    if (ENDAT_STAT_NORMAL_CHECK != reg_val)
    {
        goto error_drv;
    }

    ENDAT(pendat_base_addr_tbl[ch]).STAT.BIT.RX1   = ENDAT_BIT_SET;
    ENDAT(pendat_base_addr_tbl[ch]).STAT.BIT.RXEND = ENDAT_BIT_SET;
    ENDAT(pendat_base_addr_tbl[ch]).STAT.BIT.RDSTC = ENDAT_BIT_SET;

    goto func_end;

error_drv:
    result = ENDAT_ERR_DRV;
    goto func_end;

func_end:
    return result;
}
/*******************************************************************************
End of function endat_enc_init_clr_warn
*******************************************************************************/

/*******************************************************************************
* Function Name: endat_enc_init_dwl_check
* Description  : Check the receive data length of encoder.
* Arguments    : ch                  - EnDat channel.
*                penc_init_mem_wait  - Wait callback function.
*                penc_init_pram_wait - Wait callback function.
* Return Value : Error code.
*******************************************************************************/
static r_endat_err_t endat_enc_init_dwl_check(uint8_t ch,
                                             r_endat_wait_cb_t penc_init_mem_wait,
                                             r_endat_wait_cb_t penc_init_pram_wait)
{
    r_endat_err_t result = ENDAT_SUCCESS;
    uint32_t reg_val;

    /* Selection of the memory area. */
    endat_send_cmd(ch, R_ENDAT_MEM, R_ENDAT_MRS_ENC_MANU1, 0u, false);

    if (NULL != penc_init_mem_wait)
    {
        penc_init_mem_wait();
    }

    if (ENDAT_BIT_SET != ENDAT(pendat_base_addr_tbl[ch]).STAT.BIT.RDST)
    {
      __asm("nop");
      goto error_drv;
    }
    
    reg_val = ENDAT(pendat_base_addr_tbl[ch]).STAT.LONG & ENDAT_STAT_ERR;
    if (ENDAT_STAT_NORMAL_CHECK != reg_val)
    {
      __asm("nop");
        goto error_drv;
    }

    ENDAT(pendat_base_addr_tbl[ch]).STAT.BIT.RX1   = ENDAT_BIT_SET;
    ENDAT(pendat_base_addr_tbl[ch]).STAT.BIT.RXEND = ENDAT_BIT_SET;
    ENDAT(pendat_base_addr_tbl[ch]).STAT.BIT.RDSTC = ENDAT_BIT_SET;

    /* Encoder send the parameters. Get word13 of receive data length */
    endat_send_cmd(ch, R_ENDAT_PARAM, ENDAT_DWL_ADDR, 0u, false);
    
    if (NULL != penc_init_pram_wait)
    {
        penc_init_pram_wait();
    }

    if (ENDAT_BIT_SET != ENDAT(pendat_base_addr_tbl[ch]).STAT.BIT.RDST)
    {
      __asm("nop");
        goto error_drv;
    }

    reg_val = ENDAT(pendat_base_addr_tbl[ch]).STAT.LONG & ENDAT_STAT_ERR;
    if (ENDAT_STAT_NORMAL_CHECK != reg_val)
    {
        
      __asm("nop");
        goto error_drv;
    }

    ENDAT(pendat_base_addr_tbl[ch]).STAT.BIT.RX1   = ENDAT_BIT_SET;
    ENDAT(pendat_base_addr_tbl[ch]).STAT.BIT.RXEND = ENDAT_BIT_SET;
    ENDAT(pendat_base_addr_tbl[ch]).STAT.BIT.RDSTC = ENDAT_BIT_SET;

    /* Set the received data length */
    reg_val = ENDAT(pendat_base_addr_tbl[ch]).RECV1L.BIT.RXD1 & ENDAT_DWL_NVM_MASK;
    ENDAT(pendat_base_addr_tbl[ch]).CFG1.LONG = ENDAT_SET_DWL(ENDAT(pendat_base_addr_tbl[ch]).CFG1.LONG, reg_val);
    endat_dwl[ch] = (uint8_t)reg_val;

    goto func_end;

error_drv:
    result = ENDAT_ERR_DRV;
    goto func_end;

func_end:
    return result;
}
/*******************************************************************************
End of function endat_enc_init_dwl_check
*******************************************************************************/

/*******************************************************************************
* Function Name: endat_cable_propagation
* Description  : Measurement of the propagation delay.
* Arguments    : ch                   - EnDat channel.
*                ftclk                - Transmit frequency
*                penc_init_cable_wait - Wait callback function.
* Return Value : Error code.
*******************************************************************************/
static r_endat_err_t endat_cable_propagation(uint8_t ch,
                                             uint8_t ftclk,
                                             r_endat_wait_cb_t penc_init_cable_wait)
{
    r_endat_err_t result = ENDAT_SUCCESS;
    uint8_t loop;
    uint32_t ftclk_cyc;
    uint8_t err_count = 0u;
    uint32_t measur_sum = 0u;
    uint32_t measur_ave;
    uint32_t reg_val;
    uint8_t cptu_val;
    uint32_t div_rem;

    ftclk_cyc = endat_ftclk_cyc_tbl[0];
    for (loop = 0u; loop < ENDAT_FTCLK_NUM; loop++)
    {
        if (ftclk == endat_cable_ftclk_tbl[loop])
        {
            ftclk_cyc = endat_ftclk_cyc_tbl[loop];
        }
    }

    /* Measurement of the propagation delay */
    for (loop = 0u; loop < R_ENDAT_CABLE_DELAY; loop++)
    {
        ENDAT(pendat_base_addr_tbl[ch]).CFG1.BIT.DLY = 0u;
        ENDAT(pendat_base_addr_tbl[ch]).CFG1.BIT.DLY = ENDAT_BIT_SET;

        endat_send_cmd(ch, R_ENDAT_POS, 0u, 0u, false);

        if (NULL != penc_init_cable_wait)
        {
            penc_init_cable_wait();
        }

        if (ENDAT_BIT_SET != ENDAT(pendat_base_addr_tbl[ch]).STAT.BIT.RDST)
        {
            goto error_drv;
        }

        reg_val = ENDAT(pendat_base_addr_tbl[ch]).STAT.LONG & ENDAT_STAT_ERR;
        if (ENDAT_STAT_NORMAL_CHECK != reg_val)
        {
            goto error_drv;
        }

        measur_sum += ENDAT(pendat_base_addr_tbl[ch]).CPTL.BIT.CPTL;

        if ( 0u == ENDAT(pendat_base_addr_tbl[ch]).CPTL.BIT.CPTL)
        {
            err_count++;
        }
    }

    if (R_ENDAT_CABLE_DELAY == err_count)
    {
        goto error_drv;
    }

    /* Calculation the average value of the measurement results */
    measur_ave = measur_sum / (uint8_t)(R_ENDAT_CABLE_DELAY - err_count);

    /* Calculation of propagation delay correction */
    measur_ave = (measur_ave - ENDAT_CAL_1) * ENDAT_CAL_5;
    cptu_val = (uint8_t)(measur_ave / ftclk_cyc);
    div_rem  = (uint32_t)(measur_ave - cptu_val * ftclk_cyc);

    /* Check the upper limit of the CFG1.CPTU bit */
    if ((cptu_val > endat_dwl[ch] + ENDAT_CPTU_POS) ||
        (cptu_val > ENDAT_CPTU_PARAM)               ||
        (cptu_val > endat_dwl[ch] + ENDAT_CPTU_ADD))
    {
        goto error_drv;
    }

    ENDAT(pendat_base_addr_tbl[ch]).CFG1.LONG = ENDAT_SET_CPTU(ENDAT(pendat_base_addr_tbl[ch]).CFG1.LONG, cptu_val);
    ENDAT(pendat_base_addr_tbl[ch]).CPTL.WORD = (uint16_t)((div_rem / ENDAT_CAL_5) + ENDAT_CAL_1);

    goto func_end;

error_drv:
    result = ENDAT_ERR_DRV;
    goto func_end;

func_end:
    ENDAT(pendat_base_addr_tbl[ch]).STAT.LONG = ENDAT_STAT_RST_VAL;
    return result;
}
/*******************************************************************************
End of function endat_cable_propagation
*******************************************************************************/

/*******************************************************************************
* Function Name: endat_noise_filter
* Description  : Set of noise filter.
* Arguments    : ch    - EnDat channel.
*              : ftclk - Transmit frequency
* Return Value : None.
*******************************************************************************/
static void endat_noise_filter(uint8_t ch, uint8_t ftclk)
{
    uint8_t loop;

    for (loop = 0u; loop < ENDAT_FTCLK_NUM; loop++)
    {
        if (ftclk == endat_cable_ftclk_tbl[loop])
        {
            ENDAT_NF_DR(ch).BYTE = (uint8_t)( endat_cable_nfintv_tbl[loop] | (endat_cable_nfscnt_tbl[loop]<<4) );
        }
    }
    return;
}
/*******************************************************************************
End of function endat_noise_filter
*******************************************************************************/

/*******************************************************************************
* Function Name: endat_info_check
* Description  : parameter check of pinfo.
* Arguments    : pinfo - Setting values of CEG1 register and CFG2 register.
* Return Value : Error code.
*******************************************************************************/
static r_endat_err_t endat_info_check(r_endat_info_t* pinfo)
{
    r_endat_err_t result = ENDAT_SUCCESS;

    if ((R_ENDAT_FTCLK_16670 != pinfo->ftclk) &&
        (R_ENDAT_FTCLK_8330  != pinfo->ftclk) &&
        (R_ENDAT_FTCLK_4160  != pinfo->ftclk) &&
        (R_ENDAT_FTCLK_4000  != pinfo->ftclk) &&
        (R_ENDAT_FTCLK_2000  != pinfo->ftclk) &&
        (R_ENDAT_FTCLK_1000  != pinfo->ftclk) &&
        (R_ENDAT_FTCLK_200   != pinfo->ftclk) &&
        (R_ENDAT_FTCLK_100   != pinfo->ftclk))
    {
        goto error_arg;
    }

    if (false != pinfo->delay_comp)
    {
        if (NULL == pinfo->penc_init_cable_wait)
        {
            goto error_arg;
        }
    }

    if ((R_ENDAT_TST_HALF_TCLK != pinfo->tst) &&
        (R_ENDAT_TST_500NS     != pinfo->tst) &&
        (R_ENDAT_TST_1US       != pinfo->tst) &&
        (R_ENDAT_TST_1500NS    != pinfo->tst) &&
        (R_ENDAT_TST_2US       != pinfo->tst) &&
        (R_ENDAT_TST_4US       != pinfo->tst) &&
        (R_ENDAT_TST_8US       != pinfo->tst) &&
        (R_ENDAT_TST_10US      != pinfo->tst))
    {
        goto error_arg;
    }

    if ((NULL == pinfo->penc_init_reset_wait) ||
        (NULL == pinfo->penc_init_mem_wait)   ||
        (NULL == pinfo->penc_init_pram_wait))
    {
        goto error_arg;
    }

    goto func_end;

error_arg:
    result = ENDAT_ERR_INVALID_ARG;
    goto func_end;

func_end:
    return result;
}
/*******************************************************************************
End of function endat_info_check
*******************************************************************************/

/*******************************************************************************
* Function Name: endat_reg_init
* Description  : Setting of the CFG1 register and CFG2 register.
* Arguments    : ch    - EnDat channel.
*                pinfo - Setting values of CFG1 register and CFG2 register.
* Return Value : None.
*******************************************************************************/
static void endat_reg_init(uint8_t ch, r_endat_info_t* pinfo)
{
    /* Setting of the CFG1 register and CFG2 register */
    uint32_t cfg1_val;
    cfg1_val  =  ENDAT(pendat_base_addr_tbl[ch]).CFG1.LONG;
    cfg1_val |=  ENDAT_DU_BIT;    // set
    cfg1_val &= ~ENDAT_DT_BIT;    // clear
    cfg1_val  =  ENDAT_SET_FTCLK(cfg1_val, pinfo->ftclk);  // replace
    cfg1_val |=  ENDAT_RWIN_BIT;  // set
    cfg1_val &= ~ENDAT_ARST_BIT;  // clear
    cfg1_val &= ~ENDAT_RST_BIT;   // clear
    ENDAT(pendat_base_addr_tbl[ch]).CFG1.LONG = cfg1_val;
    ENDAT(pendat_base_addr_tbl[ch]).CFG2.LONG = ENDAT_SET_TST(ENDAT(pendat_base_addr_tbl[ch]).CFG2.LONG, pinfo->tst);

    return;
}
/*******************************************************************************
End of function endat_reg_init
*******************************************************************************/

/*******************************************************************************
* Function Name: endat_reg_clr
* Description  : Set the register to default.
* Arguments    : ch - EnDat channel.
* Return Value : None.
*******************************************************************************/
static void endat_reg_clr(uint8_t ch)
{
    ENDAT(pendat_base_addr_tbl[ch]).SEND.LONG = ENDAT_SEND_RST_VAL;
    ENDAT(pendat_base_addr_tbl[ch]).CFG1.LONG = ENDAT_CFG1_RST_VAL;
    ENDAT(pendat_base_addr_tbl[ch]).CFG2.LONG = ENDAT_CFG2_RST_VAL;
    ENDAT(pendat_base_addr_tbl[ch]).INTE.LONG = ENDAT_INTE_RST_VAL;
    ENDAT(pendat_base_addr_tbl[ch]).CPTL.WORD = ENDAT_CPTL_RST_VAL;
    ENDAT(pendat_base_addr_tbl[ch]).STAT.LONG = ENDAT_STAT_RST_VAL;
    return;
}
/*******************************************************************************
End of function endat_reg_clr
*******************************************************************************/

/*******************************************************************************
* Function Name: endat_check_send_pram
* Description  : Combine the send data.
* Arguments    : ch - EnDat channel.
*                req - MODE command.
*                    - MRS code/Address/Port addressto.
*                    - Parameters /Instructions.
* Return Value : None.
*******************************************************************************/
static void endat_check_send_pram(uint8_t ch, r_endat_req_t* req)
{
    if ((R_ENDAT_POS == req->mode_cmd) ||
        (R_ENDAT_POS_ADD_DATA == req->mode_cmd))
    {
        endat_send_cmd(ch, req->mode_cmd, 0u, 0u, req->rtcnt_enable);
    }
    else if (R_ENDAT_MEM == req->mode_cmd)
    {
        endat_send_cmd(ch, req->mode_cmd, req->mrs, 0u, req->rtcnt_enable);
    }
    else if (R_ENDAT_POS_MEM == req->mode_cmd)
    {
        endat_send_cmd(ch, req->mode_cmd, req->mrs, req->param_instruction, req->rtcnt_enable);
    }
    else if ((R_ENDAT_RX_PARAM == req->mode_cmd) ||
             (R_ENDAT_POS_RX_PARAM == req->mode_cmd))
    {
        endat_send_cmd(ch, req->mode_cmd, req->addr, req->param_instruction, req->rtcnt_enable);
    }
    else if ((R_ENDAT_PARAM == req->mode_cmd) ||
        (R_ENDAT_RESET == req->mode_cmd)      ||
        (R_ENDAT_POS_PARAM == req->mode_cmd)  ||
        (R_ENDAT_POS_RX_ERR_RESET == req->mode_cmd))
    {
        endat_send_cmd(ch, req->mode_cmd, req->addr, 0u, req->rtcnt_enable);
    }
    else
    {
        endat_send_cmd(ch, req->mode_cmd, 0u, 0u, req->rtcnt_enable);
    }

    return;
}
/*******************************************************************************
End of function endat_check_send_pram
*******************************************************************************/

/*******************************************************************************
* Function Name: endat_send_cmd
* Description  : Send the MODE command, the MRS code/Address/Port address
*                and the Parameters /Instructions.
* Arguments    : ch                - EnDat channel.
*                mode_cmd          - MODE command.
*                mrs_addr_paddr    - MRS code/Address/Port addressto.
*                param_instruction - Parameters /Instructions.
*                rtcnt_enable      - RTCNT enable flag
* Return Value : None.
*******************************************************************************/
static void endat_send_cmd(uint8_t ch,
                           uint8_t mode_cmd,
                           uint8_t mrs_addr_paddr,
                           uint16_t param_instruction,
                           bool rtcnt_enable)
{
    uint32_t send_val = 0uL;

    /* Writing the send data in the SEND register. */
    send_val = ENDAT_SET_MB( send_val, mode_cmd);
    send_val = ENDAT_SET_MAP(send_val, mrs_addr_paddr);
    send_val = ENDAT_SET_PI( send_val, param_instruction);
    send_val |= (rtcnt_enable) ? ENDAT_RTCNTEN_MASK : 0;
    ENDAT(pendat_base_addr_tbl[ch]).SEND.LONG = send_val;

    /* Send. */
    ENDAT(pendat_base_addr_tbl[ch]).SWST.BIT.STRB = ENDAT_BIT_SET;

    return;
}
/*******************************************************************************
End of function endat_send_cmd
*******************************************************************************/

/*******************************************************************************
* Function Name: endat_set_pos_cmd
* Description  : Set the MODE command.
* Arguments    : ch                - EnDat channel.
* Return Value : None.
*******************************************************************************/
static void endat_set_pos_cmd(uint8_t ch, bool rtcnt_enable)
{
    uint32_t send_val = 0uL;

    /* Writing the send data in the SEND register. */
    send_val = ENDAT_SET_MB( send_val, R_ENDAT_POS);
    send_val = ENDAT_SET_MAP(send_val, 0);
    send_val = ENDAT_SET_PI( send_val, 0);
    send_val |= (rtcnt_enable) ? ENDAT_RTCNTEN_MASK : 0;
    ENDAT(pendat_base_addr_tbl[ch]).SEND.LONG = send_val;

    return;
}
/*******************************************************************************
End of function endat_set_pos_cmd
*******************************************************************************/

/*******************************************************************************
* Function Name: endat_int_common
* Description  : Interrupt common processing.
* Arguments    : ch - EnDat channel.
* Return Value : None.
*******************************************************************************/
static void endat_int_common(uint8_t ch)
{
    uint64_t pos_shift;
    uint32_t reg_val;
    uint32_t i;

    /* Load the value of the STAT register to Local variable */
    reg_val = ENDAT(pendat_base_addr_tbl[ch]).STAT.LONG;

    if ((ENDAT_STAT_RXEND_BIT == (reg_val & ENDAT_STAT_RXEND_BIT)) ||
        (ENDAT_STAT_WDG_BIT == (reg_val & ENDAT_STAT_WDG_BIT))     ||
        (ENDAT_STAT_MBERR_BIT == (reg_val & ENDAT_STAT_MBERR_BIT)))
    {
        endat_result[ch].result      = ENDAT_REQ_SUCCESS;
        endat_result[ch].status.busy = false;
        endat_result[ch].status.rm   = false;
        endat_result[ch].status.wrn  = false;
        endat_err[ch].err1           = false;
        endat_err[ch].crc1           = false;
        endat_err[ch].ftype1         = false;
        endat_err[ch].ftype2         = false;
        endat_err[ch].mrsadr         = false;
        endat_err[ch].fifoerr        = false;
        endat_err[ch].err2           = false;
        endat_err[ch].crc3           = false;
        endat_err[ch].crc2           = false;
        endat_err[ch].wdg            = false;
        endat_err[ch].ftype3         = false;
        endat_err[ch].modeerr        = false;

        /* Check of error */
        if (ENDAT_STAT_NORMAL_CHECK != (reg_val & ENDAT_STAT_ERR))
        {
            endat_result[ch].result = ENDAT_REQ_ERR;

            if (ENDAT_STAT_ERR1_BIT == (reg_val & ENDAT_STAT_ERR1_BIT))
            {
                endat_err[ch].err1 = true;
            }

            if (ENDAT_STAT_CRC1_BIT == (reg_val & ENDAT_STAT_CRC1_BIT))
            {
                endat_err[ch].crc1 = true;
            }

            if (ENDAT_STAT_FTYPE1_BIT == (reg_val & ENDAT_STAT_FTYPE1_BIT))
            {
                endat_err[ch].ftype1 = true;
            }

            if (ENDAT_STAT_FTYPE2_BIT == (reg_val & ENDAT_STAT_FTYPE2_BIT))
            {
                endat_err[ch].ftype2 = true;
            }

            if (ENDAT_STAT_MRSADR_BIT == (reg_val & ENDAT_STAT_MRSADR_BIT))
            {
                endat_err[ch].mrsadr = true;
            }

            if (ENDAT_STAT_FIFOERR_BIT == (reg_val & ENDAT_STAT_FIFOERR_BIT))
            {
                endat_err[ch].fifoerr = true;
            }

            if (ENDAT_STAT_ERR2_BIT == (reg_val & ENDAT_STAT_ERR2_BIT))
            {
                endat_err[ch].err2 = true;
            }

            if (ENDAT_STAT_CRC3_BIT == (reg_val & ENDAT_STAT_CRC3_BIT))
            {
                endat_err[ch].crc3 = true;
            }

            if (ENDAT_STAT_CRC2_BIT == (reg_val & ENDAT_STAT_CRC2_BIT))
            {
                endat_err[ch].crc2 = true;
            }

            if (ENDAT_STAT_FTYPE3_BIT == (reg_val & ENDAT_STAT_FTYPE3_BIT))
            {
                endat_err[ch].ftype3 = true;
            }

            if (ENDAT_STAT_WDG_BIT == (reg_val & ENDAT_STAT_WDG_BIT))
            {
                endat_err[ch].wdg = true;
            }

            if (ENDAT_STAT_MBERR_BIT == (reg_val & ENDAT_STAT_MBERR_BIT))
            {
                endat_err[ch].modeerr = true;
                endat_state[ch] = ENDAT_STATE_IDLE;
            }

            if ((reg_val & ENDAT_STAT_FIFOERR_BIT) != 0u)
            {
                for (i = 0; i < R_ENDAT_FIFO_CLR + R_ENDAT_FIFO_NORM; i++)
                {
                    ENDAT_FDAT_DR(ch);  /* dummy read to clear */
                }
            }
        }
        else
        {
            /* Storing the received data */
            pos_shift                 = (uint64_t)ENDAT(pendat_base_addr_tbl[ch]).RECV1U.BIT.RXD1
                                               << ENDAT_32_SHIFT;
            endat_result[ch].data.pos = (uint64_t)(pos_shift + ENDAT(pendat_base_addr_tbl[ch]).RECV1L.BIT.RXD1);

            if (ENDAT_STATE_CONTINUE != endat_state[ch])
            {
                endat_result[ch].data.add_datum1 = ENDAT(pendat_base_addr_tbl[ch]).RECV3.BIT.RXD3 & ENDAT_MSB16_MASK;
                endat_result[ch].data.add_datum2 = ENDAT(pendat_base_addr_tbl[ch]).RECV2.BIT.RXD2 & ENDAT_MSB16_MASK;

                /* Check of status */
                if (ENDAT_STAT_WRN_BIT == (reg_val & ENDAT_STAT_WRN_BIT))
                {
                    endat_result[ch].status.wrn = true;
                }

                if (ENDAT_STAT_RM_BIT == (reg_val & ENDAT_STAT_RM_BIT))
                {
                    endat_result[ch].status.rm = true;
                }

                if (ENDAT_STAT_BUSY_BIT == (reg_val & ENDAT_STAT_BUSY_BIT))
                {
                    endat_result[ch].status.busy = true;
                }
            }
        }

        /* Call the R_ENDAT_ResultCb */
        if (NULL != pendat_isr_result_cb[ch])
        {
            pendat_isr_result_cb[ch](&endat_result[ch], &endat_err[ch]);
        }
    }

    if (ENDAT_STAT_RDSTC_BIT == (reg_val & ENDAT_STAT_RDSTC_BIT))
    {
        /* Call the R_ENDAT_RdstCb */
        if (NULL != pendat_isr_rdst_cb[ch])
        {
            pendat_isr_rdst_cb[ch]();
        }
        if (ENDAT_STATE_ELCTIMER != endat_state[ch])
        {
            endat_state[ch] = ENDAT_STATE_IDLE;
        }
    }

    /* Clear STAT register */
    ENDAT(pendat_base_addr_tbl[ch]).STAT.LONG = reg_val ^ ENDAT_STAT_XOR_CLR;

    /* Dummy read */
    reg_val = ENDAT(pendat_base_addr_tbl[ch]).STAT.LONG;

    return;
}
/*******************************************************************************
End of function endat_int_common
*******************************************************************************/

/*******************************************************************************
* Function Name: endat0_rx_int_isr
* Description  : Interrupt handler of EnDat.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void endat0_rx_int_isr(void)
{
    endat_int_common(ENDAT_CH0);

    __DMB();

    return;
}
/*******************************************************************************
 End of function endat0_rx_int_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: endat1_rx_int_isr
* Description  : Interrupt handler of EnDat.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void endat1_rx_int_isr(void)
{
    endat_int_common(ENDAT_CH1);

    __DMB();

    return;
}
/*******************************************************************************
 End of function endat1_rx_int_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: endat_fifo_int_common
* Description  : Interrupt common processing.
* Arguments    : ch - EnDat channel.
* Return Value : None.
*******************************************************************************/
static void endat_fifo_int_common(uint8_t ch)
{
    uint16_t i;
    
    if (R_ENDAT_POS == fifo_result[ch].mode_cmd)
    {
        for (i = 0; i < R_ENDAT_FIFO_POS_NORM; i++ )
        {
            fifo_result[ch].fdat[i] = ENDAT_FDAT_DR(ch).LONG;
        }
        for (i = R_ENDAT_FIFO_POS_NORM; i < R_ENDAT_FIFO_NORM; i++ )
        {
            fifo_result[ch].fdat[i] = 0;
        }
    }
    else
    {
        for (i = 0; i < R_ENDAT_FIFO_NORM; i++ )
        {
            fifo_result[ch].fdat[i] = ENDAT_FDAT_DR(ch).LONG;
        }
    }
    fifo_result[ch].rtcnt = ENDAT(pendat_base_addr_tbl[ch]).RTCNT.WORD;
    if (NULL != pendat_isr_fifodt_cb[ch])
    {
        pendat_isr_fifodt_cb[ch](&fifo_result[ch]);
    }
    return;
}
/*******************************************************************************
End of function endat_fifo_int_common
*******************************************************************************/

/*******************************************************************************
* Function Name: endat0_fifo_int_isr
* Description  : Interrupt handler of EnDat.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void endat0_fifo_int_isr(void)
{
    endat_fifo_int_common(ENDAT_CH0);

    __DMB();

    return;
}
/*******************************************************************************
 End of function endat0_fifo_int_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: endat1_fifo_int_isr
* Description  : Interrupt handler of EnDat.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void endat1_fifo_int_isr(void)
{
    endat_fifo_int_common(ENDAT_CH1);

    __DMB();

    return;
}
/*******************************************************************************
 End of function endat1_fifo_int_isr
*******************************************************************************/
