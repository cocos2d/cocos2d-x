#ifndef  __CC_APPLICATION_WOPHONE_H__
#define  __CC_APPLICATION_WOPHONE_H__

#include "TG3.h"
#include "CCDirector.h"
#include "CCCommon.h"

NS_CC_BEGIN;

class CC_DLL CCApplication : public  TApplication
{
public:
    CCApplication();
    virtual ~CCApplication();

    virtual Boolean EventHandler(EventType * pEvent);

public:
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
    } Orientation;

    /**
    @brief	Callback by CCDirector for change device orientation.
    @orientation    The defination of orientation which CCDirector want change to.
    @return         The actual orientation of the application.
    */
    Orientation setOrientation(Orientation orientation);

    /**
    @brief	Get status bar rectangle in EGLView window.
    */
    void    statusBarFrame(CCRect * rect);

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

    /**
    @brief Get the data path of the Application.
    @return If the app is installed,the return value is the "Const" path of the application,
    else the return value is "/NEWPLUS/TG3/ConstData/"
    */
    const char* getAppDataPath();

    /**
    @brief Get the writable path for the Application.
    @return If the app is installed,the return value is the "Data" path of the application.
    else the return value is "/NEWPLUS/TG3/TDA_DATA/Data/Data/"
    */
    const char* getAppWritablePath();

    void switchNotify(int nTurnOn);

    /**
    @brief	Wophone hasn't support window rotate orientation with EGL, so use orientation table instead.
    */
    static void  setDesignOrientation(UInt32 uOrientation);
    static UInt32 getDesignOrientation();

protected:
    bool isInBackground();
    void StartMainLoop();
    void StopMainLoop();

protected:
    static Int32 _OnAppIdle(MESSAGE_t * pMsg, UInt32 uData);

    MESSAGE_t   m_tMsg;
    bool        m_bRunning;
    bool        m_bNeedStop;
    bool        m_bInBackground;
    bool        m_bEnterBackgroundCalled;
    char        m_AppDataPath[EOS_FILE_MAX_PATH];
    char        m_AppWritablePath[EOS_FILE_MAX_PATH];

    static CCApplication *  sm_pSharedApplication;
    static UInt32           sm_uDesignOrientation;
    static const Orientation * const sm_OrientationTable[];
};

NS_CC_END;

#endif // __CC_APPLICATION_WOPHONE_H__
