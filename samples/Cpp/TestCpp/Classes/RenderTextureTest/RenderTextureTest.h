#ifndef _RENDERTEXTURE_TEST_H_
#define _RENDERTEXTURE_TEST_H_

#include "cocos2d.h"
#include "../testBasic.h"

class RenderTextureTest : public CCLayer
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();

    void restartCallback(CCObject* pSender);
    void nextCallback(CCObject* pSender);
    void backCallback(CCObject* pSender);
};

class RenderTextureSave : public RenderTextureTest
{
public:
    RenderTextureSave();
    ~RenderTextureSave();
    virtual std::string title();
    virtual std::string subtitle();
    virtual void ccTouchesMoved(CCSet* touches, CCEvent* event);
    void clearImage(CCObject *pSender);
    void saveImage(CCObject *pSender);

private:
    CCRenderTexture *m_pTarget;
    CCSprite *m_pBrush;
};

class RenderTextureIssue937 : public RenderTextureTest
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

class RenderTextureZbuffer : public RenderTextureTest
{
public:
    RenderTextureZbuffer();

    virtual void ccTouchesMoved(CCSet* touches, CCEvent* event);
    virtual void ccTouchesBegan(CCSet* touches, CCEvent* event);
    virtual void ccTouchesEnded(CCSet* touches, CCEvent* event);
    virtual std::string title();
    virtual std::string subtitle();

    void renderScreenShot();

private:
    cocos2d::CCSpriteBatchNode *mgr;;

    cocos2d::CCSprite *sp1;
    cocos2d::CCSprite *sp2;
    cocos2d::CCSprite *sp3;
    cocos2d::CCSprite *sp4;
    cocos2d::CCSprite *sp5;
    cocos2d::CCSprite *sp6;
    cocos2d::CCSprite *sp7;
    cocos2d::CCSprite *sp8;
    cocos2d::CCSprite *sp9;
};

class RenderTextureTestDepthStencil : public RenderTextureTest
{
public:
    RenderTextureTestDepthStencil();
    virtual std::string title();
    virtual std::string subtitle();
};

class RenderTextureTargetNode : public RenderTextureTest
{
private:
    cocos2d::CCSprite *sprite1, *sprite2;
    cocos2d::CCRenderTexture *renderTexture;
public:
    RenderTextureTargetNode();
    
    virtual void update(float t);
    virtual std::string title();
    virtual std::string subtitle();
    
    void touched(CCObject* sender);
};

class SpriteRenderTextureBug : public RenderTextureTest
{
public:
    
class SimpleSprite : public CCSprite
{
    public:
        SimpleSprite();
        virtual void draw();
        
        static SimpleSprite* create(const char* filename, const CCRect &rect);
        
    public:
        CCRenderTexture *rt;
};
        
public:
    SpriteRenderTextureBug();
    
    virtual void ccTouchesEnded(CCSet* touches, CCEvent* event);
    virtual std::string title();
    virtual std::string subtitle();
    
    SimpleSprite* addNewSpriteWithCoords(const CCPoint& p);
};

#endif
