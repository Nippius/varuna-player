//*****************************************************************************
//	
//	Copyright © 2014 Tiago Costa <nippius+github@gmail.com>
//	This work is free. You can redistribute it and/or modify it under the
//	terms of the Do What The Fuck You Want To Public License, Version 2,
//	as published by Sam Hocevar. See the COPYING file for more details.
//	
//*****************************************************************************

#ifndef CHRONO_H_
#define CHRONO_H_

#define FREQ_1KHz		1000
#define FREQ_1Hz		1

#define NUM_LOOP_CYCLES	3	//The SysCtlDelay() function takes EXACTLY 3 cycles/loop

void CHRONO_Delay_1ms(uint32_t delay);
void CHRONO_Delay_1s(uint32_t delay);

#endif