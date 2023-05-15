/*
 * UART_program.c
 *
 *  Created on: Apr 11, 2023
 *      Author: First
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"

u8* Glo_pu8RecievedData = NULL ;
void UART_voidInit(void)
{
	/***************	UCSRC CONFIG	*********/
	/* 		Select UCSRC_REG		*/
	SET_BIT(UART_UCSRC_REG , 7);
	/* 		USART MODE --> Asynch 		*/
	CLR_BIT(UART_UCSRC_REG , 6);
	/* 		Parity Check		*/
	//Clear Parity Check
	CLR_BIT(UART_UCSRC_REG , 5);
	CLR_BIT(UART_UCSRC_REG , 4);
	/*		STOP BIT SELECT		*/
	// Select 1 SP bit
	CLR_BIT(UART_UCSRC_REG , 3);
	/*	Character size		*/
	// Select 8 bit mode data
	SET_BIT(UART_UCSRC_REG , 2);
	SET_BIT(UART_UCSRC_REG , 1);
	CLR_BIT(UART_UCSRB_REG , 2 ); // Bit in other reg to select char size
	/* Clock Polarity	*/
	//Transmit in Raising , Sample in Falling
	CLR_BIT(UART_UCSRC_REG ,0 );
	/**********************************************/
	/***************	BaudRate CONFIG		*********/
	/* Select Baud Rate Register */
	CLR_BIT(UART_UCSRC_REG , 7);
	/* Write the baud rate in registers */
	UART_UBRRH_REG = (u8) (UART_BAUDRATE >>8 );
	UART_UBRRL_REG = (u8) (UART_BAUDRATE);
	/**********************************************/
	/***************	UCSRB CONFIG	*********/
	/* Enable Rx */
	SET_BIT(UART_UCSRB_REG , 4 );
	/* Enable Tx */
	SET_BIT(UART_UCSRB_REG , 3 );
	/**********************************************/
	/***************	UCSRA CONFIG	*********/
	/* No Configuration Till Now */
	/**********************************************/



}
void UART_voidSendData ( u8 Copy_u8Data  )
{
	/* Polling until Buffer is empty  */
	while(GET_BIT(UART_UCSRA_REG , 5)==0);
	/* Write data on UDR Reg */
	UART_UDR_REG = Copy_u8Data ;
	/*CLEAR the flag */
	SET_BIT(UART_UCSRA_REG , UCSRA_TXC);

}
void UART_voidAsyncSendData( u8 Copy_u8Data)
{
	/*Enable Interrupt for */
}


void UART_voidRecieveData (u8* Copy_pu8Data )
{
	/* Polling until Receive Complete  */
	while(GET_BIT(UART_UCSRA_REG , 7 )==0);
	*Copy_pu8Data = UART_UDR_REG ;
}
void UART_voidAsyncRecieveData ( u8* Copy_pu8ReturnedData )
{
	/*Enable interrupt for Recieve Complete */
	SET_BIT(UART_UCSRB_REG , UCSRB_RXCIE);
	Glo_pu8RecievedData = Copy_pu8ReturnedData ;
}
void __vector_13(void) __attribute__((signal));
void __vector_13(void)
{
	if(Glo_pu8RecievedData != NULL)
	{
		*Glo_pu8RecievedData = UART_UDR_REG ;
		/* Disable Rx Interrupt*/
		//CLR_BIT(UART_UCSRB_REG , UCSRB_RXCIE );
	}
}

