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

#ifndef __CCTEXTURE_CACHE_EMSCRIPTEN_H__
#define __CCTEXTURE_CACHE_EMSCRIPTEN_H__

#include "textures/CCTextureCache.h"

NS_CC_BEGIN

class CC_DLL TextureCacheEmscripten : public TextureCache
{
public:
    TextureCacheEmscripten();
    virtual ~TextureCacheEmscripten();

    void addImageAsync(const char *path, Object *target, SEL_CallFuncO selector);

    /* Public method since we need to call it from C code to workaround linkage from JS.
    */
    void addImageAsyncCallBack_emscripten(AsyncStruct *data, unsigned char *imgData, int width, int height);

};

NS_CC_END

#endif
