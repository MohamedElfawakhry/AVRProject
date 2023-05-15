/***************************************************************/
/**SWC :       DIO(Digital Input Output)              **********/
/**Author :   Mohamed Khaled Elfawakhry              ***********/
/**Version :       1.0                               ***********/
/**Date :            29/3/2023                      ************/
/***************************************************************/

#ifndef CLCD_CONFIG_H_
#define CLCD_CONFIG_H_

/* D0 ------> D7 */

/*

  Options:-
 	 1-DIO_PORTA
 	 2-DIO_PORTB
 	 3-DIO_PORTC
 	 4-DIO_PORTD

 */


#define CLCD_DATA_PORT      PORTD
/* RS,RW,EN */
#define CLCD_CONTROL_PORT   PORTA

/*

 Options:-
 	 1-DIO_PIN0
 	 2-DIO_PIN1
 	 3-DIO_PIN2
 	 4-DIO_PIN3
 	 5-DIO_PIN4
 	 6-DIO_PIN5
 	 7-DIO_PIN6
 	 8-DIO_PIN7

 */
#define CLCD_RS             PIN1
#define CLCD_RW             PIN2
#define CLCD_EN             PIN3


#endif /* CLCD_CONFIG_H_ */
