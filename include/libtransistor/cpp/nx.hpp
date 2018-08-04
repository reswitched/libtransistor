/**
 * @file libtransistor/cpp/nx.hpp
 * @brief Central Switch header. Includes all others (C++ version).
 */

#pragma once

#include<libtransistor/nx.h>

#include<libtransistor/cpp/types.hpp>
#include<libtransistor/cpp/ipc.hpp>
#include<libtransistor/cpp/ipcclient.hpp>
#include<libtransistor/cpp/ipcserver.hpp>
#include<libtransistor/cpp/svc.hpp>
#include<libtransistor/cpp/waiter.hpp>

// services
#include<libtransistor/cpp/ipc/hid.hpp>
#include<libtransistor/cpp/ipc/sm.hpp>
#include<libtransistor/cpp/ipc/usb_ds.hpp>
#include<libtransistor/cpp/ipc/usb.hpp>
