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

#ifndef SkGraphics_DEFINED
#define SkGraphics_DEFINED

#include "SkTypes.h"

class SkGraphics {
public:
    static void Init();
    static void Term();

    /** Return the (approximate) number of bytes used by the font cache.
    */
    static size_t GetFontCacheUsed();
    
    /** Attempt to purge the font cache until <= the specified amount remains
        in the cache. Specifying 0 will attempt to purge the entire cache.
        Returns true if some amount was purged from the font cache.
    */
    static bool SetFontCacheUsed(size_t usageInBytes);

    /** Return the version numbers for the library. If the parameter is not
        null, it is set to the version number.
     */
    static void GetVersion(int32_t* major, int32_t* minor, int32_t* patch);

private:
    /** This is automatically called by SkGraphics::Init(), and must be
        implemented by the host OS. This allows the host OS to register a callback
        with the C++ runtime to call SkGraphics::FreeCaches()
    */
    static void InstallNewHandler();
};

class SkAutoGraphics {
public:
    SkAutoGraphics() {
        SkGraphics::Init();
    }
    ~SkAutoGraphics() {
        SkGraphics::Term();
    }
};

#endif

