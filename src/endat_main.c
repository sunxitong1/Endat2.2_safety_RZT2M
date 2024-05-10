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
* System Name  : EnDat sample program
* File Name    : endat_main.c
* Version      :
* Device       : RZ
* Abstract     : Main processing source file for EnDat.
* Tool-Chain   : IAR Embedded Workbench for ARM
*                Renesas e2studio
* OS           : Not use
* H/W Platform : RZ/T2
* Description  : EnDat sample program on RZ devices.
* Limitation   : None
*******************************************************************************/
/*******************************************************************************
* History      : History is managed by Revision Control System.
*******************************************************************************/
/*******************************************************************************
Includes <System Includes> , "Project Includes"
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "bsp_api.h"
#include "hal_data.h"
#include "r_ecl_rzt2_if.h"
#include "iodefine_endat.h"
#include "r_endat_rzt2_if.h"
#include "r_endat_rzt2_dat.h"

#define BSP_DELAY_NS_PER_SECOND    (1000000)
#define BSP_DELAY_NS_PER_MS        (1000)
#define BSP_DELAY_NS_PER_US        (1)

/*******************************************************************************
Macro definitions
*******************************************************************************/
#define DEBUG_PRINT(...)            printf(__VA_ARGS__)
#define DEBUG_PRINT_END             "\n"        /* Line feed code */
#define PARAMETER_NOT_USED(p)       (void) ((p))

#define ARG_MAX                     (4)         /* maximum number of command arguments */
#define CMD_BUF_SIZE                (256)       /* command buffer size */
#define CMD_NUM                     (11)        /* number of commands */
#define EXIT_CMD_NUM                (10)        /* exit command number */
#define CMD_DELIMITER               (" \t\r\n") /* command line delimiter */
#define CMD_EXIT_ARG_NUM            (1)         /* "exit" command parameter */

#define ENDAT_FIFOE                 (1)         /* flag for activating FIFO read */

#define ENDAT_ENC_TSAT_WAIT         (1300u)     /* Waiting time after the power on reset */
#define ENDAT_ENC_100US_WAIT        (100u)      /* Wait 100us */
#define ENDAT_ENC_INIT_RESET_WAIT   (60u)       /* Wait 51ms */
#define ENDAT_ENC_INIT_MEM_WAIT     (743u)      /* Wait 743us */
#define ENDAT_ENC_INIT_PRAM_WAIT    (13u)       /* Wait 13ms */
#define ENDAT_ENC_INIT_CABLE_WAIT   (588u)      /* Wait 588us */
#define ENDAT_WDG_MAX               (127u)      /* Watchdog timer settings 25.4ms */
#define ENDAT_POS_NUM               (10u)       /* Store the number of position value */
#define ENDAT_ARG1                  (0)         /* First argument */
#define ENDAT_ARG2                  (1)         /* Second argument */
#define ENDAT_ARG3                  (2)         /* Third argument */
#define ENDAT_DEC                   (10)        /* Decimal number */
#define ENDAT_HEX                   (16)        /* Hexadecimal */
#define ENDAT_TEMP_SCA_FAC          (0.1)       /* Scaling function for temperature */
#define ENDAT_TEMP_ABS_ZERO         (273.2)     /* Absolute zero degrees Celsius */
#define ENDAT_SHIFT_16              (16)
#define ENDAT_SHIFT_32              (32)
#define ENDAT_MASK_LOW_16           (0xFFFFu)
#define ENDAT_MASK_LOW_32           (0xFFFFFFFFu)

#define CMT1_CMCOR_MAX_TO_US        (0xFFFF * 8 / 75) /* maximum time (us) to set CMCOR (PCLKD/8) */
#define PCLKMHZ                     (400u)

/*******************************************************************************
Typedef definitions
*******************************************************************************/
typedef char char_t;
typedef void (*cmd_func_t)(uint32_t arg_num, char_t *parg[]);

/*******************************************************************************
Imported global variables and functions (from other files)
*******************************************************************************/
extern uint8_t g_enc_config_dat[];
extern uint32_t g_pinmux_config[];

/*******************************************************************************
Exported global variables and functions (to be accessed by other files)
*******************************************************************************/

/*******************************************************************************
Private variables and functions
*******************************************************************************/
/* EnDat sample program */
static void endat_cmd_control(void);
static void endat_power_on_wait(void);
static void enc_init_reset_wait_callback(void);
static void enc_init_mem_wait_callback(void);
static void enc_init_pram_wait_callback(void);
static void enc_init_cable_wait_callback(void);
static void endat_pos(uint32_t arg_num, char_t *parg[]);
static void endat_poscon(uint32_t arg_num, char_t *parg[]);
static void endat_elctimer(uint32_t arg_num, char_t *parg[]);
static void endat_stop(uint32_t arg_num, char_t *parg[]);
static void endat_temp(uint32_t arg_num, char_t *parg[]);
static void endat_read(uint32_t arg_num, char_t *parg[]);
static void endat_write(uint32_t arg_num, char_t *parg[]);
static void endat_spos(uint32_t arg_num, char_t *parg[]);
static void endat_pos_safe(uint32_t arg_num, char_t *parg[]);
static void endat_sel_info(uint32_t arg_num, char_t *parg[]);
static void endat_callback(r_endat_result_t * presult, r_endat_protocol_err_t *perr);
static void endat_poscon_callback(r_endat_result_t * presult, r_endat_protocol_err_t *perr);
static void endat_fifodt_callback(r_endat_fifodt_t *pfdat);
static void endat_rdst_callback(void);
static void result_display(r_endat_result_t *presult, r_endat_protocol_err_t *perr);
static void result_display_param(r_endat_result_t *presult, r_endat_protocol_err_t *perr);
static void result_fifo_display(r_endat_result_t *presult);

/* for timer */
static void timer_start(uint32_t us);
static void timer_stop(void);

/* main function */
int32_t enc_main(uint8_t ch);

/* Terminal program */
static uint32_t get_cmd(char_t *parg[], const uint32_t arg_max);
static void cmd_exit(uint32_t arg_num, char_t *parg[]);

static const char_t *pcmd_tbl[CMD_NUM] =
{
    "pos", "poscon", "elctimer", "stop", "temp", "read", "write", "spos", "pos_safe", "sel_info", "exit"
};
static const cmd_func_t cmd_func_tbl[CMD_NUM] =
{
    &endat_pos, &endat_poscon, &endat_elctimer, &endat_stop, &endat_temp, &endat_read, &endat_write, &endat_spos,
    &endat_pos_safe, &endat_sel_info, &cmd_exit,
};

