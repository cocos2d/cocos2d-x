#ifndef _SPRITE_TEST_H_
#define _SPRITE_TEST_H_

#include "cocos2d.h"
#include "../testBasic.h"
#include <string>

class SpriteTestDemo : public CCLayer
{
protected:
    std::string    m_strTitle;

public:
    SpriteTestDemo(void);
    ~SpriteTestDemo(void);

    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();

    void restartCallback(CCObject* pSender);
    void nextCallback(CCObject* pSender);
    void backCallback(CCObject* pSender);
};

class Sprite1 : public SpriteTestDemo
{
public:
    Sprite1();
    virtual std::string title();

    void addNewSpriteWithCoords(CCPoint p);
    void ccTouchesEnded(CCSet* touches, CCEvent* event);
};

class SpriteBatchNode1: public SpriteTestDemo
{
public:
    SpriteBatchNode1();
    void addNewSpriteWithCoords(CCPoint p);
    virtual void ccTouchesEnded(CCSet* touches, CCEvent* event);
    virtual std::string title();
};

class SpriteColorOpacity : public SpriteTestDemo
{
public:
    SpriteColorOpacity();
    void removeAndAddSprite(float dt);
    virtual std::string title();
};

class SpriteBatchNodeColorOpacity : public SpriteTestDemo
{
public:
    SpriteBatchNodeColorOpacity();
    void removeAndAddSprite(float dt);
    virtual std::string title();
};

class SpriteZOrder : public SpriteTestDemo
{
    int        m_dir;
public:
    SpriteZOrder();
    void reorderSprite(float dt);
    virtual std::string title();
};

class SpriteBatchNodeZOrder: public SpriteTestDemo
{
    int        m_dir;
public:
    SpriteBatchNodeZOrder();
    void reorderSprite(float dt);
    virtual std::string title();
};

class SpriteBatchNodeReorder : public SpriteTestDemo
{
public:
    SpriteBatchNodeReorder();
    virtual std::string title();
    std::string subtitle();
};

class SpriteBatchNodeReorderIssue744: public SpriteTestDemo
{
public:
    SpriteBatchNodeReorderIssue744();
    virtual std::string title();
    std::string subtitle();
};

class SpriteBatchNodeReorderIssue766 : public SpriteTestDemo
{
public:
    SpriteBatchNodeReorderIssue766();
    virtual std::string title();
    virtual std::string subtitle();
    void reorderSprite(float dt);
    CCSprite* makeSpriteZ(int aZ);

private:
    CCSpriteBatchNode *batchNode;
    CCSprite *sprite1;
    CCSprite *sprite2;
    CCSprite *sprite3;    
};

class SpriteBatchNodeReorderIssue767 : public SpriteTestDemo
{
public:
    SpriteBatchNodeReorderIssue767();
    virtual std::string title();
    virtual std::string subtitle();
    void reorderSprites(float dt);
};

class SpriteZVertex: public SpriteTestDemo
{
    int        m_dir;
    float    m_time;
public:
    virtual void onEnter();
    virtual void onExit();
    SpriteZVertex();
    virtual std::string title();
};

class SpriteBatchNodeZVertex: public SpriteTestDemo
{
    int        m_dir;
    float    m_time;
public:
    virtual void onEnter();
    virtual void onExit();
    SpriteBatchNodeZVertex();
    virtual std::string title();
};

class SpriteAnchorPoint : public SpriteTestDemo
{
public:
    SpriteAnchorPoint();
    virtual std::string title();
};

class SpriteBatchNodeAnchorPoint : public SpriteTestDemo
{
public:
    SpriteBatchNodeAnchorPoint();
    virtual std::string title();
};

class Sprite6 : public SpriteTestDemo
{
public:
    Sprite6();
    virtual std::string title();
};

class SpriteFlip : public SpriteTestDemo
{
public:
    SpriteFlip();
    void flipSprites(float dt);
    virtual std::string title();
};

class SpriteBatchNodeFlip : public SpriteTestDemo
{
public:
    SpriteBatchNodeFlip();
    void flipSprites(float dt);
    virtual std::string title();
};

class SpriteAliased : public SpriteTestDemo
{
public:
    SpriteAliased();
    virtual void onEnter();
    virtual void onExit();
    virtual std::string title();
};

class SpriteBatchNodeAliased : public SpriteTestDemo
{
public:
    SpriteBatchNodeAliased();
    virtual void onEnter();
    virtual void onExit();
    virtual std::string title();
};

class SpriteNewTexture : public SpriteTestDemo
{
    bool                        m_usingTexture1;
    CCTexture2D*    m_texture1;
    CCTexture2D*    m_texture2; 

public:
    SpriteNewTexture();
    virtual ~SpriteNewTexture();
    void addNewSprite();
    void ccTouchesEnded(CCSet* touches, CCEvent* event);
    virtual std::string title();
};

