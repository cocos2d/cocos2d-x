#pragma once

#include "cocos2d.h"

class HelloWorldApplication : public cocos2d::CCXApplication
{
public:
	virtual bool initCocos2d();
	virtual bool InitInstance();

protected:
	cocos2d::CCXEGLView m_MainForm;
};