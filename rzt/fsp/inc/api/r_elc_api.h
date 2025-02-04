/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics Corporation and/or its affiliates and may only
 * be used with products of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.
 * Renesas products are sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for
 * the selection and use of Renesas products and Renesas assumes no liability.  No license, express or implied, to any
 * intellectual property right is granted by Renesas.  This software is protected under all applicable laws, including
 * copyright laws. Renesas reserves the right to change or discontinue this software and/or this documentation.
 * THE SOFTWARE AND DOCUMENTATION IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND
 * TO THE FULLEST EXTENT PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY,
 * INCLUDING WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE
 * SOFTWARE OR DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR
 * DOCUMENTATION (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER,
 * INCLUDING, WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY
 * LOST PROFITS, OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_INTERFACES
 * @defgroup ELC_API ELC Interface
 * @brief Interface for the Event Link Controller.
 *
 *
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_ELC_API_H
#define R_ELC_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define ELC_API_VERSION_MAJOR    (1U)  // DEPRECATED
#define ELC_API_VERSION_MINOR    (3U)  // DEPRECATED

#if (1 == BSP_FEATURE_ELC_PERIPHERAL_TYPE)
 #define ELC_PERIPHERAL_NUM      (55U)
#elif (2 == BSP_FEATURE_ELC_PERIPHERAL_TYPE)
 #define ELC_PERIPHERAL_NUM      (56U)
#endif

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
#if (1 == BSP_FEATURE_ELC_PERIPHERAL_TYPE)

/** Possible peripherals to be linked to event signals (not all available on all MCUs) */
typedef enum e_elc_peripheral
{
    ELC_PERIPHERAL_MTU0          = (0),
    ELC_PERIPHERAL_MTU3          = (1),
    ELC_PERIPHERAL_MTU4          = (2),
    ELC_PERIPHERAL_LLPPGPT_A     = (3),
    ELC_PERIPHERAL_LLPPGPT_B     = (4),
    ELC_PERIPHERAL_LLPPGPT_C     = (5),
    ELC_PERIPHERAL_LLPPGPT_D     = (6),
    ELC_PERIPHERAL_LLPPGPT_E     = (7),
    ELC_PERIPHERAL_LLPPGPT_F     = (8),
    ELC_PERIPHERAL_LLPPGPT_G     = (9),
    ELC_PERIPHERAL_LLPPGPT_H     = (10),
    ELC_PERIPHERAL_NONSAFTYGPT_A = (11),
    ELC_PERIPHERAL_NONSAFTYGPT_B = (12),
    ELC_PERIPHERAL_NONSAFTYGPT_C = (13),
    ELC_PERIPHERAL_NONSAFTYGPT_D = (14),
    ELC_PERIPHERAL_NONSAFTYGPT_E = (15),
    ELC_PERIPHERAL_NONSAFTYGPT_F = (16),
    ELC_PERIPHERAL_NONSAFTYGPT_G = (17),
    ELC_PERIPHERAL_NONSAFTYGPT_H = (18),
    ELC_PERIPHERAL_ADC0_A        = (19),
    ELC_PERIPHERAL_ADC0_B        = (20),
    ELC_PERIPHERAL_ADC1_A        = (21),
    ELC_PERIPHERAL_ADC1_B        = (22),
    ELC_PERIPHERAL_DSMIF0_CAP0   = (23),
    ELC_PERIPHERAL_DSMIF0_CAP1   = (24),
    ELC_PERIPHERAL_DSMIF0_CAP2   = (25),
    ELC_PERIPHERAL_DSMIF0_CAP3   = (26),
    ELC_PERIPHERAL_DSMIF0_CAP4   = (27),
    ELC_PERIPHERAL_DSMIF0_CAP5   = (28),
    ELC_PERIPHERAL_DSMIF0_CDCNT0 = (29),
    ELC_PERIPHERAL_DSMIF0_CDCNT1 = (30),
    ELC_PERIPHERAL_DSMIF0_CDCNT2 = (31),
    ELC_PERIPHERAL_DSMIF1_CAP0   = (32),
    ELC_PERIPHERAL_DSMIF1_CAP1   = (33),
    ELC_PERIPHERAL_DSMIF1_CAP2   = (34),
    ELC_PERIPHERAL_DSMIF1_CAP3   = (35),
    ELC_PERIPHERAL_DSMIF1_CAP4   = (36),
    ELC_PERIPHERAL_DSMIF1_CAP5   = (37),
    ELC_PERIPHERAL_DSMIF1_CDCNT0 = (38),
    ELC_PERIPHERAL_DSMIF1_CDCNT1 = (39),
    ELC_PERIPHERAL_DSMIF1_CDCNT2 = (40),
    ELC_PERIPHERAL_ENCIF_TRG0    = (41),
    ELC_PERIPHERAL_ENCIF_TRG1    = (42),
    ELC_PERIPHERAL_ESC0          = (43),
    ELC_PERIPHERAL_ESC1          = (44),
    ELC_PERIPHERAL_GMA0          = (45),
    ELC_PERIPHERAL_GMA1          = (46),
    ELC_PERIPHERAL_OUTPORTGR1    = (47),
    ELC_PERIPHERAL_OUTPORTGR2    = (48),
    ELC_PERIPHERAL_INPORTGR1     = (49),
    ELC_PERIPHERAL_INPORTGR2     = (50),
    ELC_PERIPHERAL_SINGLEPORT0   = (51),
    ELC_PERIPHERAL_SINGLEPORT1   = (52),
    ELC_PERIPHERAL_SINGLEPORT2   = (53),
    ELC_PERIPHERAL_SINGLEPORT3   = (54),
} elc_peripheral_t;
#elif (2 == BSP_FEATURE_ELC_PERIPHERAL_TYPE)
typedef enum e_elc_peripheral
{
    ELC_PERIPHERAL_MTU0           = (0),
    ELC_PERIPHERAL_MTU3           = (1),
    ELC_PERIPHERAL_MTU4           = (2),
    ELC_PERIPHERAL_LLPPGPT_A      = (3),
    ELC_PERIPHERAL_LLPPGPT_B      = (4),
    ELC_PERIPHERAL_LLPPGPT_C      = (5),
    ELC_PERIPHERAL_LLPPGPT_D      = (6),
    ELC_PERIPHERAL_LLPPGPT_E      = (7),
    ELC_PERIPHERAL_LLPPGPT_F      = (8),
    ELC_PERIPHERAL_LLPPGPT_G      = (9),
    ELC_PERIPHERAL_LLPPGPT_H      = (10),
    ELC_PERIPHERAL_NONSAFTYGPT_A  = (11),
    ELC_PERIPHERAL_NONSAFTYGPT_B  = (12),
    ELC_PERIPHERAL_NONSAFTYGPT_C  = (13),
    ELC_PERIPHERAL_NONSAFTYGPT_D  = (14),
    ELC_PERIPHERAL_NONSAFTYGPT_E  = (15),
    ELC_PERIPHERAL_NONSAFTYGPT_F  = (16),
    ELC_PERIPHERAL_NONSAFTYGPT_G  = (17),
    ELC_PERIPHERAL_NONSAFTYGPT_H  = (18),
    ELC_PERIPHERAL_ADC0_A         = (19),
    ELC_PERIPHERAL_ADC0_B         = (20),
    ELC_PERIPHERAL_ADC1_A         = (21),
    ELC_PERIPHERAL_ADC1_B         = (22),
    ELC_PERIPHERAL_DSMIF0_CAP0    = (23),
    ELC_PERIPHERAL_DSMIF0_CAP1    = (24),
    ELC_PERIPHERAL_DSMIF0_CAP2    = (25),
    ELC_PERIPHERAL_DSMIF0_CAP3    = (26),
    ELC_PERIPHERAL_DSMIF0_CAP4    = (27),
    ELC_PERIPHERAL_DSMIF0_CAP5    = (28),
    ELC_PERIPHERAL_DSMIF0_CDCNT0  = (29),
    ELC_PERIPHERAL_DSMIF0_CDCNT1  = (30),
    ELC_PERIPHERAL_DSMIF0_CDCNT2  = (31),
    ELC_PERIPHERAL_DSMIF1_CAP0    = (32),
    ELC_PERIPHERAL_DSMIF1_CAP1    = (33),
    ELC_PERIPHERAL_DSMIF1_CAP2    = (34),
    ELC_PERIPHERAL_DSMIF1_CAP3    = (35),
    ELC_PERIPHERAL_DSMIF1_CAP4    = (36),
    ELC_PERIPHERAL_DSMIF1_CAP5    = (37),
    ELC_PERIPHERAL_DSMIF1_CDCNT0  = (38),
    ELC_PERIPHERAL_DSMIF1_CDCNT1  = (39),
    ELC_PERIPHERAL_DSMIF1_CDCNT2  = (40),
    ELC_PERIPHERAL_ENCIF_TRG0     = (41),
    ELC_PERIPHERAL_ENCIF_TRG1     = (42),
    ELC_PERIPHERAL_ESC0           = (43),
    ELC_PERIPHERAL_ESC1           = (44),
    ELC_PERIPHERAL_GMA0           = (45),
    ELC_PERIPHERAL_GMA1           = (46),
    ELC_PERIPHERAL_OUTPORTGR1     = (47),
    ELC_PERIPHERAL_OUTPORTGR2     = (48),
    ELC_PERIPHERAL_INPORTGR1      = (49),
    ELC_PERIPHERAL_INPORTGR2      = (50),
    ELC_PERIPHERAL_SINGLEPORT0    = (51),
    ELC_PERIPHERAL_SINGLEPORT1    = (52),
    ELC_PERIPHERAL_SINGLEPORT2    = (53),
    ELC_PERIPHERAL_SINGLEPORT3    = (54),
    ELC_PERIPHERAL_ENCOUT_TRIGGER = (55),
} elc_peripheral_t;
#endif

/** ELC control block.  Allocate an instance specific control block to pass into the ELC API calls.
 * @par Implemented as
 * - elc_instance_ctrl_t
 */
typedef void elc_ctrl_t;

/** Main configuration structure for the Event Link Controller */
typedef struct st_elc_cfg
{
    elc_event_t const link[ELC_PERIPHERAL_NUM]; ///< Event link register (ELC_SSEL) settings
} elc_cfg_t;

/** Software event number */
typedef enum e_elc_software_event
{
    ELC_SOFTWARE_EVENT_0,              ///< Software event 0
    ELC_SOFTWARE_EVENT_1,              ///< Software event 1
} elc_software_event_t;

/** ELC driver structure. General ELC functions implemented at the HAL layer follow this API. */
typedef struct st_elc_api
{
    /** Initialize all links in the Event Link Controller.
     * @par Implemented as
     * - @ref R_ELC_Open()
     *
     * @param[in]   p_ctrl  Pointer to control structure.
     * @param[in]   p_cfg   Pointer to configuration structure.
     **/
    fsp_err_t (* open)(elc_ctrl_t * const p_ctrl, elc_cfg_t const * const p_cfg);

    /** Disable all links in the Event Link Controller and close the API.
     * @par Implemented as
     * - @ref R_ELC_Close()
     *
     * @param[in]   p_ctrl  Pointer to control structure.
     **/
    fsp_err_t (* close)(elc_ctrl_t * const p_ctrl);

    /** Generate a software event in the Event Link Controller.
     * @par Implemented as
     * - @ref R_ELC_SoftwareEventGenerate()
     *
     * @param[in]   p_ctrl  Pointer to control structure.
     * @param[in]   eventNum           Software event number to be generated.
     **/
    fsp_err_t (* softwareEventGenerate)(elc_ctrl_t * const p_ctrl, elc_software_event_t event_num);

    /** Create a single event link.
     * @par Implemented as
     * - @ref R_ELC_LinkSet()
     *
     * @param[in]   p_ctrl  Pointer to control structure.
     * @param[in]   peripheral The peripheral block that will receive the event signal.
     * @param[in]   signal     The event signal.
     **/
    fsp_err_t (* linkSet)(elc_ctrl_t * const p_ctrl, elc_peripheral_t peripheral, elc_event_t signal);

    /** Break an event link.
     * @par Implemented as
     * - @ref R_ELC_LinkBreak()
     *
     * @param[in]   p_ctrl  Pointer to control structure.
     * @param[in]   peripheral   The peripheral that should no longer be linked.
     **/
    fsp_err_t (* linkBreak)(elc_ctrl_t * const p_ctrl, elc_peripheral_t peripheral);

    /** Enable the operation of the Event Link Controller.
     * @par Implemented as
     * - @ref R_ELC_Enable()
     *
     * @param[in]   p_ctrl  Pointer to control structure.
     **/
    fsp_err_t (* enable)(elc_ctrl_t * const p_ctrl);

    /** Disable the operation of the Event Link Controller.
     * @par Implemented as
     * - @ref R_ELC_Disable()
     *
     * @param[in]   p_ctrl  Pointer to control structure.
     **/
    fsp_err_t (* disable)(elc_ctrl_t * const p_ctrl);

    /** DEPRECATED Get the driver version based on compile time macros.
     * @par Implemented as
     * - @ref R_ELC_VersionGet()
     *
     * @param[in]   p_ctrl  Pointer to control structure.
     * @param[out]  p_version is value returned.
     **/
    fsp_err_t (* versionGet)(fsp_version_t * const p_version);
} elc_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_elc_instance
{
    elc_ctrl_t      * p_ctrl;          ///< Pointer to the control structure for this instance
    elc_cfg_t const * p_cfg;           ///< Pointer to the configuration structure for this instance
    elc_api_t const * p_api;           ///< Pointer to the API structure for this instance
} elc_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end addtogroup ELC_API)
 **********************************************************************************************************************/
