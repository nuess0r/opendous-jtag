/*
    opendous-jtag by Vladimir S. Fonov, based on
    eStick-jtag, by Cahya Wirawan <cahya@gmx.at> 
    Based on opendous-jtag by Vladimir Fonov and LUFA demo applications by Dean Camera and Denver Gingerich.
    Released under the MIT Licence.
*/

#ifndef _DESCRIPTORS_H_
#define _DESCRIPTORS_H_

	/* Includes: */
		#include <LUFA/Drivers/USB/USB.h>
		#include <avr/pgmspace.h>

	/* Macros: */
		#define IN_EP                       1
		#define OUT_EP                      2
		#define IN_EP_SIZE                  64
		#define OUT_EP_SIZE                 64

	/* Type Defines: */
		typedef struct
		{
			USB_Descriptor_Configuration_Header_t Config;
			USB_Descriptor_Interface_t            Interface;
			USB_Descriptor_Endpoint_t             DataInEndpoint;
			USB_Descriptor_Endpoint_t             DataOutEndpoint;
		} USB_Descriptor_Configuration_t;

	/* External Variables: */
		extern const USB_Descriptor_Configuration_t PROGMEM ConfigurationDescriptor;

	/* Function Prototypes: */
	/*
		uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue, const uint8_t wIndex, void** const DescriptorAddress)
		                           ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);*/
															 
		uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue, const uint8_t wIndex, const void **const DescriptorAddress)
											ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);															 

#endif
