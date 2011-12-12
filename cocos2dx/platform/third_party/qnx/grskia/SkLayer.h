/*
 * Copyright (C) 2010 The Android Open Source Project
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

#ifndef SkLayer_DEFINED
#define SkLayer_DEFINED

#include "SkRefCnt.h"
#include "SkTDArray.h"
#include "SkColor.h"
#include "SkMatrix.h"
#include "SkPoint.h"
#include "SkRect.h"
#include "SkSize.h"

class SkCanvas;

class SkLayer : public SkRefCnt {

public:
    SkLayer();
    SkLayer(const SkLayer&);
    virtual ~SkLayer();

    bool isInheritFromRootTransform() const;
    SkScalar getOpacity() const { return m_opacity; }
    const SkSize& getSize() const { return m_size; }
    const SkPoint& getPosition() const { return m_position; }
    const SkPoint& getAnchorPoint() const { return m_anchorPoint; }
    const SkMatrix& getMatrix() const { return fMatrix; }
    const SkMatrix& getChildrenMatrix() const { return fChildrenMatrix; }

    SkScalar getWidth() const { return m_size.width(); }
    SkScalar getHeight() const { return m_size.height(); }

    void setInheritFromRootTransform(bool);
    void setOpacity(SkScalar opacity) { m_opacity = opacity; }
    void setSize(SkScalar w, SkScalar h) { m_size.set(w, h); }
    void setPosition(SkScalar x, SkScalar y) { m_position.set(x, y); }
    void setAnchorPoint(SkScalar x, SkScalar y) { m_anchorPoint.set(x, y); }
    void setMatrix(const SkMatrix&);
    void setChildrenMatrix(const SkMatrix&);

    // children

    /** Return the number of layers in our child list.
     */
    int countChildren() const;

    /** Return the child at the specified index (starting at 0). This does not
        affect the reference count of the child.
     */
    SkLayer* getChild(int index) const;

    /** Add this layer to our child list at the end (top-most), and ref() it.
        If it was already in another hierarchy, remove it from that list.
        Return the new child.
     */
    SkLayer* addChild(SkLayer* child);

    /** Remove this layer from its parent's list (or do nothing if it has no
        parent.) If it had a parent, then unref() is called.
     */
    void detachFromParent();

    /** Remove, and unref(), all of the layers in our child list.
     */
    void removeChildren();

    /** Return our parent layer, or NULL if we have none.
     */
    SkLayer* getParent() const { return fParent; }

    /** Return the root layer in this hiearchy. If this layer is the root
        (i.e. has no parent), then this returns itself.
     */
    SkLayer* getRootLayer() const;

    // coordinate system transformations

    /** Return, in matrix, the matix transfomations that are applied locally
        when this layer draws (i.e. its position and matrix/anchorPoint).
        This does not include the childrenMatrix, since that is only applied
        after this layer draws (but before its children draw).
     */
    void getLocalTransform(SkMatrix* matrix) const;

    /** Return, in matrix, the concatenation of transforms that are applied
        from this layer's root parent to the layer itself.
        This is the matrix that is applied to the layer during drawing.
     */
    void localToGlobal(SkMatrix* matrix) const;

    // paint method

    void draw(SkCanvas*, SkScalar opacity);
    void draw(SkCanvas* canvas) {
        this->draw(canvas, SK_Scalar1);
    }

protected:
    virtual void onDraw(SkCanvas*, SkScalar opacity);

private:
    enum Flags {
        kInheritFromRootTransform_Flag = 0x01
    };

    SkLayer*    fParent;
    SkScalar    m_opacity;
    SkSize      m_size;
    SkPoint     m_position;
    SkPoint     m_anchorPoint;
    SkMatrix    fMatrix;
    SkMatrix    fChildrenMatrix;
    uint32_t    fFlags;

    SkTDArray<SkLayer*> m_children;

    typedef SkRefCnt INHERITED;
};

#endif
