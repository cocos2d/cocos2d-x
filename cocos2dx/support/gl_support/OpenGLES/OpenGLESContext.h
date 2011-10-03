/*
 Copyright 2009 Johannes Vuorinen
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at 
 
 http://www.apache.org/licenses/LICENSE-2.0 
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#ifndef OpenGLESContext_H_
#define OpenGLESContext_H_

#include "OpenGLESConfig.h"
#include "OpenGLESImplementation.h"

typedef void            GLvoid;
typedef char            GLchar;
typedef unsigned int    GLenum;
typedef unsigned char   GLboolean;
typedef unsigned int    GLbitfield;
typedef signed char     GLbyte;
typedef short           GLshort;
typedef int             GLint;
typedef int             GLsizei;
typedef unsigned char   GLubyte;
typedef unsigned short  GLushort;
typedef unsigned int    GLuint;
typedef float           GLfloat;
typedef float           GLclampf;
typedef int             GLfixed;
typedef int             GLclampx;

/* GL types for handling large vertex buffer objects */
typedef long             GLintptr;
typedef long             GLsizeiptr;

/* Extensions */
#if !defined (__ANDROID__)
#define GL_OES_byte_coordinates           1
#define GL_OES_compressed_paletted_texture 1
#define GL_OES_draw_texture               1
#define GL_OES_fixed_point                1
#define GL_OES_matrix_get                 1
#define GL_OES_matrix_palette             1
#define GL_OES_point_size_array           1
#define GL_OES_point_sprite               1
#define GL_OES_read_format                1
#define GL_OES_single_precision           1
#endif

/* ClearBufferMask */
#define GL_DEPTH_BUFFER_BIT               0x00000100
#define GL_STENCIL_BUFFER_BIT             0x00000400
#define GL_COLOR_BUFFER_BIT               0x00004000

/* Boolean */
#define GL_FALSE                          0
#define GL_TRUE                           1

/* BeginMode */
#define GL_POINTS                         0x0000
#define GL_LINES                          0x0001
#define GL_LINE_LOOP                      0x0002
#define GL_LINE_STRIP                     0x0003
#define GL_TRIANGLES                      0x0004
#define GL_TRIANGLE_STRIP                 0x0005
#define GL_TRIANGLE_FAN                   0x0006

/* AlphaFunction */
#define GL_NEVER                          0x0200
#define GL_LESS                           0x0201
#define GL_EQUAL                          0x0202
#define GL_LEQUAL                         0x0203
#define GL_GREATER                        0x0204
#define GL_NOTEQUAL                       0x0205
#define GL_GEQUAL                         0x0206
#define GL_ALWAYS                         0x0207

/* BlendingFactorDest */
#define GL_ZERO                           0
#define GL_ONE                            1
#define GL_SRC_COLOR                      0x0300
#define GL_ONE_MINUS_SRC_COLOR            0x0301
#define GL_SRC_ALPHA                      0x0302
#define GL_ONE_MINUS_SRC_ALPHA            0x0303
#define GL_DST_ALPHA                      0x0304
#define GL_ONE_MINUS_DST_ALPHA            0x0305

/* BlendingFactorSrc */
/*      GL_ZERO */
/*      GL_ONE */
#define GL_DST_COLOR                      0x0306
#define GL_ONE_MINUS_DST_COLOR            0x0307
#define GL_SRC_ALPHA_SATURATE             0x0308
/*      GL_SRC_ALPHA */
/*      GL_ONE_MINUS_SRC_ALPHA */
/*      GL_DST_ALPHA */
/*      GL_ONE_MINUS_DST_ALPHA */

/* ClipPlaneName */
#define GL_CLIP_PLANE0                    0x3000
#define GL_CLIP_PLANE1                    0x3001
#define GL_CLIP_PLANE2                    0x3002
#define GL_CLIP_PLANE3                    0x3003
#define GL_CLIP_PLANE4                    0x3004
#define GL_CLIP_PLANE5                    0x3005

/* ColorMaterialFace */
/*      GL_FRONT_AND_BACK */

/* ColorMaterialParameter */
/*      GL_AMBIENT_AND_DIFFUSE */

/* ColorPointerType */
/*      GL_UNSIGNED_BYTE */
/*      GL_FLOAT */
/*      GL_FIXED */

/* CullFaceMode */
#define GL_FRONT                          0x0404
#define GL_BACK                           0x0405
#define GL_FRONT_AND_BACK                 0x0408

/* DepthFunction */
/*      GL_NEVER */
/*      GL_LESS */
/*      GL_EQUAL */
/*      GL_LEQUAL */
/*      GL_GREATER */
/*      GL_NOTEQUAL */
/*      GL_GEQUAL */
/*      GL_ALWAYS */

/* EnableCap */
#define GL_FOG                            0x0B60
#define GL_LIGHTING                       0x0B50
#define GL_TEXTURE_2D                     0x0DE1
#define GL_CULL_FACE                      0x0B44
#define GL_ALPHA_TEST                     0x0BC0
#define GL_BLEND                          0x0BE2
#define GL_COLOR_LOGIC_OP                 0x0BF2
#define GL_DITHER                         0x0BD0
#define GL_STENCIL_TEST                   0x0B90
#define GL_DEPTH_TEST                     0x0B71
/*      GL_LIGHT0 */
/*      GL_LIGHT1 */
/*      GL_LIGHT2 */
/*      GL_LIGHT3 */
/*      GL_LIGHT4 */
/*      GL_LIGHT5 */
/*      GL_LIGHT6 */
/*      GL_LIGHT7 */
#define GL_POINT_SMOOTH                   0x0B10
#define GL_LINE_SMOOTH                    0x0B20
#define GL_SCISSOR_TEST                   0x0C11
#define GL_COLOR_MATERIAL                 0x0B57
#define GL_NORMALIZE                      0x0BA1
#define GL_RESCALE_NORMAL                 0x803A
#define GL_POLYGON_OFFSET_FILL            0x8037
#define GL_VERTEX_ARRAY                   0x8074
#define GL_NORMAL_ARRAY                   0x8075
#define GL_COLOR_ARRAY                    0x8076
#define GL_TEXTURE_COORD_ARRAY            0x8078
#define GL_MULTISAMPLE                    0x809D
#define GL_SAMPLE_ALPHA_TO_COVERAGE       0x809E
#define GL_SAMPLE_ALPHA_TO_ONE            0x809F
#define GL_SAMPLE_COVERAGE                0x80A0

/* ErrorCode */
#define GL_NO_ERROR                       0
#define GL_INVALID_ENUM                   0x0500
#define GL_INVALID_VALUE                  0x0501
#define GL_INVALID_OPERATION              0x0502
#define GL_STACK_OVERFLOW                 0x0503
#define GL_STACK_UNDERFLOW                0x0504
#define GL_OUT_OF_MEMORY                  0x0505

/* FogMode */
/*      GL_LINEAR */
#define GL_EXP                            0x0800
#define GL_EXP2                           0x0801

