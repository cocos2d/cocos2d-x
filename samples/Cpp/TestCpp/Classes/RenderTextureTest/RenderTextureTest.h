#ifndef _RENDERTEXTURE_TEST_H_
#define _RENDERTEXTURE_TEST_H_

#include "cocos2d.h"
#include "../testBasic.h"
#include "../BaseTest.h"

class RenderTextureTest : public BaseTest
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();

    void restartCallback(Object* sender);
    void nextCallback(Object* sender);
    void backCallback(Object* sender);
};

class RenderTextureSave : public RenderTextureTest
{
public:
    RenderTextureSave();
    ~RenderTextureSave();
    virtual std::string title();
    virtual std::string subtitle();
    virtual void ccTouchesMoved(Set* touches, Event* event);
    void clearImage(Object *pSender);
    void saveImage(Object *pSender);

private:
    RenderTexture *_target;
    Sprite *_brush;
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

    virtual void ccTouchesMoved(Set* touches, Event* event);
    virtual void ccTouchesBegan(Set* touches, Event* event);
    virtual void ccTouchesEnded(Set* touches, Event* event);
    virtual std::string title();
    virtual std::string subtitle();

    void renderScreenShot();

private:
    cocos2d::SpriteBatchNode *mgr;;

    cocos2d::Sprite *sp1;
    cocos2d::Sprite *sp2;
    cocos2d::Sprite *sp3;
    cocos2d::Sprite *sp4;
    cocos2d::Sprite *sp5;
    cocos2d::Sprite *sp6;
    cocos2d::Sprite *sp7;
    cocos2d::Sprite *sp8;
    cocos2d::Sprite *sp9;
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
    cocos2d::Sprite *sprite1, *sprite2;
    cocos2d::RenderTexture *renderTexture;
public:
    RenderTextureTargetNode();
    
    virtual void update(float t);
    virtual std::string title();
    virtual std::string subtitle();
    
    void touched(Object* sender);
};

class SpriteRenderTextureBug : public RenderTextureTest
{
public:
    
class SimpleSprite : public Sprite
{
    public:
        SimpleSprite();
        virtual void draw();
        
        static SimpleSprite* create(const char* filename, const Rect &rect);
        
    public:
        RenderTexture *rt;
};
        
public:
    SpriteRenderTextureBug();
    
    virtual void ccTouchesEnded(Set* touches, Event* event);
    virtual std::string title();
    virtual std::string subtitle();
    
    SimpleSprite* addNewSpriteWithCoords(const Point& p);
};

#endif
