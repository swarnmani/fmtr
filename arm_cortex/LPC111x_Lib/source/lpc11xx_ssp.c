/***********************************************************************//**
 * @file	: lpc11xx_ssp.c
 * @brief	: Contains all functions support for SSP firmware library on LPC11xx
 * @version	: 1.0
 * @date	: 21. Jan. 2010
 * @author	: Coocox
 **********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup SSP
 * @{
 */

/* Includes ------------------------------------------------------------------- */
#include "lpc11xx_ssp.h"
#include "lpc11xx_syscon.h"
#include "lpc11xx_libcfg.h"


#if _SSP

/* Private Types -------------------------------------------------------------- */
/** @defgroup SSP_Private_Types
 * @{
 */

/** @brief SSP device configuration structure type */
typedef struct
{
	int32_t 	dataword;				/* Current data word: 0 - 8 bit; 1 - 16 bit */
	uint32_t    txrx_setup; 			/* Transmission setup */
	void		(*inthandler)(SSP_TypeDef *SSPx);   	/* Transmission interrupt handler */
} SSP_CFG_T;

/**
 * @}
 */

/* Private Variables ---------------------------------------------------------- */
/** @defgroup SSP_Private_Variables
 * @{
 */

/* SSP configuration data */
static SSP_CFG_T sspdat[2];

/**
 * @}
 */


/* Private Functions ---------------------------------------------------------- */
/** @defgroup SSP_Private_Functions
 * @{
 */

/**
 * @brief Convert from SSP peripheral to number
 */
static int32_t SSP_getNum(SSP_TypeDef *SSPx){
	if (SSPx == LPC_SSP0) {
		return (0);
	} else if (SSPx == LPC_SSP1) {
		return (1);
	}
	return (-1);
}


/*********************************************************************//**
 * @brief 		Standard Private SSP Interrupt handler
 * @param		None
 * @return 		None
 ***********************************************************************/
