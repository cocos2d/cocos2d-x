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
    ~SpriteTestDemo(void);

    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();

    void restartCallback(Object* sender);
    void nextCallback(Object* sender);
    void backCallback(Object* sender);
};

class Sprite1 : public SpriteTestDemo
{
public:
    CREATE_FUNC(Sprite1);
    Sprite1();
    virtual std::string title();

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
    virtual std::string title();
};

class SpriteColorOpacity : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteColorOpacity);
    SpriteColorOpacity();
    void removeAndAddSprite(float dt);
    virtual std::string title();
};

class SpriteBatchNodeColorOpacity : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeColorOpacity);

    SpriteBatchNodeColorOpacity();
    void removeAndAddSprite(float dt);
    virtual std::string title();
};

class SpriteZOrder : public SpriteTestDemo
{
    int        _dir;
public:
    CREATE_FUNC(SpriteZOrder);

    SpriteZOrder();
    void reorderSprite(float dt);
    virtual std::string title();
};

class SpriteBatchNodeZOrder: public SpriteTestDemo
{
    int        _dir;
public:
    CREATE_FUNC(SpriteBatchNodeZOrder);

    SpriteBatchNodeZOrder();
    void reorderSprite(float dt);
    virtual std::string title();
};

class SpriteBatchNodeReorder : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeReorder);

    SpriteBatchNodeReorder();
    virtual std::string title();
    std::string subtitle();
};

class SpriteBatchNodeReorderIssue744: public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeReorderIssue744);

    SpriteBatchNodeReorderIssue744();
    virtual std::string title();
    std::string subtitle();
};

class SpriteBatchNodeReorderIssue766 : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeReorderIssue766);

    SpriteBatchNodeReorderIssue766();
    virtual std::string title();
    virtual std::string subtitle();
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
    virtual std::string title();
    virtual std::string subtitle();
    void reorderSprites(float dt);
};

class SpriteZVertex: public SpriteTestDemo
{
    int        _dir;
    float    _time;
public:
    CREATE_FUNC(SpriteZVertex);

    virtual void onEnter();
    virtual void onExit();
    SpriteZVertex();
    virtual std::string title();
};

class SpriteBatchNodeZVertex: public SpriteTestDemo
{
    int        _dir;
    float    _time;
public:
    CREATE_FUNC(SpriteBatchNodeZVertex);

    virtual void onEnter();
    virtual void onExit();
    SpriteBatchNodeZVertex();
    virtual std::string title();
};

class SpriteAnchorPoint : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteAnchorPoint);

    SpriteAnchorPoint();
    virtual std::string title();
};

class SpriteBatchNodeAnchorPoint : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeAnchorPoint);

    SpriteBatchNodeAnchorPoint();
    virtual std::string title();
};

class Sprite6 : public SpriteTestDemo
{
public:
    CREATE_FUNC(Sprite6);

    Sprite6();
    virtual std::string title();
};

class SpriteFlip : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteFlip);

    SpriteFlip();
    void flipSprites(float dt);
    virtual std::string title();
};

class SpriteBatchNodeFlip : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeFlip);
    SpriteBatchNodeFlip();
    void flipSprites(float dt);
    virtual std::string title();
};

class SpriteAliased : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteAliased);
    SpriteAliased();
    virtual void onEnter();
    virtual void onExit();
    virtual std::string title();
};

class SpriteBatchNodeAliased : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeAliased);
    SpriteBatchNodeAliased();
    virtual void onEnter();
    virtual void onExit();
    virtual std::string title();
};

class SpriteNewTexture : public SpriteTestDemo
{
    bool                        _usingTexture1;
    Texture2D*    _texture1;
    Texture2D*    _texture2; 

public:
    CREATE_FUNC(SpriteNewTexture);
    SpriteNewTexture();
    virtual ~SpriteNewTexture();
    void addNewSprite();
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
    virtual std::string title();
};

class SpriteBatchNodeNewTexture : public SpriteTestDemo
{
    Texture2D*    _texture1;
    Texture2D*    _texture2; 

public:
    CREATE_FUNC(SpriteBatchNodeNewTexture);
    SpriteBatchNodeNewTexture();
    virtual ~SpriteBatchNodeNewTexture();
    void addNewSprite();
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
    virtual std::string title();
};

