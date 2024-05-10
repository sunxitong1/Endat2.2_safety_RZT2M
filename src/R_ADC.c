
/********************************************************************************************************************/
/*********************************************************************************************************************
	**
Pragma directive
**********************************************************************************************************************
	*/
/*********************************************************************************************************************
	**
Includes
**********************************************************************************************************************
	*/
#include "R_ADC.h"
#include "bsp_api.h"
#include "vector_data.h"

/*********************************************************************************************************************
	**
Global variables and functions
**********************************************************************************************************************
	*/

	
volatile uint16_t AD_value_0 = 0;

/*********************************************************************************************************************
	**
* Function Name: R_ADC
* Description  : This function initializes the ADC module.
* Arguments    : None
* Return Value : None
**********************************************************************************************************************
	*/
/*********************************************************************************************************************
	**
* Function Name: R_S12AD0_Create
* Description  : This function initializes the AD0 converter.
* Arguments    : None
* Return Value : None
**********************************************************************************************************************
	*/
void R_S12AD0_Create(void)
{
	R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_RESET);
	R_BSP_MODULE_START(FSP_IP_ADC12,0);
	//	R_BSP_MODULE_START(FSP_IP_ELC,0);
	R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_RESET);
	

	R_SYSC_NS->MSTPCRC_b.MSTPCRC06 = 0U;


	R_ADC120->ADCSR = 0x0000;					//_AD_DBLTRIGGER_DISABLE | _AD_SYNC_TRIGGER | _AD_SINGLE_SCAN_MODE;
	R_ADC120->ADCSR_b.ADIE = 1; 				//Enables ADCn_ADI interrupt generation upon scan completion
	R_ADC120->ADCSR_b.GBADIE = 1;				// Enables ADCn_GBADI interrupt generation upon group B scan completion
	R_ADC120->ADCSR_b.ADCS = 1; 				//Group scan mode
	R_ADC120->ADCER = _AD_RESOLUTION_12BIT | _AD_AUTO_CLEARING_ENABLE | _AD_RIGHT_ALIGNMENT;

	/* Set AD conversion start trigger sources */
	R_ADC120->ADSTRGR_b.TRSA = 4;
	R_ADC120->ADSTRGR_b.TRSB = 5;

	/* Set channels and sampling time */
	R_ADC120->ADSSTR[0] = _AD0_SAMPLING_STATE_0;
	R_ADC120->ADSSTR[1] = _AD0_SAMPLING_STATE_1;
	R_ADC120->ADSSTR[2] = _AD0_SAMPLING_STATE_2;
	R_ADC120->ADSSTR[3] = _AD0_SAMPLING_STATE_3;
	R_ADC120->ADANSA0 = 0x00;					//_AD0_CHANNEL_SELECT_A;
	R_ADC120->ADSHCR = _AD0_DSH_SAMPLING_STATE;
	R_ADC120->ADANSA0 = _AD0_CHANNEL_SELECT_A;
	R_ADC120->ADANSB0 = _AD0_CHANNEL_SELECT_A;


	R_BSP_IrqCfg(VECTOR_NUMBER_ADC0_ADI,9,(NULL));
	R_BSP_IrqEnable(VECTOR_NUMBER_ADC0_ADI);

	R_BSP_IrqCfg(VECTOR_NUMBER_ADC0_GBADI,9,(NULL));
	R_BSP_IrqEnable(VECTOR_NUMBER_ADC0_GBADI);

//	R_BSP_IrqCfg(VECTOR_NUMBER_ENCIF_INT0,11,(NULL));
//	R_BSP_IrqEnable(VECTOR_NUMBER_ENCIF_INT0);

//	R_BSP_IrqCfg(VECTOR_NUMBER_ENCIF_INT2,12,(NULL));
//	R_BSP_IrqEnable(VECTOR_NUMBER_ENCIF_INT2);
	


}


/*********************************************************************************************************************
	**
* Function Name: * Description	: This function starts the AD0 converter.
* Arguments    : None
* Return Value : None
**********************************************************************************************************************
	*/