/* FogParameter */
#define GL_FOG_DENSITY                    0x0B62
#define GL_FOG_START                      0x0B63
#define GL_FOG_END                        0x0B64
#define GL_FOG_MODE                       0x0B65
#define GL_FOG_COLOR                      0x0B66

/* FrontFaceDirection */
#define GL_CW                             0x0900
#define GL_CCW                            0x0901

/* GetPName */
#define GL_CURRENT_COLOR                  0x0B00
#define GL_CURRENT_NORMAL                 0x0B02
#define GL_CURRENT_TEXTURE_COORDS         0x0B03
#define GL_POINT_SIZE                     0x0B11
#define GL_POINT_SIZE_MIN                 0x8126
#define GL_POINT_SIZE_MAX                 0x8127
#define GL_POINT_FADE_THRESHOLD_SIZE      0x8128
#define GL_POINT_DISTANCE_ATTENUATION     0x8129
#define GL_SMOOTH_POINT_SIZE_RANGE        0x0B12
#define GL_LINE_WIDTH                     0x0B21
#define GL_SMOOTH_LINE_WIDTH_RANGE        0x0B22
#define GL_ALIASED_POINT_SIZE_RANGE       0x846D
#define GL_ALIASED_LINE_WIDTH_RANGE       0x846E
#define GL_CULL_FACE_MODE                 0x0B45
#define GL_FRONT_FACE                     0x0B46
#define GL_SHADE_MODEL                    0x0B54
#define GL_DEPTH_RANGE                    0x0B70
#define GL_DEPTH_WRITEMASK                0x0B72
#define GL_DEPTH_CLEAR_VALUE              0x0B73
#define GL_DEPTH_FUNC                     0x0B74
#define GL_STENCIL_CLEAR_VALUE            0x0B91
#define GL_STENCIL_FUNC                   0x0B92
#define GL_STENCIL_VALUE_MASK             0x0B93
#define GL_STENCIL_FAIL                   0x0B94
#define GL_STENCIL_PASS_DEPTH_FAIL        0x0B95
#define GL_STENCIL_PASS_DEPTH_PASS        0x0B96
#define GL_STENCIL_REF                    0x0B97
#define GL_STENCIL_WRITEMASK              0x0B98
#define GL_MATRIX_MODE                    0x0BA0
#define GL_VIEWPORT                       0x0BA2
#define GL_MODELVIEW_STACK_DEPTH          0x0BA3
#define GL_PROJECTION_STACK_DEPTH         0x0BA4
#define GL_TEXTURE_STACK_DEPTH            0x0BA5
#define GL_MODELVIEW_MATRIX               0x0BA6
#define GL_PROJECTION_MATRIX              0x0BA7
#define GL_TEXTURE_MATRIX                 0x0BA8
#define GL_ALPHA_TEST_FUNC                0x0BC1
#define GL_ALPHA_TEST_REF                 0x0BC2
#define GL_BLEND_DST                      0x0BE0
#define GL_BLEND_SRC                      0x0BE1
#define GL_LOGIC_OP_MODE                  0x0BF0
#define GL_SCISSOR_BOX                    0x0C10
#define GL_SCISSOR_TEST                   0x0C11
#define GL_COLOR_CLEAR_VALUE              0x0C22
#define GL_COLOR_WRITEMASK                0x0C23
#define GL_UNPACK_ALIGNMENT               0x0CF5
#define GL_PACK_ALIGNMENT                 0x0D05
#define GL_MAX_LIGHTS                     0x0D31
#define GL_MAX_CLIP_PLANES                0x0D32
#define GL_MAX_TEXTURE_SIZE               0x0D33
#define GL_MAX_MODELVIEW_STACK_DEPTH      0x0D36
#define GL_MAX_PROJECTION_STACK_DEPTH     0x0D38
#define GL_MAX_TEXTURE_STACK_DEPTH        0x0D39
#define GL_MAX_VIEWPORT_DIMS              0x0D3A
#define GL_MAX_TEXTURE_UNITS              0x84E2
#define GL_SUBPIXEL_BITS                  0x0D50
#define GL_RED_BITS                       0x0D52
#define GL_GREEN_BITS                     0x0D53
#define GL_BLUE_BITS                      0x0D54
#define GL_ALPHA_BITS                     0x0D55
#define GL_DEPTH_BITS                     0x0D56
#define GL_STENCIL_BITS                   0x0D57
#define GL_POLYGON_OFFSET_UNITS           0x2A00
#define GL_POLYGON_OFFSET_FILL            0x8037
#define GL_POLYGON_OFFSET_FACTOR          0x8038
#define GL_TEXTURE_BINDING_2D             0x8069
#define GL_VERTEX_ARRAY_SIZE              0x807A
#define GL_VERTEX_ARRAY_TYPE              0x807B
#define GL_VERTEX_ARRAY_STRIDE            0x807C
#define GL_NORMAL_ARRAY_TYPE              0x807E
#define GL_NORMAL_ARRAY_STRIDE            0x807F
#define GL_COLOR_ARRAY_SIZE               0x8081
#define GL_COLOR_ARRAY_TYPE               0x8082
#define GL_COLOR_ARRAY_STRIDE             0x8083
#define GL_TEXTURE_COORD_ARRAY_SIZE       0x8088
#define GL_TEXTURE_COORD_ARRAY_TYPE       0x8089
#define GL_TEXTURE_COORD_ARRAY_STRIDE     0x808A
#define GL_VERTEX_ARRAY_POINTER           0x808E
#define GL_NORMAL_ARRAY_POINTER           0x808F
#define GL_COLOR_ARRAY_POINTER            0x8090
#define GL_TEXTURE_COORD_ARRAY_POINTER    0x8092
#define GL_SAMPLE_BUFFERS                 0x80A8
#define GL_SAMPLES                        0x80A9
#define GL_SAMPLE_COVERAGE_VALUE          0x80AA
#define GL_SAMPLE_COVERAGE_INVERT         0x80AB

/* GetTextureParameter */
/*      GL_TEXTURE_MAG_FILTER */
/*      GL_TEXTURE_MIN_FILTER */
/*      GL_TEXTURE_WRAP_S */
/*      GL_TEXTURE_WRAP_T */

#define GL_IMPLEMENTATION_COLOR_READ_TYPE_OES   0x8B9A
#define GL_IMPLEMENTATION_COLOR_READ_FORMAT_OES 0x8B9B
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS       0x86A2
#define GL_COMPRESSED_TEXTURE_FORMATS           0x86A3

/* HintMode */
#define GL_DONT_CARE                      0x1100
#define GL_FASTEST                        0x1101
#define GL_NICEST                         0x1102

/* HintTarget */
#define GL_PERSPECTIVE_CORRECTION_HINT    0x0C50
#define GL_POINT_SMOOTH_HINT              0x0C51
#define GL_LINE_SMOOTH_HINT               0x0C52
#define GL_FOG_HINT                       0x0C54
#define GL_GENERATE_MIPMAP_HINT           0x8192
#define GL_LIGHTING_HINT                  0x0D62 // OWN ADDITION

