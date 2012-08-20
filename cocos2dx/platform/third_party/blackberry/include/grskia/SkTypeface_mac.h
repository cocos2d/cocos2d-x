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


#ifndef SkTypeface_mac_DEFINED
#define SkTypeface_mac_DEFINED

#include "SkTypeface.h"
#ifdef SK_BUILD_FOR_MAC
#import <ApplicationServices/ApplicationServices.h>
#endif

#ifdef SK_BUILD_FOR_IOS
#include <CoreText/CoreText.h>
#endif
/**
 *  Like the other Typeface create methods, this returns a new reference to the
 *  corresponding typeface for the specified CTFontRef. The caller must call
 *  unref() when it is finished.
 */
SK_API extern SkTypeface* SkCreateTypefaceFromCTFont(CTFontRef);

#endif

