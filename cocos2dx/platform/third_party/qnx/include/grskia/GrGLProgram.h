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

#ifndef GrGLProgram_DEFINED
#define GrGLProgram_DEFINED

#include "GrGLInterface.h"
#include "GrSamplerState.h"
#include "GrStringBuilder.h"
#include "GrGpu.h"

#include "SkXfermode.h"

class GrBinHashKeyBuilder;

struct ShaderCodeSegments {
    GrStringBuilder fHeader; // VS+FS, GLSL version, etc
    GrStringBuilder fVSUnis;
    GrStringBuilder fVSAttrs;
    GrStringBuilder fVaryings;
    GrStringBuilder fFSUnis;
    GrStringBuilder fFSOutputs;
    GrStringBuilder fFSFunctions;
    GrStringBuilder fVSCode;
    GrStringBuilder fFSCode;
};

/**
 * This class manages a GPU program and records per-program information.
 * We can specify the attribute locations so that they are constant
 * across our shaders. But the driver determines the uniform locations
 * at link time. We don't need to remember the sampler uniform location
 * because we will bind a texture slot to it and never change it
 * Uniforms are program-local so we can't rely on fHWState to hold the
 * previous uniform state after a program change.
 */
class GrGLProgram {
public:
    class CachedData;

    GrGLProgram();
    ~GrGLProgram();

    /**
     *  Streams data that can uniquely identifies the generated
     *  gpu program into a key, for cache indexing purposes.
     *
     *  @param key The key object to receive the key data
     */
    void buildKey(GrBinHashKeyBuilder& key) const;

    /**
     *  This is the heavy initilization routine for building a GLProgram.
     *  The result of heavy init is not stored in datamembers of GrGLProgam,
     *  but in a separate cacheable container.
     */
    bool genProgram(CachedData* programData) const;

     /**
      * The shader may modify the blend coeffecients. Params are in/out
      */
     void overrideBlend(GrBlendCoeff* srcCoeff, GrBlendCoeff* dstCoeff) const;

    /**
     * Attribute indices
     */
    static int PositionAttributeIdx() { return 0; }
    static int TexCoordAttributeIdx(int tcIdx) { return 1 + tcIdx; }
    static int ColorAttributeIdx() { return 1 + GrDrawTarget::kMaxTexCoords; }
    static int ViewMatrixAttributeIdx() {
        return 2 + GrDrawTarget::kMaxTexCoords;
    }
    static int TextureMatrixAttributeIdx(int stage) {
        return 5 + GrDrawTarget::kMaxTexCoords + 3 * stage;
    }

private:

    // Parameters that affect code generation
    // These structs should be kept compact; they are the input to an
    // expensive hash key generator.
    struct ProgramDesc {
        ProgramDesc() {
            // since we use this as part of a key we can't have any unitialized
            // padding
            memset(this, 0, sizeof(ProgramDesc));
        }

        struct StageDesc {
            enum OptFlagBits {
                kNoPerspective_OptFlagBit       = 1 << 0,
                kIdentityMatrix_OptFlagBit      = 1 << 1,
                kCustomTextureDomain_OptFlagBit = 1 << 2,
                kIsEnabled_OptFlagBit           = 1 << 7
            };
            enum Modulation {
                kColor_Modulation,
                kAlpha_Modulation
            };
            enum FetchMode {
                kSingle_FetchMode,
                k2x2_FetchMode
            };
            enum CoordMapping {
                kIdentity_CoordMapping,
                kRadialGradient_CoordMapping,
                kSweepGradient_CoordMapping,
                kRadial2Gradient_CoordMapping
            };

            uint8_t fOptFlags;
            uint8_t fModulation;  // casts to enum Modulation
            uint8_t fFetchMode;  // casts to enum FetchMode
            uint8_t fCoordMapping;  // casts to enum CoordMapping

            inline bool isEnabled() const {
                return fOptFlags & kIsEnabled_OptFlagBit;
            }
            inline void setEnabled(bool newValue) {
                if (newValue) {
                    fOptFlags |= kIsEnabled_OptFlagBit;
                } else {
                    fOptFlags &= ~kIsEnabled_OptFlagBit;
                }
            }

            uint8_t fWrapModeHorizontal; // casts to enum GrSamplerState::WrapMode
            uint8_t fWrapModeVertical;
        };

        enum ColorType {
            kNone_ColorType         = 0,
            kAttribute_ColorType    = 1,
            kUniform_ColorType      = 2,
        };
        // Dual-src blending makes use of a secondary output color that can be
        // used as a per-pixel blend coeffecient. This controls whether a
        // secondary source is output and what value it holds.
        enum DualSrcOutput {
            kNone_DualSrcOutput,
            kCoverage_DualSrcOutput,
            kCoverageISA_DualSrcOutput,
            kCoverageISC_DualSrcOutput,
            kDualSrcOutputCnt
        };

