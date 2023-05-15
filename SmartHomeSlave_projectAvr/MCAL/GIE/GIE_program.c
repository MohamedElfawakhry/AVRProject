#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"


#include "GIE_interface.h"
#include "GIE_private.h"


void GIE_voidEnable(void)
{
	SET_BIT(SREG , 7 );
}
void GIE_voidDisable(void)
{
	CLR_BIT(SREG , 7 );
}
