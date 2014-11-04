
#include "native/CCNative.h"
//#include "platform/wp8/CCNativeWP8.h"

NS_CC_EXTRA_BEGIN

void Native::showActivityIndicator(void)
{
	CCLOG("Native::showActivityIndicator() - not support this platform.");
}

void Native::hideActivityIndicator(void)
{
	CCLOG("Native::hideActivityIndicator() - not support this platform.");
}


void Native::createAlert(const char* title,
	const char* message,
	const char* cancelButtonTitle)
{
	CCLOG("Native::createAlert() - not support this platform.");
}

int Native::addAlertButton(const char* buttonTitle)
{
	CCLOG("Native::addAlertButton() - not support this platform.");
	return -1;
}

#if CC_LUA_ENGINE_ENABLED > 0
int Native::addAlertButtonLua(const char* buttonTitle)
{
	return addAlertButton(buttonTitle) + 1;
}
#endif

void Native::showAlert(AlertViewDelegate* delegate)
{
	CCLOG("Native::showAlert() - not support this platform.");
}

#if CC_LUA_ENGINE_ENABLED > 0
void Native::showAlertLua(cocos2d::LUA_FUNCTION listener)
{
	CCLOG("Native::showAlertLua() - not support this platform.");
}
#endif

void Native::cancelAlert(void)
{
	CCLOG("Native::cancelAlert() - not support this platform.");
}

const std::string Native::getOpenUDID(void)
{
	CCLOG("Native::getOpenUDID() - not support this platform.");
	return "";
}

void Native::openURL(const char* url)
{
	CCLOG("Native::openURL() - not support this platform.");
	if (!url) return;
}

const std::string Native::getInputText(const char* title, const char* message, const char* defaultValue)
{
	CCLOG("Native::getInputText() - not support this platform.");
	return message;
}

const string Native::getDeviceName(void)
{
	return "wp8";
}

void Native::vibrate()
{
	CCLOG("Native::vibrate() - not support this platform.");
}


NS_CC_EXTRA_END
