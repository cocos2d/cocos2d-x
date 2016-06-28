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
#include "base/base64.h"
#include "renderer/CCCustomCommand.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCTextureCache.h"

#include "platform/CCImage.h"
#include "platform/CCFileUtils.h"
#include "2d/CCSprite.h"
#include "2d/CCRenderTexture.h"

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
        CCLOG("Warning: CaptureScreen has been called already, don't call more than once in one frame.");
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

Image* captureNode(Node* startNode, float scale)
{ // The best snapshot API, support Scene and any Node
    auto& size = startNode->getContentSize();

    Director::getInstance()->setNextDeltaTimeZero(true);

    RenderTexture* finalRtx = nullptr;

    auto rtx = RenderTexture::create(size.width, size.height, Texture2D::PixelFormat::RGBA8888, GL_DEPTH24_STENCIL8);
    // rtx->setKeepMatrix(true);
    Point savedPos = startNode->getPosition();
    Point anchor;
    if (!startNode->isIgnoreAnchorPointForPosition()) {
        anchor = startNode->getAnchorPoint();
    }
    startNode->setPosition(Point(size.width * anchor.x, size.height * anchor.y));
    rtx->begin(); 
    startNode->visit();
    rtx->end();
    startNode->setPosition(savedPos);

    if (std::abs(scale - 1.0f) < 1e-6/* no scale */)
        finalRtx = rtx;
    else {
        /* scale */
        auto finalRect = Rect(0, 0, size.width, size.height);
        Sprite *sprite = Sprite::createWithTexture(rtx->getSprite()->getTexture(), finalRect);
        sprite->setAnchorPoint(Point(0, 0));
        sprite->setFlippedY(true);

        finalRtx = RenderTexture::create(size.width * scale, size.height * scale, Texture2D::PixelFormat::RGBA8888, GL_DEPTH24_STENCIL8);

        sprite->setScale(scale); // or use finalRtx->setKeepMatrix(true);
        finalRtx->begin(); 
        sprite->visit();
        finalRtx->end();
    }

    Director::getInstance()->getRenderer()->render();

    return finalRtx->newImage();
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
    
    // check all children bounding box, get maximize box
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

Sprite* createSpriteFromBase64Cached(const char* base64String, const char* key)
{
    Texture2D* texture = Director::getInstance()->getTextureCache()->getTextureForKey(key);

    if (texture == nullptr)
    {
        unsigned char* decoded;
        int length = base64Decode((const unsigned char*)base64String, (unsigned int)strlen(base64String), &decoded);

        Image *image = new (std::nothrow) Image();
        bool imageResult = image->initWithImageData(decoded, length);
        CCASSERT(imageResult, "Failed to create image from base64!");
        free(decoded);

        texture = Director::getInstance()->getTextureCache()->addImage(image, key);
        image->release();
    }

    Sprite* sprite = Sprite::createWithTexture(texture);
    
    return sprite;
}

Sprite* createSpriteFromBase64(const char* base64String)
{
    unsigned char* decoded;
    int length = base64Decode((const unsigned char*)base64String, (unsigned int)strlen(base64String), &decoded);

    Image *image = new (std::nothrow) Image();
    bool imageResult = image->initWithImageData(decoded, length);
    CCASSERT(imageResult, "Failed to create image from base64!");
    free(decoded);

    Texture2D *texture = new (std::nothrow) Texture2D();
    texture->initWithImage(image);
    texture->setAliasTexParameters();
    image->release();

    Sprite* sprite = Sprite::createWithTexture(texture);
    texture->release();

    return sprite;
}

Node* findChild(Node* levelRoot, const char* name)
{
    if (levelRoot == nullptr)
        return nullptr;

    // Find this node
    {
        auto target = levelRoot->getChildByName(name);
        if (target != nullptr)
            return target;
    }

    // Find recursively
    for (auto& child : levelRoot->getChildren())
    {
        auto target = findChild(child, name);
        if (target != nullptr)
            return target;
    }
    return nullptr;
}

Node* findChild(Node* levelRoot, int tag)
{
    if (levelRoot == nullptr)
        return nullptr;

    // Find this node
    {
        auto target = levelRoot->getChildByTag(tag);
        if (target != nullptr)
            return target;
    }

    // Find recursively
    for (auto& child : levelRoot->getChildren())
    {
        auto target = findChild(child, tag);
        if (target != nullptr)
            return target;
    }

    return nullptr;
}

}

NS_CC_END