/* LightModelParameter */
#define GL_LIGHT_MODEL_AMBIENT            0x0B53
#define GL_LIGHT_MODEL_TWO_SIDE           0x0B52
#define GL_LIGHT_MODEL_LOCAL_VIEWER       0x0B51 // OWN ADDITION

/* LightParameter */
#define GL_AMBIENT                        0x1200
#define GL_DIFFUSE                        0x1201
#define GL_SPECULAR                       0x1202
#define GL_POSITION                       0x1203
#define GL_SPOT_DIRECTION                 0x1204
#define GL_SPOT_EXPONENT                  0x1205
#define GL_SPOT_CUTOFF                    0x1206
#define GL_CONSTANT_ATTENUATION           0x1207
#define GL_LINEAR_ATTENUATION             0x1208
#define GL_QUADRATIC_ATTENUATION          0x1209

/* DataType */
#define GL_BYTE                           0x1400
#define GL_UNSIGNED_BYTE                  0x1401
#define GL_SHORT                          0x1402
#define GL_UNSIGNED_SHORT                 0x1403
#define GL_FLOAT                          0x1406
#define GL_FIXED                          0x140C

/* LogicOp */
#define GL_CLEAR                          0x1500
#define GL_AND                            0x1501
#define GL_AND_REVERSE                    0x1502
#define GL_COPY                           0x1503
#define GL_AND_INVERTED                   0x1504
#define GL_NOOP                           0x1505
#define GL_XOR                            0x1506
#define GL_OR                             0x1507
#define GL_NOR                            0x1508
#define GL_EQUIV                          0x1509
#define GL_INVERT                         0x150A
#define GL_OR_REVERSE                     0x150B
#define GL_COPY_INVERTED                  0x150C
#define GL_OR_INVERTED                    0x150D
#define GL_NAND                           0x150E
#define GL_SET                            0x150F

/* MaterialFace */
/*      GL_FRONT_AND_BACK */

/* MaterialParameter */
#define GL_EMISSION                       0x1600
#define GL_SHININESS                      0x1601
#define GL_AMBIENT_AND_DIFFUSE            0x1602
/*      GL_AMBIENT */
/*      GL_DIFFUSE */
/*      GL_SPECULAR */

/* MatrixMode */
#define GL_MODELVIEW                      0x1700
#define GL_PROJECTION                     0x1701
#define GL_TEXTURE                        0x1702

/* NormalPointerType */
/*      GL_BYTE */
/*      GL_SHORT */
/*      GL_FLOAT */
/*      GL_FIXED */

/* PixelFormat */
#define GL_ALPHA                          0x1906
#define GL_RGB                            0x1907
#define GL_RGBA                           0x1908
#define GL_LUMINANCE                      0x1909
#define GL_LUMINANCE_ALPHA                0x190A

/* PixelStoreParameter */
#define GL_UNPACK_ALIGNMENT               0x0CF5
#define GL_PACK_ALIGNMENT                 0x0D05

/* PixelType */
/*      GL_UNSIGNED_BYTE */
#define GL_UNSIGNED_SHORT_4_4_4_4         0x8033
#define GL_UNSIGNED_SHORT_5_5_5_1         0x8034
#define GL_UNSIGNED_SHORT_5_6_5           0x8363

/* ShadingModel */
#define GL_FLAT                           0x1D00
#define GL_SMOOTH                         0x1D01

/* StencilFunction */
/*      GL_NEVER */
/*      GL_LESS */
/*      GL_EQUAL */
/*      GL_LEQUAL */
/*      GL_GREATER */
/*      GL_NOTEQUAL */
/*      GL_GEQUAL */
/*      GL_ALWAYS */

/* StencilOp */
/*      GL_ZERO */
#define GL_KEEP                           0x1E00
#define GL_REPLACE                        0x1E01
#define GL_INCR                           0x1E02
#define GL_DECR                           0x1E03
/*      GL_INVERT */

/* StringName */
#define GL_VENDOR                         0x1F00
#define GL_RENDERER                       0x1F01
#define GL_VERSION                        0x1F02
#define GL_EXTENSIONS                     0x1F03

/* TexCoordPointerType */
/*      GL_SHORT */
/*      GL_FLOAT */
/*      GL_FIXED */
/*      GL_BYTE */

/* TextureEnvMode */
#define GL_MODULATE                       0x2100
#define GL_DECAL                          0x2101
/*      GL_BLEND */
#define GL_ADD                            0x0104
/*      GL_REPLACE */

/* TextureEnvParameter */
#define GL_TEXTURE_ENV_MODE               0x2200
#define GL_TEXTURE_ENV_COLOR              0x2201

/* TextureEnvTarget */
#define GL_TEXTURE_ENV                    0x2300

/* TextureMagFilter */
#define GL_NEAREST                        0x2600
#define GL_LINEAR                         0x2601

/* TextureMinFilter */
/*      GL_NEAREST */
/*      GL_LINEAR */
#define GL_NEAREST_MIPMAP_NEAREST         0x2700
#define GL_LINEAR_MIPMAP_NEAREST          0x2701
#define GL_NEAREST_MIPMAP_LINEAR          0x2702
#define GL_LINEAR_MIPMAP_LINEAR           0x2703

/* TextureParameterName */
#define GL_TEXTURE_MAG_FILTER             0x2800
#define GL_TEXTURE_MIN_FILTER             0x2801
#define GL_TEXTURE_WRAP_S                 0x2802
#define GL_TEXTURE_WRAP_T                 0x2803
#define GL_GENERATE_MIPMAP                0x8191

/* TextureTarget */
/*      GL_TEXTURE_2D */

/* TextureUnit */
#define GL_TEXTURE0                       0x84C0
#define GL_TEXTURE1                       0x84C1
#define GL_TEXTURE2                       0x84C2
#define GL_TEXTURE3                       0x84C3
#define GL_TEXTURE4                       0x84C4
#define GL_TEXTURE5                       0x84C5
#define GL_TEXTURE6                       0x84C6
#define GL_TEXTURE7                       0x84C7
#define GL_TEXTURE8                       0x84C8
#define GL_TEXTURE9                       0x84C9
#define GL_TEXTURE10                      0x84CA
#define GL_TEXTURE11                      0x84CB
#define GL_TEXTURE12                      0x84CC
#define GL_TEXTURE13                      0x84CD
#define GL_TEXTURE14                      0x84CE
#define GL_TEXTURE15                      0x84CF
#define GL_TEXTURE16                      0x84D0
#define GL_TEXTURE17                      0x84D1
#define GL_TEXTURE18                      0x84D2
#define GL_TEXTURE19                      0x84D3
#define GL_TEXTURE20                      0x84D4
#define GL_TEXTURE21                      0x84D5
#define GL_TEXTURE22                      0x84D6
#define GL_TEXTURE23                      0x84D7
#define GL_TEXTURE24                      0x84D8
#define GL_TEXTURE25                      0x84D9
#define GL_TEXTURE26                      0x84DA
#define GL_TEXTURE27                      0x84DB
#define GL_TEXTURE28                      0x84DC
#define GL_TEXTURE29                      0x84DD
#define GL_TEXTURE30                      0x84DE
#define GL_TEXTURE31                      0x84DF
#define GL_ACTIVE_TEXTURE                 0x84E0
#define GL_CLIENT_ACTIVE_TEXTURE          0x84E1

