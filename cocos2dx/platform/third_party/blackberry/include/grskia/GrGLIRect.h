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


#ifndef GrGLIRect_DEFINED
#define GrGLIRect_DEFINED

#include "GrGLInterface.h"

/**
 * Helper struct for dealing with the fact that Ganesh and GL use different
 * window coordinate systems (top-down vs bottom-up)
 */
struct GrGLIRect {
    GrGLint   fLeft;
    GrGLint   fBottom;
    GrGLsizei fWidth;
    GrGLsizei fHeight;

    void pushToGLViewport() const {
        GR_GL(Viewport(fLeft, fBottom, fWidth, fHeight));
    }

    void pushToGLScissor() const {
        GR_GL(Scissor(fLeft, fBottom, fWidth, fHeight));
    }

    void setFromGLViewport() {
        GR_STATIC_ASSERT(sizeof(GrGLIRect) == 4*sizeof(GrGLint));
        GR_GL_GetIntegerv(GR_GL_VIEWPORT, (GrGLint*) this);
    }

    // sometimes we have a GrIRect from the client that we
    // want to simultaneously make relative to GL's viewport
    // and convert from top-down to bottom-up.
    void setRelativeTo(const GrGLIRect& glRect,
                       int leftOffset,
                       int topOffset,
                       int width,
                       int height) {
        fLeft = glRect.fLeft + leftOffset;
        fWidth = width;
        fBottom = glRect.fBottom + (glRect.fHeight - topOffset - height);
        fHeight = height;

        GrAssert(fLeft >= 0);
        GrAssert(fWidth >= 0);
        GrAssert(fBottom >= 0);
        GrAssert(fHeight >= 0);
    }

    bool contains(const GrGLIRect& glRect) const {
        return fLeft <= glRect.fLeft &&
               fBottom <= glRect.fBottom &&
               fLeft + fWidth >=  glRect.fLeft + glRect.fWidth &&
               fBottom + fHeight >=  glRect.fBottom + glRect.fHeight;
    }

    void invalidate() {fLeft = fWidth = fBottom = fHeight = -1;}

    bool operator ==(const GrGLIRect& glRect) const {
        return 0 == memcmp(this, &glRect, sizeof(GrGLIRect));
    }

    bool operator !=(const GrGLIRect& glRect) const {return !(*this == glRect);}
};

#endif
