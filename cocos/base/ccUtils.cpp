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

#include "base/ccUtils.h"

#include <stdlib.h>

#include "base/CCDirector.h"
#include "base/CCAsyncTaskPool.h"
#include "base/CCEventDispatcher.h"
#include "renderer/CCCustomCommand.h"
#include "renderer/CCRenderer.h"
#include "platform/CCImage.h"
#include "platform/CCFileUtils.h"

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

namespace utils
{
/**
* Capture screen implementation, don't use it directly.
*/
void onCaptureScreen(const std::function<void(bool, const std::string&)>& afterCaptured, const std::string& filename)
{
    static bool startedCapture = false;

    if (startedCapture)
    {
        CCLOG("Screen capture is already working");
        if (afterCaptured)
        {
            afterCaptured(false, filename);
        }
        return;
    }
    else
    {
        startedCapture = true;
    }


    auto glView = Director::getInstance()->getOpenGLView();
    auto frameSize = glView->getFrameSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    frameSize = frameSize * glView->getFrameZoomFactor() * glView->getRetinaFactor();
#endif

    int width = static_cast<int>(frameSize.width);
    int height = static_cast<int>(frameSize.height);

    bool succeed = false;
    std::string outputFile = "";

    do
    {
        std::shared_ptr<GLubyte> buffer(new GLubyte[width * height * 4], [](GLubyte* p){ CC_SAFE_DELETE_ARRAY(p); });
        if (!buffer)
        {
            break;
        }

        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer.get());

        std::shared_ptr<GLubyte> flippedBuffer(new GLubyte[width * height * 4], [](GLubyte* p) { CC_SAFE_DELETE_ARRAY(p); });
        if (!flippedBuffer)
        {
            break;
        }

        for (int row = 0; row < height; ++row)
        {
            memcpy(flippedBuffer.get() + (height - row - 1) * width * 4, buffer.get() + row * width * 4, width * 4);
        }

        Image* image = new (std::nothrow) Image;
        if (image)
        {
            image->initWithRawData(flippedBuffer.get(), width * height * 4, width, height, 8);
            if (FileUtils::getInstance()->isAbsolutePath(filename))
            {
                outputFile = filename;
            }
            else
            {
                CCASSERT(filename.find("/") == std::string::npos, "The existence of a relative path is not guaranteed!");
                outputFile = FileUtils::getInstance()->getWritablePath() + filename;
            }

            // Save image in AsyncTaskPool::TaskType::TASK_IO thread, and call afterCaptured in mainThread
            static bool succeedSaveToFile = false;
            std::function<void(void*)> mainThread = [afterCaptured, outputFile](void* param)
            {
                if (afterCaptured)
                {
                    afterCaptured(succeedSaveToFile, outputFile);
                }
                startedCapture = false;
            };

            AsyncTaskPool::getInstance()->enqueue(AsyncTaskPool::TaskType::TASK_IO, mainThread, (void*)NULL, [image, outputFile]()
            {
                succeedSaveToFile = image->saveToFile(outputFile);
                delete image;
            });
        }
        else
        {
            CCLOG("Malloc Image memory failed!");
            if (afterCaptured)
            {
                afterCaptured(succeed, outputFile);
            }
            startedCapture = false;
        }
    } while (0);
}

/*
 * Capture screen interface
 */
static EventListenerCustom* s_captureScreenListener;
static CustomCommand s_captureScreenCommand;
void captureScreen(const std::function<void(bool, const std::string&)>& afterCaptured, const std::string& filename)
{
    if (s_captureScreenListener)
    {
        CCLOG("Warning: CaptureScreen has been caled yet, don't call more than once in one frame.");
        return;
    }
    s_captureScreenCommand.init(std::numeric_limits<float>::max());
    s_captureScreenCommand.func = std::bind(onCaptureScreen, afterCaptured, filename);
    s_captureScreenListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(Director::EVENT_AFTER_DRAW, [](EventCustom *event) {
        auto director = Director::getInstance();
        director->getEventDispatcher()->removeEventListener((EventListener*)(s_captureScreenListener));
        s_captureScreenListener = nullptr;
        director->getRenderer()->addCommand(&s_captureScreenCommand);
        director->getRenderer()->render();
    });
}

std::vector<Node*> findChildren(const Node &node, const std::string &name)
{
    std::vector<Node*> vec;
    
    node.enumerateChildren(name, [&vec](Node* nodeFound) -> bool {
        vec.push_back(nodeFound);
        return false;
    });

    return vec;
}

#define MAX_ITOA_BUFFER_SIZE 256
double atof(const char* str)
{
    if (str == nullptr)
    {
        return 0.0;
    }
    
    char buf[MAX_ITOA_BUFFER_SIZE];
    strncpy(buf, str, MAX_ITOA_BUFFER_SIZE);
    
    // strip string, only remain 7 numbers after '.'
    char* dot = strchr(buf, '.');
    if (dot != nullptr && dot - buf + 8 <  MAX_ITOA_BUFFER_SIZE)
    {
        dot[8] = '\0';
    }
    
    return ::atof(buf);
}

double gettime()
{
    struct timeval tv;
    gettimeofday(&tv, nullptr);

    return (double)tv.tv_sec + (double)tv.tv_usec/1000000;
}

long long getTimeInMilliseconds()
{
    struct timeval tv;
    gettimeofday (&tv, nullptr);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

Rect getCascadeBoundingBox(Node *node)
{
    Rect cbb;
    Size contentSize = node->getContentSize();
    
    // check all childrens bounding box, get maximize box
    Node* child = nullptr;
    bool merge = false;
    for(auto object : node->getChildren())
    {
        child = dynamic_cast<Node*>(object);
        if (!child->isVisible()) continue;
        
        const Rect box = getCascadeBoundingBox(child);
        if (box.size.width <= 0 || box.size.height <= 0) continue;
        
        if (!merge)
        {
            cbb = box;
            merge = true;
        }
        else
        {
            cbb.merge(box);
        }
    }
    
    // merge content size
    if (contentSize.width > 0 && contentSize.height > 0)
    {
        const Rect box = RectApplyAffineTransform(Rect(0, 0, contentSize.width, contentSize.height), node->getNodeToWorldAffineTransform());
        if (!merge)
        {
            cbb = box;
        }
        else
        {
            cbb.merge(box);
        }
    }
    
    return cbb;
}
    
}

NS_CC_END
