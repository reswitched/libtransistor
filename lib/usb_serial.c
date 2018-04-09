#include<libtransistor/ipc/usb.h>
#include<libtransistor/fd.h>
#include<libtransistor/svc.h>
#include<libtransistor/util.h>
#include<libtransistor/internal_util.h>
#include<libtransistor/usb_serial.h>
#include<libtransistor/alloc_pages.h>

#include<string.h>
#include<stdio.h>

const bool USB_SERIAL_DEBUG_ENABLED = false;
const size_t USB_SERIAL_TRANSFER_BUFFER_SIZE = 0x4000;

#define usb_serial_debug(...) if(USB_SERIAL_DEBUG_ENABLED) printf(__VA_ARGS__)

static usb_descriptor_data_t descriptor_data = {
	.id_vendor = 0x1209, // https://github.com/pidcodes/pidcodes.github.com/pull/313
	.id_product = 0x8b00,
	.bcd_device = 0x0100,
	.manufacturer = "ReSwitched",
	.product = "TransistorUSBSerial",
	.serial_number = "SerialNumber",
};

static usb_endpoint_descriptor_t endpoint_in_descriptor = {
	.bLength = sizeof(usb_endpoint_descriptor_t),
	.bDescriptorType = TRN_USB_DT_ENDPOINT,
	.bEndpointAddress = TRN_USB_ENDPOINT_IN,
	.bmAttributes = TRN_USB_TRANSFER_TYPE_BULK,
	.wMaxPacketSize = 0x200,
	.bInterval = 0,
};

static usb_endpoint_descriptor_t endpoint_out_descriptor = {
	.bLength = sizeof(usb_endpoint_descriptor_t),
	.bDescriptorType = TRN_USB_DT_ENDPOINT,
	.bEndpointAddress = TRN_USB_ENDPOINT_OUT,
	.bmAttributes = TRN_USB_TRANSFER_TYPE_BULK,
	.wMaxPacketSize = 0x200,
	.bInterval = 0,
};

static usb_interface_descriptor_t interface_descriptor = {
	.bLength = 0x9,
	.bDescriptorType = TRN_USB_DT_INTERFACE,
	.bInterfaceNumber = USB_DS_INTERFACE_NUMBER_AUTO,
	.bAlternateSetting = 0x00,
	.bNumEndpoints = 0x00,
	.bInterfaceClass = 0xFF,
	.bInterfaceSubClass = 0x00,
	.bInterfaceProtocol = 0x00,
	.iInterface = 0x00
};

static result_t wait_for_state(revent_h event, usb_ds_state_t state) {
	uint32_t current_state;
	result_t r = RESULT_OK;
	svcResetSignal(event);
	LIB_ASSERT_OK(fail, usb_ds_get_state(&current_state));
	usb_serial_debug("currently in 0x%x...\n", current_state);
	while(current_state != state) {
		uint32_t handle_idx;
		usb_serial_debug("waiting for 0x%x...\n", state);
		r = svcWaitSynchronization(&handle_idx, &event, 1, 10000000000);
		if(r != RESULT_OK && r != 0xea01) {
			return r;
		}
		if(r == RESULT_OK) {
			LIB_ASSERT_OK(fail, svcResetSignal(event));
		}
		LIB_ASSERT_OK(fail, usb_ds_get_state(&current_state));
		usb_serial_debug("state updated -> 0x%x\n", current_state);
	}
fail:
	return r;
}

static void dump_report(usb_ds_report_t *report) {
	if(USB_SERIAL_DEBUG_ENABLED) {
		usb_serial_debug("report: (%d entries)\n", report->entry_count);
		for(uint32_t i = 0; i < report->entry_count; i++) {
			usb_ds_report_entry_t entry = report->entries[i];
			usb_serial_debug("  [%d]: urb 0x%x, requested 0x%x bytes, transferred 0x%x bytes, status 0x%x\n",
			                 i, entry.urb_id, entry.requested_size, entry.transferred_size, entry.urb_status);
			
		}
		usb_serial_debug("hexdump of report:\n");
		hexdump(report, sizeof(*report));
		usb_serial_debug("end report\n");
	}
}

