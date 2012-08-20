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

#ifndef GrPathRenderer_DEFINED
#define GrPathRenderer_DEFINED

#include "GrDrawTarget.h"

class SkPath;
struct GrPoint;

/**
 *  Base class for drawing paths into a GrDrawTarget.
 */
class GR_API GrPathRenderer : public GrRefCnt {
public:
    GrPathRenderer(void);

    /**
     * Returns true if this path renderer is able to render the path.
     * Returning false allows the caller to fallback to another path renderer.
     *
     * @param target    The target to draw into
     * @param path      The path to draw
     * @param fill      The fill rule to use
     *
     * @return  true if the path can be drawn by this object, false otherwise.
     */
    virtual bool canDrawPath(const GrDrawTarget* target, const SkPath& path,
                             GrPathFill fill) const = 0;

    /**
     * Draws a path into the draw target. The target will already have its draw
     * state configured for the draw.
     * @param target                the target to draw into.
     * @param stages                indicates which stages the are already
     *                              in use. All enabled stages expect positions
     *                              as texture coordinates. The path renderer
     *                              use the remaining stages for its path
     *                              filling algorithm.
     * @param path                  the path to draw.
     * @param fill                  the fill rule to apply.
     * @param translate             optional additional translation to apply to
     *                              the path. NULL means (0,0).
     */
    virtual void drawPath(GrDrawTarget* target,
                          GrDrawTarget::StageBitfield stages,
                          const SkPath& path,
                          GrPathFill fill,
                          const GrPoint* translate) = 0;

    /**
     * For complex clips Gr uses the stencil buffer. The path renderer must be
     * able to render paths into the stencil buffer. However, the path renderer
     * itself may require the stencil buffer to resolve the path fill rule. This
     * function queries whether the path render needs its own stencil
     * pass. If this returns false then drawPath() should not modify the
     * the target's stencil settings but use those already set on target.
     *
     * @param target target that the path will be rendered to
     * @param path   the path that will be drawn
     * @param fill   the fill rule that will be used, will never be an inverse
     *               rule.
     *
     * @return false if this path renderer can generate interior-only fragments
     *         without changing the stencil settings on the target. If it
     *         returns true the drawPathToStencil will be used when rendering
     *         clips.
     */
    virtual bool requiresStencilPass(const GrDrawTarget* target,
                                     const SkPath& path,
                                     GrPathFill fill) const { return false; }

    /**
     * Draws a path to the stencil buffer. Assume the writable stencil bits
     * are already initialized to zero. Fill will always be either
     * kWinding_PathFill or kEvenOdd_PathFill.
     *
     * Only called if requiresStencilPass returns true for the same combo of
     * target, path, and fill. Never called with an inverse fill.
     *
     * The default implementation assumes the path filling algorithm doesn't
     * require a separate stencil pass and so crashes.
     *
     *
     * @param target                the target to draw into.
     * @param path                  the path to draw.
     * @param fill                  the fill rule to apply.
     * @param translate             optional additional translation to apply to
     *                              the path. NULL means (0,0).
     */
    virtual void drawPathToStencil(GrDrawTarget* target,
                                   const SkPath& path,
                                   GrPathFill fill,
                                   const GrPoint* translate) {
        GrCrash("Unexpected call to drawPathToStencil.");
    }
    
    /**
     * @return true if the path renderer can perform anti-aliasing (aside from
     * having FSAA enabled for a render target)
     */
    virtual bool supportsAA(GrDrawTarget* target,
                            const SkPath& path,
                            GrPathFill fill) { return false; }

    /**
     * This is called to install a custom path renderer in every GrContext at
     * create time. The default implementation in GrCreatePathRenderer_none.cpp
     * returns NULL. Link against another implementation to install your own.
     */
    static GrPathRenderer* CreatePathRenderer();

    /**
     * Multiply curve tolerance by the given value, increasing or decreasing
     * the maximum error permitted in tesselating curves with short straight
     * line segments.
     */
    void scaleCurveTolerance(GrScalar multiplier) {
        GrAssert(multiplier > 0);
        fCurveTolerance = SkScalarMul(fCurveTolerance, multiplier);
    }

protected:
    GrScalar fCurveTolerance;

private:

    typedef GrRefCnt INHERITED;
};

/**
 *  Subclass that renders the path using the stencil buffer to resolve fill
 *  rules (e.g. winding, even-odd)
 */
class GR_API GrDefaultPathRenderer : public GrPathRenderer {
public:
    GrDefaultPathRenderer(bool separateStencilSupport,
                          bool stencilWrapOpsSupport);

    virtual bool canDrawPath(const GrDrawTarget* target,
                             const SkPath& path,
                             GrPathFill fill) const { return true; }

    virtual void drawPath(GrDrawTarget* target,
                          GrDrawTarget::StageBitfield stages,
                          const SkPath& path,
                          GrPathFill fill,
                          const GrPoint* translate);
    virtual bool requiresStencilPass(const GrDrawTarget* target,
                                     const SkPath& path,
                                     GrPathFill fill) const;
    virtual void drawPathToStencil(GrDrawTarget* target,
                                   const SkPath& path,
                                   GrPathFill fill,
                                   const GrPoint* translate);
private:

    void onDrawPath(GrDrawTarget* target,
                    GrDrawTarget::StageBitfield stages,
                    const SkPath& path,
                    GrPathFill fill,
                    const GrPoint* translate,
                    bool stencilOnly);

    bool    fSeparateStencil;
    bool    fStencilWrapOps;

    typedef GrPathRenderer INHERITED;
};

#endif
