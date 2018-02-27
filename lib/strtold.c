#include <stdlib.h>
#include <locale.h>

long double strtold (const char *__restrict s00, char **__restrict se)
{
	return strtod(s00, se);
}

long double strtold_l (const char *__restrict s00, char **__restrict se, __attribute__ ((unused)) locale_t loc)
{
	return strtod(s00, se);
}
