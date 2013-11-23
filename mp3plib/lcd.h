#ifndef LCD_H_
#define LCD_H_

//Colors
#define WHITE			0xFFFF
#define BLACK			0x0000
#define GRAY			0xF7DE
#define BLUE			0x001F
#define BLUE2			0x051F
#define RED				0xF800
#define MAGENTA			0xF81F
#define GREEN			0x07E0
#define CYAN			0x7FFF
#define YELLOW			0xFFE0
#define D_GRAY			0x528A				//Dark Gray
#define L_GRAY			0x7BEF				//Light Gray

//LCD screen size and bit depth
#define LCD_WIDTH       240					//Screen Width (in pixels)
#define LCD_HEIGHT      320					//Screen Height (in pixels)
#define LCD_BPP         16					//Bits per pixel

//GPIO pins for LCD control (PORT_F)

#define LCD_BCKL	GPIO_PIN_0	//Backlight LED signal (DO NOT CONNECT DIRECTLY TO GPIO PINS! User a transistor)
#define LCD_CS		GPIO_PIN_1	//Chip-Select signal (Active Low)
#define LCD_RS		GPIO_PIN_2	//Register Select signal for register index (RS=1) or register command (RS=0) select (8k0940 TFT LCD Specification)
#define LCD_WR		GPIO_PIN_3	//Write signal
#define LCD_REST	GPIO_PIN_4	//Reset signal (Active Low)
//#define LCD_RD		GPIO_PIN_8	//(DO NOT USE) Read from RAM. Must always be set to logic 1. (Active Low?)

//Data/Command select values
#define REG_SET_DATA	0x1
#define REG_SET_COMMAND	0x0

//Used to write data and commands in parallel to the LCD in TransferToOutputPins()
#define PORT_B_BITS ( GPIO_PIN_7 | GPIO_PIN_6 | GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 | GPIO_PIN_0 )	//OxFF00
#define PORT_E_BITS ( GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 | GPIO_PIN_0 )								//0x003F
#define PORT_D_BITS ( GPIO_PIN_7 | GPIO_PIN_6 )																					//0x00C0

//Registers
#define OSCSTART	0x0000		//Oscilation Start
#define DOUTCTRL	0x0001		//Driver Output Control
#define LCDDRVAC	0x0002		//LCD drive AC control
#define PWRCTRL1	0x0003		//Power Control (1)
#define COMPREG1	0x0005		//Compare Register (1)
#define COMPREG2	0x0006		//Compare Register (2)
#define DISPCTRL	0x0007		//Display Control
#define FRACLCTL	0x000B		//Frame Cycle Control
#define PWRCTRL2	0x000C		//Power Control (2)
#define PWRCTRL3	0x000D		//Power Control (3)
#define PWRCTRL4	0x000E		//Power Control (4)
#define GTSCANSP	0x000F		//Gate Scan Start Position
#define SLEEPMOD	0x0010		//Sleep Mode
#define ENTRYMOD	0x0011		//Entry Mode
#define OPTMASP3	0x0012		//Optimize Access Speed 3
#define GINTCTRL	0x0015		//Generic Interface Control
#define HRZPORCH	0x0016		//Horizontal Porch
#define VRTPORCH	0x0017		//Vertical Porch
#define PWRCTRL5	0x001E		//Power Control (5)
#define RAMDATRW	0x0022		//RAM Data Read/Write
#define RAMDWMK1	0x0023		//RAM Data Write Mask 1
#define RAMDWMK2	0x0024		//RAM Data Write Mask 2
#define FRAMFREQ	0x0025		//Frame Frequency
#define VCOMOTP1	0x0028		//VCOM OTP (1). The number "1" isn´t in the data sheet.
#define OPTMASP1	0x0028		//Optimize Access Speed 1
#define VCOMOTP2	0x0029		//VCOM OPT (2)
#define OPTMASP2	0x002F		//Optimize Access Speed 2
#define GMCTRL01	0x0030		//Gama Control	(1)
#define GMCTRL02	0x0031		//Gama Control	(2)
#define GMCTRL03	0x0032		//Gama Control	(3)
#define GMCTRL04	0x0033		//Gama Control	(4)
#define GMCTRL05	0x0034		//Gama Control	(5)
#define GMCTRL06	0x0035		//Gama Control	(6)
#define GMCTRL07	0x0036		//Gama Control	(7)
#define GMCTRL08	0x0037		//Gama Control	(8)
#define GMCTRL09	0x003A		//Gama Control	(9)
#define GMCTRL10	0x003B		//Gama Control	(10)
#define VTSCTRL1	0x0041		//Vertical Scroll Control (1)	
#define VTSCTRL2	0x0042		//Vertical Scroll Control (2)
#define HRADRPOS	0x0044		//Horizontal RAM Address Position
#define	VRADSTPO	0x0045		//Vertical RAM Address Start Position
#define	VRADEDPO	0x0046		//Vertical RAM Address End Position
#define	FTWNDSTA	0x0048		//First Window Start
#define	FTWNDEND	0x0049		//First Window End
#define	SCWNDSTA	0x004A		//Second Window Start
#define	SCWNDEND	0x004B		//Second Window End
#define	STGDRXAC	0x004E		//Set GDDRAM X Address Counter
#define	STGDRYAC	0x004F		//Set GDDRAM Y Address Counter

//Functions

void LCD_BackLight(uint8_t state);
void LCD_Set_Address(uint32_t PX1, uint32_t PY1, uint32_t PX2, uint32_t PY2);
void LCD_Fill(uint32_t color);
void LCD_Box(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color);
void LCD_Dot(uint32_t x, uint32_t y, uint32_t color);
void LCD_Line(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color);
void LCD_H_Line(uint8_t x1, uint8_t x2, uint32_t y_pos, uint32_t color);
void LCD_V_Line(uint32_t y1, uint32_t y2, uint8_t x_pos, uint32_t color);
void LCD_Rectangle(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color);
void LCD_Circle(uint32_t x, uint32_t y, uint8_t radius, uint8_t fill, uint32_t color);
void LCD_Char(char C, uint32_t x, uint32_t y, char DimFont, uint32_t Fcolor, uint32_t Bcolor);
void LCD_Text(char* S, uint32_t x, uint32_t y, char DimFont, uint32_t Fcolor, uint32_t Bcolor);
void LCD_Image(uint32_t pos_x, uint32_t pos_y, uint32_t dim_x, uint32_t dim_y, const uint32_t *picture);
void LCD_Init();
void LCD_On();
void LCD_Sleep(char state);
void LCD_Off();
#endif