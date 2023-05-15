/***************************************************************/
/**SWC :       DIO(Digital Input Output)              **********/
/**Author :   Mohamed Khaled Elfawakhry              ***********/
/**Version :       1.0                               ***********/
/**Date :            29/3/2023                      ************/
/***************************************************************/

#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_

#define CLCD_ROW_1 1
#define CLCD_ROW_2 2

#define CLCD_COL_1   1
#define CLCD_COL_2   2
#define CLCD_COL_3   3
#define CLCD_COL_4   4
#define CLCD_COL_5   5
#define CLCD_COL_6   6
#define CLCD_COL_7   7
#define CLCD_COL_8   8
#define CLCD_COL_9   9
#define CLCD_COL_10  10
#define CLCD_COL_11  11
#define CLCD_COL_12  12
#define CLCD_COL_13  13
#define CLCD_COL_14  14
#define CLCD_COL_15  15
#define CLCD_COL_16  16


void CLCD_voidInit        ( void );
void CLCD_voidSendData    ( u8 Copy_u8Data );
void CLCD_voidSendCommend ( u8 Copy_u8Commend );
void CLCD_voidSendString  (u8 * Copy_u8ptrString );
void CLCD_voidSendNumber   ( u64 Copy_u64Number    );

void CLCD_voidSetPosition ( u8 Copy_u8Row , u8 Copy_u8Col );
void CLCD_voidSendExtraChar( u8* Copy_u8Pattern , u8 Copy_u8PatternNumber ,u8 Copy_u8Row , u8 Copy_u8Col );
#endif /* CLCD_INTERFACE_H_ */
