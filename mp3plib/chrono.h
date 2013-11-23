#ifndef CHRONO_H_
#define CHRONO_H_

#define FREQ_1KHz		1000
#define FREQ_1Hz		1

#define NUM_LOOP_CYCLES	3	//The SysCtlDelay() function takes EXACTLY 3 cycles/loop

void CHRONO_Delay_1ms(uint32_t delay);
void CHRONO_Delay_1s(uint32_t delay);

#endif