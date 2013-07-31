/*
 * EGLView.h
 *
 *  Created on: Aug 8, 2011
 *      Author: laschweinski
 */

#ifndef EGLVIEW_H_
#define EGLVIEW_H_

#include "platform/CCCommon.h"
#include "cocoa/CCGeometry.h"
#include "platform/CCEGLViewProtocol.h"
#include <SDL2/SDL.h>
#include <set>

bool initExtensions();

NS_CC_BEGIN

class EGLView : public EGLViewProtocol{
public:
    EGLView();
    virtual ~EGLView();

    friend void keyEventHandle(int,int);
    friend void mouseButtonEventHandle(int,int);
    friend void mousePosEventHandle(int,int);
    friend void charEventHandle(int,int);

    /**
     * iPixelWidth, height: the window's size
     * iWidth ,height: the point size, which may scale.
     * iDepth is not the buffer depth of opengl, it indicate how may bits for a pixel
     */
    virtual void setFrameSize(float width, float height);
    virtual void setViewPortInPoints(float x , float y , float w , float h);
    virtual void setScissorInPoints(float x , float y , float w , float h);

    /*
     * Set zoom factor for frame. This method is for debugging big resolution (e.g.new ipad) app on desktop.
     */
    void setFrameZoomFactor(float fZoomFactor);
    float getFrameZoomFactor();
    virtual bool isOpenGLReady();
    virtual void end();
    virtual void swapBuffers();
    virtual void pollInputEvents();
    virtual void setIMEKeyboardState(bool bOpen);

	/**
	 @brief	get the shared main open gl window
	 */
	static EGLView* getInstance();

    /** @deprecated Use getInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static EGLView* sharedOpenGLView();

private:
    bool initGL();
    void destroyGL();

    //store current mouse point for moving, valid if and only if the mouse pressed
    Point _mousePoint;
    bool _wasInit;
    float _frameZoomFactor;

    SDL_Window *_window;
    SDL_GLContext _context;
    // Several mouse instances are possible.
    std::set<int> _pressedMouseInstances;
    bool _IMEKeyboardOpened;
};

NS_CC_END

#endif /* EGLVIEW_H_ */
