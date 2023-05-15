/***************************************************************/
/**SWC :       DIO(Digital Input Output)              **********/
/**Author :   Mohamed Khaled Elfawakhry              ***********/
/**Version :       1.0                               ***********/
/**Date :            29/3/2023                      ************/
/***************************************************************/
#include <util/delay.h>

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/DIO/DIO_interface.h"

#include "CLCD_interface.h"
#include "CLCD_private.h"
#include "CLCD_config.h"

/*******************************************************************************/
/* Func Name : CLCD_voidInit                                             */
/* i/p arguments : void       */
/*return : void                                                                */
/*******************************************************************************/
void CLCD_voidInit        ( void ){

	DIO_voidSetPortDirection ( CLCD_DATA_PORT    , 255                   );
	DIO_voidSetPinDirection  ( CLCD_CONTROL_PORT , CLCD_RS , OUTPUT  );
	DIO_voidSetPinDirection  ( CLCD_CONTROL_PORT , CLCD_RW , OUTPUT  );
	DIO_voidSetPinDirection  ( CLCD_CONTROL_PORT , CLCD_EN , OUTPUT  );

	_delay_ms(50);
	/*FUNCTION SET COMMEND*/
	CLCD_voidSendCommend( 0b00111000 );
	_delay_ms(1);
	/* DISPLAY ON / OFF */
	CLCD_voidSendCommend( 0b00001100 );
	_delay_ms(1);
	/* DISPLAY CLEAR */
	CLCD_voidSendCommend( 0b00000001 );
	_delay_ms(2);
	/* DISPLAY ENTRY MODE */
	CLCD_voidSendCommend( 0b00000010 );
	_delay_ms(1);

}

void CLCD_voidSendData    ( u8 Copy_u8Data ){

	DIO_voidSetPortValue ( CLCD_DATA_PORT    , Copy_u8Data        );
	DIO_voidSetPinValue  ( CLCD_CONTROL_PORT , CLCD_RS , HIGH );
	DIO_voidSetPinValue  ( CLCD_CONTROL_PORT , CLCD_RW , LOW  );

	DIO_voidSetPinValue  ( CLCD_CONTROL_PORT , CLCD_EN , HIGH );
	_delay_ms(1);
	DIO_voidSetPinValue  ( CLCD_CONTROL_PORT , CLCD_EN , LOW  );
	_delay_ms(1);

}

void CLCD_voidSendCommend ( u8 Copy_u8Commend ){

	DIO_voidSetPortValue ( CLCD_DATA_PORT    , Copy_u8Commend     );
	DIO_voidSetPinValue  ( CLCD_CONTROL_PORT , CLCD_RS , LOW  );
	DIO_voidSetPinValue  ( CLCD_CONTROL_PORT , CLCD_RW , LOW  );

	DIO_voidSetPinValue  ( CLCD_CONTROL_PORT , CLCD_EN , HIGH );
	_delay_ms(1);
	DIO_voidSetPinValue  ( CLCD_CONTROL_PORT , CLCD_EN , LOW  );
	_delay_ms(1);


}
void CLCD_voidSendString  (u8 * Copy_u8ptrString ){
	u8 LOC_u8Iterator = 0 ;
	while(Copy_u8ptrString[LOC_u8Iterator] != '\0') {
		CLCD_voidSendData(Copy_u8ptrString[LOC_u8Iterator]);
		LOC_u8Iterator++ ;
	}}
void CLCD_voidSendNumber   ( u64 Copy_u64Number    ){

		u64 LOC_u64Reversed = 1 ;

		if( Copy_u64Number == 0 ) { CLCD_voidSendData('0'); }

		else{

			while( Copy_u64Number != 0 ){

				LOC_u64Reversed = ( LOC_u64Reversed * 10 ) + ( Copy_u64Number % 10 );
				Copy_u64Number /= 10 ;

			}
			while( LOC_u64Reversed != 1 ){

				CLCD_voidSendData( ( LOC_u64Reversed % 10 ) + 48 );
				LOC_u64Reversed /= 10 ;

			}

		}
}
void CLCD_voidSetPosition ( u8 Copy_u8Row , u8 Copy_u8Col ){

	if( Copy_u8Row == CLCD_ROW_1 ){

		CLCD_voidSendCommend( ( 0x80 ) + ( Copy_u8Col - 1 ) );

	}else if( Copy_u8Row == CLCD_ROW_2 ){

		CLCD_voidSendCommend( ( 0x80 ) + (64) + ( Copy_u8Col - 1 ) );

	}

}
void CLCD_voidSendExtraChar( u8* Copy_u8Pattern , u8 Copy_u8PatternNumber ,u8 Copy_u8Row , u8 Copy_u8Col )
{
	u8 Local_u8CGRAMAddress  ;
	/* Calculate the address to go*/
	if(Copy_u8PatternNumber == 0 )
	{
		Local_u8CGRAMAddress = 0 ;
	}
	else
	{
		Local_u8CGRAMAddress = Copy_u8PatternNumber * 8 ;
	}
	/* 1. Go to CGRAM */
	CLCD_voidSendCommend(Local_u8CGRAMAddress + 64);
	/*2. Draw the pattern in the CGRAM*/
	for(u8 Local_u8Iterator = 0 ; Local_u8Iterator < 8 ; Local_u8Iterator++)
	{
		CLCD_voidSendData(Copy_u8Pattern[Local_u8Iterator]);
	}
	/*3. Back to DDRAM */
	CLCD_voidSetPosition(Copy_u8Row , Copy_u8Col );
	/*4. Display the pattern written in CGRAM */
	CLCD_voidSendData(Copy_u8PatternNumber);

}
/*
void CLCD_voidSendExtraChar( u8 Copy_u8Row , u8 Copy_u8Col ){

	/* 1- Go To CGRAM            */
	//CLCD_voidSendCommend( 0b01000000 );
	/* 2- Draw Character         */
/*	for(u8 i = 0 ; i < 8 ; i++){
		CLCD_voidSendData( Arr[i] );
	}
	/* 3- Back To DDRAM          */
	/*CLCD_voidSetPosition(Copy_u8Row,Copy_u8Col);
	/* 4- Send Character Address */
	/*CLCD_voidSendData(0);

}*/








