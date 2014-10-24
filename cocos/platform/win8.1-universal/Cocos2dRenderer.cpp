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

// These are used by the shader compilation methods.
#include <vector>
#include <iostream>
#include <fstream>

using namespace Platform;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::Graphics::Display;

USING_NS_CC;


Cocos2dRenderer::Cocos2dRenderer(const int width, const int height, CoreDispatcher^ dispatcher, Panel^ panel)
    : mApp(nullptr)
    , mWidth(width)
    , mHeight(height)
    , m_dispatcher(dispatcher)
    , m_panel(panel)
{
    mApp = new AppDelegate();
    auto director = cocos2d::Director::getInstance();

    GLViewImpl* glview = GLViewImpl::create("Test Cpp");
    glview->setDispatcher(dispatcher);
    glview->setPanel(panel);
    glview->Create(static_cast<float>(width), static_cast<float>(height), DisplayOrientations::Landscape);
    director->setOpenGLView(glview);
    CCApplication::getInstance()->run();
}

Cocos2dRenderer::~Cocos2dRenderer()
{
    delete mApp;
}

// Draws a basic triangle
void Cocos2dRenderer::Draw(GLsizei width, GLsizei height)
{
    if (width != mWidth || height != mHeight)
    {
        mWidth = width;
        mHeight = height;
        GLViewImpl::sharedOpenGLView()->UpdateForWindowSizeChange(static_cast<float>(width), static_cast<float>(height));
    }

    GLViewImpl::sharedOpenGLView()->ProcessEvents();
    GLViewImpl::sharedOpenGLView()->Render();
}

void Cocos2dRenderer::QueuePointerEvent(cocos2d::PointerEventType type, Windows::UI::Core::PointerEventArgs^ args)
{
    GLViewImpl::sharedOpenGLView()->QueuePointerEvent(type, args);
}

void Cocos2dRenderer::QueueKeyBoardEvent(cocos2d::Cocos2dKeyEvent type, Windows::UI::Core::KeyEventArgs^ e)
{
    //GLViewImpl::sharedOpenGLView()->QueuePointerEvent(type, e);
}


