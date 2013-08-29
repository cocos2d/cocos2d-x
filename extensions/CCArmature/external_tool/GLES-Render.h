/*
* Copyright (c) 2006-2007 Erin Catto http://www.gphysics.com
*
* iPhone port by Simon Oliver - http://www.simonoliver.com - http://www.handcircus.com
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef CC_ARMATURE_GLES_RENDER_H
#define CC_ARMATURE_GLES_RENDER_H

#include "Box2D/Box2D.h"
#include "cocos2d.h"
#include "ExtensionMacros.h"

struct b2AABB;

NS_CC_EXT_BEGIN

// This class implements debug drawing callbacks that are invoked
// inside b2World::Step.
class GLESDebugDraw : public b2Draw
{
    float32 mRatio;
    cocos2d::CCGLProgram* mShaderProgram;
    GLint        mColorLocation;

    void initShader( void );
public:
    GLESDebugDraw();

    GLESDebugDraw( float32 ratio );

    virtual void DrawPolygon(const b2Vec2* vertices, int vertexCount, const b2Color& color);

    virtual void DrawSolidPolygon(const b2Vec2* vertices, int vertexCount, const b2Color& color);

    virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);

    virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);

    virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);

    virtual void DrawTransform(const b2Transform& xf);

    virtual void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color);

    virtual void DrawString(int x, int y, const char* string, ...); 

    virtual void DrawAABB(b2AABB* aabb, const b2Color& color);
};

NS_CC_EXT_END

#endif