void SSP_IntHandler(SSP_TypeDef *SSPx)
{
	SSP_DATA_SETUP_Type *xf_setup;
    uint16_t tmp;
    int32_t sspnum;

    // Disable interrupt
    SSPx->IMSC = 0;

    sspnum = SSP_getNum(SSPx);
    xf_setup = (SSP_DATA_SETUP_Type *)sspdat[sspnum].txrx_setup;

    // save status
    tmp = SSPx->RIS;
    xf_setup->status = tmp;

    // Check overrun error
    if (tmp & SSP_RIS_ROR){
    	// Clear interrupt
    	SSPx->ICR = SSP_RIS_ROR;
    	// update status
    	xf_setup->status |= SSP_STAT_ERROR;
    	// Callback
    	if (xf_setup->callback != NULL){
    		xf_setup->callback();
    	}
    	return;
    }

    if ((xf_setup->tx_cnt != xf_setup->length) || (xf_setup->rx_cnt != xf_setup->length)){
    	/* check if RX FIFO contains data */
		while ((SSPx->SR & SSP_SR_RNE) && (xf_setup->rx_cnt != xf_setup->length)){
			// Read data from SSP data
			tmp = SSP_ReceiveData(SSPx);

			// Store data to destination
			if (xf_setup->rx_data != NULL)
			{
				if (sspdat[sspnum].dataword == 0){
					*(uint8_t *)((uint32_t)xf_setup->rx_data + xf_setup->rx_cnt) = (uint8_t) tmp;
				} else {
					*(uint16_t *)((uint32_t)xf_setup->rx_data + xf_setup->rx_cnt) = (uint16_t) tmp;
				}
			}
			// Increase counter
			if (sspdat[sspnum].dataword == 0){
				xf_setup->rx_cnt++;
			} else {
				xf_setup->rx_cnt += 2;
			}
		}

		while ((SSPx->SR & SSP_SR_TNF) && (xf_setup->tx_cnt != xf_setup->length)){
			// Write data to buffer
			if(xf_setup->tx_data == NULL){
				if (sspdat[sspnum].dataword == 0){
					SSP_SendData(SSPx, 0xFF);
					xf_setup->tx_cnt++;
				} else {
					SSP_SendData(SSPx, 0xFFFF);
					xf_setup->tx_cnt += 2;
				}
			} else {
				if (sspdat[sspnum].dataword == 0){
					SSP_SendData(SSPx, (*(uint8_t *)((uint32_t)xf_setup->tx_data + xf_setup->tx_cnt)));
					xf_setup->tx_cnt++;
				} else {
					SSP_SendData(SSPx, (*(uint16_t *)((uint32_t)xf_setup->tx_data + xf_setup->tx_cnt)));
					xf_setup->tx_cnt += 2;
				}
			}

		    // Check overrun error
		    if ((tmp = SSPx->RIS) & SSP_RIS_ROR){
		    	// update status
		    	xf_setup->status |= SSP_STAT_ERROR;
		    	// Callback
		    	if (xf_setup->callback != NULL){
		    		xf_setup->callback();
		    	}
		    	return;
		    }

			// Check for any data available in RX FIFO
			while ((SSPx->SR & SSP_SR_RNE) && (xf_setup->rx_cnt != xf_setup->length)){
				// Read data from SSP data
				tmp = SSP_ReceiveData(SSPx);

				// Store data to destination
				if (xf_setup->rx_data != NULL)
				{
					if (sspdat[sspnum].dataword == 0){
						*(uint8_t *)((uint32_t)xf_setup->rx_data + xf_setup->rx_cnt) = (uint8_t) tmp;
					} else {
						*(uint8_t *)((uint32_t)xf_setup->rx_data + xf_setup->rx_cnt) = (uint16_t) tmp;
					}
				}
				// Increase counter
				if (sspdat[sspnum].dataword == 0){
					xf_setup->rx_cnt++;
				} else {
					xf_setup->rx_cnt += 2;
				}
			}
		}
    }

	// If there more data to sent or receive
	if ((xf_setup->rx_cnt != xf_setup->length) || (xf_setup->tx_cnt != xf_setup->length)){
		// Enable all interrupt
		SSPx->IMSC = SSP_IMSC_BITMASK;
	} else {
		// Save status
		xf_setup->status = SSP_STAT_DONE;
		// Callback
		if (xf_setup->callback != NULL){
			xf_setup->callback();
		}
	}
}

/**
 * @}
 */


/* Public Functions ----------------------------------------------------------- */
/** @addtogroup SSP_Public_Functions
 * @{
 */

/*********************************************************************//**
 * @brief 		Setup clock rate for SSP device
 * @param[in] 	SSPx	SSP peripheral definition, should be
 * 						SSP0 or SSP1.
 * @param[in]	target_clock : clock of SSP (Hz)
 * @return 		None
 ***********************************************************************/
void SSP_SetClock (SSP_TypeDef *SSPx, uint32_t target_clock)
{
    uint32_t prescale, cr0_div, cmp_clk, ssp_clk;

    CHECK_PARAM(PARAM_SSPx(SSPx));

    /* The SSP clock is derived from the (main system oscillator / 2),
       so compute the best divider from that clock */
    if (SSPx == LPC_SSP0){
    	ssp_clk = SYSCON_GetSSP0Clock(0);
    } else if (SSPx == LPC_SSP1) {
    	ssp_clk = SYSCON_GetSSP0Clock(1);
    } else {
    	return;
    }

	/* Find closest divider to get at or under the target frequency.
	   Use smallest prescale possible and rely on the divider to get
	   the closest target frequency */
	cr0_div = 0;
	cmp_clk = 0xFFFFFFFF;
	prescale = 2;
	while (cmp_clk > target_clock)
	{
		cmp_clk = ssp_clk / ((cr0_div + 1) * prescale);
		if (cmp_clk > target_clock)
		{
			cr0_div++;
			if (cr0_div > 0xFF)
			{
				cr0_div = 0;
				prescale += 2;
			}
		}
	}

    /* Write computed prescaler and divider back to register */
    SSPx->CR0 &= (~SSP_CR0_SCR(0xFF)) & SSP_CR0_BITMASK;
    SSPx->CR0 |= (SSP_CR0_SCR(cr0_div)) & SSP_CR0_BITMASK;
    SSPx->CPSR = prescale & SSP_CPSR_BITMASK;
}


