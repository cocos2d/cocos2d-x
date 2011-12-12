/*
 * Summary: compile-time version informations on Windows
 * Description: compile-time version informations for the XML library
 *              when compiled on the Windows platform
 *
 * Copy: See Copyright for the status of this software.
 *
 * Author: Daniel Veillard
 */

#ifndef __XML_VERSION_H__
#define __XML_VERSION_H__

#ifdef __cplusplus
extern "C" {
#endif

/*
 * use those to be sure nothing nasty will happen if
 * your library and includes mismatch
 */
#ifndef LIBXML2_COMPILING_MSCCDEF
extern void xmlCheckVersion(int version);
#endif /* LIBXML2_COMPILING_MSCCDEF */

/**
 * LIBXML_DOTTED_VERSION:
 *
 * the version string like "1.2.3"
 */
#define LIBXML_DOTTED_VERSION "2.4.26"

/**
 * LIBXML_VERSION:
 *
 * the version number: 1.2.3 value is 1002003
 */
#define LIBXML_VERSION 20426

/**
 * LIBXML_VERSION_STRING:
 *
 * the version number string, 1.2.3 value is "1002003"
 */
#define LIBXML_VERSION_STRING "20426"

/**
 * LIBXML_TEST_VERSION:
 *
 * Macro to check that the libxml version in use is compatible with
 * the version the software has been compiled against
 */
#define LIBXML_TEST_VERSION xmlCheckVersion(20426);

#if 0
/**
 * WITH_TRIO:
 *
 * defined if the trio support need to be configured in
 */
#define WITH_TRIO
#else
/**
 * WITHOUT_TRIO:
 *
 * defined if the trio support should not be configured in
 */
#define WITHOUT_TRIO
#endif

/**
 * LIBXML_THREAD_ENABLED:
 *
 * Whether the thread support is configured in
 */
#if 0
#define LIBXML_THREAD_ENABLED
#endif

/**
 * LIBXML_FTP_ENABLED:
 *
 * Whether the FTP support is configured in
 */
#if 1
#define LIBXML_FTP_ENABLED
#endif

/**
 * LIBXML_HTTP_ENABLED:
 *
 * Whether the HTTP support is configured in
 */
#if 1
#define LIBXML_HTTP_ENABLED
#endif

/**
 * LIBXML_HTML_ENABLED:
 *
 * Whether the HTML support is configured in
 */
#if 1
#define LIBXML_HTML_ENABLED
#endif

/**
 * LIBXML_CATALOG_ENABLED:
 *
 * Whether the Catalog support is configured in
 */
#if 1
#define LIBXML_CATALOG_ENABLED
#endif

/**
 * LIBXML_DOCB_ENABLED:
 *
 * Whether the SGML Docbook support is configured in
 */
#if 1
#define LIBXML_DOCB_ENABLED
#endif

/**
 * LIBXML_XPATH_ENABLED:
 *
 * Whether XPath is configured in
 */
#if 1
#define LIBXML_XPATH_ENABLED
#endif

/**
 * LIBXML_XPTR_ENABLED:
 *
 * Whether XPointer is configured in
 */
#if 1
#define LIBXML_XPTR_ENABLED
#endif

/**
 * LIBXML_C14N_ENABLED:
 *
 * Whether the Canonicalization support is configured in
 */
#if 0
#define LIBXML_C14N_ENABLED
#endif

/**
 * LIBXML_XINCLUDE_ENABLED:
 *
 * Whether XInclude is configured in
 */
#if 1
#define LIBXML_XINCLUDE_ENABLED
#endif

/**
 * LIBXML_ICONV_ENABLED:
 *
 * Whether iconv support is available
 */
#if 0
#define LIBXML_ICONV_ENABLED
#endif

/**
 * LIBXML_DEBUG_ENABLED:
 *
 * Whether Debugging module is configured in
 */
#if 1
#define LIBXML_DEBUG_ENABLED
#endif

/**
 * DEBUG_MEMORY_LOCATION:
 *
 * Whether the memory debugging is configured in
 */
#if 0
#define DEBUG_MEMORY_LOCATION
#endif

/**
 * LIBXML_DLL_IMPORT:
 *
 * Used on Windows (MS C compiler only) to declare a variable as 
 * imported from the library. This macro should be empty when compiling
 * libxml itself. It should expand to __declspec(dllimport)
 * when the client code includes this header, and that only if the client
 * links dynamically against libxml.
 * For this to work, we need three macros. One tells us which compiler is
 * being used and luckily the compiler defines such a thing: _MSC_VER. The
 * second macro tells us if we are compiling libxml or the client code and
 * we define the macro IN_LIBXML on the compiler's command line for this 
 * purpose. The third macro, LIBXML_STATIC, must be defined by any client 
 * code which links against libxml statically. 
 */
#ifndef LIBXML_DLL_IMPORT
#if defined(_MSC_VER) && !defined(IN_LIBXML) && !defined(LIBXML_STATIC)
#define LIBXML_DLL_IMPORT __declspec(dllimport)
#else
#define LIBXML_DLL_IMPORT
#endif
#endif

/**
 * ATTRIBUTE_UNUSED:
 *
 * Macro used to signal to GCC unused function parameters
 */
#ifdef __GNUC__
#ifdef HAVE_ANSIDECL_H
#include <ansidecl.h>
#endif
#ifndef ATTRIBUTE_UNUSED
#define ATTRIBUTE_UNUSED
#endif
#else
#define ATTRIBUTE_UNUSED
#endif

/*
 * #pragma comment(lib, "iconv.lib")
 *
 * pragma understood my MS compiler which enables a conditional link with
 * iconv.
 */
#ifdef _MSC_VER
#if defined LIBXML_ICONV_ENABLED && !defined LIBXML2_COMPILING_MSCCDEF
#pragma comment(lib, "iconv.lib")
#endif
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif
