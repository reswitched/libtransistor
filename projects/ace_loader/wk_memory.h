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

// install exit hook in webkit
int wk_mem_install_hook(void *hook_func);

// remove 'uncached' flag from all HEAP pages
int wk_mem_heap_cleanup();
