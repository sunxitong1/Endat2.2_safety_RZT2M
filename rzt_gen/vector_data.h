/* generated vector header file - do not edit */
        #ifndef VECTOR_DATA_H
        #define VECTOR_DATA_H
        #include "bsp_api.h"
                /* Number of interrupts allocated */
        #ifndef VECTOR_DATA_IRQ_COUNT
        #define VECTOR_DATA_IRQ_COUNT    (8)
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

        /* Vector table allocations */
        #define VECTOR_NUMBER_SCI0_ERI ((IRQn_Type) 288) /* SCI0_ERI (SCI0 Receive error) */
        #define VECTOR_NUMBER_SCI0_RXI ((IRQn_Type) 289) /* SCI0_RXI (SCI0 Receive data full) */
        #define VECTOR_NUMBER_SCI0_TXI ((IRQn_Type) 290) /* SCI0_TXI (SCI0 Transmit data empty) */
        #define VECTOR_NUMBER_SCI0_TEI ((IRQn_Type) 291) /* SCI0_TEI (SCI0 Transmit end) */
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
            SCI0_ERI_IRQn = 288, /* SCI0_ERI (SCI0 Receive error) */
            SCI0_RXI_IRQn = 289, /* SCI0_RXI (SCI0 Receive data full) */
            SCI0_TXI_IRQn = 290, /* SCI0_TXI (SCI0 Transmit data empty) */
            SCI0_TEI_IRQn = 291, /* SCI0_TEI (SCI0 Transmit end) */
            ENCIF_INT0_IRQn = 372, /* ENCIF_INT0 (ENCIF CH0 Interrupt A) */
            ENCIF_INT2_IRQn = 374, /* ENCIF_INT2 (ENCIF CH0 OUTPUT FIFO Interrupt) */
            ENCIF_INT4_IRQn = 376, /* ENCIF_INT4 (ENCIF CH1 Interrupt A) */
            ENCIF_INT6_IRQn = 378, /* ENCIF_INT6 (ENCIF CH1 OUTPUT FIFO Interrupt) */
            SHARED_PERIPHERAL_INTERRUPTS_MAX_ENTRIES = BSP_VECTOR_TABLE_MAX_ENTRIES
        } IRQn_Type;
        #endif /* VECTOR_DATA_H */