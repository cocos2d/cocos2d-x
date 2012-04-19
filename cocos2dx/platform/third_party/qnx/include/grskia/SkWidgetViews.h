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

#ifndef SkWidgetViews_DEFINED
#define SkWidgetViews_DEFINED

#include "SkView.h"


enum SkWidgetEnum {
    kBorder_WidgetEnum,         //!< <sk-border>
    kButton_WidgetEnum,         //!< <sk-button>
    kImage_WidgetEnum,          //!< <sk-image>
    kList_WidgetEnum,           //!< <sk-list>
    kProgress_WidgetEnum,       //!< <sk-progress>
    kScroll_WidgetEnum,         //!< <sk-scroll>
    kText_WidgetEnum,           //!< <sk-text>
    
    kWidgetEnumCount
};

//determines which skin to use
enum SkinEnum {
    kBorder_SkinEnum,
    kButton_SkinEnum,
    kProgress_SkinEnum,
    kScroll_SkinEnum,
    kStaticText_SkinEnum,
    
    kSkinEnumCount
};

#include "SkAnimator.h"
//used for inflates
const char* get_skin_enum_path(SkinEnum se);
void init_skin_anim(const char path[], SkAnimator* anim);
void init_skin_anim(SkinEnum se, SkAnimator* anim);
void init_skin_paint(SkinEnum se, SkPaint* paint);
void inflate_paint(const SkDOM& dom, const SkDOM::Node* node, SkPaint* paint);

/** Given an enum value, return an instance of the specified widget.
    If the enum is out of range, returns null
*/
SkView* SkWidgetFactory(SkWidgetEnum);
/** Given the inflate/element name of a widget, return an instance of
    the specified widget, or null if name does not match any known
    widget type.
*/
SkView* SkWidgetFactory(const char name[]);

////////////////////////////////////////////////////////////////////////////////////////////////

class SkWidgetView : public SkView {
public:
    SkWidgetView();

    const char* getLabel() const;
    void        getLabel(SkString* label) const;

    void        setLabel(const char[]);
    void        setLabel(const char[], size_t len);
    void        setLabel(const SkString&);

    SkEvent&        event() { return fEvent; }
    const SkEvent&  event() const { return fEvent; }

    /** Returns true if the widget can post its event to its listeners.
    */
    bool    postWidgetEvent();
    
    /** Returns the sinkID of the widgetview that posted the event, or 0
    */
    static SkEventSinkID GetWidgetEventSinkID(const SkEvent&);

protected:
    /** called when the label changes. override in subclasses. default action invals the view's bounds.
        called with the old and new labels, before the label has actually changed.
    */
    virtual void onLabelChange(const char oldLabel[], const char newLabel[]);
    /** called before posting the event to our listeners. Override to add slots to the event
        before posting. Return true to proceed with posting, or false to not post the event to any
        listener. Note: the event passed in may not be the same as calling this->event().
        Be sure to call your INHERITED method as well, so that all classes in the hierarchy get a shot
        at modifying the event (and possibly returning false to abort).
    */
    virtual bool onPrepareWidgetEvent(SkEvent* evt);

    // overrides
    virtual void onInflate(const SkDOM& dom, const SkDOM::Node*);
    
private:
    SkString    fLabel;
    SkEvent     fEvent;
    
    typedef SkView INHERITED;
};

////////////////////////////////////////////////////////////////////////////////////////////////

class SkButtonView : public SkWidgetView {
public:
    // inflate: "sk-button"
    
protected:
    // overrides
    virtual bool onEvent(const SkEvent&);
private:
    typedef SkWidgetView INHERITED;
};

////////////////////////////////////////////////////////////////////////////////////////////////

class SkCheckButtonView : public SkWidgetView {
public:
    SkCheckButtonView();

    // inflate: "sk-checkbutton"
    
    enum CheckState {
        kOff_CheckState,        //!< inflate: check-state="off"
        kOn_CheckState,         //!< inflate: check-state="on"
        kUnknown_CheckState     //!< inflate: check-state="unknown"
    };
    CheckState  getCheckState() const { return (CheckState)fCheckState; }
    void        setCheckState(CheckState);