static volatile bool endat_flg;
static bool endat_elc_flg;
static r_endat_result_t *pendat_result;
static r_endat_protocol_err_t *pendat_err;
static r_endat_fifodt_t *pendat_result_fifo;
static r_endat_req_err_t poscon_err[ENDAT_POS_NUM];
static uint64_t poscon[ENDAT_POS_NUM];
static uint8_t poscon_valid;
static uint8_t poscon_num;
static bool poscon_empty;

static int32_t cur_id;

/*******************************************************************************
* Function Name: enc_main
* Description  : Main processing of EnDat sample program
* Arguments    : ch - channel of EnDat
* Return Value : Error code of Encoder IF
*******************************************************************************/
int32_t enc_main(uint8_t ch)
{
    uint8_t id;
    int32_t ret_code = 0;
    int32_t err_ecl_code;

    DEBUG_PRINT("EnDat Safety sample program start" DEBUG_PRINT_END);

    if(ch==0){
      id = R_ENDAT0_ID;
    }else if(ch==1){
      id = R_ENDAT1_ID;
    }else{
      goto end;
    }

    cur_id = id;
    
    /* Waiting time after power-on of the encoder */
    endat_power_on_wait();

    err_ecl_code = R_ECL_Initialize();
    if (R_ECL_SUCCESS != err_ecl_code)
    {
      DEBUG_PRINT("R_ECL_Init: error(%ld)" DEBUG_PRINT_END, err_ecl_code);
      goto end;
    }

    err_ecl_code = R_ECL_ConfigurePin(g_pinmux_config);
    if (R_ECL_SUCCESS != err_ecl_code)
    {
        DEBUG_PRINT("R_ECL_ConfigurePincfg: error(%ld)" DEBUG_PRINT_END, err_ecl_code);
        goto end;
    }

    /* Configuration of Encoder I/F EnDat */
    err_ecl_code = R_ECL_Configure(id, g_enc_config_dat);
    if (R_ECL_SUCCESS != err_ecl_code)
    {
        DEBUG_PRINT("R_ECL_Configure: error(%ld)" DEBUG_PRINT_END, err_ecl_code);
        ret_code = err_ecl_code;
        goto end;
    }

    /* Start of Encoder I/F EnDat */
    err_ecl_code = R_ECL_Start(id, R_ENDAT_FREQ);
    if (R_ECL_SUCCESS != err_ecl_code)
    {
        DEBUG_PRINT("R_ECL_Start: error(%ld)" DEBUG_PRINT_END, err_ecl_code);
        ret_code = err_ecl_code;
        goto end;
    }
    R_BSP_SoftwareDelay(ENDAT_ENC_100US_WAIT,BSP_DELAY_UNITS_MICROSECONDS);

    /* Enable IRQ interrupt */
    __enable_irq();
    __ISB();

    /* Control of EnDat */
    endat_cmd_control();

    err_ecl_code = R_ECL_Stop(id);
    if (R_ECL_SUCCESS != err_ecl_code)
    {
        DEBUG_PRINT("R_ECL_Stop: error(%ld)" DEBUG_PRINT_END, err_ecl_code);
        ret_code = (int32_t)err_ecl_code;
        goto end;
    }

end:
    DEBUG_PRINT("EnDat sample program end" DEBUG_PRINT_END);
    return ret_code;
}
/*******************************************************************************
 End of function enc_main
*******************************************************************************/

/*******************************************************************************
* Function Name: endat_cmd_control
* Description  : Control function of EnDat.
* Arguments    : None
* Return Value : None
*******************************************************************************/
static void endat_cmd_control(void)
{
    r_endat_err_t err_endat_code;
    r_endat_info_t endat_info;
    uint32_t arg_num;
    int32_t cmd_index = 0;
    char_t *parg[ARG_MAX];

    endat_info.ftclk                = R_ENDAT_FTCLK_8330;
    endat_info.filter               = true;
    endat_info.delay_comp           = true;
    endat_info.tst                  = R_ENDAT_TST_10US;
    endat_info.penc_init_reset_wait = &enc_init_reset_wait_callback;
    endat_info.penc_init_mem_wait   = &enc_init_mem_wait_callback;
    endat_info.penc_init_pram_wait  = &enc_init_pram_wait_callback;
    endat_info.penc_init_cable_wait = &enc_init_cable_wait_callback;
    err_endat_code = R_ENDAT_Open(cur_id, &endat_info);
    if (ENDAT_SUCCESS != err_endat_code)
    {
        DEBUG_PRINT("R_ENDAT_Open: error(%d)" DEBUG_PRINT_END, (int16_t)err_endat_code);
        goto endat_stop;
    }

    do
    {
        /* Get command token from the console I/O. */
        DEBUG_PRINT("endat >");
#ifdef __GNUC__
        fflush(stdout);
#endif
        arg_num = get_cmd(&parg[0], ARG_MAX);
        if (0 < arg_num)
        {
            /* Search for the command name. */
            for (cmd_index = 0; cmd_index < CMD_NUM; cmd_index++)
            {
                if (strncmp(parg[0], pcmd_tbl[cmd_index], strlen(pcmd_tbl[cmd_index]) + CMD_EXIT_ARG_NUM) == 0)
                {
                    break;
                }
            }

            if (CMD_NUM > cmd_index)
            {
                /* Call the function corresponding to the command. */
                cmd_func_tbl[cmd_index](arg_num, &parg[0]);
            }
            else
            {
                DEBUG_PRINT("unknown command" DEBUG_PRINT_END);
            }
        }
    } while ((EXIT_CMD_NUM != cmd_index) || (CMD_EXIT_ARG_NUM != arg_num));

    err_endat_code = R_ENDAT_Close(cur_id);
    if (R_ECL_SUCCESS != err_endat_code)
    {
        DEBUG_PRINT("R_ENDAT_Close: error(%d)" DEBUG_PRINT_END, (int)err_endat_code);
    }

endat_stop:
    return;
}
/*******************************************************************************
End of function endat_cmd_control
*******************************************************************************/

/*******************************************************************************
* Function Name: endat_power_on_wait
* Description  : Generate wait time after encoder power is turned on.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
static void endat_power_on_wait(void)
{
    /* 1.3s = 1ms * 1300 */
    R_BSP_SoftwareDelay(ENDAT_ENC_TSAT_WAIT,BSP_DELAY_UNITS_MILLISECONDS);

    return;
}
/*******************************************************************************
End of function endat_power_on_wait
*******************************************************************************/

