/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.
 Copyright (c) 2014 GamePlay3D team
 
 http://www.cocos2d-x.org


 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.

 Ideas taken from:
   - GamePlay3D: http://gameplay3d.org/
   - OGRE3D: http://www.ogre3d.org/
   - Qt3D: http://qt-project.org/

 ****************************************************************************/

#ifndef __cocos2d_libs__CCRenderState__
#define __cocos2d_libs__CCRenderState__

#include <string>
#include <functional>
#include <cstdint>

#include "platform/CCPlatformMacros.h"
#include "base/CCRef.h"
#include "base/ccTypes.h"
#include "base/CCVector.h"

NS_CC_BEGIN

class Texture2D;
class Pass;

/**
 * Defines the rendering state of the graphics device.
 */
/**
 * @addtogroup support
 * @{
 */

/**
 * @class RenderState
 * @brief
 * @~english
 * Defines the rendering state of the graphics device.
 * @~chinese 定义显卡的渲染状态。
 */

class CC_DLL RenderState : public Ref
{
    friend class Material;
    friend class Technique;
    friend class Pass;

public:
    /**
     * @~english Static initializer that is called during game startup.
     * @~chinese 静态初始化函数，游戏开始运行时调用。
     */
    static void initialize();

    /**
     * @~english Static finalizer that is called during game shutdown.
     * @~chinese 静态销毁函数，当游戏结束的时候调用
     */
    static void finalize();

    /**
     * @~english Get name
     * @~chinese 获取名称
     * @return @~english Name. @~chinese 名称。
     */
    std::string getName() const;

    /** 
     * @~english Texture that will use in the CC_Texture0 uniform.
     Added to be backwards compatible. Use Samplers from .material instead.
     * @~chinese 这个函数是为了跟之前的代码兼容，这张贴图通过CC_Texture0传递到shader中。 推荐用.material文件中的Sampler来代替。
     * @param texture @~english Texture to be binding. @~chinese 将要绑定的贴图。
     */
    void setTexture(Texture2D* texture);

    /** 
     * @~english Returns the texture that is going to be used for CC_Texture0.
     Added to be backwards compatible.
     * @~chinese 为了跟之前的旧代码兼容，这个函数返回将要传递的shader CC_Texture0的贴图。
     * @return @~english texture that is going to be used for CC_Texture0. @~chinese 被CC_Texture0使用的贴图。
     */
    Texture2D* getTexture() const;

    /**
     * @~english Binds the render state for this RenderState and any of its parents, top-down,
     * for the given pass.
     * @~chinese 绑定渲染状态，从父节点到根节点应用渲染状态。
     * @param pass @~english Not used. @~chinese 没有用到。
     */
    void bind(Pass* pass);

    /**
     * @~english Returns the topmost RenderState in the hierarchy below the given RenderState.
     * @~chinese 获取给定参数下面的RenderState。
     * @return @~english The top most render state below the given RenderState. @~chinese 给定RenderState下面的RenderState。
     */
    RenderState* getTopmost(RenderState* below);
    
    void setParent(RenderState* parent) { _parent = parent; }

    enum Blend
    {
        BLEND_ZERO = GL_ZERO,
        BLEND_ONE = GL_ONE,
        BLEND_SRC_COLOR = GL_SRC_COLOR,
        BLEND_ONE_MINUS_SRC_COLOR = GL_ONE_MINUS_SRC_COLOR,
        BLEND_DST_COLOR = GL_DST_COLOR,
        BLEND_ONE_MINUS_DST_COLOR = GL_ONE_MINUS_DST_COLOR,
        BLEND_SRC_ALPHA = GL_SRC_ALPHA,
        BLEND_ONE_MINUS_SRC_ALPHA = GL_ONE_MINUS_SRC_ALPHA,
        BLEND_DST_ALPHA = GL_DST_ALPHA,
        BLEND_ONE_MINUS_DST_ALPHA = GL_ONE_MINUS_DST_ALPHA,
        BLEND_CONSTANT_ALPHA = GL_CONSTANT_ALPHA,
        BLEND_ONE_MINUS_CONSTANT_ALPHA = GL_ONE_MINUS_CONSTANT_ALPHA,
        BLEND_SRC_ALPHA_SATURATE = GL_SRC_ALPHA_SATURATE
    };

