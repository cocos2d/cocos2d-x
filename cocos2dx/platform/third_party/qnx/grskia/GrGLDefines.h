/*
    Copyright 2011 Google Inc.

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


#ifndef GrGLDefines_DEFINED
#define GrGLDefines_DEFINED

// The following constants consist of the intersection of GL constants
// exported by GLES 1.0, GLES 2.0, and desktop GL required by the system.

#define GR_GL_DEPTH_BUFFER_BIT               0x00000100
#define GR_GL_STENCIL_BUFFER_BIT             0x00000400
#define GR_GL_COLOR_BUFFER_BIT               0x00004000

/* Boolean */
#define GR_GL_FALSE                          0
#define GR_GL_TRUE                           1

/* BeginMode */
#define GR_GL_POINTS                         0x0000
#define GR_GL_LINES                          0x0001
#define GR_GL_LINE_LOOP                      0x0002
#define GR_GL_LINE_STRIP                     0x0003
#define GR_GL_TRIANGLES                      0x0004
#define GR_GL_TRIANGLE_STRIP                 0x0005
#define GR_GL_TRIANGLE_FAN                   0x0006

/* AlphaFunction (not supported in ES20) */
/*      GL_NEVER */
/*      GL_LESS */
/*      GL_EQUAL */
/*      GL_LEQUAL */
/*      GL_GREATER */
/*      GL_NOTEQUAL */
/*      GL_GEQUAL */
/*      GL_ALWAYS */

/* BlendingFactorDest */
#define GR_GL_ZERO                           0
#define GR_GL_ONE                            1
#define GR_GL_SRC_COLOR                      0x0300
#define GR_GL_ONE_MINUS_SRC_COLOR            0x0301
#define GR_GL_SRC_ALPHA                      0x0302
#define GR_GL_ONE_MINUS_SRC_ALPHA            0x0303
#define GR_GL_DST_ALPHA                      0x0304
#define GR_GL_ONE_MINUS_DST_ALPHA            0x0305

/* BlendingFactorSrc */
/*      GL_ZERO */
/*      GL_ONE */
#define GR_GL_DST_COLOR                      0x0306
#define GR_GL_ONE_MINUS_DST_COLOR            0x0307
#define GR_GL_SRC_ALPHA_SATURATE             0x0308
/*      GL_SRC_ALPHA */
/*      GL_ONE_MINUS_SRC_ALPHA */
/*      GL_DST_ALPHA */
/*      GL_ONE_MINUS_DST_ALPHA */

/* ExtendedBlendFactors */
#define GR_GL_SRC1_COLOR                     0x88F9
#define GR_GL_ONE_MINUS_SRC1_COLOR           0x88FA
/*      GL_SRC1_ALPHA */
#define GR_GL_ONE_MINUS_SRC1_ALPHA           0x88FB

/* BlendEquationSeparate */
#define GR_GL_FUNC_ADD                       0x8006
#define GR_GL_BLEND_EQUATION                 0x8009
#define GR_GL_BLEND_EQUATION_RGB             0x8009    /* same as BLEND_EQUATION */
#define GR_GL_BLEND_EQUATION_ALPHA           0x883D

/* BlendSubtract */
#define GR_GL_FUNC_SUBTRACT                  0x800A
#define GR_GL_FUNC_REVERSE_SUBTRACT          0x800B

/* Separate Blend Functions */
#define GR_GL_BLEND_DST_RGB                  0x80C8
#define GR_GL_BLEND_SRC_RGB                  0x80C9
#define GR_GL_BLEND_DST_ALPHA                0x80CA
#define GR_GL_BLEND_SRC_ALPHA                0x80CB
#define GR_GL_CONSTANT_COLOR                 0x8001
#define GR_GL_ONE_MINUS_CONSTANT_COLOR       0x8002
#define GR_GL_CONSTANT_ALPHA                 0x8003
#define GR_GL_ONE_MINUS_CONSTANT_ALPHA       0x8004
#define GR_GL_BLEND_COLOR                    0x8005

/* Buffer Objects */
#define GR_GL_ARRAY_BUFFER                   0x8892
#define GR_GL_ELEMENT_ARRAY_BUFFER           0x8893
#define GR_GL_ARRAY_BUFFER_BINDING           0x8894
#define GR_GL_ELEMENT_ARRAY_BUFFER_BINDING   0x8895

