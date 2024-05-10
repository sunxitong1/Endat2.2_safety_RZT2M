/* generated vector source file - do not edit */
        #include "bsp_api.h"
        /* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
        #if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES] =
        {
                        [288] = sci_uart_eri_isr, /* SCI0_ERI (SCI0 Receive error) */
            [289] = sci_uart_rxi_isr, /* SCI0_RXI (SCI0 Receive data full) */
            [290] = sci_uart_txi_isr, /* SCI0_TXI (SCI0 Transmit data empty) */
            [291] = sci_uart_tei_isr, /* SCI0_TEI (SCI0 Transmit end) */
            [372] = endat0_rx_int_isr, /* ENCIF_INT0 (ENCIF CH0 Interrupt A) */
            [374] = endat0_fifo_int_isr, /* ENCIF_INT2 (ENCIF CH0 OUTPUT FIFO Interrupt) */
            [376] = endat1_rx_int_isr, /* ENCIF_INT4 (ENCIF CH1 Interrupt A) */
            [378] = endat1_fifo_int_isr, /* ENCIF_INT6 (ENCIF CH1 OUTPUT FIFO Interrupt) */
        };
        #endif