    /**
     * @~english Defines the supported depth compare functions.
     *
     * Depth compare functions specify the comparison that takes place between the
     * incoming pixel's depth value and the depth value already in the depth buffer.
     * If the compare function passes, the new pixel will be drawn.
     *
     * The initial depth compare function is DEPTH_LESS.
     *
     * @~chinese 定义深度比较函数， 深度比较函数定义了将要绘制的像素的深度与在深度缓冲中的像素深度比较与替换的规则。如果比较函数通过了，那么新的像素将被绘制。深度比较函数的初始值为DEPTH_LESS。
     */
    enum DepthFunction
    {
        DEPTH_NEVER = GL_NEVER,
        DEPTH_LESS = GL_LESS,
        DEPTH_EQUAL = GL_EQUAL,
        DEPTH_LEQUAL = GL_LEQUAL,
        DEPTH_GREATER = GL_GREATER,
        DEPTH_NOTEQUAL = GL_NOTEQUAL,
        DEPTH_GEQUAL = GL_GEQUAL,
        DEPTH_ALWAYS = GL_ALWAYS
    };

    /**
     * @~english Defines culling criteria for front-facing, back-facing and both-side
     * facets.
     * @~chinese 定义面的裁剪方式，前面、背面和双面裁剪。
     */
    enum CullFaceSide
    {
        CULL_FACE_SIDE_BACK = GL_BACK,
        CULL_FACE_SIDE_FRONT = GL_FRONT,
        CULL_FACE_SIDE_FRONT_AND_BACK = GL_FRONT_AND_BACK
    };

    /**
     * @~english Defines the winding of vertices in faces that are considered front facing.
     *
     * The initial front face mode is set to FRONT_FACE_CCW.
     * @~chinese 定义前面的方向，初始情况下逆时针为前面，FRONT_FACE_CCW。
     */
    enum FrontFace
    {
        FRONT_FACE_CW = GL_CW,
        FRONT_FACE_CCW = GL_CCW
    };

    /**
     * @~english Defines the supported stencil compare functions.
     *
     * Stencil compare functions determine if a new pixel will be drawn.
     *
     * The initial stencil compare function is STENCIL_ALWAYS.
     * @~chinese 定义模板比较函数，模板比较函数将决定一个像素是否被绘制。初始模板比较函数为STENCIL_ALWAYS。
     */
    enum StencilFunction
    {
        STENCIL_NEVER = GL_NEVER,
        STENCIL_ALWAYS = GL_ALWAYS,
        STENCIL_LESS = GL_LESS,
        STENCIL_LEQUAL = GL_LEQUAL,
        STENCIL_EQUAL = GL_EQUAL,
        STENCIL_GREATER = GL_GREATER,
        STENCIL_GEQUAL = GL_GEQUAL,
        STENCIL_NOTEQUAL = GL_NOTEQUAL
    };

    /**
     * @~english Defines the supported stencil operations to perform.
     *
     * Stencil operations determine what should happen to the pixel if the
     * stencil test fails, passes, or passes but fails the depth test.
     *
     * The initial stencil operation is STENCIL_OP_KEEP.
     * @~chinese 定义对模板缓冲进行的操作。 模板操作决定在像素的模板测试失败、通过或者通过模板测试而没有通过深度测试的时候将要进行的操作。初始模板操作为STENCIL_OP_KEEP。
     */
    enum StencilOperation
    {
        STENCIL_OP_KEEP = GL_KEEP,
        STENCIL_OP_ZERO = GL_ZERO,
        STENCIL_OP_REPLACE = GL_REPLACE,
        STENCIL_OP_INCR = GL_INCR,
        STENCIL_OP_DECR = GL_DECR,
        STENCIL_OP_INVERT = GL_INVERT,
        STENCIL_OP_INCR_WRAP = GL_INCR_WRAP,
        STENCIL_OP_DECR_WRAP = GL_DECR_WRAP
    };

