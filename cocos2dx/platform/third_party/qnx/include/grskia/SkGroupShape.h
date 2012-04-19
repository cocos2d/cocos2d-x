#ifndef SkGroupShape_DEFINED
#define SkGroupShape_DEFINED

#include "SkMatrix.h"
#include "SkShape.h"
#include "SkTDArray.h"
#include "SkThread.h"

template <typename T> class SkTRefCnt : public T {
public:
    SkTRefCnt() : fRefCnt(1) {}
    ~SkTRefCnt() { SkASSERT(1 == fRefCnt); }

    int32_t getRefCnt() const { return fRefCnt; }
    
    /** Increment the reference count. Must be balanced by a call to unref().
     */
    void ref() const {
        SkASSERT(fRefCnt > 0);
        sk_atomic_inc(&fRefCnt);
    }
    
    /** Decrement the reference count. If the reference count is 1 before the
        decrement, then call delete on the object. Note that if this is the
        case, then the object needs to have been allocated via new, and not on
        the stack.
     */
    void unref() const {
        SkASSERT(fRefCnt > 0);
        if (sk_atomic_dec(&fRefCnt) == 1) {
            fRefCnt = 1;    // so our destructor won't complain
            SkDELETE(this);
        }
    }
    
    static void SafeRef(const SkTRefCnt* obj) {
        if (obj) {
            obj->ref();
        }
    }
    
    static void SafeUnref(const SkTRefCnt* obj) {
        if (obj) {
            obj->unref();
        }
    }
    
private:
    mutable int32_t fRefCnt;
};

class SkMatrixRef : public SkTRefCnt<SkMatrix> {
public:
    SkMatrixRef() { this->reset(); }
    explicit SkMatrixRef(const SkMatrix& matrix) {
        SkMatrix& m = *this;
        m = matrix;
    }
    
    SkMatrix& operator=(const SkMatrix& matrix) {
        SkMatrix& m = *this;
        m = matrix;
        return m;
    }
};

class SkGroupShape : public SkShape {
public:
            SkGroupShape();
    virtual ~SkGroupShape();

    /** Return the number of child shapes in this group
     */
    int countShapes() const;

    /** Return the shape at the specified index. Note this does not affect the
        owner count of the index'd shape. If index is out of range, returns NULL
     */
    SkShape* getShape(int index, SkMatrixRef** = NULL) const;
    
    /** Helper function to return the matrixref of the specified shape.
     */
    SkMatrixRef* getShapeMatrixRef(int index) const {
        SkMatrixRef* mr = NULL;
        (void)this->getShape(index, &mr);
        return mr;
    }

    /** Ref the specified shape, and insert it into the child list at the
        specified index. If index == countShapes(), then the shape will be
        appended to the child list, otherwise if index is out of range, the
        shape is not added. Either way, the shape parameter is returned.
     
        Child shapes are drawn in order, after the parent, so the shape at index
        0 will be drawn first, and the shape at index countShapes() - 1 will be
        drawn last.
     */
    void addShape(int index, SkShape*, SkMatrixRef* = NULL);

    void addShape(int index, SkShape* shape, const SkMatrix& matrix) {
        SkMatrixRef* mr = SkNEW_ARGS(SkMatrixRef, (matrix));
        this->addShape(index, shape, mr);
        mr->unref();
    }

    /** Helper method to append a shape, passing countShapes() for the index
     */
    SkShape* appendShape(SkShape* shape, SkMatrixRef* mr = NULL) {
        this->addShape(this->countShapes(), shape, mr);
        return shape;
    }
    
    SkShape* appendShape(SkShape* shape, const SkMatrix& matrix) {
        this->addShape(this->countShapes(), shape, matrix);
        return shape;
    }
    
    /** Unref the specified index, and remove it from the child list. If index
        is out of range, does nothing.
     */
    void removeShape(int index);

    /** Unrefs and removes all of the child shapes
     */
    void removeAllShapes();

    // overrides
    virtual Factory getFactory();
    virtual void flatten(SkFlattenableWriteBuffer&);

    // public for Registrar
    static SkFlattenable* CreateProc(SkFlattenableReadBuffer&);

protected:
    // overrides
    virtual void onDraw(SkCanvas*);

    SkGroupShape(SkFlattenableReadBuffer&);

private:
    struct Rec {
        SkShape*     fShape;
        SkMatrixRef* fMatrixRef;
    };
    SkTDArray<Rec> fList;

    typedef SkShape INHERITED;
};

#endif