/*********************************************************************//**
 * @brief		De-initializes the SSPx peripheral registers to their
*                  default reset values.
 * @param[in]	SSPx	SSP peripheral selected, should be SSP0 or SSP1
 * @return 		None
 **********************************************************************/
void SSP_DeInit(SSP_TypeDef* SSPx)
{
	CHECK_PARAM(PARAM_SSPx(SSPx));

	if (SSPx == LPC_SSP0){
        /* Reset SSP0 */        
        SYSCON_PeriphResetCmd(SYSCON_RSTPeriph_SSP0, ENABLE);                
        SYSCON_PeriphResetCmd(SYSCON_RSTPeriph_SSP0, DISABLE);                

		/* Set up clock and power for SSP0 module */
		SYSCON_AHBPeriphClockCmd(SYSCON_AHBPeriph_SSP0, DISABLE);
	} else if (SSPx == LPC_SSP1) {
        /* Reset SSP1 */        
        SYSCON_PeriphResetCmd(SYSCON_RSTPeriph_SSP1, ENABLE);                
        SYSCON_PeriphResetCmd(SYSCON_RSTPeriph_SSP1, DISABLE);                        

		/* Set up clock and power for SSP1 module */
		SYSCON_AHBPeriphClockCmd(SYSCON_AHBPeriph_SSP1, DISABLE);
	}
}

/********************************************************************//**
 * @brief		Assigns SSP0 pins:
 *                MISO : PIO0_8
 *                MOSI : PIO0_9
 *                SCK  : PIO0_10/PIO2_11/PIO0_6
 *                SSEL : PIO0_2
 * @param[in]	sck0 Locate SCK0 position, it can be
 *                   SCK0_PIO0_10 : pin location SWCLK/PIO0_10/SCK0/CT16B0_MAT2
 *                                  NOTE: SWCLK is JTAG pin
 *                   SCK0_PIO2_11 : pin location PIO2_11/SCK0
 *                   SCK0_PIO0_6  : pin location PIO0_6/SCK0
 *
 *               Note: SCK0_PIO0_10 is multiplexed with JTAG pins
 * @param[in]	useSSEL Assign SSEL pin or not	
 * @return 		None
 *********************************************************************/
void SSP_SSP0PinsInit(SCK0_Position_Typedef sck0, FunctionalState useSSEL)
{
    IOCON_SCK0Locate(sck0);

    IOCON_SetPinFunc(IOCON_PIO0_8, PIO0_8_FUN_MISO0);
    IOCON_SetPinFunc(IOCON_PIO0_9, PIO0_9_FUN_MOSI0);

    if(useSSEL == ENABLE) {
        IOCON_SetPinFunc(IOCON_PIO0_2, PIO0_2_FUN_SSEL0);
    }
           
    switch(sck0) {
    case SCK0_PIO0_10:
        IOCON_SetPinFunc(IOCON_PIO0_10, PIO0_10_FUN_SCK0); break;      
    case SCK0_PIO2_11:
        IOCON_SetPinFunc(IOCON_PIO2_11, PIO2_11_FUN_SCK0); break;
    case SCK0_PIO0_6:
        IOCON_SetPinFunc(IOCON_PIO0_6,  PIO0_6_FUN_SCK0);  break;
    default: break;
    }    
}

/********************************************************************//**
 * @brief		Assigns SSP1 pins:
 *                MISO : PIO2_2
 *                MOSI : PIO2_3
 *                SCK  : PIO2_1
 *                SSEL : PIO2_0
 * @param[in]	useSSEL Assign SSEL pin or not
 * @return 		None
 *********************************************************************/
