/*
* cocos2d-x   http://www.cocos2d-x.org
*
* Copyright (c) 2010-2014 - cocos2d-x community
*
* Portions Copyright (c) Microsoft Open Technologies, Inc.
* All Rights Reserved
*
* Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an
* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and limitations under the License.
*/

#include "Cocos2dRenderer.h"
#include "AppDelegate.h"
#include "CCGLViewImpl-winrt.h"
#include "CCApplication.h"
#include "cocos2d.h"
#include "renderer/CCTextureCache.h"

// These are used by the shader compilation methods.
#include <vector>
#include <iostream>
#include <fstream>

using namespace Platform;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::Graphics::Display;
using namespace cocos2d;

Cocos2dRenderer::Cocos2dRenderer(int width, int height, float dpi, DisplayOrientations orientation, CoreDispatcher^ dispatcher, Panel^ panel)
    : m_app(nullptr)
    , m_width(width)
    , m_height(height)
    , m_dpi(dpi)
    , m_dispatcher(dispatcher)
    , m_panel(panel)
    , m_orientation(orientation)
{
    m_app = new AppDelegate();
}

Cocos2dRenderer::~Cocos2dRenderer()
{
    delete m_app;
}

void Cocos2dRenderer::Resume()
{
    auto director = cocos2d::Director::getInstance();
    auto glview = director->getOpenGLView();

    if (!glview) 
    {
        GLViewImpl* glview = GLViewImpl::create("Test Cpp");
        glview->setDispatcher(m_dispatcher.Get());
        glview->setPanel(m_panel.Get());
        glview->Create(static_cast<float>(m_width), static_cast<float>(m_height), m_dpi, m_orientation);
        director->setOpenGLView(glview);
        CCApplication::getInstance()->run();
    }
    else
    {
        Application::getInstance()->applicationWillEnterForeground();
        cocos2d::EventCustom foregroundEvent(EVENT_COME_TO_FOREGROUND);
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&foregroundEvent);
    }
}

void Cocos2dRenderer::Pause()
{
    if (Director::getInstance()->getOpenGLView()) {
        Application::getInstance()->applicationDidEnterBackground();
        cocos2d::EventCustom backgroundEvent(EVENT_COME_TO_BACKGROUND);
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&backgroundEvent);
    }
}

bool Cocos2dRenderer::AppShouldExit()
{
    return GLViewImpl::sharedOpenGLView()->AppShouldExit();
}

void Cocos2dRenderer::DeviceLost()
{
    Pause();

    auto director = cocos2d::Director::getInstance();
    if (director->getOpenGLView()) {
        cocos2d::GL::invalidateStateCache();
        cocos2d::GLProgramCache::getInstance()->reloadDefaultGLPrograms();
        cocos2d::DrawPrimitives::init();
        cocos2d::VolatileTextureMgr::reloadAllTextures();

        cocos2d::EventCustom recreatedEvent(EVENT_RENDERER_RECREATED);
        director->getEventDispatcher()->dispatchEvent(&recreatedEvent);
        director->setGLDefaultValues();

        Application::getInstance()->applicationWillEnterForeground();
        cocos2d::EventCustom foregroundEvent(EVENT_COME_TO_FOREGROUND);
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&foregroundEvent);
    }
}



void Cocos2dRenderer::Draw(GLsizei width, GLsizei height, float dpi, DisplayOrientations orientation)
{
    auto glView = GLViewImpl::sharedOpenGLView();

    if (orientation != m_orientation)
    {
        m_orientation = orientation;
        glView->UpdateOrientation(orientation);
    }

    if (width != m_width || height != m_height)
    {
        m_width = width;
        m_height = height;
        glView->UpdateForWindowSizeChange(static_cast<float>(width), static_cast<float>(height));
    }

    if (dpi != m_dpi)
    {
        m_dpi = dpi;
        glView->SetDPI(m_dpi);
    }

    glView->ProcessEvents();
    glView->Render();
}

void Cocos2dRenderer::QueuePointerEvent(cocos2d::PointerEventType type, Windows::UI::Core::PointerEventArgs^ args)
{
    GLViewImpl::sharedOpenGLView()->QueuePointerEvent(type, args);
}

void Cocos2dRenderer::QueueBackButtonEvent()
{
    GLViewImpl::sharedOpenGLView()->QueueBackKeyPress();
}

void Cocos2dRenderer::QueueKeyboardEvent(WinRTKeyboardEventType type, Windows::UI::Core::KeyEventArgs^ args)
{
	GLViewImpl::sharedOpenGLView()->QueueWinRTKeyboardEvent(type, args);
}



