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

#ifndef SkView_DEFINED
#define SkView_DEFINED

#include "SkEventSink.h"
#include "SkRect.h"
#include "SkDOM.h"
#include "SkTDict.h"

class SkCanvas;
class SkLayerView;

/** \class SkView

    SkView is the base class for screen management. All widgets and controls inherit
    from SkView.
*/
class SkView : public SkEventSink {
public:
    enum Flag_Shift {
        kVisible_Shift,
        kEnabled_Shift,
        kFocusable_Shift,
        kFlexH_Shift,
        kFlexV_Shift,
        kNoClip_Shift,

        kFlagShiftCount
    };
    enum Flag_Mask {
        kVisible_Mask   = 1 << kVisible_Shift,      //!< set if the view is visible
        kEnabled_Mask   = 1 << kEnabled_Shift,      //!< set if the view is enabled
        kFocusable_Mask = 1 << kFocusable_Shift,    //!< set if the view can receive focus
        kFlexH_Mask     = 1 << kFlexH_Shift,        //!< set if the view's width is stretchable
        kFlexV_Mask     = 1 << kFlexV_Shift,        //!< set if the view's height is stretchable
        kNoClip_Mask    = 1 << kNoClip_Shift,        //!< set if the view is not clipped to its bounds

        kAllFlagMasks   = (uint32_t)(0 - 1) >> (32 - kFlagShiftCount)
    };

                SkView(uint32_t flags = 0);
    virtual     ~SkView();

    /** Return the flags associated with the view
    */
    uint32_t    getFlags() const { return fFlags; }
    /** Set the flags associated with the view
    */
    void        setFlags(uint32_t flags);

    /** Helper that returns non-zero if the kVisible_Mask bit is set in the view's flags
    */
    int         isVisible() const { return fFlags & kVisible_Mask; }
    int         isEnabled() const { return fFlags & kEnabled_Mask; }
    int         isFocusable() const { return fFlags & kFocusable_Mask; }
    int         isClipToBounds() const { return !(fFlags & kNoClip_Mask); }
    /** Helper to set/clear the view's kVisible_Mask flag */
    void        setVisibleP(bool);
    void        setEnabledP(bool);
    void        setFocusableP(bool);
    void        setClipToBounds(bool);

    /** Return the view's width */
    SkScalar    width() const { return fWidth; }
    /** Return the view's height */
    SkScalar    height() const { return fHeight; }
    /** Set the view's width and height. These must both be >= 0. This does not affect the view's loc */
    void        setSize(SkScalar width, SkScalar height);
    void        setSize(const SkPoint& size) { this->setSize(size.fX, size.fY); }
    void        setWidth(SkScalar width) { this->setSize(width, fHeight); }
    void        setHeight(SkScalar height) { this->setSize(fWidth, height); }
    /** Return a rectangle set to [0, 0, width, height] */
    void        getLocalBounds(SkRect* bounds) const;

    /** Return the view's left edge */
    SkScalar    locX() const { return fLoc.fX; }
    /** Return the view's top edge */
    SkScalar    locY() const { return fLoc.fY; }
    /** Set the view's left and top edge. This does not affect the view's size */
    void        setLoc(SkScalar x, SkScalar y);
    void        setLoc(const SkPoint& loc) { this->setLoc(loc.fX, loc.fY); }
    void        setLocX(SkScalar x) { this->setLoc(x, fLoc.fY); }
    void        setLocY(SkScalar y) { this->setLoc(fLoc.fX, y); }
    /** Offset (move) the view by the specified dx and dy. This does not affect the view's size */
    void        offset(SkScalar dx, SkScalar dy);

    /** Call this to have the view draw into the specified canvas. */
    virtual void draw(SkCanvas* canvas);

    /** Call this to invalidate part of all of a view, requesting that the view's
        draw method be called. The rectangle parameter specifies the part of the view
        that should be redrawn. If it is null, it specifies the entire view bounds.
    */
    void        inval(SkRect* rectOrNull);

    //  Focus management

    SkView* getFocusView() const;
    bool    hasFocus() const;

    enum FocusDirection {
        kNext_FocusDirection,
        kPrev_FocusDirection,

        kFocusDirectionCount
    };
    bool    acceptFocus();
    SkView* moveFocus(FocusDirection);

    //  Click handling

