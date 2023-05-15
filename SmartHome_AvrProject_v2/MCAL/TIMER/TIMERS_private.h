/***************************************************************/
/**SWC :       TIMERS                               **********/
/**Author :   Mohamed Khaled Elfawakhry              ***********/
/**Version :       1.0                               ***********/
/**Date :            5/4/2023                      ************/
/***************************************************************/
/*      File Gaurd    */
#ifndef TIMERS_PRIVATE_H
#define TIMERS_PRIVATE_H

#define TIMERS_TCCR0_REG                 *((volatile u8*)0x53)
#define TIMERS_TCNT0_REG                 *((volatile u8*)0x52)
#define TIMERS_OCR0_REG                  *((volatile u8*)0x5C)
#define TIMERS_TIMSK_REG                 *((volatile u8*)0x59)
#define TIMERS_TIFR_REG                  *((volatile u8*)0x58)

#define TIMERS_TCCR1A_REG                     *((volatile u8*)   0x4F)
#define TIMERS_TCCR1B_REG                     *((volatile u8*)   0x4E)
#define TIMERS_TCNT1_REG                      *((volatile u16*)  0x4C)
#define TIMERS_OCR1A_REG                     *((volatile u16*)  0x4A)
#define TIMERS_OCR1B_REG                      *((volatile u16*)  0x48)
#define TIMERS_ICR1_REG                       *((volatile u16*)  0x46)

/*TCCR1A , PINS*/
#define TIMERS_TCCR1A_COM1A1          7
#define TIMERS_TCCR1A_COM1A0          6
#define TIMERS_TCCR1A_COM1B1          5
#define TIMERS_TCCR1A_COM1B0          4
#define TIMERS_TCCR1A_FOC1A           3
#define TIMERS_TCCR1A_FOC1B           2
#define TIMERS_TCCR1A_WGM11           1
#define TIMERS_TCCR1A_WGM10           0

/*TCCR1A , PINS*/
#define TIMERS_TCCR1B_ICNC1           7
#define TIMERS_TCCR1B_ICES1           6
/*              Reserved              5*/
#define TIMERS_TCCR1B_WGM13           4
#define TIMERS_TCCR1B_WGM12           3
#define TIMERS_TCCR1B_CS12            2
#define TIMERS_TCCR1B_CS11            1
#define TIMERS_TCCR1B_CS10            0




#endif
