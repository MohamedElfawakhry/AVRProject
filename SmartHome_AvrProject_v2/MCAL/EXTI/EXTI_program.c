
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"


#include "../DIO/DIO_Interface.h"
#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"

void (*Glo_Apf[3])(void) = {NULL , NULL , NULL};

void EXTI_voidInit(void)
{
#if INT_ENABLE == INT0
	/* DIO Pin Configuration */
	DIO_voidSetPinDirection(PORTD , PIN2 , INPUT);
	SET_BIT(GICR_REG , 6);
#if INT_SENSE_CONTROL == FALLING_EDGE
	SET_BIT(MCUCR_REG , 1 );
	CLR_BIT(MCUCR_REG , 0);
	DIO_voidSetPinValue(PORTD , PIN2 , HIGH);
#elif INT_SENSE_CONTROL == RAISING_EDGE
	SET_BIT(MCUCR_REG , 1 );
	SET_BIT(MCUCR_REG , 0);
#elif INT_SENSE_CONTROL == LOW_LEVEL
	CLR_BIT(MCUCR_REG , 1 );
	CLR_BIT(MCUCR_REG , 0);

#elif INT_SENSE_CONTROL == ON_CHANGE
	CLR_BIT(MCUCR_REG , 1 );
	SET_BIT(MCUCR_REG , 0);
#endif

#elif INT_ENABLE == INT1
	DIO_voidSetPinDirection(PORTD , PIN3 , INPUT);
	SET_BIT(GICR_REG , 7);
#if (INT_SENSE_CONTROL == FALLING_EDGE)
	SET_BIT(    MCUCR_REG , 3   );
	CLR_BIT(    MCUCR_REG , 2   );
	DIO_voidSetPinValue(PORTD , PIN2 , HIGH);
#elif INT_SENSE_CONTROL == RAISING_EDGE
	SET_BIT(    MCUCR_REG , 3   );
	SET_BIT(    MCUCR_REG , 2   );
#elif INT_SENSE_CONTROL == LOW_LEVEL
	CLR_BIT(    MCUCR_REG , 3   );
	CLR_BIT(    MCUCR_REG , 2)  ;

#elif INT_SENSE_CONTROL == ON_CHANGE
	CLR_BIT(    MCUCR_REG , 3   );
	SET_BIT(    MCUCR_REG , 2   );
#endif
#elif INT_ENABLE == INT2
	SET_BIT(GICR_REG , 5);
#if INT_SENSE_CONTROL == FALLING_EDGE
	CLR_BIT(    MCUCSR_REG , 6   );
#elif INT_SENSE_CONTROL == RAISING_EDGE
	SET_BIT(    MCUCSR_REG , 6   );
#endif
#endif
}
void EXTI_voidEnable  (u8 Copy_u8IntId , u8 Copy_u8SenseControl )
{
	switch(Copy_u8IntId)
	{
	case INT0 : /*Enable INT0*/
		SET_BIT(GICR_REG , 6 );
		switch(Copy_u8SenseControl)
		{
			case FALLING_EDGE :
				SET_BIT(MCUCR_REG , 1 );
				CLR_BIT(MCUCR_REG , 0);
				break;
			case RAISING_EDGE :
				SET_BIT(MCUCR_REG , 1 );
				SET_BIT(MCUCR_REG , 0);
				break;
			case LOW_LEVEL :
				CLR_BIT(MCUCR_REG , 1 );
				CLR_BIT(MCUCR_REG , 0);
				break;
			case ON_CHANGE :
				CLR_BIT(MCUCR_REG , 1 );
				SET_BIT(MCUCR_REG , 0);
				break;
			default : break;
		}
		break;
		case INT1 :
			SET_BIT(GICR_REG , 7);
			switch(Copy_u8SenseControl)
			{
				case FALLING_EDGE :
					SET_BIT(MCUCR_REG , 3 );
					CLR_BIT(MCUCR_REG , 2);
					break;
				case RAISING_EDGE :
					SET_BIT(MCUCR_REG , 3 );
					SET_BIT(MCUCR_REG , 2);
					break;
				case LOW_LEVEL :
					CLR_BIT(MCUCR_REG , 3 );
					CLR_BIT(MCUCR_REG , 2);
					break;
				case ON_CHANGE :
					CLR_BIT(MCUCR_REG , 3 );
					SET_BIT(MCUCR_REG , 2);
					break;
				default : break;
			}
			break;
			case INT2 :
				SET_BIT(GICR_REG , 5);
				switch(Copy_u8SenseControl)
				{
					case FALLING_EDGE :

						CLR_BIT(MCUCSR_REG , 6);
						break;
					case RAISING_EDGE :
						SET_BIT(MCUCSR_REG , 6);
						break;
				}

				break;
				default:
					break;
	}
}
void EXTI_voidDisable (u8 Copy_u8IntId)
{
	switch(Copy_u8IntId)
	{
	case INT0 :
		CLR_BIT(GICR_REG , 6);
		break;
	case INT1 :
		CLR_BIT(GICR_REG , 7);
		break ;
	case INT2 :
		CLR_BIT(GICR_REG , 5);
		break;
	default : break;
	}
}

void EXTI_voidSetCallBack(void (*Local_pf)(void) , u8 Copy_u8IntId)
{
	switch(Copy_u8IntId)
	{
	case INT0 :
		Glo_Apf[0] = Local_pf ;
		break;
	case INT1 :
		Glo_Apf[1] = Local_pf ;
		break ;
	case INT2 :
		Glo_Apf[2] = Local_pf ;
		break;
	default : break;
	}
}
/* ISR for INT0 */
void __vector_1(void)	__attribute__((signal));
void __vector_1(void)
{
	if(Glo_Apf[0] != NULL)
	{
		Glo_Apf[0]() ;
	}
}
/* ISR for INT1 */
void __vector_2(void)	__attribute__((signal));
void __vector_2(void)
{
	if(Glo_Apf[1] != NULL)
	{
		Glo_Apf[1]() ;
	}
}
/* ISR for INT0 */
void __vector_3(void)	__attribute__((signal));
void __vector_3(void)
{
	if(Glo_Apf[2] != NULL)
	{
		Glo_Apf[2]() ;
	}
}
