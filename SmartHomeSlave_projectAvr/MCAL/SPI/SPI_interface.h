/***************************************************************/
/**SWC :       SPI                                   **********/
/**Author :   Mohamed Khaled Elfawakhry              ***********/
/**Version :       1.0                               ***********/
/**Date :            2/4/2023                      ************/
/***************************************************************/
/*      File Gaurd    */
#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H

void SPI_voidMasterInit(void);

void SPI_voidSlaveInit(void);

void SPI_voidMasterSendData(u8 Copy_u8DataToBeSent , u8* Copy_pu8ReceivedData);

void SPI_voidAsyncSendData (u8 Copy_u8DataToBeSent , u8* Copy_pu8RecievedData );
u8 SPI_u8AsyncReturnedData(void);
void SPI_voidSetCallBackFunction ( void (*Lpf)(void));
#endif
