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

#include "../MCAL/GIE/GIE_interface.h"
#include "../MCAL/UART/UART_interface.h"
#include "../MCAL/SPI/SPI_interface.h"
#include "../HAL/CLCD/CLCD_interface.h"


#define USER_1		{'M','H','M','D','#'}
#define USER_2		{'A','M','#'}
#define USER_3		{'Y','O','Y','O','Z','#'}
#define PASSWORD_1	{'1','2','3','4','#'}
#define PASSWORD_2	{'1','2','3','#'}
#define PASSWORD_3  {'1','2','#'}
#define PASS		1
#define FAIL		0
u8 LogIn_Au8Users [10][10]={ USER_1 , USER_2 , USER_3 };
u8 LogIn_Au8Pw   [10][10]={ PASSWORD_1 ,PASSWORD_2 , PASSWORD_3};
u8 LogInFunction (void);
u8 SolinedOpen ( void );
void Fan_Function(void);
u8 GetTempSensReading(void);
void SendTempSensToUART(u8 Copy_u8Temp );

volatile u8 Glo_u8RecievedUARTData = 0 ;
int main(void)
{

	/* SPI pin configuration */
	DIO_voidSetPinDirection( PORTB , PIN5 , OUTPUT );
	DIO_voidSetPinDirection( PORTB , PIN6 , INPUT  );
	DIO_voidSetPinDirection( PORTB , PIN7 , OUTPUT  );
	DIO_voidSetPinDirection( PORTB , PIN4 , OUTPUT  );
	//DIO_voidSetPinValue(PORTB , PIN4 , HIGH );

	DIO_voidSetPinDirection(PORTD , PIN4 , OUTPUT);
	DIO_voidSetPinDirection(PORTD , PIN3 , OUTPUT); //Buzzer
	DIO_voidSetPinDirection(PORTD , PIN2 , OUTPUT); // Fan

	DIO_voidSetPinDirection(PORTD , PIN5 , OUTPUT);

	CLCD_voidInit();
	UART_voidInit();
	SPI_voidMasterInit();
	ADC_voidInit();

	TIMERS_voidTIMER1Init();
	TIMERS_voidTIMER1SetICR1Value(20000);
	CLCD_voidSendString((u8*)"SMART HOME");
	_delay_ms(500);
	CLCD_voidSendCommend(0x01);
	u8 LogIn_u8State = LogInFunction();


	UART_voidAsyncRecieveData(&Glo_u8RecievedUARTData);
	GIE_voidEnable();
	u8 Local_u8SolinedState ;
	u8 SystemTemp ;
	while(1)
	{
		if(LogIn_u8State == PASS)
		{
			Local_u8SolinedState = SolinedOpen();

			if(SystemTemp < 40 )
			{
				CLCD_voidSetPosition(CLCD_ROW_1 , CLCD_COL_1);
				CLCD_voidSendString((u8*)"Soliniod :");

			}
			if(Local_u8SolinedState == PASS && SystemTemp < 40)
			{
				DIO_voidSetPinValue(PORTD , PIN4 , HIGH);
				CLCD_voidSetPosition(CLCD_ROW_1 , CLCD_COL_11);
				CLCD_voidSendString((u8*)"Open");
				/* Open Door .. Servo */
				TIMERS_voidTIMER1SetPinACompMatch(1500 - 1 );
				_delay_ms(10);
			}
			else if(Local_u8SolinedState == FAIL && SystemTemp < 40)
			{

				DIO_voidSetPinValue(PORTD , PIN4 , LOW);
				CLCD_voidSetPosition(CLCD_ROW_1 , CLCD_COL_11);
				CLCD_voidSendString((u8*)"Closed");
				TIMERS_voidTIMER1SetPinACompMatch(1000 - 1);
				_delay_ms(10);

			}

			/*For LM35 & TEMP READING */
			SystemTemp = GetTempSensReading();
			SendTempSensToUART(SystemTemp);
			CLCD_voidSetPosition(CLCD_ROW_2 , CLCD_COL_1);
			CLCD_voidSendString((u8*)"Temp :");
			CLCD_voidSendData( ( SystemTemp / 10) + '0' );
			CLCD_voidSendData( ( (SystemTemp) - (( SystemTemp / 10) * 10) ) + '0' );
			/* If Temp > 35 --> Open Buzzer */
			if(SystemTemp > 40 )
			{
				DIO_voidSetPinValue(PORTD , PIN3 , HIGH);
				CLCD_voidSetPosition(CLCD_ROW_1 , CLCD_COL_1);
				CLCD_voidSendString((u8*)"                 ");
				CLCD_voidSetPosition(CLCD_ROW_1 , CLCD_COL_1);
				CLCD_voidSendString((u8*)"FFFIIRREEE");
			}
			else
			{
				DIO_voidSetPinValue(PORTD , PIN3 , LOW);
			}
			if(SystemTemp > 30)
			{
				DIO_voidSetPinValue(PORTD , PIN2 , HIGH);

			}
			else
			{
				DIO_voidSetPinValue(PORTD , PIN2 , LOW);
				Fan_Function();
			}
		}

		/* Send Slave Light System State  */
		if(Glo_u8RecievedUARTData == '5' ||Glo_u8RecievedUARTData == '6'||Glo_u8RecievedUARTData == '7' )
		{
			SPI_voidMasterSendData(Glo_u8RecievedUARTData , NULL );
		//	CLCD_voidSendCommend(0x01);
			//CLCD_voidSendData(Glo_u8RecievedUARTData);
			_delay_ms(500);
		}
	}
	return 0 ;
}

