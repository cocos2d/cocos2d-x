/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org

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

#ifndef _SPRITE_TEST_H_
#define _SPRITE_TEST_H_

#include "cocos2d.h"
#include "../testBasic.h"
#include "../BaseTest.h"
#include <string>

class SpriteTestDemo : public BaseTest
{
protected:
    std::string    _title;

public:
    SpriteTestDemo(void);
    virtual ~SpriteTestDemo(void);

    void restartCallback(Ref* sender);
    void nextCallback(Ref* sender);
    void backCallback(Ref* sender);

    // overrides
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void onEnter() override;
};

class Sprite1 : public SpriteTestDemo
{
public:
    CREATE_FUNC(Sprite1);
    Sprite1();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void addNewSpriteWithCoords(Point p);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
};

class SpriteBatchNode1: public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNode1);
    SpriteBatchNode1();
    void addNewSpriteWithCoords(Point p);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteColorOpacity : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteColorOpacity);
    SpriteColorOpacity();
    void removeAndAddSprite(float dt);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

};

class SpriteBatchNodeColorOpacity : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeColorOpacity);

    SpriteBatchNodeColorOpacity();
    void removeAndAddSprite(float dt);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteZOrder : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteZOrder);

    SpriteZOrder();
    void reorderSprite(float dt);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

protected:
    int _dir;
};

class SpriteBatchNodeZOrder: public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeZOrder);

    SpriteBatchNodeZOrder();
    void reorderSprite(float dt);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

protected:
    int _dir;
};

class SpriteBatchNodeReorder : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeReorder);

    SpriteBatchNodeReorder();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteBatchNodeReorderIssue744: public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeReorderIssue744);

    SpriteBatchNodeReorderIssue744();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteBatchNodeReorderIssue766 : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeReorderIssue766);

    SpriteBatchNodeReorderIssue766();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void reorderSprite(float dt);
    Sprite* makeSpriteZ(int aZ);

private:
    SpriteBatchNode *batchNode;
    Sprite *sprite1;
    Sprite *sprite2;
    Sprite *sprite3;    
};

class SpriteBatchNodeReorderIssue767 : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeReorderIssue767);

    SpriteBatchNodeReorderIssue767();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void reorderSprites(float dt);
};

class SpriteZVertex: public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteZVertex);

    virtual void onEnter() override;
    virtual void onExit() override;
    SpriteZVertex();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

protected:
    int _dir;
    float _time;
};

class SpriteBatchNodeZVertex: public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeZVertex);

    virtual void onEnter() override;
    virtual void onExit() override;
    SpriteBatchNodeZVertex();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

protected:
    int _dir;
    float _time;
};

class SpriteAnchorPoint : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteAnchorPoint);

    SpriteAnchorPoint();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteBatchNodeAnchorPoint : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeAnchorPoint);

    SpriteBatchNodeAnchorPoint();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class Sprite6 : public SpriteTestDemo
{
public:
    CREATE_FUNC(Sprite6);

    Sprite6();
    virtual std::string title() const override;
};

class SpriteFlip : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteFlip);

    SpriteFlip();
    void flipSprites(float dt);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteBatchNodeFlip : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeFlip);
    SpriteBatchNodeFlip();
    void flipSprites(float dt);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteAliased : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteAliased);
    SpriteAliased();
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteBatchNodeAliased : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeAliased);
    SpriteBatchNodeAliased();
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteNewTexture : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteNewTexture);
    SpriteNewTexture();
    virtual ~SpriteNewTexture();
    void addNewSprite();
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

protected:
    bool _usingTexture1;
    Texture2D *_texture1;
    Texture2D *_texture2;
};

class SpriteBatchNodeNewTexture : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeNewTexture);
    SpriteBatchNodeNewTexture();
    virtual ~SpriteBatchNodeNewTexture();
    void addNewSprite();
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

protected:
    Texture2D*    _texture1;
    Texture2D*    _texture2;
};

class SpriteFrameTest: public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteFrameTest);
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void startIn05Secs(float dt);
    void flipSprites(float dt);
private:
    
    Sprite *_sprite1;
    Sprite *_sprite2;
    int      _counter;
};

class SpriteFrameAliasNameTest : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteFrameAliasNameTest);

    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteOffsetAnchorRotation: public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteOffsetAnchorRotation);

    SpriteOffsetAnchorRotation();
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteBatchNodeOffsetAnchorRotation: public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeOffsetAnchorRotation);
    SpriteBatchNodeOffsetAnchorRotation();
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteOffsetAnchorScale: public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteOffsetAnchorScale);
    SpriteOffsetAnchorScale();
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteBatchNodeOffsetAnchorScale: public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeOffsetAnchorScale);
    SpriteBatchNodeOffsetAnchorScale();
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteOffsetAnchorSkew : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteOffsetAnchorSkew);
    SpriteOffsetAnchorSkew();
    virtual ~SpriteOffsetAnchorSkew();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteOffsetAnchorRotationalSkew : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteOffsetAnchorRotationalSkew);
    SpriteOffsetAnchorRotationalSkew();
    virtual ~SpriteOffsetAnchorRotationalSkew();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteBatchNodeOffsetAnchorSkew : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeOffsetAnchorSkew);
    SpriteBatchNodeOffsetAnchorSkew();
    virtual ~SpriteBatchNodeOffsetAnchorSkew();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteOffsetAnchorRotationalSkewScale : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteOffsetAnchorRotationalSkewScale);
    SpriteOffsetAnchorRotationalSkewScale();
    virtual ~SpriteOffsetAnchorRotationalSkewScale();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteBatchNodeOffsetAnchorRotationalSkew : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeOffsetAnchorRotationalSkew);
    SpriteBatchNodeOffsetAnchorRotationalSkew();
    virtual ~SpriteBatchNodeOffsetAnchorRotationalSkew();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteOffsetAnchorSkewScale : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteOffsetAnchorSkewScale);
    SpriteOffsetAnchorSkewScale();
    virtual ~SpriteOffsetAnchorSkewScale();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteBatchNodeOffsetAnchorSkewScale : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeOffsetAnchorSkewScale);
    SpriteBatchNodeOffsetAnchorSkewScale();
    virtual ~SpriteBatchNodeOffsetAnchorSkewScale();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteBatchNodeOffsetAnchorRotationalSkewScale : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeOffsetAnchorRotationalSkewScale);
    SpriteBatchNodeOffsetAnchorRotationalSkewScale();
    virtual ~SpriteBatchNodeOffsetAnchorRotationalSkewScale();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteOffsetAnchorFlip : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteOffsetAnchorFlip);
    SpriteOffsetAnchorFlip();
    virtual ~SpriteOffsetAnchorFlip();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteBatchNodeOffsetAnchorFlip : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeOffsetAnchorFlip);
    SpriteBatchNodeOffsetAnchorFlip();
    virtual ~SpriteBatchNodeOffsetAnchorFlip();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteAnimationSplit : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteAnimationSplit);
    SpriteAnimationSplit();
    virtual void onExit() override;
    virtual std::string title() const override;
};

