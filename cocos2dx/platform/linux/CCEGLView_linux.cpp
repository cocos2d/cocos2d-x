/*
 * CCEGLViewlinux.cpp
 *
 *  Created on: Aug 8, 2011
 *      Author: laschweinski
 */

#include "CCEGLView_linux.h"

#include "CCGL.h"

#include "GL/glfw.h"

#include "CCSet.h"
#include "ccMacros.h"
#include "CCDirector.h"
#include "CCTouch.h"
#include "CCTouchDispatcher.h"
#include "CCIMEDispatcher.h"

PFNGLGENFRAMEBUFFERSEXTPROC glGenFramebuffersEXT = NULL;
PFNGLDELETEFRAMEBUFFERSEXTPROC glDeleteFramebuffersEXT = NULL;
PFNGLBINDFRAMEBUFFEREXTPROC glBindFramebufferEXT = NULL;
PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC glCheckFramebufferStatusEXT = NULL;
PFNGLFRAMEBUFFERTEXTURE2DEXTPROC glFramebufferTexture2DEXT = NULL;
PFNGLGENERATEMIPMAPEXTPROC glGenerateMipmapEXT = NULL;

PFNGLGENBUFFERSARBPROC glGenBuffersARB = NULL;
PFNGLBINDBUFFERARBPROC glBindBufferARB = NULL;
PFNGLBUFFERDATAARBPROC glBufferDataARB = NULL;
PFNGLBUFFERSUBDATAARBPROC glBufferSubDataARB = NULL;
PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB = NULL;

bool initExtensions() {
#define LOAD_EXTENSION_FUNCTION(TYPE, FN)  FN = (TYPE)glfwGetProcAddress(#FN);
	bool bRet = false;
	do {

//		char* p = (char*) glGetString(GL_EXTENSIONS);
//		printf(p);

		/* Supports frame buffer? */
		if (glfwExtensionSupported("GL_EXT_framebuffer_object") != GL_FALSE)
		{

			/* Loads frame buffer extension functions */
			LOAD_EXTENSION_FUNCTION(PFNGLGENERATEMIPMAPEXTPROC,
					glGenerateMipmapEXT);
			LOAD_EXTENSION_FUNCTION(PFNGLGENFRAMEBUFFERSEXTPROC,
					glGenFramebuffersEXT);
			LOAD_EXTENSION_FUNCTION(PFNGLDELETEFRAMEBUFFERSEXTPROC,
					glDeleteFramebuffersEXT);
			LOAD_EXTENSION_FUNCTION(PFNGLBINDFRAMEBUFFEREXTPROC,
					glBindFramebufferEXT);
			LOAD_EXTENSION_FUNCTION(PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC,
					glCheckFramebufferStatusEXT);
			LOAD_EXTENSION_FUNCTION(PFNGLFRAMEBUFFERTEXTURE2DEXTPROC,
					glFramebufferTexture2DEXT);

		} else {
			break;
		}

		if (glfwExtensionSupported("GL_ARB_vertex_buffer_object") != GL_FALSE) {
			LOAD_EXTENSION_FUNCTION(PFNGLGENBUFFERSARBPROC, glGenBuffersARB);
			LOAD_EXTENSION_FUNCTION(PFNGLBINDBUFFERARBPROC, glBindBufferARB);
			LOAD_EXTENSION_FUNCTION(PFNGLBUFFERDATAARBPROC, glBufferDataARB);
			LOAD_EXTENSION_FUNCTION(PFNGLBUFFERSUBDATAARBPROC,
					glBufferSubDataARB);
			LOAD_EXTENSION_FUNCTION(PFNGLDELETEBUFFERSARBPROC,
					glDeleteBuffersARB);
		} else {
			break;
		}
		bRet = true;
	} while (0);
	return bRet;
}

NS_CC_BEGIN;
static CCEGLView* s_pMainWindow = NULL;

CCEGLView::CCEGLView()
: m_bCaptured(false)
, m_bOrientationReverted(false)
, m_bOrientationInitVertical(false)
, m_pDelegate(NULL)
, bIsInit(false)
, m_eInitOrientation(CCDeviceOrientationPortrait)
, m_fScreenScaleFactor(1.0f)
{
	m_pTouch = new CCTouch;
	m_pSet = new CCSet;
	m_sSizeInPoint.width = m_sSizeInPoint.height = 0;
//    SetRectEmpty(&m_rcViewPort);
}

CCEGLView::~CCEGLView()
{
}

