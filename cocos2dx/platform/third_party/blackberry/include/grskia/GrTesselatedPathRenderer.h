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

#ifndef GrTesselatedPathRenderer_DEFINED
#define GrTesselatedPathRenderer_DEFINED

#include "GrPathRenderer.h"

class GrTesselatedPathRenderer : public GrPathRenderer {
public:
    GrTesselatedPathRenderer();

    virtual void drawPath(GrDrawTarget* target,
                          GrDrawTarget::StageBitfield stages,
                          const GrPath& path,
                          GrPathFill fill,
                          const GrPoint* translate);
    virtual bool canDrawPath(const GrDrawTarget* target,
                             const GrPath& path,
                             GrPathFill fill) const;

    virtual bool requiresStencilPass(const GrDrawTarget* target,
                                     const GrPath& path,
                                     GrPathFill fill) const { return false; }
    virtual void drawPathToStencil(GrDrawTarget* target,
                                   const GrPath& path,
                                   GrPathFill fill,
                                   const GrPoint* translate);
    virtual bool supportsAA(GrDrawTarget* target,
                            const GrPath& path,
                            GrPathFill fill);
};

#endif