void SSP_SSP1PinsInit(FunctionalState useSSEL)
{
    IOCON_SetPinFunc(IOCON_PIO2_2, PIO2_2_FUN_MISO1);
    IOCON_SetPinFunc(IOCON_PIO2_3, PIO2_3_FUN_PIO_MOSI1);
    IOCON_SetPinFunc(IOCON_PIO2_1, PIO2_1_FUN_SCK1);

    if(useSSEL == ENABLE) {
        IOCON_SetPinFunc(IOCON_PIO2_0, PIO2_0_FUN_SSEL1);
    }   
}

/********************************************************************//**
 * @brief		Initializes the SSPx peripheral according to the specified
*               parameters in the SSP_ConfigStruct.
 * @param[in]	SSPx	SSP peripheral selected, should be SSP0 or SSP1
 * @param[in]	SSP_ConfigStruct Pointer to a SSP_CFG_Type structure
*                    that contains the configuration information for the
*                    specified SSP peripheral.
 * @return 		None
 *********************************************************************/
void SSP_Init(SSP_TypeDef *SSPx, SSP_CFG_Type *SSP_ConfigStruct)
{
	uint32_t tmp;

	CHECK_PARAM(PARAM_SSPx(SSPx));

	if(SSPx == LPC_SSP0) {
		/* Set up clock and power for SSP0 module */
		SYSCON_AHBPeriphClockCmd(SYSCON_AHBPeriph_SSP0, ENABLE);
	} else if(SSPx == LPC_SSP1) {
		/* Set up clock and power for SSP1 module */
		SYSCON_AHBPeriphClockCmd(SYSCON_AHBPeriph_SSP1, ENABLE);
	} else {
		return;
	}

	/* Configure SSP, interrupt is disable, LoopBack mode is disable,
	 * SSP is disable, Slave output is disable as default
	 */
	tmp = ((SSP_ConfigStruct->CPHA) | (SSP_ConfigStruct->CPOL) \
		| (SSP_ConfigStruct->FrameFormat) | (SSP_ConfigStruct->Databit))
		& SSP_CR0_BITMASK;
	// write back to SSP control register
	SSPx->CR0 = tmp;
	tmp = SSP_getNum(SSPx);
	if (SSP_ConfigStruct->Databit > SSP_DATABIT_8){
		sspdat[tmp].dataword = 1;
	} else {
		sspdat[tmp].dataword = 0;
	}

	tmp = SSP_ConfigStruct->Mode & SSP_CR1_BITMASK;
	// Write back to CR1
	SSPx->CR1 = tmp;

	// Set clock rate for SSP peripheral
	SSP_SetClock(SSPx, SSP_ConfigStruct->ClockRate);
}



/*****************************************************************************//**
* @brief		Fills each SSP_InitStruct member with its default value:
* 				- CPHA = SSP_CPHA_FIRST
* 				- CPOL = SSP_CPOL_HI
* 				- ClockRate = 1000000
* 				- Databit = SSP_DATABIT_8
* 				- Mode = SSP_MASTER_MODE
* 				- FrameFormat = SSP_FRAME_SSP
* @param[in]	SSP_InitStruct Pointer to a SSP_CFG_Type structure
*                    which will be initialized.
* @return		None
*******************************************************************************/
void SSP_ConfigStructInit(SSP_CFG_Type *SSP_InitStruct)
{
	SSP_InitStruct->CPHA = SSP_CPHA_FIRST;
	SSP_InitStruct->CPOL = SSP_CPOL_HI;
	SSP_InitStruct->ClockRate = 1000000;
	SSP_InitStruct->Databit = SSP_DATABIT_8;
	SSP_InitStruct->Mode = SSP_MASTER_MODE;
	SSP_InitStruct->FrameFormat = SSP_FRAME_SPI;
}


/*********************************************************************//**
 * @brief		Enable or disable SSP peripheral's operation
 * @param[in]	SSPx	SSP peripheral, should be SSP0 or SSP1
 * @param[in]	NewState New State of SSPx peripheral's operation
 * @return 		none
 **********************************************************************/
void SSP_Cmd(SSP_TypeDef* SSPx, FunctionalState NewState)
{
	CHECK_PARAM(PARAM_SSPx(SSPx));
	CHECK_PARAM(PARAM_FUNCTIONALSTATE(NewState));

	if (NewState == ENABLE)
	{
		SSPx->CR1 |= SSP_CR1_SSP_EN;
	}
	else
	{
		SSPx->CR1 &= (~SSP_CR1_SSP_EN) & SSP_CR1_BITMASK;
	}
}



/*********************************************************************//**
 * @brief		Enable or disable Loop Back mode function in SSP peripheral
 * @param[in]	SSPx	SSP peripheral selected, should be SSP0 or SSP1
 * @param[in]	NewState	New State of Loop Back mode, should be:
 * 							- ENABLE: Enable this function
 * 							- DISABLE: Disable this function
 * @return 		None
 **********************************************************************/
void SSP_LoopBackCmd(SSP_TypeDef* SSPx, FunctionalState NewState)
{
	CHECK_PARAM(PARAM_SSPx(SSPx));
	CHECK_PARAM(PARAM_FUNCTIONALSTATE(NewState));

	if (NewState == ENABLE)
	{
		SSPx->CR1 |= SSP_CR1_LBM_EN;
	}
	else
	{
		SSPx->CR1 &= (~SSP_CR1_LBM_EN) & SSP_CR1_BITMASK;
	}
}



/*********************************************************************//**
 * @brief		Enable or disable Slave Output function in SSP peripheral
 * @param[in]	SSPx	SSP peripheral selected, should be SSP0 or SSP1
 * @param[in]	NewState	New State of Slave Output function, should be:
 * 							- ENABLE: Slave Output in normal operation
 * 							- DISABLE: Slave Output is disabled. This blocks
 * 							SSP controller from driving the transmit data
 * 							line (MISO)
 * Note: 		This function is available when SSP peripheral in Slave mode
 * @return 		None
 **********************************************************************/
void SSP_SlaveOutputCmd(SSP_TypeDef* SSPx, FunctionalState NewState)
{
	CHECK_PARAM(PARAM_SSPx(SSPx));
	CHECK_PARAM(PARAM_FUNCTIONALSTATE(NewState));

	if (NewState == ENABLE)
	{
		SSPx->CR1 &= (~SSP_CR1_SO_DISABLE) & SSP_CR1_BITMASK;
	}
	else
	{
		SSPx->CR1 |= SSP_CR1_SO_DISABLE;
	}
}



/*********************************************************************//**
 * @brief		Transmit a single data through SSPx peripheral
 * @param[in]	SSPx	SSP peripheral selected, should be SSP
 * @param[in]	Data	Data to transmit (must be 16 or 8-bit long,
 * 						this depend on SSP data bit number configured)
 * @return 		none
 **********************************************************************/
void SSP_SendData(SSP_TypeDef* SSPx, uint16_t Data)
{
	CHECK_PARAM(PARAM_SSPx(SSPx));

	SSPx->DR = SSP_DR_BITMASK(Data);
}



/*********************************************************************//**
 * @brief		Receive a single data from SSPx peripheral
 * @param[in]	SSPx	SSP peripheral selected, should be SSP
 * @return 		Data received (16-bit long)
 **********************************************************************/
uint16_t SSP_ReceiveData(SSP_TypeDef* SSPx)
{
	CHECK_PARAM(PARAM_SSPx(SSPx));

	return ((uint16_t) (SSP_DR_BITMASK(SSPx->DR)));
}

/*********************************************************************//**
 * @brief 		SSP Read write data function
 * @param[in]	SSPx 	Pointer to SSP peripheral, should be SSP0 or SSP1
 * @param[in]	dataCfg	Pointer to a SSP_DATA_SETUP_Type structure that
 * 						contains specified information about transmit
 * 						data configuration.
 * @param[in]	xfType	Transfer type, should be:
 * 						- SSP_TRANSFER_POLLING: Polling mode
 * 						- SSP_TRANSFER_INTERRUPT: Interrupt mode
 * @return 		Actual Data length has been transferred in polling mode.
 * 				In interrupt mode, always return (0)
 * 				Return (-1) if error.
 * Note: This function can be used in both master and slave mode.
 ***********************************************************************/
