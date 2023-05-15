/*************************************************************************/
/* !File Name:         TWI_interface.h                                   */
/* !Layer    :         MCAL                                              */
/* !Author   :         Abdullah M. Abdullah                              */
/* !Date     :         2 SEP, 2021                                       */
/* !Version  :         v1.0                                              */
/*************************************************************************/
#ifndef TWI_INTERFACE_H
#define TWI_INTERFACE_H

typedef enum
{
	NoError,
	StartConditionError,
	RepeatedStartError,
	SlaveAddressWithWriteError,
	SlaveAddressWithReadError,
	MasterWriteByteWithACKError,
	MasterReadByteWithACKError,
	SlaveReadByteWithACKError,



}TWI_ErrorStatus_t;

void 				TWI_voidInitMaster(u8 Copy_u8Address);
void 				TWI_voidInitSlave(u8 Copy_u8Address);
TWI_ErrorStatus_t 	TWI_ErrorStatusSendStartConditionWithACK(void);
TWI_ErrorStatus_t 	TWI_ErrorStatusSendRepeatedStartConditionWithACK(void);
TWI_ErrorStatus_t 	TWI_ErrorStatusSendSlaveAddressWithWriteACK(u8 Copy_u8SlaveAddress);
TWI_ErrorStatus_t 	TWI_ErrorStatusSendSlaveAddressWithReadACK(u8 Copy_u8SlaveAddress);
TWI_ErrorStatus_t 	TWI_ErrorStatusMasterWriteDataByteWithACK(u8 Copy_u8DataByte);
TWI_ErrorStatus_t 	TWI_ErrorStatusMasterReadDataByteWithACK(u8 * Copy_pu8ReceivedByte);
void 				TWI_voidSendStopCondition(void);


#endif
