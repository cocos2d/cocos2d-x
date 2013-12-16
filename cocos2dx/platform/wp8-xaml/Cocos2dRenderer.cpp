#include "pch.h"
#include "Cocos2dRenderer.h"
#include "cocos2d.h"
#include "CCApplication.h"
#include "CCEGLView.h"
#include "support/CCNotificationCenter.h"


#include <ppltasks.h>

using namespace Concurrency;

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;
USING_NS_CC;

Cocos2dRenderer::Cocos2dRenderer(): mInitialized(false), m_loadingComplete(false)
{
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
    // Handled in CreateGLResources()
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

// restore your game state here
void Cocos2dRenderer::OnResuming()
{

}

// user pressed the Back Key on the phone
bool Cocos2dRenderer::OnBackKeyPress()
{
    return false;
}

void Cocos2dRenderer::OnFocusChange(bool active)
{
   if(active)
   {
        CCDirector::sharedDirector()->resume(); 
   }
   else
   {
        CCDirector::sharedDirector()->pause(); 
   }
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



