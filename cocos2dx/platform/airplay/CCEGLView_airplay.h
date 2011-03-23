#ifndef __CC_EGLVIEW_AIRPLAY_H__
#define __CC_EGLVIEW_AIRPLAY_H__

#include "CCGeometry.h"
#include "s3eKeyboard.h"
#include "IwUtil.h"
#include "IwUtilInitTerm.h"

NS_CC_BEGIN;
class CCSet;
class CCTouch;
class EGLTouchDelegate;
class CCKeypadDelegate;


class CC_DLL CCEGLView
{
public:
    CCEGLView();
    virtual ~CCEGLView();

    CCSize  getSize();
    bool    isOpenGLReady();
	/**
	 * the width and height is the real size of phone
	 */
    void    setFrameWitdAndHeight(int width, int height);
	/**
	 * create a drawing rect, 
	 * the width and heiht is the resource size match best
	 */
	void    create(int width, int height);
    EGLTouchDelegate* getDelegate(void);
    
    // keep compatible
    void    release();
    void    setTouchDelegate(EGLTouchDelegate * pDelegate);
    void    swapBuffers();
    bool    canSetContentScaleFactor();
    void    setContentScaleFactor(float contentScaleFactor);
	void    setViewPortInPoints(float x, float y, float w, float h);
	CCRect  getViewPort();
	float   getScreenScaleFactor();

	// static function
	/**
	 @brief	get the shared main open gl window
	 */
	static CCEGLView& sharedOpenGLView();

private:

	CCSize m_sSizeInPixel;
	CCSize m_sSizeInPoint;
	CCRect m_rcViewPort;
	bool   m_bNotHVGA;
	
	EGLTouchDelegate *m_pDelegate;
	float  m_fScreenScaleFactor;
	
	bool				m_bAccelState;
	bool				m_bCaptured;
	s3eKey				m_Key;
    CCSet *             m_pSet;
    CCTouch *           m_pTouch;
	
	void setTouch(void* systemData);
	void setMotionTouch();
	void setKeyTouch(void* systemData);

	static int32 TouchEventHandler(void* systemData, void* userData)
	{
		((CCEGLView*)userData)->setTouch(systemData);
		return 0;
	}
	static int32 MotionEventHandler(void* systemData, void* userData)
	{
		((CCEGLView*)userData)->setMotionTouch();
		return 0;
	}
	static int32 KeyEventHandler(void* systemData, void* userData)
	{
		((CCEGLView*)userData)->setKeyTouch(systemData);
		return 0;
	}
};
	
NS_CC_END;

#endif	// end of __CC_EGLVIEW_AIRPLAY_H__
