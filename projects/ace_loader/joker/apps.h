
#define MAXAPPS	16	// can be more, memory is the limit
#define MAXOPTIONS 8	// can't be more, unless scrolling is added

#define APP_MAXNAME	32
#define APP_MAXINFO	32
#define APP_MAXPATH	32

#define OPTION_TITLE_LEN	16
#define OPTION_NROPATH_LEN	16

enum
{
	OPTYPE_ENUM0, // pick only one from list; selected option will be added; at least one must be selected
	OPTYPE_ENUM1, // pick only one from list; selected option will be added; no selection needed
	OPTYPE_BOOLEAN, // pick any from list; picked options will be added
	NUM_OPTION_TYPES
};

// since options have variable size,
// linked list is used
typedef struct option_s
{
	struct option_s *next;
	char title[OPTION_TITLE_LEN];
	uint8_t type; // option type
	uint8_t choice; // for menu navigation
	uint16_t value; // bit mask selection
	// suboptions follow; NUL terminated strings, first char 0xFF = no more suboptions
} option_t;

typedef struct
{
	char name[APP_MAXNAME];
	char info[APP_MAXINFO];
	char path[APP_MAXPATH];
	icon8bit_t icon;
	option_t *options;
} app_t;

extern app_t apps[MAXAPPS];
extern char filetmp[96*1024];

int A_Init();

