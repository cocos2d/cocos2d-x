/****************************************************************************
Copyright (c) 2010      cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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
#include "CCGLView.h"
#include "2d/ccUtils.h"
#include "2d/platform/CCImage.h"
#include "2d/platform/CCFileUtils.h"
#include "base/ccMacros.h"
#include "base/CCDirector.h"
#include "renderer/CCRenderer.h"

NS_CC_BEGIN

int ccNextPOT(int x)
{
    x = x - 1;
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >>16);
    return x + 1;
}
   
UtilsHelper* UtilsHelper::s_sharedHelper = nullptr;

UtilsHelper::UtilsHelper()
{
}
    
UtilsHelper::~UtilsHelper()
{
}
    
UtilsHelper* UtilsHelper::getInstance()
{
    if (!s_sharedHelper)
    {
        s_sharedHelper = new UtilsHelper();
    }
    return s_sharedHelper;
}
    
void UtilsHelper::destroyInstance()
{
    CC_SAFE_DELETE(s_sharedHelper);
}

    
void UtilsHelper::captureScreen(const std::function<void(bool, const std::string&)>& afterCaptured, const std::string& filename, const Rect& rect)
{
    _captureScreen.init(std::numeric_limits<float>::max());
    _captureScreen.func = CC_CALLBACK_0(UtilsHelper::onCaptureScreen, this, afterCaptured, filename, rect);
    Director::getInstance()->getRenderer()->addCommand(&_captureScreen);
}

void UtilsHelper::onCaptureScreen(const std::function<void(bool, const std::string&)>& afterCaptured, const std::string& filename, const Rect& rect)
{
    // Generally the user specifiy the rect with design resolution, thus we have to convert it
    // into a significant value which is metered by pixel.
    Size frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
    int originx = 0;
    int originy = 0;
    int width = (int)frameSize.width;
    int height = (int)frameSize.height;
    bool succeed = false;
    std::string outputFile = "";
    
    if (!rect.equals(Rect::ZERO))
    {
        originx = (int)rect.origin.x;
        originy = (int)rect.origin.y;
        width = (int)rect.size.width * Director::getInstance()->getOpenGLView()->getScaleX();
        height = (int)rect.size.height * Director::getInstance()->getOpenGLView()->getScaleY();
        
        auto clip = [](int in, int min, int max) { return std::max(std::min(in, max), min); };
        originx = clip(originx, 0, (int)frameSize.width);
        originy = clip(originy, 0, (int)frameSize.height);
        width = clip(width, 0, frameSize.width - originx);
        height = clip(height, 0, frameSize.height - originy);
    }
    
    do
    {
        GLubyte* buffer = new GLubyte[width * height * 4];
        if (!buffer)
        {
            break;
        }
        
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glReadPixels(originx, originy, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
        
        GLubyte* flippedBuffer = new GLubyte[width * height * 4];
        if (!flippedBuffer)
        {
            break;
        }
        
        for (int row = 0; row < height; ++row)
        {
            memcpy(flippedBuffer + (height - row - 1) * width * 4, buffer + row * width * 4, width * 4);
        }
        CC_SAFE_DELETE_ARRAY(buffer);
        
        Image* image = new Image();
        if (image)
        {
            image->initWithRawData(flippedBuffer, width * height * 4, width, height, 8);
            if (FileUtils::getInstance()->isAbsolutePath(filename))
            {
                outputFile = filename;
            }
            else
            {
                outputFile = FileUtils::getInstance()->getWritablePath() + filename;
            }
            image->saveToFile(outputFile);
            succeed = true;
        }
        CC_SAFE_DELETE_ARRAY(flippedBuffer);
        CC_SAFE_DELETE(image);
    }while(0);
    
    if (afterCaptured)
    {
        afterCaptured(succeed, outputFile);
    }
}

NS_CC_END