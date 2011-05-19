#ifndef __PERFORMANCE_SPRITE_TEST_H__
#define __PERFORMANCE_SPRITE_TEST_H__

#include "cocos2d.h"

class SubTest
{
public:
    ~SubTest();
    void removeByTag(int tag);
    cocos2d::CCSprite* createSpriteWithTag(int tag);
    void initWithSubTest(int nSubTest, cocos2d::CCNode* parent);

protected:
    int					subtestNumber;
    cocos2d::CCSpriteBatchNode	*batchNode;
    cocos2d::CCNode* 			parent;
};

class SpriteMainScene : public cocos2d::CCScene
{
public:
    virtual ~SpriteMainScene();
    virtual std::string title();

    void initWithSubTest(int nSubTest, int nNodes);
    void updateNodes();

    void testNCallback(cocos2d::CCObject* pSender);
    void onIncrease(cocos2d::CCObject* pSender);
    void onDecrease(cocos2d::CCObject* pSender);

    virtual void doTest(cocos2d::CCSprite* sprite) = 0;

    void restartCallback(cocos2d::CCObject* pSender);
    void nextCallback(cocos2d::CCObject* pSender);
    void backCallback(cocos2d::CCObject* pSender);
    void showCurrentTest();

    // a selector callback
    virtual void menuCloseCallback(CCObject* pSender);

protected:
    int			lastRenderedCount;
    int			quantityNodes;
    SubTest		*m_pSubTest;
    int			subtestNumber;
};

class SpritePerformTest1 : public SpriteMainScene
{
public:
    virtual void doTest(cocos2d::CCSprite* sprite);
    virtual std::string title();
};

class SpritePerformTest2 : public SpriteMainScene
{
public:
    virtual void doTest(cocos2d::CCSprite* sprite);
    virtual std::string title();
};

class SpritePerformTest3 : public SpriteMainScene
{
public:
    virtual void doTest(cocos2d::CCSprite* sprite);
    virtual std::string title();
};

class SpritePerformTest4 : public SpriteMainScene
{
public:
    virtual void doTest(cocos2d::CCSprite* sprite);
    virtual std::string title();
};

class SpritePerformTest5 : public SpriteMainScene
{
public:
    virtual void doTest(cocos2d::CCSprite* sprite);
    virtual std::string title();
};

class SpritePerformTest6 : public SpriteMainScene
{
public:
    virtual void doTest(cocos2d::CCSprite* sprite);
    virtual std::string title();
};

class SpritePerformTest7 : public SpriteMainScene
{
public:
    virtual void doTest(cocos2d::CCSprite* sprite);
    virtual std::string title();
};

#endif
