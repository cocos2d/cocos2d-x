#ifndef _WCHAR_H_
#define _WCHAR_H_

#include <_ansi.h>

#include <sys/reent.h>

#define __need_size_t
#define __need_wchar_t
#define __need_wint_t
#include <stddef.h>

#define __need___va_list
#include <stdarg.h>

/* For _mbstate_t definition. */
#include <sys/_types.h>

#ifndef NULL
#define NULL	0
#endif

#ifndef WEOF
# define WEOF ((wint_t)-1)
#endif

#ifndef WCHAR_MIN
#define WCHAR_MIN 0
#endif

#ifndef WCHAR_MAX
#ifdef __WCHAR_MAX__
#define WCHAR_MAX __WCHAR_MAX__
#else
#define WCHAR_MAX 0x7fffffffu
#endif
#endif

_BEGIN_STD_C

/* As required by POSIX.1-2008, declare tm as incomplete type.
   The actual definition is in time.h. */
struct tm;

#ifndef _MBSTATE_T
#define _MBSTATE_T
typedef _mbstate_t mbstate_t;
#endif /* _MBSTATE_T */

wint_t	_EXFUN(btowc, (int));
int	_EXFUN(wctob, (wint_t));
size_t	_EXFUN(mbrlen, (const char * , size_t, mbstate_t *));
size_t	_EXFUN(mbrtowc, (wchar_t * , const char * , size_t, mbstate_t *));
size_t	_EXFUN(_mbrtowc_r, (struct _reent *, wchar_t * , const char * , 
			size_t, mbstate_t *));
int	_EXFUN(mbsinit, (const mbstate_t *));
size_t	_EXFUN(mbsnrtowcs, (wchar_t * , const char ** , size_t, size_t,
			mbstate_t *));
size_t	_EXFUN(_mbsnrtowcs_r, (struct _reent *, wchar_t * , const char ** ,
			size_t, size_t, mbstate_t *));
size_t	_EXFUN(mbsrtowcs, (wchar_t * , const char ** , size_t, mbstate_t *));
size_t	_EXFUN(_mbsrtowcs_r, (struct _reent *, wchar_t * , const char ** , size_t, mbstate_t *));
size_t	_EXFUN(wcrtomb, (char * , wchar_t, mbstate_t *));
size_t	_EXFUN(_wcrtomb_r, (struct _reent *, char * , wchar_t, mbstate_t *));
size_t	_EXFUN(wcsnrtombs, (char * , const wchar_t ** , size_t, size_t,
			mbstate_t *));
size_t	_EXFUN(_wcsnrtombs_r, (struct _reent *, char * , const wchar_t ** , 
			size_t, size_t, mbstate_t *));
size_t	_EXFUN(wcsrtombs, (char * , const wchar_t ** , size_t, mbstate_t *));
size_t	_EXFUN(_wcsrtombs_r, (struct _reent *, char * , const wchar_t ** , 
			size_t, mbstate_t *));