    /**
     * @class StateBlock
     * @brief
     * @~english Defines a block of fixed-function render states that can be applied to a
     * RenderState object.
     * @~chinese 一系列渲染状态的组合，可以应用到RenderState物体上。
     */
    class CC_DLL StateBlock : public Ref
    {
        friend class RenderState;
        friend class Pass;
        friend class RenderQueue;
        friend class Renderer;
        
    public:
        /**
         * @~english Creates a new StateBlock with default render state settings.
         * @~chinese 用缺省的渲染状态设置创建新的StateBlock
         * @return @~english Created StateBlock. @~chinese 新创建的StateBlock。
         */
        static StateBlock* create();

        /** @~english The recommended way to create StateBlocks is by calling `create`.
         * Don't use `new` or `delete` on them.
         * @~chinese 构造函数，推荐使用create方法来创建。
         */
        StateBlock();
        
        /** @~english Destructor.
         * @~chinese 析构函数。
         */
        ~StateBlock();

        /**
         * @~english Binds the state in this StateBlock to the renderer.
         *
         * This method handles both setting and restoring of render states to ensure that
         * only the state explicitly defined by this StateBlock is applied to the renderer.
         * @~chinese 绑定渲染状态，这个函数除了应用RenderBlock中设置的渲染状态外，也会恢复那些没有在StateBlock中设置的状态到缺省的渲染状态。
         */
        void bind();

        /**
         * @~english Explicitly sets the source and destination used in the blend function for this render state.
         *
         * Note that the blend function is only applied when blending is enabled.
         * @~chinese 设置混合函数，注意混合函数只有在blend为true时才起作用。
         * @param blendFunc @~english Specifies how the blending factors are computed.
         * @~chinese 混合函数的源和目标的定义。
         */
        void setBlendFunc(const BlendFunc& blendFunc);

        /**
         * @~english Toggles blending.
         * @~chinese 设置是否启用混合
         * @param enabled @~english true to enable, false to disable. @~chinese 启用混合为true否则为false。
         */
        void setBlend(bool enabled);

        /**
         * @~english Explicitly sets the source used in the blend function for this render state.
         *
         * Note that the blend function is only applied when blending is enabled.
         * @~chinese 设置源的混合方式。注意只有当blend为true时该函数才有作用。
         * @param blend @~english Specifies how the source blending factors are computed. @~chinese 定义源的混合方式。
         */
        void setBlendSrc(Blend blend);

        /**
         * @~english Explicitly sets the destination used in the blend function for this render state.
         *
         * Note that the blend function is only applied when blending is enabled.
         * @~chinese 设置目标的混合方式。注意只有当blend为true时才有作用。
         * @param blend @~english Specifies how the destination blending factors are computed. @~chinese 定义目标的混合方式。
         */
        void setBlendDst(Blend blend);

        /**
         * @~english Explicitly enables or disables backface culling.
         * @~chinese 设置是否允许裁剪
         * @param enabled @~english true to enable, false to disable. @~chinese 允许裁剪为true，否则为false。
         */
        void setCullFace(bool enabled);

        /**
         * @~english Sets the side of the facets to cull.
         *
         * When not explicitly set, the default is to cull back-facing facets.
         * @~chinese 设置裁剪的面。缺省值为裁剪背面。
         * @param side @~english The side to cull. @~chinese 待剪裁的面。
         */
        void setCullFaceSide(CullFaceSide side);

        /**
         * @~english Sets the winding for front facing polygons.
         *
         * By default, counter-clockwise wound polygons are considered front facing.
         * @~chinese 设置定义为前面的朝向，默认值为逆时针方向。
         * @param winding @~english The winding for front facing polygons. @~chinese 定义为前面的朝向。
         */
        void setFrontFace(FrontFace winding);

        /**
         * @~english Toggles depth testing.
         *
         * By default, depth testing is disabled.
         * @~chinese 设置深度测试是否开启。
         * @param enabled @~english true to enable, false to disable. @~chinese 为true开启深度测试，false关闭深度测试。
         */
        void setDepthTest(bool enabled);

