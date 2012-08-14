/*
 * CCEGLView.h
 *
 *  Created on: Aug 8, 2011
 *      Author: laschweinski
 */

#ifndef CCEGLVIEW_H_
#define CCEGLVIEW_H_

#include "CCCommon.h"
#include "cocoa/CCGeometry.h"
#include "platform/CCEGLViewProtocol.h"

bool initExtensions();

NS_CC_BEGIN

class CCEGLView : public CCEGLViewProtocol{
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
	virtual void setSize(float width, float height);
	virtual bool isOpenGLReady();
	virtual void end();
	virtual void swapBuffers();
	virtual void setIMEKeyboardState(bool bOpen);

	/**
	 @brief	get the shared main open gl window
	 */
	static CCEGLView& sharedOpenGLView();
private:
    bool initGL();
    void destroyGL();
private:
	bool m_bCaptured;
	//store current mouse point for moving, valid if and only if the mouse pressed
	CCPoint m_mousePoint;
	bool bIsInit;
};

NS_CC_END

#endif /* CCEGLVIEW_H_ */