    /** use this to extract the CheckState from an event (i.e. one that as posted
        by a SkCheckButtonView). Returns true if the proper slot was present in the event,
        and sets state to that value. If no proper slot is found, returns false and does not
        modify state.
    */
    static bool GetWidgetEventCheckState(const SkEvent&, CheckState* state);

protected:
    // called when the check-state is about to change, but before it actually has
    virtual void onCheckStateChange(CheckState oldState, CheckState newState);

    // overrides
    virtual void onInflate(const SkDOM& dom, const SkDOM::Node*);
    virtual bool onPrepareWidgetEvent(SkEvent* evt);
    
private:
    uint8_t  fCheckState;
    
    typedef SkWidgetView INHERITED;
};

////////////////////////////////////////////////////////////////////////////////////////////////
#include "SkTextBox.h"

class SkStaticTextView : public SkView {
public:
            SkStaticTextView();
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

////////////////////////////////////////////////////////////////////////////////////////////////

class SkAnimator;
class SkListSource;
class SkScrollBarView;

class SkListView : public SkWidgetView {
public:
            SkListView();
    virtual ~SkListView();

    bool    hasScrollBar() const { return fScrollBar != NULL; }
    void    setHasScrollBar(bool);
    
    /** Return the number of visible rows
    */
    int     getVisibleRowCount() const { return fVisibleRowCount; }
    /** Return the index of the selected row, or -1 if none
    */
    int     getSelection() const { return fCurrIndex; }
    /** Set the index of the selected row, or -1 for none
    */
    void    setSelection(int);
    /** If possible, move the selection up and return true,
        else do nothing and return false
        If nothing is selected, select the last item (unless there are no items).
    */
    bool    moveSelectionUp();
    /** If possible, move the selection down and return true,
        else do nothing and return false.
        If nothing is selected, select the first item (unless there are no items).
    */
    bool    moveSelectionDown();

    SkListSource*   getListSource() const { return fSource; }
    SkListSource*   setListSource(SkListSource*);

    /** Call this in your event handler. If the specified event is from a SkListView,
        then it returns the index of the selected item in this list, otherwise it
        returns -1
    */
    static int GetWidgetEventListIndex(const SkEvent&);

protected:
    // overrides
    virtual void onDraw(SkCanvas*);
    virtual void onSizeChange();
    virtual bool onEvent(const SkEvent&);
    virtual void onInflate(const SkDOM& dom, const SkDOM::Node* node);
    virtual bool onPrepareWidgetEvent(SkEvent*);

private:
    enum DirtyFlags {
        kAnimCount_DirtyFlag    = 0x01,
        kAnimContent_DirtyFlag  = 0x02
    };
    void    dirtyCache(unsigned dirtyFlags);
    bool    ensureCache();

    int     logicalToVisualIndex(int index) const { return index - fScrollIndex; }
    void    invalSelection();
    SkScalar getContentWidth() const;
    bool    getRowRect(int index, SkRect*) const;
    void    ensureSelectionIsVisible();
    void    ensureVisibleRowCount();

    struct BindingRec;

    enum Heights {
        kNormal_Height,
        kSelected_Height
    };
    SkListSource*   fSource;
    SkScrollBarView*    fScrollBar;
    SkAnimator*     fAnims;
    BindingRec*     fBindings;
    SkString        fSkinName;
    SkScalar        fHeights[2];
    int16_t         fScrollIndex, fCurrIndex;
    uint16_t        fVisibleRowCount, fBindingCount;
    SkBool8         fAnimContentDirty;
    SkBool8         fAnimFocusDirty;

    typedef SkWidgetView INHERITED;
};

class SkListSource : public SkRefCnt {
public:
    virtual int countFields();
    virtual void getFieldName(int index, SkString* field);
    /** Return the index of the named field, or -1 if not found */
    virtual int findFieldIndex(const char field[]);

    virtual int countRecords();
    virtual void getRecord(int rowIndex, int fieldIndex, SkString* data);

    virtual bool prepareWidgetEvent(SkEvent*, int rowIndex);
    
    static SkListSource* Factory(const char name[]);
};

#endif
