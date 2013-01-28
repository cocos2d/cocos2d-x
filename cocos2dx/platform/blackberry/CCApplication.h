#ifndef __CC_APPLICATION_BLACKBERRY_H__
#define __CC_APPLICATION_BLACKBERRY_H__

#include "platform/CCCommon.h"
#include "platform/CCApplicationProtocol.h"

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

	typedef enum
	{
		/// Device oriented vertically, home button on the bottom
		kOrientationPortrait = 0,
		/// Device oriented vertically, home button on the top
		kOrientationPortraitUpsideDown = 1,
		/// Device oriented horizontally, home button on the right
		kOrientationLandscapeLeft = 2,
		/// Device oriented horizontally, home button on the left
		kOrientationLandscapeRight = 3,
	} Orientation;

	/**
	@brief    Callback by CCDirector for change device orientation.
	@orientation    The defination of orientation which CCDirector want change to.
	@return         The actual orientation of the application.
	*/
	Orientation setOrientation(Orientation orientation);


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


	/* set the Resource root path */
	void setResourceRootPath(const char *pszRootResDir);

	/* get the Resource root path */
	const char *getResourceRootPath(void);



protected:
	static CCApplication * sm_pSharedApplication;
	std::string m_resourceRootPath;
	static long   			m_animationInterval;
};

NS_CC_END

#endif	// __CC_APPLICATION_BLACKBERRY_H__
