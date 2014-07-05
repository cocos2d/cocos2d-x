#pragma once

#include "platform\wp8-xaml\cpp\Cocos2dRenderer.h"

class AppDelegate;

ref class CustomRenderer sealed : public Cocos2dRenderer
{
private:	
	AppDelegate* m_App;

public:
	CustomRenderer();
};
