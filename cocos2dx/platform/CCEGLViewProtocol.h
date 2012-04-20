#ifndef __CCEGLVIEWPROTOCOL_H__
#define __CCEGLVIEWPROTOCOL_H__

#include "ccTypes.h"

NS_CC_BEGIN

class EGLTouchDelegate;
class CCSet;

class CC_DLL CCEGLViewProtocol
{
public:
    CCEGLViewProtocol();
    virtual ~CCEGLViewProtocol();

    virtual void    end() = 0;
    virtual bool    isOpenGLReady() = 0;
    virtual void    swapBuffers() = 0;
    virtual void    setIMEKeyboardState(bool bOpen) = 0;

    virtual CCRect  getViewPort();
    virtual CCSize  getSize();
    virtual void    setTouchDelegate(EGLTouchDelegate * pDelegate);
    virtual float   getScreenScaleFactor();
    virtual bool    canSetContentScaleFactor();
    virtual void    setContentScaleFactor(float contentScaleFactor);
    virtual void    setViewPortInPoints(float x , float y , float w , float h);
    virtual void    setScissorInPoints(float x , float y , float w , float h);
    virtual float   getMainScreenScale();
    
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
    CCSize m_sSizeInPixel;
    CCSize m_sSizeInPoint;
    CCRect m_rcViewPort;
};

NS_CC_END

#endif /* __CCEGLVIEWPROTOCOL_H__ */
