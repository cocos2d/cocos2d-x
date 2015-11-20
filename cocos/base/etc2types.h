/**
    @file   etc2types.h
    @note   etc2 typedefs and defines.
*/

/*
Copyright (c) 2010 The Khronos Group Inc.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and/or associated documentation files (the
"Materials"), to deal in the Materials without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Materials, and to
permit persons to whom the Materials are furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
unaltered in all copies or substantial portions of the Materials.
Any additions, deletions, or changes to the original source files
must be clearly indicated in accompanying documentation.

If only executable code is distributed, then the accompanying
documentation must state that "this software is based in part on the
work of the Khronos Group."

THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
*/

#ifndef _ETC2_TYPES_H_
#define _ETC2_TYPES_H_

#include "platform/CCGL.h"

/*
   typedefs
*/
typedef unsigned int    etc2_uint32_t;


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Error codes returned by library functions.
 */
typedef enum ETC2_error_code_t {
	ETC2_SUCCESS = 0,		 /*!< Operation was successful. */
	ETC2_FILE_OPEN_FAILED,	 /*!< The target file could not be opened. */
	ETC2_FILE_WRITE_ERROR,    /*!< An error occurred while writing to the file. */
	ETC2_GL_ERROR,            /*!< GL operations resulted in an error. */
	ETC2_INVALID_OPERATION,   /*!< The operation is not allowed in the current state. */
	ETC2_INVALID_VALUE,	     /*!< A parameter value was not valid */
	ETC2_NOT_FOUND,			 /*!< Requested key was not found */
	ETC2_OUT_OF_MEMORY,       /*!< Not enough memory to complete the operation. */
	ETC2_UNEXPECTED_END_OF_FILE, /*!< The file did not contain enough data */
	ETC2_UNKNOWN_FILE_FORMAT, /*!< The file not a ETC2 file */
	ETC2_UNSUPPORTED_TEXTURE_TYPE, /*!< The ETC2 file specifies an unsupported texture type. */
} ETC2_error_code;


/**
 * @internal
 * @brief used to pass GL context capabilites to subroutines.
 */
#define ETC2_NO_R16_FORMATS     0x0
#define ETC2_R16_FORMATS_NORM	0x1
#define ETC2_R16_FORMATS_SNORM	0x2
#define ETC2_ALL_R16_FORMATS (ETC2_R16_FORMATS_NORM | ETC2_R16_FORMATS_SNORM)


/*
 * These defines are needed to compile the KTX library. When
 * these things are not available in the GL header in use at
 * compile time, the library provides its own support, handles
 * the expected run-time errors or just needs the token value.
 */
#ifndef GL_LUMINANCE
#define GL_ALPHA						0x1906
#define GL_LUMINANCE					0x1909
#define GL_LUMINANCE_ALPHA				0x190A
#endif
#ifndef GL_INTENSITY
#define GL_INTENSITY					0x8049
#endif
#ifndef GL_TEXTURE_1D
#define GL_TEXTURE_1D                   0x0DE0
#endif
#ifndef GL_TEXTURE_3D
#define GL_TEXTURE_3D                   0x806F
#endif
#ifndef GL_TEXTURE_CUBE_MAP
#define GL_TEXTURE_CUBE_MAP             0x8513
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X  0x8515
#endif
/* from GL_EXT_texture_array */
#ifndef GL_TEXTURE_1D_ARRAY_EXT
#define GL_TEXTURE_1D_ARRAY_EXT         0x8C18
#define GL_TEXTURE_2D_ARRAY_EXT         0x8C1A
#endif
#ifndef GL_GENERATE_MIPMAP
#define GL_GENERATE_MIPMAP              0x8191
#endif

