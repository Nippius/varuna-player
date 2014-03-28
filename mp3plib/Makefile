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
# I'm using codesourcery g++ lite compilers available here:
# http://www.mentor.com/embedded-software/sourcery-tools/sourcery-codebench/editions/lite-edition/
PREFIX_ARM = arm-none-eabi

# Microcontroller properties.
PART = TM4C1233H6PM
CPU = -mcpu=cortex-m4
FPU = -mfpu=fpv4-sp-d16 -mfloat-abi=softfp
# To use hardware FPU, the stellarisware lib must be built using hard FP also! (see makedefs)
#FPU = -mfpu=fpv4-sp-d16 -mfloat-abi=hard
#Note:
#hard = Use hardware floating point
#softfp = Use hardware floating point but use normal register, calling conventions, etc
#soft = Use software for floating point operations


# Stellarisware path
#Assuming Stellaris install path=C:\Stellaris\TivaWare and using cygwin
TIVAWARE_PATH=../../TivaWare/

# Program name definition for ARM GNU C compiler.
CC = ${PREFIX_ARM}-gcc
# Program name definition for ARM GNU Archiver.
AR = ${PREFIX_ARM}-ar

# Option arguments for C compiler.
CFLAGS =-mthumb ${CPU} ${FPU} -O0 -ffunction-sections -fdata-sections -MD -std=c99 -Wall -pedantic -Wextra -c -g
# Library stuff passed as flags!
CFLAGS += -I ${TIVAWARE_PATH} -DPART_$(PART) -c -DTARGET_IS_BLIZZARD_RA1

# Option arguments for Archiver
AFLAGS = rcs

# I want to save the path to libgcc, libc.a and libm.a for linking.
# I can get them from the gcc frontend, using some options.
# See gcc documentation
LIB_GCC_PATH = ${shell ${CC} ${CFLAGS} -print-libgcc-file-name}
LIBC_PATH = ${shell ${CC} ${CFLAGS} -print-file-name=libc.a}
LIBM_PATH = ${shell ${CC} ${CFLAGS} -print-file-name=libm.a}


#==============================================================================
#                         Project properties
#==============================================================================

# Project name (W/O .c extension eg. "main")
PROJECT_NAME = mp3plib

SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)

#==============================================================================
#                      Rules to make the target
#==============================================================================

#make all rule
all: $(OBJS) ${PROJECT_NAME}.a

%.o: %.c
	@echo
	@echo Compiling $<...
	$(CC) -c $(CFLAGS) ${<} -o ${@}

${PROJECT_NAME}.a: $(OBJS)
	@echo
	@echo [Generating mp3plib]
	$(AR) $(AFLAGS) ${PROJECT_NAME}.a $(OBJS)

# make clean rule
clean:
	rm -f *.o *.a *.d