class SpriteBatchNodeNewTexture : public SpriteTestDemo
{
    CCTexture2D*    m_texture1;
    CCTexture2D*    m_texture2; 

public:
    SpriteBatchNodeNewTexture();
    virtual ~SpriteBatchNodeNewTexture();
    void addNewSprite();
    void ccTouchesEnded(CCSet* touches, CCEvent* event);
    virtual std::string title();
};

class SpriteFrameTest: public SpriteTestDemo
{
public:
    virtual void onEnter();
    virtual void onExit();
    virtual std::string title();
    virtual std::string subtitle();

    void startIn05Secs(float dt);
    void flipSprites(float dt);
private:
    CCSprite *m_pSprite1;
    CCSprite *m_pSprite2;
    int      m_nCounter;
};

class SpriteFrameAliasNameTest : public SpriteTestDemo
{
public:
    virtual void onEnter();
    virtual void onExit();
    virtual std::string title();
    virtual std::string subtitle();
};

class SpriteOffsetAnchorRotation: public SpriteTestDemo
{
public:
    SpriteOffsetAnchorRotation();
    virtual void onExit();
    virtual std::string title();
};

class SpriteBatchNodeOffsetAnchorRotation: public SpriteTestDemo
{
public:
    SpriteBatchNodeOffsetAnchorRotation();
    virtual void onExit();
    virtual std::string title();
};

class SpriteOffsetAnchorScale: public SpriteTestDemo
{
public:
    SpriteOffsetAnchorScale();
    virtual void onExit();
    virtual std::string title();
};

class SpriteBatchNodeOffsetAnchorScale: public SpriteTestDemo
{
public:
    SpriteBatchNodeOffsetAnchorScale();
    virtual void onExit();
    virtual std::string title();
};

class SpriteOffsetAnchorSkew : public SpriteTestDemo
{
public:
    SpriteOffsetAnchorSkew();
    ~SpriteOffsetAnchorSkew();
    virtual std::string title();
};

class SpriteOffsetAnchorRotationalSkew : public SpriteTestDemo
{
public:
    SpriteOffsetAnchorRotationalSkew();
    ~SpriteOffsetAnchorRotationalSkew();
    virtual std::string title();
};

class SpriteBatchNodeOffsetAnchorSkew : public SpriteTestDemo
{
public:
    SpriteBatchNodeOffsetAnchorSkew();
    ~SpriteBatchNodeOffsetAnchorSkew();
    virtual std::string title();
};

class SpriteOffsetAnchorRotationalSkewScale : public SpriteTestDemo
{
public:
    SpriteOffsetAnchorRotationalSkewScale();
    ~SpriteOffsetAnchorRotationalSkewScale();
    virtual std::string title();
};

class SpriteBatchNodeOffsetAnchorRotationalSkew : public SpriteTestDemo
{
public:
    SpriteBatchNodeOffsetAnchorRotationalSkew();
    ~SpriteBatchNodeOffsetAnchorRotationalSkew();
    virtual std::string title();
};

class SpriteOffsetAnchorSkewScale : public SpriteTestDemo
{
public:
    SpriteOffsetAnchorSkewScale();
    ~SpriteOffsetAnchorSkewScale();
    virtual std::string title();
};

class SpriteBatchNodeOffsetAnchorSkewScale : public SpriteTestDemo
{
public:
    SpriteBatchNodeOffsetAnchorSkewScale();
    ~SpriteBatchNodeOffsetAnchorSkewScale();
    virtual std::string title();
};

class SpriteBatchNodeOffsetAnchorRotationalSkewScale : public SpriteTestDemo
{
public:
    SpriteBatchNodeOffsetAnchorRotationalSkewScale();
    ~SpriteBatchNodeOffsetAnchorRotationalSkewScale();
    virtual std::string title();
};

class SpriteOffsetAnchorFlip : public SpriteTestDemo
{
public:
    SpriteOffsetAnchorFlip();
    ~SpriteOffsetAnchorFlip();
    virtual std::string title();
    virtual std::string subtitle();
};

class SpriteBatchNodeOffsetAnchorFlip : public SpriteTestDemo
{
public:
    SpriteBatchNodeOffsetAnchorFlip();
    ~SpriteBatchNodeOffsetAnchorFlip();
    virtual std::string title();
    virtual std::string subtitle();
};

class SpriteAnimationSplit : public SpriteTestDemo
{
public:
    SpriteAnimationSplit();
    virtual void onExit();
    virtual std::string title();
};

class SpriteHybrid: public SpriteTestDemo
{
    bool     m_usingSpriteBatchNode; 
public:
    SpriteHybrid();
    void reparentSprite(float dt);
    virtual std::string title();
    virtual void onExit();
};