void keyEventHandle(int iKeyID,int iKeyState) {
	if (iKeyState ==GLFW_RELEASE) {
		return;
	}

	if (iKeyID == GLFW_KEY_DEL) {
		CCIMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
	} else if (iKeyID == GLFW_KEY_ENTER) {
		CCIMEDispatcher::sharedDispatcher()->dispatchInsertText("\n", 1);
	} else if (iKeyID == GLFW_KEY_TAB) {

	}
}

void charEventHandle(int iCharID,int iCharState) {
	if (iCharState ==GLFW_RELEASE) {
		return;
	}

	// ascii char
	CCIMEDispatcher::sharedDispatcher()->dispatchInsertText((const char *)&iCharID, 1);

}

void mouseButtonEventHandle(int iMouseID,int iMouseState) {
	if (iMouseID == GLFW_MOUSE_BUTTON_LEFT) {
		//get current mouse pos
		int x,y;
		glfwGetMousePos(&x, &y);
		CCPoint oPoint((float)x,(float)y);

		if (!CCRect::CCRectContainsPoint(s_pMainWindow->m_rcViewPort,oPoint)) {
			CCLOG("not in the viewport");
			return;
		}

		s_pMainWindow->m_pTouch->SetTouchInfo(0, (float)(oPoint.x - s_pMainWindow->m_rcViewPort.origin.x) / s_pMainWindow->m_fScreenScaleFactor,
				(float)(oPoint.y - s_pMainWindow->m_rcViewPort.origin.y) / s_pMainWindow->m_fScreenScaleFactor);
		s_pMainWindow->m_pSet->addObject(s_pMainWindow->m_pTouch);
		s_pMainWindow->m_mousePoint = oPoint;

		if (iMouseState == GLFW_PRESS) {
			s_pMainWindow->m_pDelegate->touchesBegan(s_pMainWindow->m_pSet,NULL);

		} else if (iMouseState == GLFW_RELEASE) {
			s_pMainWindow->m_pDelegate->touchesEnded(s_pMainWindow->m_pSet,NULL);
		}
	}
}

void mousePosEventHandle(int iPosX,int iPosY) {
	int iButtonState = glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT);

	//to test move
	if (iButtonState == GLFW_PRESS) {
		if (iPosX!=(int)s_pMainWindow->m_mousePoint.x||iPosY!=(int)s_pMainWindow->m_mousePoint.y) {
			//it movies
			s_pMainWindow->m_pTouch->SetTouchInfo(0, (float)(iPosX- s_pMainWindow->m_rcViewPort.origin.x) / s_pMainWindow->m_fScreenScaleFactor,
					(float)(iPosY - s_pMainWindow->m_rcViewPort.origin.y) / s_pMainWindow->m_fScreenScaleFactor);
			s_pMainWindow->m_pDelegate->touchesMoved(s_pMainWindow->m_pSet, NULL);
			//update new mouse pos
			s_pMainWindow->m_mousePoint.x = iPosX;
			s_pMainWindow->m_mousePoint.y = iPosY;
		}
	}
}

