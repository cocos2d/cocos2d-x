/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __CC_EGLVIEW_WIN32_H__
#define __CC_EGLVIEW_WIN32_H__

#include <Windows.h>
#include "platform/CCCommon.h"
#include "cocoa/CCGeometry.h"
#include "platform/CCEGLViewProtocol.h"

NS_CC_BEGIN

class CCEGL;

class CC_DLL CCEGLView : public CCEGLViewProtocol
{
public:
    CCEGLView();
    virtual ~CCEGLView();

    /* override functions */
    virtual bool isOpenGLReady();
    virtual void end();
    virtual void swapBuffers();
    virtual bool canSetContentScaleFactor();
    virtual void setContentScaleFactor(float contentScaleFactor);
    virtual void setFrameSize(float width, float height);
    virtual void setIMEKeyboardState(bool bOpen);

private:
    virtual bool Create(LPCTSTR pTitle, int w, int h);
    bool initGL();
    void destroyGL();
public:
    virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

    // win32 platform function
    HWND getHWnd();
    void resize(int width, int height);
    void centerWindow();

    typedef void (*LPFN_ACCELEROMETER_KEYHOOK)( UINT message,WPARAM wParam, LPARAM lParam );
    void setAccelerometerKeyHook( LPFN_ACCELEROMETER_KEYHOOK lpfnAccelerometerKeyHook );

    // static function
    /**
    @brief    get the shared main open gl window
    */
    static CCEGLView& sharedOpenGLView();

protected:

private:
    bool m_bCaptured;
    HWND m_hWnd;
    HDC  m_hDC;
    HGLRC m_hRC;
    LPFN_ACCELEROMETER_KEYHOOK m_lpfnAccelerometerKeyHook;
};

NS_CC_END

#endif    // end of __CC_EGLVIEW_WIN32_H__
