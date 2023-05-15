/*
 * main.c
 *
 *  Created on: Apr 2, 2023
 *      Author: First
 */
#include <util/delay.h>
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../MCAL/DIO/DIO_Interface.h"
#include "../MCAL/TIMER/TIMERS_interface.h"
#include "../MCAL/ADC/ADC_interface.h"
#include "../MCAL/SPI/SPI_interface.h"
#include "../MCAL/GIE/GIE_interface.h"
#include "../HAL/CLCD/CLCD_interface.h"

int main(void)
{
	DIO_voidSetPinDirection(PORTA, PIN0 , INPUT);
	/*Initilize leds */
	DIO_voidSetPortDirection(PORTC , OUTPUT);
	DIO_voidSetPortValue(PORTC , 0 );
	/* SPI pin configuration */
	DIO_voidSetPinDirection( PORTB , PIN5 , INPUT );
	DIO_voidSetPinDirection( PORTB , PIN6 , OUTPUT  );
	DIO_voidSetPinDirection( PORTB , PIN7 , INPUT  );
	DIO_voidSetPinDirection( PORTB , PIN4 , INPUT  );
	SPI_voidSlaveInit();

	CLCD_voidInit();
	GIE_voidEnable();
	ADC_voidInit();
	u16 Loc_u16GetRead = 0 ;
	u16 Loc_u16AnalogVal ;
	u8 Local_u8SPIReading = '0'  ;
	//CLCD_voidSendData('H');
	CLCD_voidSendString((u8*)"SMART HOME");
	_delay_ms(1000);
	Local_u8SPIReading = 'n' ;
	SPI_voidAsyncSendData(0,&Local_u8SPIReading);
	while(1)
	{
		//SPI_voidMasterSendData((u8)Loc_u16AnalogVal,&Local_u8SPIReading);
		CLCD_voidSetPosition(CLCD_ROW_1 , CLCD_COL_1);
		//CLCD_voidSendData(Local_u8SPIReading);

		/*Automatic Mode*/
		if(Local_u8SPIReading == 'n' )
		{
			Loc_u16GetRead = ADC_u16GetReading(ADC_SING_END_ADC0);
			Loc_u16AnalogVal = ((u32)Loc_u16GetRead*5000) / 1024 ;
			//	DIO_voidSetPortValue(PORTC , ((u32)(Loc_u16AnalogVal *255)/5000));
			CLCD_voidSendString((u8*)"Light System ");
			CLCD_voidSetPosition(CLCD_ROW_2 , CLCD_COL_1);
			CLCD_voidSendString((u8*)"Automatic");

			if(Loc_u16AnalogVal < 500)
			{
				DIO_voidSetPinValue(PORTC , PIN0 , HIGH);
				DIO_voidSetPinValue(PORTC , PIN1 , LOW);
				DIO_voidSetPinValue(PORTC , PIN2 , LOW);
				DIO_voidSetPinValue(PORTC , PIN3 , LOW);
				DIO_voidSetPinValue(PORTC , PIN4 , LOW);
				DIO_voidSetPinValue(PORTC , PIN5 , LOW);
				DIO_voidSetPinValue(PORTC , PIN6 , LOW);
				DIO_voidSetPinValue(PORTC , PIN7 , LOW);

			}
			else if(Loc_u16AnalogVal < 1000)
			{
				DIO_voidSetPinValue(PORTC , PIN0 , HIGH);
				DIO_voidSetPinValue(PORTC , PIN1 , HIGH);
				DIO_voidSetPinValue(PORTC , PIN2 , LOW);
				DIO_voidSetPinValue(PORTC , PIN3 , LOW);
				DIO_voidSetPinValue(PORTC , PIN4 , LOW);
				DIO_voidSetPinValue(PORTC , PIN5 , LOW);
				DIO_voidSetPinValue(PORTC , PIN6 , LOW);
				DIO_voidSetPinValue(PORTC , PIN7 , LOW);

			}
			else if(Loc_u16AnalogVal < 1500)
			{
				DIO_voidSetPinValue(PORTC , PIN0 , HIGH);
				DIO_voidSetPinValue(PORTC , PIN1 , HIGH);
				DIO_voidSetPinValue(PORTC , PIN2 , HIGH);
				DIO_voidSetPinValue(PORTC , PIN3 , LOW);
				DIO_voidSetPinValue(PORTC , PIN4 , LOW);
				DIO_voidSetPinValue(PORTC , PIN5 , LOW);
				DIO_voidSetPinValue(PORTC , PIN6 , LOW);
				DIO_voidSetPinValue(PORTC , PIN7 , LOW);

			}
			else if(Loc_u16AnalogVal < 2000)
			{
				DIO_voidSetPinValue(PORTC , PIN0 , HIGH);
				DIO_voidSetPinValue(PORTC , PIN1 , HIGH);
				DIO_voidSetPinValue(PORTC , PIN2 , HIGH);
				DIO_voidSetPinValue(PORTC , PIN3 , HIGH);
				DIO_voidSetPinValue(PORTC , PIN4 , LOW);
				DIO_voidSetPinValue(PORTC , PIN5 , LOW);
				DIO_voidSetPinValue(PORTC , PIN6 , LOW);
				DIO_voidSetPinValue(PORTC , PIN7 , LOW);

			}
			else if(Loc_u16AnalogVal < 2500)
			{
				DIO_voidSetPinValue(PORTC , PIN0 , HIGH);
				DIO_voidSetPinValue(PORTC , PIN1 , HIGH);
				DIO_voidSetPinValue(PORTC , PIN2 , HIGH);
				DIO_voidSetPinValue(PORTC , PIN3 , HIGH);
				DIO_voidSetPinValue(PORTC , PIN4 , HIGH);
				DIO_voidSetPinValue(PORTC , PIN5 , LOW);
				DIO_voidSetPinValue(PORTC , PIN6 , LOW);
				DIO_voidSetPinValue(PORTC , PIN7 , LOW);

			}
			else if(Loc_u16AnalogVal < 3400)
			{
				DIO_voidSetPinValue(PORTC , PIN0 , HIGH);
				DIO_voidSetPinValue(PORTC , PIN1 , HIGH);
				DIO_voidSetPinValue(PORTC , PIN2 , HIGH);
				DIO_voidSetPinValue(PORTC , PIN3 , HIGH);
				DIO_voidSetPinValue(PORTC , PIN4 , HIGH);
				DIO_voidSetPinValue(PORTC , PIN5 , HIGH);
				DIO_voidSetPinValue(PORTC , PIN6 , LOW);
				DIO_voidSetPinValue(PORTC , PIN7 , LOW);

			}
			else if(Loc_u16AnalogVal < 4000)
			{
				DIO_voidSetPinValue(PORTC , PIN0 , HIGH);
				DIO_voidSetPinValue(PORTC , PIN1 , HIGH);
				DIO_voidSetPinValue(PORTC , PIN2 , HIGH);
				DIO_voidSetPinValue(PORTC , PIN3 , HIGH);
				DIO_voidSetPinValue(PORTC , PIN4 , HIGH);
				DIO_voidSetPinValue(PORTC , PIN5 , HIGH);
				DIO_voidSetPinValue(PORTC , PIN6 , HIGH);
				DIO_voidSetPinValue(PORTC , PIN7 , LOW);

			}
			else if (Loc_u16AnalogVal < 4200)
			{
				DIO_voidSetPinValue(PORTC , PIN0 , HIGH);
				DIO_voidSetPinValue(PORTC , PIN1 , HIGH);
				DIO_voidSetPinValue(PORTC , PIN2 , HIGH);
				DIO_voidSetPinValue(PORTC , PIN3 , HIGH);
				DIO_voidSetPinValue(PORTC , PIN4 , HIGH);
				DIO_voidSetPinValue(PORTC , PIN5 , HIGH);
				DIO_voidSetPinValue(PORTC , PIN6 , HIGH);
				DIO_voidSetPinValue(PORTC , PIN7 , HIGH);
			}
		}
		/*LEDS ON */
		else if (Local_u8SPIReading == 'j' ) // HIGH
		{
			DIO_voidSetPortValue(PORTC , 255 );
			CLCD_voidSendString((u8*)"Light System ON ");
CLCD_voidSetPosition(CLCD_ROW_2 , CLCD_COL_1);
CLCD_voidSendString((u8*)"                 ");
		}
		/*LEDS OFF */
		else if (Local_u8SPIReading == 'l' ) // LOW
		{
			DIO_voidSetPortValue(PORTC , 0 );
			CLCD_voidSendString((u8*)"Light System OFF ");
			CLCD_voidSetPosition(CLCD_ROW_2 , CLCD_COL_1);
			CLCD_voidSendString((u8*)"                 ");
		}

	}
	return 0 ;
}