    class Click {
    public:
        Click(SkView* target);
        virtual ~Click();

        const char* getType() const { return fType; }
        bool        isType(const char type[]) const;
        void        setType(const char type[]);     // does NOT make a copy of the string
        void        copyType(const char type[]);    // makes a copy of the string

        enum State {
            kDown_State,
            kMoved_State,
            kUp_State
        };
        SkPoint     fOrig, fPrev, fCurr;
        SkIPoint    fIOrig, fIPrev, fICurr;
        State       fState;
        void*       fOwner;
    private:
        SkEventSinkID   fTargetID;
        char*           fType;
        bool            fWeOwnTheType;

        void resetType();

        friend class SkView;
    };
    Click*  findClickHandler(SkScalar x, SkScalar y);

    static void DoClickDown(Click*, int x, int y);
    static void DoClickMoved(Click*, int x, int y);
    static void DoClickUp(Click*, int x, int y);

    /** Send the event to the view's parent, and its parent etc. until one of them
        returns true from its onEvent call. This view is returned. If no parent handles
        the event, null is returned.
     */
    SkView*     sendEventToParents(const SkEvent&);
    /** Send the query to the view's parent, and its parent etc. until one of them
        returns true from its onQuery call. This view is returned. If no parent handles
        the query, null is returned.
     */
    SkView* sendQueryToParents(SkEvent*);

    /** Depricated helper function. Just call event->post(sinkID, delay);
    */
    bool    postEvent(SkEvent* evt, SkEventSinkID sinkID, SkMSec delay) { return evt->post(sinkID, delay); }

    //  View hierarchy management

    /** Return the view's parent, or null if it has none. This does not affect the parent's reference count. */
    SkView*     getParent() const { return fParent; }
    SkView*     attachChildToFront(SkView* child);
    /** Attach the child view to this view, and increment the child's reference count. The child view is added
        such that it will be drawn before all other child views.
        The child view parameter is returned.
    */
    SkView*     attachChildToBack(SkView* child);
    /** If the view has a parent, detach the view from its parent and decrement the view's reference count.
        If the parent was the only owner of the view, this will cause the view to be deleted.
    */
    void        detachFromParent();
    /** Attach the child view to this view, and increment the child's reference count. The child view is added
        such that it will be drawn after all other child views.
        The child view parameter is returned.
    */
    /** Detach all child views from this view. */
    void        detachAllChildren();

    /** Convert the specified point from global coordinates into view-local coordinates
    */
    void        globalToLocal(SkPoint* pt) const { if (pt) this->globalToLocal(pt->fX, pt->fY, pt); }
    /** Convert the specified x,y from global coordinates into view-local coordinates, returning
        the answer in the local parameter.
    */
    void        globalToLocal(SkScalar globalX, SkScalar globalY, SkPoint* local) const;

    /** \class F2BIter
    
        Iterator that will return each of this view's children, in
        front-to-back order (the order used for clicking). The first
        call to next() returns the front-most child view. When
        next() returns null, there are no more child views.
    */
    class F2BIter {
    public:
        F2BIter(const SkView* parent);
        SkView* next();
    private:
        SkView* fFirstChild, *fChild;
    };

    /** \class B2FIter
    
        Iterator that will return each of this view's children, in
        back-to-front order (the order they are drawn). The first
        call to next() returns the back-most child view. When
        next() returns null, there are no more child views.
    */
    class B2FIter {
    public:
        B2FIter(const SkView* parent);
        SkView* next();
    private:
        SkView* fFirstChild, *fChild;
    };

    /** \class Artist
    
        Install a subclass of this in a view (calling setArtist()), and then the
        default implementation of that view's onDraw() will invoke this object
        automatically.
    */
    class Artist : public SkRefCnt {
    public:
        void draw(SkView*, SkCanvas*);
        void inflate(const SkDOM&, const SkDOM::Node*);
    protected:
        virtual void onDraw(SkView*, SkCanvas*) = 0;
        virtual void onInflate(const SkDOM&, const SkDOM::Node*);
    };
    /** Return the artist attached to this view (or null). The artist's reference
        count is not affected.
    */
    Artist* getArtist() const;
    /** Attach the specified artist (or null) to the view, replacing any existing
        artist. If the new artist is not null, its reference count is incremented.
        The artist parameter is returned.
    */
    Artist* setArtist(Artist* artist);