int32_t SSP_ReadWrite (SSP_TypeDef *SSPx, SSP_DATA_SETUP_Type *dataCfg, \
						SSP_TRANSFER_Type xfType)
{
	uint8_t *rdata8;
    uint8_t *wdata8;
	uint16_t *rdata16;
    uint16_t *wdata16;
    uint32_t stat;
    uint32_t tmp;
    int32_t sspnum;
    int32_t dataword;

    dataCfg->rx_cnt = 0;
    dataCfg->tx_cnt = 0;
    dataCfg->status = 0;


	/* Clear all remaining data in RX FIFO */
	while (SSPx->SR & SSP_SR_RNE){
		tmp = (uint32_t) SSP_ReceiveData(SSPx);
	}

	// Clear status
	SSPx->ICR = SSP_ICR_BITMASK;

	sspnum = SSP_getNum(SSPx);
	dataword = sspdat[sspnum].dataword;

	// Polling mode ----------------------------------------------------------------------
	if (xfType == SSP_TRANSFER_POLLING){
		if (dataword == 0){
			rdata8 = (uint8_t *)dataCfg->rx_data;
			wdata8 = (uint8_t *)dataCfg->tx_data;
		} else {
			rdata16 = (uint16_t *)dataCfg->rx_data;
			wdata16 = (uint16_t *)dataCfg->tx_data;
		}
		while ((dataCfg->tx_cnt != dataCfg->length) || (dataCfg->rx_cnt != dataCfg->length)){
			if ((SSPx->SR & SSP_SR_TNF) && (dataCfg->tx_cnt != dataCfg->length)){
				// Write data to buffer
				if(dataCfg->tx_data == NULL){
					if (dataword == 0){
						SSP_SendData(SSPx, 0xFF);
						dataCfg->tx_cnt++;
					} else {
						SSP_SendData(SSPx, 0xFFFF);
						dataCfg->tx_cnt += 2;
					}
				} else {
					if (dataword == 0){
						SSP_SendData(SSPx, *wdata8);
						wdata8++;
						dataCfg->tx_cnt++;
					} else {
						SSP_SendData(SSPx, *wdata16);
						wdata16++;
						dataCfg->tx_cnt += 2;
					}
				}
			}

			// Check overrun error
			if ((stat = SSPx->RIS) & SSP_RIS_ROR){
				// save status and return
				dataCfg->status = stat | SSP_STAT_ERROR;
				return (-1);
			}

			// Check for any data available in RX FIFO
			while ((SSPx->SR & SSP_SR_RNE) && (dataCfg->rx_cnt != dataCfg->length)){
				// Read data from SSP data
				tmp = SSP_ReceiveData(SSPx);

				// Store data to destination
				if (dataCfg->rx_data != NULL)
				{
					if (dataword == 0){
						*(rdata8) = (uint8_t) tmp;
						rdata8++;
					} else {
						*(rdata16) = (uint16_t) tmp;
						rdata16++;
					}
				}
				// Increase counter
				if (dataword == 0){
					dataCfg->rx_cnt++;
				} else {
					dataCfg->rx_cnt += 2;
				}
			}
		}

		// save status
		dataCfg->status = SSP_STAT_DONE;

		if (dataCfg->tx_data != NULL){
			return dataCfg->tx_cnt;
		} else if (dataCfg->rx_data != NULL){
			return dataCfg->rx_cnt;
		} else {
			return (0);
		}
	}

	// Interrupt mode ----------------------------------------------------------------------
	else if (xfType == SSP_TRANSFER_INTERRUPT){
		sspdat[sspnum].inthandler = SSP_IntHandler;
		sspdat[sspnum].txrx_setup = (uint32_t)dataCfg;

		while ((SSPx->SR & SSP_SR_TNF) && (dataCfg->tx_cnt != dataCfg->length)){
			// Write data to buffer
			if(dataCfg->tx_data == NULL){
				if (sspdat[sspnum].dataword == 0){
					SSP_SendData(SSPx, 0xFF);
					dataCfg->tx_cnt++;
				} else {
					SSP_SendData(SSPx, 0xFFFF);
					dataCfg->tx_cnt += 2;
				}
			} else {
				if (sspdat[sspnum].dataword == 0){
					SSP_SendData(SSPx, (*(uint8_t *)((uint32_t)dataCfg->tx_data + dataCfg->tx_cnt)));
					dataCfg->tx_cnt++;
				} else {
					SSP_SendData(SSPx, (*(uint16_t *)((uint32_t)dataCfg->tx_data + dataCfg->tx_cnt)));
					dataCfg->tx_cnt += 2;
				}
			}

			// Check error
			if ((stat = SSPx->RIS) & SSP_RIS_ROR){
				// save status and return
				dataCfg->status = stat | SSP_STAT_ERROR;
				return (-1);
			}

			// Check for any data available in RX FIFO
			while ((SSPx->SR & SSP_SR_RNE) && (dataCfg->rx_cnt != dataCfg->length)){
				// Read data from SSP data
				tmp = SSP_ReceiveData(SSPx);

				// Store data to destination
				if (dataCfg->rx_data != NULL)
				{
					if (sspdat[sspnum].dataword == 0){
						*(uint8_t *)((uint32_t)dataCfg->rx_data + dataCfg->rx_cnt) = (uint8_t) tmp;
					} else {
						*(uint16_t *)((uint32_t)dataCfg->rx_data + dataCfg->rx_cnt) = (uint16_t) tmp;
					}
				}
				// Increase counter
				if (sspdat[sspnum].dataword == 0){
					dataCfg->rx_cnt++;
				} else {
					dataCfg->rx_cnt += 2;
				}
			}
		}

		// If there more data to sent or receive
		if ((dataCfg->rx_cnt != dataCfg->length) || (dataCfg->tx_cnt != dataCfg->length)){
			// Enable all interrupt
			SSPx->IMSC = SSP_IMSC_BITMASK;
		} else {
			// Save status
			dataCfg->status = SSP_STAT_DONE;
		}
		return (0);
	}

	return (-1);
}

