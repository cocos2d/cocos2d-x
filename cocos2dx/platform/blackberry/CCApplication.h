#ifndef __CC_APPLICATION_BLACKBERRY_H__
#define __CC_APPLICATION_BLACKBERRY_H__

#include "platform/CCCommon.h"
#include "platform/CCApplicationProtocol.h"
#include <string>
NS_CC_BEGIN;

class CCRect;

class CC_DLL CCApplication : public CCApplicationProtocol
{
public:
    CCApplication();
    virtual ~CCApplication();

   /**
	@brief    Callback by CCDirector for limit FPS.
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
	static CCApplication* sharedApplication();

	/**
	@brief Get current language config
	@return Current language config
	*/
	virtual ccLanguageType getCurrentLanguage();

    /**
     @brief Get target platform
     */
    virtual TargetPlatform getTargetPlatform();


    /**
	 *  Sets the Resource root path.
	 *  @deprecated Please use CCFileUtils::sharedFileUtils()->setSearchPaths() instead.
	 */
	CC_DEPRECATED_ATTRIBUTE void setResourceRootPath(const std::string& rootResDir);

	/**
	 *  Gets the Resource root path.
	 *  @deprecated Please use CCFileUtils::sharedFileUtils()->getSearchPaths() instead.
	 */
	CC_DEPRECATED_ATTRIBUTE const std::string& getResourceRootPath(void);



protected:
	static CCApplication * sm_pSharedApplication;
	std::string m_resourceRootPath;
	static long   			m_animationInterval;
};

NS_CC_END

#endif	// __CC_APPLICATION_BLACKBERRY_H__
