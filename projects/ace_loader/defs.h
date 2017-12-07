
#define STDOUT_PORT	2991

#define make_ip(a,b,c,d)	((a) | ((b) << 8) | ((c) << 16) | ((d) << 24))

extern FILE custom_stdout;
extern int std_sck;

void exit_loader();

