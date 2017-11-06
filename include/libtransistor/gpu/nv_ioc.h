#pragma once

#define NVMAP_IOC_CREATE 0xC0080101
#define NVMAP_IOC_FROM_ID 0xC0080103
#define NVMAP_IOC_ALLOC 0xC0200104
#define NVMAP_IOC_PARAM 0xC00C0109
#define NVMAP_IOC_GET_ID 0xC008010E

typedef struct {
  uint32_t size; // in
  uint32_t handle; // out
} nvmap_ioc_create_args;

typedef struct {
  uint32_t id; // in
  uint32_t handle; // out
} nvmap_ioc_from_id_args;

typedef struct {
  uint32_t handle;
  uint32_t heapmask;
  uint32_t flags;
  uint32_t align;
  uint8_t kind;
  uint8_t pad[7];
  uint64_t addr;
} nvmap_ioc_alloc_args;

typedef struct {
  uint32_t handle;
  uint32_t param;
  uint32_t value;
} nvmap_ioc_param_args;

typedef struct {
  uint32_t id; // out
  uint32_t handle; // in
} nvmap_ioc_get_id_args;
