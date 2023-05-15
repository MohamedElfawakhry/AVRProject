/***************************************************************/
/**SWC :       WatchDog                               **********/
/**Author :   Mohamed Khaled Elfawakhry              ***********/
/**Version :       1.0                               ***********/
/**Date :            5/4/2023                      ************/
/***************************************************************/
/*      File Gaurd    */
#ifndef WATCHDOG_INTERFACE_H
#define WATCHDOG_INTERFACE_H

#define WDT_TIME        7

void WDT_voidEnable(void);
void WDT_voidDisable(void);
void WDT_voidSetTime(u8 Copy_u8ResetTime);

#endif