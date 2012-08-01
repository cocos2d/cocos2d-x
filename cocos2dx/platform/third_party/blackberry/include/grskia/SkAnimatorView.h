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

#ifndef SkAnimatorView_DEFINED
#define SkAnimatorView_DEFINED

#include "SkView.h"
#include "SkAnimator.h"

class SkAnimatorView : public SkView {
public:
            SkAnimatorView();
    virtual ~SkAnimatorView();

    SkAnimator* getAnimator() const { return fAnimator; }

    bool    decodeFile(const char path[]);
    bool    decodeMemory(const void* buffer, size_t size);
    bool    decodeStream(SkStream* stream);

protected:
    // overrides
    virtual bool onEvent(const SkEvent&);
    virtual void onDraw(SkCanvas*);
    virtual void onInflate(const SkDOM&, const SkDOM::Node*);

private:
    SkAnimator* fAnimator;

    typedef SkView INHERITED;
};

#endif

