#ifndef _RENDERTEXTURE_TEST_H_
#define _RENDERTEXTURE_TEST_H_

#include "cocos2d.h"
#include "../testBasic.h"
#include "../BaseTest.h"
#include "renderer/CCCustomCommand.h"

class RenderTextureTest : public BaseTest
{
public:
    virtual void onEnter();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void restartCallback(Object* sender);
    void nextCallback(Object* sender);
    void backCallback(Object* sender);
};

class RenderTextureSave : public RenderTextureTest
{
public:
    CREATE_FUNC(RenderTextureSave);
    RenderTextureSave();
    ~RenderTextureSave();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void onTouchesMoved(const std::vector<Touch*>& touches, Event* event);
    void clearImage(Object *pSender);
    void saveImage(Object *pSender);

private:
    RenderTexture *_target;
    Vector<Sprite*> _brushs;
};

class RenderTextureIssue937 : public RenderTextureTest
{
public:
    CREATE_FUNC(RenderTextureIssue937);
    RenderTextureIssue937();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class RenderTextureScene : public TestScene
{
public:
    virtual void runThisTest();
};

class RenderTextureZbuffer : public RenderTextureTest
{
public:
    CREATE_FUNC(RenderTextureZbuffer);
    RenderTextureZbuffer();

    void onTouchesMoved(const std::vector<Touch*>& touches, Event* event);
    void onTouchesBegan(const std::vector<Touch*>& touches, Event* event);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

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
    CREATE_FUNC(RenderTextureTestDepthStencil);
    RenderTextureTestDepthStencil();
    virtual ~RenderTextureTestDepthStencil();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void draw() override;
private:
    CustomCommand _renderCmds[4];
    void onBeforeClear();
    void onBeforeStencil();
    void onBeforDraw();
    void onAfterDraw();
    
private:
    RenderTexture* _rend;
    Sprite* _spriteDS;
    Sprite* _spriteDraw;
};

class RenderTextureTargetNode : public RenderTextureTest
{
private:
    cocos2d::Sprite *sprite1, *sprite2;
    cocos2d::RenderTexture *renderTexture;
public:
    CREATE_FUNC(RenderTextureTargetNode);
    RenderTextureTargetNode();
    
    virtual void update(float t);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    void touched(Object* sender);
};

class SpriteRenderTextureBug : public RenderTextureTest
{
public:
    
    class SimpleSprite : public Sprite
    {
    public:
        static SimpleSprite* create(const char* filename, const Rect &rect);
        SimpleSprite();
        virtual void draw();
        
    protected:
        void onBeforeDraw();
    public:
        RenderTexture *_rt;
    protected:
        CustomCommand _customCommand;
    };
        
public:
    CREATE_FUNC(SpriteRenderTextureBug);
    SpriteRenderTextureBug();
    
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    SimpleSprite* addNewSpriteWithCoords(const Point& p);
};

#endif
