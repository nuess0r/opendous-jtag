# opendous-jtag
This project implments MCU part of a simple USB-JTAG converter using Atmel AVR

This is firmware for AT90USB162 MCU for making simple USB-JTAG interface
primary goal is to replace parallel port based adapters (Wiggler and alike).

Patches for openocd and urjtag are included in patches directory. 

To compile make sure that you have AVR gnu toolchain installed and [LUFA library]( http://www.fourwalledcubicle.com/LUFA.php). This version is using the LUFA Version 151115.

To connect to the actual hardware one must connect pins of PORTB as following:

    TDI  0
    TMS  1
    TCK  4
    TDO  5
    
    EMU  6 (optional)
    TRST 2 (optinal)
    SRST 3 (optinal)

Maximum achievable speed is about 60KHz. Speed control is implemented 
in firmware, but not in the patches for UrJtag and openocd yet. So, 
the interface will always run at maximum speed.

# Compile
It was tested with avr-gcc (GCC) 4.9.2 and avr-libc_1.8.0+Atmel3.5.0-1

Depending on the Board you use, you have to adjust the MCU and F_CPU values for correct controller type and clock frequency in the makefile. (Default value is now atmega32u4 and 16 MHz, correct for a Teensy 2.0 or a Arduino Leonardo)

You need to have the correct LUFA library in this path relative to this repository:

    ../lufa-LUFA-151115

Then a simple

    make

should compile the firmware without error or warning.

# Usage
You can use this JTAG adapter together with [OpenOCD](http://openocd.org/) or urjtag.

For urjtag use the patched version from mstarostik: [urjtag](https://github.com/mstarostik/urjtag)

urjtag should recognise the opendous-jtag automaticaly by using the command `cable probe`

# Credits
This project is cloned from [opendous-jtag on Google code](https://code.google.com/archive/p/opendous-jtag/)

opendous-jtag by Vladimir S. Fonov implementing the improvments from eStick-jtag, by Cahya Wirawan based on LUFA demo applications by Dean Camera and Denver Gingerich.

# License
Released under the MIT Licence.
