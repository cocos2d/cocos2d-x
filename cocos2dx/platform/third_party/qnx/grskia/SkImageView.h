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

#ifndef SkImageView_DEFINED
#define SkImageView_DEFINED

#include "SkView.h"
#include "SkString.h"

class SkAnimator;
class SkBitmap;
class SkMatrix;

class SkImageView : public SkView {
public:
            SkImageView();
    virtual ~SkImageView();

    void    getUri(SkString*) const;
    void    setUri(const char []);
    void    setUri(const SkString&);
    

    enum ScaleType {
        kMatrix_ScaleType,
        kFitXY_ScaleType,
        kFitStart_ScaleType,
        kFitCenter_ScaleType,
        kFitEnd_ScaleType
    };
    ScaleType   getScaleType() const { return (ScaleType)fScaleType; }
    void        setScaleType(ScaleType);
    
    bool    getImageMatrix(SkMatrix*) const;
    void    setImageMatrix(const SkMatrix*);

protected:
    // overrides
    virtual bool    onEvent(const SkEvent&);
    virtual void    onDraw(SkCanvas*);
    virtual void    onInflate(const SkDOM&, const SkDOMNode*);
    
private:
    SkString    fUri;
    SkMatrix*   fMatrix;    // null or copy of caller's matrix ,,,,,
    union {
        SkAnimator* fAnim;
        SkBitmap* fBitmap;
    } fData;
    uint8_t     fScaleType;
    SkBool8     fDataIsAnim;    // as opposed to bitmap
    SkBool8     fUriIsValid;
    
    void    onUriChange();
    bool    getDataBounds(SkRect* bounds);
    bool    freeData();
    bool    ensureUriIsLoaded();

    typedef SkView INHERITED;
};

#endif
