/***************************************************************/
/**SWC :       ADC                                   **********/
/**Author :   Mohamed Khaled Elfawakhry              ***********/
/**Version :       1.0                               ***********/
/**Date :            2/4/2023                      ************/
/***************************************************************/
/*      File Gaurd    */
#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

#define ADMUX_REG        *((volatile u8*)0x27)
#define ADCSRA_REG       *((volatile u8*)0x26)
#define ADC_REG         *((volatile u16*)0x24)
#define SFIOR_REG        *((volatile u8*)0x50)
#define ADCL_REG        *((volatile u8*)0x24)
#define ADCH_REG        *((volatile u8*)0x25)


#define PRESCALER_MASK		0b11111000

#endif
