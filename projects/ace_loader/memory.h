
#define HEAP_MAP_SIZE	32

#define WK_SIZE		0x5e3000
#define WK_MEM_SIZE	0x11f000

// used to keep track of mapped heap
// for future unmapping
typedef struct
{
	void *src; // HEAP
	void *dst; // mirror
	uint64_t size;
} heap_map_t;

extern void *wkBase;

extern void *map_base;
extern uint64_t map_size;

extern void *heap_base;
extern uint64_t heap_size;

void mem_info();
int mem_make_block();
int mem_destroy_block();
int mem_heap_cleanup();
int mem_get_heap();
int mem_install_hook(void *hook_func);

