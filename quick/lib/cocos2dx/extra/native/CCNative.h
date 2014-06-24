
#ifndef __CC_EXTENSION_CCNATIVE_H_
#define __CC_EXTENSION_CCNATIVE_H_

#include "cocos2dx_extra.h"
#include "CCAlertViewDelegate.h"

#if CC_LUA_ENGINE_ENABLED > 0
#include "CCLuaEngine.h"
#endif

NS_CC_EXTRA_BEGIN

class Native
{
public:
    
#pragma mark -
#pragma mark activity indicator
    
    /** @brief Show activity indicator */
    static void showActivityIndicator(void);
    
    /** @brief Hide activity indicator */
    static void hideActivityIndicator(void);
    
#pragma mark -
#pragma mark alert view
    
    /** @brief Create alert view */
    static void createAlert(const char* title,
                            const char* message,
                            const char* cancelButtonTitle);
    
    /** @brief Add button to alert view, return button index */
    static int addAlertButton(const char* buttonTitle);

    /** @brief Show alert view */
    static void showAlert(AlertViewDelegate* delegate = NULL);
    /** @brief Hide and remove alert view */
    static void cancelAlert(void);
    
#pragma mark -
#pragma mark OpenUDID
    
    /** @brief Get OpenUDID value */
    static const std::string getOpenUDID(void);
    
#pragma mark -
#pragma mark misc
    
    /** @brief Open a web page in the browser; create an email; or call a phone number. */
    static void openURL(const char* url);
    
	/** @brief Show alert view, and get user input */
    static const std::string getInputText(const char* title, const char* message, const char* defaultValue);
    
#pragma mark -
#pragma mark helper
    
    static const std::string getDeviceName(void);
    static void vibrate();
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    static void showAlertObjc(void *delegate);
#endif
    
#if CC_LUA_ENGINE_ENABLED > 0
    static int addAlertButtonLua(const char* buttonTitle);
    static void showAlertLua(LUA_FUNCTION listener);
#endif

private:
    Native(void) {}
};

NS_CC_EXTRA_END

#endif // __CC_EXTENSION_CCNATIVE_H_
