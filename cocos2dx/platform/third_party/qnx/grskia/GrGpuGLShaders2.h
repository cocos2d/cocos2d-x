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


#ifndef GrGpuGLShaders2_DEFINED
#define GrGpuGLShaders2_DEFINED

#include "GrGpuGL.h"

// Programmable OpenGL or OpenGL ES 2.0
class GrGpuGLShaders2 : public GrGpuGL {
public:
             GrGpuGLShaders2();
    virtual ~GrGpuGLShaders2();

    virtual void resetContext();

protected:
    // overrides from GrGpu
    virtual bool flushGraphicsState(PrimitiveType type);
    virtual void setupGeometry(uint32_t startVertex,
                               uint32_t startIndex,
                               uint32_t vertexCount,
                               uint32_t indexCount);

private:

    void resetContextHelper();

    // sets the texture matrix uniform for currently bound program
    void flushTextureMatrix(int stage);
   
    // sets the MVP matrix uniform for currently bound program
    void flushViewMatrix();

    // flushes the parameters to two point radial gradient
    void flushRadial2(int stage);

    // called at flush time to setup the appropriate program
    void flushProgram(PrimitiveType type);

    struct Program;

    struct StageDesc;
    struct ProgramDesc;

    struct UniLocations;
    struct StageUniLocations;

    struct ShaderCodeSegments;

    class ProgramCache;

    // gets a description of needed shader
    void getProgramDesc(PrimitiveType primType, ProgramDesc* desc);

    // generates and compiles a program from a description and vertex layout
    // will change GL's bound program
    static void GenProgram(const ProgramDesc& desc, Program* program);

    // generates code for a stage of the shader
    static void GenStageCode(int stageNum,
                             const StageDesc& desc,
                             const char* psInColor,
                             const char* psOutColor,
                             const char* vsInCoord,
                             ShaderCodeSegments* segments,
                             StageUniLocations* locations);

    // Compiles a GL shader, returns shader ID or 0 if failed
    // params have same meaning as glShaderSource
    static GLuint CompileShader(GLenum type, int stringCnt,
                                             const char** strings,
                                             int* stringLengths);
    static void DeleteProgram(Program* program);

    void ProgramUnitTest();

    GrGLTexture::Orientation  fTextureOrientation;

    ProgramCache*   fProgramCache;
    Program*        fProgram;
    GLuint          fHWProgramID;

    typedef GrGpuGL INHERITED;
};

#endif