/* TextureWrapMode */
#define GL_REPEAT                         0x2901
#define GL_CLAMP_TO_EDGE                  0x812F

/* PixelInternalFormat */
#define GL_PALETTE4_RGB8_OES              0x8B90
#define GL_PALETTE4_RGBA8_OES             0x8B91
#define GL_PALETTE4_R5_G6_B5_OES          0x8B92
#define GL_PALETTE4_RGBA4_OES             0x8B93
#define GL_PALETTE4_RGB5_A1_OES           0x8B94
#define GL_PALETTE8_RGB8_OES              0x8B95
#define GL_PALETTE8_RGBA8_OES             0x8B96
#define GL_PALETTE8_R5_G6_B5_OES          0x8B97
#define GL_PALETTE8_RGBA4_OES             0x8B98
#define GL_PALETTE8_RGB5_A1_OES           0x8B99

/* VertexPointerType */
/*      GL_SHORT */
/*      GL_FLOAT */
/*      GL_FIXED */
/*      GL_BYTE */

/* LightName */
#define GL_LIGHT0                         0x4000
#define GL_LIGHT1                         0x4001
#define GL_LIGHT2                         0x4002
#define GL_LIGHT3                         0x4003
#define GL_LIGHT4                         0x4004
#define GL_LIGHT5                         0x4005
#define GL_LIGHT6                         0x4006
#define GL_LIGHT7                         0x4007

/* Buffer Objects */
#define GL_ARRAY_BUFFER                   0x8892
#define GL_ELEMENT_ARRAY_BUFFER           0x8893

#define GL_ARRAY_BUFFER_BINDING           0x8894
#define GL_ELEMENT_ARRAY_BUFFER_BINDING   0x8895
#define GL_VERTEX_ARRAY_BUFFER_BINDING    0x8896
#define GL_NORMAL_ARRAY_BUFFER_BINDING    0x8897
#define GL_COLOR_ARRAY_BUFFER_BINDING     0x8898
#define GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING 0x889A

#define GL_STATIC_DRAW                    0x88E4
#define GL_DYNAMIC_DRAW                   0x88E8

#define GL_BUFFER_SIZE                    0x8764
#define GL_BUFFER_USAGE                   0x8765

/* Framebuffer Object. */
#define GL_FRAMEBUFFER                                      0x8D40
#define GL_RENDERBUFFER                                     0x8D41

#define GL_RGBA4                                            0x8056
#define GL_RGB5_A1                                          0x8057
#define GL_RGB565                                           0x8D62
#define GL_DEPTH_COMPONENT16                                0x81A5
#define GL_STENCIL_INDEX                                    0x1901
#define GL_STENCIL_INDEX8                                   0x8D48

#define GL_RENDERBUFFER_WIDTH                               0x8D42
#define GL_RENDERBUFFER_HEIGHT                              0x8D43
#define GL_RENDERBUFFER_INTERNAL_FORMAT                     0x8D44
#define GL_RENDERBUFFER_RED_SIZE                            0x8D50
#define GL_RENDERBUFFER_GREEN_SIZE                          0x8D51
#define GL_RENDERBUFFER_BLUE_SIZE                           0x8D52
#define GL_RENDERBUFFER_ALPHA_SIZE                          0x8D53
#define GL_RENDERBUFFER_DEPTH_SIZE                          0x8D54
#define GL_RENDERBUFFER_STENCIL_SIZE                        0x8D55

#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE               0x8CD0
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME               0x8CD1
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL             0x8CD2
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE     0x8CD3

#define GL_COLOR_ATTACHMENT0                                0x8CE0
#define GL_DEPTH_ATTACHMENT                                 0x8D00
#define GL_STENCIL_ATTACHMENT                               0x8D20

#define GL_NONE                                             0

#define GL_FRAMEBUFFER_COMPLETE                             0x8CD5
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT                0x8CD6
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT        0x8CD7
#define GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS                0x8CD9
#define GL_FRAMEBUFFER_UNSUPPORTED                          0x8CDD

#define GL_FRAMEBUFFER_BINDING                              0x8CA6
#define GL_RENDERBUFFER_BINDING                             0x8CA7
#define GL_MAX_RENDERBUFFER_SIZE                            0x84E8

#define GL_INVALID_FRAMEBUFFER_OPERATION                    0x0506

/* Texture combine + dot3 */
#define GL_SUBTRACT                       0x84E7
#define GL_COMBINE                        0x8570
#define GL_COMBINE_RGB                    0x8571
#define GL_COMBINE_ALPHA                  0x8572
#define GL_RGB_SCALE                      0x8573
#define GL_ADD_SIGNED                     0x8574
#define GL_INTERPOLATE                    0x8575
#define GL_CONSTANT                       0x8576
#define GL_PRIMARY_COLOR                  0x8577
#define GL_PREVIOUS                       0x8578
#define GL_OPERAND0_RGB                   0x8590
#define GL_OPERAND1_RGB                   0x8591
#define GL_OPERAND2_RGB                   0x8592
#define GL_OPERAND0_ALPHA                 0x8598
#define GL_OPERAND1_ALPHA                 0x8599
#define GL_OPERAND2_ALPHA                 0x859A

#define GL_ALPHA_SCALE                    0x0D1C

#define GL_SRC0_RGB                       0x8580
#define GL_SRC1_RGB                       0x8581
#define GL_SRC2_RGB                       0x8582
#define GL_SRC0_ALPHA                     0x8588
#define GL_SRC1_ALPHA                     0x8589
#define GL_SRC2_ALPHA                     0x858A

#define GL_DOT3_RGB                       0x86AE
#define GL_DOT3_RGBA                      0x86AF

#define GL_BLUR							  0x86FF  // OWN ADDITION
#define GL_BLUR_AMOUNT					  0x86FE  // OWN ADDITION

/*****************************************************************************************/
/*                                 OES extension functions                               */
/*****************************************************************************************/

/* OES_draw_texture */
#define GL_TEXTURE_CROP_RECT_OES          0x8B9D

/* OES_matrix_get */
#define GL_MODELVIEW_MATRIX_FLOAT_AS_INT_BITS_OES   0x898D
#define GL_PROJECTION_MATRIX_FLOAT_AS_INT_BITS_OES  0x898E
#define GL_TEXTURE_MATRIX_FLOAT_AS_INT_BITS_OES     0x898F

