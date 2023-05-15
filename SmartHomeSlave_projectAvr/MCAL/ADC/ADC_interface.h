/***************************************************************/
/**SWC :       ADC                                   **********/
/**Author :   Mohamed Khaled Elfawakhry              ***********/
/**Version :       1.0                               ***********/
/**Date :            2/4/2023                      ************/
/***************************************************************/
/*      File Gaurd    */
#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

#define ADC_SING_END_ADC0       0
#define ADC_SING_END_ADC1       1
#define ADC_SING_END_ADC2       2
#define ADC_SING_END_ADC3       3
#define ADC_SING_END_ADC4       4
#define ADC_SING_END_ADC5       5
#define ADC_SING_END_ADC6       6
#define ADC_SING_END_ADC7       7

void ADC_voidInit(void);

u16 ADC_u16GetReading(u8 Copy_u8Channel);


#endif
