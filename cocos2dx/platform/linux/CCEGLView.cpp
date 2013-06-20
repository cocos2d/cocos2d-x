/*
 * EGLViewlinux.cpp
 *
 *  Created on: Aug 8, 2011
 *      Author: laschweinski
 */

#include "CCEGLView.h"
#include "CCGL.h"
#include "GL/glfw.h"
#include "ccMacros.h"
#include "CCDirector.h"
#include "touch_dispatcher/CCTouch.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "text_input_node/CCIMEDispatcher.h"
#ifdef KEYBOARD_SUPPORT
#include "keyboard_dispatcher/CCKeyboardDispatcher.h"
#endif

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

NS_CC_BEGIN

EGLView::EGLView()
: bIsInit(false)
, _frameZoomFactor(1.0f)
{
}

EGLView::~EGLView()
{
}

void keyEventHandle(int iKeyID,int iKeyState) {
	if (iKeyState ==GLFW_RELEASE) {
		return;
	}

	if (iKeyID == GLFW_KEY_DEL) {
		IMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
	} else if (iKeyID == GLFW_KEY_ENTER) {
		IMEDispatcher::sharedDispatcher()->dispatchInsertText("\n", 1);
	} else if (iKeyID == GLFW_KEY_TAB) {

	}
}

void charEventHandle(int iCharID,int iCharState) {
	if (iCharState ==GLFW_RELEASE) {
		return;
	}

	// ascii char
	IMEDispatcher::sharedDispatcher()->dispatchInsertText((const char *)&iCharID, 1);
}

void mouseButtonEventHandle(int iMouseID,int iMouseState) {
	if (iMouseID == GLFW_MOUSE_BUTTON_LEFT) {
        EGLView* pEGLView = EGLView::sharedOpenGLView();
		//get current mouse pos
		int x,y;
		glfwGetMousePos(&x, &y);
		Point oPoint((float)x,(float)y);
		/*
		if (!Rect::RectContainsPoint(s_pMainWindow->_rcViewPort,oPoint))
		{
			CCLOG("not in the viewport");
			return;
		}
		*/
         oPoint.x /= pEGLView->_frameZoomFactor;
         oPoint.y /= pEGLView->_frameZoomFactor;
		int id = 0;
		if (iMouseState == GLFW_PRESS) {
			pEGLView->handleTouchesBegin(1, &id, &oPoint.x, &oPoint.y);

		} else if (iMouseState == GLFW_RELEASE) {
			pEGLView->handleTouchesEnd(1, &id, &oPoint.x, &oPoint.y);
		}
	}
}

void mousePosEventHandle(int iPosX,int iPosY) {
	int iButtonState = glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT);

	//to test move
	if (iButtonState == GLFW_PRESS) {
            EGLView* pEGLView = EGLView::sharedOpenGLView();
            int id = 0;
            float x = (float)iPosX;
            float y = (float)iPosY;
            x /= pEGLView->_frameZoomFactor;
            y /= pEGLView->_frameZoomFactor;
            pEGLView->handleTouchesMove(1, &id, &x, &y);
	}
}

int closeEventHandle() {
	Director::sharedDirector()->end();
	return GL_TRUE;
}

#ifdef KEYBOARD_SUPPORT
void GLFWCALL keyboardEventHandle(int keyCode, int action)
{
    KeyboardDispatcher *kbDisp = Director::sharedDirector()->getKeyboardDispatcher();

    switch (action)
    {   
        case GLFW_PRESS:
            kbDisp->dispatchKeyboardEvent(keyCode, true);
            break;
        case GLFW_RELEASE:
            kbDisp->dispatchKeyboardEvent(keyCode, false);
            break;
    }   
}
#endif

