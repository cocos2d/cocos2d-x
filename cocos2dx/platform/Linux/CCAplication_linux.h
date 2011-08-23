/*
 * CCAplication_linux.h
 *
 *  Created on: Aug 8, 2011
 *      Author: laschweinski
 */

#ifndef CCAPLICATION_LINUX_H_
#define CCAPLICATION_LINUX_H_

#include "CCCommon.h"

NS_CC_BEGIN;
class CCRect;

class CCApplication {
public:
	CCApplication();
	virtual ~CCApplication();

	/**
	 @brief	Implement for initialize OpenGL instance, set source path, etc...
	 */
	virtual bool initInstance() = 0;

	/**
	 @brief	Implement CCDirector and CCScene init code here.
	 @return true    Initialize success, app continue.
	 @return false   Initialize failed, app terminate.
	 */
	virtual bool applicationDidFinishLaunching() = 0;

	/**
	 @brief  The function be called when the application enter background
	 @param  the pointer of the application
	 */
	virtual void applicationDidEnterBackground() = 0;

	/**
	 @brief  The function be called when the application enter foreground
	 @param  the pointer of the application
	 */
	virtual void applicationWillEnterForeground() = 0;

	/**
	 @brief	Callback by CCDirector for limit FPS.
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
	}Orientation;

	/**
	 @brief	Callback by CCDirector for change device orientation.
	 @orientation    The defination of orientation which CCDirector want change to.
	 @return         The actual orientation of the application.
	 */
	Orientation setOrientation(Orientation orientation);

	/**
	 @brief	Get status bar rectangle in EGLView window.
	 */
	void statusBarFrame(CCRect * rect);

	/**
	 @brief	Run the message loop.
	 */
	int run();

	/**
	 @brief	Get current applicaiton instance.
	 @return Current application instance pointer.
	 */
	static CCApplication& sharedApplication();

	/**
	 @brief Get current language config
	 @return Current language config
	 */
	static ccLanguageType getCurrentLanguage();
protected:
    long       m_nAnimationInterval;  //micro second

	static CCApplication * sm_pSharedApplication;
};

NS_CC_END;

#endif /* CCAPLICATION_LINUX_H_ */