/* For writer.c */
#if !defined(GL_BGR)
#define GL_BGR							0x80E0
#define GL_BGRA							0x80E1
#endif
#if !defined(GL_RED_INTEGER)
#define GL_RED_INTEGER					0x8D94
#define GL_RGB_INTEGER					0x8D98
#define GL_RGBA_INTEGER					0x8D99
#endif
#if !defined(GL_GREEN_INTEGER)
#define GL_GREEN_INTEGER				0x8D95
#define GL_BLUE_INTEGER					0x8D96
#define GL_ALPHA_INTEGER				0x8D97
#endif
#if !defined (GL_BGR_INTEGER)
#define GL_BGR_INTEGER					0x8D9A
#define GL_BGRA_INTEGER					0x8D9B
#endif
#if !defined(GL_INT)
#define GL_INT 0x1404
#define GL_UNSIGNED_INT 0x1405
#endif
#if !defined(GL_HALF_FLOAT)
typedef unsigned short GLhalf;
#define GL_HALF_FLOAT					0x140B
#endif
#if !defined(GL_UNSIGNED_BYTE_3_3_2)
#define GL_UNSIGNED_BYTE_3_3_2			0x8032
#define GL_UNSIGNED_INT_8_8_8_8			0x8035
#define GL_UNSIGNED_INT_10_10_10_2		0x8036
#endif
#if !defined(GL_UNSIGNED_BYTE_2_3_3_REV)
#define GL_UNSIGNED_BYTE_2_3_3_REV		0x8362
#define GL_UNSIGNED_SHORT_5_6_5			0x8363
#define GL_UNSIGNED_SHORT_5_6_5_REV		0x8364
#define GL_UNSIGNED_SHORT_4_4_4_4_REV	0x8365
#define GL_UNSIGNED_SHORT_1_5_5_5_REV	0x8366
#define GL_UNSIGNED_INT_8_8_8_8_REV		0x8367
#define GL_UNSIGNED_INT_2_10_10_10_REV	0x8368
#endif
#if !defined(GL_UNSIGNED_INT_24_8)
#define GL_DEPTH_STENCIL				0x84F9
#define GL_UNSIGNED_INT_24_8			0x84FA
#endif
#if !defined(GL_UNSIGNED_INT_5_9_9_9_REV)
#define GL_UNSIGNED_INT_5_9_9_9_REV		0x8C3E
#endif
#if !defined(GL_UNSIGNED_INT_10F_11F_11F_REV)
#define GL_UNSIGNED_INT_10F_11F_11F_REV 0x8C3B
#endif
#if !defined (GL_FLOAT_32_UNSIGNED_INT_24_8_REV)
#define GL_FLOAT_32_UNSIGNED_INT_24_8_REV	0x8DAD
#endif

#ifndef GL_ETC1_RGB8_OES
#define GL_ETC1_RGB8_OES				0x8D64
#endif

#ifndef GL_COMPRESSED_R11_EAC
#define GL_COMPRESSED_R11_EAC                            0x9270
#define GL_COMPRESSED_SIGNED_R11_EAC                     0x9271
#define GL_COMPRESSED_RG11_EAC                           0x9272
#define GL_COMPRESSED_SIGNED_RG11_EAC                    0x9273
#define GL_COMPRESSED_RGB8_ETC2                          0x9274
#define GL_COMPRESSED_SRGB8_ETC2                         0x9275
#define GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2      0x9276
#define GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2     0x9277
#define GL_COMPRESSED_RGBA8_ETC2_EAC                     0x9278
#define GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC				 0x9279
#endif
#ifndef GL_R16_SNORM
#define GL_R16_SNORM					0x8F98
#define GL_RG16_SNORM					0x8F99
#endif
#ifndef GL_RED
#define GL_RED							0x1903
#define GL_GREEN						0x1904
#define GL_BLUE							0x1905
#define GL_RG							0x8227
#define GL_RG_INTEGER					0x8228
#endif
#ifndef GL_R16
#define GL_R16							0x822A
#define GL_RG16							0x822C
#endif
#ifndef GL_RGB8
#define GL_RGB8                         0x8051
#define GL_RGBA8                        0x8058
#endif
#ifndef GL_SRGB8
#define GL_SRGB8						0x8C41
#define GL_SRGB8_ALPHA8					0x8C43
#endif

#ifndef GL_MAJOR_VERSION
#define GL_MAJOR_VERSION                0x821B
#define GL_MINOR_VERSION                0x821C
#endif

#ifndef GL_CONTEXT_PROFILE_MASK
#define GL_CONTEXT_PROFILE_MASK				 0x9126
#define GL_CONTEXT_CORE_PROFILE_BIT			 0x00000001
#define GL_CONTEXT_COMPATIBILITY_PROFILE_BIT 0x00000002
#endif

#ifndef MAX
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#endif


#ifdef __cplusplus
}
#endif

#endif // _ETC2_TYPES_H_