int	_EXFUN(wcscasecmp, (const wchar_t *, const wchar_t *));
wchar_t	*_EXFUN(wcscat, (wchar_t * , const wchar_t *));
wchar_t	*_EXFUN(wcschr, (const wchar_t *, wchar_t));
int	_EXFUN(wcscmp, (const wchar_t *, const wchar_t *));
int	_EXFUN(wcscoll, (const wchar_t *, const wchar_t *));
wchar_t	*_EXFUN(wcscpy, (wchar_t * , const wchar_t *));
wchar_t	*_EXFUN(wcpcpy, (wchar_t * , const wchar_t *));
wchar_t	*_EXFUN(wcsdup, (const wchar_t *));
wchar_t	*_EXFUN(_wcsdup_r, (struct _reent *, const wchar_t * ));
size_t	_EXFUN(wcscspn, (const wchar_t *, const wchar_t *));
size_t  _EXFUN(wcsftime, (wchar_t *, size_t, const wchar_t *, const struct tm *));
size_t	_EXFUN(wcslcat, (wchar_t *, const wchar_t *, size_t));
size_t	_EXFUN(wcslcpy, (wchar_t *, const wchar_t *, size_t));
size_t	_EXFUN(wcslen, (const wchar_t *));
int	_EXFUN(wcsncasecmp, (const wchar_t *, const wchar_t *, size_t));
wchar_t	*_EXFUN(wcsncat, (wchar_t * , const wchar_t * , size_t));
int	_EXFUN(wcsncmp, (const wchar_t *, const wchar_t *, size_t));
wchar_t	*_EXFUN(wcsncpy, (wchar_t *  , const wchar_t * , size_t));
wchar_t	*_EXFUN(wcpncpy, (wchar_t *  , const wchar_t * , size_t));
size_t	_EXFUN(wcsnlen, (const wchar_t *, size_t));
wchar_t	*_EXFUN(wcspbrk, (const wchar_t *, const wchar_t *));
wchar_t	*_EXFUN(wcsrchr, (const wchar_t *, wchar_t));
size_t	_EXFUN(wcsspn, (const wchar_t *, const wchar_t *));
wchar_t	*_EXFUN(wcsstr, (const wchar_t *, const wchar_t *));
wchar_t	*_EXFUN(wcstok, (wchar_t *, const wchar_t *, wchar_t **));
double _EXFUN(wcstod, (const wchar_t *, wchar_t **));
double _EXFUN(_wcstod_r, (struct _reent *, const wchar_t *, wchar_t **));
float _EXFUN(wcstof, (const wchar_t *, wchar_t **));
float _EXFUN(_wcstof_r, (struct _reent *, const wchar_t *, wchar_t **));
int	_EXFUN(wcswidth, (const wchar_t *, size_t));
size_t	_EXFUN(wcsxfrm, (wchar_t *, const wchar_t *, size_t));
int	_EXFUN(wcwidth, (const wchar_t));
wchar_t	*_EXFUN(wmemchr, (const wchar_t *, wchar_t, size_t));
int	_EXFUN(wmemcmp, (const wchar_t *, const wchar_t *, size_t));
wchar_t	*_EXFUN(wmemcpy, (wchar_t * , const wchar_t * , size_t));
wchar_t	*_EXFUN(wmemmove, (wchar_t *, const wchar_t *, size_t));
wchar_t	*_EXFUN(wmemset, (wchar_t *, wchar_t, size_t));

long    _EXFUN(wcstol, (const wchar_t *, wchar_t **, int));
long long _EXFUN(wcstoll, (const wchar_t *, wchar_t **, int));
unsigned long _EXFUN(wcstoul, (const wchar_t *, wchar_t **, int));
unsigned long long _EXFUN(wcstoull, (const wchar_t *, wchar_t **, int));
long    _EXFUN(_wcstol_r, (struct _reent *, const wchar_t *, wchar_t **, int));
long long _EXFUN(_wcstoll_r, (struct _reent *, const wchar_t *, wchar_t **, int));
unsigned long _EXFUN(_wcstoul_r, (struct _reent *, const wchar_t *, wchar_t **, int));
unsigned long long _EXFUN(_wcstoull_r, (struct _reent *, const wchar_t *, wchar_t **, int));

wint_t _EXFUN(fgetwc, (__FILE *));
wchar_t *_EXFUN(fgetws, (wchar_t *, int, __FILE *));
wint_t _EXFUN(fputwc, (wchar_t, __FILE *));
int _EXFUN(fputws, (const wchar_t *, __FILE *));
int _EXFUN (fwide, (__FILE *, int));
wint_t _EXFUN (getwc, (__FILE *));
wint_t _EXFUN (getwchar, (void));
wint_t _EXFUN(putwc, (wchar_t, __FILE *));
wint_t _EXFUN(putwchar, (wchar_t));
wint_t _EXFUN (ungetwc, (wint_t wc, __FILE *));