class SpriteBatchNodeChildren: public SpriteTestDemo
{
public:
    SpriteBatchNodeChildren();
    virtual void onExit();
    virtual std::string title();
};

class SpriteBatchNodeChildrenZ : public SpriteTestDemo
{
public:
    SpriteBatchNodeChildrenZ();
    virtual void onExit();
    virtual std::string title();
};

class SpriteChildrenVisibility: public SpriteTestDemo
{
public:
    SpriteChildrenVisibility();
    virtual void onExit();
    virtual std::string title();
};

class SpriteChildrenVisibilityIssue665 : public SpriteTestDemo
{
public:
    SpriteChildrenVisibilityIssue665();
    ~SpriteChildrenVisibilityIssue665();
    virtual std::string title();
    virtual std::string subtitle();
};

class SpriteChildrenAnchorPoint: public SpriteTestDemo
{
public:
    SpriteChildrenAnchorPoint();
    virtual void onExit();
    virtual std::string title();
};

class SpriteBatchNodeChildrenAnchorPoint: public SpriteTestDemo
{
public:
    SpriteBatchNodeChildrenAnchorPoint();
    virtual void onExit();
    virtual std::string title();
};

class SpriteBatchNodeChildrenScale: public SpriteTestDemo
{
public:
    SpriteBatchNodeChildrenScale();
    virtual std::string title();
};

class SpriteChildrenChildren: public SpriteTestDemo
{
public:
    SpriteChildrenChildren();
    virtual std::string title();
};


class SpriteBatchNodeChildrenChildren: public SpriteTestDemo
{
public:
    SpriteBatchNodeChildrenChildren();
    virtual std::string title();
};

class SpriteNilTexture: public SpriteTestDemo
{
public:
    SpriteNilTexture();
    virtual std::string title();
    std::string subtitle();
};

class SpriteSubclass : public SpriteTestDemo
{
public:
    SpriteSubclass();
    virtual std::string title();
    virtual std::string subtitle();
};

class AnimationCache : public SpriteTestDemo
{
public:
    AnimationCache();
    virtual std::string title();
    virtual std::string subtitle();
};

class NodeSort : public SpriteTestDemo
{
public:
    NodeSort();

    virtual std::string title();
    virtual std::string subtitle();
    void reorderSprite(float dt);

private:
    CCNode *m_pNode;
    CCSprite *m_pSprite1;
    CCSprite *m_pSprite2;
    CCSprite *m_pSprite3;
    CCSprite *m_pSprite4;
    CCSprite *m_pSprite5;
};

class SpriteBatchNodeReorderSameIndex : public SpriteTestDemo
{
public:
    SpriteBatchNodeReorderSameIndex();
    
    virtual std::string title();
    virtual std::string subtitle();
    void reorderSprite(float dt);

private:
    CCSpriteBatchNode *m_pBatchNode;
    CCSprite *m_pSprite1;
    CCSprite *m_pSprite2;
    CCSprite *m_pSprite3;
    CCSprite *m_pSprite4;
    CCSprite *m_pSprite5;
};

class SpriteBatchNodeReorderOneChild : public SpriteTestDemo
{
public:
    SpriteBatchNodeReorderOneChild();
    void reorderSprite(float dt);
    virtual std::string title();
private:
    CCSpriteBatchNode *m_pBatchNode;
    CCSprite *m_pReorderSprite;
};

class SpriteBatchNodeSkewNegativeScaleChildren : public SpriteTestDemo
{
public:
    SpriteBatchNodeSkewNegativeScaleChildren();
    ~SpriteBatchNodeSkewNegativeScaleChildren();
    virtual std::string title();
    virtual std::string subtitle();
};

class SpriteBatchNodeRotationalSkewNegativeScaleChildren : public SpriteTestDemo
{
public:
    SpriteBatchNodeRotationalSkewNegativeScaleChildren();
    ~SpriteBatchNodeRotationalSkewNegativeScaleChildren();
    virtual std::string title();
};

class SpriteSkewNegativeScaleChildren : public SpriteTestDemo
{
public:
    SpriteSkewNegativeScaleChildren();
    ~SpriteSkewNegativeScaleChildren();
    virtual std::string title();
    virtual std::string subtitle();
};

class SpriteRotationalSkewNegativeScaleChildren : public SpriteTestDemo
{
public:
    SpriteRotationalSkewNegativeScaleChildren();
    ~SpriteRotationalSkewNegativeScaleChildren();
    virtual std::string title();
};

class SpriteDoubleResolution : public SpriteTestDemo
{
public:
    SpriteDoubleResolution();
    virtual std::string title();
    virtual std::string subtitle();
};

class AnimationCacheFile : public SpriteTestDemo
{
public:
    AnimationCacheFile();
    virtual std::string title();
    virtual std::string subtitle();
};

class SpriteBatchBug1217 : public SpriteTestDemo
{
public:
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
