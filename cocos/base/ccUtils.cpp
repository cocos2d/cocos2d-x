/****************************************************************************
Copyright (c) 2010      cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#include <cmath>
#include <stdlib.h>
#include "md5/md5.h"

#include "base/CCDirector.h"
#include "base/CCAsyncTaskPool.h"
#include "base/CCEventDispatcher.h"
#include "base/base64.h"
#include "base/ccConstants.h"
#include "base/ccUTF8.h"
#include "renderer/CCCustomCommand.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCRenderState.h"
#include "renderer/backend/Types.h"

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
void onCaptureScreen(const std::function<void(bool, const std::string&)>& afterCaptured, const std::string& filename, const unsigned char* imageData, int width, int height)
{
    if(!imageData)
    {
        afterCaptured(false, "");
        return;
    }
    
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

    bool succeed = false;
    std::string outputFile = "";

    do
    {
        Image* image = new (std::nothrow) Image;
        if (image)
        {
            image->initWithRawData(imageData, width * height * 4, width, height, 8);
            if (FileUtils::getInstance()->isAbsolutePath(filename))
            {
                outputFile = filename;
            }
            else
            {
                CCASSERT(filename.find('/') == std::string::npos, "The existence of a relative path is not guaranteed!");
                outputFile = FileUtils::getInstance()->getWritablePath() + filename;
            }

            // Save image in AsyncTaskPool::TaskType::TASK_IO thread, and call afterCaptured in mainThread
            static bool succeedSaveToFile = false;
            std::function<void(void*)> mainThread = [afterCaptured, outputFile](void* /*param*/)
            {
                if (afterCaptured)
                {
                    afterCaptured(succeedSaveToFile, outputFile);
                }
                startedCapture = false;
            };

            AsyncTaskPool::getInstance()->enqueue(AsyncTaskPool::TaskType::TASK_IO, std::move(mainThread), nullptr, [image, outputFile]()
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
static CaptureScreenCallbackCommand s_captureScreenCommand;
void captureScreen(const std::function<void(bool, const std::string&)>& afterCaptured, const std::string& filename)
{
    if (s_captureScreenListener)
    {
        CCLOG("Warning: CaptureScreen has been called already, don't call more than once in one frame.");
        return;
    }
    s_captureScreenCommand.init(std::numeric_limits<float>::max());
    s_captureScreenCommand.func = std::bind(onCaptureScreen, afterCaptured, filename, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    
    s_captureScreenListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(Director::EVENT_AFTER_DRAW, [](EventCustom* /*event*/) {
        auto director = Director::getInstance();
        director->getEventDispatcher()->removeEventListener((EventListener*)(s_captureScreenListener));
        s_captureScreenListener = nullptr;
        director->getRenderer()->addCommand(&s_captureScreenCommand);
        director->getRenderer()->render();
    });

}

static std::unordered_map<Node*, EventListenerCustom*> s_captureNodeListener;
void captureNode(Node* startNode, std::function<void(Image*)> imageCallback, float scale)
{
    if (s_captureNodeListener.find(startNode) != s_captureNodeListener.end())
    {
        CCLOG("Warning: current node has been captured already");
        return;
    }

    auto callback = [startNode, scale, imageCallback](EventCustom* /*event*/) {
        auto director = Director::getInstance();
        auto captureNodeListener = s_captureNodeListener[startNode];
        director->getEventDispatcher()->removeEventListener((EventListener*)(captureNodeListener));
        s_captureNodeListener.erase(startNode);
        auto& size = startNode->getContentSize();
        
        Director::getInstance()->setNextDeltaTimeZero(true);
        
        RenderTexture* finalRtx = nullptr;
        
        auto rtx = RenderTexture::create(size.width, size.height, backend::PixelFormat::RGBA8888, PixelFormat::D24S8);
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
        
        if (std::abs(scale - 1.0f) < 1e-6f/* no scale */)
            finalRtx = rtx;
        else {
            /* scale */
            auto finalRect = Rect(0, 0, size.width, size.height);
            Sprite *sprite = Sprite::createWithTexture(rtx->getSprite()->getTexture(), finalRect);
            sprite->setAnchorPoint(Point(0, 0));
            sprite->setFlippedY(true);
            finalRtx = RenderTexture::create(size.width * scale, size.height * scale, backend::PixelFormat::RGBA8888, PixelFormat::D24S8);
            
            sprite->setScale(scale); // or use finalRtx->setKeepMatrix(true);
            finalRtx->begin();
            sprite->visit();
            finalRtx->end();
        }
        Director::getInstance()->getRenderer()->render();
        
        finalRtx->newImage(imageCallback);
    };
    
    auto listener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(Director::EVENT_BEFORE_DRAW, callback);
    
    s_captureNodeListener[startNode] = listener;
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
    return (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
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

        if (!imageResult) {
            CC_SAFE_RELEASE_NULL(image);
            return nullptr;
        }

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

    if (!imageResult) {
        CC_SAFE_RELEASE_NULL(image);
        return nullptr;
    }

    Texture2D *texture = new (std::nothrow) Texture2D();
    texture->initWithImage(image);
    texture->setAliasTexParameters();
    image->release();

    Sprite* sprite = Sprite::createWithTexture(texture);
    texture->release();

    return sprite;
}

Node* findChild(Node* levelRoot, const std::string& name)
{
    if (levelRoot == nullptr || name.empty())
        return nullptr;

    // Find this node
    auto target = levelRoot->getChildByName(name);
    if (target != nullptr)
        return target;

    // Find recursively
    for (auto& child : levelRoot->getChildren())
    {
        target = findChild(child, name);
        if (target != nullptr)
            return target;
    }
    return nullptr;
}

Node* findChild(Node* levelRoot, int tag)
{
    if (levelRoot == nullptr || tag == Node::INVALID_TAG)
        return nullptr;

    // Find this node
    auto target = levelRoot->getChildByTag(tag);
    if (target != nullptr)
        return target;

    // Find recursively
    for (auto& child : levelRoot->getChildren())
    {
        target = findChild(child, tag);
        if (target != nullptr)
            return target;
    }

    return nullptr;
}

std::string getFileMD5Hash(const std::string &filename)
{
    Data data;
    FileUtils::getInstance()->getContents(filename, &data);

    return getDataMD5Hash(data);
}

std::string getDataMD5Hash(const Data &data)
{
    static const unsigned int MD5_DIGEST_LENGTH = 16;

    if (data.isNull())
    {
        return std::string();
    }

    md5_state_t state;
    md5_byte_t digest[MD5_DIGEST_LENGTH];
    char hexOutput[(MD5_DIGEST_LENGTH << 1) + 1] = { 0 };

    md5_init(&state);
    md5_append(&state, (const md5_byte_t *)data.getBytes(), (int)data.getSize());
    md5_finish(&state, digest);

    for (int di = 0; di < 16; ++di)
        sprintf(hexOutput + di * 2, "%02x", digest[di]);

    return hexOutput;
}

LanguageType getLanguageTypeByISO2(const char* code)
{
    // this function is used by all platforms to get system language
    // except windows: cocos/platform/win32/CCApplication-win32.cpp
    LanguageType ret = LanguageType::ENGLISH;

    if (strncmp(code, "zh", 2) == 0)
    {
        ret = LanguageType::CHINESE;
    }
    else if (strncmp(code, "ja", 2) == 0)
    {
        ret = LanguageType::JAPANESE;
    }
    else if (strncmp(code, "fr", 2) == 0)
    {
        ret = LanguageType::FRENCH;
    }
    else if (strncmp(code, "it", 2) == 0)
    {
        ret = LanguageType::ITALIAN;
    }
    else if (strncmp(code, "de", 2) == 0)
    {
        ret = LanguageType::GERMAN;
    }
    else if (strncmp(code, "es", 2) == 0)
    {
        ret = LanguageType::SPANISH;
    }
    else if (strncmp(code, "nl", 2) == 0)
    {
        ret = LanguageType::DUTCH;
    }
    else if (strncmp(code, "ru", 2) == 0)
    {
        ret = LanguageType::RUSSIAN;
    }
    else if (strncmp(code, "hu", 2) == 0)
    {
        ret = LanguageType::HUNGARIAN;
    }
    else if (strncmp(code, "pt", 2) == 0)
    {
        ret = LanguageType::PORTUGUESE;
    }
    else if (strncmp(code, "ko", 2) == 0)
    {
        ret = LanguageType::KOREAN;
    }
    else if (strncmp(code, "ar", 2) == 0)
    {
        ret = LanguageType::ARABIC;
    }
    else if (strncmp(code, "nb", 2) == 0)
    {
        ret = LanguageType::NORWEGIAN;
    }
    else if (strncmp(code, "pl", 2) == 0)
    {
        ret = LanguageType::POLISH;
    }
    else if (strncmp(code, "tr", 2) == 0)
    {
        ret = LanguageType::TURKISH;
    }
    else if (strncmp(code, "uk", 2) == 0)
    {
        ret = LanguageType::UKRAINIAN;
    }
    else if (strncmp(code, "ro", 2) == 0)
    {
        ret = LanguageType::ROMANIAN;
    }
    else if (strncmp(code, "bg", 2) == 0)
    {
        ret = LanguageType::BULGARIAN;
    }
    else if (strncmp(code, "be", 2) == 0)
    {
        ret = LanguageType::BELARUSIAN;
    }
    return ret;
}
    
backend::BlendFactor toBackendBlendFactor(int factor)
{
    switch (factor) {
        case GLBlendConst::ONE:
            return backend::BlendFactor::ONE;
        case GLBlendConst::ZERO:
            return backend::BlendFactor::ZERO;
        case GLBlendConst::SRC_COLOR:
            return backend::BlendFactor::SRC_COLOR;
        case GLBlendConst::ONE_MINUS_SRC_COLOR:
            return backend::BlendFactor::ONE_MINUS_SRC_COLOR;
        case GLBlendConst::SRC_ALPHA:
            return backend::BlendFactor::SRC_ALPHA;
        case GLBlendConst::ONE_MINUS_SRC_ALPHA:
            return backend::BlendFactor::ONE_MINUS_SRC_ALPHA;
        case GLBlendConst::DST_COLOR:
            return backend::BlendFactor::DST_COLOR;
        case GLBlendConst::ONE_MINUS_DST_COLOR:
            return backend::BlendFactor::ONE_MINUS_DST_COLOR;
        case GLBlendConst::DST_ALPHA:
            return backend::BlendFactor::DST_ALPHA;
        case GLBlendConst::ONE_MINUS_DST_ALPHA:
            return backend::BlendFactor::ONE_MINUS_DST_ALPHA;
        case GLBlendConst::SRC_ALPHA_SATURATE:
            return backend::BlendFactor::SRC_ALPHA_SATURATE;
        case GLBlendConst::BLEND_COLOR:
            return backend::BlendFactor::BLEND_CLOLOR;
        case GLBlendConst::CONSTANT_ALPHA:
            return backend::BlendFactor::CONSTANT_ALPHA;
        case GLBlendConst::ONE_MINUS_CONSTANT_ALPHA:
            return backend::BlendFactor::ONE_MINUS_CONSTANT_ALPHA;
        default:
            assert(false);
            break;
    }
    return backend::BlendFactor::ONE;
}

int toGLBlendFactor(backend::BlendFactor blendFactor)
{
    int ret = GLBlendConst::ONE;
    switch (blendFactor)
    {
    case backend::BlendFactor::ZERO:
        ret = GLBlendConst::ZERO;
        break;
    case backend::BlendFactor::ONE:
        ret = GLBlendConst::ONE;
        break;
    case backend::BlendFactor::SRC_COLOR:
        ret = GLBlendConst::SRC_COLOR;
        break;
    case backend::BlendFactor::ONE_MINUS_SRC_COLOR:
        ret = GLBlendConst::ONE_MINUS_SRC_COLOR;
        break;
    case backend::BlendFactor::SRC_ALPHA:
        ret = GLBlendConst::SRC_ALPHA;
        break;
    case backend::BlendFactor::ONE_MINUS_SRC_ALPHA:
        ret = GLBlendConst::ONE_MINUS_SRC_ALPHA;
        break;
    case backend::BlendFactor::DST_COLOR:
        ret = GLBlendConst::DST_COLOR;
        break;
    case backend::BlendFactor::ONE_MINUS_DST_COLOR:
        ret = GLBlendConst::ONE_MINUS_DST_COLOR;
        break;
    case backend::BlendFactor::DST_ALPHA:
        ret = GLBlendConst::DST_ALPHA;
        break;
    case backend::BlendFactor::ONE_MINUS_DST_ALPHA:
        ret = GLBlendConst::ONE_MINUS_DST_ALPHA;
        break;
    case backend::BlendFactor::SRC_ALPHA_SATURATE:
        ret = GLBlendConst::SRC_ALPHA_SATURATE;
        break;
    case backend::BlendFactor::BLEND_CLOLOR:
        ret = GLBlendConst::BLEND_COLOR;
        break;
    default:
        break;
    }
    return ret;
}

backend::SamplerFilter toBackendSamplerFilter(int mode)
{
    switch (mode)
    {
    case GLTexParamConst::LINEAR:
    case GLTexParamConst::LINEAR_MIPMAP_LINEAR:
    case GLTexParamConst::LINEAR_MIPMAP_NEAREST:
    case GLTexParamConst::NEAREST_MIPMAP_LINEAR:
        return backend::SamplerFilter::LINEAR;
    case GLTexParamConst::NEAREST:
    case GLTexParamConst::NEAREST_MIPMAP_NEAREST:
        return backend::SamplerFilter::NEAREST;
    default:
        CCASSERT(false, "invalid GL sampler filter!");
        return backend::SamplerFilter::LINEAR;
    }
}

backend::SamplerAddressMode toBackendAddressMode(int mode)
{
    switch (mode)
    {
    case GLTexParamConst::REPEAT:
        return backend::SamplerAddressMode::REPEAT;
    case GLTexParamConst::CLAMP:
    case GLTexParamConst::CLAMP_TO_EDGE:
        return backend::SamplerAddressMode::CLAMP_TO_EDGE;
    case GLTexParamConst::MIRROR_REPEAT:
        return backend::SamplerAddressMode::MIRROR_REPEAT;
    default:
        CCASSERT(false, "invalid GL address mode");
        return backend::SamplerAddressMode::REPEAT;
    }
}

const Mat4& getAdjustMatrix()
{
    static cocos2d::Mat4 adjustMatrix = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 0.5, 0.5,
        0, 0, 0, 1
    };

    return adjustMatrix;
}

std::vector<float> getNormalMat3OfMat4(const Mat4 &mat)
{
    std::vector<float> normalMat(9);
    Mat4 mvInverse = mat;
    mvInverse.m[12] = mvInverse.m[13] = mvInverse.m[14] = 0.0f;
    mvInverse.inverse();
    mvInverse.transpose();
    normalMat[0] = mvInverse.m[0]; normalMat[1] = mvInverse.m[1]; normalMat[2] = mvInverse.m[2];
    normalMat[3] = mvInverse.m[4]; normalMat[4] = mvInverse.m[5]; normalMat[5] = mvInverse.m[6];
    normalMat[6] = mvInverse.m[8]; normalMat[7] = mvInverse.m[9]; normalMat[8] = mvInverse.m[10];
    return normalMat;
}

std::vector<int> parseIntegerList(const std::string &intsString) {
    std::vector<int> result;

    const char *cStr = intsString.c_str();
    char *endptr;

    for (long int i = strtol(cStr, &endptr, 10); endptr != cStr; i = strtol(cStr, &endptr, 10)) {
        if (errno == ERANGE) {
            errno = 0;
            CCLOGWARN("%s contains out of range integers", intsString.c_str());
        }
        result.push_back(static_cast<int>(i));
        cStr= endptr;
    }

    return result;
}

}

NS_CC_END
