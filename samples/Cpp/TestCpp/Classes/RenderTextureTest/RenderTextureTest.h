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

    void restartCallback(Object* pSender);
    void nextCallback(Object* pSender);
    void backCallback(Object* pSender);
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
    cc::SpriteBatchNode *mgr;;

    cc::Sprite *sp1;
    cc::Sprite *sp2;
    cc::Sprite *sp3;
    cc::Sprite *sp4;
    cc::Sprite *sp5;
    cc::Sprite *sp6;
    cc::Sprite *sp7;
    cc::Sprite *sp8;
    cc::Sprite *sp9;
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
    cc::Sprite *sprite1, *sprite2;
    cc::RenderTexture *renderTexture;
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
