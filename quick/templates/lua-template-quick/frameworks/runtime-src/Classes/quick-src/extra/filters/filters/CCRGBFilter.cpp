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

#include "CCRGBFilter.h"
#include "filters/nodes/CCFilteredSprite.h"

NS_CC_EXT_BEGIN

//================== RGBFilter

RGBFilter* RGBFilter::create()
{
	RGBFilter* __filter = new RGBFilter();
	__filter->autorelease();
	return __filter;
}

RGBFilter* RGBFilter::create(float $readAdj, float $greenAdj, float $blueAdj)
{
	RGBFilter* __filter = RGBFilter::create();
	__filter->setParameter($readAdj, $greenAdj, $blueAdj);
	return __filter;
}

RGBFilter::RGBFilter()
: _redAdj(1.f)
, _greenAdj(1.f)
, _blueAdj(1.f)
{
	this->shaderName = kCCFilterShader_rgb;
}

GLProgram* RGBFilter::loadShader()
{
    GLProgram* __p = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, ccFilterShader_rgb_frag);
    
//	GLProgram* __p = new GLProgram();
//	__p->initWithByteArrays(ccPositionTexture_vert, ccFilterShader_rgb_frag);
	return __p;
}

void RGBFilter::setParameter(float $redAdj, float $greenAdj, float $blueAdj)
{
	_redAdj = $redAdj;
	_greenAdj = $greenAdj;
	_blueAdj = $blueAdj;
	initProgram();
}

void RGBFilter::setAttributes(GLProgram* $cgp)
{
	//CCLOG("RGBFilter::setAttributes");
	$cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	$cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
}

void RGBFilter::setUniforms(GLProgram* $cgp)
{
//	int __redAdj = $cgp->getUniformLocationForName("u_redAdj");
//	int __greenAdj = $cgp->getUniformLocationForName("u_greenAdj");
//	int __blueAdj = $cgp->getUniformLocationForName("u_blueAdj");
//	$cgp->setUniformLocationWith1f(__redAdj, _redAdj);
//	$cgp->setUniformLocationWith1f(__greenAdj, _greenAdj);
//	$cgp->setUniformLocationWith1f(__blueAdj, _blueAdj);
    
    _pProgramState->setUniformFloat("u_redAdj", _redAdj);
    _pProgramState->setUniformFloat("u_greenAdj", _greenAdj);
    _pProgramState->setUniformFloat("u_blueAdj", _blueAdj);
}

NS_CC_EXT_END