    /** \class Layout
    
        Install a subclass of this in a view (calling setLayout()), and then the
        default implementation of that view's onLayoutChildren() will invoke
        this object automatically.
    */
    class Layout : public SkRefCnt {
    public:
        void layoutChildren(SkView* parent);
        void inflate(const SkDOM&, const SkDOM::Node*);
    protected:
        virtual void onLayoutChildren(SkView* parent) = 0;
        virtual void onInflate(const SkDOM&, const SkDOM::Node*);
    };

    /** Return the layout attached to this view (or null). The layout's reference
        count is not affected.
    */
    Layout* getLayout() const;
    /** Attach the specified layout (or null) to the view, replacing any existing
        layout. If the new layout is not null, its reference count is incremented.
        The layout parameter is returned.
    */
    Layout* setLayout(Layout*, bool invokeLayoutNow = true);
    /** If a layout is attached to this view, call its layoutChildren() method
    */
    void    invokeLayout();

    /** Call this to initialize this view based on the specified XML node
    */
    void    inflate(const SkDOM& dom, const SkDOM::Node* node);
    /** After a view hierarchy is inflated, this may be called with a dictionary
        containing pairs of <name, view*>, where the name string was the view's
        "id" attribute when it was inflated.

        This will call the virtual onPostInflate for this view, and the recursively
        call postInflate on all of the view's children.
    */
    void    postInflate(const SkTDict<SkView*>& ids);

    SkDEBUGCODE(void dump(bool recurse) const;)

protected:
    /** Override this to draw inside the view. Be sure to call the inherited version too */
    virtual void    onDraw(SkCanvas*);
    /** Override this to be notified when the view's size changes. Be sure to call the inherited version too */
    virtual void    onSizeChange();
    /** Override this if you want to handle an inval request from this view or one of its children.
        Tyically this is only overridden by the by the "window". If your subclass does handle the
        request, return true so the request will not continue to propogate to the parent.
    */
    virtual bool    handleInval(const SkRect*);
    //! called once before all of the children are drawn (or clipped/translated)
    virtual SkCanvas* beforeChildren(SkCanvas* c) { return c; }
    //! called once after all of the children are drawn (or clipped/translated)
    virtual void afterChildren(SkCanvas* orig) {}

    //! called right before this child's onDraw is called
    virtual void beforeChild(SkView* child, SkCanvas* canvas) {}
    //! called right after this child's onDraw is called
    virtual void afterChild(SkView* child, SkCanvas* canvas) {}

    /** Override this if you might handle the click
    */
    virtual Click* onFindClickHandler(SkScalar x, SkScalar y);
    /** Override this to decide if your children are targets for a click.
        The default returns true, in which case your children views will be
        candidates for onFindClickHandler. Returning false wil skip the children
        and just call your onFindClickHandler.
     */
    virtual bool onSendClickToChildren(SkScalar x, SkScalar y);
    /** Override this to track clicks, returning true as long as you want to track
        the pen/mouse.
    */
    virtual bool    onClick(Click*);
    /** Override this to initialize your subclass from the XML node. Be sure to call the inherited version too */
    virtual void    onInflate(const SkDOM& dom, const SkDOM::Node* node);
    /** Override this if you want to perform post initialization work based on the ID dictionary built
        during XML parsing. Be sure to call the inherited version too.
    */
    virtual void    onPostInflate(const SkTDict<SkView*>&);

public:
    // default action is to inval the view
    virtual void    onFocusChange(bool gainFocusP);
protected:

    // override these if you're acting as a layer/host
    virtual bool    onGetFocusView(SkView**) const { return false; }
    virtual bool    onSetFocusView(SkView*) { return false; }

private:
    SkScalar    fWidth, fHeight;
    SkPoint     fLoc;
    SkView*     fParent;
    SkView*     fFirstChild;
    SkView*     fNextSibling;
    SkView*     fPrevSibling;
    uint8_t     fFlags;
    uint8_t     fContainsFocus;

    friend class B2FIter;
    friend class F2BIter;
    
    friend class SkLayerView;

    bool    setFocusView(SkView* fvOrNull);
    SkView* acceptFocus(FocusDirection);
    void    detachFromParent_NoLayout();
};

#endif

