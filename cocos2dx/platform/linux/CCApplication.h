/*
 * Aplication.h
 *
 *  Created on: Aug 8, 2011
 *      Author: laschweinski
 */

#ifndef CCAPLICATION_H_
#define CCAPLICATION_H_

#include "platform/CCCommon.h"
#include "platform/CCApplicationProtocol.h"
#include <string>

NS_CC_BEGIN
class Rect;

class Application : public ApplicationProtocol
{
public:
	Application();
	virtual ~Application();

	/**
	 @brief	Callback by Director for limit FPS.
	 @interval       The time, which expressed in second in second, between current frame and next.
	 */
	void setAnimationInterval(double interval);

	/**
	 @brief	Run the message loop.
	 */
	int run();

	/**
	 @brief	Get current applicaiton instance.
	 @return Current application instance pointer.
	 */
	static Application* sharedApplication();

	/* override functions */
	virtual ccLanguageType getCurrentLanguage();

	/**
     *  Sets the Resource root path.
     *  @deprecated Please use FileUtils::sharedFileUtils()->setSearchPaths() instead.
     */
    CC_DEPRECATED_ATTRIBUTE void setResourceRootPath(const std::string& rootResDir);
    
	/** 
     *  Gets the Resource root path.
     *  @deprecated Please use FileUtils::sharedFileUtils()->getSearchPaths() instead. 
     */
    CC_DEPRECATED_ATTRIBUTE const std::string& getResourceRootPath(void);
    
    /**
     @brief Get target platform
     */
    virtual TargetPlatform getTargetPlatform();
protected:
    long       _animationInterval;  //micro second
    std::string _resourceRootPath;
    
	static Application * sm_pSharedApplication;
};

NS_CC_END

#endif /* CCAPLICATION_H_ */
