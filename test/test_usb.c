#include<libtransistor/nx.h>

#include<stdio.h>

static usb_device_data_t device_data = {
	.id_vendor = 0x57e,
	.id_product = 0x4000,
	.bcd_device = 0x0100,
	.manufacturer = "ReSwitched",
	.product = "TransistorUSBTest",
	.serial_number = "SerialNumber",
};

static usb_endpoint_descriptor_t endpoint_descriptor = {
	.bLength = sizeof(usb_endpoint_descriptor_t),
	.bDescriptorType = TRN_USB_DT_ENDPOINT,
	.bEndpointAddress = TRN_USB_ENDPOINT_OUT,
	.bmAttributes = TRN_USB_TRANSFER_TYPE_BULK,
	.wMaxPacketSize = 0x200,
	.bInterval = 0,
};

#define TRACE_STATE r = usb_ds_get_state(&usb_state); printf("usb state: 0x%x -> 0x%x\n", r, usb_state);

/*static result_t wait_for_state(revent_h event, usb_ds_state_t state) {
	usb_ds_state_t current_state;
	result_t r = RESULT_OK;
	svcResetSignal(event);
	ASSERT_OK(fail, usb_ds_get_state(&current_state));
	while(current_state != state) {
		uint32_t handle_idx;
		printf("waiting...\n");
		ASSERT_OK(fail, svcWaitSynchronization(&handle_idx, &event, 1, 1000000000));
		ASSERT_OK(fail, svcResetSignal(event));
		ASSERT_OK(fail, usb_ds_get_state(&current_state));
		printf("state updated -> 0x%x\n", current_state);
	}
fail:
	return r;
}*/

int main() {
	result_t r;
	usb_ds_state_t usb_state;
	
	printf("initializing usb\n");
	ASSERT_OK(fail, usb_ds_init(2, &device_data));

	revent_h usb_state_event = 0xFFFFFFFF;
	printf("getting state change event\n");
	ASSERT_OK(fail_usb, usb_ds_get_state_change_event(&usb_state_event));
	printf("  -> 0x%x\n", usb_state_event);
	
	usb_ds_interface_t interface;
	printf("getting interface...\n");
	ASSERT_OK(fail_usb, usb_ds_get_interface(&usb_default_interface_descriptor, "usb", &interface));

	printf("obtained interface; object id = 0x%x\n", interface.object.object_id);
	
	usb_ds_endpoint_t endpoint;
	printf("getting endpoint...\n");
	ASSERT_OK(fail_usb_interface, usb_ds_interface_get_endpoint(&interface, &endpoint_descriptor, &endpoint));

	printf("enabling interface...\n");
	ASSERT_OK(fail_usb_endpoint, usb_ds_interface_enable(&interface));
	printf("enabled interface\n");
	
	printf("sleeping for 25 seconds\n");
	printf("  -> 0x%x\n", svcSleepThread(15000000000));
	TRACE_STATE;
	
fail_usb_endpoint:
	printf("closing endpoint...\n");
	usb_ds_close_endpoint(&endpoint);
fail_usb_interface:
	printf("closing interface...\n");
	usb_ds_close_interface(&interface);
fail_usb:
	if(usb_state_event != 0xFFFFFFFF) {
		svcCloseHandle(usb_state_event);
	}
	printf("finalizing usb..\n");
	usb_ds_finalize();
fail:
	return r != RESULT_OK;
}
