//            Based on Hello_Triangle.c from
// Book:      OpenGL(R) ES 2.0 Programming Guide
// Authors:   Aaftab Munshi, Dan Ginsburg, Dave Shreiner
// ISBN-10:   0321502795
// ISBN-13:   9780321502797
// Publisher: Addison-Wesley Professional
// URLs:      http://safari.informit.com/9780321563835
//            http://www.opengles-book.com

//
// This file is used by the template to render a basic scene using GL.
//

#include "pch.h"
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

using namespace Windows::Graphics::Display;

USING_NS_CC;


Cocos2dRenderer::Cocos2dRenderer(const int width, const int height, CoreDispatcher^ dispatcher)
    : mApp(nullptr)
    , mWidth(width)
    , mHeight(height)
    , m_dispatcher(dispatcher)
{
    mApp = new AppDelegate();
    auto director = cocos2d::Director::getInstance();

    GLViewImpl* glview = GLViewImpl::create("Test Cpp");
    glview->setDispatcher(dispatcher);
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


