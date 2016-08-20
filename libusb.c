#include <stdio.h>
#include <libusb-1.0/libusb.h>
void print_dev(libusb_device *dev) {
	struct libusb_device_descriptor desc;
	int r = libusb_get_device_descriptor(dev, &desc);
	int bus_number = libusb_get_bus_number(dev);
	int device_number = libusb_get_device_address(dev);
	struct libusb_config_descriptor *config;
	const struct libusb_interface *inter;
	const struct libusb_interface_descriptor *inter_desc;
	const struct libusb_endpoint_descriptor *ep_desc;	
	libusb_get_config_descriptor(dev, 0, &config);
	inter = &config->interface[0];
	inter_desc = &inter->altsetting[0];

	if (r < 0) {
		printf("failed to get device descriptor");
		return;
	}
	printf("Bus %03d Device %03d: ID %04x:%04x \n",bus_number,device_number,desc.idVendor, desc.idProduct);
	printf("Device Descriptor:\n");
	printf(" bLength: %d\n", (int)desc.bLength);
	printf(" bDescriptorType: %d\n", (int)desc.bDescriptorType);
	printf(" bcdUSB: %d\n", (int)desc.bcdUSB);
	printf(" bDeviceClass: %d\n", (int)desc.bDeviceClass);
	printf(" bDeviceSubClass: %d\n", (int)desc.bDeviceSubClass);
	printf(" bDeviceProtocol: %d\n", (int)desc.bDeviceProtocol);
	printf(" bMaxPacketSize0: %d\n", (int)desc.bMaxPacketSize0);
	printf(" idVendor: %x\n", desc.idVendor);
	printf(" idProduct: %x\n", desc.idProduct);
	printf(" bcdDevice: %x\n", desc.bcdDevice);
	printf(" bNumConfigurations: %d\n", (int)desc.bNumConfigurations);
	printf(" Configuration Descriptor\n");
	printf("   bLength: %d\n", (int)config->bLength);
	printf("   bDescriptorType: %d\n", (int)config->bDescriptorType);
	printf("   wTotalLength: %d\n", (int)config->wTotalLength);
	printf("   bNumInterfaces: %d\n", (int)config->bNumInterfaces);
	printf("   bConfigurationValue: %d\n", (int)config->bConfigurationValue);
	printf("   iConfiguration: %d\n", (int)config->iConfiguration);
	printf("   bmAttributes: %d\n", (int)config->bmAttributes);
	printf("   MaxPower: %d\n", (int)config->MaxPower);

	inter_desc = &inter->altsetting[0];
	printf("   Interface Descriptors\n");
	printf("     bLength: %d\n", (int)inter_desc->bLength);
	printf("     bDescriptorType: %d\n", (int)inter_desc->bDescriptorType);
	printf("     bInterfaceNumber: %d\n", (int)inter_desc->bInterfaceNumber);
	printf("     bAlternateSetting: %d\n", (int)inter_desc->bAlternateSetting);
	printf("     bNumEndpoints: %d\n", (int)inter_desc->bNumEndpoints);
	printf("     bInterfaceClass: %d\n", (int)inter_desc->bInterfaceClass);
	printf("     bInterfaceSubClass: %d\n", (int)inter_desc->bInterfaceSubClass);
	printf("     bInterfaceProtocol: %d\n", (int)inter_desc->bInterfaceProtocol);
	printf("     iInterface: %d\n", (int)inter_desc->iInterface);

	ep_desc = &inter_desc->endpoint[0];
	printf("     Endpoint Descriptor\n");
	printf("       bLength: %d\n", (int)ep_desc->bLength);
	printf("       bDescriptorType %d\n", (int)ep_desc->bDescriptorType);
	printf("       bEndpointAddress: %x\n", (int)ep_desc->bEndpointAddress);
	printf("       bmAttributes: %d\n", (int)ep_desc->bmAttributes);
	printf("       wMaxPacketSize: %04x\n", (int)ep_desc->wMaxPacketSize);
	printf("       bInterval: %d\n", (int)ep_desc->bInterval);












}
int  main(int argc, char *argv[]){
	struct libusb_device **devs;
	int i,r,cnt;
	struct libusb_context *ctx = NULL;
	r = libusb_init(&ctx);
	if(r < 0) {
	printf("init error\n");
	return 0;
	}
	libusb_set_debug(ctx, 3);
	cnt = libusb_get_device_list(ctx, &devs);
	if (cnt < 0){
	printf("get device error\n");
	return 0;
	}
	for(i = 0; i < cnt; i++) {
		print_dev(devs[i]);
	}
	libusb_free_device_list(devs,1);
	libusb_exit(ctx);
	
	
	return 0;
}
