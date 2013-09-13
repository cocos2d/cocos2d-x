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
    /**
     * @js ctor
     */
	Application();
    /**
     * @js NA
     * @lua NA
     */
	virtual ~Application();

	/**
	 @brief	Callback by Director for limit FPS.
	 @param interval    The time, which expressed in second in second, between current frame and next.
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
	static Application* getInstance();

    /** @deprecated Use getInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static Application* sharedApplication();
    
	/* override functions */
	virtual LanguageType getCurrentLanguage();

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
    
    /**
     @brief Get target platform
     */
    virtual Platform getTargetPlatform();
protected:
    long       _animationInterval;  //micro second
    std::string _resourceRootPath;
    
	static Application * sm_pSharedApplication;
};

NS_CC_END

#endif /* CCAPLICATION_H_ */
