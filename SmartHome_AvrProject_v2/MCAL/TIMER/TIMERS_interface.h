/***************************************************************/
/**SWC :       TIMERS                                   **********/
/**Author :   Mohamed Khaled Elfawakhry              ***********/
/**Version :       1.0                               ***********/
/**Date :            5/4/2023                      ************/
/***************************************************************/
/*      File Gaurd    */
#ifndef TIMERS_INTERFACE_H
#define TIMERS_INTERFACE_H

#define TIMER0_CTC_TIME		250 // MicroSeconds
void TIMERS_voidTIMER0Init(void);
void TIMERS_voidSetCallBackTIMER0OVF (void(*Lpf)(void));
void TIMERS_voidSetPreloadValueTIMER0OVF(u8 Copy_u8PreloadValue);
void TIMERS_voidSetCallBackTIMER0CTC (void(*Lpf)(void));
void TIMERS_voidSetCompareMatchValue (u8 Copy_u8CompareMatchValue );
void TIMERS_voidT1SetBusyWait(u32 Copy_u32MilliSeconds);

/*************************      TIMER1        ***********************************/
void TIMERS_voidTIMER1Init(void);
void TIMERS_voidTIMER1SetPinACompMatch (u16 Copy_u16Value );
void TIMERS_voidTIMER1SetICR1Value(u16 Copy_u16Value);

#define TIMERS_ICU_RAISINGEDGE		1
#define TIMERS_ICU_FALLINGEDGE		0
void TIMERS_voidICUInterruptEnable(void);
void TIMERS_voidICUInterruptDisable(void);
void TIMERS_voidICUEdgeSelect(u8 Copy_u8Edge );
u16 TIMERS_u16ICUGetReading(void);
void TIMERS_voidICUSetCallBack(void(*Lpf)(void));

#endif