/* OES_matrix_palette */
#define GL_MAX_VERTEX_UNITS_OES           0x86A4
#define GL_MAX_PALETTE_MATRICES_OES       0x8842
#define GL_MATRIX_PALETTE_OES             0x8840
#define GL_MATRIX_INDEX_ARRAY_OES         0x8844
#define GL_WEIGHT_ARRAY_OES               0x86AD
#define GL_CURRENT_PALETTE_MATRIX_OES     0x8843

#define GL_MATRIX_INDEX_ARRAY_SIZE_OES    0x8846
#define GL_MATRIX_INDEX_ARRAY_TYPE_OES    0x8847
#define GL_MATRIX_INDEX_ARRAY_STRIDE_OES  0x8848
#define GL_MATRIX_INDEX_ARRAY_POINTER_OES 0x8849
#define GL_MATRIX_INDEX_ARRAY_BUFFER_BINDING_OES 0x8B9E

#define GL_WEIGHT_ARRAY_SIZE_OES          0x86AB
#define GL_WEIGHT_ARRAY_TYPE_OES          0x86A9
#define GL_WEIGHT_ARRAY_STRIDE_OES        0x86AA
#define GL_WEIGHT_ARRAY_POINTER_OES       0x86AC
#define GL_WEIGHT_ARRAY_BUFFER_BINDING_OES 0x889E

/* OES_point_size_array */
#define GL_POINT_SIZE_ARRAY_OES           0x8B9C
#define GL_POINT_SIZE_ARRAY_TYPE_OES      0x898A
#define GL_POINT_SIZE_ARRAY_STRIDE_OES    0x898B
#define GL_POINT_SIZE_ARRAY_POINTER_OES   0x898C
#define GL_POINT_SIZE_ARRAY_BUFFER_BINDING_OES 0x8B9F

/* OES_point_sprite */
#define GL_POINT_SPRITE_OES               0x8861
#define GL_COORD_REPLACE_OES              0x8862

/* GL_IMG_texture_compression_pvrtc */
#define GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG                      0x8C00
#define GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG                      0x8C01
#define GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG                     0x8C02
#define GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG                     0x8C03

/* GL_IMG_texture_format_BGRA8888 */
#define GL_BGRA										0x80E1

/* GL_APPLE_framebuffer_multisample */
#define GL_RENDERBUFFER_SAMPLES_APPLE                           0x8CAB
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_APPLE             0x8D56
#define GL_MAX_SAMPLES_APPLE                                    0x8D57
#define GL_READ_FRAMEBUFFER_APPLE                               0x8CA8
#define GL_DRAW_FRAMEBUFFER_APPLE                               0x8CA9
#define GL_DRAW_FRAMEBUFFER_BINDING_APPLE                       0x8CA6
#define GL_READ_FRAMEBUFFER_BINDING_APPLE                       0x8CAA

/*************************************************************/

namespace OpenGLES {
	
	class OpenGLESContext {
	public:
		OpenGLESContext(int version, OpenGLESImplementation *impl);
		virtual ~OpenGLESContext();
		
		int getOpenGLESVersion();
		
