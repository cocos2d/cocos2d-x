#ifndef _RENDERTEXTURE_TEST_H_
#define _RENDERTEXTURE_TEST_H_

#include "cocos2d.h"
#include "../testBasic.h"

class RenderTextureTest : public CCLayer
{
public:
	RenderTextureTest();
	~RenderTextureTest();
	virtual void ccTouchesMoved(NSSet* touches, UIEvent* event);

private:
    CCRenderTexture*	m_target;
    CCSprite*			m_brush;
};

class RenderTextureScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
