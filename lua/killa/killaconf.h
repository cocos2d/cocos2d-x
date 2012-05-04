/* ========================================================================== */
/*   Configuration file for Killa                                             */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#ifndef KCONFIG_H_
#define KCONFIG_H_

#include <limits.h>
#include <stddef.h>


/*
** ==================================================================
** Search for "@@" to find all configurable definitions.
** ===================================================================
*/


/*
@@ KILLA_ANSI controls the use of non-ansi features.
** CHANGE it (define it) if you want Killa to avoid the use of any
** non-ansi feature or library.
*/
#if !defined(KILLA_ANSI) && defined(__STRICT_ANSI__)
#define KILLA_ANSI
#endif


#if !defined(KILLA_ANSI) && defined(_WIN32) && !defined(_WIN32_WCE)
#define KILLA_WIN		/* enable goodies for regular Windows platforms */
#endif

#if defined(KILLA_WIN)
#define KILLA_DL_DLL
#define KILLA_USE_AFORMAT       /* assume 'printf' handles 'aA' specifiers */
#endif



#if defined(KILLA_USE_LINUX)
#define KILLA_USE_POSIX
#define KILLA_USE_DLOPEN        /* needs an extra library: -ldl */
#define KILLA_USE_READLINE      /* needs some extra libraries */
#define KILLA_USE_STRTODHEX     /* assume 'strtod' handles hexa formats */
#define KILLA_USE_AFORMAT       /* assume 'printf' handles 'aA' specifiers */
#define KILLA_USE_LONGLONG      /* assume support for long long */
#endif

#if defined(KILLA_USE_MACOSX)
#define KILLA_USE_POSIX
#define KILLA_USE_DLOPEN        /* does not need -ldl */
#define KILLA_USE_READLINE      /* needs an extra library: -lreadline */
#define KILLA_USE_STRTODHEX     /* assume 'strtod' handles hexa formats */
#define KILLA_USE_AFORMAT       /* assume 'printf' handles 'aA' specifiers */
#define KILLA_USE_LONGLONG      /* assume support for long long */
#endif



/*
@@ KILLA_USE_POSIX includes all functionality listed as X/Open System
@* Interfaces Extension (XSI).
** CHANGE it (define it) if your system is XSI compatible.
*/
#if defined(KILLA_USE_POSIX)
#define KILLA_USE_MKSTEMP
#define KILLA_USE_ISATTY
#define KILLA_USE_POPEN
#define KILLA_USE_ULONGJMP
#define KILLA_USE_GMTIME_R
#endif



/*
@@ KILLA_PATH_DEFAULT is the default path that Killa uses to look for
@* Killa libraries.
@@ KILLA_CPATH_DEFAULT is the default path that Killa uses to look for
@* C libraries.
** CHANGE them if your machine has a non-conventional directory
** hierarchy or if you want to install your libraries in
** non-conventional directories.
*/
#if defined(_WIN32)	/* { */
/*
** In Windows, any exclamation mark ('!') in the path is replaced by the
** path of the directory of the executable file of the current process.
*/
#define KILLA_LDIR	"!\\killa\\"
#define KILLA_CDIR	"!\\"
#define KILLA_PATH_DEFAULT  \
		KILLA_LDIR"?.kia;"  KILLA_LDIR"?\\init.kia;" \
		KILLA_CDIR"?.kia;"  KILLA_CDIR"?\\init.kia;" ".\\?.kia"
#define KILLA_CPATH_DEFAULT \
		KILLA_CDIR"?.dll;" KILLA_CDIR"loadall.dll;" ".\\?.dll"

#else			/* }{ */

#define KILLA_VDIR	KILLA_VERSION_MAJOR "." KILLA_VERSION_MINOR "/"
#define KILLA_ROOT	"/usr/local/"
#define KILLA_LDIR	KILLA_ROOT "share/killa/" KILLA_VDIR
#define KILLA_CDIR	KILLA_ROOT "lib/killa/" KILLA_VDIR
#define KILLA_PATH_DEFAULT  \
		KILLA_LDIR"?.kia;"  KILLA_LDIR"?/init.kia;" \
		KILLA_CDIR"?.kia;"  KILLA_CDIR"?/init.kia;" "./?.kia"
#define KILLA_CPATH_DEFAULT \
		KILLA_CDIR"?.so;" KILLA_CDIR"loadall.so;" "./?.so"
#endif			/* } */


