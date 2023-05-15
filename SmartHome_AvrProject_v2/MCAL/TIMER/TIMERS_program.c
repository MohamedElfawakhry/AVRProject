
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../DIO/DIO_Interface.h"


#include "TIMERS_interface.h"
#include "TIMERS_private.h"
#include "TIMERS_config.h"

void (*pNotificationT0OVF)(void) = NULL ;
void (*pNotificationT0CTC)(void) = NULL ;
void (*pNotificationT1ICU)(void) = NULL ;
void TIMERS_voidTIMER0Init(void)
{
//	/*Normal Mode (OVF MODE)*/
//	CLR_BIT(TIMERS_TCCR0_REG , 6);
//	CLR_BIT(TIMERS_TCCR0_REG , 3);

	/*Compare Match Mode (CTC MODE)*/
	CLR_BIT(TIMERS_TCCR0_REG , 6);
	SET_BIT(TIMERS_TCCR0_REG , 3);

//	/*	FAST PWM MODE */
//	SET_BIT(TIMERS_TCCR0_REG , 6);
//	SET_BIT(TIMERS_TCCR0_REG , 3);
//
//	/* Clear OC0 on compare , Set on Top*/
//	CLR_BIT(TIMERS_TCCR0_REG , 4);
//	SET_BIT(TIMERS_TCCR0_REG , 5);
//	/* Prescaler value */
	CLR_BIT(TIMERS_TCCR0_REG ,2);
	SET_BIT(TIMERS_TCCR0_REG ,1);
	CLR_BIT(TIMERS_TCCR0_REG ,0);
	
	/*Enable Timer0 interrupt PIE (OVF)*/
//	SET_BIT(TIMERS_TIMSK_REG , 0 );
	/*Enable Timer0 interrupt PIE (CTC)*/
	SET_BIT(TIMERS_TIMSK_REG , 1 );
}
void TIMERS_voidT1SetBusyWait(u32 Copy_u32MilliSeconds)
{
	u64 Local_u64SWCounter = 0 ;
	u64 Local_u64Iterator = 0 ;
	Local_u64SWCounter = (Copy_u32MilliSeconds*1000) / (TIMER0_CTC_TIME );
	for(Local_u64Iterator = 0 ; Local_u64Iterator < Local_u64SWCounter ; Local_u64Iterator++)
	{
		while(GET_BIT(TIMERS_TIFR_REG , 1) == 0 );
		SET_BIT(TIMERS_TIFR_REG , 1);
	}
}
void TIMERS_voidSetPreloadValueTIMER0OVF(u8 Copy_u8PreloadValue)
{
	TIMERS_TCNT0_REG = Copy_u8PreloadValue ;
}
void TIMERS_voidSetCompareMatchValue (u8 Copy_u8CompareMatchValue )
{
	TIMERS_OCR0_REG = Copy_u8CompareMatchValue ;
}
void TIMERS_voidSetCallBackTIMER0OVF(void(*Lpf)(void))
{
	pNotificationT0OVF = Lpf ;
}
void TIMERS_voidSetCallBackTIMER0CTC (void(*Lpf)(void))
{
	pNotificationT0CTC = Lpf ;
}

