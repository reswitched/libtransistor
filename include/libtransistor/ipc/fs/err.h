/**
 * @file libtransistor/ipc/fs/err.h
 * @brief Error definitions for Switch FS
 */

#pragma once

#include<libtransistor/err.h>

#define FSPSRV_RESULT(code) MAKE_RESULT(MODULE_FS, code)
#define FSPSRV_ERR_NOT_FOUND FSPSRV_RESULT(1)
#define FSPSRV_ERR_EXISTS FSPSRV_RESULT(2)
#define FSPSRV_ERR_DIRECTORY_NOT_EMPTY FSPSRV_RESULT(8)
