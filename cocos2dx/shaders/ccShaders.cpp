/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.

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

#include "ccShaders.h"

NS_CC_BEGIN
//
const GLchar * ccPosition_uColor_frag = 
#include "ccShader_Position_uColor_frag.h"
const GLchar * ccPosition_uColor_vert =
#include "ccShader_Position_uColor_vert.h"

//
const GLchar * ccPositionColor_frag =
#include "ccShader_PositionColor_frag.h"
const GLchar * ccPositionColor_vert =
#include "ccShader_PositionColor_vert.h"

//
const GLchar * ccPositionTexture_frag =
#include "ccShader_PositionTexture_frag.h"
const GLchar * ccPositionTexture_vert =
#include "ccShader_PositionTexture_vert.h"

//
const GLchar * ccPositionTextureA8Color_frag =
#include "ccShader_PositionTextureA8Color_frag.h"
const GLchar * ccPositionTextureA8Color_vert =
#include "ccShader_PositionTextureA8Color_vert.h"

//
const GLchar * ccPositionTextureColor_frag =
#include "ccShader_PositionTextureColor_frag.h"
const GLchar * ccPositionTextureColor_vert =
#include "ccShader_PositionTextureColor_vert.h"

//
const GLchar * ccPositionTextureColorAlphaTest_frag = 
#include "ccShader_PositionTextureColorAlphaTest_frag.h"

//
const GLchar * ccPositionTexture_uColor_frag = 
#include "ccShader_PositionTexture_uColor_frag.h"
const GLchar * ccPositionTexture_uColor_vert = 
#include "ccShader_PositionTexture_uColor_vert.h"

const GLchar * ccExSwitchMask_frag = 
#include "ccShaderEx_SwitchMask_frag.h"

const GLchar * ccPositionColorLengthTexture_frag =
#include "ccShader_PositionColorLengthTexture_frag.h"
const GLchar * ccPositionColorLengthTexture_vert =
#include "ccShader_PositionColorLengthTexture_vert.h"

NS_CC_END
