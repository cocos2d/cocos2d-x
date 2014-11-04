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

#include "CCGrayFilter.h"

NS_CC_EXT_BEGIN

//================== GrayFilter

GrayFilter* GrayFilter::create()
{
	GrayFilter* __filter = new GrayFilter();
	__filter->autorelease();
	__filter->initProgram();
	return __filter;
}

GrayFilter* GrayFilter::create(Color4F $param)
{
	GrayFilter* __filter = GrayFilter::create();
	__filter->setParameter($param);
	return __filter;
}

GrayFilter* GrayFilter::create(float $r, float $g, float $b, float $a)
{
	GrayFilter* __filter = GrayFilter::create();
	__filter->setParameter($r, $a, $b, $a);
	return __filter;
}


GrayFilter::GrayFilter()
: _param(Color4F(0.299f, 0.587f, 0.114f, 0.0f))
{
	this->shaderName = kCCFilterShader_gray;
}

void GrayFilter::setParameter(Color4F $param)
{
	_param = $param;
	initProgram();
}

void GrayFilter::setParameter(float $r, float $g, float $b, float $a)
{
	setParameter(Color4F($r, $g, $b, $a));
}

GLProgram* GrayFilter::loadShader()
{
    GLProgram* __p = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, ccFilterShader_gray_frag);
//	GLProgram* __p = new GLProgram();
//	__p->initWithByteArrays(ccPositionTextureColor_noMVP_vert, ccFilterShader_gray_frag);
	return __p;
}

void GrayFilter::setAttributes(GLProgram* $cgp)
{
	$cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	$cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	$cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
}

void GrayFilter::setUniforms(GLProgram* $cgp)
{
	//int __grayParam = $cgp->getUniformLocationForName("u_grayParam");
	//CCLOG("GrayFilter::setUniforms, u_grayParam:%d", __grayParam);
	//$cgp->setUniformLocationWith4f(__grayParam, _param.r, _param.g, _param.b, _param.a);
    _pProgramState->setUniformVec4("u_grayParam", Vec4(_param.r, _param.g, _param.b, _param.a));
}

NS_CC_EXT_END