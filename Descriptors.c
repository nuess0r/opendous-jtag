/*
    opendous-jtag by Vladimir S. Fonov, based on
    eStick-jtag, by Cahya Wirawan <cahya@gmx.at> 
    Based on opendous-jtag by Vladimir Fonov and LUFA demo applications by Dean Camera and Denver Gingerich.
    Released under the MIT Licence.
*/

/** \file
 *
 *  USB Device Descriptors, for library use when in USB device mode. Descriptors are special 
 *  computer-readable structures which the host requests upon device enumeration, to determine
 *  the device's capabilities and functions.  
 */

#include "Descriptors.h"

 /** Device descriptor structure. This descriptor, located in FLASH memory, describes the overall
 *  device characteristics, including the supported USB version, control endpoint size and the
 *  number of device configurations. The descriptor is read out by the USB host when the enumeration
 *  process begins.
 */
 
 
const USB_Descriptor_Device_t PROGMEM DeviceDescriptor =
{
	.Header                 = {.Size = sizeof(USB_Descriptor_Device_t), .Type = DTYPE_Device},
		
	.USBSpecification       = VERSION_BCD(01,10,00),
	.Class                  = 0x02,
	.SubClass               = 0x00,
	.Protocol               = 0x00,
				
	.Endpoint0Size          = ENDPOINT_CONTROLEP_DEFAULT_SIZE,
	
#ifdef ESTICK
	.VendorID              = 0x1781,
	.ProductID             = 0xC0C0,
	.ReleaseNumber         = 0x0001,
#else //OPENDOUS
	.VendorID              = 0x03EB,
	.ProductID             = 0x204F,
	.ReleaseNumber         = 0x0001,	
#endif 
		
	.ManufacturerStrIndex   = 0x01,
	.ProductStrIndex        = 0x02,
	.SerialNumStrIndex      = USE_INTERNAL_SERIAL,
		
	.NumberOfConfigurations = 1
};

/** Configuration descriptor structure. This descriptor, located in FLASH memory, describes the usage
 *  of the device in one of its supported configurations, including information about any device interfaces
 *  and endpoints. The descriptor is read out by the USB host during the enumeration process when selecting
 *  a configuration so that the host may correctly communicate with the USB device.
 */

const USB_Descriptor_Configuration_t PROGMEM ConfigurationDescriptor =
{
		.Config = 
		{
			.Header                 = 
				{.Size = sizeof(USB_Descriptor_Configuration_Header_t), 
				 .Type = DTYPE_Configuration},

			.TotalConfigurationSize = sizeof(USB_Descriptor_Configuration_t),
			.TotalInterfaces        = 1,
				
			.ConfigurationNumber    = 1,
			.ConfigurationStrIndex  = NO_DESCRIPTOR,
				
			.ConfigAttributes       = 0,
			
			.MaxPowerConsumption    = USB_CONFIG_POWER_MA(100)
		},
		
		.Interface = 
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), 
			                           .Type = DTYPE_Interface},

			.InterfaceNumber        = 0,
			.AlternateSetting       = 0,
			
			.TotalEndpoints         = 2,
				
			.Class                  = 0xff,
			.SubClass               = 0x00,
			.Protocol               = 0x00,
				
			.InterfaceStrIndex      = NO_DESCRIPTOR
		},
		
		.DataOutEndpoint = 
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), 
			                           .Type = DTYPE_Endpoint},
										 
			.EndpointAddress        = (ENDPOINT_DIR_OUT | OUT_EP),
			.Attributes             = (EP_TYPE_BULK | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
			.EndpointSize           = IN_EP_SIZE,
			.PollingIntervalMS      = 0x00
		},
		
		.DataInEndpoint = 
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), 
			                           .Type = DTYPE_Endpoint},
										 
			.EndpointAddress        = (ENDPOINT_DIR_IN |IN_EP),
			.Attributes             = (EP_TYPE_BULK | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
			.EndpointSize           = OUT_EP_SIZE,
			.PollingIntervalMS      = 0x00
		}
};

/** Language descriptor structure. This descriptor, located in FLASH memory, is returned when the host requests
 *  the string descriptor with index 0 (the first index). It is actually an array of 16-bit integers, which indicate
 *  via the language ID table available at USB.org what languages the device supports for its string descriptors.
 */
const USB_Descriptor_String_t PROGMEM LanguageString =
{
	.Header                 = {.Size = USB_STRING_LEN(1), .Type = DTYPE_String},
		
	.UnicodeString          = {LANGUAGE_ID_ENG}
};

/** Manufacturer descriptor string. This is a Unicode string containing the manufacturer's details in human readable
 *  form, and is read out upon request by the host when the appropriate string ID is requested, listed in the Device
 *  Descriptor.
 */
const USB_Descriptor_String_t PROGMEM ManufacturerString =
{
	.Header                 = {.Size = USB_STRING_LEN(7), .Type = DTYPE_String},
		
	.UnicodeString          = L"Ilmarin"
};

/** Product descriptor string. This is a Unicode string containing the product's details in human readable form,
 *  and is read out upon request by the host when the appropriate string ID is requested, listed in the Device
 *  Descriptor.
 */
const USB_Descriptor_String_t PROGMEM ProductString =
{
	.Header                 = {.Size = USB_STRING_LEN(12), .Type = DTYPE_String},
		
	.UnicodeString          = L"opendous-jtag"
};

/** This function is called by the library when in device mode, and must be overridden (see StdDescriptors.h
 *  documentation) by the application code so that the address and size of a requested descriptor can be given
 *  to the USB library. When the device recieves a Get Descriptor request on the control endpoint, this function
 *  is called so that the descriptor details can be passed back and the appropriate descriptor sent back to the
 *  USB host.
 */
uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue, const uint8_t wIndex, const void** const DescriptorAddress)
{
	const uint8_t  DescriptorType   = (wValue >> 8);
	const uint8_t  DescriptorNumber = (wValue & 0xFF);

	void*    Address = NULL;
	uint16_t Size    = NO_DESCRIPTOR;

	switch (DescriptorType)
	{
		case DTYPE_Device:
			Address = (void*)&DeviceDescriptor;
			Size    = sizeof(USB_Descriptor_Device_t);
			break;
		case DTYPE_Configuration: 
			Address = (void*)&ConfigurationDescriptor;
			Size    = sizeof(USB_Descriptor_Configuration_t);
			break;
		case DTYPE_String:
			switch (DescriptorNumber)
			{
				case 0x00:
					Address = (void*)&LanguageString;
					Size    = pgm_read_byte(&LanguageString.Header.Size);
					break;
				case 0x01:
					Address = (void*)&ManufacturerString;
					Size    = pgm_read_byte(&ManufacturerString.Header.Size);
					break;
				case 0x02:
					Address = (void*)&ProductString;
					Size    = pgm_read_byte(&ProductString.Header.Size);
					break;
			}
			
			break;
	}
	
	*DescriptorAddress = Address;
	return Size;
}
