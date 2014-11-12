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

#include "CCBrightnessFilter.h"
#include "filters/nodes/CCFilteredSprite.h"

NS_CC_EXT_BEGIN
//================== BrightnessFilter

BrightnessFilter* BrightnessFilter::create()
{
	BrightnessFilter* __filter = new BrightnessFilter();
	__filter->autorelease();
	return __filter;
}

BrightnessFilter* BrightnessFilter::create(float $brightness)
{
	BrightnessFilter* __filter = BrightnessFilter::create();
	__filter->setParameter($brightness);
	return __filter;
}

BrightnessFilter::BrightnessFilter()
{
	this->shaderName = kCCFilterShader_brightness;
	_param = 0.f;
}

GLProgram* BrightnessFilter::loadShader()
{
    GLProgram* __p = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, ccFilterShader_brightness_frag);
    
//	GLProgram* __p = new GLProgram();
//	__p->initWithByteArrays(ccPositionTexture_vert, ccFilterShader_brightness_frag);
	return __p;
}

void BrightnessFilter::setParameter(float $brightness)
{
	_param = MIN(1.f, MAX($brightness, -1.f));
	initProgram();
}

void BrightnessFilter::setAttributes(GLProgram* $cgp)
{
	//CCLOG("CCRGBFilter::setAttributes");
	$cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	$cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
}

void BrightnessFilter::setUniforms(GLProgram* $cgp)
{
//	int u_brightness = $cgp->getUniformLocationForName("u_brightness");
//	$cgp->setUniformLocationWith1f(u_brightness, _param);
    
    _pProgramState->setUniformFloat("u_brightness", _param);
}
NS_CC_EXT_END