/*********************************************************************//**
 * @brief		Checks whether the specified SSP status flag is set or not
 * @param[in]	SSPx	SSP peripheral selected, should be SSP0 or SSP1
 * @param[in]	FlagType	Type of flag to check status, should be one
 * 							of following:
 *							- SSP_STAT_TXFIFO_EMPTY: TX FIFO is empty
 *							- SSP_STAT_TXFIFO_NOTFULL: TX FIFO is not full
 *							- SSP_STAT_RXFIFO_NOTEMPTY: RX FIFO is not empty
 *							- SSP_STAT_RXFIFO_FULL: RX FIFO is full
 *							- SSP_STAT_BUSY: SSP peripheral is busy
 * @return		New State of specified SSP status flag
 **********************************************************************/
FlagStatus SSP_GetStatus(SSP_TypeDef* SSPx, uint32_t FlagType)
{
	CHECK_PARAM(PARAM_SSPx(SSPx));
	CHECK_PARAM(PARAM_SSP_STAT(FlagType));

	return ((SSPx->SR & FlagType) ? SET : RESET);
}



/*********************************************************************//**
 * @brief		Enable or disable specified interrupt type in SSP peripheral
 * @param[in]	SSPx	SSP peripheral selected, should be SSP0 or SSP1
 * @param[in]	IntType	Interrupt type in SSP peripheral, should be:
 * 				- SSP_INTCFG_ROR: Receive Overrun interrupt
 * 				- SSP_INTCFG_RT: Receive Time out interrupt
 * 				- SSP_INTCFG_RX: RX FIFO is at least half full interrupt
 * 				- SSP_INTCFG_TX: TX FIFO is at least half empty interrupt
 * @param[in]	NewState New State of specified interrupt type, should be:
 * 				- ENABLE: Enable this interrupt type
 * 				- DISABLE: Disable this interrupt type
 * @return		None
 **********************************************************************/
