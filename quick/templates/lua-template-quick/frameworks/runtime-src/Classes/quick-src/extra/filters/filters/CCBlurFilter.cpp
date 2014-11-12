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

#include "CCBlurFilter.h"
#include "filters/nodes/CCFilteredSprite.h"

NS_CC_EXT_BEGIN

//================== BlurBaseFilter

BlurBaseFilter::BlurBaseFilter()
: _param(0.1f)
{
}

void BlurBaseFilter::setAttributes(GLProgram* $cgp)
{
	//CCLOG("BlurBaseFilter::setAttributes");
	$cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	$cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
	$cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
}

void BlurBaseFilter::setUniforms(GLProgram* $cgp)
{
//	int __radius = $cgp->getUniformLocationForName("u_radius");
//	$cgp->setUniformLocationWith1f(__radius, _param);
    
    _pProgramState->setUniformFloat("u_radius", _param);
}

void BlurBaseFilter::setParameter(float $param)
{
	_param = $param;
	//CCLOG("BlurBaseFilter::setParameter %f", _param);
	initProgram();
}

//================== HBlurFilter

HBlurFilter* HBlurFilter::create()
{
	HBlurFilter* __filter = new HBlurFilter();
	__filter->autorelease();
	return __filter;
}

HBlurFilter* HBlurFilter::create(float $param)
{
	HBlurFilter* __filter = HBlurFilter::create();
	__filter->setParameter($param);
	return __filter;
}

HBlurFilter::HBlurFilter()
{
	this->shaderName = kCCFilterShader_hblur;
}

GLProgram* HBlurFilter::loadShader()
{
    GLProgram* __p = GLProgram::createWithByteArrays(ccFilterShader_hblur_vert, ccFilterShader_blur_frag);
//	GLProgram* __p = new GLProgram();
//	__p->initWithByteArrays(ccFilterShader_hblur_vert, ccFilterShader_blur_frag);
	//CCLOG("HBlurFilter::loadShader %f", _param);
	return __p;
}

//================== VBlurFilter

VBlurFilter* VBlurFilter::create()
{
	VBlurFilter* __filter = new VBlurFilter();
	__filter->autorelease();
	return __filter;
}

VBlurFilter* VBlurFilter::create(float $param)
{
	VBlurFilter* __filter = VBlurFilter::create();
	__filter->setParameter($param);
	return __filter;
}

VBlurFilter::VBlurFilter()
{
	this->shaderName = kCCFilterShader_vblur;
}

GLProgram* VBlurFilter::loadShader()
{
    GLProgram* __p = GLProgram::createWithByteArrays(ccFilterShader_vblur_vert, ccFilterShader_blur_frag);
//	GLProgram* __p = new GLProgram();
//	__p->initWithByteArrays(ccFilterShader_vblur_vert, ccFilterShader_blur_frag);

	return __p;
}

//================== GaussianHBlurFilter

GaussianHBlurFilter* GaussianHBlurFilter::create()
{
	GaussianHBlurFilter* __filter = new GaussianHBlurFilter();
	__filter->autorelease();
	return __filter;
}

GaussianHBlurFilter* GaussianHBlurFilter::create(float $param)
{
	GaussianHBlurFilter* __filter = GaussianHBlurFilter::create();
	__filter->setParameter($param);
	return __filter;
}

GaussianHBlurFilter::GaussianHBlurFilter()
: _resolation(800.f)
{
	this->shaderName = kCCFilterShader_gaussian_hblur;
}

GLProgram* GaussianHBlurFilter::loadShader()
{
    GLProgram* __p = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, ccFilterShader_gaussian_hblur_frag);
//	GLProgram* __p = new GLProgram();
//	__p->initWithByteArrays(ccPositionTextureColor_vert,
//		ccFilterShader_gaussian_hblur_frag);
	return __p;
}

void GaussianHBlurFilter::setUniforms(GLProgram* $cgp)
{
	BlurBaseFilter::setUniforms($cgp);

//	int u_resolution = $cgp->getUniformLocationForName("u_resolution");
//	$cgp->setUniformLocationWith1f(u_resolution, _resolation);
    
    _pProgramState->setUniformFloat("u_resolution", _resolation);
}

void GaussianHBlurFilter::initSprite(FilteredSprite* $sprite)
{
	//_resolation = $sprite->getContentSize().width;
	_resolation = 1024;
	//CCLOG("GaussianHBlurFilter.initSprite resulation:%f", _resolation);
    BlurBaseFilter::initSprite(nullptr);
}

//================== GaussianVBlurFilter

GaussianVBlurFilter* GaussianVBlurFilter::create()
{
	GaussianVBlurFilter* __filter = new GaussianVBlurFilter();
	__filter->autorelease();
	return __filter;
}

GaussianVBlurFilter* GaussianVBlurFilter::create(float $param)
{
	GaussianVBlurFilter* __filter = GaussianVBlurFilter::create();
	__filter->setParameter($param);
	return __filter;
}

GaussianVBlurFilter::GaussianVBlurFilter()
: _resolation(800.f)
{
	this->shaderName = kCCFilterShader_gaussian_vblur;
}

GLProgram* GaussianVBlurFilter::loadShader()
{
    GLProgram* __p = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, ccFilterShader_gaussian_vblur_frag);
//	GLProgram* __p = new GLProgram();
//	__p->initWithByteArrays(ccPositionTextureColor_vert,
//		ccFilterShader_gaussian_vblur_frag);
	return __p;
}

