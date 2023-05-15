
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "SPI_interface.h"
#include "SPI_private.h"
#include "SPI_config.h"

void (*Glo_pfNotificationSPIRecieved)(void)= NULL ;
u8* Glo_pu8SPIRecievedData =NULL;
void SPI_voidMasterInit(void)
{
	/*SPI Interrupt Enable*/
	CLR_BIT(SPCR_REG , 7 );
	/*	Data Order */
	/*LSB First*/
	SET_BIT(SPCR_REG , 5);
	/*Master / Slave Select*/
	/*Master*/
	SET_BIT(SPCR_REG , 4);

	/*Clock polarity */
	/*CPOL = 0 , Leading Edge is raising*/
	CLR_BIT(SPCR_REG , 3);
	/*Clock Phase */
	/*Sample on leading , setup on traliling*/
	CLR_BIT(SPCR_REG, 2);
	/*SPI Clock Rate */
	/* /4 */
	CLR_BIT(SPCR_REG , 1);
	SET_BIT(SPCR_REG , 0);
	CLR_BIT(SPSR_REG , 0);

	/*SPI Enable*/
	SET_BIT(SPCR_REG , 6);
}

void SPI_voidSlaveInit(void)
{
	/*SPI Interrupt Enable*/
	CLR_BIT(SPCR_REG , 7 );
	/*	Data Order */
	/*LSB First*/
	SET_BIT(SPCR_REG , 5);
	/*Master / Slave Select*/
	/*Slave*/
	CLR_BIT(SPCR_REG , 4);
	/*Clock polarity */
	/*CPOL = 0 , Leading Edge is raising*/
	CLR_BIT(SPCR_REG , 3);
	/*Clock Phase */
	/*Sample on leading , setup on traliling*/
	CLR_BIT(SPCR_REG, 2);
	/*SPI Enable*/
	SET_BIT(SPCR_REG , 6);
}

void SPI_voidMasterSendData(u8 Copy_u8DataToBeSent , u8* Copy_pu8ReceivedData)
{
	
	/*Set the Data to register */
	SPDR_REG = Copy_u8DataToBeSent ;
	/*Polling on the transmition flag */
	while( ( GET_BIT(SPSR_REG , 7) ) == 0) ;
	/*Clear the flag */
	SET_BIT(SPSR_REG  , 7 );
	/* Read data returned from the slave */
	if(Copy_pu8ReceivedData != NULL)
	*Copy_pu8ReceivedData = SPDR_REG ;
}
void SPI_voidAsyncSendData (u8 Copy_u8DataToBeSent , u8* Copy_pu8RecievedData )
{
	/* SPI Interrupt enable */
	SET_BIT(SPCR_REG , 7 );

	Glo_pu8SPIRecievedData = Copy_pu8RecievedData ;
	SPDR_REG = Copy_u8DataToBeSent ;

}
void __vector_12(void)	__attribute__((signal));
void __vector_12(void)
{
	if(Glo_pu8SPIRecievedData != NULL)
	{
	/*Return Data */
	*Glo_pu8SPIRecievedData = SPDR_REG ;
	/* Disable Interrupt */
	//CLR_BIT(SPCR_REG , 7 );
	}
}
void SPI_voidSetCallBackFunction ( void (*Lpf)(void))
{
	if (Glo_pfNotificationSPIRecieved != NULL)
	{
		Glo_pfNotificationSPIRecieved();
	}
}