class SpriteFrameTest: public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteFrameTest);
    virtual void onEnter();
    virtual void onExit();
    virtual std::string title();
    virtual std::string subtitle();

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

    virtual void onEnter();
    virtual void onExit();
    virtual std::string title();
    virtual std::string subtitle();
};

class SpriteOffsetAnchorRotation: public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteOffsetAnchorRotation);

    SpriteOffsetAnchorRotation();
    virtual void onExit();
    virtual std::string title();
};

class SpriteBatchNodeOffsetAnchorRotation: public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeOffsetAnchorRotation);
    SpriteBatchNodeOffsetAnchorRotation();
    virtual void onExit();
    virtual std::string title();
};

class SpriteOffsetAnchorScale: public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteOffsetAnchorScale);
    SpriteOffsetAnchorScale();
    virtual void onExit();
    virtual std::string title();
};

class SpriteBatchNodeOffsetAnchorScale: public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeOffsetAnchorScale);
    SpriteBatchNodeOffsetAnchorScale();
    virtual void onExit();
    virtual std::string title();
};

class SpriteOffsetAnchorSkew : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteOffsetAnchorSkew);
    SpriteOffsetAnchorSkew();
    ~SpriteOffsetAnchorSkew();
    virtual std::string title();
};

class SpriteOffsetAnchorRotationalSkew : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteOffsetAnchorRotationalSkew);
    SpriteOffsetAnchorRotationalSkew();
    ~SpriteOffsetAnchorRotationalSkew();
    virtual std::string title();
};

class SpriteBatchNodeOffsetAnchorSkew : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeOffsetAnchorSkew);
    SpriteBatchNodeOffsetAnchorSkew();
    ~SpriteBatchNodeOffsetAnchorSkew();
    virtual std::string title();
};

class SpriteOffsetAnchorRotationalSkewScale : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteOffsetAnchorRotationalSkewScale);
    SpriteOffsetAnchorRotationalSkewScale();
    ~SpriteOffsetAnchorRotationalSkewScale();
    virtual std::string title();
};

class SpriteBatchNodeOffsetAnchorRotationalSkew : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeOffsetAnchorRotationalSkew);
    SpriteBatchNodeOffsetAnchorRotationalSkew();
    ~SpriteBatchNodeOffsetAnchorRotationalSkew();
    virtual std::string title();
};

class SpriteOffsetAnchorSkewScale : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteOffsetAnchorSkewScale);
    SpriteOffsetAnchorSkewScale();
    ~SpriteOffsetAnchorSkewScale();
    virtual std::string title();
};

class SpriteBatchNodeOffsetAnchorSkewScale : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeOffsetAnchorSkewScale);
    SpriteBatchNodeOffsetAnchorSkewScale();
    ~SpriteBatchNodeOffsetAnchorSkewScale();
    virtual std::string title();
};

class SpriteBatchNodeOffsetAnchorRotationalSkewScale : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeOffsetAnchorRotationalSkewScale);
    SpriteBatchNodeOffsetAnchorRotationalSkewScale();
    ~SpriteBatchNodeOffsetAnchorRotationalSkewScale();
    virtual std::string title();
};

class SpriteOffsetAnchorFlip : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteOffsetAnchorFlip);
    SpriteOffsetAnchorFlip();
    ~SpriteOffsetAnchorFlip();
    virtual std::string title();
    virtual std::string subtitle();
};

class SpriteBatchNodeOffsetAnchorFlip : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeOffsetAnchorFlip);
    SpriteBatchNodeOffsetAnchorFlip();
    ~SpriteBatchNodeOffsetAnchorFlip();
    virtual std::string title();
    virtual std::string subtitle();
};

class SpriteAnimationSplit : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteAnimationSplit);
    SpriteAnimationSplit();
    virtual void onExit();
    virtual std::string title();
};

class SpriteHybrid: public SpriteTestDemo
{
    bool     _usingSpriteBatchNode; 
public:
    CREATE_FUNC(SpriteHybrid);

    SpriteHybrid();
    void reparentSprite(float dt);
    virtual std::string title();
    virtual void onExit();
};