void EGLView::setFrameSize(float width, float height)
{
	bool eResult = false;
	int u32GLFWFlags = GLFW_WINDOW;
	//create the window by glfw.

	//check
	CCAssert(width!=0&&height!=0, "invalid window's size equal 0");

	//Inits GLFW
	eResult = glfwInit() != GL_FALSE;

	if (!eResult) {
		CCAssert(0, "fail to init the glfw");
	}

	/* Updates window hint */
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);

	int iDepth = 16; // set default value
	/* Depending on video depth */
	switch(iDepth)
	{
		/* 16-bit */
		case 16:
		{
			/* Updates video mode */
			eResult = (glfwOpenWindow(width, height, 5, 6, 5, 0, 16, 8, (int)u32GLFWFlags) != false) ? true : false;

			break;
		}

		/* 24-bit */
		case 24:
		{
			/* Updates video mode */
			eResult = (glfwOpenWindow(width, height, 8, 8, 8, 0, 16, 8, (int)u32GLFWFlags) != false) ? true : false;

			break;
		}

		/* 32-bit */
		default:
		case 32:
		{
			/* Updates video mode */
			eResult = (glfwOpenWindow(width, height, 8, 8, 8, 8, 16, 8, (int)u32GLFWFlags) != GL_FALSE) ? true :false;
			break;
		}
	}

	/* Success? */
	if(eResult)
	{

		/* Updates actual size */
	  //		glfwGetWindowSize(&width, &height);

		EGLViewProtocol::setFrameSize(width, height);		

		/* Updates its title */
		glfwSetWindowTitle("Cocos2dx-Linux");

		//set the init flag
		bIsInit = true;

		//register the glfw key event
		glfwSetKeyCallback(keyEventHandle);
		//register the glfw char event
		glfwSetCharCallback(charEventHandle);
		//register the glfw mouse event
		glfwSetMouseButtonCallback(mouseButtonEventHandle);
		//register the glfw mouse pos event
		glfwSetMousePosCallback(mousePosEventHandle);
#ifdef KEYBOARD_SUPPORT
        //register the glfw keyboard event
        glfwSetKeyCallback(keyboardEventHandle);
#endif

		glfwSetWindowCloseCallback(closeEventHandle);

		//Inits extensions
		eResult = initExtensions();

		if (!eResult) {
			CCAssert(0, "fail to init the extensions of opengl");
		}
		initGL();
	}
}

void EGLView::setFrameZoomFactor(float fZoomFactor)
{
    _frameZoomFactor = fZoomFactor;
    glfwSetWindowSize(_screenSize.width * fZoomFactor, _screenSize.height * fZoomFactor);
    Director::sharedDirector()->setProjection(Director::sharedDirector()->getProjection());
}

float EGLView::getFrameZoomFactor()
{
    return _frameZoomFactor;
}

void EGLView::setViewPortInPoints(float x , float y , float w , float h)
{
    glViewport((GLint)(x * _scaleX * _frameZoomFactor+ _viewPortRect.origin.x * _frameZoomFactor),
        (GLint)(y * _scaleY * _frameZoomFactor + _viewPortRect.origin.y * _frameZoomFactor),
        (GLsizei)(w * _scaleX * _frameZoomFactor),
        (GLsizei)(h * _scaleY * _frameZoomFactor));
}

void EGLView::setScissorInPoints(float x , float y , float w , float h)
{
    glScissor((GLint)(x * _scaleX * _frameZoomFactor + _viewPortRect.origin.x * _frameZoomFactor),
              (GLint)(y * _scaleY * _frameZoomFactor + _viewPortRect.origin.y * _frameZoomFactor),
              (GLsizei)(w * _scaleX * _frameZoomFactor),
              (GLsizei)(h * _scaleY * _frameZoomFactor));
}


bool EGLView::isOpenGLReady()
{
	return bIsInit;
}

void EGLView::end()
{
	/* Exits from GLFW */
	glfwTerminate();
	delete this;
	exit(0);
}

void EGLView::swapBuffers() {
	if (bIsInit) {
		/* Swap buffers */
		glfwSwapBuffers();
	}
}

void EGLView::setIMEKeyboardState(bool bOpen) {

}

bool EGLView::initGL()
{
    GLenum GlewInitResult = glewInit();
    if (GLEW_OK != GlewInitResult) 
    {
        fprintf(stderr,"ERROR: %s\n",glewGetErrorString(GlewInitResult));
        return false;
    }

    if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
    {
        CCLog("Ready for GLSL");
    }
    else 
    {
        CCLog("Not totally ready :(");
    }

    if (glewIsSupported("GL_VERSION_2_0"))
    {
        CCLog("Ready for OpenGL 2.0");
    }
    else
    {
        CCLog("OpenGL 2.0 not supported");
    }

    // Enable point size by default on linux.
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

    return true;
}

void EGLView::destroyGL()
{
	/*
    if (_DC != NULL && _RC != NULL)
    {
        // deselect rendering context and delete it
        wglMakeCurrent(_DC, NULL);
        wglDeleteContext(_RC);
    }
	*/
}

EGLView* EGLView::sharedOpenGLView()
{
    static EGLView* s_pEglView = NULL;
    if (s_pEglView == NULL)
    {
        s_pEglView = new EGLView();
    }
    return s_pEglView;
}

NS_CC_END
