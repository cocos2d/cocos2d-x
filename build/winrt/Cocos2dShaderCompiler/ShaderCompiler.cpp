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

#include "ShaderCompiler.h"
#include "cocos2d.h"
#include "CCPrecompiledShaders.h"

using namespace Concurrency;
using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;

USING_NS_CC;

ShaderCompiler::ShaderCompiler() 
    : m_display(nullptr), 
    m_context(nullptr), 
    m_initialized(false),
    m_resultText(nullptr)
{

}

ShaderCompiler::~ShaderCompiler()
{

    CloseAngle();

}

bool ShaderCompiler::applicationDidFinishLaunching()
{
    return true;
}

void ShaderCompiler::applicationDidEnterBackground()
{

}

void ShaderCompiler::applicationWillEnterForeground()
{


}


bool ShaderCompiler::Compile(Windows::UI::Xaml::Controls::TextBlock^ resultText)
{
    m_resultText = resultText;
    resultText->Text = "Compiling shaders...";

    if (!InitializeAngle(ANGLE_D3D_FEATURE_LEVEL::ANGLE_D3D_FEATURE_LEVEL_9_3))
    {
        resultText->Text = "Unable to initialize Angle";
        return false;
    }

    Director::getInstance()->setAnimationInterval(1.0 / 60.0);
    CCShaderCache::getInstance()->loadDefaultShaders();
    CCPrecompiledShaders::getInstance()->savePrecompiledShaders();
    resultText->Text = "Complete";
    return true;
}


// Creates and restores Cocos2d-x after DirectX and Angle contexts are created or updated
void ShaderCompiler::InitializeCocos2d()
{


}

void ShaderCompiler::CloseAngle()
{
    eglMakeCurrent(NULL, NULL, NULL, NULL);

    if (m_display && m_context)
    {
        eglDestroyContext(m_context, m_context);
    }
    if (m_display)
    {
        eglTerminate(m_display);
    }

    m_eglWindow = nullptr;

}

bool ShaderCompiler::InitializeAngle(ANGLE_D3D_FEATURE_LEVEL featureLevel)
{
    // setup EGL
    EGLint configAttribList[] = {
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_DEPTH_SIZE, 8,
        EGL_STENCIL_SIZE, 8,
        EGL_SAMPLE_BUFFERS, 0,
        EGL_NONE
    };

    EGLint surfaceAttribList[] = {
        EGL_NONE, EGL_NONE
    };

    EGLint numConfigs;
    EGLint majorVersion;
    EGLint minorVersion;
    EGLConfig config;
    EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };

    IUnknown* dummy = nullptr;
    HRESULT result = CreateWinrtEglWindow(WINRT_EGL_IUNKNOWN(dummy), featureLevel, m_eglWindow.GetAddressOf());
    if (!SUCCEEDED(result))
    {
        return false;
    }

    m_display = eglGetDisplay(m_eglWindow);
    if (m_display == EGL_NO_DISPLAY){
        return false;
    }

    if (!eglInitialize(m_display, &majorVersion, &minorVersion)){
        return false;
    }

    // Get configs
    if (!eglGetConfigs(m_display, NULL, 0, &numConfigs)){
        return false;
    }

    // Choose config
    if (!eglChooseConfig(m_display, configAttribList, &config, 1, &numConfigs)){
        return false;
    }

    // Create a GL context
    m_context = eglCreateContext(m_display, config, EGL_NO_CONTEXT, contextAttribs);
    if (m_context == EGL_NO_CONTEXT){
        return false;
    }

    // Make the context current
    // Note: we are not using a surface
    if (!eglMakeCurrent(m_display, NULL, NULL, m_context)){
        return false;
    }

    return true;
}





