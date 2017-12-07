
extern char http_hostname[128];

int http_init(const char *hostname);
void http_paste_ip(uint32_t *target);

int http_get_file(const char *path, void *buff, uint64_t maxsize);

