/*
 * Copyright (C) 2006 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SkGLCanvas_DEFINED
#define SkGLCanvas_DEFINED

#include "SkCanvas.h"

#ifdef SK_BUILD_FOR_MAC
    #include <OpenGL/gl.h>
#elif defined(ANDROID)
    #include <GLES/gl.h>
#endif

class SkGLDevice;
class SkGLClipIter;

class SkGLCanvas : public SkCanvas {
public:
    // notice, we do NOT allow the SkCanvas(bitmap) constructor, since that
    // does not create a SkGLDevice, which we require
    SkGLCanvas();
    virtual ~SkGLCanvas();

    // overrides from SkCanvas

    virtual bool getViewport(SkIPoint*) const;
    virtual bool setViewport(int width, int height);

    virtual SkDevice* createDevice(SkBitmap::Config, int width, int height,
                                   bool isOpaque, bool isForLayer);

    // settings for the global texture cache

    static size_t GetTextureCacheMaxCount();
    static void SetTextureCacheMaxCount(size_t count);

    static size_t GetTextureCacheMaxSize();
    static void SetTextureCacheMaxSize(size_t size);

    /** Call glDeleteTextures for all textures (including those for text)
        This should be called while the gl-context is still valid. Its purpose
        is to free up gl resources. Note that if a bitmap or text is drawn after
        this call, new caches will be created.
    */
    static void DeleteAllTextures();

    /** Forget all textures without calling delete (including those for text).
        This should be called if the gl-context has changed, and the texture
        IDs that have been cached are no longer valid.
    */
    static void AbandonAllTextures();

private:
    SkIPoint fViewportSize;

    // need to disallow this guy
    virtual SkDevice* setBitmapDevice(const SkBitmap& bitmap) {
        sk_throw();
        return NULL;
    }

    typedef SkCanvas INHERITED;
};

#endif

