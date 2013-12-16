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

void Cocos2dRenderer::CreateDeviceResources()
{
	DirectXBase::CreateDeviceResources();
}

void Cocos2dRenderer::CreateGLResources()
{
    if(!mInitialized)
    {
        mInitialized = true;
        CCEGLView* pEGLView = new CCEGLView();
	    pEGLView->Create(m_eglDisplay, m_eglContext, m_eglSurface, m_renderTargetSize.Width, m_renderTargetSize.Height);
 		//pEGLView->UpdateOrientation(mCurrentOrientation);
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
    }
    m_loadingComplete = true;




}

IAsyncAction^ Cocos2dRenderer::OnSuspending()
{
    return create_async([]() { });
}

void Cocos2dRenderer::OnResuming()
{

}

bool Cocos2dRenderer::OnBackPressed()
{
    return false;
}

void Cocos2dRenderer::OnUpdateDevice()
{
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    pEGLView->UpdateDevice(m_eglDisplay, m_eglContext, m_eglSurface);
}

void Cocos2dRenderer::CreateWindowSizeDependentResources()
{
	DirectXBase::CreateWindowSizeDependentResources();
}

void Cocos2dRenderer::OnOrientationChanged(Windows::Graphics::Display::DisplayOrientations orientation)
{
	DirectXBase::OnOrientationChanged(orientation);
    CCEGLView::sharedOpenGLView()->UpdateOrientation(orientation);
}

void Cocos2dRenderer::Update(float timeTotal, float timeDelta)
{
	(void) timeTotal;
	(void) timeDelta;
}

bool Cocos2dRenderer::OnRender()
{
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    pEGLView->Render();
    return true; // eglSwapBuffers was called by pEGLView->Render();
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



