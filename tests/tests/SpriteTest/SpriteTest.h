#ifndef _SPRITE_TEST_H_
#define _SPRITE_TEST_H_

#include "cocos2d.h"
#include "../testBasic.h"

class SpriteTestDemo : public CCLayer
{
protected:
	std::string	m_strTitle;

public:
	SpriteTestDemo(void);
	~SpriteTestDemo(void);

	virtual std::string title();
	virtual std::string subtitle();
	virtual void onEnter();

	void restartCallback(NSObject* pSender);
	void nextCallback(NSObject* pSender);
	void backCallback(NSObject* pSender);
};

class Sprite1 : public SpriteTestDemo
{
public:
	Sprite1();
	virtual std::string title();

	void addNewSpriteWithCoords(CGPoint p);
	void ccTouchesEnded(NSSet* touches, UIEvent* event);
};

class SpriteSheet1: public SpriteTestDemo
{
public:
	SpriteSheet1();
	void addNewSpriteWithCoords(CGPoint p);
	virtual void ccTouchesEnded(NSSet* touches, UIEvent* event);
	virtual std::string title();
};

class SpriteColorOpacity : public SpriteTestDemo
{
public:
	SpriteColorOpacity();
	void removeAndAddSprite(ccTime dt);
	virtual std::string title();
};

class SpriteSheetColorOpacity : public SpriteTestDemo
{
public:
	SpriteSheetColorOpacity();
	void removeAndAddSprite(ccTime dt);
	virtual std::string title();
};

class SpriteZOrder : public SpriteTestDemo
{
	int		m_dir;
public:
	SpriteZOrder();
	void reorderSprite(ccTime dt);
	virtual std::string title();
};

class SpriteSheetZOrder: public SpriteTestDemo
{
	int		m_dir;
public:
	SpriteSheetZOrder();
	void reorderSprite(ccTime dt);
	virtual std::string title();
};

class SpriteSheetReorder : public SpriteTestDemo
{
public:
	SpriteSheetReorder();
	virtual std::string title();
	std::string subtitle();
};

class SpriteSheetReorderIssue744: public SpriteTestDemo
{
public:
	SpriteSheetReorderIssue744();
	virtual std::string title();
	std::string subtitle();
};

class SpriteZVertex: public SpriteTestDemo
{
	int		m_dir;
	float	m_time;
public:
	virtual void onEnter();
	virtual void onExit();
	SpriteZVertex();
	virtual std::string title();
};

class SpriteSheetZVertex: public SpriteTestDemo
{
	int		m_dir;
	float	m_time;
public:
	virtual void onEnter();
	virtual void onExit();
	SpriteSheetZVertex();
	virtual std::string title();
};

class SpriteAnchorPoint : public SpriteTestDemo
{
public:
	SpriteAnchorPoint();
	virtual std::string title();
};

class SpriteSheetAnchorPoint : public SpriteTestDemo
{
public:
	SpriteSheetAnchorPoint();
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
	void flipSprites(ccTime dt);
	virtual std::string title();
};

class SpriteSheetFlip : public SpriteTestDemo
{
public:
	SpriteSheetFlip();
	void flipSprites(ccTime dt);
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

class SpriteSheetAliased : public SpriteTestDemo
{
public:
	SpriteSheetAliased();
	virtual void onEnter();
	virtual void onExit();
	virtual std::string title();
};

class SpriteNewTexture : public SpriteTestDemo
{
	bool                        m_usingTexture1;
	CCTexture2D*	m_texture1;
	CCTexture2D*	m_texture2; 

public:
	SpriteNewTexture();
	virtual ~SpriteNewTexture();
	void addNewSprite();
	void ccTouchesEnded(NSSet* touches, UIEvent* event);
	virtual std::string title();
};

class SpriteSheetNewTexture : public SpriteTestDemo
{
	CCTexture2D*	m_texture1;
	CCTexture2D*	m_texture2; 

public:
	SpriteSheetNewTexture();
	virtual ~SpriteSheetNewTexture();
	void addNewSprite();
	void ccTouchesEnded(NSSet* touches, UIEvent* event);
	virtual std::string title();
};

class SpriteFrameTest: public SpriteTestDemo
{
public:
	SpriteFrameTest();
	~SpriteFrameTest();
	virtual void onExit();
	virtual std::string title();
    virtual std::string subtitle();

    void startIn05Secs(ccTime dt);
    void flipSprites(ccTime dt);
private:
    CCSprite *m_pSprite1;
    CCSprite *m_pSprite2;
    int      m_nCounter;
};

class SpriteOffsetAnchorRotation: public SpriteTestDemo
{
public:
	SpriteOffsetAnchorRotation();
	virtual void onExit();
	virtual std::string title();
};

class SpriteSheetOffsetAnchorRotation: public SpriteTestDemo
{
public:
	SpriteSheetOffsetAnchorRotation();
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

class SpriteSheetOffsetAnchorScale: public SpriteTestDemo
{
public:
	SpriteSheetOffsetAnchorScale();
	virtual void onExit();
	virtual std::string title();
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
	bool 	m_usingSpriteSheet; 
public:
	SpriteHybrid();
	void reparentSprite(ccTime dt);
	virtual std::string title();
	virtual void onExit();
};

class SpriteSheetChildren: public SpriteTestDemo
{
public:
	SpriteSheetChildren();
	virtual void onExit();
	virtual std::string title();
};

class SpriteSheetChildren2: public SpriteTestDemo
{
public:
	SpriteSheetChildren2();
	virtual void onExit();
	virtual std::string title();
};

class SpriteSheetChildrenZ : public SpriteTestDemo
{
public:
	SpriteSheetChildrenZ();
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

class SpriteChildrenAnchorPoint: public SpriteTestDemo
{
public:
	SpriteChildrenAnchorPoint();
	virtual void onExit();
	virtual std::string title();
};

class SpriteSheetChildrenAnchorPoint: public SpriteTestDemo
{
public:
	SpriteSheetChildrenAnchorPoint();
	virtual void onExit();
	virtual std::string title();
};

class SpriteSheetChildrenScale: public SpriteTestDemo
{
public:
	SpriteSheetChildrenScale();
	virtual std::string title();
};

class SpriteChildrenChildren: public SpriteTestDemo
{
public:
	SpriteChildrenChildren();
	virtual std::string title();
};


class SpriteSheetChildrenChildren: public SpriteTestDemo
{
public:
	SpriteSheetChildrenChildren();
	virtual std::string title();
};

class SpriteNilTexture: public SpriteTestDemo
{
public:
	SpriteNilTexture();
	virtual std::string title();
	std::string subtitle();
};

class SpriteTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
