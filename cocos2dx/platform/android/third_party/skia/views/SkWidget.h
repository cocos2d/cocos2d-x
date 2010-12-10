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

#ifndef SkWidget_DEFINED
#define SkWidget_DEFINED

#include "SkView.h"
#include "SkBitmap.h"
#include "SkDOM.h"
#include "SkPaint.h"
#include "SkString.h"
#include "SkTDArray.h"

//////////////////////////////////////////////////////////////////////////////

class SkWidget : public SkView {
public:
    SkWidget(uint32_t flags = 0) : SkView(flags | kFocusable_Mask | kEnabled_Mask) {}

    /** Call this to post the widget's event to its listeners */
    void    postWidgetEvent();

    static void Init();
    static void Term();
protected:
    // override to add slots to an event before posting
    virtual void prepareWidgetEvent(SkEvent*);
    virtual void onEnabledChange();

    // <event ...> to initialize the event from XML
    virtual void onInflate(const SkDOM& dom, const SkDOM::Node* node);

private:
    SkEvent fEvent;
    typedef SkView INHERITED;
};

class SkHasLabelWidget : public SkWidget {
public:
    SkHasLabelWidget(uint32_t flags = 0) : SkWidget(flags) {}

    size_t  getLabel(SkString* label = NULL) const;
    size_t  getLabel(char lable[] = NULL) const;
    void    setLabel(const SkString&);
    void    setLabel(const char label[]);
    void    setLabel(const char label[], size_t len);

protected:
    // called when the label changes
    virtual void onLabelChange();

    // overrides
    virtual void onInflate(const SkDOM& dom, const SkDOM::Node*);

private:
    SkString    fLabel;
    typedef SkWidget INHERITED;
};

class SkButtonWidget : public SkHasLabelWidget {
public:
    SkButtonWidget(uint32_t flags = 0) : SkHasLabelWidget(flags), fState(kOff_State) {}

    enum State {
        kOff_State,     //!< XML: buttonState="off"
        kOn_State,      //!< XML: buttonState="on"
        kUnknown_State  //!< XML: buttonState="unknown"
    };
    State   getButtonState() const { return fState; }
    void    setButtonState(State);

protected:
    /** called when the label changes. default behavior is to inval the widget */
    virtual void onButtonStateChange();

    // overrides
    virtual void onInflate(const SkDOM& dom, const SkDOM::Node*);

private:
    State   fState;
    typedef SkHasLabelWidget INHERITED;
};

class SkPushButtonWidget : public SkButtonWidget {
public:
    SkPushButtonWidget(uint32_t flags = 0) : SkButtonWidget(flags) {}

protected:
    virtual bool onEvent(const SkEvent&);
    virtual void onDraw(SkCanvas*);
    virtual Click* onFindClickHandler(SkScalar x, SkScalar y);
    virtual bool onClick(Click* click);

private:
    typedef SkButtonWidget INHERITED;
};

class SkCheckBoxWidget : public SkButtonWidget {
public:
    SkCheckBoxWidget(uint32_t flags = 0);

protected:
    virtual bool onEvent(const SkEvent&);
    virtual void onDraw(SkCanvas*);
    virtual void onInflate(const SkDOM& dom, const SkDOM::Node*);

private:
    typedef SkButtonWidget INHERITED;
};

#include "SkTextBox.h"

class SkStaticTextView : public SkView {
public:
            SkStaticTextView(uint32_t flags = 0);
    virtual ~SkStaticTextView();

    enum Mode {
        kFixedSize_Mode,
        kAutoWidth_Mode,
        kAutoHeight_Mode,

        kModeCount
    };
    Mode    getMode() const { return (Mode)fMode; }
    void    setMode(Mode);

    SkTextBox::SpacingAlign getSpacingAlign() const { return (SkTextBox::SpacingAlign)fSpacingAlign; }
    void    setSpacingAlign(SkTextBox::SpacingAlign);

    void    getMargin(SkPoint* margin) const;
    void    setMargin(SkScalar dx, SkScalar dy);

    size_t  getText(SkString* text = NULL) const;
    size_t  getText(char text[] = NULL) const;
    void    setText(const SkString&);
    void    setText(const char text[]);
    void    setText(const char text[], size_t len);

