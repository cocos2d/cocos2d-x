/****************************************************************************
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2012 		cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "renderer/ccShaders.h"

#define STRINGIFY(A)  #A

NS_CC_BEGIN

#if (DIRECTX_ENABLED == 1)

const ShaderDescriptor ccPosition_uColor_frag = ShaderDescriptor("Position_uColor");
const ShaderDescriptor ccPosition_uColor_vert = ShaderDescriptor("Position_uColor")
.Input("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0)
.Input("COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 12);

const ShaderDescriptor ccPositionColor_frag = ShaderDescriptor("PositionColor");
const ShaderDescriptor ccPositionColor_vert = ShaderDescriptor("PositionColor")
.Input("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0)
.Input("COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 12);

const ShaderDescriptor ccPositionTexture_frag = ShaderDescriptor("PositionTexture");
const ShaderDescriptor ccPositionTexture_vert = ShaderDescriptor("PositionTexture")
.Input("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0)
.Input("COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 12);

const ShaderDescriptor ccPositionTextureA8Color_frag = ShaderDescriptor("PositionTextureA8Color");
const ShaderDescriptor ccPositionTextureA8Color_vert = ShaderDescriptor("PositionTextureA8Color")
.Input("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0)
.Input("COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 12);

const ShaderDescriptor ccPositionTextureColor_frag = ShaderDescriptor("PositionTextureColor");
const ShaderDescriptor ccPositionTextureColor_vert = ShaderDescriptor("PositionTextureColor")
.Input("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0)
.Input("COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 12)
.Input("TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 16)
.Const(GLProgram::UNIFORM_NAME_MVP_MATRIX, sizeof(Mat4));

const ShaderDescriptor ccPositionTextureColor_noMVP_frag = ShaderDescriptor("PositionTextureColor_noMVP");
const ShaderDescriptor ccPositionTextureColor_noMVP_vert = ShaderDescriptor("PositionTextureColor_noMVP")
.Input("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0)
.Input("COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 12)
.Input("TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 16)
.Const(GLProgram::UNIFORM_NAME_P_MATRIX, sizeof(Mat4));

const ShaderDescriptor ccPositionTextureColorAlphaTest_frag = ShaderDescriptor("PositionTextureColorAlphaTest");

const ShaderDescriptor ccPositionTexture_uColor_frag = ShaderDescriptor("PositionTexture_uColor");
const ShaderDescriptor ccPositionTexture_uColor_vert = ShaderDescriptor("PositionTexture_uColor")
.Input("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0)
.Input("COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 12);

const ShaderDescriptor ccPositionColorLengthTexture_frag = ShaderDescriptor("PositionColorLengthTexture");
const ShaderDescriptor ccPositionColorLengthTexture_vert = ShaderDescriptor("PositionColorLengthTexture")
.Input("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0)
.Input("COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 12);

const ShaderDescriptor ccLabelDistanceFieldNormal_frag = ShaderDescriptor("Label_df_Normal")
.Const("u_textColor", sizeof(float) * 4);
const ShaderDescriptor ccLabelDistanceFieldGlow_frag = ShaderDescriptor("Label_df_Glow")
.Const("u_effectColor", sizeof(float) * 4)
.Const("u_textColor", sizeof(float) * 4);

const ShaderDescriptor ccLabelNormal_frag = ShaderDescriptor("Label_normal")
.Const("u_textColor", sizeof(float) * 4);
const ShaderDescriptor ccLabelOutline_frag = ShaderDescriptor("Label_outline")
.Const("u_effectColor", sizeof(float) * 4)
.Const("u_textColor", sizeof(float) * 4);

const ShaderDescriptor ccLabel_vert = ShaderDescriptor("Label")
.Input("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0)
.Input("COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 12)
.Input("TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 16)
.Const(GLProgram::UNIFORM_NAME_MVP_MATRIX, sizeof(Mat4));

const ShaderDescriptor cc3D_PositionTex_vert = ShaderDescriptor("3D_PositionTex")
.Input("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0)
.Input("COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 12);
const ShaderDescriptor cc3D_SkinPositionTex_vert = ShaderDescriptor("3D_PositionTex")
.Input("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0)
.Input("COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 12);
const ShaderDescriptor cc3D_ColorTex_frag = ShaderDescriptor("3D_ColorTex");
const ShaderDescriptor cc3D_Color_frag = ShaderDescriptor("3D_Color");

#else
//
#include "ccShader_Position_uColor.frag"
#include "ccShader_Position_uColor.vert"

//
#include "ccShader_PositionColor.frag"
#include "ccShader_PositionColor.vert"

//
#include "ccShader_PositionTexture.frag"
#include "ccShader_PositionTexture.vert"

//
#include "ccShader_PositionTextureA8Color.frag"
#include "ccShader_PositionTextureA8Color.vert"

//
#include "ccShader_PositionTextureColor.frag"
#include "ccShader_PositionTextureColor.vert"

//
#include "ccShader_PositionTextureColor_noMVP.frag"
#include "ccShader_PositionTextureColor_noMVP.vert"

//
#include "ccShader_PositionTextureColorAlphaTest.frag"

//
#include "ccShader_PositionTexture_uColor.frag"
#include "ccShader_PositionTexture_uColor.vert"

#include "ccShader_PositionColorLengthTexture.frag"
#include "ccShader_PositionColorLengthTexture.vert"

//
#include "ccShader_Label.vert"
#include "ccShader_Label_df.frag"
#include "ccShader_Label_df_glow.frag"
#include "ccShader_Label_normal.frag"
#include "ccShader_Label_outline.frag"

//
#include "ccShader_3D_PositionTex.vert"
#include "ccShader_3D_Color.frag"
#include "ccShader_3D_ColorTex.frag"
#endif

NS_CC_END