class SpriteHybrid: public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteHybrid);

    SpriteHybrid();
    void reparentSprite(float dt);
    virtual std::string title() const override;
    virtual void onExit() override;

protected:
    bool     _usingSpriteBatchNode;
};

class SpriteBatchNodeChildren: public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeChildren);
    SpriteBatchNodeChildren();
    virtual void onExit() override;
    virtual std::string title() const override;
};

class SpriteBatchNodeChildrenZ : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeChildrenZ);
    SpriteBatchNodeChildrenZ();
    virtual void onExit() override;
    virtual std::string title() const override;
};

class SpriteChildrenVisibility: public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteChildrenVisibility);
    SpriteChildrenVisibility();
    virtual void onExit() override;
    virtual std::string title() const override;
};

class SpriteChildrenVisibilityIssue665 : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteChildrenVisibilityIssue665);
    SpriteChildrenVisibilityIssue665();
    virtual ~SpriteChildrenVisibilityIssue665();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteChildrenAnchorPoint: public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteChildrenAnchorPoint);
    SpriteChildrenAnchorPoint();
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteBatchNodeChildrenAnchorPoint: public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeChildrenAnchorPoint);
    SpriteBatchNodeChildrenAnchorPoint();
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteBatchNodeChildrenScale: public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeChildrenScale);
    SpriteBatchNodeChildrenScale();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteChildrenChildren: public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteChildrenChildren);
    SpriteChildrenChildren();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};


class SpriteBatchNodeChildrenChildren: public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeChildrenChildren);
    SpriteBatchNodeChildrenChildren();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteNilTexture: public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteNilTexture);
    SpriteNilTexture();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteSubclass : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteSubclass);
    SpriteSubclass();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class AnimationCacheTest : public SpriteTestDemo
{
public:
    CREATE_FUNC(AnimationCacheTest);
    AnimationCacheTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class NodeSort : public SpriteTestDemo
{
public:
    CREATE_FUNC(NodeSort);
    NodeSort();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void reorderSprite(float dt);

private:
    Node *_node;
    Sprite *_sprite1;
    Sprite *_sprite2;
    Sprite *_sprite3;
    Sprite *_sprite4;
    Sprite *_sprite5;
};

class SpriteBatchNodeReorderSameIndex : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeReorderSameIndex);
    SpriteBatchNodeReorderSameIndex();
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void reorderSprite(float dt);

private:
    SpriteBatchNode *_batchNode;
    Sprite *_sprite1;
    Sprite *_sprite2;
    Sprite *_sprite3;
    Sprite *_sprite4;
    Sprite *_sprite5;
};

class SpriteBatchNodeReorderOneChild : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeReorderOneChild);
    SpriteBatchNodeReorderOneChild();
    void reorderSprite(float dt);
    virtual std::string title() const override;
private:
    SpriteBatchNode *_batchNode;
    Sprite *_reorderSprite;
};

class SpriteBatchNodeSkewNegativeScaleChildren : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeSkewNegativeScaleChildren);
    SpriteBatchNodeSkewNegativeScaleChildren();
    virtual ~SpriteBatchNodeSkewNegativeScaleChildren();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteBatchNodeRotationalSkewNegativeScaleChildren : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeRotationalSkewNegativeScaleChildren);
    SpriteBatchNodeRotationalSkewNegativeScaleChildren();
    virtual ~SpriteBatchNodeRotationalSkewNegativeScaleChildren();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteSkewNegativeScaleChildren : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteSkewNegativeScaleChildren);
    SpriteSkewNegativeScaleChildren();
    virtual ~SpriteSkewNegativeScaleChildren();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteRotationalSkewNegativeScaleChildren : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteRotationalSkewNegativeScaleChildren);
    SpriteRotationalSkewNegativeScaleChildren();
    virtual ~SpriteRotationalSkewNegativeScaleChildren();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteDoubleResolution : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteDoubleResolution);
    SpriteDoubleResolution();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class AnimationCacheFile : public SpriteTestDemo
{
public:
    CREATE_FUNC(AnimationCacheFile);

    AnimationCacheFile();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteBatchBug1217 : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchBug1217);
    SpriteBatchBug1217();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteCullTest1 : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteCullTest1);
    SpriteCullTest1();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteCullTest2 : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteCullTest2);
    SpriteCullTest2();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
