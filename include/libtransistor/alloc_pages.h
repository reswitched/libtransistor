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

#ifdef __cplusplus
}
#endif
