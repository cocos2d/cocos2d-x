/* Version number of package */
#define VERSION "2.5.0"

#ifdef _WIN32
/* protobuf config.h for MSVC.  On other platforms, this is generated
 * automatically by autoheader / autoconf / configure. */

/* the location of <hash_map> */
#define HASH_MAP_H <hash_map>

/* the namespace of hash_map/hash_set */
// Apparently Microsoft decided to move hash_map *back* to the std namespace
// in MSVC 2010:
//   http://blogs.msdn.com/vcblog/archive/2009/05/25/stl-breaking-changes-in-visual-studio-2010-beta-1.aspx
// TODO(kenton):  Use unordered_map instead, which is available in MSVC 2010.
#if _MSC_VER < 1310 || _MSC_VER >= 1600
#define HASH_NAMESPACE std
#else
#define HASH_NAMESPACE stdext
#endif

/* the location of <hash_set> */
#define HASH_SET_H <hash_set>

/* define if the compiler has hash_map */
#define HAVE_HASH_MAP 1

/* define if the compiler has hash_set */
#define HAVE_HASH_SET 1

/* define if you want to use zlib.  See readme.txt for additional
 * requirements. */
// #define HAVE_ZLIB 1


#else

/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* the name of <hash_map> */
#define HASH_MAP_CLASS unordered_map

/* the location of <unordered_map> or <hash_map> */
#define HASH_MAP_H <unordered_map>

/* the namespace of hash_map/hash_set */
#define HASH_NAMESPACE std

/* the name of <hash_set> */
#define HASH_SET_CLASS unordered_set

/* the location of <unordered_set> or <hash_set> */
#define HASH_SET_H <unordered_set>

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 1

/* Define to 1 if you have the `ftruncate' function. */
#define HAVE_FTRUNCATE 1

/* define if the compiler has hash_map */
#define HAVE_HASH_MAP 1

/* define if the compiler has hash_set */
#define HAVE_HASH_SET 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `memset' function. */
#define HAVE_MEMSET 1

/* Define to 1 if you have the `mkdir' function. */
#define HAVE_MKDIR 1

/* Define if you have POSIX threads libraries and header files. */
#define HAVE_PTHREAD 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `strchr' function. */
#define HAVE_STRCHR 1

/* Define to 1 if you have the `strerror' function. */
#define HAVE_STRERROR 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strtol' function. */
#define HAVE_STRTOL 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Enable classes using zlib compression. */
#define HAVE_ZLIB 1

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Name of package */
#define PACKAGE "protobuf"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "protobuf@googlegroups.com"

/* Define to the full name of this package. */
#define PACKAGE_NAME "Protocol Buffers"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "Protocol Buffers 2.5.0"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "protobuf"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "2.5.0"

/* Define to necessary symbol if this constant uses a non-standard name on
   your system. */
/* #undef PTHREAD_CREATE_JOINABLE */

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# define _ALL_SOURCE 1
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
/* Enable threading extensions on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# define _TANDEM_SOURCE 1
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif

/* Define to 1 if on MINIX. */
/* #undef _MINIX */

/* Define to 2 if the system does not provide POSIX.1 features except with
   this defined. */
/* #undef _POSIX_1_SOURCE */

/* Define to 1 if you need to in order for `stat' and other things to work. */
/* #undef _POSIX_SOURCE */

#endif