        /**
         * @~english Toggles depth writing.
         * @~chinese 设置是否开启深度写。
         * @param enabled @~english true to enable, false to disable. @~chinese true开启深度写，false关闭深度写。
         */
        void setDepthWrite(bool enabled);

        /**
         * @~english Sets the depth function to use when depth testing is enabled.
         *
         * When not explicitly set and when depth testing is enabled, the default
         * depth function is DEPTH_LESS.
         * @~chinese 设置深度比较函数，当且仅当深度测试开启时有效。缺省深度比较函数为DEPTH_LESS。
         * @param func @~english The depth function. @~chinese 深度比较函数。
         */
        void setDepthFunction(DepthFunction func);

        // /**
        //  * @~english Toggles stencil testing.
        //  *
        //  * By default, stencil testing is disabled.
        //  * @~chinese 设置模板测试是否开启。默认模板测试关闭。
        //  * @param enabled @~english true to enable, false to disable. @~chinese true开启，false关闭。
        //  */
        // void setStencilTest(bool enabled);

        // /**
        //  * @~english Sets the stencil writing mask.
        //  *
        //  * By default, the stencil writing mask is all 1's.
        //  * @~chinese 设置模板写的掩码，缺省模板掩码写的掩码为都是1.
        //  * @param mask @~english Bit mask controlling writing to individual stencil planes. @~chinese 掩码用来控制写到模板面上。
        //  */
        // void setStencilWrite(unsigned int mask);

        // /**
        //  * @~english Sets the stencil function.
        //  *
        //  * By default, the function is set to STENCIL_ALWAYS, the reference value is 0, and the mask is all 1's.
        //  * @~chinese 设置模板比较函数。默认的模板函数为STENCIL_ALWAYS，参考值为0，掩码为全是1。
        //  * @param func @~english The stencil function. @~chinese 模板函数。
        //  * @param ref @~english The stencil reference value. @~chinese 模板参考值。
        //  * @param mask @~english The stencil mask. @~chinese 模板掩码。
        //  */
        // void setStencilFunction(StencilFunction func, int ref, unsigned int mask);

        // /**
        //  * @~english Sets the stencil operation.
        //  *
        //  * By default, stencil fail, stencil pass/depth fail, and stencil and depth pass are set to STENCIL_OP_KEEP.
        //  * @~chinese 设置模板操作。默认情况下模板测试失败、模板测试失败深度测试通过、模板测试深度测试都通过，模板操作都设置为STENCIL_OP_KEEP。
        //  * @param sfail @~english The stencil operation if the stencil test fails.@~chinese 模板测试失败时候的模板操作。
        //  * @param dpfail @~english The stencil operation if the stencil test passes, but the depth test fails. @~chinese 模板测试通过，深度测试失败时候的模板操作。
        //  * @param dppass @~english The stencil operation if both the stencil test and depth test pass. @~chinese 模板测试和深度测试都失败时候的模板操作。
        //  */
        // void setStencilOperation(StencilOperation sfail, StencilOperation dpfail, StencilOperation dppass);

        /**
         * @~english Sets a render state from the given name and value strings.
         *
         * This method attempts to interpret the passed in strings as render state
         * name and value. This is normally used when loading render states from
         * material files.
         * @~chinese 通过给定名字和值字符串设置渲染状态。该函数在从材质文件中加载渲染状态时使用。
         * @param name @~english Name of the render state to set. @~chinese 待设置渲染状态的名字。
         * @param value @~english Value of the specified render state. @~chinese 待设置渲染状态的值。
         */
        void setState(const std::string& name, const std::string& value);

        /**
         * @~english Get hash code of this render state.
         * @~chinese 获取该渲染状态的哈希码。
         * @return @~english Hash code of this render state. @~chinese 改渲染状态的哈希码。
         */
        uint32_t getHash() const;
        /**
         * @~english Is this render state dirty?
         * @~chinese 渲染状态是否被修改过？
         * @return @~english true dirty, false not dirty. @~chinese true表示修改过，false没有修改过。
         */
        bool isDirty() const;