/*
@@ KILLA_DIRSEP is the directory separator (for submodules).
** CHANGE it if your machine does not use "/" as the directory separator
** and is not Windows. (On Windows Killa automatically uses "\".)
*/
#if defined(_WIN32)
#define KILLA_DIRSEP	"\\"
#else
#define KILLA_DIRSEP	"/"
#endif


/*
@@ KILLA_ENV is the name of the variable that holds the current
@@ environment, used to access global names.
** CHANGE it if you do not like this name.
*/
#define KILLA_ENV		"global"


/*
@@ KILLA_API is a mark for all core API functions.
@@ KILLALIB_API is a mark for all auxiliary library functions.
@@ KILLAMOD_API is a mark for all standard library opening functions.
** CHANGE them if you need to define those functions in some special way.
** For instance, if you want to create one Windows DLL with the core and
** the libraries, you may want to use the following definition (define
** KILLA_BUILD_AS_DLL to get it).
*/
#if defined(KILLA_BUILD_AS_DLL)	/* { */

#if defined(KILLA_CORE) || defined(KILLA_LIB)	/* { */
#define KILLA_API __declspec(dllexport)
#else						/* }{ */
#define KILLA_API __declspec(dllimport)
#endif						/* } */

#else				/* }{ */

#define KILLA_API		extern

#endif				/* } */


/* more often than not the libs go together with the core */
#define KILLALIB_API	KILLA_API
#define KILLAMOD_API	KILLALIB_API


/*
@@ KILLAI_FUNC is a mark for all extern functions that are not to be
@* exported to outside modules.
@@ KILLAI_DDEF and KILLAI_DDEC are marks for all extern (const) variables
@* that are not to be exported to outside modules (KILLAI_DDEF for
@* definitions and KILLAI_DDEC for declarations).
** CHANGE them if you need to mark them in some special way. Elf/gcc
** (versions 3.2 and later) mark them as "hidden" to optimize access
** when Killa is compiled as a shared library. Not all elf targets support
** this attribute. Unfortunately, gcc does not offer a way to check
** whether the target offers that support, and those without support
** give a warning about it. To avoid these warnings, change to the
** default definition.
*/
#if defined(__GNUC__) && ((__GNUC__*100 + __GNUC_MINOR__) >= 302) && \
    defined(__ELF__)		/* { */
#define KILLAI_FUNC	__attribute__((visibility("hidden"))) extern
#define KILLAI_DDEC	KILLAI_FUNC
#define KILLAI_DDEF	/* empty */

#else				/* }{ */
#define KILLAI_FUNC	extern
#define KILLAI_DDEC	extern
#define KILLAI_DDEF	/* empty */
#endif				/* } */



/*
@@ KILLA_QL describes how error messages quote program elements.
** CHANGE it if you want a different appearance.
*/
#define KILLA_QL(x)	"'" x "'"
#define KILLA_QS		KILLA_QL("%s")


/*
@@ KILLA_IDSIZE gives the maximum size for the description of the source
@* of a function in debug information.
** CHANGE it if you want a different size.
*/
#define KILLA_IDSIZE	60


/*
@@ killai_writestring/killai_writeline define how 'print' prints its results.
** They are only used in libraries and the stand-alone program. (The #if
** avoids including 'stdio.h' everywhere.)
*/
#if defined(KILLA_LIB) || defined(KILLA_C_)
#include <stdio.h>
#define killai_writestring(s,l)	fwrite((s), sizeof(char), (l), stdout)
#define killai_writeline()	(killai_writestring("\n", 1), fflush(stdout))
#endif

/*
@@ killai_writestringerror defines how to print error messages.
** (A format string with one argument is enough for Killa...)
*/
#define killai_writestringerror(s,p) \
	(fprintf(stderr, (s), (p)), fflush(stderr))





/*
** {==================================================================
** Compatibility with previous versions
** ===================================================================
*/

/*
@@ KILLA_COMPAT_ALL controls all compatibility options.
** You can define it to get all options, or change specific options
** to fit your specific needs.
*/
#if defined(KILLA_COMPAT_ALL)	/* { */

/*
@@ KILLA_COMPAT_UNPACK controls the presence of global 'unpack'.
** You can replace it with 'table.unpack'.
*/
#define KILLA_COMPAT_UNPACK

/*
@@ KILLA_COMPAT_LOADERS controls the presence of table 'package.loaders'.
** You can replace it with 'package.searchers'.
*/
#define KILLA_COMPAT_LOADERS

