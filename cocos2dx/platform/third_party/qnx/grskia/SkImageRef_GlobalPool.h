/*
 * Copyright (C) 2008 The Android Open Source Project
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

#ifndef SkImageRef_GlobalPool_DEFINED
#define SkImageRef_GlobalPool_DEFINED

#include "SkImageRef.h"

class SkImageRef_GlobalPool : public SkImageRef {
public:
    // if pool is null, use the global pool
    SkImageRef_GlobalPool(SkStream*, SkBitmap::Config, int sampleSize = 1);
    virtual ~SkImageRef_GlobalPool();
    
    // overrides
    virtual Factory getFactory() const {
        return Create;
    }
    static SkPixelRef* Create(SkFlattenableReadBuffer&);

    // API to control the global pool

    /** Return the amount specified as the budget for the cache (in bytes).
     */
    static size_t GetRAMBudget();
    
    /** Set a new budget value for the cache.
     */
    static void SetRAMBudget(size_t);
    
    /** Return how much ram is currently in use by the global cache.
     */
    static size_t GetRAMUsed();
    
    /** Free up (approximately) enough such that the amount used by the cache
     is <= the specified amount. Since some images may be "in use", the
     amount actually freed may not always result in a ram usage value <=
     to the requested amount. In addition, because of the
     chunky nature of the cache, the resulting usage may be < the requested
     amount.
     */
    static void SetRAMUsed(size_t usageInBytes);
    
    static void DumpPool();

protected:
    virtual bool onDecode(SkImageDecoder* codec, SkStream* stream,
                          SkBitmap* bitmap, SkBitmap::Config config,
                          SkImageDecoder::Mode mode);
    
    virtual void onUnlockPixels();
    
    SkImageRef_GlobalPool(SkFlattenableReadBuffer&);

private:
    typedef SkImageRef INHERITED;
};

#endif
