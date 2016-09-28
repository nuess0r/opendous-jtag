# opendous-jtag
This project implments MCU part of a simple USB-JTAG converter using Atmel AVR

This is firmware for AT90USB162 MCU for making simple USB-JTAG interface
primary goal is to replace parallel port based adapters (Wiggler and alike).

Patches for openocd and urjtag are included in patches directory. 

To compile make sure that you have AVR gnu toolchain installed and LUFA 
library ( http://www.fourwalledcubicle.com/LUFA.php ). 

To connect to the actual hardware one must connect pins of PORTB as following:

TDI  0
TMS  1
TCK  4
TDO  5

EMU  6 (optional)
TRST 2 (optinal)
SRST 3 (optinal)

Maximum achievable speed is about 60KHz . Speed control is implemented 
in firmware, but not in the patches for UrJtag and openocd yet. So, 
the interface will always run at maximum speed.


# Credits
This project is cloned from [opendous-jtag on Google code](https://code.google.com/archive/p/opendous-jtag/)

opendous-jtag by Vladimir S. Fonov implementing the improvments from eStick-jtag, by Cahya Wirawan based on LUFA demo applications by Dean Camera and Denver Gingerich.

# License
Released under the MIT Licence.
