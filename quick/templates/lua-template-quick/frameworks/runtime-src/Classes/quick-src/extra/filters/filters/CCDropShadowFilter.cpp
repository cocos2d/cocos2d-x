/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2014      Jacky Tsang (zengrong.net)

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

#include "CCDropShadowFilter.h"
#include "filters/nodes/CCFilteredSprite.h"

NS_CC_EXT_BEGIN

//================== DropShadowFilter

DropShadowFilter* DropShadowFilter::create()
{
	DropShadowFilter* __filter = new DropShadowFilter();
	__filter->autorelease();
	return __filter;
}

DropShadowFilter* DropShadowFilter::create(float $resolation)
{
	DropShadowFilter* __filter = DropShadowFilter::create();
	__filter->setParameter($resolation);
	return __filter;
}

DropShadowFilter::DropShadowFilter()
{
	this->shaderName = kCCFilterShader_drop_shadow;
}

GLProgram* DropShadowFilter::loadShader()
{
    GLProgram* __p = GLProgram::createWithByteArrays(ccFilterShader_drop_shadow_vert, ccFilterShader_drop_shadow_frag);
    
//	GLProgram* __p = new GLProgram();
//	__p->initWithByteArrays(ccFilterShader_drop_shadow_vert, 
//		ccFilterShader_drop_shadow_frag);
	return __p;
}

void DropShadowFilter::setParameter(float $resolation)
{
	//The initProgram() will perform in initSprite()
}

void DropShadowFilter::initSprite(FilteredSprite* $sprite)
{
	float __aspectRatio = 1.0f;
	Size __size = $sprite->getContentSize();
	/*_textureWidth = __size.width;
	_textureHeight = __size.height;*/
	_textureWidth = 480;
	_textureHeight = 320;
	initProgram();
}

void DropShadowFilter::setAttributes(GLProgram* $cgp)
{
	//CCLOG("DropShadowFilter::setAttributes");
	$cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	$cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
	$cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
}

void DropShadowFilter::setUniforms(GLProgram* $cgp)
{
//	int u_resolution = $cgp->getUniformLocationForName("u_resolution");
//	$cgp->setUniformLocationWith2f(u_resolution, _textureWidth, _textureHeight);
    
    _pProgramState->setUniformVec2("u_resolution", Vec2(_textureWidth, _textureHeight));
}

NS_CC_EXT_END
