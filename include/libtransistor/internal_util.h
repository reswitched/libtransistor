/**
 * @file libtransistor/internal_util.h
 * @brief Various utility functions internal to libtransistor
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<libtransistor/err.h>

/**
 * @brief Asserts that the given module has been initialized, returning an appropriate \ref result_t if it has not.
 */
#define INITIALIZATION_GUARD(module) if(module ## _initializations <= 0) { return LIBTRANSISTOR_ERR_MODULE_NOT_INITIALIZED; }

/**
 * @brief Asserts that the given module has been initialized, returning if it has not.
 */
#define INITIALIZATION_GUARD_RETURN_VOID(module) if(module ## _initializations <= 0) { return; }

#ifdef __cplusplus
}
#endif
