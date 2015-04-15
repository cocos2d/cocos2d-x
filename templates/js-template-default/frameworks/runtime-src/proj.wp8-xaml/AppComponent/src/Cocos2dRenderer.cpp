/****************************************************************************
Copyright (c) 2013 cocos2d-x.org
Copyright (c) Microsoft Open Technologies, Inc.

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

#include "Cocos2dRenderer.h"
#include "cocos2d.h"
#include "CCApplication.h"
#include "CCGLViewImpl-wp8.h"
#include "AppDelegate.h"
#include <ppltasks.h>

using namespace Concurrency;
using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;

USING_NS_CC;

Cocos2dRenderer::Cocos2dRenderer(Windows::Graphics::Display::DisplayOrientations orientation): mInitialized(false), m_loadingComplete(false), m_delegate(nullptr), m_messageBoxDelegate(nullptr)
{
    mApp = new AppDelegate();
    m_orientation = orientation;
}

// Creates and restores Cocos2d-x after DirectX and Angle contexts are created or updated
void Cocos2dRenderer::CreateGLResources()
{
    auto director = cocos2d::Director::getInstance();

    if(!mInitialized)
    {
        mInitialized = true;
        GLViewImpl* glview = GLViewImpl::create("Test JavaScript");
	    glview->Create(m_eglDisplay, m_eglContext, m_eglSurface, m_renderTargetSize.Width, m_renderTargetSize.Height,m_orientation);
        director->setOpenGLView(glview);
        glview->SetXamlEventDelegate(m_delegate);
        glview->SetXamlMessageBoxDelegate(m_messageBoxDelegate);
        glview->SetXamlEditBoxDelegate(m_editBoxDelegate);
        CCApplication::getInstance()->run();
    }
    else
    {
        cocos2d::GL::invalidateStateCache();
        cocos2d::ShaderCache::getInstance()->reloadDefaultGLPrograms();
        cocos2d::DrawPrimitives::init();
        cocos2d::VolatileTextureMgr::reloadAllTextures();
        cocos2d::EventCustom recreatedEvent(EVENT_RENDERER_RECREATED);
        director->getEventDispatcher()->dispatchEvent(&recreatedEvent);
        cocos2d::Application::getInstance()->applicationWillEnterForeground();
        director->setGLDefaultValues();
    }

    m_loadingComplete = true;
}

void Cocos2dRenderer::Connect()
{

}

// purge Cocos2d-x gl GL resourses since the DirectX/Angle Context has been lost 
void Cocos2dRenderer::Disconnect()
{
    Application::getInstance()->applicationDidEnterBackground();
    cocos2d::EventCustom backgroundEvent(EVENT_COME_TO_BACKGROUND);
    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&backgroundEvent); 
    CloseAngle();
    m_loadingComplete = false;
}

// save your game state here
IAsyncAction^ Cocos2dRenderer::OnSuspending()
{
    return create_async([]() { 
        // save your game state here
    });
}


void Cocos2dRenderer::OnUpdateDevice()
{
    //GLView* glview = GLView::sharedOpenGLView();
	GLViewImpl::sharedOpenGLView()->UpdateDevice(m_eglDisplay, m_eglContext, m_eglSurface);
}

void Cocos2dRenderer::OnOrientationChanged(Windows::Graphics::Display::DisplayOrientations orientation)
{
	DirectXBase::OnOrientationChanged(orientation);
    GLViewImpl::sharedOpenGLView()->UpdateOrientation(orientation);
}

// return true if eglSwapBuffers was called by OnRender()
bool Cocos2dRenderer::OnRender()
{
    if(m_loadingComplete)
    {
        //GLView* glview = GLView::sharedOpenGLView();
		GLViewImpl::sharedOpenGLView()->Render();
        return true; // eglSwapBuffers was called by glview->Render();
    }
    return false;
}

void Cocos2dRenderer::OnKeyPressed(Platform::String^ text)
{
    char szUtf8[8] = {0};
    int nLen = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)text->Data(), 1, szUtf8, sizeof(szUtf8), NULL, NULL);
    IMEDispatcher::sharedDispatcher()->dispatchInsertText(szUtf8, nLen);
}

void Cocos2dRenderer::OnCocos2dKeyEvent(Cocos2dKeyEvent event)
{
    switch(event)
    {
    case Cocos2dKeyEvent::Escape:
        //Director::getInstance()()->getKeypadDispatcher()->dispatchKeypadMSG(kTypeBackClicked);
        break;
	case Cocos2dKeyEvent::Back:
        IMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
        break;
    case Cocos2dKeyEvent::Enter:
		//SetFocus(false);
        IMEDispatcher::sharedDispatcher()->dispatchInsertText("\n", 1);
        break;
    default:
        break;
    }

}

void Cocos2dRenderer::SetXamlEventDelegate(Cocos2dEventDelegate^ delegate)
{
    m_delegate = delegate;
    GLViewImpl* eglView = GLViewImpl::sharedOpenGLView();
    if(eglView)
    {
        eglView->SetXamlEventDelegate(delegate);
    }
}

void Cocos2dRenderer::SetXamlMessageBoxDelegate(Cocos2dMessageBoxDelegate^ delegate)
{
    m_messageBoxDelegate = delegate;
    GLViewImpl* eglView = GLViewImpl::sharedOpenGLView();
    if(eglView)
    {
        eglView->SetXamlMessageBoxDelegate(delegate);
    }
}

void Cocos2dRenderer::SetXamlEditBoxDelegate(Cocos2dEditBoxDelegate^ delegate)
{
    m_editBoxDelegate = delegate;
    GLViewImpl* eglView = GLViewImpl::sharedOpenGLView();
    if(eglView)
    {
        eglView->SetXamlEditBoxDelegate(delegate);
    }
}

void Cocos2dRenderer::SetXamlOpenURLDelegate(Cocos2dOpenURLDelegate^ delegate)
{
    m_openURLDelegate = delegate;
    Application* app = Application::getInstance();
    if (app)
    {
        app->SetXamlOpenURLDelegate(delegate);
    }
}
