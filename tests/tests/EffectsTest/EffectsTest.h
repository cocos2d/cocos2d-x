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

	void restartCallback(NSObject* pSender);
	void nextCallback(NSObject* pSender);
	void backCallback(NSObject* pSender);

	void newOrientation();
	void newScene();

	static TextLayer* node();
};

#endif