/*******************************************************************************
* Function Name: enc_init_reset_wait_callback
* Description  : Encoder reset wait time.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
static void enc_init_reset_wait_callback(void)
{
    /* 60ms = 1ms * 60 */
    R_BSP_SoftwareDelay(ENDAT_ENC_INIT_RESET_WAIT,BSP_DELAY_UNITS_MILLISECONDS);

    return;
}
/*******************************************************************************
End of function enc_init_reset_wait_callback
*******************************************************************************/

/*******************************************************************************
* Function Name: enc_init_mem_wait_callback
* Description  : Memory selection wait time of encoder.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
static void enc_init_mem_wait_callback(void)
{
    /* 743us */
    R_BSP_SoftwareDelay(ENDAT_ENC_INIT_MEM_WAIT,BSP_DELAY_UNITS_MICROSECONDS);
    
    return;
}
/*******************************************************************************
End of function enc_init_mem_wait_callback
*******************************************************************************/

/*******************************************************************************
* Function Name: enc_init_pram_wait_callback
* Description  : Parameters receive wait time of encoder.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
static void enc_init_pram_wait_callback(void)
{
    /* 13ms */
    R_BSP_SoftwareDelay(ENDAT_ENC_INIT_PRAM_WAIT, BSP_DELAY_UNITS_MILLISECONDS);

    return;
}
/*******************************************************************************
End of function enc_init_pram_wait_callback
*******************************************************************************/

/*******************************************************************************
* Function Name: enc_init_cable_wait_callback
* Description  : Waiting time of cable propagation delay measurement.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
static void enc_init_cable_wait_callback(void)
{
    /* 588us */
    R_BSP_SoftwareDelay(ENDAT_ENC_INIT_CABLE_WAIT,BSP_DELAY_UNITS_MICROSECONDS);
    
    return;
}
/*******************************************************************************
End of function enc_init_cable_wait_callback
*******************************************************************************/

/*******************************************************************************
* Function Name: endat_pos
* Description  : "pos" command process.
* Arguments    : arg_num - Number of command arguments.
*                parg    - Command arguments.
* Return Value : None.
*******************************************************************************/
static void endat_pos(uint32_t arg_num, char_t *parg[])
{
    r_endat_req_t endat_req;
    r_endat_err_t err_code;

    PARAMETER_NOT_USED(arg_num);
    PARAMETER_NOT_USED(parg);

    endat_flg = false;

    DEBUG_PRINT("pos command" DEBUG_PRINT_END);

    endat_req.mode_cmd          = R_ENDAT_POS;
    endat_req.dt                = false;
    endat_req.watchdog.range    = R_ENDAT_WD_RANGE_US;
    endat_req.watchdog.time     = ENDAT_WDG_MAX;
    endat_req.elc               = false;
    endat_req.fifo_enable       = ENDAT_FIFOE;
    endat_req.rtcnt_enable      = false;
    endat_req.pisr_result       = &endat_callback;
    endat_req.pisr_fifodt       = &endat_fifodt_callback;
    endat_req.pisr_rdst         = &endat_rdst_callback;
    err_code = R_ENDAT_Control(cur_id, ENDAT_CMD_REQ, &endat_req);

    if (ENDAT_SUCCESS == err_code)
    {
        while (false == endat_flg)
        {
            ; // DO NOTHING 
        }
        endat_elc_flg = false;

        result_display(pendat_result, pendat_err);
        result_fifo_display(pendat_result);
    }
    else
    {
        DEBUG_PRINT("  R_ENDAT_Control(ENDAT_CMD_REQ) error: %d" DEBUG_PRINT_END, (int16_t)err_code);
    }

    return;
}
/*******************************************************************************
End of function endat_pos
*******************************************************************************/

/*******************************************************************************
* Function Name: endat_poscon
* Description  : "poscon" command process.
* Arguments    : arg_num - Number of command arguments.
*                parg    - Command arguments.
* Return Value : None.
*******************************************************************************/
static void endat_poscon(uint32_t arg_num, char_t *parg[])
{       
    r_endat_req_t endat_req;
    r_endat_err_t err_code;
    uint32_t loop;
    
    PARAMETER_NOT_USED(arg_num);
    PARAMETER_NOT_USED(parg);

    endat_flg = false;
    poscon_num = 0u;
    poscon_valid = 0u;
    poscon_empty = true;
    
    for (loop = 0; loop < ENDAT_POS_NUM; loop++)
    {
        poscon_err[loop] = ENDAT_REQ_SUCCESS;
        poscon[loop] =  0u;
    }

    DEBUG_PRINT("poscon command" DEBUG_PRINT_END);

    endat_req.mode_cmd          = R_ENDAT_POS;
    endat_req.dt                = true;
    endat_req.watchdog.range    = R_ENDAT_WD_RANGE_US;
    endat_req.watchdog.time     = 0u;
    endat_req.elc               = false;
    endat_req.fifo_enable       = false;
    endat_req.rtcnt_enable      = false;
    endat_req.pisr_result       = &endat_poscon_callback;
    endat_req.pisr_fifodt       = NULL;
    endat_req.pisr_rdst         = &endat_rdst_callback;
    err_code = R_ENDAT_Control(cur_id, ENDAT_CMD_REQ, &endat_req);

    if (ENDAT_SUCCESS != err_code)
    {
        DEBUG_PRINT("  R_ENDAT_Control(ENDAT_CMD_REQ) error: %d" DEBUG_PRINT_END, (int16_t)err_code);
    }
    else
    {
        endat_elc_flg = false;
    }

    return;
}
/*******************************************************************************
End of function endat_poscon
*******************************************************************************/

