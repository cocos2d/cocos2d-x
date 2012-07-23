#ifndef _EFFECTS_TEST_H_
#define _EFFECTS_TEST_H_

#include "../testBasic.h"

class EffectTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

class TextLayer : public CCLayerColor
{
protected:
	//UxString	m_strTitle;

public:
	TextLayer(void);
	~TextLayer(void);

	void checkAnim(ccTime dt);

	virtual void onEnter();

	void restartCallback(CCObject* pSender);
	void nextCallback(CCObject* pSender);
	void backCallback(CCObject* pSender);

	void newOrientation();
	void newScene();

	static TextLayer* node();
};

#endif
