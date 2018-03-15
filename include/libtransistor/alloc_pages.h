/**
 * @file libtransistor/alloc_pages.h
 * @brief Page allocation functions
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<libtransistor/types.h>

#include<stdint.h>

/**
 * @brief Allocates memory pages
 *
 * This will allocate a page-aligned region of memory that is at
 * least min bytes long and no more than max bytes long. The actual
 * length of the memory region is written to \ref actual.
 *
 * If \ref min == \ref max, you are guaranteed to either get that much
 * memory or no memory at all, and can pass NULL in \ref actual.
 *
 * The pointer returned by this function should be passed to \ref free_pages
 * before the program terminates.
 *
 * If alloc_pages has been set in \ref loader_config, that allocator
 * will be used instead of the application's self-hosted one.
 *
 * @param min Lower bound on how much memory to allocate (in bytes)
 * @param max Upper bound on how much memory to allocate (in bytes)
 * @param actual Output for how much memory was actually allocated. Can be NULL.
 * @returns Pointer to the allocated region, or NULL if it was not able to be allocated.
 */
void *alloc_pages(size_t min, size_t max, size_t *actual);

/**
 * @brief Frees memory pages returned from \ref alloc_pages
 *
 * Frees a region of memory returned from \ref alloc_pages. The memory
 * should be RW-, type 5 (HEAP), and have no attributes set.
 *
 * If alloc_pages has been set in \ref loader_config, that allocator
 * will be used instead of the application's self-hosted one.
 *
 * @param pages Pointer returned by \ref alloc_pages
 * @returns True if there was an error freeing the memory region
 */
bool free_pages(void *pages);

/**
 * @brief Initialize the application's page allocator
 *
 * This is called in crt0 when appropriate. If the heap has been overridden
 * by \ref loader_config, the overridden heap will be used as a memory pool.
 * Otherwise, the allocator will use any available heap regions, attempting
 * to resize the heap when neccessary.
 */
result_t ap_init();

/**
 * @brief Mark a region of memory as not available for use with alloc_pages
 *
 * This should only be used if the application is self-hosting the page
 * allocator (no page allocator is specified in \ref loader_config).
 *
 * This is called by crt0 when \ref LCONFIG_KEY_LOCK_REGION is encountered
 * parsing the \ref loader_config, and must be called before \ref ap_init.
 *
 * This is useful if certain regions of the heap are used in ways that cannot
 * be detected by \ref svcQueryMemory and are unsafe to overwrite, such as
 * the application's stack.
 *
 * @param base Pointer to the memory region to blacklist
 * @param size Size of the memory region to blacklist (in bytes)
 */
result_t ap_lock_region(void *base, size_t size);

/**
 * @brief Search for additional usable heap regions
 *
 * This should only be used if the application is self-hosting the page
 * allocator (no page allocator is specified in \ref loader_config).
 *
 * This will use \ref svcQueryMemory to probe the address space for heap
 * regions suitable for use, and add them to the memory pool.
 */
result_t ap_probe_full_address_space();

/**
 * @brief Allocate the largest available region of memory
 *
 * This should only be used if the application is self-hosting the page
 * allocator (no page allocator is specified in \ref loader_config).
 *
 * Regions allocated from this function should be freed with
 * \ref free_pages, just like regions allocated with \ref alloc_pages.
 *
 * @param size Output for how large the allocated region was
 * @returns Pointer to the allocated region
 */
void *ap_alloc_largest(size_t *size);

/**
 * @brief Print debug info
 *
 * This should only be used if the application is self-hosting the page
 * allocator (no page allocator is specified in \ref loader_config).
 */
void ap_dump_info();

#ifdef __cplusplus
}
#endif
