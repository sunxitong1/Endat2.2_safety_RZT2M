/* generated vector header file - do not edit */
        #ifndef VECTOR_DATA_H
        #define VECTOR_DATA_H
        #include "bsp_api.h"
                /* Number of interrupts allocated */
        #ifndef VECTOR_DATA_IRQ_COUNT
        #define VECTOR_DATA_IRQ_COUNT    (10)
        #endif
        /* ISR prototypes */
        void sci_uart_eri_isr(void);
        void sci_uart_rxi_isr(void);
        void sci_uart_txi_isr(void);
        void sci_uart_tei_isr(void);
        void endat0_rx_int_isr(void);
        void endat0_fifo_int_isr(void);
        void endat1_rx_int_isr(void);
        void endat1_fifo_int_isr(void);
       	void adc_scan_end_isr(void);

        /* Vector table allocations */
        #define VECTOR_NUMBER_SCI4_ERI ((IRQn_Type) 304) /* SCI4_ERI (SCI4 Receive error) */
        #define VECTOR_NUMBER_SCI4_RXI ((IRQn_Type) 305) /* SCI4_RXI (SCI4 Receive data full) */
        #define VECTOR_NUMBER_SCI4_TXI ((IRQn_Type) 306) /* SCI4_TXI (SCI4 Transmit data empty) */
        #define VECTOR_NUMBER_SCI4_TEI ((IRQn_Type) 307) /* SCI4_TEI (SCI4 Transmit end) */

        #define VECTOR_NUMBER_ADC0_ADI ((IRQn_Type) 345) /* ADC0 A/D scan end interrupt */
        #define VECTOR_NUMBER_ADC0_GBADI ((IRQn_Type) 346) /* ADC0 A/D scan end interrupt */
        
        #define VECTOR_NUMBER_ENCIF_INT0 ((IRQn_Type) 372) /* ENCIF_INT0 (ENCIF CH0 Interrupt A) */
        #define VECTOR_NUMBER_ENCIF_INT2 ((IRQn_Type) 374) /* ENCIF_INT2 (ENCIF CH0 OUTPUT FIFO Interrupt) */
        #define VECTOR_NUMBER_ENCIF_INT4 ((IRQn_Type) 376) /* ENCIF_INT4 (ENCIF CH1 Interrupt A) */
        #define VECTOR_NUMBER_ENCIF_INT6 ((IRQn_Type) 378) /* ENCIF_INT6 (ENCIF CH1 OUTPUT FIFO Interrupt) */

        
        typedef enum IRQn {
            SoftwareGeneratedInt0 = -32,
            SoftwareGeneratedInt1 = -31,
            SoftwareGeneratedInt2 = -30,
            SoftwareGeneratedInt3 = -29,
            SoftwareGeneratedInt4 = -28,
            SoftwareGeneratedInt5 = -27,
            SoftwareGeneratedInt6 = -26,
            SoftwareGeneratedInt7 = -25,
            SoftwareGeneratedInt8 = -24,
            SoftwareGeneratedInt9 = -23,
            SoftwareGeneratedInt10 = -22,
            SoftwareGeneratedInt11 = -21,
            SoftwareGeneratedInt12 = -20,
            SoftwareGeneratedInt13 = -19,
            SoftwareGeneratedInt14 = -18,
            SoftwareGeneratedInt15 = -17,
            DebugCommunicationsChannelInt = -10,
            PerformanceMonitorCounterOverflowInt = -9,
            CrossTriggerInterfaceInt = -8,
            VritualCPUInterfaceMaintenanceInt = -7,
            HypervisorTimerInt = -6,
            VirtualTimerInt = -5,
            NonSecurePhysicalTimerInt = -2,
            SCI4_ERI_IRQn = 304, /* SCI4_ERI (SCI4 Receive error) */
            SCI4_RXI_IRQn = 305, /* SCI4_RXI (SCI4 Receive data full) */
            SCI4_TXI_IRQn = 306, /* SCI4_TXI (SCI4 Transmit data empty) */
            SCI4_TEI_IRQn = 307, /* SCI4_TEI (SCI4 Transmit end) */
            ADC0_ADI_IRQn = 345,
            ADC0_GBADI_IRQn = 346,
            ENCIF_INT0_IRQn = 372, /* ENCIF_INT0 (ENCIF CH0 Interrupt A) */
            ENCIF_INT2_IRQn = 374, /* ENCIF_INT2 (ENCIF CH0 OUTPUT FIFO Interrupt) */
            ENCIF_INT4_IRQn = 376, /* ENCIF_INT4 (ENCIF CH1 Interrupt A) */
            ENCIF_INT6_IRQn = 378, /* ENCIF_INT6 (ENCIF CH1 OUTPUT FIFO Interrupt) */
            SHARED_PERIPHERAL_INTERRUPTS_MAX_ENTRIES = BSP_VECTOR_TABLE_MAX_ENTRIES
        } IRQn_Type;
        #endif /* VECTOR_DATA_H */