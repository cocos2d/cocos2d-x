#ifndef __CCEGLVIEWPROTOCOL_H__
#define __CCEGLVIEWPROTOCOL_H__

#include "ccTypes.h"

enum ResolutionPolicy
{
    // The entire application is visible in the specified area without trying to preserve the original aspect ratio.
    // Distortion can occur, and the application may appear stretched or compressed.
    kResolutionExactFit,
    // The entire application fills the specified area, without distortion but possibly with some cropping,
    // while maintaining the original aspect ratio of the application.
    kResolutionNoBorder,
    // The entire application is visible in the specified area without distortion while maintaining the original
    // aspect ratio of the application. Borders can appear on two sides of the application.
    kResolutionShowAll,
    // The application takes the height of the design resolution size and modifies the width of the internal
    // canvas so that it fits the aspect ratio of the device
    // no distortion will occur however you must make sure your application works on different
    // aspect ratios
    kResolutionFixedHeight,
    // The application takes the width of the design resolution size and modifies the height of the internal
    // canvas so that it fits the aspect ratio of the device
    // no distortion will occur however you must make sure your application works on different
    // aspect ratios
    kResolutionFixedWidth,

    kResolutionUnKnown,
};

NS_CC_BEGIN

#define CC_MAX_TOUCHES  5

class EGLTouchDelegate;
class CCSet;

/**
 * @addtogroup platform
 * @{
 * @js NA
 */

class CC_DLL CCEGLViewProtocol
{
public:
    /**
     * @lua NA
     */
    CCEGLViewProtocol();
    /**
     * @lua NA
     */
    virtual ~CCEGLViewProtocol();

    /** Force destroying EGL view, subclass must implement this method. 
     * @lua NA
     */
    virtual void    end() = 0;

    /** Get whether opengl render system is ready, subclass must implement this method. 
     * @lua NA
     */
    virtual bool    isOpenGLReady() = 0;

    /** Exchanges the front and back buffers, subclass must implement this method. 
     * @lua NA
     */
    virtual void    swapBuffers() = 0;

    /** Open or close IME keyboard , subclass must implement this method. 
     * @lua NA
     */
    virtual void    setIMEKeyboardState(bool bOpen) = 0;

    /**
     * Get the frame size of EGL view.
     * In general, it returns the screen size since the EGL view is a fullscreen view.
     */
    virtual const CCSize& getFrameSize() const;

    /**
     * Set the frame size of EGL view.
     */
    virtual void setFrameSize(float width, float height);

    /**
     * Get the visible area size of opengl viewport.
     */
    virtual CCSize getVisibleSize() const;

    /**
     * Get the visible origin point of opengl viewport.
     */
    virtual CCPoint getVisibleOrigin() const;

    /**
     * Set the design resolution size.
     * @param width Design resolution width.
     * @param height Design resolution height.
     * @param resolutionPolicy The resolution policy desired, you may choose:
     *                         [1] kResolutionExactFit Fill screen by stretch-to-fit: if the design resolution ratio of width to height is different from the screen resolution ratio, your game view will be stretched.
     *                         [2] kResolutionNoBorder Full screen without black border: if the design resolution ratio of width to height is different from the screen resolution ratio, two areas of your game view will be cut.
     *                         [3] kResolutionShowAll  Full screen with black border: if the design resolution ratio of width to height is different from the screen resolution ratio, two black borders will be shown.
     */
    virtual void setDesignResolutionSize(float width, float height, ResolutionPolicy resolutionPolicy);

    /** Get design resolution size.
     *  Default resolution size is the same as 'getFrameSize'.
     */
    virtual const CCSize&  getDesignResolutionSize() const;

    /** Set touch delegate */
    virtual void setTouchDelegate(EGLTouchDelegate * pDelegate);

    /**
     * Set opengl view port rectangle with points.
     */
    virtual void setViewPortInPoints(float x , float y , float w , float h);

    /**
     * Set Scissor rectangle with points.
     */
    virtual void setScissorInPoints(float x , float y , float w , float h);

    /**
     * Get whether GL_SCISSOR_TEST is enable
     * @lua NA
     */
    virtual bool isScissorEnabled();

    /**
     * Get the current scissor rectangle
     * @lua NA
     */
    virtual CCRect getScissorRect();
    /**
     * @lua NA
     */
    virtual void setViewName(const char* pszViewName);
    /**
     * @lua NA
     */
    const char* getViewName();

    /** Touch events are handled by default; if you want to customize your handlers, please override these functions: 
     * @lua NA
     */
    virtual void handleTouchesBegin(int num, int ids[], float xs[], float ys[]);
    /**
     * @lua NA
     */
    virtual void handleTouchesMove(int num, int ids[], float xs[], float ys[]);
    /**
     * @lua NA
     */
    virtual void handleTouchesEnd(int num, int ids[], float xs[], float ys[]);
    /**
     * @lua NA
     */
    virtual void handleTouchesCancel(int num, int ids[], float xs[], float ys[]);

    /**
     * Get the opengl view port rectangle.
     */
    const CCRect& getViewPortRect() const;

    /**
     * Get scale factor of the horizontal direction.
     */
    float getScaleX() const;

    /**
     * Get scale factor of the vertical direction.
     */
    float getScaleY() const;
private:
    void getSetOfTouchesEndOrCancel(CCSet& set, int num, int ids[], float xs[], float ys[]);

protected:
    EGLTouchDelegate* m_pDelegate;

    // real screen size
    CCSize m_obScreenSize;
    // resolution size, it is the size appropriate for the app resources.
    CCSize m_obDesignResolutionSize;
    // the view port size
    CCRect m_obViewPortRect;
    // the view name
    char   m_szViewName[50];

    float  m_fScaleX;
    float  m_fScaleY;
    ResolutionPolicy m_eResolutionPolicy;
};

// end of platform group
/// @}

NS_CC_END

#endif /* __CCEGLVIEWPROTOCOL_H__ */
