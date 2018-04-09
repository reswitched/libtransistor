/**
 * @file libtransistor/usb_serial.h
 * @brief USB Serial Console
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<libtransistor/types.h>

/**
 * @brief Initialize USB serial console
 */
result_t usb_serial_init();

/**
 * @brief Write data over the USB serial console
 */
result_t usb_serial_write(const void *data, size_t size, size_t *bytes_written);

/**
 * @brief Read data from the USB serial console
 */
result_t usb_serial_read(void *data, size_t size, size_t *bytes_read);

/**
 * @brief Create a file descriptor for the USB serial console
 * Does not require \ref usb_serial_init to have been called
 */
int usb_serial_open_fd();

/**
 * @brief Finalize USB serial console
 */
void usb_serial_finalize();

#ifdef __cplusplus
}
#endif
