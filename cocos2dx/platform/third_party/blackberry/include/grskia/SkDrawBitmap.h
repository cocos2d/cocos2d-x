/* libs/graphics/animator/SkDrawBitmap.h
**
** Copyright 2006, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License"); 
** you may not use this file except in compliance with the License. 
** You may obtain a copy of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** Unless required by applicable law or agreed to in writing, software 
** distributed under the License is distributed on an "AS IS" BASIS, 
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
** See the License for the specific language governing permissions and 
** limitations under the License.
*/

#ifndef SkDrawBitmap_DEFINED
#define SkDrawBitmap_DEFINED

#include "SkBoundable.h"
#include "SkBase64.h"
#include "SkBitmap.h"
// #include "SkImageDecoder.h"
#include "SkMemberInfo.h"

class SkBaseBitmap : public SkBoundable {
    DECLARE_MEMBER_INFO(BaseBitmap);
    SkBaseBitmap();
    virtual ~SkBaseBitmap();
    virtual bool draw(SkAnimateMaker& );
protected:
    SkBitmap fBitmap;
    SkScalar x;
    SkScalar y;
private:
    friend class SkDrawTo;
    friend class SkDrawBitmapShader;
    typedef SkBoundable INHERITED;
};

class SkDrawBitmap : public SkBaseBitmap {
    DECLARE_DRAW_MEMBER_INFO(Bitmap);
    SkDrawBitmap();
    virtual ~SkDrawBitmap();
#ifdef SK_DUMP_ENABLED
    virtual void dump(SkAnimateMaker* );
#endif
    virtual void onEndElement(SkAnimateMaker& );
    virtual bool setProperty(int index, SkScriptValue& value);
protected:
    int /*SkBitmap::Config*/ format;
    int32_t height;
    int32_t rowBytes;
    int32_t width;
    SkColor fColor;
    SkBool fColorSet;
    typedef SkBaseBitmap INHERITED;
};

class SkImage : public SkBaseBitmap {
    DECLARE_MEMBER_INFO(Image);
    SkImage();
    virtual ~SkImage();
    virtual SkDisplayable* deepCopy(SkAnimateMaker* );
    virtual void dirty();
    virtual bool draw(SkAnimateMaker& );
    virtual bool getProperty(int index, SkScriptValue* value) const;
    virtual void onEndElement(SkAnimateMaker& maker);
private:
    void resolve() const { (const_cast<SkImage*>(this))->resolve(); }
    void resolve();
protected:
    SkBase64 base64;
    SkString src;
    SkString fLast; // cache of src so that stream isn't unnecessarily decoded 
    SkBool fDirty;
    const char* fUriBase;
    typedef SkBaseBitmap INHERITED;
};

#endif // SkDrawBitmap_DEFINED