bool CCEGLView::Create(const char* pTitle, int iPixelWidth, int iPixelHeight, int iWidth, int iHeight, int iDepth) {
	bool eResult;
	int u32GLFWFlags = GLFW_WINDOW;
	//create the window by glfw.

	//check
	CCAssert(iPixelWidth!=0&&iPixelHeight!=0, "invalid window's size equal 0");
	CCAssert(iWidth!=0&&iHeight!=0, "invalid the size in points equal 0");

	//Inits GLFW
	eResult = glfwInit() != GL_FALSE;

	if (!eResult) {
		CCAssert(0, "fail to init the glfw");
	}

	/* Updates window hint */
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);

	/* Depending on video depth */
	switch(iDepth)
	{
		/* 16-bit */
		case 16:
		{
			/* Updates video mode */
			eResult = (glfwOpenWindow(iPixelWidth, iPixelHeight, 5, 6, 5, 0, 16, 0, (int)u32GLFWFlags) != false) ? true : false;

			break;
		}

		/* 24-bit */
		case 24:
		{
			/* Updates video mode */
			eResult = (glfwOpenWindow(iPixelWidth, iPixelHeight, 8, 8, 8, 0, 16, 0, (int)u32GLFWFlags) != false) ? true : false;

			break;
		}

		/* 32-bit */
		default:
		case 32:
		{
			/* Updates video mode */
			eResult = (glfwOpenWindow(iPixelWidth, iPixelHeight, 8, 8, 8, 8, 16, 0, (int)u32GLFWFlags) != GL_FALSE) ? true :false;
			break;
		}
	}

	/* Success? */
	if(eResult)
	{

		/* Updates actual size */
		glfwGetWindowSize(&iPixelWidth, &iPixelHeight);

		//assign screen size and point's size
		m_sSizeInPixel.width = iPixelWidth;
		m_sSizeInPixel.height = iPixelHeight;

		m_sSizeInPoint.width = iWidth;
		m_sSizeInPoint.height = iHeight;

		// calculate the factor and the rect of viewport
		m_fScreenScaleFactor = MIN((float)m_sSizeInPixel.width / m_sSizeInPoint.width,
				(float)m_sSizeInPixel.height / m_sSizeInPoint.height);

		int viewPortW = (int)(m_sSizeInPoint.width * m_fScreenScaleFactor);
		int viewPortH = (int)(m_sSizeInPoint.height * m_fScreenScaleFactor);
		m_rcViewPort.origin.x = (m_sSizeInPixel.width - viewPortW) / 2;
		m_rcViewPort.origin.y = (m_sSizeInPixel.height - viewPortH) / 2;
		m_rcViewPort.size.width = viewPortW;
		m_rcViewPort.size.height = viewPortH;

		/* Updates its title */
		glfwSetWindowTitle(pTitle);

		//set the init flag
		bIsInit = true;
		s_pMainWindow = this;

		//register the glfw key event
		glfwSetKeyCallback(keyEventHandle);
		//register the glfw char event
		glfwSetCharCallback(charEventHandle);
		//register the glfw mouse event
		glfwSetMouseButtonCallback(mouseButtonEventHandle);
		//register the glfw mouse pos event
		glfwSetMousePosCallback(mousePosEventHandle);

		//Inits extensions
		eResult = initExtensions();

		if (!eResult) {
			CCAssert(0, "fail to init the extensions of opengl");
		}

	}
	return true;
}

CCSize CCEGLView::getSize()
{
	return CCSize((float)(m_sSizeInPoint.width), (float)(m_sSizeInPoint.height));
}

bool CCEGLView::isOpenGLReady()
{
	return bIsInit;
}

void CCEGLView::release()
{
	/* Exits from GLFW */
	glfwTerminate();
	exit(0);
}

void CCEGLView::setTouchDelegate(EGLTouchDelegate * pDelegate) {
	//TODO touch event
	m_pDelegate = pDelegate;

}
void CCEGLView::swapBuffers() {
	if (bIsInit) {
		/* Swap buffers */
		glfwSwapBuffers();
	}
}

int CCEGLView::setDeviceOrientation(int eOritation) {
	CCLog("warning:could not setDeviceOrientation after initialized");
    return -1;
}

void CCEGLView::setViewPortInPoints(float x, float y, float w, float h) {
//	TODO
	if (bIsInit) {
		float factor = m_fScreenScaleFactor / CC_CONTENT_SCALE_FACTOR();
		glViewport((GLint)(x * factor) + m_rcViewPort.origin.x,
				(GLint)(y * factor) + m_rcViewPort.origin.y,
				(GLint)(w * factor),
				(GLint)(h * factor));
	}
}
void CCEGLView::setScissorInPoints(float x, float y, float w, float h) {
	//TODO
	if (bIsInit) {
		float factor = m_fScreenScaleFactor / CC_CONTENT_SCALE_FACTOR();
		glScissor((GLint)(x * factor) + m_rcViewPort.origin.x,
				(GLint)(y * factor) + m_rcViewPort.origin.y,
				(GLint)(w * factor),
				(GLint)(h * factor));
	}
}

void CCEGLView::setIMEKeyboardState(bool bOpen) {

}

//void CCEGLView::resize(int width, int height) {
//	//TODO
//	return;
//}

//void CCEGLView::centerWindow() {
//	//TODO
//	return;
//}
//void CCEGLView::setScreenScale(float factor) {
//	m_fScreenScaleFactor = factor;
//
//}

bool CCEGLView::canSetContentScaleFactor() {
	return false;
}

void CCEGLView::setContentScaleFactor(float contentScaleFactor) {
	CCLog("could not set contentScaleFactor after initialized");

}

CCEGLView& CCEGLView::sharedOpenGLView()
{
	CC_ASSERT(s_pMainWindow);
	return *s_pMainWindow;
}

NS_CC_END;