        /** StateBlock bits to be used with invalidate */
        enum
        {
            RS_BLEND = (1 << 0),
            RS_BLEND_FUNC = (1 << 1),
            RS_CULL_FACE = (1 << 2),
            RS_DEPTH_TEST = (1 << 3),
            RS_DEPTH_WRITE = (1 << 4),
            RS_DEPTH_FUNC = (1 << 5),
            RS_CULL_FACE_SIDE = (1 << 6),
//            RS_STENCIL_TEST = (1 << 7),
//            RS_STENCIL_WRITE = (1 << 8),
//            RS_STENCIL_FUNC = (1 << 9),
//            RS_STENCIL_OP = (1 << 10),
            RS_FRONT_FACE = (1 << 11),
            
            RS_ALL_ONES = 0xFFFFFFFF,
        };

        /** 
        @~english
         * Invalidates the default StateBlock.
         *
         * Only call it if you are calling GL calls directly. Invoke this function
         * at the end of your custom draw call.
         * This function restores the default render state its defaults values.
         * Since this function might call GL calls, it must be called in a GL context is present.
         * @~chinese 让默认的StateBlock状态失效。通常情况下，如果你直接调用了openGL的函数来修改渲染状态，那么stateBlock中保存
         * 的状态会与openGL的状态不一致。这个函数用于把openGL重置为默认状态,必须在openGL context存在时调用。
         * @param stateBits @~english Bitwise-OR of the states that needs to be invalidated
         * @~chinese 需要重置的状态位，可以通过按位或操作来指定多个状态。
         */
        static void invalidate(long stateBits);

        /**
         * @~english
         * Restores the global Render State to the default state
         *
         * The difference between `invalidate()` and `restore()`, is that `restore()` will
         * restore the global Render State based on its current state. Only the
         * states that were changed will be restored.
         *
         * Rule of thumb:
         
         - call `restore()` if you want to restore to the default state after using `StateBlock`.
         - call `invalidate()` if you want to restore to the default state after calling manual GL calls.
         * @~chinese 将全局的渲染状态设置为默认状态， 这个函数与invalidate()的区别在于，restore()函数会基于当前的StateBlock记录的状态
         * 来恢复。所以
         * -当你使用stateBlock时，可以通过restore()来将stateblock重置为默认状态。
         * -当你直接调用openGL函数设置了状态时，需要调用invalidate()。
         * @param stateOverrideBits @~english Bitwise-OR of the states that needs to be override. @~chinese 待覆盖位的相与。
         */
        static void restore(long stateOverrideBits);

        /***
         * @~english Default render state.
         * @~chinese 默认渲染状态。
         */
        static StateBlock* _defaultState;

    protected:

        void bindNoRestore();
        static void enableDepthWrite();

        void cloneInto(StateBlock* renderState) const;

        bool _cullFaceEnabled;
        bool _depthTestEnabled;
        bool _depthWriteEnabled;
        DepthFunction _depthFunction;
        bool _blendEnabled;
        Blend _blendSrc;
        Blend _blendDst;
        CullFaceSide _cullFaceSide;
        FrontFace _frontFace;
        bool _stencilTestEnabled;
        unsigned int _stencilWrite;
        StencilFunction _stencilFunction;
        int _stencilFunctionRef;
        unsigned int _stencilFunctionMask;
        StencilOperation _stencilOpSfail;
        StencilOperation _stencilOpDpfail;
        StencilOperation _stencilOpDppass;

        long _bits;

        mutable uint32_t _hash;
        mutable bool _hashDirty;
    };

    void setStateBlock(StateBlock* state);
    StateBlock* getStateBlock() const;

protected:
    RenderState();
    ~RenderState();
    bool init(RenderState* parent);
    void cloneInto(RenderState* state) const;

    mutable uint32_t _hash;
    mutable bool _hashDirty;

    /**
     * The StateBlock of fixed-function render states that can be applied to the RenderState.
     */
    mutable StateBlock* _state;

    /**
     * The RenderState's parent. Weak Reference
     */
    RenderState* _parent;

    // name, for filtering
    std::string _name;

    Texture2D* _texture;
};

/**
 end of support group
 @}
 */

NS_CC_END

#endif /* defined(__cocos2d_libs__CCRenderState__) */
