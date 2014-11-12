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

#include "CCMaskFilter.h"
#include "filters/nodes/CCFilteredSprite.h"

NS_CC_EXT_BEGIN

//================== MaskFilter

MaskFilter* MaskFilter::create()
{
	MaskFilter* __filter = new MaskFilter();
	__filter->autorelease();
	return __filter;
}

MaskFilter* MaskFilter::create(std::string* $maskImage)
{
	MaskFilter* __filter = MaskFilter::create();
	__filter->setParameter($maskImage);
	__filter->setIsSpriteFrame(false);
	return __filter;
}

MaskFilter* MaskFilter::createWithSpriteFrameName(std::string* $maskImage)
{
	MaskFilter* __filter = MaskFilter::create();
	__filter->setParameter($maskImage);
	__filter->setIsSpriteFrame(true);
	return __filter;
}

MaskFilter::MaskFilter()
: _param(NULL)
, _isSpriteFrame(false)
{
	this->shaderName = NULL;
}

void MaskFilter::initProgram()
{
	//Do nothing in MaskFilter
	//CCLOG("MaskFilter initProgram");
}

void MaskFilter::initSprite(FilteredSprite* $sprite)
{
	//CCLOG("MaskFilter initSprite maskImage:%s", _param->c_str());
	BlendFunc __maskBF = { GL_ONE, GL_ZERO };
	BlendFunc __imgBF = { GL_DST_ALPHA, GL_ZERO };

	Sprite* __pMask = _isSpriteFrame ?
		Sprite::create(_param->c_str()):
		Sprite::createWithSpriteFrameName(_param->c_str());
	__pMask->setAnchorPoint(Vec2(0, 0));
	__pMask->setPosition(Vec2(0, 0));

	Sprite* __pImg = Sprite::createWithSpriteFrameName("helloworld.png");
	__pImg->setAnchorPoint(Vec2(0, 0));
	__pImg->setPosition(Vec2(0, 0));

	__pMask->setBlendFunc(__maskBF);
	__pImg->setBlendFunc(__imgBF);

	Size __size = __pImg->getContentSize();
	RenderTexture* __pRender = RenderTexture::create(__size.width, __size.height);
	__pRender->begin();
	__pMask->visit();
	__pImg->visit();
	__pRender->end();

	Texture2D* __pTex = new Texture2D();
	__pTex->initWithImage(__pRender->newImage(true));
	__pTex->autorelease();
	$sprite->setTexture(__pTex);
}

void MaskFilter::setParameter(std::string* $maskImage)
{
	_param = $maskImage;
}

NS_CC_EXT_END