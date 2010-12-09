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

#ifndef SkComposeShader_DEFINED
#define SkComposeShader_DEFINED

#include "SkShader.h"

class SkXfermode;

///////////////////////////////////////////////////////////////////////////////////////////

/** \class SkComposeShader
    This subclass of shader returns the coposition of two other shaders, combined by
    a xfermode.
*/
class SkComposeShader : public SkShader {
public:
    /** Create a new compose shader, given shaders A, B, and a combining xfermode mode.
        When the xfermode is called, it will be given the result from shader A as its
        "dst", and the result of from shader B as its "src".
        mode->xfer32(sA_result, sB_result, ...)
        @param shaderA  The colors from this shader are seen as the "dst" by the xfermode
        @param shaderB  The colors from this shader are seen as the "src" by the xfermode
        @param mode     The xfermode that combines the colors from the two shaders. If mode
                        is null, then SRC_OVER is assumed.
    */
    SkComposeShader(SkShader* sA, SkShader* sB, SkXfermode* mode = NULL);
    virtual ~SkComposeShader();
    
    // override
    virtual bool setContext(const SkBitmap& device, const SkPaint& paint, const SkMatrix& matrix);
    virtual void shadeSpan(int x, int y, SkPMColor result[], int count);
    virtual void beginSession();
    virtual void endSession();

protected:
    SkComposeShader(SkFlattenableReadBuffer& );
    virtual void flatten(SkFlattenableWriteBuffer& );
    virtual Factory getFactory() { return CreateProc; }

private:
    static SkFlattenable* CreateProc(SkFlattenableReadBuffer& buffer) { 
        return SkNEW_ARGS(SkComposeShader, (buffer)); }

    SkShader*   fShaderA;
    SkShader*   fShaderB;
    SkXfermode* fMode;

    typedef SkShader INHERITED;
};

#endif
