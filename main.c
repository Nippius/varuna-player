/Tiva-C
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/systick.h"

//mp3plib
#include "uartstdio.h"
#include "lcd.h"
#include "common.h"
#include "chrono.h"

#define VERSION "0.02"

void UART_Init()
{
	/*
		Os pinos da UART0 são partilhados com o ICDI. Em teoria, o ICDI deveria fazer match á frequencia da UART
		colocada aqui mas pelos vistos não é esse o caso. 
		Tenho 2 possíveis soluções para o problema dos caracteres marados. Ou meto um delay(1000) algures antes
		de usar a UART pela primeira vez (mas depois de configurada), ou então tento usar a UART1 a ver se dá
		para comunicar com o putty.
	*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	
	//arg0 - UART Port
	//arg1 - Baud rate
	//arg2 - SrcClock
    UARTStdioConfig(0, 115200, 16000000);	//Obtained from the example "hello.c".
	
	//UARTStdioInit(0);
    UARTprintf("Welcome to the Varuna MP3 Player v0.2 Project!\n");
	UARTprintf("----------------------------------------------\n\n");
}

/*
ESTUDAR COMO FUNCIONA ESTA LIB!
*/

//*****************************************************************************
//
// Delay for the specified number of seconds.  Depending upon the current
// SysTick value, the delay will be between N-1 and N seconds (i.e. N-1 full
// seconds are guaranteed, along with the remainder of the current second).
//
//*****************************************************************************
void
Delay(uint32_t ui32Seconds)
{
    //
    // Loop while there are more seconds to wait.
    //
    while(ui32Seconds--)
    {
        //
        // Wait until the SysTick value is less than 1000.
        //
        while(ROM_SysTickValueGet() > 1000)
        {
        }

        //
        // Wait until the SysTick value is greater than 1000.
        //
        while(ROM_SysTickValueGet() < 1000)
        {
        }
    }
}


void dot_test()
{	
	int i=0;
	int j=0;
	for(i = 0; i<LCD_WIDTH; i++)
	{
		for(j=0; j<LCD_HEIGHT; j++)
		{
			if(j%2==0)
			{
				LCD_Dot(i, j, RED);
			}else{
				LCD_Dot(i, j, GREEN);
			}
		}
	}
}

void rainbow_test()
{
	while(1)
	{
		CHRONO_Delay_1ms(500);
		LCD_Fill(WHITE);
		CHRONO_Delay_1ms(500);
		LCD_Fill(RED);
		CHRONO_Delay_1ms(500);
		LCD_Fill(YELLOW);
		CHRONO_Delay_1ms(500);
		LCD_Fill(GREEN);
		CHRONO_Delay_1ms(500);
		LCD_Fill(BLUE);
		CHRONO_Delay_1ms(500);
		LCD_Fill(BLUE2);
		CHRONO_Delay_1ms(500);
		LCD_Fill(CYAN);
		CHRONO_Delay_1ms(500);
		LCD_Fill(MAGENTA);
		CHRONO_Delay_1ms(500);
		LCD_Fill(L_GRAY);
		CHRONO_Delay_1ms(500);
		LCD_Fill(GRAY);
		CHRONO_Delay_1ms(500);
		LCD_Fill(D_GRAY);
		CHRONO_Delay_1ms(500);
		LCD_Fill(BLACK);
	}
}

/*void concentric_squares_test()
{
	int sizeX = 10;
	int sizeY = 10;
	int x = 0;
	int y = 0;
}*/


int main()
{
	//Configure System Clock at 50 MHz
	//To run at 80MHz use SYSCTL_SYSDIV_2_5
	//SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
	//To run at 50MHz use SYSCTL_SYSDIV_4
	SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

	LCD_Init();

	LCD_On();

	LCD_BackLight(ENABLE);

	LCD_Fill(BLACK);
	
	LCD_Text(VERSION,35, 20, 16, GREEN, BLACK);

	CHRONO_Delay_1ms(1000);
	
	//dot_test();
	rainbow_test();
	
	while(1);

	return 0;
}