class SpriteBatchNodeChildren: public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeChildren);
    SpriteBatchNodeChildren();
    virtual void onExit();
    virtual std::string title();
};

class SpriteBatchNodeChildrenZ : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeChildrenZ);
    SpriteBatchNodeChildrenZ();
    virtual void onExit();
    virtual std::string title();
};

class SpriteChildrenVisibility: public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteChildrenVisibility);
    SpriteChildrenVisibility();
    virtual void onExit();
    virtual std::string title();
};

class SpriteChildrenVisibilityIssue665 : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteChildrenVisibilityIssue665);
    SpriteChildrenVisibilityIssue665();
    ~SpriteChildrenVisibilityIssue665();
    virtual std::string title();
    virtual std::string subtitle();
};

class SpriteChildrenAnchorPoint: public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteChildrenAnchorPoint);
    SpriteChildrenAnchorPoint();
    virtual void onExit();
    virtual std::string title();
};

class SpriteBatchNodeChildrenAnchorPoint: public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeChildrenAnchorPoint);
    SpriteBatchNodeChildrenAnchorPoint();
    virtual void onExit();
    virtual std::string title();
};

class SpriteBatchNodeChildrenScale: public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeChildrenScale);
    SpriteBatchNodeChildrenScale();
    virtual std::string title();
};

class SpriteChildrenChildren: public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteChildrenChildren);
    SpriteChildrenChildren();
    virtual std::string title();
};


class SpriteBatchNodeChildrenChildren: public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeChildrenChildren);
    SpriteBatchNodeChildrenChildren();
    virtual std::string title();
};

class SpriteNilTexture: public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteNilTexture);
    SpriteNilTexture();
    virtual std::string title();
    std::string subtitle();
};

class SpriteSubclass : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteSubclass);
    SpriteSubclass();
    virtual std::string title();
    virtual std::string subtitle();
};

class AnimationCacheTest : public SpriteTestDemo
{
public:
    CREATE_FUNC(AnimationCacheTest);
    AnimationCacheTest();
    virtual std::string title();
    virtual std::string subtitle();
};

class NodeSort : public SpriteTestDemo
{
public:
    CREATE_FUNC(NodeSort);
    NodeSort();

    virtual std::string title();
    virtual std::string subtitle();
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
    
    virtual std::string title();
    virtual std::string subtitle();
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
    virtual std::string title();
private:
    SpriteBatchNode *_batchNode;
    Sprite *_reorderSprite;
};

class SpriteBatchNodeSkewNegativeScaleChildren : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeSkewNegativeScaleChildren);
    SpriteBatchNodeSkewNegativeScaleChildren();
    ~SpriteBatchNodeSkewNegativeScaleChildren();
    virtual std::string title();
    virtual std::string subtitle();
};

class SpriteBatchNodeRotationalSkewNegativeScaleChildren : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchNodeRotationalSkewNegativeScaleChildren);
    SpriteBatchNodeRotationalSkewNegativeScaleChildren();
    ~SpriteBatchNodeRotationalSkewNegativeScaleChildren();
    virtual std::string title();
};

class SpriteSkewNegativeScaleChildren : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteSkewNegativeScaleChildren);
    SpriteSkewNegativeScaleChildren();
    ~SpriteSkewNegativeScaleChildren();
    virtual std::string title();
    virtual std::string subtitle();
};

class SpriteRotationalSkewNegativeScaleChildren : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteRotationalSkewNegativeScaleChildren);
    SpriteRotationalSkewNegativeScaleChildren();
    ~SpriteRotationalSkewNegativeScaleChildren();
    virtual std::string title();
};

class SpriteDoubleResolution : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteDoubleResolution);
    SpriteDoubleResolution();
    virtual std::string title();
    virtual std::string subtitle();
};

class AnimationCacheFile : public SpriteTestDemo
{
public:
    CREATE_FUNC(AnimationCacheFile);

    AnimationCacheFile();
    virtual std::string title();
    virtual std::string subtitle();
};

class SpriteBatchBug1217 : public SpriteTestDemo
{
public:
    CREATE_FUNC(SpriteBatchBug1217);
    SpriteBatchBug1217();
    virtual std::string title();
    virtual std::string subtitle();
};

class SpriteTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
