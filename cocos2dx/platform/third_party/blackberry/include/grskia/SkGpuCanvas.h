/*
    Copyright 2010 Google Inc.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

         http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
 */


#ifndef SkGpuCanvas_DEFINED
#define SkGpuCanvas_DEFINED

#include "SkCanvas.h"

class GrContext;
class GrRenderTarget;

/**
 *  Subclass of canvas that creates devices compatible with the GrContext pass
 *  to the canvas' constructor.
 */
class SK_API SkGpuCanvas : public SkCanvas {
public:
    /**
     *  The GrContext object is reference counted. When passed to our
     *  constructor, its reference count is incremented. In our destructor, the
     *  GrGpu's reference count will be decremented.
     *  GrRenderTarget represents the rendering destination in the underlying
     *  3D API. Its reference count is incremented in the constructor and
     *  decremented in the destructor.
     *  SkGpuDevice::Current3DApiRenderTarget() can be passed as a special
     *  value that will cause the factory to create a render target object
     *  that reflects the state of the underlying 3D API at the time of
     *  construction.
     */
    explicit SkGpuCanvas(GrContext*, GrRenderTarget*);
    virtual ~SkGpuCanvas();

    /**
     *  Override from SkCanvas. Returns true, and if not-null, sets size to
     *  be the width/height of our viewport.
     */
    virtual bool getViewport(SkIPoint* size) const;

#if 0
    virtual int saveLayer(const SkRect* bounds, const SkPaint* paint,
                          SaveFlags flags = kARGB_ClipLayer_SaveFlag) {
        return this->save(flags);
    }
#endif

private:
    GrContext* fContext;

    typedef SkCanvas INHERITED;
};

#endif


