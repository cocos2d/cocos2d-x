/****************************************************************************
Copyright (c) 2013      Zynga Inc.

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

#include "CCTextureCacheEmscripten.h"
#include "platform/CCImage.h"
#include "platform/CCFileUtils.h"
#include <emscripten/emscripten.h>
#include <sstream>

using namespace cocos2d;
using namespace std;

#define MULTILINE(...) #__VA_ARGS__

// Following methods are implemented in CCTextureCacheEmscripten.js:
extern "C" {
void cocos2dx_newAsyncImageLoader(int textureCache, int callback__ignored);
void cocos2dx_asyncImageLoader_LoadImage(const char *path, AsyncStruct *asyncData);
void cocos2dx_shutdownAsyncImageLoader();
};

extern "C" {
// This C interface is exposed so that the JavaScript in
// CCTextureCacheEmscripten.js is able to call into these functions.
void CCTextureCacheEmscripten_addImageAsyncCallBack(CCTextureCacheEmscripten *tc, AsyncStruct *data, unsigned char *imgData, int width, int height);
void CCTextureCacheEmscripten_preMultiplyImageRegion( unsigned char *in, int win, int hin, unsigned char *out, int wout, int hout, int xout, int yout);
};

void CCTextureCacheEmscripten_addImageAsyncCallBack(CCTextureCacheEmscripten *tc, AsyncStruct *data, unsigned char *imgData, int width, int height)
{
    tc->addImageAsyncCallBack_emscripten(data, imgData, width, height);
}

/**
 * Construct a new CCTextureCacheEmscripten object. Note that the code in
 * CCTextureCacheEmscripten.js will be injected into the JavaScript runtime as
 * a side-affect.
 */
CCTextureCacheEmscripten::CCTextureCacheEmscripten()
{
    // Add dummy references to these functions so that the compiler will emit
    // code for them prior to this point (which is before when we will call
    // them.
    int deps[] = {
        (int)&CCTextureCacheEmscripten_addImageAsyncCallBack,
        (int)&CCTextureCacheEmscripten_preMultiplyImageRegion
    };

    cocos2dx_newAsyncImageLoader((int)this, (int)&deps);
}

/**
 * Destroy this object. Note that this will shutdown the image processing queue
 * (and hence stall anything waiting for those images to finish loading), and
 * unload the classes and objects instantiated in JavaScript to make this class
 * work.
 */
CCTextureCacheEmscripten::~CCTextureCacheEmscripten()
{
    cocos2dx_shutdownAsyncImageLoader();
}

/**
 * "Blit" the input image to a particular location on the target image. Output
 * image will be alpha pre-multiplied in the process.
 *
 * @in:     Pointer to input image raw data bytes
 * @win:    Width of input image in pixels
 * @hin:    Height of input image in pixels
 * @out:    Pointer to memory where output image raw pixels should be written
 * @wout:   Width of output image in pixels
 * @hout:   Height of output image in pixels
 * @xout:   x-offset into target image where blitted image should be placed
 * @yout:   y-offset into target image where blitted image should be placed
 */
void CCTextureCacheEmscripten_preMultiplyImageRegion(
    unsigned char *in, int win, int hin, // Input image, its width and height
    unsigned char *out, int wout, int hout, // Output image, its width and height
    int xout, int yout) // x and y offsets into the output image
{
    int iter = 0;
    for(int j = 0; j < hin; j++)
    {
        for(int i = 0; i < win; i++)
        {
            int inOffset = 4 * (j * win + i);
            int outOffset = 4 * ((j + yout) * wout + (i + xout));

            unsigned char *pin = in + inOffset;
            unsigned int *pout = (unsigned int *) (out + outOffset);

            *pout = CC_RGB_PREMULTIPLY_ALPHA( pin[0], pin[1], pin[2], pin[3] );
        }
    }
}

/**
 * "Private" callback method to load a texture based on the image data
 * generated in CCTextureCacheEmscripten.js. Exposed here as public so that it
 * can be called from the C wrapper method
 * @CCTextureCacheEmscripten_addImageAsyncCallBack, above.
 */
void CCTextureCacheEmscripten::addImageAsyncCallBack_emscripten(AsyncStruct *data, unsigned char *imgData, int width, int height)
{
    const char *filename = data->filename.c_str();

    CCImage *pImage = new CCImage();
    pImage->initWithRawData((unsigned char*) imgData, 4 * width * height, width, height, 8, true);

    free(imgData);

    CCTexture2D *texture = new CCTexture2D();
    texture->initWithImage(pImage); 

#if CC_ENABLE_CACHE_TEXTURE_DATA
    // cache the texture file name
    VolatileTexture::addImageTexture(texture, filename, CCImage::kFmtRawData);
#endif

    // cache the texture
    _textures->setObject(texture, filename);
    texture->autorelease();

    CCObject *target = data->target;
    SEL_CallFuncO selector = data->selector;

    if (target && selector)
    {
        (target->*selector)(texture);
        target->release();
    }

    pImage->release();
    delete data;
}

void CCTextureCacheEmscripten::addImageAsync(const char *path, CCObject *target, SEL_CallFuncO selector)
{
    CCAssert(path != NULL, "TextureCache: fileimage MUST not be NULL");    

    CCTexture2D *texture = NULL;

    // optimization
    std::string pathKey = CCFileUtils::sharedFileUtils()->fullPathForFilename(path);
    texture = (CCTexture2D*)_textures->objectForKey(pathKey.c_str());

    std::string fullpath = pathKey;
    if (texture != NULL)
    {
        if (target && selector)
        {
            (target->*selector)(texture);
        }
        
        return;
    }

    if (target)
    {
        target->retain();
    }

    // generate async struct
    AsyncStruct *data = new AsyncStruct(fullpath, target, selector);

    // Call into JavaScript code in CCTextureCacheEmscripten.js to do the rest.
    cocos2dx_asyncImageLoader_LoadImage(data->filename.c_str(), data);

    return;
}
