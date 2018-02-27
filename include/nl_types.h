#ifndef NL_TYPES_H
#define NL_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/* Value for FLAG parameter of `catgets' to say we want XPG4 compliance.  */
#define NL_CAT_LOCALE 1

/* Message catalog descriptor type.  */
typedef void *nl_catd;

/* Type used by `nl_langinfo'.  */
typedef int nl_item;

/* Open message catalog for later use, returning descriptor. */
extern nl_catd catopen (const char *__cat_name, int __flag) __attribute__((__nonnull__(1)));

/* Return translation with NUMBER in SET of CATALOG */
extern char *catgets (nl_catd __catalog, int __set, int __number,
		      const char *__string) __attribute__((__nonnull__(1)));

/* Close message CATALOG. */
extern int catclose (nl_catd __catalog) __attribute__((__nonnull__(1)));

#ifdef __cplusplus
}
#endif

#endif