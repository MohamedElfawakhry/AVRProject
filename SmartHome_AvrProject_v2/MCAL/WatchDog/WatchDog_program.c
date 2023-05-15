#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "WatchDog_interface.h"
#include "WatchDog_private.h"


void WDT_voidEnable(void)
{
    SET_BIT(WDTCR_REG , 3 );
}
void WDT_voidDisable(void)
{
    /* Reset WDT */
    //_WDR();
    /*Write Logical one on 3&4 bit*/
    SET_BIT(WDTCR_REG , 3 );
    SET_BIT(WDTCR_REG , 4 );
    /*Turn off WDT*/
    WDTCR_REG = 0x00 ;

}
void WDT_voidSetTime(u8 Copy_u8ResetTime)
{
    WDTCR_REG &= 0b11111000 ;
    WDTCR_REG |= Copy_u8ResetTime;
    
}
