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

#ifndef SkWindow_DEFINED
#define SkWindow_DEFINED

#include "SkView.h"
#include "SkBitmap.h"
#include "SkMatrix.h"
#include "SkRegion.h"
#include "SkEvent.h"
#include "SkKey.h"
#include "SkTDArray.h"

#ifdef SK_BUILD_FOR_WINCEx
    #define SHOW_FPS
#endif
//#define USE_GX_SCREEN

class SkCanvas;

class SkOSMenu;

class SkWindow : public SkView {
public:
            SkWindow();
    virtual ~SkWindow();

    const SkBitmap& getBitmap() const { return fBitmap; }

    void    setConfig(SkBitmap::Config);
    void    resize(int width, int height, SkBitmap::Config config = SkBitmap::kNo_Config);
    void    eraseARGB(U8CPU a, U8CPU r, U8CPU g, U8CPU b);
    void    eraseRGB(U8CPU r, U8CPU g, U8CPU b);

    bool    isDirty() const { return !fDirtyRgn.isEmpty(); }
    bool    update(SkIRect* updateArea, SkCanvas* = NULL);
    // does not call through to onHandleInval(), but does force the fDirtyRgn
    // to be wide open. Call before update() to ensure we redraw everything.
    void    forceInvalAll();
    // return the bounds of the dirty/inval rgn, or [0,0,0,0] if none
    const SkIRect& getDirtyBounds() const { return fDirtyRgn.getBounds(); }

    bool    handleClick(int x, int y, Click::State, void* owner = NULL);
    bool    handleChar(SkUnichar);
    bool    handleKey(SkKey);
    bool    handleKeyUp(SkKey);
    bool    handleMenu(uint32_t os_cmd);

    void    addMenu(SkOSMenu*);
    
    const char* getTitle() const { return fTitle.c_str(); }
    void    setTitle(const char title[]);

    const SkMatrix& getMatrix() const { return fMatrix; }
    void    setMatrix(const SkMatrix&);
    void    preConcat(const SkMatrix&);
    void    postConcat(const SkMatrix&);

    virtual void onPDFSaved(const char title[], const char desc[],
        const char path[]) {}
protected:
    virtual bool onEvent(const SkEvent&);
    virtual bool onDispatchClick(int x, int y, Click::State, void* owner);
    // called if part of our bitmap is invalidated
    virtual void onHandleInval(const SkIRect&);
    virtual bool onHandleChar(SkUnichar);
    virtual bool onHandleKey(SkKey);
    virtual bool onHandleKeyUp(SkKey);
    virtual void onAddMenu(const SkOSMenu*) {}
    virtual void onSetTitle(const char title[]) {}

    // overrides from SkView
    virtual bool handleInval(const SkRect*);
    virtual bool onGetFocusView(SkView** focus) const;
    virtual bool onSetFocusView(SkView* focus);

private:
    SkBitmap::Config    fConfig;
    SkBitmap    fBitmap;
    SkRegion    fDirtyRgn;

    SkTDArray<Click*>       fClicks; // to track clicks

    SkTDArray<SkOSMenu*>    fMenus;

    SkView* fFocusView;
    bool    fWaitingOnInval;
    
    SkString    fTitle;
    SkMatrix    fMatrix;

    typedef SkView INHERITED;
};

///////////////////////////////////////////////////////////

#ifdef SK_USE_WXWIDGETS
    #include "SkOSWindow_wxwidgets.h"
#elif defined(SK_BUILD_FOR_MAC)
    #include "SkOSWindow_Mac.h"
#elif defined(SK_BUILD_FOR_WIN)
    #include "SkOSWindow_Win.h"
#elif defined(ANDROID)
    #include "SkOSWindow_Android.h"
#elif defined(SK_BUILD_FOR_UNIX)
  #include "SkOSWindow_Unix.h"
#elif defined(SK_BUILD_FOR_SDL)
    #include "SkOSWindow_SDL.h"
#elif defined(SK_BUILD_FOR_IOS)
    #include "SkOSWindow_iOS.h"
#endif

#endif

