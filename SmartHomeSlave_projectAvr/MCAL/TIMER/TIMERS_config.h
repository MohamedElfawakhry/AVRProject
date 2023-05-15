/***************************************************************/
/**SWC :      TIMERS                                    **********/
/**Author :   Mohamed Khaled Elfawakhry              ***********/
/**Version :       1.0                               ***********/
/**Date :            5/4/2023                      ************/
/***************************************************************/
/*      File Gaurd    */
#ifndef TIMERS_CONFIG_H
#define TIMERS_CONFIG_H

#define TIMERS_T0_PRELOADVALUE		192
#define TIMERS_T0OVF_SWCOUNTER			3907

#define TIMERS_T0CTC_SWCOUNTER			4000

/*=================================== TIMER1 /*==================================*/
/*=======================================================*/
/*  Compare Output Mode for Compare unit */
#define TIMERS_OC_DISCONNECTED        0
//#define TIMERS_TOGG_OC_ONCOMPMATCH  1
#define TIMERS_NON_INVERTING_MODE     2
#define TIMERS_INVERTING_MODE         3

#define TIMRES_OC1A_CONFIG      TIMERS_NON_INVERTING_MODE
#define TIMERS_OC1B_CONFIG      TIMERS_OC_DISCONNECTED
/*=======================================================*/
#define ENABLE              1
#define DISABLE             0
#define TIMERS_T1_ICU_NOISE_CANCLER        DISABLE
/*=======================================================*/
/*      CLOCK SET ( PRESCALER )         */
#define TIMERS_T1_NO_CLOCK_SOURCE          0
#define TIMERS_T1_CLK_1                    1   //divided by 1
#define TIMERS_T1_CLK_8                    2   //divided by 8
#define TIMERS_T1_CLK_64                   3   //divided by 64
#define TIMERS_T1_CLK_256                  4   //divided by 256
#define TIMERS_T1_CLK_1024                 5   //divided by 1024
#define TIMERS_T1_CLK_SET           TIMERS_T1_CLK_8
/*=======================================================*/
/*  Wave Generation Mode   */
#define TIMERS_T1_NORMAL                   0
#define TIMERS_T1_PHAS_CORRECT_8BIT        1
#define TIMERS_T1_PHAS_CORRECT_9BIT        2
#define TIMERS_T1_PHAS_CORRECT_10BIT       3
#define TIMERS_T1_CTC                      4
#define TIMERS_T1_FAST_PWM_8BIT            5
#define TIMERS_T1_FAST_PWM_9BIT            6
#define TIMERS_T1_FAST_PWM_10BIT           7

#define TIMERS_T1_FAST_PWM_TOP_ICR1        14
#define TIMERS_T1_FAST_PWM_TOP_OCR1A       15

#define TIMERS_T1_WAVE_GENERATION_MODE    TIMERS_T1_FAST_PWM_TOP_ICR1
/*=======================================================*/
/*===============================================================================*/



#endif
