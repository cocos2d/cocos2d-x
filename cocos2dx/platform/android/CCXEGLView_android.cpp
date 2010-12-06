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
#include "CCXEGLView_android.h"
#include "GLES/gl.h"

#include "CCXCocos2dDefine.h"
#include "NSSet.h"
#include "CCDirector.h"
#include "CCTouch.h"
#include "CCTouchDispatcher.h"
#include "ccMacros.h"

#include <stdlib.h>
#include <jni.h>
#include <android/log.h>

extern "C"
{
	static cocos2d::EGLTouchDelegate *s_pDelegate;
	static cocos2d::CCTouch s_touch;
	static cocos2d::NSSet s_set;
	
	
	void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesBegin(JNIEnv*  env, jobject thiz, jfloat x, jfloat y)
	{
		s_touch.SetTouchInfo(0, x, y);
		s_set.addObject(&s_touch);
		s_pDelegate->touchesBegan(&s_set, NULL);
	}
	
	void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesEnd(JNIEnv*  env, jobject thiz, jfloat x, jfloat y)
	{
		s_touch.SetTouchInfo(0, x, y);
		s_pDelegate->touchesEnded(&s_set, NULL);
		s_set.removeObject(&s_touch);
	}
	
	void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesMove(JNIEnv*  env, jobject thiz, jfloat x, jfloat y)
	{
		s_touch.SetTouchInfo(0, x, y);
		s_pDelegate->touchesMoved(&s_set, NULL);
	}
	
	void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesCancel(JNIEnv*  env, jobject thiz, jfloat x, jfloat y)
	{
		s_touch.SetTouchInfo(0, x, y);
		s_pDelegate->touchesCancelled(&s_set, NULL);
		s_set.removeObject(&s_touch);
	}
}

namespace cocos2d {


CCXEGLView::CCXEGLView()
{
	m_nWidth = 0;
	m_nHeight = 0;
}

void CCXEGLView::setFrameWitdAndHeight(int width, int height)
{
	m_nWidth = width;
	m_nHeight = height;
}

CCXEGLView::~CCXEGLView()
{
	CCX_SAFE_DELETE(s_pDelegate);
}

CGSize  CCXEGLView::getSize()
{
	CGSize size(m_nWidth, m_nHeight);
	return size;
}

bool CCXEGLView::isOpenGLReady()
{
    return (m_nWidth != 0 && m_nHeight !=0);
}

void CCXEGLView::release()
{
	exit(0);
}

void CCXEGLView::setTouchDelegate(EGLTouchDelegate * pDelegate)
{
	s_pDelegate = pDelegate;
}

void CCXEGLView::swapBuffers()
{
}

}       // end of namespace cocos2d