    void    getPaint(SkPaint*) const;
    void    setPaint(const SkPaint&);

protected:
    // overrides
    virtual void onDraw(SkCanvas*);
    virtual void onInflate(const SkDOM& dom, const SkDOM::Node*);

private:
    SkPoint     fMargin;
    SkString    fText;
    SkPaint     fPaint;
    uint8_t     fMode;
    uint8_t     fSpacingAlign;

    void computeSize();

    typedef SkView INHERITED;
};

class SkBitmapView : public SkView {
public:
            SkBitmapView(uint32_t flags = 0);
    virtual ~SkBitmapView();

    bool    getBitmap(SkBitmap*) const;
    void    setBitmap(const SkBitmap*, bool viewOwnsPixels);
    bool    loadBitmapFromFile(const char path[]);

protected:
    virtual void onDraw(SkCanvas*);
    virtual void onInflate(const SkDOM&, const SkDOM::Node*);

private:
    SkBitmap    fBitmap;
    typedef SkView INHERITED;
};

/////////////////////////////////////////////////////////////////////////////

class SkShader;
class SkInterpolator;

class SkWidgetView : public SkView {
public:
            SkWidgetView(uint32_t flags = 0);
    virtual ~SkWidgetView();

    static const char*  GetEventType();
};

class SkSliderView : public SkWidgetView {
public:
    SkSliderView(uint32_t flags = 0);

    uint16_t    getValue() const { return fValue; }
    uint16_t    getMax() const { return fMax; }

    void    setMax(U16CPU max);
    void    setValue(U16CPU value);

protected:
    virtual void    onDraw(SkCanvas*);
    virtual Click*  onFindClickHandler(SkScalar x, SkScalar y);
    virtual bool    onClick(Click*);

private:
    uint16_t fValue, fMax;

    typedef SkWidgetView INHERITED;
};

//////////////////////////////////////////////////////////////////////////////

class SkHasLabelView : public SkView {
public:
    void    getLabel(SkString*) const;
    void    setLabel(const SkString&);
    void    setLabel(const char label[]);

protected:
    SkString    fLabel;

    // called when the label changes
    virtual void onLabelChange();

    // overrides
    virtual void onInflate(const SkDOM& dom, const SkDOM::Node*);
};

class SkPushButtonView : public SkHasLabelView {
public:
    SkPushButtonView(uint32_t flags = 0);

protected:
    virtual void onDraw(SkCanvas*);
    virtual void onInflate(const SkDOM& dom, const SkDOM::Node*);
};

class SkCheckBoxView : public SkHasLabelView {
public:
    SkCheckBoxView(uint32_t flags = 0);

    enum State {
        kOff_State,
        kOn_State,
        kMaybe_State
    };
    State   getState() const { return fState; }
    void    setState(State);

protected:
    virtual void onDraw(SkCanvas*);
    virtual void onInflate(const SkDOM& dom, const SkDOM::Node*);

private:
    State   fState;
};

class SkProgressView : public SkView {
public:
    SkProgressView(uint32_t flags = 0);
    virtual ~SkProgressView();

    uint16_t    getValue() const { return fValue; }
    uint16_t    getMax() const { return fMax; }

    void    setMax(U16CPU max);
    void    setValue(U16CPU value);

protected:
    virtual void onDraw(SkCanvas*);
    virtual void onInflate(const SkDOM& dom, const SkDOM::Node* node);

private:
    uint16_t    fValue, fMax;
    SkShader*   fOnShader, *fOffShader;
    SkInterpolator* fInterp;
    bool fDoInterp;

    typedef SkView INHERITED;
};

class SkTextView : public SkView {
public:
            SkTextView(uint32_t flags = 0);
    virtual ~SkTextView();

    enum AnimaDir {
        kNeutral_AnimDir,
        kForward_AnimDir,
        kBackward_AnimDir,
        kAnimDirCount
    };

    void    getText(SkString*) const;
    void    setText(const SkString&, AnimaDir dir = kNeutral_AnimDir);
    void    setText(const char text[], AnimaDir dir = kNeutral_AnimDir);
    void    setText(const char text[], size_t len, AnimaDir dir = kNeutral_AnimDir);

    void    getMargin(SkPoint* margin) const;
    void    setMargin(const SkPoint&);

    SkPaint&    paint() { return fPaint; }

protected:
    virtual void onDraw(SkCanvas*);
    virtual void onInflate(const SkDOM& dom, const SkDOM::Node* node);

private:
    SkString fText;
    SkPaint  fPaint;
    SkPoint  fMargin;

