#ifndef __CC_APPLICATION_BLACKBERRY_H__
#define __CC_APPLICATION_BLACKBERRY_H__

#include "platform/CCCommon.h"
#include "platform/CCApplicationProtocol.h"
#include <string>
NS_CC_BEGIN;

class Rect;

class CC_DLL Application : public ApplicationProtocol
{
public:
    Application();
    virtual ~Application();

   /**
	@brief    Callback by Director for limit FPS.
	@interval       The time, which expressed in second in second, between current frame and next.
	*/
	void setAnimationInterval(double interval);

	/**
	@brief    Run the message loop.
	*/
	int run();

	/**
	@brief    Get current applicaiton instance.
	@return Current application instance pointer.
	*/
	static Application* getInstance();

    /** @deprecated Use getInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static Application* sharedApplication();
    
	/**
	@brief Get current language config
	@return Current language config
	*/
	virtual LanguageType getCurrentLanguage();

    /**
     @brief Get target platform
     */
    virtual Platform getTargetPlatform();


    /**
	 *  Sets the Resource root path.
	 *  @deprecated Please use FileUtils::getInstance()->setSearchPaths() instead.
	 */
	CC_DEPRECATED_ATTRIBUTE void setResourceRootPath(const std::string& rootResDir);

	/**
	 *  Gets the Resource root path.
	 *  @deprecated Please use FileUtils::getInstance()->getSearchPaths() instead.
	 */
	CC_DEPRECATED_ATTRIBUTE const std::string& getResourceRootPath(void);



protected:
	static Application * sm_pSharedApplication;
	std::string _resourceRootPath;
	static long   			_animationInterval;
};

NS_CC_END

#endif	// __CC_APPLICATION_BLACKBERRY_H__
