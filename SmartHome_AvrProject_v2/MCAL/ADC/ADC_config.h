/***************************************************************/
/**SWC :       ADC                                   **********/
/**Author :   Mohamed Khaled Elfawakhry              ***********/
/**Version :       1.0                               ***********/
/**Date :            2/4/2023                      ************/
/***************************************************************/
/*      File Gaurd    */
#ifndef ADC_CONFIG_H
#define ADC_CONFIG_H
/******************************************************/

#define ENABLE            1
#define DISABLE           0

#define ADC_EN          ENABLE
#define ADC_TRIG_EN     DISABLE
#define ADC_INT_EN      DISABLE

/*******************************************************/
#define AREF    0                 //Internal Vref turned off
#define AVCC    1                // 5v
#define INTERNAL_2_56V    2      // Internal with 2.56v

#define ADC_REF_SELEC   AVCC
/******************************************************/
#define LEFT_ADJUST        0
#define RIGHT_ADJUST       1

#define ADC_ADLAR         RIGHT_ADJUST
/******************************************************/

/*
    Options : 
                1.ADC_SING_END_ADC0       
                2.ADC_SING_END_ADC1       
                3.ADC_SING_END_ADC2       
                4.ADC_SING_END_ADC3       
                5.ADC_SING_END_ADC4       
                6.ADC_SING_END_ADC5       
                7.ADC_SING_END_ADC6       
                8.ADC_SING_END_ADC7       
*/
#define ADC_MUX       ADC_SING_END_ADC0  
/******************************************************/
#define ADC_PRE_2           0
#define ADC_PRE_4           1
#define ADC_PRE_8           2
#define ADC_PRE_16          3
#define ADC_PRE_32          4
#define ADC_PRE_64          5
#define ADC_PRE_128         6

#define ADC_PRESCALER       ADC_PRE_128
/******************************************************/


#endif