/*******************************************************************************
* Function Name: endat_elctimer
* Description  : "elctimer" command process.
* Arguments    : arg_num - Number of command arguments.
*                parg    - Command arguments.
* Return Value : None.
*******************************************************************************/
static void endat_elctimer(uint32_t arg_num, char_t *parg[])
{
    r_endat_req_t endat_req;
    r_endat_err_t err_code;
    uint32_t loop;
    char_t *perr_adr;
    uint32_t pram;
    
    /* check number of arguments */
    if (arg_num <= ENDAT_ARG2)
    {
        goto arg_err;
    }

    /* Check of the second argument */
    pram = (uint32_t)strtol(parg[ENDAT_ARG2], &perr_adr, ENDAT_DEC);
    if ((NULL != perr_adr) && ('\0' != (*perr_adr)))
    {
        goto arg_err;
    }
    else if ((CMT1_CMCOR_MAX_TO_US < pram) || (0u == pram))
    {
        goto arg_err;
    }
    else
    {
        /* Do nothing */
    }

    endat_flg = false;
    poscon_num = 0u;
    poscon_valid = 0u;
    poscon_empty = true;
    
    for (loop = 0; loop < ENDAT_POS_NUM; loop++)
    {
        poscon_err[loop] = ENDAT_REQ_SUCCESS;
        poscon[loop] =  0u;
    }

    DEBUG_PRINT("elctimer command" DEBUG_PRINT_END);

    endat_req.mode_cmd          = R_ENDAT_POS;
    endat_req.dt                = false;
    endat_req.watchdog.range    = R_ENDAT_WD_RANGE_US;
    endat_req.watchdog.time     = ENDAT_WDG_MAX;
    endat_req.elc               = true;
    endat_req.fifo_enable       = ENDAT_FIFOE;
    endat_req.rtcnt_enable      = false;
    endat_req.pisr_result       = &endat_poscon_callback;
    endat_req.pisr_fifodt       = &endat_fifodt_callback;
    endat_req.pisr_rdst         = &endat_rdst_callback;
    err_code = R_ENDAT_Control(cur_id, ENDAT_CMD_REQ, &endat_req);

    if (ENDAT_SUCCESS != err_code)
    {
        DEBUG_PRINT("  R_ENDAT_Control(ENDAT_CMD_REQ) error: %d" DEBUG_PRINT_END, (int16_t)err_code);
    }
    else
    {
        endat_elc_flg = true;

        timer_start(pram);

        DEBUG_PRINT(DEBUG_PRINT_END);
    }

    goto end;

arg_err:
    DEBUG_PRINT("Argument error" DEBUG_PRINT_END);
    goto end;

end:
    return;
}
/*******************************************************************************
End of function endat_elctimer
*******************************************************************************/

/*******************************************************************************
* Function Name: endat_stop
* Description  : "stop" command process.
* Arguments    : arg_num - Number of command arguments.
*                parg    - Command arguments.
* Return Value : None.
*******************************************************************************/
static void endat_stop(uint32_t arg_num, char_t *parg[])
{
    r_endat_err_t err_code;
    uint32_t pos_upper;
    uint32_t pos_lower;
    uint16_t loop;
    uint16_t loop_data;

    PARAMETER_NOT_USED(arg_num);
    PARAMETER_NOT_USED(parg);

    endat_flg = false;

    DEBUG_PRINT("stop command" DEBUG_PRINT_END);

    err_code = R_ENDAT_Control(cur_id, ENDAT_CMD_POS_STOP, NULL);

    if (false != endat_elc_flg)
    {
        timer_stop();
        endat_flg = true;
    }

    if (ENDAT_SUCCESS == err_code)
    {

        while (false == endat_flg)
        {
            ; /* DO NOTHING */
        }

        if(false != endat_elc_flg)
        {
            DEBUG_PRINT("  elctimer_valid : %d" DEBUG_PRINT_END, poscon_valid);
        }
        else
        {
            DEBUG_PRINT("  poscon_valid : %d" DEBUG_PRINT_END, poscon_valid);
        }

        loop_data = poscon_num;
        for (loop = 0; loop < poscon_valid; loop++)
        {
            DEBUG_PRINT("  %d ------------------------------ " DEBUG_PRINT_END, loop);

            if (ENDAT_REQ_SUCCESS == poscon_err[loop_data])
            {
                pos_upper = (uint32_t)(poscon[loop_data] >> ENDAT_SHIFT_32);
                pos_lower = (uint32_t)(poscon[loop_data] & ENDAT_MASK_LOW_32);
                DEBUG_PRINT("      result    : ENDAT_SUCCESS" DEBUG_PRINT_END);
                DEBUG_PRINT("      pos_upper : 0x%08lX" DEBUG_PRINT_END, pos_upper);
                DEBUG_PRINT("      pos_lower : 0x%08lX" DEBUG_PRINT_END, pos_lower);
            }
            else
            {
                DEBUG_PRINT("      result    : ENDAT_REQ_ERR" DEBUG_PRINT_END);
            }
            
            loop_data++;
            if (ENDAT_POS_NUM <= loop_data)
            {
                loop_data = 0;
            }
        }

    }
    else
    {
        DEBUG_PRINT("  R_ENDAT_Control(ENDAT_CMD_POS_STOP) error: %d" DEBUG_PRINT_END, (int16_t)err_code);
    }
    endat_elc_flg = false;

    return;
}
/*******************************************************************************
End of function endat_stop
*******************************************************************************/

/*******************************************************************************
* Function Name: endat_temp
* Description  : "temp" command process.
* Arguments    : arg_num - Number of command arguments.
*                parg    - Command arguments.
* Return Value : None.
*******************************************************************************/
static void endat_temp(uint32_t arg_num, char_t *parg[])
{

    r_endat_req_t endat_req;
    r_endat_err_t err_code = ENDAT_SUCCESS;
    float temp_celsius;

    PARAMETER_NOT_USED(arg_num);
    PARAMETER_NOT_USED(parg);

    endat_flg = false;

    DEBUG_PRINT("temp command" DEBUG_PRINT_END);

    endat_req.mode_cmd          = R_ENDAT_POS_MEM;
    endat_req.dt                = false;
    endat_req.mrs               = R_ENDAT_MRS_TEMP2;
    endat_req.watchdog.range    = R_ENDAT_WD_RANGE_US;
    endat_req.watchdog.time     = ENDAT_WDG_MAX;
    endat_req.elc               = false;
    endat_req.fifo_enable       = ENDAT_FIFOE;
    endat_req.rtcnt_enable      = false;
    endat_req.pisr_result       = &endat_callback;
    endat_req.pisr_fifodt       = &endat_fifodt_callback;
    endat_req.pisr_rdst         = &endat_rdst_callback;
    err_code = R_ENDAT_Control(cur_id, ENDAT_CMD_REQ, &endat_req);

    if (ENDAT_SUCCESS == err_code)
    {
        while (false == endat_flg)
        {
            ; /* DO NOTHING */
        }
    }
    else
    {
        goto temp_err;
    }

    endat_flg = false;

    endat_req.mode_cmd          = R_ENDAT_POS_ADD_DATA;
    endat_req.dt                = false;
    endat_req.watchdog.range    = R_ENDAT_WD_RANGE_US;
    endat_req.watchdog.time     = ENDAT_WDG_MAX;
    endat_req.elc               = false;
    endat_req.fifo_enable       = ENDAT_FIFOE;
    endat_req.rtcnt_enable      = false;
    endat_req.pisr_result       = &endat_callback;
    endat_req.pisr_fifodt       = &endat_fifodt_callback;
    endat_req.pisr_rdst         = &endat_rdst_callback;
    err_code = R_ENDAT_Control(cur_id, ENDAT_CMD_REQ, &endat_req);

    if (ENDAT_SUCCESS == err_code)
    {
        while (false == endat_flg)
        {
            ; /* DO NOTHING */
        }

        result_display(pendat_result, pendat_err);
        temp_celsius = (float)((pendat_result->data.add_datum1 * ENDAT_TEMP_SCA_FAC) - ENDAT_TEMP_ABS_ZERO);
        DEBUG_PRINT(" temperature : %d [deg C]" DEBUG_PRINT_END, (int16_t)temp_celsius);
        result_fifo_display(pendat_result);
    }
    else
    {
        goto temp_err;
    }

    goto end;

temp_err:
    DEBUG_PRINT("  R_ENDAT_Control(ENDAT_CMD_REQ) error: %d" DEBUG_PRINT_END, (int16_t)err_code);

end:
    return;
}
/*******************************************************************************
End of function endat_temp
*******************************************************************************/