#define GR_GL_STREAM_DRAW                    0x88E0
#define GR_GL_STATIC_DRAW                    0x88E4
#define GR_GL_DYNAMIC_DRAW                   0x88E8

#define GR_GL_BUFFER_SIZE                    0x8764
#define GR_GL_BUFFER_USAGE                   0x8765

#define GR_GL_CURRENT_VERTEX_ATTRIB          0x8626

/* CullFaceMode */
#define GR_GL_FRONT                          0x0404
#define GR_GL_BACK                           0x0405
#define GR_GL_FRONT_AND_BACK                 0x0408

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
#define GR_GL_TEXTURE_2D                     0x0DE1
#define GR_GL_CULL_FACE                      0x0B44
#define GR_GL_BLEND                          0x0BE2
#define GR_GL_DITHER                         0x0BD0
#define GR_GL_STENCIL_TEST                   0x0B90
#define GR_GL_DEPTH_TEST                     0x0B71
#define GR_GL_SCISSOR_TEST                   0x0C11
#define GR_GL_POLYGON_OFFSET_FILL            0x8037
#define GR_GL_SAMPLE_ALPHA_TO_COVERAGE       0x809E
#define GR_GL_SAMPLE_COVERAGE                0x80A0

/* ErrorCode */
#define GR_GL_NO_ERROR                       0
#define GR_GL_INVALID_ENUM                   0x0500
#define GR_GL_INVALID_VALUE                  0x0501
#define GR_GL_INVALID_OPERATION              0x0502
#define GR_GL_OUT_OF_MEMORY                  0x0505
#define GR_GL_CONTEXT_LOST                   0x300E  // TODO(gman): What value?

/* FrontFaceDirection */
#define GR_GL_CW                             0x0900
#define GR_GL_CCW                            0x0901

/* GetPName */
#define GR_GL_LINE_WIDTH                     0x0B21
#define GR_GL_ALIASED_POINT_SIZE_RANGE       0x846D
#define GR_GL_ALIASED_LINE_WIDTH_RANGE       0x846E
#define GR_GL_CULL_FACE_MODE                 0x0B45
#define GR_GL_FRONT_FACE                     0x0B46
#define GR_GL_DEPTH_RANGE                    0x0B70
#define GR_GL_DEPTH_WRITEMASK                0x0B72
#define GR_GL_DEPTH_CLEAR_VALUE              0x0B73
#define GR_GL_DEPTH_FUNC                     0x0B74
#define GR_GL_STENCIL_CLEAR_VALUE            0x0B91
#define GR_GL_STENCIL_FUNC                   0x0B92
#define GR_GL_STENCIL_FAIL                   0x0B94
#define GR_GL_STENCIL_PASS_DEPTH_FAIL        0x0B95
#define GR_GL_STENCIL_PASS_DEPTH_PASS        0x0B96
#define GR_GL_STENCIL_REF                    0x0B97
#define GR_GL_STENCIL_VALUE_MASK             0x0B93
#define GR_GL_STENCIL_WRITEMASK              0x0B98
#define GR_GL_STENCIL_BACK_FUNC              0x8800
#define GR_GL_STENCIL_BACK_FAIL              0x8801
#define GR_GL_STENCIL_BACK_PASS_DEPTH_FAIL   0x8802
#define GR_GL_STENCIL_BACK_PASS_DEPTH_PASS   0x8803
#define GR_GL_STENCIL_BACK_REF               0x8CA3
#define GR_GL_STENCIL_BACK_VALUE_MASK        0x8CA4
#define GR_GL_STENCIL_BACK_WRITEMASK         0x8CA5
#define GR_GL_VIEWPORT                       0x0BA2
#define GR_GL_SCISSOR_BOX                    0x0C10
/*      GL_SCISSOR_TEST */
#define GR_GL_COLOR_CLEAR_VALUE              0x0C22
#define GR_GL_COLOR_WRITEMASK                0x0C23
#define GR_GL_UNPACK_ALIGNMENT               0x0CF5
#define GR_GL_PACK_ALIGNMENT                 0x0D05
#define GR_GL_MAX_TEXTURE_SIZE               0x0D33
#define GR_GL_MAX_VIEWPORT_DIMS              0x0D3A
#define GR_GL_SUBPIXEL_BITS                  0x0D50
#define GR_GL_RED_BITS                       0x0D52
#define GR_GL_GREEN_BITS                     0x0D53
#define GR_GL_BLUE_BITS                      0x0D54
#define GR_GL_ALPHA_BITS                     0x0D55
#define GR_GL_DEPTH_BITS                     0x0D56
#define GR_GL_STENCIL_BITS                   0x0D57
#define GR_GL_POLYGON_OFFSET_UNITS           0x2A00
/*      GL_POLYGON_OFFSET_FILL */
#define GR_GL_POLYGON_OFFSET_FACTOR          0x8038
#define GR_GL_TEXTURE_BINDING_2D             0x8069
#define GR_GL_SAMPLE_BUFFERS                 0x80A8
#define GR_GL_SAMPLES                        0x80A9
#define GR_GL_SAMPLE_COVERAGE_VALUE          0x80AA
#define GR_GL_SAMPLE_COVERAGE_INVERT         0x80AB

