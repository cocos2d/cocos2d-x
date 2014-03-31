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
#include "CCEGLView.h"
#include "AppDelegate.h"
#include <ppltasks.h>

using namespace Concurrency;
using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;
using namespace PhoneDirect3DXamlAppComponent;

USING_NS_CC;

Cocos2dRenderer::Cocos2dRenderer(): mInitialized(false), m_loadingComplete(false), m_delegate(nullptr), m_messageBoxDelegate(nullptr)
{
    mApp = new AppDelegate();
}

// Creates and restores Cocos2d-x after DirectX and Angle contexts are created or updated
void Cocos2dRenderer::CreateGLResources()
{
    if(!mInitialized)
    {
        mInitialized = true;
        CCEGLView* pEGLView = new CCEGLView();
	    pEGLView->Create(m_eglDisplay, m_eglContext, m_eglSurface, m_renderTargetSize.Width, m_renderTargetSize.Height);
        pEGLView->setViewName("Cocos2d-x");
        CCApplication::sharedApplication()->run();
        pEGLView->SetXamlEventDelegate(m_delegate);
        pEGLView->SetXamlMessageBoxDelegate(m_messageBoxDelegate);
        pEGLView->SetXamlEditBoxDelegate(m_editBoxDelegate);
   }
    else
    {
        ccGLInvalidateStateCache();
        CCShaderCache::sharedShaderCache()->reloadDefaultShaders();
        ccDrawInit();
        CCTextureCache::sharedTextureCache()->reloadAllTextures();
        CCNotificationCenter::sharedNotificationCenter()->postNotification(EVENT_COME_TO_FOREGROUND, NULL);
        CCDirector::sharedDirector()->setGLDefaultValues(); 
        CCDirector::sharedDirector()->resume(); 
   }

    m_loadingComplete = true;
}

void Cocos2dRenderer::Connect()
{
}

// purge Cocos2d-x gl GL resourses since the DirectX/Angle Context has been lost 
void Cocos2dRenderer::Disconnect()
{
    CCDirector::sharedDirector()->pause(); 
    CCDirector::sharedDirector()->purgeCachedData(); 
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


// user pressed the Back Key on the phone
void Cocos2dRenderer::OnBackKeyPress()
{
    // handle the backkey in your app here.
    // call Cocos2dEvent::TerminateApp if it is time to exit your app.
    // ie. the user is on your first page and wishes to exit your app.
    // uncomment next line and comment TerminateApp to respond with keyBackClicked() in layers, remember to add init layer use setKeypadEnabled(true)
    // CCDirector::sharedDirector()->getKeypadDispatcher()->dispatchKeypadMSG( ccKeypadMSGType::kTypeBackClicked );
    m_delegate->Invoke(Cocos2dEvent::TerminateApp);
}

void Cocos2dRenderer::OnUpdateDevice()
{
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    pEGLView->UpdateDevice(m_eglDisplay, m_eglContext, m_eglSurface);
}

void Cocos2dRenderer::OnOrientationChanged(Windows::Graphics::Display::DisplayOrientations orientation)
{
	DirectXBase::OnOrientationChanged(orientation);
    CCEGLView::sharedOpenGLView()->UpdateOrientation(orientation);
}

// return true if eglSwapBuffers was called by OnRender()
bool Cocos2dRenderer::OnRender()
{
    if(m_loadingComplete)
    {
        CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
        pEGLView->Render();
        return true; // eglSwapBuffers was called by pEGLView->Render();
    }
    return false;
}

void Cocos2dRenderer::OnPointerPressed(PointerEventArgs^ args)
{
    CCEGLView::sharedOpenGLView()->OnPointerPressed(args);
}

void Cocos2dRenderer::OnPointerMoved(PointerEventArgs^ args)
{
    CCEGLView::sharedOpenGLView()->OnPointerMoved(args);
}

void Cocos2dRenderer::OnPointerReleased(PointerEventArgs^ args)
{
    CCEGLView::sharedOpenGLView()->OnPointerReleased(args);
}

void Cocos2dRenderer::OnKeyPressed(Platform::String^ text)
{
    char szUtf8[8] = {0};
    int nLen = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)text->Data(), 1, szUtf8, sizeof(szUtf8), NULL, NULL);
    CCIMEDispatcher::sharedDispatcher()->dispatchInsertText(szUtf8, nLen);
}


void Cocos2dRenderer::OnCocos2dKeyEvent(Cocos2dKeyEvent event)
{
    switch(event)
    {
    case Cocos2dKeyEvent::Escape:
        CCDirector::sharedDirector()->getKeypadDispatcher()->dispatchKeypadMSG(kTypeBackClicked);
        break;
	case Cocos2dKeyEvent::Back:
        CCIMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
        break;
    case Cocos2dKeyEvent::Enter:
		//SetFocus(false);
        CCIMEDispatcher::sharedDispatcher()->dispatchInsertText("\n", 1);
        break;
    default:
        break;
    }

}

void Cocos2dRenderer::SetXamlEventDelegate(PhoneDirect3DXamlAppComponent::Cocos2dEventDelegate^ delegate)
{
    m_delegate = delegate;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    if(eglView)
    {
        eglView->SetXamlEventDelegate(delegate);
    }
}

void Cocos2dRenderer::SetXamlMessageBoxDelegate(PhoneDirect3DXamlAppComponent::Cocos2dMessageBoxDelegate^ delegate)
{
    m_messageBoxDelegate = delegate;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    if(eglView)
    {
        eglView->SetXamlMessageBoxDelegate(delegate);
    }
}

void Cocos2dRenderer::SetXamlEditBoxDelegate(PhoneDirect3DXamlAppComponent::Cocos2dEditBoxDelegate^ delegate)
{
    m_editBoxDelegate = delegate;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    if(eglView)
    {
        eglView->SetXamlEditBoxDelegate(delegate);
    }
}