static usb_ds_report_entry_t *find_entry(usb_ds_report_t *report, uint32_t urb_id) {
	for(uint32_t i = 0; i < report->entry_count; i++) {
		if(report->entries[i].urb_id == urb_id) {
			return &report->entries[i];
		}
	}
	return NULL;
}

static usb_ds_interface_t interface;
static usb_ds_endpoint_t endpoint_in;
static usb_ds_endpoint_t endpoint_out;
static void *buffer;
static revent_h completion_in;
static revent_h completion_out;

static int usb_serial_initializations = 0;

result_t usb_serial_init() {
	if(usb_serial_initializations++ > 0) {
		return RESULT_OK;
	}
	
	result_t r;
	
	LIB_ASSERT_OK(fail, usb_init());

	revent_h usb_state_event = 0xFFFFFFFF;
	LIB_ASSERT_OK(fail_usb, usb_ds_get_state_change_event(&usb_state_event));

	usb_serial_debug("binding device...\n");
	LIB_ASSERT_OK(fail_usb,              usb_ds_bind_device(2));
	usb_serial_debug("bound\n");
	LIB_ASSERT_OK(fail_usb,              usb_ds_bind_client_process(0xffff8001));
	LIB_ASSERT_OK(fail_usb,              usb_ds_set_vid_pid_bcd(&descriptor_data));
	LIB_ASSERT_OK(fail_usb,              usb_ds_get_interface(&interface_descriptor, "usb", &interface));
	LIB_ASSERT_OK(fail_usb_interface,    usb_ds_interface_get_endpoint(&interface, &endpoint_in_descriptor,  &endpoint_in));
	LIB_ASSERT_OK(fail_usb_endpoint_in,  usb_ds_interface_get_endpoint(&interface, &endpoint_out_descriptor, &endpoint_out));
	LIB_ASSERT_OK(fail_usb_endpoint_out, usb_ds_interface_enable(&interface));
	usb_serial_debug("enabled interface\n");

	buffer = alloc_pages(USB_SERIAL_TRANSFER_BUFFER_SIZE, USB_SERIAL_TRANSFER_BUFFER_SIZE, NULL);
	if(buffer == NULL) {
		r = LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
		goto fail_usb_endpoint_out;
	}

	LIB_ASSERT_OK(fail_buffer,        svcSetMemoryAttribute(buffer, USB_SERIAL_TRANSFER_BUFFER_SIZE, 0x8, 0x8));
	LIB_ASSERT_OK(fail_buffer_ma,     usb_ds_get_completion_event(&endpoint_in,  &completion_in));
	LIB_ASSERT_OK(fail_completion_in, usb_ds_get_completion_event(&endpoint_out, &completion_out));
	wait_for_state(usb_state_event, 5);

	svcCloseHandle(usb_state_event);
	return RESULT_OK;
	
fail_completion_in:
	svcCloseHandle(completion_in);
fail_buffer_ma:
	svcSetMemoryAttribute(buffer, USB_SERIAL_TRANSFER_BUFFER_SIZE, 0x0, 0x0);
fail_buffer:
	free_pages(buffer);
fail_usb_endpoint_out:
	usb_ds_close_endpoint(&endpoint_out);
fail_usb_endpoint_in:
	usb_ds_close_endpoint(&endpoint_in);
fail_usb_interface:
	usb_ds_close_interface(&interface);
fail_usb:
	if(usb_state_event != 0xFFFFFFFF) {
		svcCloseHandle(usb_state_event);
	}
	usb_finalize();
fail:
	usb_serial_initializations--;
	return r != RESULT_OK;
}