/* GetTextureParameter */
/*      GL_TEXTURE_MAG_FILTER */
/*      GL_TEXTURE_MIN_FILTER */
/*      GL_TEXTURE_WRAP_S */
/*      GL_TEXTURE_WRAP_T */

#define GR_GL_NUM_COMPRESSED_TEXTURE_FORMATS 0x86A2
#define GR_GL_COMPRESSED_TEXTURE_FORMATS     0x86A3

/* HintMode */
#define GR_GL_DONT_CARE                      0x1100
#define GR_GL_FASTEST                        0x1101
#define GR_GL_NICEST                         0x1102

/* HintTarget */
#define GR_GL_GENERATE_MIPMAP_HINT            0x8192

/* DataType */
#define GR_GL_BYTE                           0x1400
#define GR_GL_UNSIGNED_BYTE                  0x1401
#define GR_GL_SHORT                          0x1402
#define GR_GL_UNSIGNED_SHORT                 0x1403
#define GR_GL_INT                            0x1404
#define GR_GL_UNSIGNED_INT                   0x1405
#define GR_GL_FLOAT                          0x1406
#define GR_GL_FIXED                          0x140C

/* Lighting */
#define GR_GL_LIGHTING                       0x0B50
#define GR_GL_LIGHT0                         0x4000
#define GR_GL_LIGHT1                         0x4001
#define GR_GL_LIGHT2                         0x4002
#define GR_GL_LIGHT3                         0x4003
#define GR_GL_LIGHT4                         0x4004
#define GR_GL_LIGHT5                         0x4005
#define GR_GL_LIGHT6                         0x4006
#define GR_GL_LIGHT7                         0x4007
#define GR_GL_SPOT_EXPONENT                  0x1205
#define GR_GL_SPOT_CUTOFF                    0x1206
#define GR_GL_CONSTANT_ATTENUATION           0x1207
#define GR_GL_LINEAR_ATTENUATION             0x1208
#define GR_GL_QUADRATIC_ATTENUATION          0x1209
#define GR_GL_AMBIENT                        0x1200
#define GR_GL_DIFFUSE                        0x1201
#define GR_GL_SPECULAR                       0x1202
#define GR_GL_SHININESS                      0x1601
#define GR_GL_EMISSION                       0x1600
#define GR_GL_POSITION                       0x1203
#define GR_GL_SPOT_DIRECTION                 0x1204
#define GR_GL_AMBIENT_AND_DIFFUSE            0x1602
#define GR_GL_COLOR_INDEXES                  0x1603
#define GR_GL_LIGHT_MODEL_TWO_SIDE           0x0B52
#define GR_GL_LIGHT_MODEL_LOCAL_VIEWER       0x0B51
#define GR_GL_LIGHT_MODEL_AMBIENT            0x0B53
#define GR_GL_FRONT_AND_BACK                 0x0408
#define GR_GL_SHADE_MODEL                    0x0B54
#define GR_GL_FLAT                           0x1D00
#define GR_GL_SMOOTH                         0x1D01
#define GR_GL_COLOR_MATERIAL                 0x0B57
#define GR_GL_COLOR_MATERIAL_FACE            0x0B55
#define GR_GL_COLOR_MATERIAL_PARAMETER       0x0B56
#define GR_GL_NORMALIZE                      0x0BA1

/* Matrix Mode */
#define GR_GL_MATRIX_MODE                    0x0BA0
#define GR_GL_MODELVIEW                      0x1700
#define GR_GL_PROJECTION                     0x1701
#define GR_GL_TEXTURE                        0x1702

/* multisample */
#define GR_GL_MULTISAMPLE                    0x809D

/* Points */
#define GR_GL_POINT_SMOOTH                   0x0B10
#define GR_GL_POINT_SIZE                     0x0B11
#define GR_GL_POINT_SIZE_GRANULARITY         0x0B13
#define GR_GL_POINT_SIZE_RANGE               0x0B12

/* Lines */
#define GR_GL_LINE_SMOOTH                    0x0B20
#define GR_GL_LINE_STIPPLE                   0x0B24
#define GR_GL_LINE_STIPPLE_PATTERN           0x0B25
#define GR_GL_LINE_STIPPLE_REPEAT            0x0B26
#define GR_GL_LINE_WIDTH                     0x0B21
#define GR_GL_LINE_WIDTH_GRANULARITY         0x0B23
#define GR_GL_LINE_WIDTH_RANGE               0x0B22

/* PixelFormat */
#define GR_GL_DEPTH_COMPONENT                0x1902
#define GR_GL_ALPHA                          0x1906
#define GR_GL_RGB                            0x1907
#define GR_GL_RGBA                           0x1908
#define GR_GL_BGRA                           0x80E1
#define GR_GL_LUMINANCE                      0x1909
#define GR_GL_LUMINANCE_ALPHA                0x190A
#define GR_GL_PALETTE8_RGBA8                 0x8B96

/* PixelType */
/*      GL_UNSIGNED_BYTE */
#define GR_GL_UNSIGNED_SHORT_4_4_4_4         0x8033
#define GR_GL_UNSIGNED_SHORT_5_5_5_1         0x8034
#define GR_GL_UNSIGNED_SHORT_5_6_5           0x8363

/* Shaders */
#define GR_GL_FRAGMENT_SHADER                  0x8B30
#define GR_GL_VERTEX_SHADER                    0x8B31
#define GR_GL_MAX_VERTEX_ATTRIBS               0x8869
#define GR_GL_MAX_VERTEX_UNIFORM_VECTORS       0x8DFB
#define GR_GL_MAX_VARYING_VECTORS              0x8DFC
#define GR_GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 0x8B4D
#define GR_GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS   0x8B4C
#define GR_GL_MAX_TEXTURE_IMAGE_UNITS          0x8872
#define GR_GL_MAX_FRAGMENT_UNIFORM_VECTORS     0x8DFD
#define GR_GL_SHADER_TYPE                      0x8B4F
#define GR_GL_DELETE_STATUS                    0x8B80
#define GR_GL_LINK_STATUS                      0x8B82
#define GR_GL_VALIDATE_STATUS                  0x8B83
#define GR_GL_ATTACHED_SHADERS                 0x8B85
#define GR_GL_ACTIVE_UNIFORMS                  0x8B86
#define GR_GL_ACTIVE_UNIFORM_MAX_LENGTH        0x8B87
#define GR_GL_ACTIVE_ATTRIBUTES                0x8B89
#define GR_GL_ACTIVE_ATTRIBUTE_MAX_LENGTH      0x8B8A
#define GR_GL_SHADING_LANGUAGE_VERSION         0x8B8C
#define GR_GL_CURRENT_PROGRAM                  0x8B8D
#define GR_GL_MAX_FRAGMENT_UNIFORM_COMPONENTS  0x8B49
#define GR_GL_MAX_VERTEX_UNIFORM_COMPONENTS    0x8B4A

/* StencilFunction */
#define GR_GL_NEVER                          0x0200
#define GR_GL_LESS                           0x0201
#define GR_GL_EQUAL                          0x0202
#define GR_GL_LEQUAL                         0x0203
#define GR_GL_GREATER                        0x0204
#define GR_GL_NOTEQUAL                       0x0205
#define GR_GL_GEQUAL                         0x0206
#define GR_GL_ALWAYS                         0x0207

/* StencilOp */
/*      GL_ZERO */
#define GR_GL_KEEP                           0x1E00
#define GR_GL_REPLACE                        0x1E01
#define GR_GL_INCR                           0x1E02
#define GR_GL_DECR                           0x1E03
#define GR_GL_INVERT                         0x150A
#define GR_GL_INCR_WRAP                      0x8507
#define GR_GL_DECR_WRAP                      0x8508

/* StringName */
#define GR_GL_VENDOR                         0x1F00
#define GR_GL_RENDERER                       0x1F01
#define GR_GL_VERSION                        0x1F02
#define GR_GL_EXTENSIONS                     0x1F03

/* Pixel Mode / Transfer */
#define GR_GL_UNPACK_ROW_LENGTH            0x0CF2

/* TextureMagFilter */
#define GR_GL_NEAREST                        0x2600
#define GR_GL_LINEAR                         0x2601

/* TextureMinFilter */
/*      GL_NEAREST */
/*      GL_LINEAR */
#define GR_GL_NEAREST_MIPMAP_NEAREST         0x2700
#define GR_GL_LINEAR_MIPMAP_NEAREST          0x2701
#define GR_GL_NEAREST_MIPMAP_LINEAR          0x2702
#define GR_GL_LINEAR_MIPMAP_LINEAR           0x2703

/* TextureParameterName */
#define GR_GL_TEXTURE_MAG_FILTER             0x2800
#define GR_GL_TEXTURE_MIN_FILTER             0x2801
#define GR_GL_TEXTURE_WRAP_S                 0x2802
#define GR_GL_TEXTURE_WRAP_T                 0x2803

/* TextureTarget */
/*      GL_TEXTURE_2D */
#define GR_GL_TEXTURE                        0x1702
#define GR_GL_TEXTURE_CUBE_MAP               0x8513
#define GR_GL_TEXTURE_BINDING_CUBE_MAP       0x8514
#define GR_GL_TEXTURE_CUBE_MAP_POSITIVE_X    0x8515
#define GR_GL_TEXTURE_CUBE_MAP_NEGATIVE_X    0x8516
#define GR_GL_TEXTURE_CUBE_MAP_POSITIVE_Y    0x8517
#define GR_GL_TEXTURE_CUBE_MAP_NEGATIVE_Y    0x8518
#define GR_GL_TEXTURE_CUBE_MAP_POSITIVE_Z    0x8519
#define GR_GL_TEXTURE_CUBE_MAP_NEGATIVE_Z    0x851A
#define GR_GL_MAX_CUBE_MAP_TEXTURE_SIZE      0x851C

/* TextureUnit */
#define GR_GL_TEXTURE0                       0x84C0
#define GR_GL_TEXTURE1                       0x84C1
#define GR_GL_TEXTURE2                       0x84C2
#define GR_GL_TEXTURE3                       0x84C3
#define GR_GL_TEXTURE4                       0x84C4
#define GR_GL_TEXTURE5                       0x84C5
#define GR_GL_TEXTURE6                       0x84C6
#define GR_GL_TEXTURE7                       0x84C7
#define GR_GL_TEXTURE8                       0x84C8
#define GR_GL_TEXTURE9                       0x84C9
#define GR_GL_TEXTURE10                      0x84CA
#define GR_GL_TEXTURE11                      0x84CB
#define GR_GL_TEXTURE12                      0x84CC
#define GR_GL_TEXTURE13                      0x84CD
#define GR_GL_TEXTURE14                      0x84CE
#define GR_GL_TEXTURE15                      0x84CF
#define GR_GL_TEXTURE16                      0x84D0
#define GR_GL_TEXTURE17                      0x84D1
#define GR_GL_TEXTURE18                      0x84D2
#define GR_GL_TEXTURE19                      0x84D3
#define GR_GL_TEXTURE20                      0x84D4
#define GR_GL_TEXTURE21                      0x84D5
#define GR_GL_TEXTURE22                      0x84D6
#define GR_GL_TEXTURE23                      0x84D7
#define GR_GL_TEXTURE24                      0x84D8
#define GR_GL_TEXTURE25                      0x84D9
#define GR_GL_TEXTURE26                      0x84DA
#define GR_GL_TEXTURE27                      0x84DB
#define GR_GL_TEXTURE28                      0x84DC
#define GR_GL_TEXTURE29                      0x84DD
#define GR_GL_TEXTURE30                      0x84DE
#define GR_GL_TEXTURE31                      0x84DF
#define GR_GL_ACTIVE_TEXTURE                 0x84E0
#define GR_GL_MAX_TEXTURE_UNITS              0x84E2

/* TextureWrapMode */
#define GR_GL_REPEAT                         0x2901
#define GR_GL_CLAMP_TO_EDGE                  0x812F
#define GR_GL_MIRRORED_REPEAT                0x8370

/* Texture mapping */
#define GR_GL_TEXTURE_ENV                   0x2300
#define GR_GL_TEXTURE_ENV_MODE              0x2200
#define GR_GL_TEXTURE_1D                    0x0DE0
#define GR_GL_TEXTURE_2D                    0x0DE1
/*	GL_TEXTURE_WRAP_S */
/*	GL_TEXTURE_WRAP_T */
/*	GL_TEXTURE_MAG_FILTER */
/*	GL_TEXTURE_MIN_FILTER */
#define GR_GL_TEXTURE_ENV_COLOR             0x2201
#define GR_GL_TEXTURE_GEN_S                 0x0C60
#define GR_GL_TEXTURE_GEN_T                 0x0C61
#define GR_GL_TEXTURE_GEN_MODE              0x2500
#define GR_GL_TEXTURE_BORDER_COLOR          0x1004
#define GR_GL_TEXTURE_WIDTH                 0x1000
#define GR_GL_TEXTURE_HEIGHT                0x1001
#define GR_GL_TEXTURE_BORDER                0x1005
#define GR_GL_TEXTURE_COMPONENTS            0x1003
#define GR_GL_TEXTURE_RED_SIZE              0x805C
#define GR_GL_TEXTURE_GREEN_SIZE            0x805D
#define GR_GL_TEXTURE_BLUE_SIZE             0x805E
#define GR_GL_TEXTURE_ALPHA_SIZE            0x805F
#define GR_GL_TEXTURE_LUMINANCE_SIZE        0x8060
#define GR_GL_TEXTURE_INTENSITY_SIZE        0x8061
/*	GL_NEAREST_MIPMAP_NEAREST */
/*	GL_NEAREST_MIPMAP_LINEAR */
/*	GL_LINEAR_MIPMAP_NEAREST */
/*	GL_LINEAR_MIPMAP_LINEAR */
#define GR_GL_OBJECT_LINEAR                 0x2401
#define GR_GL_OBJECT_PLANE                  0x2501
#define GR_GL_EYE_LINEAR                    0x2400
#define GR_GL_EYE_PLANE                     0x2502
#define GR_GL_SPHERE_MAP                    0x2402
#define GR_GL_DECAL                         0x2101
#define GR_GL_MODULATE                      0x2100
/*	GL_NEAREST */
/*	GL_REPEAT */
#define GR_GL_CLAMP                         0x2900
#define GR_GL_S                             0x2000
#define GR_GL_T                             0x2001
#define GR_GL_R                             0x2002
#define GR_GL_Q                             0x2003
#define GR_GL_TEXTURE_GEN_R                 0x0C62
#define GR_GL_TEXTURE_GEN_Q                 0x0C63

/* texture_env_combine */
#define GR_GL_COMBINE                       0x8570
#define GR_GL_COMBINE_RGB                   0x8571
#define GR_GL_COMBINE_ALPHA                 0x8572
#define GR_GL_SOURCE0_RGB                   0x8580
#define GR_GL_SOURCE1_RGB                   0x8581
#define GR_GL_SOURCE2_RGB                   0x8582
#define GR_GL_SOURCE0_ALPHA                 0x8588
#define GR_GL_SOURCE1_ALPHA                 0x8589
#define GR_GL_SOURCE2_ALPHA                 0x858A
#define GR_GL_OPERAND0_RGB                  0x8590
#define GR_GL_OPERAND1_RGB                  0x8591
#define GR_GL_OPERAND2_RGB                  0x8592
#define GR_GL_OPERAND0_ALPHA                0x8598
#define GR_GL_OPERAND1_ALPHA                0x8599
#define GR_GL_OPERAND2_ALPHA                0x859A
#define GR_GL_RGB_SCALE                     0x8573
#define GR_GL_ADD_SIGNED                    0x8574
#define GR_GL_INTERPOLATE                   0x8575
#define GR_GL_SUBTRACT                      0x84E7
#define GR_GL_CONSTANT                      0x8576
#define GR_GL_PRIMARY_COLOR                 0x8577
#define GR_GL_PREVIOUS                      0x8578
#define GR_GL_SRC0_RGB                      0x8580
#define GR_GL_SRC1_RGB                      0x8581
#define GR_GL_SRC2_RGB                      0x8582
#define GR_GL_SRC0_ALPHA                    0x8588
#define GR_GL_SRC1_ALPHA                    0x8589
#define GR_GL_SRC2_ALPHA                    0x858A

/* Uniform Types */
#define GR_GL_FLOAT_VEC2                     0x8B50
#define GR_GL_FLOAT_VEC3                     0x8B51
#define GR_GL_FLOAT_VEC4                     0x8B52
#define GR_GL_INT_VEC2                       0x8B53
#define GR_GL_INT_VEC3                       0x8B54
#define GR_GL_INT_VEC4                       0x8B55
#define GR_GL_BOOL                           0x8B56
#define GR_GL_BOOL_VEC2                      0x8B57
#define GR_GL_BOOL_VEC3                      0x8B58
#define GR_GL_BOOL_VEC4                      0x8B59
#define GR_GL_FLOAT_MAT2                     0x8B5A
#define GR_GL_FLOAT_MAT3                     0x8B5B
#define GR_GL_FLOAT_MAT4                     0x8B5C
#define GR_GL_SAMPLER_2D                     0x8B5E
#define GR_GL_SAMPLER_CUBE                   0x8B60

/* Vertex Arrays */
#define GR_GL_VERTEX_ATTRIB_ARRAY_ENABLED        0x8622
#define GR_GL_VERTEX_ATTRIB_ARRAY_SIZE           0x8623
#define GR_GL_VERTEX_ATTRIB_ARRAY_STRIDE         0x8624
#define GR_GL_VERTEX_ATTRIB_ARRAY_TYPE           0x8625
#define GR_GL_VERTEX_ATTRIB_ARRAY_NORMALIZED     0x886A
#define GR_GL_VERTEX_ATTRIB_ARRAY_POINTER        0x8645
#define GR_GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING 0x889F
#define GR_GL_VERTEX_ARRAY                       0x8074
#define GR_GL_NORMAL_ARRAY                       0x8075
#define GR_GL_COLOR_ARRAY                        0x8076
#define GR_GL_INDEX_ARRAY                        0x8077
#define GR_GL_TEXTURE_COORD_ARRAY                0x8078
#define GR_GL_EDGE_FLAG_ARRAY                    0x8079
#define GR_GL_VERTEX_ARRAY_SIZE                  0x807A
#define GR_GL_VERTEX_ARRAY_TYPE                  0x807B
#define GR_GL_VERTEX_ARRAY_STRIDE                0x807C
#define GR_GL_NORMAL_ARRAY_TYPE                  0x807E
#define GR_GL_NORMAL_ARRAY_STRIDE                0x807F
#define GR_GL_COLOR_ARRAY_SIZE                   0x8081
#define GR_GL_COLOR_ARRAY_TYPE                   0x8082
#define GR_GL_COLOR_ARRAY_STRIDE                 0x8083
#define GR_GL_INDEX_ARRAY_TYPE                   0x8085
#define GR_GL_INDEX_ARRAY_STRIDE                 0x8086
#define GR_GL_TEXTURE_COORD_ARRAY_SIZE           0x8088
#define GR_GL_TEXTURE_COORD_ARRAY_TYPE           0x8089
#define GR_GL_TEXTURE_COORD_ARRAY_STRIDE         0x808A
#define GR_GL_EDGE_FLAG_ARRAY_STRIDE             0x808C
#define GR_GL_VERTEX_ARRAY_POINTER               0x808E
#define GR_GL_NORMAL_ARRAY_POINTER               0x808F
#define GR_GL_COLOR_ARRAY_POINTER                0x8090
#define GR_GL_INDEX_ARRAY_POINTER                0x8091
#define GR_GL_TEXTURE_COORD_ARRAY_POINTER        0x8092
#define GR_GL_EDGE_FLAG_ARRAY_POINTER            0x8093
#define GR_GL_V2F                                0x2A20
#define GR_GL_V3F                                0x2A21
#define GR_GL_C4UB_V2F                           0x2A22
#define GR_GL_C4UB_V3F                           0x2A23
#define GR_GL_C3F_V3F                            0x2A24
#define GR_GL_N3F_V3F                            0x2A25
#define GR_GL_C4F_N3F_V3F                        0x2A26
#define GR_GL_T2F_V3F                            0x2A27
#define GR_GL_T4F_V4F                            0x2A28
#define GR_GL_T2F_C4UB_V3F                       0x2A29
#define GR_GL_T2F_C3F_V3F                        0x2A2A
#define GR_GL_T2F_N3F_V3F                        0x2A2B
#define GR_GL_T2F_C4F_N3F_V3F                    0x2A2C
#define GR_GL_T4F_C4F_N3F_V4F                    0x2A2D