/*******************************************************************************
* Function Name: endat_read
* Description  : "read" command process.
* Arguments    : arg_num - Number of command arguments.
*                parg    - Command arguments.
* Return Value : None.
*******************************************************************************/
static void endat_read(uint32_t arg_num, char_t *parg[])
{
    r_endat_req_t endat_req;
    r_endat_err_t err_code = ENDAT_SUCCESS;
    char_t *perr_adr;
    uint32_t addr;

    /* check number of arguments */
    if (arg_num <= ENDAT_ARG2)
    {
        goto arg_err;
    }

    /* Check of the second argument */
    addr = (uint32_t)strtol(parg[ENDAT_ARG2], &perr_adr, ENDAT_HEX);
    if ((NULL != perr_adr) && ('\0' != (*perr_adr)))
    {
        goto arg_err;
    }
    else if (0xff < addr)
    {
        goto arg_err;
    }
    else
    {
        /* Do nothing */
    }

    endat_flg = false;

    DEBUG_PRINT("read command" DEBUG_PRINT_END);

    endat_req.mode_cmd          = R_ENDAT_PARAM;
    endat_req.dt                = false;
    endat_req.addr              = (uint8_t)addr;
    endat_req.watchdog.range    = R_ENDAT_WD_RANGE_US;
    endat_req.watchdog.time     = 0u;
    endat_req.elc               = false;
    endat_req.fifo_enable       = false;
    endat_req.rtcnt_enable      = false;
    endat_req.pisr_result       = &endat_callback;
    endat_req.pisr_fifodt       = NULL;
    endat_req.pisr_rdst         = &endat_rdst_callback;
    err_code = R_ENDAT_Control(cur_id, ENDAT_CMD_REQ, &endat_req);

    if (ENDAT_SUCCESS == err_code)
    {
        while (false == endat_flg)
        {
            ; /* DO NOTHING */
        }
        result_display_param(pendat_result, pendat_err);
    }
    else
    {
        goto cmd_err;
    }
    goto end;

arg_err:
    DEBUG_PRINT("Argument error" DEBUG_PRINT_END);
    goto end;

cmd_err:
    DEBUG_PRINT("  R_ENDAT_Control(ENDAT_CMD_REQ) error: %d" DEBUG_PRINT_END, (int16_t)err_code);

end:
    return;
}
/*******************************************************************************
End of function endat_read
*******************************************************************************/

/*******************************************************************************
* Function Name: endat_write
* Description  : "write" command process.
* Arguments    : arg_num - Number of command arguments.
*                parg    - Command arguments.
* Return Value : None.
*******************************************************************************/
static void endat_write(uint32_t arg_num, char_t *parg[])
{
    r_endat_req_t endat_req;
    r_endat_err_t err_code = ENDAT_SUCCESS;
    char_t *perr_adr;
    uint32_t addr;
    uint32_t param;

    /* check number of arguments */
    if (arg_num <= ENDAT_ARG3)
    {
        goto arg_err;
    }

    /* Check of the second argument */
    addr = (uint32_t)strtol(parg[ENDAT_ARG2], &perr_adr, ENDAT_HEX);
    if ((NULL != perr_adr) && ('\0' != (*perr_adr)))
    {
        goto arg_err;
    }
    else if (0xff < addr)
    {
        goto arg_err;
    }
    else
    {
        /* Do nothing */
    }

    /* Check of the third argument */
    param = (uint32_t)strtol(parg[ENDAT_ARG3], &perr_adr, ENDAT_HEX);
    if ((NULL != perr_adr) && ('\0' != (*perr_adr)))
    {
        goto arg_err;
    }
    else if (0xffff < param)
    {
        goto arg_err;
    }
    else
    {
        /* Do nothing */
    }

    endat_flg = false;

    DEBUG_PRINT("write command" DEBUG_PRINT_END);

    endat_req.mode_cmd          = R_ENDAT_RX_PARAM;
    endat_req.dt                = false;
    endat_req.addr              = (uint8_t)addr;
    endat_req.param_instruction = (uint16_t)param;
    endat_req.watchdog.range    = R_ENDAT_WD_RANGE_US;
    endat_req.watchdog.time     = 0u;
    endat_req.elc               = false;
    endat_req.fifo_enable       = false;
    endat_req.rtcnt_enable      = false;
    endat_req.pisr_result       = &endat_callback;
    endat_req.pisr_fifodt       = NULL;
    endat_req.pisr_rdst         = &endat_rdst_callback;
    err_code = R_ENDAT_Control(cur_id, ENDAT_CMD_REQ, &endat_req);

    if (ENDAT_SUCCESS == err_code)
    {
        while (false == endat_flg)
        {
            ; /* DO NOTHING */
        }
        result_display_param(pendat_result, pendat_err);
    }
    else
    {
        goto cmd_err;
    }
    goto end;

arg_err:
    DEBUG_PRINT("Argument error" DEBUG_PRINT_END);
    goto end;

cmd_err:
    DEBUG_PRINT("  R_ENDAT_Control(ENDAT_CMD_REQ) error: %d" DEBUG_PRINT_END, (int16_t)err_code);

end:
    return;
}
/*******************************************************************************
End of function endat_write
*******************************************************************************/

