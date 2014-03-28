#==============================================================================
#
#	Copyright © 2014 Tiago Costa <nippius+github@gmail.com>
#	This work is free. You can redistribute it and/or modify it under the
#	terms of the Do What The Fuck You Want To Public License, Version 2,
#	as published by Sam Hocevar. See the COPYING file for more details.
#
#==============================================================================

#==============================================================================
#           Cross compiling toolchain / tools specifications
#==============================================================================

# Prefix for the arm-eabi-none toolchain.
# I'm using GNU Tools for ARM Embedded Processors compilers available here:
# https://launchpad.net/gcc-arm-embedded
PREFIX_ARM = arm-none-eabi

#==============================================================================
# Microcontroller properties
#==============================================================================

# old part number for stelarisware
# PART = LM4F120H5QR
# New part number for TivaWare
PART = TM4C1233H6PM
CPU = -mcpu=cortex-m4
FPU = -mfpu=fpv4-sp-d16 -mfloat-abi=softfp
# To use hardware FPU, the stellarisware lib must be built using hard FP also! (see makedefs)
# FPU = -mfpu=fpv4-sp-d16 -mfloat-abi=hard
# Note:
# hard = Use hardware floating point
# softfp = Use hardware floating point but use normal register, calling conventions, etc
# soft = Use software for floating point operations

#==============================================================================
# Librarys
#==============================================================================

# MP3PlayerLib path
MP3PLIB_PATH = mp3plib/

# TivaWare path
TIVAWARE_PATH = ../TivaWare/

#==============================================================================
# Compiler stuff
#==============================================================================

# Program name definition for ARM GNU C compiler.
CC = ${PREFIX_ARM}-gcc
# Program name definition for ARM GNU Linker.
LD = ${PREFIX_ARM}-ld
# Program name definition for ARM GNU Object copy.
CP = ${PREFIX_ARM}-objcopy
# Program name definition for ARM GNU Object dump.
OD = ${PREFIX_ARM}-objdump

# Option arguments for C compiler.
CFLAGS = -mthumb ${CPU} ${FPU} -O0 -ffunction-sections -fdata-sections -MD -std=c99 -Wall -pedantic -Wextra -c -g
# Library stuff passed as flags!
CFLAGS += -I ${TIVAWARE_PATH} -I ${MP3PLIB_PATH} -DPART_$(PART) -c -DTARGET_IS_BLIZZARD_RA1

# Flags for LD
LFLAGS  = --gc-sections

# Flags for objcopy
CPFLAGS = -Obinary

# flags for objectdump
ODFLAGS = -S

# I want to save the path to libgcc, libc.a and libm.a for linking.
# I can get them from the gcc frontend, using some options.
# See gcc documentation
LIB_GCC_PATH = ${shell ${CC} ${CFLAGS} -print-libgcc-file-name}
LIBC_PATH = ${shell ${CC} ${CFLAGS} -print-file-name=libc.a}
LIBM_PATH = ${shell ${CC} ${CFLAGS} -print-file-name=libm.a}

#==============================================================================
# Tools
#==============================================================================

# Uploader tool path.
# Set a relative or absolute path to the upload tool program.
FLASHER = "C:/Program Files (x86)/Texas Instruments/Stellaris/LM Flash Programmer/lmflash"
# Flags for the uploader program.
FLASHER_FLAGS = -q ek-lm4f120xl -r

# OpenOCD path.
# Set a relative or absolute path to the debug tool program.

# %OS% is only defined in Windows systems so we can
# use this as crude way to detect the operating system
ifdef OS
	# Assuming OpenOCD install path = C:\TivaC\OpenOCD
	OPENOCD_PATH = ../OpenOCD
	# OpenOCD executable (remove -x64 for 32bit binary)
	OPENOCD = ${OPENOCD_PATH}/bin-x64/openocd-x64-0.7.0.exe
	# Flags for OpenOCD
	OPENOCD_FLAGS = -f ${OPENOCD_PATH}/scripts/board/${OPENOCD_BOARD_CFG}
else
	OPENOCD = openocd
	OPENOCD_FLAGS = -f /usr/share/openocd/scripts/board/${OPENOCD_BOARD_CFG}
endif


# OpenOCD config file for the Stellaries Lauchpad board
OPENOCD_BOARD_CFG = ek-lm4f120xl.cfg

#==============================================================================
#                         Project properties
#==============================================================================

# Project name (W/O .c extension eg. "main")
PROJECT_NAME = varuna-player
# Startup file name (W/O .c extension eg. "LM4F_startup")
STARTUP_FILE = LM4F_startup
# Linker file name
LINKER_FILE = LM4F.ld

SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)

#==============================================================================
#                      Rules to make the target
#==============================================================================

# make all rule
all: $(OBJS) ${PROJECT_NAME}.axf ${PROJECT_NAME}

%.o: %.c
	@echo
	@echo Compiling $<...
	$(CC) -c $(CFLAGS) ${<} -o ${@}

${PROJECT_NAME}.axf: $(OBJS)
	@echo
	@echo [Making mp3plib]
	$(MAKE) -C ${MP3PLIB_PATH}
	@echo
	@echo [Making driverlib]
	$(MAKE) -C ${TIVAWARE_PATH}driverlib/
	@echo
	@echo Linking...
	$(LD) -T $(LINKER_FILE) $(LFLAGS) -o ${PROJECT_NAME}.axf $(OBJS) ${MP3PLIB_PATH}mp3plib.a ${TIVAWARE_PATH}driverlib/gcc/libdriver.a $(LIBM_PATH) $(LIBC_PATH) $(LIB_GCC_PATH)

${PROJECT_NAME}: ${PROJECT_NAME}.axf
	@echo
	@echo Copying...
	$(CP) $(CPFLAGS) ${PROJECT_NAME}.axf ${PROJECT_NAME}.bin
	@echo
	@echo Creating list file...
	$(OD) $(ODFLAGS) ${PROJECT_NAME}.axf > ${PROJECT_NAME}.lst

# make clean rule
clean:
	@echo
	@echo Cleanning mp3lib...
	$(MAKE) -C ${MP3PLIB_PATH} clean
	@echo
	@echo Cleanning project files...
	rm -f *.bin *.o *.d *.axf *.lst

# Rule to load the project to the board
load:
	${FLASHER} ${PROJECT_NAME}.bin ${FLASHER_FLAGS}

# Rule to connect OpenOCD to the board to allow debugging
debug:
	${OPENOCD} ${OPENOCD_FLAGS}
