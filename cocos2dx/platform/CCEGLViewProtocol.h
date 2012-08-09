#ifndef __CCEGLVIEWPROTOCOL_H__
#define __CCEGLVIEWPROTOCOL_H__

#include "ccTypes.h"

enum ResolutionPolicy
{
    // The entire application is visible in the specified area without trying to preserve the original aspect ratio. 
    // Distortion can occur, and the application may appear stretched or compressed.
    kCCResolutionExactFit,
    // The entire application fills the specified area, without distortion but possibly with some cropping, 
    // while maintaining the original aspect ratio of the application.
    kCCResolutionNoBorder,
    // The entire application is visible in the specified area without distortion while maintaining the original 
    // aspect ratio of the application. Borders can appear on two sides of the application.
    kCCResolutionShowAll,
    
    kResolutionUnKnown,
};

NS_CC_BEGIN

#define CC_MAX_TOUCHES  5

class EGLTouchDelegate;
class CCSet;

/**
 * @addtogroup platform
 * @{
 */

class CC_DLL CCEGLViewProtocol
{
public:
    CCEGLViewProtocol();
    virtual ~CCEGLViewProtocol();

    virtual void    end() = 0;
    virtual bool    isOpenGLReady() = 0;
    virtual void    swapBuffers() = 0;
    virtual void    setIMEKeyboardState(bool bOpen) = 0;

    virtual CCSize  getSize();
    virtual void    setSize(float width, float height);
    virtual CCSize  getVisibleSize();
    virtual CCPoint getVisibleOrigin();
    virtual void    setDesignResolutionSize(float width, float height, ResolutionPolicy resolutionPolicy);
    virtual void    setTouchDelegate(EGLTouchDelegate * pDelegate);
    virtual float   getScreenScaleFactor();
    virtual bool    setContentScaleFactor(float contentScaleFactor);
    virtual void    setViewPortInPoints(float x , float y , float w , float h);
    virtual void    setScissorInPoints(float x , float y , float w , float h);
    virtual bool    enableRetina();

    /** handle touch events by default, if you want to custom your handles, please override these functions */
    virtual void    handleTouchesBegin(int num, int ids[], float xs[], float ys[]);
    virtual void    handleTouchesMove(int num, int ids[], float xs[], float ys[]);
    virtual void    handleTouchesEnd(int num, int ids[], float xs[], float ys[]);
    virtual void    handleTouchesCancel(int num, int ids[], float xs[], float ys[]);

private:
    void getSetOfTouchesEndOrCancel(CCSet& set, int num, int ids[], float xs[], float ys[]);
protected:
    EGLTouchDelegate* m_pDelegate;
    float  m_fScreenScaleFactor;
    // real size of screen
    CCSize m_obScreenSize;
    // resolution size, it is the size the app resources designed for
    CCSize m_obDesignResolutionSize;
    // the view port size
    CCRect m_obViewPortRect;
    char   m_szViewName[50];
    float  m_fXScale;
    float  m_fYScale;
    ResolutionPolicy m_eResolutionPolicy;
    bool   m_bIsRetinaEnabled;
};

// end of platform group
/// @}

NS_CC_END

#endif /* __CCEGLVIEWPROTOCOL_H__ */