    class Interp;
    Interp* fInterp;
    bool    fDoInterp;
    // called by the other setText methods. This guy does not check for !=
    // before doing the assign, so the caller must check for us
    void privSetText(const SkString&, AnimaDir dir);

    typedef SkView INHERITED;
};

//////////////////////////////////////////////////////////

class SkEvent;

class SkListSource : public SkEventSink {
public:
    virtual int countRows() = 0;
    virtual void getRow(int index, SkString* left, SkString* right) = 0;
    virtual SkEvent* getEvent(int index);

    static SkListSource* CreateFromDir(const char path[], const char suffix[],
                                        const char targetPrefix[]);
    static SkListSource* CreateFromDOM(const SkDOM& dom, const SkDOM::Node* node);
};

class SkListView : public SkWidgetView {
public:
            SkListView(uint32_t flags = 0);
    virtual ~SkListView();

    SkScalar    getRowHeight() const { return fRowHeight; }
    void        setRowHeight(SkScalar);

    /** Return the index of the selected row, or -1 if none
    */
    int     getSelection() const { return fCurrIndex; }
    /** Set the index of the selected row, or -1 for none
    */
    void    setSelection(int);

    void    moveSelectionUp();
    void    moveSelectionDown();

    enum Attr {
        kBG_Attr,
        kNormalText_Attr,
        kHiliteText_Attr,
        kHiliteCell_Attr,
        kAttrCount
    };
    SkPaint&    paint(Attr);

    SkListSource*   getListSource() const { return fSource; }
    SkListSource*   setListSource(SkListSource*);

#if 0
    enum Action {
        kSelectionChange_Action,
        kSelectionPicked_Action,
        kActionCount
    };
    /** If event is not null, it is retained by the view, and a copy
        of the event will be posted to its listeners when the specified
        action occurs. If event is null, then no event will be posted for
        the specified action.
    */
    void    setActionEvent(Action, SkEvent* event);
#endif

protected:
    virtual void onDraw(SkCanvas*);
    virtual void onSizeChange();
    virtual bool onEvent(const SkEvent&);
    virtual void onInflate(const SkDOM& dom, const SkDOM::Node* node);

private:
    SkPaint         fPaint[kAttrCount];
    SkListSource*   fSource;
    SkScalar        fRowHeight;
    int             fCurrIndex;     // logical index
    int             fScrollIndex;   // logical index of top-most visible row
    int             fVisibleRowCount;
    SkString*       fStrCache;

    void    dirtyStrCache();
    void    ensureStrCache(int visibleCount);

    int     logicalToVisualIndex(int index) const { return index - fScrollIndex; }
    void    invalSelection();
    bool    getRowRect(int index, SkRect*) const;
    void    ensureSelectionIsVisible();

    typedef SkWidgetView INHERITED;
};

//////////////////////////////////////////////////////////

class SkGridView : public SkWidgetView {
public:
            SkGridView(uint32_t flags = 0);
    virtual ~SkGridView();

    void    getCellSize(SkPoint*) const;
    void    setCellSize(SkScalar x, SkScalar y);

    /** Return the index of the selected item, or -1 if none
    */
    int     getSelection() const { return fCurrIndex; }
    /** Set the index of the selected row, or -1 for none
    */
    void    setSelection(int);

    void    moveSelectionUp();
    void    moveSelectionDown();

    enum Attr {
        kBG_Attr,
        kHiliteCell_Attr,
        kAttrCount
    };
    SkPaint&    paint(Attr);

    SkListSource*   getListSource() const { return fSource; }
    SkListSource*   setListSource(SkListSource*);

protected:
    virtual void onDraw(SkCanvas*);
    virtual void onSizeChange();
    virtual bool onEvent(const SkEvent&);
    virtual void onInflate(const SkDOM& dom, const SkDOM::Node* node);

private:
    SkView*         fScrollBar;
    SkPaint         fPaint[kAttrCount];
    SkListSource*   fSource;
    int             fCurrIndex;     // logical index

    SkPoint         fCellSize;
    SkIPoint        fVisibleCount;

    int     logicalToVisualIndex(int index) const { return index; }
    void    invalSelection();
    bool    getCellRect(int index, SkRect*) const;
    void    ensureSelectionIsVisible();

    typedef SkWidgetView INHERITED;
};

#endif

