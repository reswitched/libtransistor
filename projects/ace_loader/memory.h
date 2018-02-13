// heap block for internal use
extern void *heap_base;
extern uint64_t heap_size;

// heap for NROs
extern void *map_base;
extern uint64_t map_size;

// dump mapping info
void mem_info();

// create one huge contiguous block from HEAP, put it in map_base and map_size
int mem_make_block();

// free created contiguous block
int mem_destroy_block();

// get biggest HEAP block
int mem_get_heap();
