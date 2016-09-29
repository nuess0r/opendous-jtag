# Hey Emacs, this is a -*- makefile -*-
#----------------------------------------------------------------------------
#
#             LUFA Library
#     Copyright (C) Dean Camera, 2015.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#
# --------------------------------------
#         LUFA Project Makefile.
# --------------------------------------
#
# Run "make help" for target help.
#
# On command line:
#
# make all = Make software.
#
# make clean = Clean out built project files.
#
# make avrdude = Download the hex file to the device, using avrdude.
#                Please customize the avrdude settings below first!
#
#
# make doxygen = Generate DoxyGen documentation for the project (must have
#                DoxyGen installed)
#
# To rebuild project do "make clean" then "make all".
#----------------------------------------------------------------------------

ARCH = AVR8
# MCU name
#MCU = at90usb162
MCU = atmega32u4
#MCU = at90usb647


# Target board (see library "Board Types" documentation, USER or blank for projects not requiring
# LUFA board drivers). If USER is selected, put custom board drivers in a directory called 
# "Board" inside the application directory.
BOARD  = USER


# Processor frequency.
#     This will define a symbol, F_CPU, in all source code files equal to the 
#     processor frequency. You can then use this symbol in your source code to 
#     calculate timings. Do NOT tack on a 'UL' at the end, this will be done
#     automatically to create a 32-bit value in your source code.
#     Typical values are:
#         F_CPU =  1000000
#         F_CPU =  1843200
#         F_CPU =  2000000
#         F_CPU =  3686400
#         F_CPU =  4000000
#         F_CPU =  7372800
#         F_CPU =  8000000
#         F_CPU = 11059200
#         F_CPU = 14745600
#         F_CPU = 16000000
#         F_CPU = 18432000
#         F_CPU = 20000000
F_CPU = 16000000


# Input clock frequency.
#     This will define a symbol, F_CLOCK, in all source code files equal to the 
#     input clock frequency (before any prescaling is performed). This value may
#     differ from F_CPU if prescaling is used on the latter, and is required as the
#     raw input clock is fed directly to the PLL sections of the AVR for high speed
#     clock generation for the USB and other AVR subsections. Do NOT tack on a 'UL'
#     at the end, this will be done automatically to create a 32-bit value in your
#     source code.
#
#     If no clock division is performed on the input clock inside the AVR (via the
#     CPU clock adjust registers or the clock division fuses), this will be equal to F_CPU.
F_CLOCK = $(F_CPU)
F_USB   = $(F_CLOCK)


# Output format. (can be srec, ihex, binary)
FORMAT = ihex


# Target file name (without extension).
TARGET = opendous-jtag


# Object files directory
#     To put object files in current directory, use a dot (.), do NOT make
#     this an empty or blank macro!
OBJDIR = .


# Path to the LUFA library
#LUFA_PATH = ../LUFA_091223
LUFA_PATH = ../lufa-LUFA-151115/LUFA

# List C source files here. (C dependencies are automatically generated.)
SRC = opendous-jtag.c                                                 \
	  Descriptors.c                                               \
	  jtag_functions.c                                            \
	  $(LUFA_PATH)/Drivers/Peripheral/AVR8/Serial_AVR8.c \
	  $(LUFA_SRC_USB)

CC_FLAGS     = -DUSB_DEVICE_ONLY -DUSE_FLASH_DESCRIPTORS
LD_FLAGS     =

# Default target
all:

# Include LUFA build script makefiles
include $(LUFA_PATH)/Build/lufa_core.mk
include $(LUFA_PATH)/Build/lufa_sources.mk
include $(LUFA_PATH)/Build/lufa_build.mk
include $(LUFA_PATH)/Build/lufa_cppcheck.mk
include $(LUFA_PATH)/Build/lufa_doxygen.mk
include $(LUFA_PATH)/Build/lufa_avrdude.mk
include $(LUFA_PATH)/Build/lufa_atprogram.mk
