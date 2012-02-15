/*
    Copyright 2011 Google Inc.

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

#ifndef GrResource_DEFINED
#define GrResource_DEFINED

#include "GrRefCnt.h"

class GrGpu;

class GrResource : public GrRefCnt {
public:
    explicit GrResource(GrGpu* gpu);

    virtual ~GrResource() {
        // subclass should have released this.
        GrAssert(!isValid());
    }

    /**
     * Frees the resource in the underlying 3D API. It must be safe to call this
     * when the resource has been previously abandoned.
     */
    void release();

    /**
     * Removes references to objects in the underlying 3D API without freeing
     * them. Used when the API context has been torn down before the GrContext.
     */
    void abandon();

    /**
     * Tests whether a resource has been abandoned or released. All resources
     * will be in this state after their creating GrContext is destroyed or has
     * contextLost called. It's up to the client to test isValid() before
     * attempting to use a resource if it holds refs on resources across
     * ~GrContext, freeResources with the force flag, or contextLost.
     *
     * @return true if the resource has been released or abandoned,
     *         false otherwise.
     */
    bool isValid() const { return NULL != fGpu; }

protected:

    virtual void onRelease() = 0;
    virtual void onAbandon() = 0;

    GrGpu* getGpu() const { return fGpu; }

private:
    GrResource(); // unimpl

    GrGpu* fGpu; // not reffed. This can outlive the GrGpu.

    friend class GrGpu; // GrGpu manages list of resources.

    GrResource* fNext;      // dl-list of resources per-GrGpu
    GrResource* fPrevious;

    typedef GrRefCnt INHERITED;
};

#endif
