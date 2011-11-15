/*
 * CCEGLViewlinux.h
 *
 *  Created on: Aug 8, 2011
 *      Author: laschweinski
 */

#ifndef CCEGLVIEWLINUX_H_
#define CCEGLVIEWLINUX_H_

#include "CCCommon.h"
#include "CCGeometry.h"

bool initExtensions();

NS_CC_BEGIN;

class CCSet;
class CCTouch;
class EGLTouchDelegate;

class CCEGLView {
public:
	CCEGLView();
	virtual ~CCEGLView();

	friend void keyEventHandle(int,int);
	friend void mouseButtonEventHandle(int,int);
	friend void mousePosEventHandle(int,int);
	friend void charEventHandle(int,int);

	/**
	 * iPixelWidth, height: the window's size
	 * iWidth ,height: the point size, which may scale.
	 * iDepth is not the buffer depth of opengl, it indicate how may bits for a pixel
	 */
	virtual bool Create(const char* pTitle, int iPixelWidth, int iPixelHeight, int iWidth, int iHeight, int iDepth=16);

	CCSize getSize();
	bool isOpenGLReady();
	void release();
	void setTouchDelegate(EGLTouchDelegate * pDelegate);
	void swapBuffers();
	bool canSetContentScaleFactor();
	void setContentScaleFactor(float contentScaleFactor);

	int setDeviceOrientation(int eOritation);
	void setViewPortInPoints(float x, float y, float w, float h);
	void setScissorInPoints(float x, float y, float w, float h);

	void setIMEKeyboardState(bool bOpen);

//	void resize(int width, int height);

	/**
	 * not essential
	 */
//	void centerWindow();
//	void setScreenScale(float factor);

	/**
	 * the width and height is the real size of phone
	 */
	void setFrameWidthAndHeight(int width, int height);

	/**
	 @brief	get the shared main open gl window
	 */
	static CCEGLView& sharedOpenGLView();
private:

	bool m_bCaptured;
	bool m_bOrientationReverted;
	bool m_bOrientationInitVertical;
	CCSet * m_pSet;
	CCTouch * m_pTouch;

	//store current mouse point for moving, valid if and only if the mouse pressed
	CCPoint m_mousePoint;

	EGLTouchDelegate * m_pDelegate;

	CCSize m_sSizeInPixel;
	CCSize m_sSizeInPoint;
	CCRect m_rcViewPort;

	bool bIsInit;
	int m_eInitOrientation;
	float m_fScreenScaleFactor;
};

NS_CC_END;

#endif /* CCEGLVIEWLINUX_H_ */
