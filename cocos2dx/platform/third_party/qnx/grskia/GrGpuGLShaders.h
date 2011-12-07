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


#ifndef GrGpuGLShaders_DEFINED
#define GrGpuGLShaders_DEFINED

#include "GrGpuGL.h"
#include "GrGLProgram.h"

class GrGpuGLProgram;

// Programmable OpenGL or OpenGL ES 2.0
class GrGpuGLShaders : public GrGpuGL {
public:
             GrGpuGLShaders();
    virtual ~GrGpuGLShaders();

    virtual void resetContext();

    virtual void abandonResources();

protected:
    // overrides from GrGpu
    virtual bool flushGraphicsState(GrPrimitiveType type);
    virtual void setupGeometry(int* startVertex,
                               int* startIndex,
                               int vertexCount,
                               int indexCount);
    virtual void postDraw();

private:

    class ProgramCache;

    // Helpers to make code more readable
    const GrMatrix& getHWSamplerMatrix(int stage);
    void recordHWSamplerMatrix(int stage, const GrMatrix& matrix);

    // sets the texture matrix uniform for currently bound program
    void flushTextureMatrix(int stage);

    // sets the texture domain uniform for currently bound program
    void flushTextureDomain(int stage);

    // sets the color specified by GrDrawTarget::setColor()
    void flushColor();

    // sets the MVP matrix uniform for currently bound program
    void flushViewMatrix();

    // flushes the parameters to two point radial gradient
    void flushRadial2(int stage);

    // flushes the normalized texel size
    void flushTexelSize(int stage);

    // flushes the edges for edge AA
    void flushEdgeAAData();

    static void DeleteProgram(GrGLProgram::CachedData* programData);

    void ProgramUnitTest();

    void buildProgram(GrPrimitiveType type);

    ProgramCache*               fProgramCache;
    GrGLProgram::CachedData*    fProgramData;
    GrGLuint                    fHWProgramID;
    GrGLProgram                 fCurrentProgram;

    typedef GrGpuGL INHERITED;
};

#endif

