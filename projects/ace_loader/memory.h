// initialize memory allocator
int mem_init();

// dump mapping info
void mem_dump_info();

// allocate clean type-5 memory
void *mem_alloc_pages(size_t min, size_t max, size_t *actual);

// free pages allocated with mem_alloc_pages
bool mem_free_pages(void *pages);

// allocate the largest block available
void *mem_alloc_largest(size_t *size);
