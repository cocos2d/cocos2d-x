/* This source file must have a .cpp extension so that all C++ compilers
   recognize the extension without flags.  Borland does not know .cxx for
   example.  */
#ifndef __cplusplus
# error "A C compiler has been selected for C++."
#endif

#if defined(__COMO__)
# define COMPILER_ID "Comeau"

#elif defined(__INTEL_COMPILER) || defined(__ICC)
# define COMPILER_ID "Intel"

#elif defined(__BORLANDC__)
# define COMPILER_ID "Borland"

#elif defined(__WATCOMC__)
# define COMPILER_ID "Watcom"

#elif defined(__SUNPRO_CC)
# define COMPILER_ID "SunPro"

#elif defined(__HP_aCC)
# define COMPILER_ID "HP"

#elif defined(__DECCXX)
# define COMPILER_ID "Compaq"

#elif defined(__IBMCPP__)
# if defined(__COMPILER_VER__)
#  define COMPILER_ID "zOS"
# elif __IBMCPP__ >= 800
#  define COMPILER_ID "XL"
# else
#  define COMPILER_ID "VisualAge"
# endif

#elif defined(__PGI)
# define COMPILER_ID "PGI"

#elif defined(__PATHSCALE__)
# define COMPILER_ID "PathScale"

#elif defined(__GNUC__)
# define COMPILER_ID "GNU"

#elif defined(_MSC_VER)
# define COMPILER_ID "MSVC"

#elif defined(__ADSPBLACKFIN__) || defined(__ADSPTS__) || defined(__ADSP21000__)
/* Analog Devices C++ compiler for Blackfin, TigerSHARC and
   SHARC (21000) DSPs */
# define COMPILER_ID "ADSP"

#elif defined(_SGI_COMPILER_VERSION) || defined(_COMPILER_VERSION)
# define COMPILER_ID "MIPSpro"

/* This compiler is either not known or is too old to define an
   identification macro.  Try to identify the platform and guess that
   it is the native compiler.  */
#elif defined(__sgi)
# define COMPILER_ID "MIPSpro"

#elif defined(__hpux) || defined(__hpua)
# define COMPILER_ID "HP"

#else /* unknown compiler */
# define COMPILER_ID ""

#endif

/* Construct the string literal in pieces to prevent the source from
   getting matched.  Store it in a pointer rather than an array
   because some compilers will just produce instructions to fill the
   array rather than assigning a pointer to a static array.  */
char* info_compiler = "INFO" ":" "compiler[" COMPILER_ID "]";

/* Identify known platforms by name.  */
#if defined(__linux) || defined(__linux__) || defined(linux)
# define PLATFORM_ID "Linux"

#elif defined(__CYGWIN__)
# define PLATFORM_ID "Cygwin"

#elif defined(__MINGW32__)
# define PLATFORM_ID "MinGW"

#elif defined(__APPLE__)
# define PLATFORM_ID "Darwin"

#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
# define PLATFORM_ID "Windows"

#elif defined(__FreeBSD__) || defined(__FreeBSD)
# define PLATFORM_ID "FreeBSD"

#elif defined(__NetBSD__) || defined(__NetBSD)
# define PLATFORM_ID "NetBSD"

#elif defined(__OpenBSD__) || defined(__OPENBSD)
# define PLATFORM_ID "OpenBSD"

#elif defined(__sun) || defined(sun)
# define PLATFORM_ID "SunOS"

#elif defined(_AIX) || defined(__AIX) || defined(__AIX__) || defined(__aix) || defined(__aix__)
# define PLATFORM_ID "AIX"

#elif defined(__sgi) || defined(__sgi__) || defined(_SGI)
# define PLATFORM_ID "IRIX"

#elif defined(__hpux) || defined(__hpux__)
# define PLATFORM_ID "HP-UX"

#elif defined(__HAIKU) || defined(__HAIKU__) || defined(_HAIKU)
# define PLATFORM_ID "Haiku"
/* Haiku also defines __BEOS__ so we must 
   put it prior to the check for __BEOS__
*/

#elif defined(__BeOS) || defined(__BEOS__) || defined(_BEOS)
# define PLATFORM_ID "BeOS"

#elif defined(__QNX__) || defined(__QNXNTO__)
# define PLATFORM_ID "QNX"

#elif defined(__tru64) || defined(_tru64) || defined(__TRU64__)
# define PLATFORM_ID "Tru64"

#elif defined(__riscos) || defined(__riscos__)
# define PLATFORM_ID "RISCos"

#elif defined(__sinix) || defined(__sinix__) || defined(__SINIX__)
# define PLATFORM_ID "SINIX"

#elif defined(__UNIX_SV__)
# define PLATFORM_ID "UNIX_SV"

#elif defined(__bsdos__)
# define PLATFORM_ID "BSDOS"

#elif defined(_MPRAS) || defined(MPRAS)
# define PLATFORM_ID "MP-RAS"

#elif defined(__osf) || defined(__osf__)
# define PLATFORM_ID "OSF1"

#elif defined(_SCO_SV) || defined(SCO_SV) || defined(sco_sv)
# define PLATFORM_ID "SCO_SV"

#elif defined(__ultrix) || defined(__ultrix__) || defined(_ULTRIX)
# define PLATFORM_ID "ULTRIX"

#elif defined(__XENIX__) || defined(_XENIX) || defined(XENIX)
# define PLATFORM_ID "Xenix"

#else /* unknown platform */
# define PLATFORM_ID ""

#endif

/* For windows compilers MSVC and Intel we can determine
   the architecture of the compiler being used.  This is becase
   the compilers do not have flags that can change the architecture,
   but rather depend on which compiler is being used
*/
#if defined(_WIN32) && defined(_MSC_VER)
# if defined(_M_IA64)
#  define ARCHITECTURE_ID "IA64"

# elif defined(_M_X64) || defined(_M_AMD64)
#  define ARCHITECTURE_ID "x64" 

# elif defined(_M_IX86)
#  define ARCHITECTURE_ID "X86"

# else /* unknown architecture */
#  define ARCHITECTURE_ID ""
# endif

#else
#  define ARCHITECTURE_ID ""
#endif

/* Construct the string literal in pieces to prevent the source from
   getting matched.  Store it in a pointer rather than an array
   because some compilers will just produce instructions to fill the
   array rather than assigning a pointer to a static array.  */
char* info_platform = "INFO" ":" "platform[" PLATFORM_ID "]";
char* info_arch = "INFO" ":" "arch[" ARCHITECTURE_ID "]";



/*--------------------------------------------------------------------------*/

int main(int argc, char* argv[])
{
  int require = 0;
  require += info_compiler[argc];
  require += info_platform[argc];
  (void)argv;
  return require;
}