/*
@@ macro 'killa_cpcall' emulates deprecated function killa_cpcall.
** You can call your C function directly (with light C functions).
*/
#define killa_cpcall(L,f,u)  \
	(killa_pushcfunction(L, (f)), \
	 killa_pushlightuserdata(L,(u)), \
	 killa_pcall(L,1,0,0))


/*
@@ KILLA_COMPAT_LOG10 defines the function 'log10' in the math library.
** You can rewrite 'log10(x)' as 'log(x, 10)'.
*/
#define KILLA_COMPAT_LOG10

/*
@@ KILLA_COMPAT_LOADSTRING defines the function 'loadstring' in the base
** library. You can rewrite 'loadstring(s)' as 'load(s)'.
*/
#define KILLA_COMPAT_LOADSTRING

/*
@@ KILLA_COMPAT_MAXN defines the function 'maxn' in the table library.
*/
#define KILLA_COMPAT_MAXN

/*
@@ The following macros supply trivial compatibility for some
** changes in the API. The macros themselves document how to
** change your code to avoid using them.
*/
#define killa_strlen(L,i)   killa_rawlen(L, (i))

#define killa_objlen(L,i)   killa_rawlen(L, (i))

#define killa_equal(L,idx1,idx2)    killa_compare(L,(idx1),(idx2),KILLA_OPEQ)
#define killa_lessthan(L,idx1,idx2) killa_compare(L,(idx1),(idx2),KILLA_OPLT)

/*
@@ KILLA_COMPAT_MODULE controls compatibility with previous
** module functions 'module' (Killa) and 'killaL_register' (C).
*/
#define KILLA_COMPAT_MODULE

#endif				/* } */

/* }================================================================== */



/*
@@ KILLAI_BITSINT defines the number of bits in an int.
** CHANGE here if Killa cannot automatically detect the number of bits of
** your machine. Probably you do not need to change this.
*/
/* avoid overflows in comparison */
#if INT_MAX-20 < 32760		/* { */
#define KILLAI_BITSINT	16
#elif INT_MAX > 2147483640L	/* }{ */
/* int has at least 32 bits */
#define KILLAI_BITSINT	32
#else				/* }{ */
#error "you must define KILLAI_BITSINT with number of bits in an integer"
#endif				/* } */


/*
@@ KILLA_INT32 is an signed integer with exactly 32 bits.
@@ KILLAI_UMEM is an unsigned integer big enough to count the total
@* memory used by Killa.
@@ KILLAI_MEM is a signed integer big enough to count the total memory
@* used by Killa.
** CHANGE here if for some weird reason the default definitions are not
** good enough for your machine. Probably you do not need to change
** this.
*/
#if KILLAI_BITSINT >= 32		/* { */
#define KILLA_INT32	int
#define KILLAI_UMEM	size_t
#define KILLAI_MEM	ptrdiff_t
#else				/* }{ */
/* 16-bit ints */
#define KILLA_INT32	long
#define KILLAI_UMEM	unsigned long
#define KILLAI_MEM	long
#endif				/* } */


/*
@@ KILLAI_MAXSTACK limits the size of the Killa stack.
** CHANGE it if you need a different limit. This limit is arbitrary;
** its only purpose is to stop Killa to consume unlimited stack
** space (and to reserve some numbers for pseudo-indices).
*/
#if KILLAI_BITSINT >= 32
#define KILLAI_MAXSTACK		1000000
#else
#define KILLAI_MAXSTACK		15000
#endif

/* reserve some space for error handling */
#define KILLAI_FIRSTPSEUDOIDX	(-KILLAI_MAXSTACK - 1000)




/*
@@ KILLAL_BUFFERSIZE is the buffer size used by the lauxlib buffer system.
** CHANGE it if it uses too much C-stack space.
*/
#define KILLAL_BUFFERSIZE		BUFSIZ




/*
** {==================================================================
@@ KILLA_NUMBER is the type of numbers in Killa.
** CHANGE the following definitions only if you want to build Killa
** with a number type different from double. You may also need to
** change killa_number2int & killa_number2integer.
** ===================================================================
*/

#define KILLA_NUMBER_DOUBLE
#define KILLA_NUMBER	double

/*
@@ KILLAI_UACNUMBER is the result of an 'usual argument conversion'
@* over a number.
*/
#define KILLAI_UACNUMBER	double


/*
@@ KILLA_NUMBER_SCAN is the format for reading numbers.
@@ KILLA_NUMBER_FMT is the format for writing numbers.
@@ killa_number2str converts a number to a string.
@@ KILLAI_MAXNUMBER2STR is maximum size of previous conversion.
*/
#define KILLA_NUMBER_SCAN		"%lf"
#define KILLA_NUMBER_FMT		"%.14g"
#define killa_number2str(s,n)	sprintf((s), KILLA_NUMBER_FMT, (n))
#define KILLAI_MAXNUMBER2STR	32 /* 16 digits, sign, point, and \0 */