u8 LogInFunction (void)
{
	u8 Local_u8UserPass = 0 ;
	u8 Local_u8PwPass = 0 ;
	u8 Local_u8UartRecievedData = 0  ;
	u8 Local_Au8Recieved[10] ;
	u8 Local_u8Iterator = 0 ;
	u8 Local_u8Iterator2 = 0 ;
	u8 Local_u8Id = 0 ;
	u8 Local_u8UserIterator = 0 ;
	while(Local_u8UserIterator < 3)
	{
		CLCD_voidSetPosition(CLCD_ROW_1 , CLCD_COL_1);
		CLCD_voidSendString((u8*)"Enter UserName");
		/* Getting The User from UART */

		while(Local_u8UartRecievedData != '#')
		{
			UART_voidRecieveData(&Local_u8UartRecievedData);
			Local_Au8Recieved[Local_u8Iterator]  = Local_u8UartRecievedData ;
			Local_u8Iterator++ ;
		}

		/*Check About UserName for 3 Times*/

		while(Local_u8Iterator > Local_u8Iterator2 && Local_u8Id < 5)
		{
			if(Local_Au8Recieved[ Local_u8Iterator2 ] != LogIn_Au8Users [Local_u8Id][Local_u8Iterator2] )
			{
				Local_u8UserPass = FAIL ;
				Local_u8Id++ ;
				Local_u8Iterator2 =  0 ;
				continue ;
			}
			else
			{
				Local_u8UserPass = PASS ;
			}

			Local_u8Iterator2++;
		}

		/* Check For UserName */
		CLCD_voidSendCommend(0x01);

		if(Local_u8UserPass == PASS )
		{
			CLCD_voidSendString((u8*)"Enter Password");
			break;
		}
		else if (Local_u8UserPass == FAIL )
		{
			CLCD_voidSendString((u8*)"Wrong UserName");

			CLCD_voidSetPosition(CLCD_ROW_2 , CLCD_COL_1);
			CLCD_voidSendString((u8*)"Trials =");
			CLCD_voidSendData((3-Local_u8UserIterator-1) +'0');
			Local_u8Id = 0 ;
			Local_u8Iterator = 0 ;
			Local_u8Iterator2 = 0 ;
		}
		Local_u8UartRecievedData= 0 ;

		Local_u8UserIterator++;
	}
	if(Local_u8UserIterator == 3 && Local_u8UserPass == FAIL )
	{
		CLCD_voidSendCommend(0x01);
		CLCD_voidSendString((u8*)"SHUTDOWN SYSTEM");
	}

	/*Getting Password from UART */
	if(Local_u8UserPass == PASS)
	{
		u8 Local_Au8RecievedPw[10] ;
		Local_u8Iterator = 0 ;
		Local_u8UartRecievedData = 0 ;
		while(Local_u8UartRecievedData != '#')
		{
			UART_voidRecieveData(&Local_u8UartRecievedData);
			Local_Au8RecievedPw[Local_u8Iterator]  = Local_u8UartRecievedData ;
			Local_u8Iterator++ ;
		}
		Local_u8Iterator2 = 0 ;
		while(Local_u8Iterator > Local_u8Iterator2 )
		{
			if(Local_Au8RecievedPw[ Local_u8Iterator2 ] != LogIn_Au8Pw [Local_u8Id][Local_u8Iterator2] )
			{
				Local_u8PwPass = FAIL ;
				break ;
			}
			else
			{
				Local_u8PwPass = PASS ;
			}

			Local_u8Iterator2++;
		}
		CLCD_voidSendCommend(0x01);
		if(Local_u8PwPass == PASS )
		{
			CLCD_voidSendString((u8*)"Welcome");
			_delay_ms(500);

		}
		else
		{
			CLCD_voidSendString((u8*)"Wrong Password");
			CLCD_voidSetPosition(CLCD_ROW_2 , CLCD_COL_1);
			for(u8 i = 0 ; i < 5 ; i++)
			{
				CLCD_voidSendData(Local_Au8RecievedPw[ i ]);
			}
		}
	}
	return ( Local_u8UserPass && Local_u8PwPass) ;
}
u8 SolinedOpen ( void )
{
	u8 Local_u8State = 0xff ;
	if(Glo_u8RecievedUARTData == '1')
	{

		Local_u8State = PASS ;
	}
	else if(Glo_u8RecievedUARTData == '0')
	{

		Local_u8State = FAIL ;

	}
	return Local_u8State  ;
}
u8 GetTempSensReading(void)
{
	u16 Local_u16Reading = ADC_u16GetReading(ADC_SING_END_ADC7);
	u16 Local_u16AnalogReading = ((u32)Local_u16Reading* 5000 ) / 1024 ;
	u8  Local_u8Temp = Local_u16AnalogReading / 10 ;
	return Local_u8Temp ;
}
void SendTempSensToUART(u8 Copy_u8Temp )
{
	UART_voidSendData( ( Copy_u8Temp / 10) + '0' );
	UART_voidSendData( ( (Copy_u8Temp) - (( Copy_u8Temp / 10) * 10) ) + '0' );
}
void Fan_Function(void)
{
	if(Glo_u8RecievedUARTData == '2' ) // open
	{
		DIO_voidSetPinValue(PORTD , PIN2 , HIGH);
	}
	else if (Glo_u8RecievedUARTData == '3') // closed
	{
		DIO_voidSetPinValue(PORTD , PIN2 , LOW);
	}
}
