/**
 * @file libtransistor/ipc/pm.h
 * @brief Process management
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<libtransistor/types.h>

/**
 * @brief Initialize Process Manager
 */
result_t pm_init();

/**
 * @brief Terminate a process by title ID
 */
result_t pm_terminate_process_by_title_id(uint64_t title_id);

/**
 * @brief Finalize Process Manager
 */
void pm_finalize();

#ifdef __cplusplus
}
#endif
