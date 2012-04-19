/* libs/graphics/animator/SkDrawShader.h
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

#ifndef SkDrawShader_DEFINED
#define SkDrawShader_DEFINED

#include "SkPaintParts.h"
#include "SkShader.h"

class SkBaseBitmap;

class SkDrawBitmapShader : public SkDrawShader {
    DECLARE_DRAW_MEMBER_INFO(BitmapShader);
    SkDrawBitmapShader();
    virtual bool add();
    virtual SkShader* getShader();
protected:
    SkBool filterBitmap;
    SkBaseBitmap* image;
private:
    typedef SkDrawShader INHERITED;
};

#endif // SkDrawShader_DEFINED