void __vector_11 (void) 	__attribute__((signal))		;
void __vector_11 (void)
{
	static u16 Local_u16Counter = 0 ;
	Local_u16Counter++ ;
	if(Local_u16Counter == TIMERS_T0OVF_SWCOUNTER)
	{
		pNotificationT0OVF() ;
		Local_u16Counter = 0 ;
		TIMERS_voidSetPreloadValueTIMER0OVF(TIMERS_T0_PRELOADVALUE);
	}

}
void __vector_10 (void) 	__attribute__((signal))		;
void __vector_10 (void)
{

	if(pNotificationT0CTC != NULL )
	{
		pNotificationT0CTC() ;
	}

}
/*=================================================================================================*/
void TIMERS_voidTIMER1Init(void)
{
	/* Timer 1 channel A , Fast PWM */
	//TIMERS_TCCR1A_REG = 0b10000010 ;
	//TIMERS_TCCR1B_REG = 0b00011010 ; //prescaler 8
	//TIMERS_OCR1A  = 
	//TIMERS_ICR1_REG = 20000 ;
	/************************************************************/
	/* OC1A Configuration*/
	#if	TIMRES_OC1A_CONFIG == TIMERS_OC_DISCONNECTED
	CLR_BIT(TIMERS_TCCR1A_REG , TIMERS_TCCR1A_COM1A0);
	CLR_BIT(TIMERS_TCCR1A_REG , TIMERS_TCCR1A_COM1A1);
	#elif TIMRES_OC1A_CONFIG == TIMERS_NON_INVERTING_MODE
	CLR_BIT(TIMERS_TCCR1A_REG , TIMERS_TCCR1A_COM1A0);
	SET_BIT(TIMERS_TCCR1A_REG , TIMERS_TCCR1A_COM1A1);
	#elif  TIMRES_OC1A_CONFIG == TIMERS_INVERTING_MODE
	SET_BIT(TIMERS_TCCR1A_REG , TIMERS_TCCR1A_COM1A0);
	SET_BIT(TIMERS_TCCR1A_REG , TIMERS_TCCR1A_COM1A1);
	#endif
	/* OC1B Configuration*/
	#if	TIMERS_OC1B_CONFIG == TIMERS_OC_DISCONNECTED
	CLR_BIT(TIMERS_TCCR1A_REG , TIMERS_TCCR1A_COM1B0);
	CLR_BIT(TIMERS_TCCR1A_REG , TIMERS_TCCR1A_COM1B1);
	#elif TIMERS_OC1B_CONFIG == TIMERS_NON_INVERTING_MODE
	CLR_BIT(TIMERS_TCCR1A_REG , TIMERS_TCCR1A_COM1B0);
	SET_BIT(TIMERS_TCCR1A_REG , TIMERS_TCCR1A_COM1B1);
	#elif  TIMERS_OC1B_CONFIG == TIMERS_INVERTING_MODE
	SET_BIT(TIMERS_TCCR1A_REG , TIMERS_TCCR1A_COM1B0);
	SET_BIT(TIMERS_TCCR1A_REG , TIMERS_TCCR1A_COM1B1);
	#endif
	/************************************************************/
	/*Disable Force Pins for Channel A&B*/
	CLR_BIT(TIMERS_TCCR1A_REG , TIMERS_TCCR1A_FOC1A);
	CLR_BIT(TIMERS_TCCR1A_REG , TIMERS_TCCR1A_FOC1B);
	/************************************************************/
	/* INPUT Capture Noise Cancler */
	#if TIMERS_T1_ICU_NOISE_CANCLER == ENABLE
	SET_BIT(TIMERS_TCCR1B_REG , TIMERS_TCCR1B_ICNC1);
	#elif TIMERS_T1_ICU_NOISE_CANCLER == DISABLE
	CLR_BIT(TIMERS_TCCR1B_REG , TIMERS_TCCR1B_ICNC1);
	#endif
	/************************************************************/
	/*  CLOCK SET ( PRESCALER ) */
	#if TIMERS_T1_CLK_SET == TIMERS_T1_NO_CLOCK_SOURCE
	CLR_BIT(TIMERS_TCCR1B_REG , TIMERS_TCCR1B_CS10);
	CLR_BIT(TIMERS_TCCR1B_REG , TIMERS_TCCR1B_CS11);
	CLR_BIT(TIMERS_TCCR1B_REG , TIMERS_TCCR1B_CS12);
	#elif TIMERS_T1_CLK_SET == TIMERS_T1_CLK_1
	SET_BIT(TIMERS_TCCR1B_REG , TIMERS_TCCR1B_CS10);
	CLR_BIT(TIMERS_TCCR1B_REG , TIMERS_TCCR1B_CS11);
	CLR_BIT(TIMERS_TCCR1B_REG , TIMERS_TCCR1B_CS12);
	#elif TIMERS_T1_CLK_SET == TIMERS_T1_CLK_8
	CLR_BIT(TIMERS_TCCR1B_REG , TIMERS_TCCR1B_CS10);
	SET_BIT(TIMERS_TCCR1B_REG , TIMERS_TCCR1B_CS11);
	CLR_BIT(TIMERS_TCCR1B_REG , TIMERS_TCCR1B_CS12);
	#elif TIMERS_T1_CLK_SET == TIMERS_T1_CLK_64
	SET_BIT(TIMERS_TCCR1B_REG , TIMERS_TCCR1B_CS10);
	SET_BIT(TIMERS_TCCR1B_REG , TIMERS_TCCR1B_CS11);
	CLR_BIT(TIMERS_TCCR1B_REG , TIMERS_TCCR1B_CS12);
	#elif TIMERS_T1_CLK_SET == TIMERS_T1_CLK_256
	CLR_BIT(TIMERS_TCCR1B_REG , TIMERS_TCCR1B_CS10);
	CLR_BIT(TIMERS_TCCR1B_REG , TIMERS_TCCR1B_CS11);
	SET_BIT(TIMERS_TCCR1B_REG , TIMERS_TCCR1B_CS12);
	#elif TIMERS_T1_CLK_SET == TIMERS_T1_CLK_1024
	SET_BIT(TIMERS_TCCR1B_REG , TIMERS_TCCR1B_CS10);
	CLR_BIT(TIMERS_TCCR1B_REG , TIMERS_TCCR1B_CS11);
	SET_BIT(TIMERS_TCCR1B_REG , TIMERS_TCCR1B_CS12);
	#endif
	/************************************************************/
	/*  Wave Generation Mode   */
	#if TIMERS_T1_WAVE_GENERATION_MODE == TIMERS_T1_NORMAL
	CLR_BIT(TIMERS_TCCR1A_REG,TIMERS_TCCR1A_WGM10);
	CLR_BIT(TIMERS_TCCR1A_REG,TIMERS_TCCR1A_WGM11);
	CLR_BIT(TIMERS_TCCR1B_REG,TIMERS_TCCR1B_WGM12);
	CLR_BIT(TIMERS_TCCR1B_REG,TIMERS_TCCR1B_WGM13);
	#elif TIMERS_T1_WAVE_GENERATION_MODE == TIMERS_T1_FAST_PWM_TOP_ICR1
	CLR_BIT(TIMERS_TCCR1A_REG,TIMERS_TCCR1A_WGM10);
	SET_BIT(TIMERS_TCCR1A_REG,TIMERS_TCCR1A_WGM11);
	SET_BIT(TIMERS_TCCR1B_REG,TIMERS_TCCR1B_WGM12);
	SET_BIT(TIMERS_TCCR1B_REG,TIMERS_TCCR1B_WGM13);
	#endif


}
void TIMERS_voidICUInterruptEnable(void)
{
	SET_BIT(TIMERS_TIMSK_REG , 5);
}