/*******************************************************************************
* Function Name: endat_spos
* Description  : "spos" command process.
* Arguments    : arg_num - Number of command arguments.
*                parg    - Command arguments.
* Return Value : None.
*******************************************************************************/
static void endat_spos(uint32_t arg_num, char_t *parg[])
{
    r_endat_req_t endat_req;
    r_endat_err_t err_code = ENDAT_SUCCESS;
    uint8_t mrs_list[4] =
    {   R_ENDAT_MRS_POS2_LSB,
        R_ENDAT_MRS_POS2_CENTER,
        R_ENDAT_MRS_POS2_MSB,
        R_ENDAT_MRS_INFO1_NOP
    };
    uint16_t i;

    PARAMETER_NOT_USED(arg_num);
    PARAMETER_NOT_USED(parg);

    DEBUG_PRINT("spos command" DEBUG_PRINT_END);

    for (i = 0; i < 4; i++)
    {
        endat_flg = false;

        endat_req.mode_cmd          = R_ENDAT_POS_MEM;
        endat_req.dt                = false;
        endat_req.mrs               = mrs_list[i];
        endat_req.watchdog.range    = R_ENDAT_WD_RANGE_US;
        endat_req.watchdog.time     = ENDAT_WDG_MAX;
        endat_req.elc               = false;
        endat_req.fifo_enable       = ENDAT_FIFOE;
        endat_req.rtcnt_enable      = false;
        endat_req.pisr_result       = &endat_callback;
        endat_req.pisr_fifodt       = &endat_fifodt_callback;
        endat_req.pisr_rdst         = &endat_rdst_callback;
        err_code = R_ENDAT_Control(cur_id, ENDAT_CMD_REQ, &endat_req);

        if (ENDAT_SUCCESS == err_code)
        {
            while (false == endat_flg)
            {
                ; /* DO NOTHING */
            }
        }
        else
        {
            goto cmd_err;
        }

        endat_flg = false;

        endat_req.mode_cmd          = R_ENDAT_POS_ADD_DATA;
        endat_req.dt                = false;
        endat_req.watchdog.range    = R_ENDAT_WD_RANGE_US;
        endat_req.watchdog.time     = ENDAT_WDG_MAX;
        endat_req.elc               = false;
        endat_req.fifo_enable       = ENDAT_FIFOE;
        endat_req.rtcnt_enable      = (i == 0);
        endat_req.pisr_result       = &endat_callback;
        endat_req.pisr_fifodt       = &endat_fifodt_callback;
        endat_req.pisr_rdst         = &endat_rdst_callback;
        err_code = R_ENDAT_Control(cur_id, ENDAT_CMD_REQ, &endat_req);

        if (ENDAT_SUCCESS == err_code)
        {
            while (false == endat_flg)
            {
                ; /* DO NOTHING */
            }

            result_display(pendat_result, pendat_err);
            result_fifo_display(pendat_result);
        }
        else
        {
            goto cmd_err;
        }
    }

    goto end;

cmd_err:
    DEBUG_PRINT("  R_ENDAT_Control(ENDAT_CMD_REQ) error: %d" DEBUG_PRINT_END, (int16_t)err_code);

end:
    return;
}
/*******************************************************************************
End of function endat_spos
*******************************************************************************/

/*******************************************************************************
* Function Name: endat_pos_safe
* Description  : "pos_safe" command process.
* Arguments    : arg_num - Number of command arguments.
*                parg    - Command arguments.
* Return Value : None.
*******************************************************************************/
static void endat_pos_safe(uint32_t arg_num, char_t *parg[])
{
    r_endat_req_t endat_req;
    r_endat_err_t err_code = ENDAT_SUCCESS;

    PARAMETER_NOT_USED(arg_num);
    PARAMETER_NOT_USED(parg);

    endat_flg = false;

    DEBUG_PRINT("pos_safe command" DEBUG_PRINT_END);

    endat_req.mode_cmd          = R_ENDAT_POS_ADD_DATA;
    endat_req.dt                = false;
    endat_req.watchdog.range    = R_ENDAT_WD_RANGE_US;
    endat_req.watchdog.time     = ENDAT_WDG_MAX;
    endat_req.elc               = false;
    endat_req.fifo_enable       = ENDAT_FIFOE;
    endat_req.rtcnt_enable      = false;
    endat_req.pisr_result       = &endat_callback;
    endat_req.pisr_fifodt       = &endat_fifodt_callback;
    endat_req.pisr_rdst         = &endat_rdst_callback;
    err_code = R_ENDAT_Control(cur_id, ENDAT_CMD_REQ, &endat_req);

    if (ENDAT_SUCCESS == err_code)
    {
        while (false == endat_flg)
        {
            ; /* DO NOTHING */
        }

        result_display(pendat_result, pendat_err);
        result_fifo_display(pendat_result);
    }
    else
    {
        goto cmd_err;
    }

    goto end;

cmd_err:
    DEBUG_PRINT("  R_ENDAT_Control(ENDAT_CMD_REQ) error: %d" DEBUG_PRINT_END, (int16_t)err_code);

end:
    return;
}
/*******************************************************************************
End of function endat_pos_safe
*******************************************************************************/

/*******************************************************************************
* Function Name: endat_sel_info
* Description  : "sel_info" command process.
* Arguments    : arg_num - Number of command arguments.
*                parg    - Command arguments.
* Return Value : None.
*******************************************************************************/
static void endat_sel_info(uint32_t arg_num, char_t *parg[])
{
    r_endat_req_t endat_req;
    r_endat_err_t err_code = ENDAT_SUCCESS;
    char_t *perr_adr;
    uint32_t pram;
    uint8_t mrs;

    /* check number of arguments */
    if (arg_num <= ENDAT_ARG2)
    {
        goto arg_err;
    }

    /* Check of the second argument */
    pram = (uint32_t)strtol(parg[ENDAT_ARG2], &perr_adr, ENDAT_HEX);
    if ((NULL != perr_adr) && ('\0' != (*perr_adr)))
    {
        goto arg_err;
    }
    else
    {
        /* Do nothing */
    }

    endat_flg = false;

    DEBUG_PRINT("sel_info command" DEBUG_PRINT_END);

    mrs = (uint8_t)pram;

    endat_req.mode_cmd          = R_ENDAT_POS_MEM;
    endat_req.dt                = false;
    endat_req.mrs               = mrs;
    endat_req.watchdog.range    = R_ENDAT_WD_RANGE_US;
    endat_req.watchdog.time     = ENDAT_WDG_MAX;
    endat_req.elc               = false;
    endat_req.fifo_enable       = ENDAT_FIFOE;
    endat_req.rtcnt_enable      = false;
    endat_req.pisr_result       = &endat_callback;
    endat_req.pisr_fifodt       = &endat_fifodt_callback;
    endat_req.pisr_rdst         = &endat_rdst_callback;
    err_code = R_ENDAT_Control(cur_id, ENDAT_CMD_REQ, &endat_req);

    if (ENDAT_SUCCESS == err_code)
    {
        while (false == endat_flg)
        {
            ; /* DO NOTHING */
        }

        result_display(pendat_result, pendat_err);
    }
    else
    {
        goto cmd_err;
    }

    goto end;

cmd_err:
    DEBUG_PRINT("  R_ENDAT_Control(ENDAT_CMD_REQ) error: %d" DEBUG_PRINT_END, (int16_t)err_code);

arg_err:
    DEBUG_PRINT("Argument error" DEBUG_PRINT_END);
    goto end;

end:
    return;
}
/*******************************************************************************
End of function endat_sel_info
*******************************************************************************/

