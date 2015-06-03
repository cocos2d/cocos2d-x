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
#include "CCEGLView-Win8_1.h"
#include "CCApplication.h"
#include "cocos2d.h"

// These are used by the shader compilation methods.
#include <vector>
#include <iostream>
#include <fstream>

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::Graphics::Display;

USING_NS_CC;


Cocos2dRenderer::Cocos2dRenderer(int width, int height, float dpi, CoreDispatcher^ dispatcher, Panel^ panel)
    : m_app(nullptr)
    , m_width(width)
    , m_height(height)
    , m_dpi(dpi)
    , m_orientation(DisplayOrientations::None)
    , m_dispatcher(dispatcher)
    , m_panel(panel)
{
    m_app = new AppDelegate();
    CCEGLView* pEGLView = new CCEGLView();
    pEGLView->Create(width, height);
    pEGLView->setViewName("Cocos2d-x");
    pEGLView->setDispatcher(dispatcher);
    pEGLView->setPanel(panel);
    CCApplication::sharedApplication()->run();
}

Cocos2dRenderer::~Cocos2dRenderer()
{
    delete m_app;
}

// Draws a basic triangle
void Cocos2dRenderer::Draw(GLsizei width, GLsizei height, Windows::Graphics::Display::DisplayOrientations orientation, float dpi)
{
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    if (width != m_width || height != m_height)
    {
        m_width = width;
        m_height = height;
        pEGLView->UpdateForWindowSizeChange(static_cast<float>(width), static_cast<float>(height));
    }

    if (dpi != m_dpi)
    {
        m_dpi = dpi;
        //CCEGLView::sharedOpenGLView()->SetDPI(m_dpi);
    }

    if (orientation != m_orientation)
    {
        m_orientation = orientation;
        pEGLView->UpdateOrientation(m_orientation);
    }

    pEGLView->Render();
}

void Cocos2dRenderer::QueuePointerEvent(cocos2d::PointerEventType type, Windows::UI::Core::PointerEventArgs^ args)
{
    CCEGLView::sharedOpenGLView()->QueuePointerEvent(type, args);
}

void Cocos2dRenderer::QueueKeyBoardEvent(cocos2d::Cocos2dKeyEvent type, Windows::UI::Core::KeyEventArgs^ e)
{
    //CCEGLView::sharedOpenGLView()->QueuePointerEvent(type, e);
}

void Cocos2dRenderer::QueueBackButtonEvent()
{
    CCEGLView::sharedOpenGLView()->QueueBackKeyPress();
}

bool Cocos2dRenderer::AppShouldExit()
{
    return CCEGLView::sharedOpenGLView()->AppShouldExit();
}