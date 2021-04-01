/****************************************************************************
 Copyright (c) 2015-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __PHYSICS_3D_VIEWER_H__
#define __PHYSICS_3D_VIEWER_H__

#include "math/CCMath.h"
#include "base/CCRef.h"
#include "base/ccTypes.h"
#include "base/ccConfig.h"
#include "renderer/CCCustomCommand.h"
#include "renderer/backend/ProgramState.h"
#include "renderer/backend/Types.h"

#if CC_USE_3D_PHYSICS

#if (CC_ENABLE_BULLET_INTEGRATION)
#include "bullet/LinearMath/btIDebugDraw.h"

NS_CC_BEGIN

/**
 * @addtogroup _3d
 * @{
 */

class Renderer;

/** @brief Physics3DDebugDrawer: debug draw the physics object, used by Physics3DWorld */
class Physics3DDebugDrawer : public btIDebugDraw
{
public:

    Physics3DDebugDrawer();
    virtual ~Physics3DDebugDrawer();

    void draw(cocos2d::Renderer *renderer);

    // override function
    virtual void	drawLine(const btVector3& from,const btVector3& to,const btVector3& color) override;
    virtual void	drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color) override;
    virtual void	reportErrorWarning(const char* warningString) override;
    virtual void	draw3dText(const btVector3& location,const char* textString) override;
    virtual void	setDebugMode(int debugMode) override;
    virtual int		getDebugMode() const override;

    void clear();

protected:

    void init();
    void onBeforeDraw();
    void onAfterDraw();

protected:

    struct V3F_V4F
    {
        cocos2d::Vec3 vertex;
        cocos2d::Vec4 color;
    };

    std::vector<V3F_V4F>                _buffer;
    cocos2d::backend::UniformLocation   _locMVP;

    cocos2d::BlendFunc                  _blendFunc      = BlendFunc::DISABLE;
    cocos2d::CustomCommand              _customCommand;
    cocos2d::backend::ProgramState *    _programState   = nullptr;

    bool                                _dirty          = true;
    int                                 _debugMode      = DBG_DrawWireframe | DBG_DrawConstraints | DBG_DrawConstraintLimits;

private:
    bool                                _oldDepthTestEnabled    = false;
};

// end of 3d group
/// @}

NS_CC_END

#endif // CC_ENABLE_BULLET_INTEGRATION

#endif // CC_USE_3D_PHYSICS

#endif // __PHYSICS_3D_VIEWER_H__
