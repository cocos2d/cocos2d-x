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

/*
 *  SkOSWindow_wxwidgets.h
 *  wxwidgets
 *
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef SkOSWindow_wxwidgets_DEFINED
#define SkOSWindow_wxwidgets_DEFINED

#include "SkWindow.h"
#include "wx/frame.h"

class SkOSWindow: public SkWindow
{
public:
    SkOSWindow();
    SkOSWindow(const wxString& title, int x, int y, int width, int height);
    ~SkOSWindow();
    
    wxFrame* getWXFrame() const { return fFrame; }
    
    void updateSize();
    
protected:
    virtual void onHandleInval(const SkIRect&);
    virtual void onAddMenu(const SkOSMenu*);
    
private:
    wxFrame* fFrame;
    typedef SkWindow INHERITED;
    
};

#endifpedef SkWindow INHERITED;