void SSP_IntConfig(SSP_TypeDef *SSPx, uint32_t IntType, FunctionalState NewState)
{
	CHECK_PARAM(PARAM_SSPx(SSPx));
	CHECK_PARAM(PARAM_SSP_INTCFG(IntType));

	if (NewState == ENABLE)
	{
		SSPx->IMSC |= IntType;
	}
	else
	{
		SSPx->IMSC &= (~IntType) & SSP_IMSC_BITMASK;
	}
}


/*********************************************************************//**
 * @brief	Check whether the specified Raw interrupt status flag is
 * 			set or not
 * @param[in]	SSPx	SSP peripheral selected, should be SSP0 or SSP1
 * @param[in]	RawIntType	Raw Interrupt Type, should be:
 * 				- SSP_INTSTAT_RAW_ROR: Receive Overrun interrupt
 * 				- SSP_INTSTAT_RAW_RT: Receive Time out interrupt
 * 				- SSP_INTSTAT_RAW_RX: RX FIFO is at least half full interrupt
 * 				- SSP_INTSTAT_RAW_TX: TX FIFO is at least half empty interrupt
 * @return	New State of specified Raw interrupt status flag in SSP peripheral
 * Note: Enabling/Disabling specified interrupt in SSP peripheral does not
 * 		effect to Raw Interrupt Status flag.
 **********************************************************************/
IntStatus SSP_GetRawIntStatus(SSP_TypeDef *SSPx, uint32_t RawIntType)
{
	CHECK_PARAM(PARAM_SSPx(SSPx));
	CHECK_PARAM(PARAM_SSP_INTSTAT_RAW(RawIntType));

	return ((SSPx->RIS & RawIntType) ? SET : RESET);
}


/*********************************************************************//**
 * @brief	Check whether the specified interrupt status flag is
 * 			set or not
 * @param[in]	SSPx	SSP peripheral selected, should be SSP0 or SSP1
 * @param[in]	RawIntType	Raw Interrupt Type, should be:
 * 				- SSP_INTSTAT_ROR: Receive Overrun interrupt
 * 				- SSP_INTSTAT_RT: Receive Time out interrupt
 * 				- SSP_INTSTAT_RX: RX FIFO is at least half full interrupt
 * 				- SSP_INTSTAT_TX: TX FIFO is at least half empty interrupt
 * @return	New State of specified interrupt status flag in SSP peripheral
 * Note: Enabling/Disabling specified interrupt in SSP peripheral effects
 * 			to Interrupt Status flag.
 **********************************************************************/
IntStatus SSP_GetIntStatus (SSP_TypeDef *SSPx, uint32_t IntType)
{
	CHECK_PARAM(PARAM_SSPx(SSPx));
	CHECK_PARAM(PARAM_SSP_INTSTAT(IntType));

	return ((SSPx->MIS & IntType) ? SET :RESET);
}



/*********************************************************************//**
 * @brief				Clear specified interrupt pending in SSP peripheral
 * @param[in]	SSPx	SSP peripheral selected, should be SSP0 or SSP1
 * @param[in]	IntType	Interrupt pending to clear, should be:
 * 						- SSP_INTCLR_ROR: clears the "frame was received when
 * 						RxFIFO was full" interrupt.
 * 						- SSP_INTCLR_RT: clears the "Rx FIFO was not empty and
 * 						has not been read for a timeout period" interrupt.
 * @return		None
 **********************************************************************/
void SSP_ClearIntPending(SSP_TypeDef *SSPx, uint32_t IntType)
{
	CHECK_PARAM(PARAM_SSPx(SSPx));
	CHECK_PARAM(PARAM_SSP_INTCLR(IntType));

	SSPx->ICR = IntType;
}

/**
 * @brief		Standard SSP0 Interrupt handler
 * @param[in] 	None
 * @return		None
 */
void SSP0_StdIntHandler(void)
{
	// Call relevant handler
	sspdat[0].inthandler(LPC_SSP0);
}

/**
 * @brief		Standard SSP1 Interrupt handler
 * @param[in] 	None
 * @return		None
 */
void SSP1_StdIntHandler(void)
{
	// Call relevant handler
	sspdat[1].inthandler(LPC_SSP1);
}

/**
 * @}
 */

#endif /* _SSP */

/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */

