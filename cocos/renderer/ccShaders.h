/****************************************************************************
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2012 		cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#ifndef __CCSHADER_H__
#define __CCSHADER_H__
/// @cond DO_NOT_SHOW

#include "platform/CCGL.h"
#include "platform/CCPlatformMacros.h"

/**
 * @addtogroup renderer
 * @{
 */

NS_CC_BEGIN

extern CC_DLL const GLchar * ccPosition_uColor_frag;
extern CC_DLL const GLchar * ccPosition_uColor_vert;

extern CC_DLL const GLchar * ccPositionColor_frag;
extern CC_DLL const GLchar * ccPositionColor_vert;

extern CC_DLL const GLchar * ccPositionColorTextureAsPointsize_vert;

extern CC_DLL const GLchar * ccPositionTexture_frag;
extern CC_DLL const GLchar * ccPositionTexture_vert;

extern CC_DLL const GLchar * ccPositionTextureA8Color_frag;
extern CC_DLL const GLchar * ccPositionTextureA8Color_vert;

extern CC_DLL const GLchar * ccPositionTextureColor_frag;
extern CC_DLL const GLchar * ccPositionTextureColor_vert;

extern CC_DLL const GLchar * ccPositionTextureColor_noMVP_frag;
extern CC_DLL const GLchar * ccPositionTextureColor_noMVP_vert;

extern CC_DLL const GLchar * ccPositionTextureColorAlphaTest_frag;

extern CC_DLL const GLchar * ccPositionTexture_uColor_frag;
extern CC_DLL const GLchar * ccPositionTexture_uColor_vert;

extern CC_DLL const GLchar * ccPositionColorLengthTexture_frag;
extern CC_DLL const GLchar * ccPositionColorLengthTexture_vert;

extern CC_DLL const GLchar * ccPositionTexture_GrayScale_frag;

extern CC_DLL const GLchar * ccLabelDistanceFieldNormal_frag;
extern CC_DLL const GLchar * ccLabelDistanceFieldGlow_frag;
extern CC_DLL const GLchar * ccLabelNormal_frag;
extern CC_DLL const GLchar * ccLabelOutline_frag;

extern CC_DLL const GLchar * ccLabel_vert;

extern CC_DLL const GLchar * cc3D_PositionTex_vert;
extern CC_DLL const GLchar * cc3D_SkinPositionTex_vert;
extern CC_DLL const GLchar * cc3D_ColorTex_frag;
extern CC_DLL const GLchar * cc3D_Color_frag;
extern CC_DLL const GLchar * cc3D_PositionNormalTex_vert;
extern CC_DLL const GLchar * cc3D_SkinPositionNormalTex_vert;
extern CC_DLL const GLchar * cc3D_ColorNormalTex_frag;
extern CC_DLL const GLchar * cc3D_ColorNormal_frag;
extern CC_DLL const GLchar * cc3D_Particle_vert;
extern CC_DLL const GLchar * cc3D_Particle_tex_frag;
extern CC_DLL const GLchar * cc3D_Particle_color_frag;
extern CC_DLL const GLchar * cc3D_Skybox_vert;
extern CC_DLL const GLchar * cc3D_Skybox_frag;
extern CC_DLL const GLchar * cc3D_Terrain_vert;
extern CC_DLL const GLchar * cc3D_Terrain_frag;
extern CC_DLL const GLchar * ccCameraClearVert;
extern CC_DLL const GLchar * ccCameraClearFrag;
// ETC1 ALPHA supports.
extern CC_DLL const GLchar* ccETC1ASPositionTextureColor_frag;
extern CC_DLL const GLchar* ccETC1ASPositionTextureGray_frag;

extern CC_DLL const GLchar* ccPosition_vert;
extern CC_DLL const GLchar* ccShader_LayerRadialGradient_frag;

NS_CC_END
/**
 end of support group
 @}
 */
/// @endcond
#endif /* __CCSHADER_H__ */
