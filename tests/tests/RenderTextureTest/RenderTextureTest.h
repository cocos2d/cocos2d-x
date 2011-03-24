#ifndef _RENDERTEXTURE_TEST_H_
#define _RENDERTEXTURE_TEST_H_

#include "cocos2d.h"
#include "../testBasic.h"

class RenderTextureTestDemo : public CCLayer
{
public:
	virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();

    void restartCallback(CCObject* pSender);
    void nextCallback(CCObject* pSender);
    void backCallback(CCObject* pSender);
};

/**
@todo refactor the save image feature
*/
class RenderTextureTest : public RenderTextureTestDemo
{
public:
    RenderTextureTest();
    ~RenderTextureTest();
    virtual void ccTouchesMoved(CCSet* touches, CCEvent* event);

private:
    CCRenderTexture*	m_target;
    CCSprite*			m_brush;
};

class RenderTextureIssue937 : public RenderTextureTestDemo
{
public:
    RenderTextureIssue937();
    virtual std::string title();
    virtual std::string subtitle();
};

class RenderTextureScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
