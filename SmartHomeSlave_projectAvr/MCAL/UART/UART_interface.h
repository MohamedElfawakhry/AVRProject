/*
 * UART_interface.h
 *
 *  Created on: Apr 11, 2023
 *      Author: Mohamed Elfawakhry
 */

#ifndef MCAL_UART_UART_INTERFACE_H_
#define MCAL_UART_UART_INTERFACE_H_

void UART_voidInit(void);
void UART_voidSendData ( u8 Copy_u8Data  );
void UART_voidAsyncSendData( u8 Copy_u8Data);
void UART_voidRecieveData (u8* Copy_pu8Data );
void UART_voidAsyncRecieveData ( u8* Copy_pu8ReturnedData );

#endif /* MCAL_UART_UART_INTERFACE_H_ */