static void usb_serial_force_finalize() {
	svcCloseHandle(completion_out);
	svcCloseHandle(completion_in);
	svcSetMemoryAttribute(buffer, USB_SERIAL_TRANSFER_BUFFER_SIZE, 0x0, 0x0);
	free_pages(buffer);
	usb_ds_close_endpoint(&endpoint_out);
	usb_ds_close_endpoint(&endpoint_in);
	usb_ds_close_interface(&interface);
	usb_finalize();
}

void usb_serial_finalize() {
	if(--usb_serial_initializations == 0) {
		usb_serial_force_finalize();
	}
}

static __attribute__((destructor)) void usb_serial_destruct() {
	if(usb_serial_initializations > 0) {
		usb_serial_force_finalize();
	}
}

result_t usb_serial_write(const void *data, size_t size, size_t *bytes_written) {
	INITIALIZATION_GUARD(usb_serial);

	result_t r;
	uint32_t urb_id;
	uint32_t handle_idx;
	usb_ds_report_t report;

	if(size > USB_SERIAL_TRANSFER_BUFFER_SIZE) {
		size = USB_SERIAL_TRANSFER_BUFFER_SIZE;
	}
	
	memcpy(buffer, data, size);
	LIB_ASSERT_OK(fail, usb_ds_post_buffer_async(&endpoint_in,  buffer, size, &urb_id));
	LIB_ASSERT_OK(fail, svcWaitSynchronization(&handle_idx, &completion_in, 1, 50000000000));
	LIB_ASSERT_OK(fail, usb_ds_get_report_data(&endpoint_in, &report));
	usb_ds_report_entry_t *entry = find_entry(&report, urb_id);
	if(entry == NULL) {
		r = LIBTRANSISTOR_ERR_USB_REPORT_NOT_FOUND;
		goto fail;
	}
	if(entry->urb_status != 3) {
		r = LIBTRANSISTOR_ERR_USB_TRANSFER_FAILED;
		goto fail;
	}
	*bytes_written = entry->transferred_size;
fail:
	return r;
}

result_t usb_serial_read(void *data, size_t size, size_t *bytes_read) {
	INITIALIZATION_GUARD(usb_serial);

	result_t r;
	uint32_t urb_id;
	uint32_t handle_idx;
	usb_ds_report_t report;

	if(size > USB_SERIAL_TRANSFER_BUFFER_SIZE) {
		size = USB_SERIAL_TRANSFER_BUFFER_SIZE;
	}

	LIB_ASSERT_OK(fail, usb_ds_post_buffer_async(&endpoint_out, buffer, 10, &urb_id));
	LIB_ASSERT_OK(fail, svcWaitSynchronization(&handle_idx, &completion_out, 1, 50000000000));
	LIB_ASSERT_OK(fail, usb_ds_get_report_data(&endpoint_out, &report));
	usb_ds_report_entry_t *entry = find_entry(&report, urb_id);
	if(entry == NULL) {
		r = LIBTRANSISTOR_ERR_USB_REPORT_NOT_FOUND;
		goto fail;
	}
	if(entry->urb_status != 3) {
		r = LIBTRANSISTOR_ERR_USB_TRANSFER_FAILED;
		goto fail;
	}
	memcpy(data, buffer, entry->transferred_size);
	*bytes_read = entry->transferred_size;
fail:
	return r;
}

static result_t usb_serial_file_read(void *data, void *buf, size_t size, size_t *bytes_read) {
	return usb_serial_read(buf, size, bytes_read);
}

static result_t usb_serial_file_write(void *data, const void *buf, size_t size, size_t *bytes_written) {
	return usb_serial_write(buf, size, bytes_written);
}

static result_t usb_serial_file_release(trn_file_t *file) {
	usb_serial_finalize();
	return RESULT_OK;
}

static trn_file_ops_t usb_serial_fops = {
	.seek = NULL,
	.read = usb_serial_file_read,
	.write = usb_serial_file_write,
	.release = usb_serial_file_release
};

int usb_serial_open_fd() {
	result_t r;
	LIB_ASSERT_OK(fail, usb_serial_init());
	return fd_create_file(&usb_serial_fops, NULL);
fail:
	return -trn_result_to_errno(r);
}