/* Vertex Buffer Object */
#define GR_GL_WRITE_ONLY                         0x88B9
#define GR_GL_BUFFER_MAPPED                      0x88BC
/* Read Format */
#define GR_GL_IMPLEMENTATION_COLOR_READ_TYPE   0x8B9A
#define GR_GL_IMPLEMENTATION_COLOR_READ_FORMAT 0x8B9B

/* Shader Source */
#define GR_GL_COMPILE_STATUS                 0x8B81
#define GR_GL_INFO_LOG_LENGTH                0x8B84
#define GR_GL_SHADER_SOURCE_LENGTH           0x8B88
#define GR_GL_SHADER_COMPILER                0x8DFA

/* Shader Binary */
#define GR_GL_SHADER_BINARY_FORMATS          0x8DF8
#define GR_GL_NUM_SHADER_BINARY_FORMATS      0x8DF9

/* Shader Precision-Specified Types */
#define GR_GL_LOW_FLOAT                      0x8DF0
#define GR_GL_MEDIUM_FLOAT                   0x8DF1
#define GR_GL_HIGH_FLOAT                     0x8DF2
#define GR_GL_LOW_INT                        0x8DF3
#define GR_GL_MEDIUM_INT                     0x8DF4
#define GR_GL_HIGH_INT                       0x8DF5

/* Framebuffer Object. */
#define GR_GL_FRAMEBUFFER                    0x8D40
#define GR_GL_READ_FRAMEBUFFER               0x8CA8
#define GR_GL_DRAW_FRAMEBUFFER               0x8CA9

#define GR_GL_RENDERBUFFER                   0x8D41

#define GR_GL_RGBA4                          0x8056
#define GR_GL_RGB5_A1                        0x8057
#define GR_GL_RGB565                         0x8D62
#define GR_GL_RGBA8                          0x8058
#define GR_GL_DEPTH_COMPONENT16              0x81A5
#define GR_GL_STENCIL_INDEX                  0x1901
#define GR_GL_STENCIL_INDEX4                 0x8D47
#define GR_GL_STENCIL_INDEX8                 0x8D48
#define GR_GL_STENCIL_INDEX16                0x8D49
#define GR_GL_DEPTH_STENCIL                  0x84F9
#define GR_GL_DEPTH24_STENCIL8               0x88F0

#define GR_GL_MAX_SAMPLES                    0x8D57

#define GR_GL_RENDERBUFFER_WIDTH             0x8D42
#define GR_GL_RENDERBUFFER_HEIGHT            0x8D43
#define GR_GL_RENDERBUFFER_INTERNAL_FORMAT   0x8D44
#define GR_GL_RENDERBUFFER_RED_SIZE          0x8D50
#define GR_GL_RENDERBUFFER_GREEN_SIZE        0x8D51
#define GR_GL_RENDERBUFFER_BLUE_SIZE         0x8D52
#define GR_GL_RENDERBUFFER_ALPHA_SIZE        0x8D53
#define GR_GL_RENDERBUFFER_DEPTH_SIZE        0x8D54
#define GR_GL_RENDERBUFFER_STENCIL_SIZE      0x8D55

#define GR_GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE           0x8CD0
#define GR_GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME           0x8CD1
#define GR_GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL         0x8CD2
#define GR_GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE 0x8CD3

#define GR_GL_COLOR_ATTACHMENT0              0x8CE0
#define GR_GL_DEPTH_ATTACHMENT               0x8D00
#define GR_GL_STENCIL_ATTACHMENT             0x8D20
#define GR_GL_DEPTH_STENCIL_ATTACHMENT       0x821A

#define GR_GL_NONE                           0

#define GR_GL_FRAMEBUFFER_COMPLETE                      0x8CD5
#define GR_GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT         0x8CD6
#define GR_GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 0x8CD7
#define GR_GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS         0x8CD9
#define GR_GL_FRAMEBUFFER_UNSUPPORTED                   0x8CDD

#define GR_GL_FRAMEBUFFER_BINDING            0x8CA6
#define GR_GL_RENDERBUFFER_BINDING           0x8CA7
#define GR_GL_MAX_RENDERBUFFER_SIZE          0x84E8

#define GR_GL_INVALID_FRAMEBUFFER_OPERATION  0x0506

#endif