void R_S12AD0_Start(void)
{
	R_ADC120->ADCSR_b.TRGE = 1U;
	R_ADC120->ADCSR_b.ADST = 1U;
}


/*********************************************************************************************************************
	**
* Function Name: R_S12AD0_Stop
* Description  : This function stops the AD0 converter.
* Arguments    : None
* Return Value : None
**********************************************************************************************************************
	*/
void R_S12AD0_Stop(void)
{
	R_ADC120->ADCSR_b.TRGE = 0U;
	R_ADC120->ADCSR_b.ADST = 0U;
}


/*********************************************************************************************************************
	**
* Function Name: R_S12AD0_Get_ValueResult
* Description  : This function gets result from the AD0 converter.
* Arguments    : channel -
*					 channel of data register to be read
*				 buffer -
*					 buffer pointer
* Return Value : None
**********************************************************************************************************************
	*/
void R_S12AD0_Get_ValueResult(ad_channel_t channel,uint16_t * const buffer)
{
	if(channel == ADCHANNEL0)
	{
		*buffer = (uint16_t) (R_ADC120->ADDR[0]);
	}
	else if(channel == ADCHANNEL1)
	{
		*buffer = (uint16_t) (R_ADC120->ADDR[1]);
	}
	else if(channel == ADCHANNEL2)
	{
		*buffer = (uint16_t) (R_ADC120->ADDR[2]);
	}
	else if(channel == ADCHANNEL3)
	{
		*buffer = (uint16_t) (R_ADC120->ADDR[3]);
	}
	else if(channel == ADCHANNEL4)
	{
		*buffer = (uint16_t) (R_ADC120->ADDR[4]);
	}
	else if(channel == ADCHANNEL5)
	{
		*buffer = (uint16_t) (R_ADC120->ADDR[5]);
	}
	else if(channel == ADCHANNEL6)
	{
		*buffer = (uint16_t) (R_ADC120->ADDR[6]);
	}
	else if(channel == ADCHANNEL7)
	{
		*buffer = (uint16_t) (R_ADC120->ADDR[7]);
	}
}


/*********************************************************************************************************************
	**
* Function Name: R_S12AD1_Create
* Description  : This function initializes the AD1 converter.
* Arguments    : None
* Return Value : None
**********************************************************************************************************************
	*/
void R_S12AD1_Create(void)
{
	R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_RESET);
	R_BSP_MODULE_START(FSP_IP_ADC12,1);
	R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_RESET);


	/* Set S12AD0 control registers */
	R_ADC121->ADCSR = 0x0000;					//_AD_DBLTRIGGER_DISABLE | _AD_SYNC_TRIGGER | _AD_SINGLE_SCAN_MODE;
	R_ADC121->ADCER = _AD_RESOLUTION_12BIT | _AD_AUTO_CLEARING_ENABLE | _AD_RIGHT_ALIGNMENT;

	/* Set AD conversion start trigger sources */
	//	R_ADC121->ADSTRGR_b.TRSB = _AD_TRSA_TRGA4N;
	R_ADC121->ADSTRGR_b.TRSA = 5;
	//	R_ADC121->ADSTRGR_b.TRSB = 5;
	/* Set channels and sampling time */
	R_ADC121->ADSSTR[0] = _AD0_SAMPLING_STATE_0;
	R_ADC121->ADSSTR[1] = _AD0_SAMPLING_STATE_1;
	R_ADC121->ADSSTR[2] = _AD0_SAMPLING_STATE_2;
	R_ADC121->ADSSTR[3] = _AD0_SAMPLING_STATE_3;
	R_ADC121->ADANSA0 = 0x00;					//_AD0_CHANNEL_SELECT_A;
	R_ADC121->ADSHCR = _AD0_DSH_SAMPLING_STATE;
	R_ADC121->ADANSA0 = _AD1_CHANNEL_SELECT_A;


}


