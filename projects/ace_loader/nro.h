#define NRO_MAX_ARG_BUF	0x1000
#define NRO_MAX_ARGS	16

#define NRO_MAGIC	0x304f524e

typedef struct {
	uint32_t unk00;
	uint32_t mod_hdr_offset;
	uint32_t unk08;
	uint32_t unk0C;
	uint32_t magic;
	uint32_t unk14;
	uint32_t nro_size;
	uint32_t unk1C;
	uint32_t text_offset;
	uint32_t text_size;
	uint32_t ro_offset;
	uint32_t ro_size;
	uint32_t data_offset;
	uint32_t data_size;
	uint32_t bss_size;
	uint32_t unk3C;
} nro_header_t;

int nro_load_count;
int nro_unload_fail;
int nro_loaded_count;

result_t nro_load(void *load_base, int in_size);
uint64_t nro_start();

uint64_t nro_execute(void *load_base, int in_size);

void nro_arg_name(const char *text);
void nro_add_arg(const char *text);
void nro_print_args();