        // stripped of bits that don't affect prog generation
        GrVertexLayout fVertexLayout;

        StageDesc fStages[GrDrawTarget::kNumStages];

        uint8_t fColorType;  // casts to enum ColorType
        uint8_t fDualSrcOutput;  // casts to enum DualSrcOutput
        int8_t fFirstCoverageStage;
        SkBool8 fEmitsPointSize;
        SkBool8 fEdgeAAConcave;

        int8_t fEdgeAANumEdges;
        uint8_t fColorFilterXfermode;  // casts to enum SkXfermode::Mode

        uint8_t fPadTo32bLengthMultiple [1];

    } fProgramDesc;

    const ProgramDesc& getDesc() { return fProgramDesc; }

public:
    enum {
        kUnusedUniform = -1,
        kSetAsAttribute = 1000,
    };

    struct StageUniLocations {
        GrGLint fTextureMatrixUni;
        GrGLint fNormalizedTexelSizeUni;
        GrGLint fSamplerUni;
        GrGLint fRadial2Uni;
        GrGLint fTexDomUni;
        void reset() {
            fTextureMatrixUni = kUnusedUniform;
            fNormalizedTexelSizeUni = kUnusedUniform;
            fSamplerUni = kUnusedUniform;
            fRadial2Uni = kUnusedUniform;
            fTexDomUni = kUnusedUniform;
        }
    };

    struct UniLocations {
        GrGLint fViewMatrixUni;
        GrGLint fColorUni;
        GrGLint fEdgesUni;
        GrGLint fColorFilterUni;
        StageUniLocations fStages[GrDrawTarget::kNumStages];
        void reset() {
            fViewMatrixUni = kUnusedUniform;
            fColorUni = kUnusedUniform;
            fEdgesUni = kUnusedUniform;
            fColorFilterUni = kUnusedUniform;
            for (int s = 0; s < GrDrawTarget::kNumStages; ++s) {
                fStages[s].reset();
            }
        }
    };

    class CachedData : public ::GrNoncopyable {
    public:
        CachedData() {
        }

        ~CachedData() {
        }

        void copyAndTakeOwnership(CachedData& other) {
            memcpy(this, &other, sizeof(*this));
        }

    public:

        // IDs
        GrGLuint    fVShaderID;
        GrGLuint    fFShaderID;
        GrGLuint    fProgramID;
        // shader uniform locations (-1 if shader doesn't use them)
        UniLocations fUniLocations;

        GrMatrix  fViewMatrix;

        // these reflect the current values of uniforms
        // (GL uniform values travel with program)
        GrColor                     fColor;
        GrColor                     fColorFilterColor;
        GrMatrix                    fTextureMatrices[GrDrawTarget::kNumStages];
        // width and height used for normalized texel size
        int                         fTextureWidth[GrDrawTarget::kNumStages];
        int                         fTextureHeight[GrDrawTarget::kNumStages]; 
        GrScalar                    fRadial2CenterX1[GrDrawTarget::kNumStages];
        GrScalar                    fRadial2Radius0[GrDrawTarget::kNumStages];
        bool                        fRadial2PosRoot[GrDrawTarget::kNumStages];
        GrRect                      fTextureDomain[GrDrawTarget::kNumStages];

    private:
        enum Constants {
            kUniLocationPreAllocSize = 8
        };

    }; // CachedData

private:
    enum {
        kUseUniform = 2000
    };

    // should set all fields in locations var to kUseUniform if the
    // corresponding uniform is required for the program.
    void genStageCode(int stageNum,
                      const ProgramDesc::StageDesc& desc,
                      const char* fsInColor, // NULL means no incoming color
                      const char* fsOutColor,
                      const char* vsInCoord,
                      ShaderCodeSegments* segments,
                      StageUniLocations* locations) const;

    static bool CompileFSAndVS(const ShaderCodeSegments& segments, 
                               CachedData* programData);

    // Compiles a GL shader, returns shader ID or 0 if failed
    // params have same meaning as glShaderSource
    static GrGLuint CompileShader(GrGLenum type, int stringCnt,
                                  const char** strings,
                                  int* stringLengths);

    // Creates a GL program ID, binds shader attributes to GL vertex attrs, and
    // links the program
    bool bindOutputsAttribsAndLinkProgram(
                GrStringBuilder texCoordAttrNames[GrDrawTarget::kMaxTexCoords],
                bool bindColorOut,
                bool bindDualSrcOut,
                CachedData* programData) const;

    // Gets locations for all uniforms set to kUseUniform and initializes cache
    // to invalid values.
    void getUniformLocationsAndInitCache(CachedData* programData) const;

    friend class GrGpuGLShaders;
};

#endif