/*********************************************************************************************************************
	**
* Function Name: R_S12AD1_Start
* Description  : This function starts the AD1 converter.
* Arguments    : None
* Return Value : None
**********************************************************************************************************************
	*/
void R_S12AD1_Start(void)
{
	//	R_ADC121->ADCSR_b.TRGE = 1U;
	R_ADC121->ADCSR_b.ADST = 1U;
}





/*********************************************************************************************************************
	**
* Function Name: R_S12AD1_Stop
* Description  : This function stops the AD1 converter.
* Arguments    : None
* Return Value : None
**********************************************************************************************************************
	*/
void R_S12AD1_Stop(void)
{
	R_ADC121->ADCSR_b.TRGE = 0U;
	R_ADC121->ADCSR_b.ADST = 0U;

	//		R_ADC121->ADSTRGR  = 0U;
	//	  R_ADC121->ADGCTRGR = 0U;
	//
	//	  /* Stop the ADC. */
	//	  R_ADC121->ADCSR = 0U;
	//
	//
	//	  R_ADC121->ADSHCR = 0U;
	//
	//
	//
	//		/* Cancel ADC unit1 stop state in LPC */
	//	R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_RESET);
	//	R_BSP_MODULE_STOP(FSP_IP_ADC12,1);
	//	R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_RESET);
}


/*********************************************************************************************************************
	**
* Function Name: R_S12AD1_Get_ValueResult
* Description  : This function gets result from the AD1 converter.
* Arguments    : channel -
*					 channel of data register to be read
*				 buffer -
*					 buffer pointer
* Return Value : None
**********************************************************************************************************************
	*/
void R_S12AD1_Get_ValueResult(ad_channel_t channel,uint16_t * const buffer)
{
	if(channel == ADCHANNEL0)
	{
		*buffer = (uint16_t) (R_ADC121->ADDR[0]);
	}
	else if(channel == ADCHANNEL1)
	{
		*buffer = (uint16_t) (R_ADC121->ADDR[1]);
	}
	else if(channel == ADCHANNEL2)
	{
		*buffer = (uint16_t) (R_ADC121->ADDR[2]);
	}
	else if(channel == ADCHANNEL3)
	{
		*buffer = (uint16_t) (R_ADC121->ADDR[3]);
	}
	else if(channel == ADCHANNEL4)
	{
		*buffer = (uint16_t) (R_ADC121->ADDR[4]);
	}
	else if(channel == ADCHANNEL5)
	{
		*buffer = (uint16_t) (R_ADC121->ADDR[5]);
	}
	else if(channel == ADCHANNEL6)
	{
		*buffer = (uint16_t) (R_ADC121->ADDR[6]);
	}
	else if(channel == ADCHANNEL7)
	{
		*buffer = (uint16_t) (R_ADC121->ADDR[7]);
	}
	else if(channel == ADCHANNEL8)
	{
		*buffer = (uint16_t) (R_ADC121->ADDR[8]);
	}
	else if(channel == ADCHANNEL9)
	{
		*buffer = (uint16_t) (R_ADC121->ADDR[9]);
	}
	else if(channel == ADCHANNEL10)
	{
		*buffer = (uint16_t) (R_ADC121->ADDR[10]);
	}
	else if(channel == ADCHANNEL11)
	{
		*buffer = (uint16_t) (R_ADC121->ADDR[11]);
	}
	else if(channel == ADCHANNEL12)
	{
		*buffer = (uint16_t) (R_ADC121->ADDR[12]);
	}
	else if(channel == ADCHANNEL13)
	{
		*buffer = (uint16_t) (R_ADC121->ADDR[13]);
	}
	else if(channel == ADCHANNEL14)
	{
		*buffer = (uint16_t) (R_ADC121->ADDR[14]);
	}
	else if(channel == ADCHANNEL15)
	{
		*buffer = (uint16_t) (R_ADC121->ADDR[15]);
	}
}



void adc_scan_end_isr(void)
{
  R_S12AD0_Get_ValueResult(ADCHANNEL0,(uint16_t*)&AD_value_0);
}




