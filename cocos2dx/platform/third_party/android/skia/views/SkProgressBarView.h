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

#ifndef SkProgressBarView_DEFINED
#define SkProgressBarView_DEFINED

#include "SkView.h"
#include "SkWidgetViews.h"
#include "SkAnimator.h"

class SkProgressBarView : public SkWidgetView {
    public:
        SkProgressBarView();
        //SkProgressBarView(int max);
                
        //inflate: "sk-progress"
    
        void reset();   //reset progress to zero
        void setProgress(int progress);
        void changeProgress(int diff);
        void setMax(int max);
        
        int getProgress() const { return fProgress; }
        int getMax() const { return fMax; }
    
    protected:
        //overrides
        virtual void onInflate(const SkDOM& dom, const SkDOM::Node* node);
        virtual void onSizeChange();
        virtual void onDraw(SkCanvas* canvas);
        virtual bool onEvent(const SkEvent& evt);
    
    private:
        SkAnimator  fAnim;
        int         fProgress;
        int         fMax;
        
        typedef SkWidgetView INHERITED;
};




#endif
