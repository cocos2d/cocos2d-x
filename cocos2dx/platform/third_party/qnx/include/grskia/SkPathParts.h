/* libs/graphics/animator/SkPathParts.h
**
** Copyright 2006, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License"); 
** you may not use this file except in compliance with the License. 
** You may obtain a copy of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** Unless required by applicable law or agreed to in writing, software 
** distributed under the License is distributed on an "AS IS" BASIS, 
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
** See the License for the specific language governing permissions and 
** limitations under the License.
*/

#ifndef SkPathParts_DEFINED
#define SkPathParts_DEFINED

#include "SkDisplayable.h"
#include "SkMemberInfo.h"
#include "SkPath.h"

class SkDrawPath;
class SkDrawMatrix;

class SkPathPart : public SkDisplayable {
public:
    SkPathPart();
    virtual bool add() = 0;
    virtual void dirty();
    virtual SkDisplayable* getParent() const;
    virtual bool setParent(SkDisplayable* parent);
#ifdef SK_DEBUG
    virtual bool isPathPart() const { return true; }
#endif
protected:
    SkDrawPath* fPath;
};

class SkMoveTo : public SkPathPart {
    DECLARE_MEMBER_INFO(MoveTo);
    SkMoveTo();
    virtual bool add();
protected:
    SkScalar x;
    SkScalar y;
};

class SkRMoveTo : public SkMoveTo {
    DECLARE_MEMBER_INFO(RMoveTo);
    virtual bool add();
private:
    typedef SkMoveTo INHERITED;
};

class SkLineTo : public SkPathPart {
    DECLARE_MEMBER_INFO(LineTo);
    SkLineTo();
    virtual bool add();
protected:
    SkScalar x;
    SkScalar y;
};

class SkRLineTo : public SkLineTo {
    DECLARE_MEMBER_INFO(RLineTo);
    virtual bool add();
private:
    typedef SkLineTo INHERITED;
};

class SkQuadTo : public SkPathPart {
    DECLARE_MEMBER_INFO(QuadTo);
    SkQuadTo();
    virtual bool add();
protected:
    SkScalar x1;
    SkScalar y1;
    SkScalar x2;
    SkScalar y2;
};

class SkRQuadTo : public SkQuadTo {
    DECLARE_MEMBER_INFO(RQuadTo);
    virtual bool add();
private:
    typedef SkQuadTo INHERITED;
};

class SkCubicTo : public SkPathPart {
    DECLARE_MEMBER_INFO(CubicTo);
    SkCubicTo();
    virtual bool add();
protected:
    SkScalar x1;
    SkScalar y1;
    SkScalar x2;
    SkScalar y2;
    SkScalar x3;
    SkScalar y3;
};

class SkRCubicTo : public SkCubicTo {
    DECLARE_MEMBER_INFO(RCubicTo);
    virtual bool add();
private:
    typedef SkCubicTo INHERITED;
};

class SkClose : public SkPathPart {
    DECLARE_EMPTY_MEMBER_INFO(Close);
    virtual bool add();
};

class SkAddGeom : public SkPathPart {
    DECLARE_PRIVATE_MEMBER_INFO(AddGeom);
    SkAddGeom();
protected:
    int /*SkPath::Direction*/ direction;
};

class SkAddRect : public SkAddGeom {
    DECLARE_MEMBER_INFO(AddRect);
    SkAddRect();
    virtual bool add();
protected:
    SkRect fRect;
private:
    typedef SkAddGeom INHERITED;
};

class SkAddOval : public SkAddRect {
    DECLARE_MEMBER_INFO(AddOval);
    virtual bool add();
private:
    typedef SkAddRect INHERITED;
};

class SkAddCircle : public SkAddGeom {
    DECLARE_MEMBER_INFO(AddCircle);
    SkAddCircle();
    virtual bool add();
private:
    SkScalar radius;
    SkScalar x;
    SkScalar y;
    typedef SkAddGeom INHERITED;
};

class SkAddRoundRect : public SkAddRect {
    DECLARE_MEMBER_INFO(AddRoundRect);
    SkAddRoundRect();
    virtual bool add();
private:
    SkScalar rx;
    SkScalar ry;
    typedef SkAddRect INHERITED;
};

class SkAddPath : public SkPathPart {
    DECLARE_MEMBER_INFO(AddPath);
    SkAddPath();
    virtual bool add();
private:
    typedef SkPathPart INHERITED;
    SkDrawMatrix* matrix;
    SkDrawPath* path;
};

#endif // SkPathParts_DEFINED