wint_t _EXFUN(_fgetwc_r, (struct _reent *, __FILE *));
wchar_t *_EXFUN(_fgetws_r, (struct _reent *, wchar_t *, int, __FILE *));
wint_t _EXFUN(_fputwc_r, (struct _reent *, wchar_t, __FILE *));
int _EXFUN(_fputws_r, (struct _reent *, const wchar_t *, __FILE *));
int _EXFUN (_fwide_r, (struct _reent *, __FILE *, int));
wint_t _EXFUN (_getwc_r, (struct _reent *, __FILE *));
wint_t _EXFUN (_getwchar_r, (struct _reent *ptr));
wint_t _EXFUN(_putwc_r, (struct _reent *, wchar_t, __FILE *));
wint_t _EXFUN(_putwchar_r, (struct _reent *, wchar_t));
wint_t _EXFUN (_ungetwc_r, (struct _reent *, wint_t wc, __FILE *));

__FILE *_EXFUN (open_wmemstream, (wchar_t **, size_t *));
__FILE *_EXFUN (_open_wmemstream_r, (struct _reent *, wchar_t **, size_t *));

#ifndef __VALIST
#ifdef __GNUC__
#define __VALIST __gnuc_va_list
#else
#define __VALIST char*
#endif
#endif

int	_EXFUN(fwprintf, (__FILE *, const wchar_t *, ...));
int	_EXFUN(swprintf, (wchar_t *, size_t, const wchar_t *, ...));
int	_EXFUN(vfwprintf, (__FILE *, const wchar_t *, __VALIST));
int	_EXFUN(vswprintf, (wchar_t *, size_t, const wchar_t *, __VALIST));
int	_EXFUN(vwprintf, (const wchar_t *, __VALIST));
int	_EXFUN(wprintf, (const wchar_t *, ...));

int	_EXFUN(_fwprintf_r, (struct _reent *, __FILE *, const wchar_t *, ...));
int	_EXFUN(_swprintf_r, (struct _reent *, wchar_t *, size_t, const wchar_t *, ...));
int	_EXFUN(_vfwprintf_r, (struct _reent *, __FILE *, const wchar_t *, __VALIST));
int	_EXFUN(_vswprintf_r, (struct _reent *, wchar_t *, size_t, const wchar_t *, __VALIST));
int	_EXFUN(_vwprintf_r, (struct _reent *, const wchar_t *, __VALIST));
int	_EXFUN(_wprintf_r, (struct _reent *, const wchar_t *, ...));

int	_EXFUN(fwscanf, (__FILE *, const wchar_t *, ...));
int	_EXFUN(swscanf, (const wchar_t *, const wchar_t *, ...));
int	_EXFUN(vfwscanf, (__FILE *, const wchar_t *, __VALIST));
int	_EXFUN(vswscanf, (const wchar_t *, const wchar_t *, __VALIST));
int	_EXFUN(vwscanf, (const wchar_t *, __VALIST));
int	_EXFUN(wscanf, (const wchar_t *, ...));

int	_EXFUN(_fwscanf_r, (struct _reent *, __FILE *, const wchar_t *, ...));
int	_EXFUN(_swscanf_r, (struct _reent *, const wchar_t *, const wchar_t *, ...));
int	_EXFUN(_vfwscanf_r, (struct _reent *, __FILE *, const wchar_t *, __VALIST));
int	_EXFUN(_vswscanf_r, (struct _reent *, const wchar_t *, const wchar_t *, __VALIST));
int	_EXFUN(_vwscanf_r, (struct _reent *, const wchar_t *, __VALIST));
int	_EXFUN(_wscanf_r, (struct _reent *, const wchar_t *, ...));

long double _EXFUN(wcstold, (const wchar_t *nptr, wchar_t **endptr)); /* XXX Emscripten */

#define getwc(fp)	fgetwc(fp)
#define putwc(wc,fp)	fputwc((wc), (fp))
#ifndef _REENT_ONLY
#define getwchar()	fgetwc(_REENT->_stdin)
#define putwchar(wc)	fputwc((wc), _REENT->_stdout)
#else
#define getwchar()	fgetwc(_impure_ptr->_stdin)
#define putwchar(wc)	fputwc((wc), _impure_ptr->_stdout)
#endif

_END_STD_C

#endif /* _WCHAR_H_ */
