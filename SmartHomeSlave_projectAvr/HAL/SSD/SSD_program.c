/***************************************************************/
/**SWC :       SSD(Seven Segment Display              **********/
/**Author :   Mohamed Khaled Elfawakhry              ***********/
/**Version :       1.0                               ***********/
/**Date :            27/3/2023                      ************/
/***************************************************************/

#include"../../LIB/STD_TYPES.h"
#include"../../LIB/BIT_MATH.h"

#include"../../MCAL/DIO/DIO_interface.h"
#include"SSD_interface.h"

u8 SSD_ArrNumbers[10]={ZERO , ONE , TWO , THREE , FOUR , FIVE , SIX , SEVEN , EIGHT ,NINE };
/*******************************************************************************/
/* Func Name : SSD_voidInit                                                    */
/* i/p arguments : S : Struct from Seven Segment type					       */
/*return : void                                                                */
/*******************************************************************************/
void SSD_voidInit(SSD_t S)
{
    DIO_voidSetPortDirection(S.PortNumber , OUTPUT );
    /*Initilize with display off all cells */
    switch (S.CommonState)
    {
    case COMMON_ANODE:
        DIO_voidSetPortValue(S.PortNumber , HIGH );
        break;
    case COMMON_CATHODE:
        DIO_voidSetPortValue(S.PortNumber , LOW );
        break;
    default:
        break;
    }
}
/*******************************************************************************/
/* Func Name : SSD_voidInit                                                    */
/* i/p arguments :   S : Struct from Seven Segment type						   */
/*  Copy_u8Number:     1 -> 9											       */
/*return : void                                                                */
/*******************************************************************************/
void SSD_voidDisplayNumber(SSD_t S , u8 Copy_u8Number )
{
     switch (S.CommonState)
    {
    case COMMON_ANODE:
                  	  DIO_voidSetPortValue(S.PortNumber , ~SSD_ArrNumbers[Copy_u8Number]);
        break;
    case COMMON_CATHODE:
    				DIO_voidSetPortValue(S.PortNumber , SSD_ArrNumbers[Copy_u8Number]);
        break;
    default:
        break;
    }
}