/*
@@ killa_str2number converts a decimal numeric string to a number.
@@ killa_strx2number converts an hexadecimal numeric string to a number.
** In C99, 'strtod' do both conversions. C89, however, has no function
** to convert floating hexadecimal strings to numbers. For these
** systems, you can leave 'killa_strx2number' undefined and Killa will
** provide its own implementation.
*/
#define killa_str2number(s,p)	strtod((s), (p))

#if defined(KILLA_USE_STRTODHEX)
#define killa_strx2number(s,p)	strtod((s), (p))
#endif


/*
@@ The killai_num* macros define the primitive operations over numbers.
*/

/* the following operations need the math library */
#if defined(KOBJECT_C_) || defined(KVM_C_)
#include <math.h>
#define killai_nummod(L,a,b)	((a) - floor((a)/(b))*(b))
#define killai_numpow(L,a,b)	(pow(a,b))
#endif

/* these are quite standard operations */
#if defined(KILLA_CORE)
#define killai_numadd(L,a,b)    ((a)+(b))
#define killai_numsub(L,a,b)    ((a)-(b))
#define killai_nummul(L,a,b)    ((a)*(b))
#define killai_numdiv(L,a,b)    ((a)/(b))
#define killai_numunm(L,a)      (-(a))
#define killai_numeq(a,b)       ((a)==(b))
#define killai_numlt(L,a,b)     ((a)<(b))
#define killai_numle(L,a,b)     ((a)<=(b))
#define killai_numisnan(L,a)    (!killai_numeq((a), (a)))
#endif



/*
@@ KILLA_INTEGER is the integral type used by killa_pushinteger/killa_tointeger.
** CHANGE that if ptrdiff_t is not adequate on your machine. (On most
** machines, ptrdiff_t gives a good choice between int or long.)
*/
#define KILLA_INTEGER	ptrdiff_t

/*
@@ KILLA_UNSIGNED is the integral type used by killa_pushunsigned/killa_tounsigned.
** It must have at least 32 bits.
*/
#define KILLA_UNSIGNED	unsigned KILLA_INT32


#if defined(KILLA_CORE)		/* { */

#if defined(KILLA_NUMBER_DOUBLE) && !defined(KILLA_ANSI)	/* { */

/* On a Microsoft compiler on a Pentium, use assembler to avoid clashes
   with a DirectX idiosyncrasy */
#if defined(KILLA_WIN) && defined(_MSC_VER) && defined(_M_IX86)	/* { */

#define KILLA_MS_ASMTRICK

#else				/* }{ */
/* the next definition uses a trick that should work on any machine
   using IEEE754 with a 32-bit integer type */

#define KILLA_IEEE754TRICK

/*
@@ KILLA_IEEEENDIAN is the endianness of doubles in your machine
** (0 for little endian, 1 for big endian); if not defined, Killa will
** check it dynamically.
*/
/* check for known architectures */
#if defined(__i386__) || defined(__i386) || defined(__X86__) || \
    defined (__x86_64)
#define KILLA_IEEEENDIAN	0
#elif defined(__POWERPC__) || defined(__ppc__)
#define KILLA_IEEEENDIAN	1
#endif

#endif				/* } */

#endif			/* } */

#endif			/* } */

/* }================================================================== */


/*
@@ KILLA_NANTRICK_LE/KILLA_NANTRICK_BE controls the use of a trick to
** pack all types into a single double value, using NaN values to
** represent non-number values. The trick only works on 32-bit machines
** (ints and pointers are 32-bit values) with numbers represented as
** IEEE 754-2008 doubles with conventional endianess (12345678 or
** 87654321), in CPUs that do not produce signaling NaN values (all NaNs
** are quiet).
*/
#if defined(KILLA_CORE) && \
    defined(KILLA_NUMBER_DOUBLE) && !defined(KILLA_ANSI)	/* { */

/* little-endian architectures that satisfy those conditions */
#if defined(__i386__) || defined(__i386) || defined(__X86__) || \
    defined(_M_IX86)

#define KILLA_NANTRICK_LE

#endif

#endif							/* } */




/* =================================================================== */

/*
** Local configuration. You can use this space to add your redefinitions
** without modifying the main part of the file.
*/



#endif

