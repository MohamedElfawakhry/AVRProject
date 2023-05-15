/***************************************************************/
/**SWC :       ADC                                   **********/
/**Author :   Mohamed Khaled Elfawakhry              ***********/
/**Version :       1.0                               ***********/
/**Date :            2/4/2023                      ************/
/***************************************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"

void ADC_voidInit(void)
{
    #if ADC_REF_SELEC == AREF
    CLR_BIT(ADMUX_REG , 7);
    CLR_BIT(ADMUX_REG , 6);
    #elif ADC_REF_SELEC == AVCC
    CLR_BIT(ADMUX_REG , 7);
    SET_BIT(ADMUX_REG , 6);
    #elif ADC_REF_SELEC == INTERNAL_2_56V
    SET_BIT(ADMUX_REG , 7);
    SET_BIT(ADMUX_REG , 6);
    #endif
    /************************************************/
    #if ADC_ADLAR == LEFT_ADJUST
    SET_BIT(ADMUX_REG , 5);
    #elif ADC_ADLAR == RIGHT_ADJUST
    CLR_BIT(ADMUX_REG, 5);
    #endif
    /************************************************/
    #if ADC_EN == ENABLE
    SET_BIT(ADCSRA_REG , 7 );
    #elif ADC_EN == DISABLE
    CLR_BIT(ADCSRA_REG , 7 );
    #endif
   /************************************************/
    #if ADC_TRIG_EN == ENABLE
    SET_BIT(ADCSRA_REG , 5 );
    #elif ADC_TRIG_EN == DISABLE
    CLR_BIT(ADCSRA_REG , 5 );
    #endif
    /************************************************/
    #if ADC_INT_EN == ENABLE
    SET_BIT(ADCSRA_REG , 3 );
    #elif ADC_INT_EN == DISABLE
    CLR_BIT(ADCSRA_REG , 3 );
    #endif
    /************************************************/
    /*Choose Prescaler */
    ADCSRA_REG &= PRESCALER_MASK ;
    #if ADC_PRESCALER == ADC_PRE_2
    SET_BIT(ADCSRA_REG , 0 );
    CLR_BIT(ADCSRA_REG , 1);
    CLR_BIT(ADCSRA_REG , 2);
    #elif ADC_PRESCALER == ADC_PRE_4
    CLR_BIT(ADCSRA_REG , 0 );
    SET_BIT(ADCSRA_REG , 1);
    CLR_BIT(ADCSRA_REG , 2);
    #elif ADC_PRESCALER == ADC_PRE_8
    SET_BIT(ADCSRA_REG , 0 );
    SET_BIT(ADCSRA_REG , 1);
    CLR_BIT(ADCSRA_REG , 2);
    #elif ADC_PRESCALER == ADC_PRE_16
    CLR_BIT(ADCSRA_REG , 0 );
    CLR_BIT(ADCSRA_REG , 1);
    SET_BIT(ADCSRA_REG , 2);
    #elif ADC_PRESCALER == ADC_PRE_32
    SET_BIT(ADCSRA_REG , 0 );
    CLR_BIT(ADCSRA_REG , 1);
    SET_BIT(ADCSRA_REG , 2);
    #elif ADC_PRESCALER == ADC_PRE_64
    CLR_BIT(ADCSRA_REG , 0 );
    SET_BIT(ADCSRA_REG , 1);
    SET_BIT(ADCSRA_REG , 2);
    #elif ADC_PRESCALER == ADC_PRE_128
    SET_BIT(ADCSRA_REG , 0 );
    SET_BIT(ADCSRA_REG , 1);
    SET_BIT(ADCSRA_REG , 2);
    #endif
    /************************************************/
    
    /* Free Running AutoTrigger */
    CLR_BIT(SFIOR_REG , 7);
    CLR_BIT(SFIOR_REG , 6);
    CLR_BIT(SFIOR_REG , 5);
}

u16 ADC_u16GetReading(u8 Copy_u8Channel)
{
    u16 Local_u16ReturnedVal ; 

    /* Clear Mux */
    ADMUX_REG &= 0b11100000;
    /*Set Channel in Mux */
    switch (Copy_u8Channel)
    {
    case ADC_SING_END_ADC0:
        ADMUX_REG |= 0x00;
        break;
    case ADC_SING_END_ADC1:
       ADMUX_REG |= 0x01;
        break;
    case ADC_SING_END_ADC2:
        ADMUX_REG |= 0x02;
        break;
    case ADC_SING_END_ADC3:
        ADMUX_REG |= 0x03;
        break;
    case ADC_SING_END_ADC4:
        ADMUX_REG |= 0x04;
    break;
    case ADC_SING_END_ADC5:
        ADMUX_REG |= 0x05;
        break;
    case ADC_SING_END_ADC6:
        ADMUX_REG |= 0x06;
        break;
    case ADC_SING_END_ADC7:
        ADMUX_REG |= 0x07;
        break;
    default:
        break;
    }

    /*Start Conversion*/
    SET_BIT(ADCSRA_REG , 6);
    /*Polling on the Flag*/
    while(GET_BIT(ADCSRA_REG , 4) ==0);
    /*Clear The Flag */
    SET_BIT(ADCSRA_REG , 4);
    /*Get Reading then return it*/
    #if ADC_ADLAR == RIGHT_ADJUST
    Local_u16ReturnedVal = ADCL_REG | (ADCH_REG << 8)  ;
    #elif ADC_ADLAR == LEFT_ADJUST
    Local_u16ReturnedVal = ADCH_REG << 2 ;
    #endif

    return Local_u16ReturnedVal ;
}