		// OpenglES 1.0 functions
		virtual void glActiveTexture (GLenum texture) = 0;
		virtual void glAlphaFunc (GLenum func, GLclampf ref) = 0;
		virtual void glAlphaFuncx (GLenum func, GLclampx ref) = 0;
		virtual void glBindTexture (GLenum target, GLuint texture) = 0;
		virtual void glBlendFunc (GLenum sfactor, GLenum dfactor) = 0;
		virtual void glClear(GLbitfield mask) = 0;
		virtual void glClearColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) = 0;
		virtual void glClearColorx (GLclampx red, GLclampx green, GLclampx blue, GLclampx alpha) = 0;
		virtual void glClearDepthf (GLclampf depth) = 0;
		virtual void glClearDepthx (GLclampx depth) = 0;
		virtual void glClearStencil (GLint s) = 0;
		virtual void glClientActiveTexture (GLenum texture) = 0;
		virtual void glColor4f (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) = 0;
		virtual void glColor4x (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha) = 0;
		virtual void glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) = 0;
		virtual void glColorPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer) = 0;
		virtual void glCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data) = 0;
		virtual void glCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data) = 0;
		virtual void glCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) = 0;
		virtual void glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) = 0;
		virtual void glCullFace (GLenum mode) = 0;
		virtual void glDeleteTextures (GLsizei n, const GLuint *textures) = 0;
		virtual void glDepthFunc (GLenum func) = 0;
		virtual void glDepthMask (GLboolean flag) = 0;
		virtual void glDepthRangef (GLclampf zNear, GLclampf zFar) = 0;
		virtual void glDepthRangex (GLclampx zNear, GLclampx zFar) = 0;
		virtual void glDisable (GLenum cap) = 0;
		virtual void glDisableClientState (GLenum array) = 0;
		virtual void glDrawArrays(GLenum mode, GLint first, GLsizei count) = 0;
		virtual void glDrawElements (GLenum mode, GLsizei count, GLenum type, const GLvoid *indices) = 0;
		virtual void glEnable (GLenum cap) = 0;
		virtual void glEnableClientState (GLenum array) = 0;
		virtual void glFinish (void) = 0;
		virtual void glFlush (void) = 0;
		virtual void glFogf (GLenum pname, GLfloat param) = 0;
		virtual void glFogfv (GLenum pname, const GLfloat *params) = 0;
		virtual void glFogx (GLenum pname, GLfixed param) = 0;
		virtual void glFogxv (GLenum pname, const GLfixed *params) = 0;
		virtual void glFrontFace (GLenum mode) = 0;
		virtual void glFrustumf (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar) = 0;
		virtual void glFrustumx (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar) = 0;
		virtual void glGenTextures (GLsizei n, GLuint *textures) = 0;
		virtual GLenum glGetError (void) = 0;
		virtual void glGetIntegerv (GLenum pname, GLint *params) = 0;
		virtual const GLubyte *glGetString (GLenum name) = 0;
		virtual void glHint (GLenum target, GLenum mode) = 0;
		virtual void glLightModelf (GLenum pname, GLfloat param) = 0;
		virtual void glLightModelfv (GLenum pname, const GLfloat *params) = 0;
		virtual void glLightModelx (GLenum pname, GLfixed param) = 0;
		virtual void glLightModelxv (GLenum pname, const GLfixed *params) = 0;
		virtual void glLightf (GLenum light, GLenum pname, GLfloat param) = 0;
		virtual void glLightfv (GLenum light, GLenum pname, const GLfloat *params) = 0;
		virtual void glLightx (GLenum light, GLenum pname, GLfixed param) = 0;
		virtual void glLightxv (GLenum light, GLenum pname, const GLfixed *params) = 0;
		virtual void glLineWidth (GLfloat width) = 0;
		virtual void glLineWidthx (GLfixed width) = 0;
		virtual void glLoadIdentity (void) = 0;
		virtual void glLoadMatrixf (const GLfloat *m) = 0;
		virtual void glLoadMatrixx (const GLfixed *m) = 0;
		virtual void glLogicOp (GLenum opcode) = 0;
		virtual void glMaterialf (GLenum face, GLenum pname, GLfloat param) = 0;
		virtual void glMaterialfv (GLenum face, GLenum pname, const GLfloat *params) = 0;
		virtual void glMaterialx (GLenum face, GLenum pname, GLfixed param) = 0;
		virtual void glMaterialxv (GLenum face, GLenum pname, const GLfixed *params) = 0;
		virtual void glMatrixMode (GLenum mode) = 0;
		virtual void glMultMatrixf (const GLfloat *m) = 0;
		virtual void glMultMatrixx (const GLfixed *m) = 0;
		virtual void glMultiTexCoord4f (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q) = 0;
		virtual void glMultiTexCoord4x (GLenum target, GLfixed s, GLfixed t, GLfixed r, GLfixed q) = 0;
		virtual void glNormal3f (GLfloat nx, GLfloat ny, GLfloat nz) = 0;
		virtual void glNormal3x (GLfixed nx, GLfixed ny, GLfixed nz) = 0;
		virtual void glNormalPointer (GLenum type, GLsizei stride, const GLvoid *pointer) = 0;
		virtual void glOrthof (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar) = 0;
		virtual void glOrthox (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar) = 0;
		virtual void glPixelStorei (GLenum pname, GLint param) = 0;
		virtual void glPointSize (GLfloat size) = 0;
		virtual void glPointSizex (GLfixed size) = 0;
		virtual void glPolygonOffset (GLfloat factor, GLfloat units) = 0;
		virtual void glPolygonOffsetx (GLfixed factor, GLfixed units) = 0;
		virtual void glPopMatrix (void) = 0;
		virtual void glPushMatrix (void) = 0;
		virtual void glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels) = 0;
		virtual void glRotatef (GLfloat angle, GLfloat x, GLfloat y, GLfloat z) = 0;
		virtual void glRotatex (GLfixed angle, GLfixed x, GLfixed y, GLfixed z) = 0;
		virtual void glSampleCoverage (GLclampf value, GLboolean invert) = 0;
		virtual void glSampleCoveragex (GLclampx value, GLboolean invert) = 0;
		virtual void glScalef (GLfloat x, GLfloat y, GLfloat z) = 0;
		virtual void glScalex (GLfixed x, GLfixed y, GLfixed z) = 0;
		virtual void glScissor (GLint x, GLint y, GLsizei width, GLsizei height) = 0;
		virtual void glShadeModel (GLenum mode) = 0;
		virtual void glStencilFunc (GLenum func, GLint ref, GLuint mask) = 0;
		virtual void glStencilMask (GLuint mask) = 0;
		virtual void glStencilOp (GLenum fail, GLenum zfail, GLenum zpass) = 0;
		virtual void glTexCoordPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer) = 0;
		virtual void glTexEnvf (GLenum target, GLenum pname, GLfloat param) = 0;
		virtual void glTexEnvfv (GLenum target, GLenum pname, const GLfloat *params) = 0;
		virtual void glTexEnvx (GLenum target, GLenum pname, GLfixed param) = 0;
		virtual void glTexEnvxv (GLenum target, GLenum pname, const GLfixed *params) = 0;
		virtual void glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels) = 0;
		virtual void glTexParameterf (GLenum target, GLenum pname, GLfloat param) = 0;
		virtual void glTexParameterx (GLenum target, GLenum pname, GLfixed param) = 0;
		virtual void glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels) = 0;
		virtual void glTranslatef (GLfloat x, GLfloat y, GLfloat z) = 0;
		virtual void glTranslatex (GLfixed x, GLfixed y, GLfixed z) = 0;
		virtual void glVertexPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer) = 0;
		virtual void glViewport (GLint x, GLint y, GLsizei width, GLsizei height) = 0;
		
		// OpenGL ES 1.1 functions
		virtual void glBindBuffer (GLenum target, GLuint buffer) = 0;
		virtual void glBufferData (GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage) = 0;
		virtual void glBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data) = 0;
		virtual void glClipPlanef(GLenum plane, const GLfloat *equation) = 0;
		virtual void glClipPlanex (GLenum plane, const GLfixed *equation) = 0;
		virtual void glColor4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha) = 0;
		virtual void glDeleteBuffers (GLsizei n, const GLuint *buffers) = 0;
		virtual void glGenBuffers (GLsizei n, GLuint *buffers) = 0;
		virtual void glGetClipPlanef(GLenum pname, GLfloat eqn[4]) = 0;
		virtual void glGetFloatv(GLenum pname, GLfloat *params) = 0;
		virtual void glGetLightfv (GLenum light, GLenum pname, GLfloat *params) = 0;
		virtual void glGetLightxv (GLenum light, GLenum pname, GLfixed *params) = 0;
		virtual void glGetMaterialfv (GLenum face, GLenum pname, GLfloat *params) = 0;
		virtual void glGetMaterialxv (GLenum face, GLenum pname, GLfixed *params) = 0;
		virtual void glGetTexEnvfv (GLenum env, GLenum pname, GLfloat *params) = 0;
		virtual void glGetTexEnviv (GLenum env, GLenum pname, GLint *params) = 0;
		virtual void glGetTexEnvxv (GLenum env, GLenum pname, GLfixed *params) = 0;
		virtual void glGetTexParameterfv (GLenum target, GLenum pname, GLfloat *params) = 0;
		virtual void glGetTexParameteriv (GLenum target, GLenum pname, GLint *params) = 0;
		virtual void glGetTexParameterxv (GLenum target, GLenum pname, GLfixed *params) = 0;
		virtual void glGetBooleanv (GLenum pname, GLboolean *params) = 0;
		virtual void glGetBufferParameteriv (GLenum target, GLenum pname, GLint *params) = 0;
		virtual void glGetFixedv (GLenum pname, GLfixed *params) = 0;
		virtual void glGetPointerv (GLenum pname, void **params) = 0;
		virtual GLboolean glIsBuffer (GLuint buffer) = 0;
		virtual GLboolean glIsEnabled (GLenum cap) = 0;
		virtual GLboolean glIsTexture (GLuint texture) = 0;
		virtual void glPointParameterf (GLenum pname, GLfloat param) = 0;
		virtual void glPointParameterfv (GLenum pname, const GLfloat *params) = 0;
		virtual void glPointParameterx (GLenum pname, GLfixed param) = 0;
		virtual void glPointParameterxv (GLenum pname, const GLfixed *params) = 0;
		virtual void glTexEnvi (GLenum target, GLenum pname, GLint param) = 0;
		virtual void glTexEnviv (GLenum target, GLenum pname, const GLint *params) = 0;
		virtual void glTexParameteri (GLenum target, GLenum pname, GLint param) = 0;
		virtual void glTexParameteriv (GLenum target, GLenum pname, const GLint *params) = 0;
		
		// OpenGL ES 1.1 extensions
		virtual void glCurrentPaletteMatrixOES (GLuint matrixpaletteindex) = 0;
		virtual void glLoadPaletteFromModelViewMatrixOES (void) = 0;
		virtual void glMatrixIndexPointerOES (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer) = 0;
		virtual void glWeightPointerOES (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer) = 0;
		virtual void glPointSizePointerOES (GLenum type, GLsizei stride, const GLvoid *pointer) = 0;
		virtual void glDrawTexsOES (GLshort x, GLshort y, GLshort z, GLshort width, GLshort height) = 0;
		virtual void glDrawTexiOES (GLint x, GLint y, GLint z, GLint width, GLint height) = 0;
		virtual void glDrawTexxOES (GLfixed x, GLfixed y, GLfixed z, GLfixed width, GLfixed height) = 0;
		virtual void glDrawTexsvOES (const GLshort *coords) = 0;
		virtual void glDrawTexivOES (const GLint *coords) = 0;
		virtual void glDrawTexxvOES (const GLfixed *coords) = 0;
		virtual void glDrawTexfOES (GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height) = 0;
		virtual void glDrawTexfvOES (const GLfloat *coords) = 0;
		
		// OpenGL ES 2
		//virtual void glActiveTexture (GLenum texture); DUPLICATE
		virtual void glAttachShader (GLuint program, GLuint shader) = 0;
		virtual void glBindAttribLocation (GLuint program, GLuint index, const GLchar* name) = 0;
		//virtual void glBindBuffer (GLenum target, GLuint buffer); DUPLICATE
		virtual void glBindFramebuffer (GLenum target, GLuint framebuffer) = 0;
		virtual void glBindRenderbuffer (GLenum target, GLuint renderbuffer) = 0;
		//virtual void glBindTexture (GLenum target, GLuint texture); DUPLICATE
		virtual void glBlendColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) = 0;
		virtual void glBlendEquation ( GLenum mode ) = 0;
		virtual void glBlendEquationSeparate (GLenum modeRGB, GLenum modeAlpha) = 0;
		//virtual void glBlendFunc (GLenum sfactor, GLenum dfactor); DUPLICATE
		virtual void glBlendFuncSeparate (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) = 0;
		//virtual void glBufferData (GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage); DUPLICATE
		//virtual void glBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data); DUPLICATE
		virtual GLenum glCheckFramebufferStatus (GLenum target) = 0;
		//virtual void glClear (GLbitfield mask); DUPLICATE
		//virtual void glClearColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha); DUPLICATE
		//virtual void glClearDepthf (GLclampf depth); DUPLICATE
		//virtual void glClearStencil (GLint s); DUPLICATE
		//virtual void glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha); DUPLICATE
		virtual void glCompileShader (GLuint shader) = 0;
		//virtual void glCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data); DUPLICATE
		//virtual void glCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data); DUPLICATE
		//virtual void glCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border); DUPLICATE
		//virtual void glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height); DUPLICATE
		virtual GLuint glCreateProgram (void) = 0;
		virtual GLuint glCreateShader (GLenum type) = 0;
		//virtual void glCullFace (GLenum mode); DUPLICATE
		//virtual void glDeleteBuffers (GLsizei n, const GLuint* buffers); DUPLICATE
		virtual void glDeleteFramebuffers (GLsizei n, const GLuint* framebuffers) = 0;
		virtual void glDeleteProgram (GLuint program) = 0;
		virtual void glDeleteRenderbuffers (GLsizei n, const GLuint* renderbuffers) = 0;
		virtual void glDeleteShader (GLuint shader) = 0;
		//virtual void glDeleteTextures (GLsizei n, const GLuint* textures); DUPLICATE
		//virtual void glDepthFunc (GLenum func); DUPLICATE
		//virtual void glDepthMask (GLboolean flag); DUPLICATE
		//virtual void glDepthRangef (GLclampf zNear, GLclampf zFar); DUPLICATE
		virtual void glDetachShader (GLuint program, GLuint shader) = 0;
		//virtual void glDisable (GLenum cap); DUPLICATE
		virtual void glDisableVertexAttribArray (GLuint index) = 0;
		virtual void glDiscardFramebufferEXT(GLenum target, GLsizei numAttachments, const GLenum *attachments) = 0;
		//virtual void glDrawArrays (GLenum mode, GLint first, GLsizei count); DUPLICATE
		//virtual void glDrawElements (GLenum mode, GLsizei count, GLenum type, const GLvoid* indices); DUPLICATE
		//virtual void glEnable (GLenum cap); DUPLICATE
		virtual void glEnableVertexAttribArray (GLuint index) = 0;
		//virtual void glFinish (void); DUPLICATE
		//virtual void glFlush (void); DUPLICATE
		virtual void glFramebufferRenderbuffer (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) = 0;
		virtual void glFramebufferTexture2D (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) = 0;
		//virtual void glFrontFace (GLenum mode); DUPLICATE
		//virtual void glGenBuffers (GLsizei n, GLuint* buffers); DUPLICATE
		virtual void glGenerateMipmap (GLenum target) = 0;
		virtual void glGenFramebuffers (GLsizei n, GLuint* framebuffers) = 0;
		virtual void glGenRenderbuffers (GLsizei n, GLuint* renderbuffers) = 0;
		//virtual void glGenTextures (GLsizei n, GLuint* textures); DUPLICATE
		virtual void glGetActiveAttrib (GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name) = 0;
		virtual void glGetActiveUniform (GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name) = 0;
		virtual void glGetAttachedShaders (GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders) = 0;
		virtual int glGetAttribLocation (GLuint program, const GLchar* name) = 0;
		//virtual void glGetBooleanv (GLenum pname, GLboolean* params); DUPLICATE
		//virtual void glGetBufferParameteriv (GLenum target, GLenum pname, GLint* params); DUPLICATE
		//virtual GLenum glGetError (void); DUPLICATE
		//virtual void glGetFloatv (GLenum pname, GLfloat* params); DUPLICATE
		virtual void glGetFramebufferAttachmentParameteriv (GLenum target, GLenum attachment, GLenum pname, GLint* params) = 0;
		//virtual void glGetIntegerv (GLenum pname, GLint* params); DUPLICATE
		virtual void glGetProgramiv (GLuint program, GLenum pname, GLint* params) = 0;
		virtual void glGetProgramInfoLog (GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog) = 0;
		virtual void glGetRenderbufferParameteriv (GLenum target, GLenum pname, GLint* params) = 0;
		virtual void glGetShaderiv (GLuint shader, GLenum pname, GLint* params) = 0;
		virtual void glGetShaderInfoLog (GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog) = 0;
		virtual void glGetShaderPrecisionFormat (GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision) = 0;
		virtual void glGetShaderSource (GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* source) = 0;
		//virtual const GLubyte* glGetString (GLenum name); DUPLICATE
		//virtual void glGetTexParameterfv (GLenum target, GLenum pname, GLfloat* params); DUPLICATE
		//virtual void glGetTexParameteriv (GLenum target, GLenum pname, GLint* params); DUPLICATE
		virtual void glGetUniformfv (GLuint program, GLint location, GLfloat* params) = 0;
		virtual void glGetUniformiv (GLuint program, GLint location, GLint* params) = 0;
		virtual int glGetUniformLocation (GLuint program, const GLchar* name) = 0;
		virtual void glGetVertexAttribfv (GLuint index, GLenum pname, GLfloat* params) = 0;
		virtual void glGetVertexAttribiv (GLuint index, GLenum pname, GLint* params) = 0;
		virtual void glGetVertexAttribPointerv (GLuint index, GLenum pname, GLvoid** pointer) = 0;
		//virtual void glHint (GLenum target, GLenum mode); DUPLICATE
		//virtual GLboolean glIsBuffer (GLuint buffer); DUPLICATE
		//virtual GLboolean glIsEnabled (GLenum cap); DUPLICATE
		virtual GLboolean glIsFramebuffer (GLuint framebuffer) = 0;
		virtual GLboolean glIsProgram (GLuint program) = 0;
		virtual GLboolean glIsRenderbuffer (GLuint renderbuffer) = 0;
		virtual GLboolean glIsShader (GLuint shader) = 0;
		//virtual GLboolean glIsTexture (GLuint texture); DUPLICATE
		//virtual void glLineWidth (GLfloat width); DUPLICATE
		virtual void glLinkProgram (GLuint program) = 0;
		//virtual void glPixelStorei (GLenum pname, GLint param); DUPLICATE
		//virtual void glPolygonOffset (GLfloat factor, GLfloat units); DUPLICATE
		//virtual void glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels); DUPLICATE
		virtual void glReleaseShaderCompiler (void) = 0;
		virtual void glRenderbufferStorage (GLenum target, GLenum internalformat, GLsizei width, GLsizei height) = 0;
		//virtual void glSampleCoverage (GLclampf value, GLboolean invert); DUPLICATE
		//virtual void glScissor (GLint x, GLint y, GLsizei width, GLsizei height); DUPLICATE
		virtual void glRenderbufferStorageMultisampleAPPLE(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) = 0;
		virtual void glResolveMultisampleFramebufferAPPLE(void) = 0;
		virtual void glShaderBinary (GLsizei n, const GLuint* shaders, GLenum binaryformat, const GLvoid* binary, GLsizei length) = 0;
		virtual void glShaderSource (GLuint shader, GLsizei count, const GLchar** string, const GLint* length) = 0;
		//virtual void glStencilFunc (GLenum func, GLint ref, GLuint mask); DUPLICATE
		virtual void glStencilFuncSeparate (GLenum face, GLenum func, GLint ref, GLuint mask) = 0;
		//virtual void glStencilMask (GLuint mask); DUPLICATE
		virtual void glStencilMaskSeparate (GLenum face, GLuint mask) = 0;
		//virtual void glStencilOp (GLenum fail, GLenum zfail, GLenum zpass); DUPLICATE
		virtual void glStencilOpSeparate (GLenum face, GLenum fail, GLenum zfail, GLenum zpass) = 0;
		//virtual void glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels); DUPLICATE
		//virtual void glTexParameterf (GLenum target, GLenum pname, GLfloat param); DUPLICATE
		virtual void glTexParameterfv (GLenum target, GLenum pname, const GLfloat* params) = 0;
		//virtual void glTexParameteri (GLenum target, GLenum pname, GLint param); DUPLICATE
		//virtual void glTexParameteriv (GLenum target, GLenum pname, const GLint* params); DUPLICATE
		//virtual void glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels); DUPLICATE
		virtual void glUniform1f (GLint location, GLfloat x) = 0;
		virtual void glUniform1fv (GLint location, GLsizei count, const GLfloat* v) = 0;
		virtual void glUniform1i (GLint location, GLint x) = 0;
		virtual void glUniform1iv (GLint location, GLsizei count, const GLint* v) = 0;
		virtual void glUniform2f (GLint location, GLfloat x, GLfloat y) = 0;
		virtual void glUniform2fv (GLint location, GLsizei count, const GLfloat* v) = 0;
		virtual void glUniform2i (GLint location, GLint x, GLint y) = 0;
		virtual void glUniform2iv (GLint location, GLsizei count, const GLint* v) = 0;
		virtual void glUniform3f (GLint location, GLfloat x, GLfloat y, GLfloat z) = 0;
		virtual void glUniform3fv (GLint location, GLsizei count, const GLfloat* v) = 0;
		virtual void glUniform3i (GLint location, GLint x, GLint y, GLint z) = 0;
		virtual void glUniform3iv (GLint location, GLsizei count, const GLint* v) = 0;
		virtual void glUniform4f (GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w) = 0;
		virtual void glUniform4fv (GLint location, GLsizei count, const GLfloat* v) = 0;
		virtual void glUniform4i (GLint location, GLint x, GLint y, GLint z, GLint w) = 0;
		virtual void glUniform4iv (GLint location, GLsizei count, const GLint* v) = 0;
		virtual void glUniformMatrix2fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = 0;
		virtual void glUniformMatrix3fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = 0;
		virtual void glUniformMatrix4fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = 0;
		virtual void glUseProgram (GLuint program) = 0;
		virtual void glValidateProgram (GLuint program) = 0;
		virtual void glVertexAttrib1f (GLuint indx, GLfloat x) = 0;
		virtual void glVertexAttrib1fv (GLuint indx, const GLfloat* values) = 0;
		virtual void glVertexAttrib2f (GLuint indx, GLfloat x, GLfloat y) = 0;
		virtual void glVertexAttrib2fv (GLuint indx, const GLfloat* values) = 0;
		virtual void glVertexAttrib3f (GLuint indx, GLfloat x, GLfloat y, GLfloat z) = 0;
		virtual void glVertexAttrib3fv (GLuint indx, const GLfloat* values) = 0;
		virtual void glVertexAttrib4f (GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w) = 0;
		virtual void glVertexAttrib4fv (GLuint indx, const GLfloat* values) = 0;
		virtual void glVertexAttribPointer (GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr) = 0;
		//virtual void glViewport (GLint x, GLint y, GLsizei width, GLsizei height); DUPLICATE
		
		// OpenGL ES 2 Extensions
		virtual void glGetBufferPointervOES (GLenum target, GLenum pname, GLvoid **params) = 0;
		virtual GLvoid * glMapBufferOES (GLenum target, GLenum access) = 0;
		virtual GLboolean glUnmapBufferOES (GLenum target) = 0;
		
	protected:
		OpenGLESImplementation *implementation;
		int version;
	};
	
}

#endif
