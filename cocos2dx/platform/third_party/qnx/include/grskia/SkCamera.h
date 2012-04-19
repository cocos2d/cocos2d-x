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



//  Inspired by Rob Johnson's most excellent QuickDraw GX sample code

#ifndef SkCamera_DEFINED
#define SkCamera_DEFINED

#include "Sk64.h"
#include "SkMatrix.h"

class SkCanvas;

#ifdef SK_SCALAR_IS_FIXED
    typedef SkFract SkUnitScalar;
    #define SK_UnitScalar1          SK_Fract1
    #define SkUnitScalarMul(a, b)   SkFractMul(a, b)
    #define SkUnitScalarDiv(a, b)   SkFractDiv(a, b)
#else
    typedef float   SkUnitScalar;
    #define SK_UnitScalar1          SK_Scalar1
    #define SkUnitScalarMul(a, b)   SkScalarMul(a, b)
    #define SkUnitScalarDiv(a, b)   SkScalarDiv(a, b)
#endif

struct SkUnit3D {
    SkUnitScalar    fX, fY, fZ;

    void set(SkUnitScalar x, SkUnitScalar y, SkUnitScalar z)
    {
        fX = x; fY = y; fZ = z;
    }
    static SkUnitScalar Dot(const SkUnit3D&, const SkUnit3D&);
    static void Cross(const SkUnit3D&, const SkUnit3D&, SkUnit3D* cross);
};

struct SkPoint3D {
    SkScalar    fX, fY, fZ;

    void set(SkScalar x, SkScalar y, SkScalar z)
    {
        fX = x; fY = y; fZ = z;
    }
    SkScalar    normalize(SkUnit3D*) const;
};
typedef SkPoint3D SkVector3D;

struct SkMatrix3D {
    SkScalar    fMat[3][4];
    
    void reset();

    void setRow(int row, SkScalar a, SkScalar b, SkScalar c, SkScalar d = 0)
    {
        SkASSERT((unsigned)row < 3);
        fMat[row][0] = a;
        fMat[row][1] = b;
        fMat[row][2] = c;
        fMat[row][3] = d;
    }

    void setRotateX(SkScalar deg);
    void setRotateY(SkScalar deg);
    void setRotateZ(SkScalar deg);
    void setTranslate(SkScalar x, SkScalar y, SkScalar z);
    
    void preRotateX(SkScalar deg);
    void preRotateY(SkScalar deg);
    void preRotateZ(SkScalar deg);
    void preTranslate(SkScalar x, SkScalar y, SkScalar z);

    void setConcat(const SkMatrix3D& a, const SkMatrix3D& b);
    void mapPoint(const SkPoint3D& src, SkPoint3D* dst) const;
    void mapVector(const SkVector3D& src, SkVector3D* dst) const;

    void mapPoint(SkPoint3D* v) const
    {
        this->mapPoint(*v, v);
    }
    void mapVector(SkVector3D* v) const
    {
        this->mapVector(*v, v);
    }
};

class SkPatch3D {
public:
    SkPatch3D();

    void    reset();
    void    transform(const SkMatrix3D&, SkPatch3D* dst = NULL) const;

    // dot a unit vector with the patch's normal
    SkScalar dotWith(SkScalar dx, SkScalar dy, SkScalar dz) const;
    SkScalar dotWith(const SkVector3D& v) const
    {
        return this->dotWith(v.fX, v.fY, v.fZ);
    }

    // depreicated, but still here for animator (for now)
    void rotate(SkScalar x, SkScalar y, SkScalar z) {}
    void rotateDegrees(SkScalar x, SkScalar y, SkScalar z) {}

private:
public: // make public for SkDraw3D for now
    SkVector3D  fU, fV;
    SkPoint3D   fOrigin;
    
    friend class SkCamera3D;
};

class SkCamera3D {
public:
    SkCamera3D();

    void reset();
    void update();
    void patchToMatrix(const SkPatch3D&, SkMatrix* matrix) const;

    SkPoint3D   fLocation;
    SkPoint3D   fAxis;
    SkPoint3D   fZenith;
    SkPoint3D   fObserver;

private:
    mutable SkMatrix    fOrientation;
    mutable bool        fNeedToUpdate;

    void doUpdate() const;
};

class Sk3DView : SkNoncopyable {
public:
    Sk3DView();
    ~Sk3DView();

    void save();
    void restore();

    void translate(SkScalar x, SkScalar y, SkScalar z);
    void rotateX(SkScalar deg);
    void rotateY(SkScalar deg);
    void rotateZ(SkScalar deg);

#ifdef ANDROID
    void setCameraLocation(SkScalar x, SkScalar y, SkScalar z);
#endif

    void getMatrix(SkMatrix*) const;
    void applyToCanvas(SkCanvas*) const;

    SkScalar dotWithNormal(SkScalar dx, SkScalar dy, SkScalar dz) const;
    
private:
    struct Rec {
        Rec*        fNext;
        SkMatrix3D  fMatrix;
    };
    Rec*        fRec;
    Rec         fInitialRec;
    SkCamera3D  fCamera;
};

#endif

