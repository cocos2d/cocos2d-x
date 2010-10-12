#ifndef __TEST_APPLICATION_H__
#define __TEST_APPLICATION_H__

#include "cocos2d.h"

class TestApplication : public cocos2d::CCXApplication
{
public:
	virtual bool initCocos2d();
	virtual bool InitInstance();

	virtual void applicationDidEnterBackground();
	virtual void applicationWillEnterForeground();

protected:
	cocos2d::CCXEGLView m_MainForm;
};

#endif	// __TEST_APPLICATION_H__