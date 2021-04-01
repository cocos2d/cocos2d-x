/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#ifndef _RENDERTEXTURE_TEST_H_
#define _RENDERTEXTURE_TEST_H_

#include "cocos2d.h"
#include "../BaseTest.h"

DEFINE_TEST_SUITE(RenderTextureTests);

class RenderTextureTest : public TestCase
{
};

class RenderTextureSave : public RenderTextureTest
{
public:
    CREATE_FUNC(RenderTextureSave);
    RenderTextureSave();
    ~RenderTextureSave();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void clearImage(cocos2d::Ref* pSender);
    void clearImageTransparent(cocos2d::Ref* sender);
    void saveImageWithPremultipliedAlpha(cocos2d::Ref* pSender);
    void saveImageWithNonPremultipliedAlpha(cocos2d::Ref* pSender);
    void addImage(cocos2d::Ref* sender);

private:
    cocos2d::RenderTexture* _target;
    cocos2d::Vector<cocos2d::Sprite*> _brushs;
};

class RenderTextureIssue937 : public RenderTextureTest
{
public:
    CREATE_FUNC(RenderTextureIssue937);
    RenderTextureIssue937();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class RenderTextureZbuffer : public RenderTextureTest
{
public:
    CREATE_FUNC(RenderTextureZbuffer);
    RenderTextureZbuffer();

    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void renderScreenShot();

private:
    cocos2d::SpriteBatchNode *mgr;

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
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
private:
    cocos2d::CallbackCommand _renderCmds[4];
    void onBeforeClear();
    void onBeforeStencil();
    void onBeforeDraw();
    void onAfterDraw();
    
private:
    cocos2d::RenderTexture* _rend;
    cocos2d::Sprite* _spriteDS;
    cocos2d::Sprite* _spriteDraw;
};

class RenderTextureTargetNode : public RenderTextureTest
{
private:
    cocos2d::Sprite *sprite1, *sprite2;
    cocos2d::RenderTexture *renderTexture;
public:
    CREATE_FUNC(RenderTextureTargetNode);
    RenderTextureTargetNode();
    
    virtual void update(float t)override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    void touched(cocos2d::Ref* sender);
};

class RenderTexturePartTest : public RenderTextureTest
{
public:
    CREATE_FUNC(RenderTexturePartTest);
    RenderTexturePartTest();
    virtual ~RenderTexturePartTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
private:
    cocos2d::RenderTexture* _rend;
    cocos2d::Sprite* _spriteDraw;
};

class SpriteRenderTextureBug : public RenderTextureTest
{
public:
    
    class SimpleSprite : public cocos2d::Sprite
    {
    public:
        static SimpleSprite* create(const char* filename, const cocos2d::Rect &rect);
        SimpleSprite();
        ~SimpleSprite();
        virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags);
    public:
        cocos2d::RenderTexture* _rt;
    };
        
public:
    CREATE_FUNC(SpriteRenderTextureBug);
    SpriteRenderTextureBug();
    
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    SimpleSprite* addNewSpriteWithCoords(const cocos2d::Vec2& p);
};

class Issue16113Test : public RenderTextureTest
{
public:
    CREATE_FUNC(Issue16113Test);
    Issue16113Test();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class RenderTextureWithSprite3DIssue16894 : public RenderTextureTest
{
public:
    CREATE_FUNC(RenderTextureWithSprite3DIssue16894);
    RenderTextureWithSprite3DIssue16894();
    virtual ~RenderTextureWithSprite3DIssue16894();

    virtual void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags) override;

    virtual std::string title() const override;
    virtual std::string subtitle() const override;

private:
    cocos2d::Sprite3D* _ship[3];

    cocos2d::RenderTexture* _renderTexDefault;
    cocos2d::RenderTexture* _renderTexWithBuffer;
};

#endif
