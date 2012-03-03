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

#ifndef __CC_EGLVIEW_ANDROID_H__
#define __CC_EGLVIEW_ANDROID_H__

#include "CCGeometry.h"

namespace   cocos2d {
class CCSet;
class CCTouch;
class EGLTouchDelegate;

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
    void    setFrameWidthAndHeight(int width, int height);
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
    void    setScissorInPoints(float x, float y, float w, float h);
	CCRect  getViewPort();
	float   getScreenScaleFactor();
    void    setIMEKeyboardState(bool bOpen);
    
    float   getMainScreenScale() { return -1.0f; }

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
};

}   // end of namespace   cocos2d

#endif	// end of __CC_EGLVIEW_ANDROID_H__
