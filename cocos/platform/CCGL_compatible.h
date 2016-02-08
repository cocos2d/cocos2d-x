/**
    @date   2015/12/04
    @note   When you build in Opengles2, thereby compatible OpenGLES3
*/


#ifndef __PLATFORM_CCGL_COMPATIBLE_H__
#define __PLATFORM_CCGL_COMPATIBLE_H__

#ifndef GL_LUMINANCE
#define GL_ALPHA						0x1906
#define GL_LUMINANCE					0x1909
#define GL_LUMINANCE_ALPHA				0x190A
#endif
#ifndef GL_INTENSITY
#define GL_INTENSITY					0x8049
#endif
#if SUPPORT_LEGACY_FORMAT_CONVERSION
/* For loading legacy KTX files. */
#ifndef GL_LUMINANCE4
#define GL_ALPHA4						0x803B
#define GL_ALPHA8						0x803C
#define GL_ALPHA12						0x803D
#define GL_ALPHA16						0x803E
#define GL_LUMINANCE4					0x803F
#define GL_LUMINANCE8					0x8040
#define GL_LUMINANCE12					0x8041
#define GL_LUMINANCE16					0x8042
#define GL_LUMINANCE4_ALPHA4			0x8043
#define GL_LUMINANCE6_ALPHA2			0x8044
#define GL_LUMINANCE8_ALPHA8			0x8045
#define GL_LUMINANCE12_ALPHA4			0x8046
#define GL_LUMINANCE12_ALPHA12			0x8047
#define GL_LUMINANCE16_ALPHA16			0x8048
#endif
#ifndef GL_INTENSITY4
#define GL_INTENSITY4					0x804A
#define GL_INTENSITY8					0x804B
#define GL_INTENSITY12					0x804C
#define GL_INTENSITY16					0x804D
#endif
#ifndef GL_SLUMINANCE
#define GL_SLUMINANCE_ALPHA				0x8C44
#define GL_SLUMINANCE8_ALPHA8			0x8C45
#define GL_SLUMINANCE					0x8C46
#define GL_SLUMINANCE8					0x8C47
#endif
#endif /* SUPPORT_LEGACY_FORMAT_CONVERSION */
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

#endif // __PLATFORM_CCGL_COMPATIBLE_H__