/*******************************************************************************
* Function Name: endat_callback
* Description  : Call back function for Endat.
* Arguments    : presult - Result of request for EnDat
*                perr    - Error information.
* Return Value : None.
*******************************************************************************/
static void endat_callback(r_endat_result_t * presult, r_endat_protocol_err_t *perr)
{
    pendat_result = presult;
    pendat_err = perr;

    if (false != pendat_err->modeerr)
    {
        endat_flg = true;
    }

    return;
}
/*******************************************************************************
End of function endat_callback
*******************************************************************************/

/*******************************************************************************
* Function Name: endat_poscon_callback
* Description  : Call back function for Endat.
* Arguments    : presult - Result of request for EnDat
*                perr    - Error information.
* Return Value : None.
*******************************************************************************/
static void endat_poscon_callback(r_endat_result_t * presult, r_endat_protocol_err_t *perr)
{
    PARAMETER_NOT_USED(perr);

    poscon_err[poscon_num] = presult->result;
    poscon[poscon_num] =  presult->data.pos;

    poscon_num++;

    if (false != poscon_empty)
    {
        poscon_valid++;
    }

    if (ENDAT_POS_NUM <= poscon_num)
    {
        poscon_num = 0u;
        poscon_empty = false;
    }

    return;

}
/*******************************************************************************
End of function endat_poscon_callback
*******************************************************************************/

/*******************************************************************************
* Function Name: endat_fifodt_callback
* Description  : Call back function for Endat.
* Arguments    : pfifodt - Result of request for EnDat
* Return Value : None.
*******************************************************************************/
static void endat_fifodt_callback(r_endat_fifodt_t * pfdat)
{
    pendat_result_fifo = pfdat;
    return;
}
/*******************************************************************************
End of function endat_fifodt_callback
*******************************************************************************/

/*******************************************************************************
* Function Name: endat_rdst_callback
* Description  : Call back function for Endat.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
static void endat_rdst_callback(void)
{
    endat_flg = true;

    return;
}
/*******************************************************************************
End of function endat_rdst_callback
*******************************************************************************/

/*******************************************************************************
* Function Name: get_cmd
* Description  : Get token of command line.
* Arguments    : parg    - Command arguments.
*                arg_max - Maximum number of command arguments.
* Return Value : Number of command arguments.
*******************************************************************************/
static uint32_t get_cmd(char_t *parg[], const uint32_t arg_max)
{
    uint32_t count = 0u;
    uint32_t loop = 0u;
    static char_t cmd_buf[CMD_BUF_SIZE];
    char_t *ptok;

    /* Read one line from the console. */
    while(1)
    {
        cmd_buf[loop] = (char)getchar();
        if (('\n' == (cmd_buf[loop])) || (loop >= (CMD_BUF_SIZE - 1)))
        {
            cmd_buf[loop] = '\0';
            break;
        }
        loop++;
    }

    /* Token of first. */
    ptok = strtok(&cmd_buf[0], CMD_DELIMITER);
    while ((NULL != ptok) && (count < arg_max))
    {
        parg[count] = ptok;

        /* Token of second and later. */
        ptok = strtok(NULL, CMD_DELIMITER);
        count++;
    }

    return count;
}
/*******************************************************************************
End of function get_cmd
*******************************************************************************/

/*******************************************************************************
* Function Name: cmd_exit
* Description  : "exit" command processing.
* Arguments    : arg_num - Number of command arguments.
*                parg    - Command arguments.
* Return Value : None.
*******************************************************************************/
static void cmd_exit(uint32_t arg_num, char_t *parg[])
{
    PARAMETER_NOT_USED(arg_num);
    PARAMETER_NOT_USED(parg);

    DEBUG_PRINT("exit command" DEBUG_PRINT_END);

    return;
}
/*******************************************************************************
End of function cmd_exit
*******************************************************************************/

/*******************************************************************************
* Function Name: result_display
* Description  : Result display function for Endat.
* Arguments    : presult - Result of request for EnDat
*                perr    - Error information.
* Return Value : None.
*******************************************************************************/
static void result_display(r_endat_result_t *presult, r_endat_protocol_err_t *perr)
{
    uint32_t pos_upper;
    uint32_t pos_lower;

    if (ENDAT_REQ_SUCCESS == presult->result)
    {
        pos_upper = (uint32_t)(presult->data.pos >> ENDAT_SHIFT_32);
        pos_lower = (uint32_t)(presult->data.pos & ENDAT_MASK_LOW_32);
        DEBUG_PRINT("  result     : ENDAT_SUCCESS" DEBUG_PRINT_END);
        DEBUG_PRINT("  pos_upper  : 0x%08lX" DEBUG_PRINT_END, pos_upper);
        DEBUG_PRINT("  pos_lower  : 0x%08lX" DEBUG_PRINT_END, pos_lower);
        DEBUG_PRINT("  add_datum1 : 0x%08lX" DEBUG_PRINT_END, presult->data.add_datum1);
        DEBUG_PRINT("  add_datum2 : 0x%08lX" DEBUG_PRINT_END, presult->data.add_datum2);

        if (false != presult->status.busy)
        {
            DEBUG_PRINT("  busy       : true " DEBUG_PRINT_END);
        }

        if (false != presult->status.rm)
        {
            DEBUG_PRINT("  rm         : true " DEBUG_PRINT_END);
        }

        if (false != presult->status.wrn)
        {
            DEBUG_PRINT("  wrn        : true " DEBUG_PRINT_END);
        }
    }
    else
    {
        DEBUG_PRINT("  result   : ENDAT_REQ_ERR   " DEBUG_PRINT_END);
        if (false != perr->err1)
        {
            DEBUG_PRINT("    err1   : true " DEBUG_PRINT_END);
        }

        if (false != perr->crc1)
        {
            DEBUG_PRINT("    crc1   : true " DEBUG_PRINT_END);
        }

        if (false != perr->ftype1)
        {
            DEBUG_PRINT("    ftype1 : true" DEBUG_PRINT_END);
        }

        if (false != perr->ftype2)
        {
            DEBUG_PRINT("    ftype2 : true" DEBUG_PRINT_END);
        }

        if (false != perr->err2)
        {
            DEBUG_PRINT("    err2   : true" DEBUG_PRINT_END);
        }

        if (false != perr->crc3)
        {
            DEBUG_PRINT("    crc3   : true" DEBUG_PRINT_END);
        }

        if (false != perr->crc2)
        {
            DEBUG_PRINT("    crc2   : true" DEBUG_PRINT_END);
        }

        if (false != perr->wdg)
        {
            DEBUG_PRINT("    wdg    : true" DEBUG_PRINT_END);
        }

        if (false != perr->ftype3)
        {
            DEBUG_PRINT("    ftype3 : true" DEBUG_PRINT_END);
        }

        if (false !=  perr->modeerr)
        {
            DEBUG_PRINT("    modeerr: true" DEBUG_PRINT_END);
        }

    }

    return;
}