void GaussianVBlurFilter::setUniforms(GLProgram* $cgp)
{
	BlurBaseFilter::setUniforms($cgp);

//	int u_resolution = $cgp->getUniformLocationForName("u_resolution");
//	$cgp->setUniformLocationWith1f(u_resolution, _resolation);
    
    _pProgramState->setUniformFloat("u_resolution", _resolation);
}

void GaussianVBlurFilter::initSprite(FilteredSprite* $sprite)
{
	//_resolation = $sprite->getContentSize().height;
	_resolation = 1024;
	//CCLOG("GaussianVBlurFilter.initSprite resulation:%f", _resolation);
    BlurBaseFilter::initSprite(nullptr);
}

//================== ZoomBlurFilter

ZoomBlurFilter* ZoomBlurFilter::create()
{
	ZoomBlurFilter* __filter = new ZoomBlurFilter();
	__filter->autorelease();
	return __filter;
}

ZoomBlurFilter* ZoomBlurFilter::create(float $blurSize, float $centerX, float $centerY)
{
	ZoomBlurFilter* __filter = ZoomBlurFilter::create();
	__filter->setParameter($blurSize, $centerX, $centerY);
	return __filter;
}

ZoomBlurFilter::ZoomBlurFilter()
: _blurSize(1.f)
, _centerX(0.5f)
, _centerY(0.5f)
{
	this->shaderName = kCCFilterShader_zoom_blur;
}

GLProgram* ZoomBlurFilter::loadShader()
{
    GLProgram* __p = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, ccFilterShader_zoom_blur_frag);
    
//	GLProgram* __p = new GLProgram();
//	__p->initWithByteArrays(ccPositionTexture_vert, ccFilterShader_zoom_blur_frag);
	return __p;
}

void ZoomBlurFilter::setParameter(float $blurSize, float $centerX, float $centerY)
{
	_blurSize = $blurSize < 0 ? 0.f : $blurSize;
	//_blurSize = MIN(10.f, MAX($blurSize, 0.f));
	//_centerX = MIN(1.f, MAX($centerX, 0.f));
	//_centerY = MIN(1.f, MAX($centerY, 0.f));
	_blurSize = $blurSize;
	_centerX = $centerX;
	_centerY = $centerY;
	initProgram();
}

void ZoomBlurFilter::setAttributes(GLProgram* $cgp)
{
	//CCLOG("ZoomBlurFilter::setAttributes");
	$cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	$cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
}

void ZoomBlurFilter::setUniforms(GLProgram* $cgp)
{
//	int __blurSize = $cgp->getUniformLocationForName("u_blurSize");
//	int __blurCenter = $cgp->getUniformLocationForName("u_blurCenter");
//	$cgp->setUniformLocationWith1f(__blurSize, _blurSize);
//	$cgp->setUniformLocationWith2f(__blurCenter, _centerX, _centerY);
    
    _pProgramState->setUniformFloat("u_blurSize", _blurSize);
    _pProgramState->setUniformVec2("u_blurCenter", Vec2(_centerX, _centerY));
}

//================== MotionBlurFilter

MotionBlurFilter* MotionBlurFilter::create()
{
	MotionBlurFilter* __filter = new MotionBlurFilter();
	__filter->autorelease();
	return __filter;
}

MotionBlurFilter* MotionBlurFilter::create(float $blurSize, float $blurAngle)
{
	MotionBlurFilter* __filter = MotionBlurFilter::create();
	__filter->setParameter($blurSize, $blurAngle);
	return __filter;
}

MotionBlurFilter::MotionBlurFilter()
: _blurSize(1.f)
, _blurAngle(0.f)
, _texelOffsetX(0.f)
, _texelOffsetY(0.f)
{
	this->shaderName = kCCFilterShader_motion_blur;
}

GLProgram* MotionBlurFilter::loadShader()
{
    GLProgram* __p = GLProgram::createWithByteArrays(ccFilterShader_motion_blur_vert, ccFilterShader_motion_blur_frag);
    
//	GLProgram* __p = new GLProgram();
//	__p->initWithByteArrays(ccFilterShader_motion_blur_vert, ccFilterShader_motion_blur_frag);
	return __p;
}

void MotionBlurFilter::setParameter(float $blurSize, float $blurAngle)
{
	_blurSize = $blurSize < 0 ? 0.f : $blurSize;
	_blurAngle = $blurAngle;
	//The initProgram() will perform in initSprite()
}

void MotionBlurFilter::initSprite(FilteredSprite* $sprite)
{
	float __aspectRatio = 1.0f;
	Size __size = $sprite->getContentSize();
	__aspectRatio = __size.height / __size.width;
	_texelOffsetX = _blurSize*cos(_blurAngle*M_PI / 180.0f) / __size.width;
	_texelOffsetY = _blurSize*sin(_blurAngle*M_PI / 180.0f) / __size.width;
	initProgram();
    
    Filter::initSprite(nullptr);
}

void MotionBlurFilter::setAttributes(GLProgram* $cgp)
{
	//CCLOG("MotionBlurFilter::setAttributes");
	$cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	$cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
}

void MotionBlurFilter::setUniforms(GLProgram* $cgp)
{
//	int __directionalTexelStep = $cgp->getUniformLocationForName("u_directionalTexelStep");
//	$cgp->setUniformLocationWith2f(__directionalTexelStep, _texelOffsetX, _texelOffsetY);
    
    _pProgramState->setUniformVec2("u_directionalTexelStep", Vec2(_texelOffsetX, _texelOffsetY));
}

NS_CC_EXT_END