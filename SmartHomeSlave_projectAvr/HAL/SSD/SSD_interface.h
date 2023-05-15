/***************************************************************/
/**SWC :       SSD(Seven Segment Display              **********/
/**Author :   Mohamed Khaled Elfawakhry              ***********/
/**Version :       1.0                               ***********/
/**Date :            27/3/2023                      ************/
/***************************************************************/
#ifndef SSD_INTERFACE_H
#define SSD_INTERFACE_H

#define COMMON_ANODE        1
#define COMMON_CATHODE      2

typedef struct ssd
{
    u8 PortNumber ;
    u8 CommonState ;
}SSD_t ;

#define ZERO 	0b00111111
#define ONE		0b00000110
#define TWO		0b01011011
#define THREE	0b01001111
#define FOUR	0b01100110
#define FIVE	0b01101101
#define SIX		0b01111101
#define SEVEN	0b00000111
#define EIGHT	0b01111111
#define NINE 	0b01101111


/*******************************************************************************/
/* Func Name : SSD_voidInit                                                    */
/* i/p arguments : S : Struct from Seven Segment type					       */
/*return : void                                                                */
/*******************************************************************************/
void SSD_voidInit(SSD_t S);
/*******************************************************************************/
/* Func Name : SSD_voidInit                                                    */
/* i/p arguments :   S : Struct from Seven Segment type						   */
/*  Copy_u8Number:     1 -> 9											       */
/*return : void                                                                */
/*******************************************************************************/
void SSD_voidDisplayNumber(SSD_t S , u8 Copy_u8Number );


#endif
