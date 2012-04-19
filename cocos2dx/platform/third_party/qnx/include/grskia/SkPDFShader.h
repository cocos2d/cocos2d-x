/*
 * Copyright (C) 2011 Google Inc.
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

#ifndef SkPDFShader_DEFINED
#define SkPDFShader_DEFINED

#include "SkPDFStream.h"
#include "SkPDFTypes.h"
#include "SkMatrix.h"
#include "SkRefCnt.h"
#include "SkShader.h"

class SkObjRef;
class SkPDFCatalog;

/** \class SkPDFShader

    In PDF parlance, this is a pattern, used in place of a color when the
    pattern color space is selected.
*/

class SkPDFShader : public SkPDFObject {
public:
    virtual ~SkPDFShader();

    // The SkPDFObject interface.
    virtual void emitObject(SkWStream* stream, SkPDFCatalog* catalog,
                            bool indirect);
    virtual size_t getOutputSize(SkPDFCatalog* catalog, bool indirect);
    virtual void getResources(SkTDArray<SkPDFObject*>* resourceList);

    /** Get the PDF shader for the passed SkShader. If the SkShader is
     *  invalid in some way, returns NULL. The reference count of
     *  the object is incremented and it is the caller's responsibility to
     *  unreference it when done.  This is needed to accommodate the weak
     *  reference pattern used when the returned object is new and has no
     *  other references.
     *  @param shader     The SkShader to emulate.
     *  @param matrix     The current transform. (PDF shaders are absolutely
     *                    positioned, relative to where the page is drawn.)
     *  @param surfceBBox The bounding box of the drawing surface (with matrix
     *                    already applied).
     */
    static SkPDFShader* getPDFShader(const SkShader& shader,
                                     const SkMatrix& matrix,
                                     const SkIRect& surfaceBBox);

private:
    class State {
    public:
        SkShader::GradientType fType;
        SkShader::GradientInfo fInfo;
        SkAutoFree fColorData;
        SkMatrix fCanvasTransform;
        SkMatrix fShaderTransform;
        SkIRect fBBox;

        SkBitmap fImage;
        uint32_t fPixelGeneration;
        SkShader::TileMode fImageTileModes[2];

        explicit State(const SkShader& shader, const SkMatrix& canvasTransform,
                       const SkIRect& bbox);
        bool operator==(const State& b) const;
    };

    SkRefPtr<SkPDFDict> fContent;
    SkTDArray<SkPDFObject*> fResources;
    SkAutoTDelete<const State> fState;

    class ShaderCanonicalEntry {
    public:
        SkPDFShader* fPDFShader;
        const State* fState;

        bool operator==(const ShaderCanonicalEntry& b) const {
            return fPDFShader == b.fPDFShader || *fState == *b.fState;
        }
        ShaderCanonicalEntry(SkPDFShader* pdfShader, const State* state)
            : fPDFShader(pdfShader),
              fState(state) {
        }
    };
    // This should be made a hash table if performance is a problem.
    static SkTDArray<ShaderCanonicalEntry>& canonicalShaders();
    static SkMutex& canonicalShadersMutex();

    static SkPDFObject* rangeObject();

    SkPDFShader(State* state);

    void doFunctionShader();
    void doImageShader();
    SkPDFStream* makePSFunction(const SkString& psCode, SkPDFArray* domain);
};

#endif
