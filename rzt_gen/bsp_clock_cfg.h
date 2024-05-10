/* generated configuration header file - do not edit */
#ifndef BSP_CLOCK_CFG_H_
#define BSP_CLOCK_CFG_H_
#define BSP_CFG_CLOCKS_SECURE (0)
#define BSP_CFG_CLOCKS_OVERRIDE (0)
#define BSP_CFG_MAIN_CLOCK_HZ (25000000) /* Main Clock: 25MHz */
#define BSP_CFG_LOCO_ENABLE (BSP_CLOCKS_LOCO_ENABLE) /* LOCO Enabled */
#define BSP_CFG_PLL1 (BSP_CLOCKS_PLL1_INITIAL) /* PLL1 is initial state */
#define BSP_CFG_PHYSEL (BSP_CLOCKS_PHYSEL_PLL1_DIV) /* Ethernet Clock src: PLL1 divider clock */
#define BSP_CFG_CLMA0_ENABLE (BSP_CLOCKS_CLMA0_ENABLE) /* CLMA0 Enabled */
#define BSP_CFG_CLMA0MASK (BSP_CLOCKS_CLMA0_ERROR_NOT_MASK) /* CLMA0 error not mask */
#define BSP_CFG_CLMA3MASK (BSP_CLOCKS_CLMA3_ERROR_NOT_MASK) /* CLMA3 error not mask */
#define BSP_CFG_CLMA1MASK (BSP_CLOCKS_CLMA1_ERROR_MASK) /* CLMA1 error mask */
#define BSP_CFG_CLMA3_ENABLE (BSP_CLOCKS_CLMA3_ENABLE) /* CLMA3 Enabled */
#define BSP_CFG_CLMA1_ENABLE (BSP_CLOCKS_CLMA1_ENABLE) /* CLMA1 Enabled */
#define BSP_CFG_CLMA2_ENABLE (BSP_CLOCKS_CLMA2_ENABLE) /* CLMA2 Enabled */
#define BSP_CFG_CLMA0_CMPL (1) /* CLMA0 CMPL 1 */
#define BSP_CFG_CLMA1_CMPL (1) /* CLMA1 CMPL 1 */
#define BSP_CFG_CLMA2_CMPL (1) /* CLMA2 CMPL 1 */
#define BSP_CFG_CLMA3_CMPL (1) /* CLMA3 CMPL 1 */
#define BSP_CFG_CLMASEL (BSP_CLOCKS_CLMASEL_LOCO) /* Alternative clock: LOCO */
#define BSP_CFG_CLMA0_CMPH (1023) /* CLMA0 CMPH 1023 */
#define BSP_CFG_CLMA1_CMPH (1023) /* CLMA1 CMPH 1023 */
#define BSP_CFG_CLMA2_CMPH (1023) /* CLMA2 CMPH 1023 */
#define BSP_CFG_CLMA3_CMPH (1023) /* CLMA3 CMPH 1023 */
#define BSP_CFG_DIVSELSUB (BSP_CLOCKS_DIVSELSUB_0) /* ICLK 200MHz */
#define BSP_CFG_SCI0ASYNCCLK (BSP_CLOCKS_SCI0_ASYNCHRONOUS_SERIAL_CLOCK_96_MHZ) /* SCI0ASYNCCLK: 96MHz */
#define BSP_CFG_SCI1ASYNCCLK (BSP_CLOCKS_SCI1_ASYNCHRONOUS_SERIAL_CLOCK_96_MHZ) /* SCI1ASYNCCLK: 96MHz */
#define BSP_CFG_SCI2ASYNCCLK (BSP_CLOCKS_SCI2_ASYNCHRONOUS_SERIAL_CLOCK_96_MHZ) /* SCI2ASYNCCLK: 96MHz */
#define BSP_CFG_SCI3ASYNCCLK (BSP_CLOCKS_SCI3_ASYNCHRONOUS_SERIAL_CLOCK_96_MHZ) /* SCI3ASYNCCLK: 96MHz */
#define BSP_CFG_SCI4ASYNCCLK (BSP_CLOCKS_SCI4_ASYNCHRONOUS_SERIAL_CLOCK_96_MHZ) /* SCI4ASYNCCLK: 96MHz */
#define BSP_CFG_SCI5ASYNCCLK (BSP_CLOCKS_SCI5_ASYNCHRONOUS_SERIAL_CLOCK_96_MHZ) /* SCI5ASYNCCLK: 96MHz */
#define BSP_CFG_SPI0ASYNCCLK (BSP_CLOCKS_SPI0_ASYNCHRONOUS_SERIAL_CLOCK_96_MHZ) /* SPI0ASYNCCLK: 96MHz */
#define BSP_CFG_SPI1ASYNCCLK (BSP_CLOCKS_SPI1_ASYNCHRONOUS_SERIAL_CLOCK_96_MHZ) /* SPI1ASYNCCLK: 96MHz */
#define BSP_CFG_SPI2ASYNCCLK (BSP_CLOCKS_SPI2_ASYNCHRONOUS_SERIAL_CLOCK_96_MHZ) /* SPI2ASYNCCLK: 96MHz */
#define BSP_CFG_SPI3ASYNCCLK (BSP_CLOCKS_SPI3_ASYNCHRONOUS_SERIAL_CLOCK_96_MHZ) /* SPI3ASYNCCLK: 96MHz */
#define BSP_CFG_FSELCPU0 (BSP_CLOCKS_FSELCPU0_ICLK_MUL4) /* CPU0CLK Mul x4 */
#define BSP_CFG_FSELCPU1 (BSP_CLOCKS_FSELCPU1_ICLK_MUL4) /* CPU1CLK Mul: x4 */
#define BSP_CFG_CKIO (BSP_CLOCKS_CKIO_ICLK_DIV4) /* CKIO Div /4 */
#define BSP_CFG_FSELCANFD (BSP_CLOCKS_CANFD_CLOCK_40_MHZ) /* PCLKCAN 40MHz */
#define BSP_CFG_FSELXSPI0_DIVSELXSPI0 (BSP_CLOCKS_XSPI0_CLOCK_DIV0_12_5_MHZ) /* XSPI_CLK0 12.5MHz */
#define BSP_CFG_FSELXSPI1_DIVSELXSPI1 (BSP_CLOCKS_XSPI1_CLOCK_DIV0_12_5_MHZ) /* XSPI_CLK1 12.5MHz */
#endif /* BSP_CLOCK_CFG_H_ */