/*******************************************************************************
End of function result_display
*******************************************************************************/

/*******************************************************************************
* Function Name: result_display_param
* Description  : Result display function for Endat parameter access.
* Arguments    : presult - Result of request for EnDat
*                perr    - Error information.
* Return Value : None.
*******************************************************************************/
static void result_display_param(r_endat_result_t *presult, r_endat_protocol_err_t *perr)
{
    uint8_t addr;
    uint16_t param;

    if (ENDAT_REQ_SUCCESS == presult->result)
    {
        addr  = (uint8_t)(presult->data.pos >> ENDAT_SHIFT_16);
        param = (uint16_t)(presult->data.pos & ENDAT_MASK_LOW_16);
        DEBUG_PRINT("  result     : ENDAT_SUCCESS" DEBUG_PRINT_END);
        DEBUG_PRINT("  addr       : 0x%02X" DEBUG_PRINT_END, addr);
        DEBUG_PRINT("  param      : 0x%04X" DEBUG_PRINT_END, param);

        if (false != presult->status.busy)
        {
            DEBUG_PRINT("  busy       : true " DEBUG_PRINT_END);
        }

        if (false != presult->status.rm)
        {
            DEBUG_PRINT("  rm         : true " DEBUG_PRINT_END);
        }

        if (false != presult->status.wrn)
        {
            DEBUG_PRINT("  wrn        : true " DEBUG_PRINT_END);
        }
    }
    else
    {
        DEBUG_PRINT("  result   : ENDAT_REQ_ERR   " DEBUG_PRINT_END);
        if (false != perr->err1)
        {
            DEBUG_PRINT("    err1   : true " DEBUG_PRINT_END);
        }

        if (false != perr->crc1)
        {
            DEBUG_PRINT("    crc1   : true " DEBUG_PRINT_END);
        }

        if (false != perr->ftype1)
        {
            DEBUG_PRINT("    ftype1 : true" DEBUG_PRINT_END);
        }

        if (false != perr->ftype2)
        {
            DEBUG_PRINT("    ftype2 : true" DEBUG_PRINT_END);
        }

        if (false != perr->err2)
        {
            DEBUG_PRINT("    err2   : true" DEBUG_PRINT_END);
        }

        if (false != perr->crc3)
        {
            DEBUG_PRINT("    crc3   : true" DEBUG_PRINT_END);
        }

        if (false != perr->crc2)
        {
            DEBUG_PRINT("    crc2   : true" DEBUG_PRINT_END);
        }

        if (false != perr->wdg)
        {
            DEBUG_PRINT("    wdg    : true" DEBUG_PRINT_END);
        }

        if (false != perr->ftype3)
        {
            DEBUG_PRINT("    ftype3 : true" DEBUG_PRINT_END);
        }

        if (false !=  perr->modeerr)
        {
            DEBUG_PRINT("    modeerr: true" DEBUG_PRINT_END);
        }

    }

    return;
}

/*******************************************************************************
End of function result_display_param
*******************************************************************************/

/*******************************************************************************
* Function Name: result_fifo_display
* Description  : Result display function for Endat.
* Arguments    : presult - Result of request for EnDat
* Return Value : None.
*******************************************************************************/
static void result_fifo_display(r_endat_result_t *presult)
{
    if (ENDAT_FIFOE != 0)
    {
        if (ENDAT_REQ_SUCCESS == presult->result)
        {
            if (R_ENDAT_POS == pendat_result_fifo->mode_cmd)
            {
                DEBUG_PRINT("    FDAT[31:0] 1st : %lx"DEBUG_PRINT_END, pendat_result_fifo->fdat[0]);
                DEBUG_PRINT("    FDAT[31:0] 2nd : %lx"DEBUG_PRINT_END, pendat_result_fifo->fdat[1]);
            }
            else
            {
                DEBUG_PRINT("    FDAT[31:0] 1st : %lx"DEBUG_PRINT_END, pendat_result_fifo->fdat[0]);
                DEBUG_PRINT("    FDAT[31:0] 2nd : %lx"DEBUG_PRINT_END, pendat_result_fifo->fdat[1]);
                DEBUG_PRINT("    FDAT[31:0] 3rd : %lx"DEBUG_PRINT_END, pendat_result_fifo->fdat[2]);
                DEBUG_PRINT("    FDAT[31:0] 4th : %lx"DEBUG_PRINT_END, pendat_result_fifo->fdat[3]);
            }
            DEBUG_PRINT("    RTCNT(pre)     : %x"DEBUG_PRINT_END, pendat_result_fifo->rtcnt_pre);
            DEBUG_PRINT("    RTCNT(post)    : %x"DEBUG_PRINT_END, pendat_result_fifo->rtcnt);
        }
    }

    return;
}

/*******************************************************************************
End of function result_fifo_display
*******************************************************************************/

/*******************************************************************************
* Function Name: timer_start
* Description  : Start timer.
* Arguments    : us - wait time (us).
* Return Value : None.
*******************************************************************************/
static void timer_start(uint32_t us)
{
    uint32_t count;
    
    if((0xFFFFFFFF / PCLKMHZ) < us){
      count = 0xFFFFFFFF;
    }else{
      count = us * PCLKMHZ; // set time [us]
    }
    
    R_GPT_PeriodSet(&g_timer0_ctrl, count);
    R_GPT_Start(&g_timer0_ctrl);

    return;
}
/*******************************************************************************
End of function timer_start
*******************************************************************************/

/*******************************************************************************
* Function Name: timer_stop
* Description  : Stop timer.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
static void timer_stop(void)
{
    R_GPT_Stop(&g_timer0_ctrl);

    return;
}
/*******************************************************************************
End of function timer_stop
*******************************************************************************/
