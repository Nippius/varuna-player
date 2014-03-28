//*****************************************************************************
//	
//	Copyright © 2014 Tiago Costa <nippius+github@gmail.com>
//	This work is free. You can redistribute it and/or modify it under the
//	terms of the Do What The Fuck You Want To Public License, Version 2,
//	as published by Sam Hocevar. See the COPYING file for more details.
//	
//*****************************************************************************

//Stellaris
#include "stdint.h"
#include "stdbool.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/timer.h"
#include "driverlib/sysctl.h"
//mp3plib
#include "chrono.h"

void CHRONO_Delay_1ms(uint32_t delay)
{
	uint32_t i = 0;
	while(i<delay)
	{
		SysCtlDelay((SysCtlClockGet() / FREQ_1KHz / NUM_LOOP_CYCLES ));
		i++;
	}
}

void CHRONO_Delay_1s(uint32_t delay)
{
	//NOT WORKING!
	uint32_t i = 0;
	while(i<delay)
	{
		CHRONO_Delay_1ms(1000);
		//SysCtlDelay((SysCtlClockGet() / NUM_LOOP_CYCLES ));	//Isto devia gerar um delay de 1 segundo
		i++;
	}
}