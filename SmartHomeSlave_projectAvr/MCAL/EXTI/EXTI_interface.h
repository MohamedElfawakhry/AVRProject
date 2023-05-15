/***************************************************************/
/**SWC :       EXTI                                   **********/
/**Author :   Mohamed Khaled Elfawakhry              ***********/
/**Version :       1.0                               ***********/
/**Date :            2/4/2023                      ************/
/***************************************************************/
/*      File Gaurd    */
#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

#define FALLING_EDGE    0
#define RAISING_EDGE    1
#define LOW_LEVEL       2
#define ON_CHANGE       3

#define INT0        0
#define INT1        1
#define INT2        2

void EXTI_voidInit(void);
void EXTI_voidEnable  (u8 Copy_u8IntId , u8 Copy_u8SenseControl );
void EXTI_voidDisable (u8 Copy_u8IntId);
void EXTI_voidSetCallBack(void (*Local_pf)(void) , u8 Copy_u8IntId);


#endif