void TIMERS_voidICUInterruptDisable(void)
{
	CLR_BIT(TIMERS_TIMSK_REG , 5);
}

void TIMERS_voidTIMER1SetPinACompMatch (u16 Copy_u16Value )
{
	TIMERS_OCR1A_REG = Copy_u16Value ;
}
void TIMERS_voidTIMER1SetICR1Value(u16 Copy_u16Value)
{
	TIMERS_ICR1_REG = Copy_u16Value ;
}
void TIMERS_voidICUEdgeSelect(u8 Copy_u8Edge )
{
	if(Copy_u8Edge == TIMERS_ICU_RAISINGEDGE)
	{
		SET_BIT(TIMERS_TCCR1B_REG , 6);
	}
	else if(Copy_u8Edge == TIMERS_ICU_FALLINGEDGE)
	{
		CLR_BIT(TIMERS_TCCR1B_REG , 6);
	}
}
u16 TIMERS_u16ICUGetReading(void)
{
	return TIMERS_ICR1_REG ;
}
void TIMERS_voidICUSetCallBack(void(*Lpf)(void))
{
	pNotificationT1ICU = Lpf ;
}

void __vector_6 (void) __attribute__((signal));
void __vector_6 (void)
{
	if(pNotificationT1ICU != NULL)
	{
		pNotificationT1ICU();
	}
}
/*=================================================================================================*/


		
