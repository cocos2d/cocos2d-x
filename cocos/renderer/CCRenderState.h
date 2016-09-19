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
class CC_DLL RenderState : public Ref
{
    friend class Material;
    friend class Technique;
    friend class Pass;

public:
    /**
     * Static initializer that is called during game startup.
     */
    static void initialize();

    /**
     * Static finalizer that is called during game shutdown.
     */
    static void finalize();

    std::string getName() const;


    /** Texture that will use in the CC_Texture0 uniform.
     Added to be backwards compatible. Use Samplers from .material instead.
     */
    void setTexture(Texture2D* texture);

    /** Returns the texture that is going to be used for CC_Texture0.
     Added to be backwards compatible.
     */
    Texture2D* getTexture() const;

    /**
     * Binds the render state for this RenderState and any of its parents, top-down,
     * for the given pass.
     */
    void bind(Pass* pass);

    /**
     * Returns the topmost RenderState in the hierarchy below the given RenderState.
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
     * Defines the supported depth compare functions.
     *
     * Depth compare functions specify the comparison that takes place between the
     * incoming pixel's depth value and the depth value already in the depth buffer.
     * If the compare function passes, the new pixel will be drawn.
     *
     * The initial depth compare function is DEPTH_LESS.
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
     * Defines culling criteria for front-facing, back-facing and both-side
     * facets.
     */
    enum CullFaceSide
    {
        CULL_FACE_SIDE_BACK = GL_BACK,
        CULL_FACE_SIDE_FRONT = GL_FRONT,
        CULL_FACE_SIDE_FRONT_AND_BACK = GL_FRONT_AND_BACK
    };

    /**
     * Defines the winding of vertices in faces that are considered front facing.
     *
     * The initial front face mode is set to FRONT_FACE_CCW.
     */
    enum FrontFace
    {
        FRONT_FACE_CW = GL_CW,
        FRONT_FACE_CCW = GL_CCW
    };

    /**
     * Defines the supported stencil compare functions.
     *
     * Stencil compare functions determine if a new pixel will be drawn.
     *
     * The initial stencil compare function is STENCIL_ALWAYS.
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
     * Defines the supported stencil operations to perform.
     *
     * Stencil operations determine what should happen to the pixel if the
     * stencil test fails, passes, or passes but fails the depth test.
     *
     * The initial stencil operation is STENCIL_OP_KEEP.
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
     * Defines a block of fixed-function render states that can be applied to a
     * RenderState object.
     */
    class CC_DLL StateBlock : public Ref
    {
        friend class RenderState;
        friend class Pass;
        friend class RenderQueue;
        friend class Renderer;
        
    public:
        /**
         * Creates a new StateBlock with default render state settings.
         */
        static StateBlock* create();

        /** The recommended way to create StateBlocks is by calling `create`.
         * Don't use `new` or `delete` on them.
         * 
         */
        StateBlock();
        ~StateBlock();

        /**
         * Binds the state in this StateBlock to the renderer.
         *
         * This method handles both setting and restoring of render states to ensure that
         * only the state explicitly defined by this StateBlock is applied to the renderer.
         */
        void bind();

        /**
         * Explicitly sets the source and destination used in the blend function for this render state.
         *
         * Note that the blend function is only applied when blending is enabled.
         *
         * @param blendFunc Specifies how the blending factors are computed.
         */
        void setBlendFunc(const BlendFunc& blendFunc);

        /**
         * Toggles blending.
         *
         * @param enabled true to enable, false to disable.
         */
        void setBlend(bool enabled);

        /**
         * Explicitly sets the source used in the blend function for this render state.
         *
         * Note that the blend function is only applied when blending is enabled.
         *
         * @param blend Specifies how the source blending factors are computed.
         */
        void setBlendSrc(Blend blend);

        /**
         * Explicitly sets the source used in the blend function for this render state.
         *
         * Note that the blend function is only applied when blending is enabled.
         *
         * @param blend Specifies how the destination blending factors are computed.
         */
        void setBlendDst(Blend blend);

        /**
         * Explicitly enables or disables backface culling.
         *
         * @param enabled true to enable, false to disable.
         */
        void setCullFace(bool enabled);

        /**
         * Sets the side of the facets to cull.
         *
         * When not explicitly set, the default is to cull back-facing facets.
         *
         * @param side The side to cull.
         */
        void setCullFaceSide(CullFaceSide side);

        /**
         * Sets the winding for front facing polygons.
         *
         * By default, counter-clockwise wound polygons are considered front facing.
         *
         * @param winding The winding for front facing polygons.
         */
        void setFrontFace(FrontFace winding);

        /**
         * Toggles depth testing.
         *
         * By default, depth testing is disabled.
         *
         * @param enabled true to enable, false to disable.
         */
        void setDepthTest(bool enabled);

        /**
         * Toggles depth writing.
         *
         * @param enabled true to enable, false to disable.
         */
        void setDepthWrite(bool enabled);

        /**
         * Sets the depth function to use when depth testing is enabled.
         *
         * When not explicitly set and when depth testing is enabled, the default
         * depth function is DEPTH_LESS.
         *
         * @param func The depth function.
         */
        void setDepthFunction(DepthFunction func);

//        /**
//         * Toggles stencil testing.
//         *
//         * By default, stencil testing is disabled.
//         *
//         * @param enabled true to enable, false to disable.
//         */
//        void setStencilTest(bool enabled);
//
//        /**
//         * Sets the stencil writing mask.
//         *
//         * By default, the stencil writing mask is all 1's.
//         *
//         * @param mask Bit mask controlling writing to individual stencil planes.
//         */
//        void setStencilWrite(unsigned int mask);
//
//        /**
//         * Sets the stencil function.
//         *
//         * By default, the function is set to STENCIL_ALWAYS, the reference value is 0, and the mask is all 1's.
//         *
//         * @param func The stencil function.
//         * @param ref The stencil reference value.
//         * @param mask The stencil mask.
//         */
//        void setStencilFunction(StencilFunction func, int ref, unsigned int mask);
//
//        /**
//         * Sets the stencil operation.
//         *
//         * By default, stencil fail, stencil pass/depth fail, and stencil and depth pass are set to STENCIL_OP_KEEP.
//         *
//         * @param sfail The stencil operation if the stencil test fails.
//         * @param dpfail The stencil operation if the stencil test passes, but the depth test fails.
//         * @param dppass The stencil operation if both the stencil test and depth test pass.
//         */
//        void setStencilOperation(StencilOperation sfail, StencilOperation dpfail, StencilOperation dppass);

        /**
         * Sets a render state from the given name and value strings.
         *
         * This method attempts to interpret the passed in strings as render state
         * name and value. This is normally used when loading render states from
         * material files.
         *
         * @param name Name of the render state to set.
         * @param value Value of the specified render state.
         */
        void setState(const std::string& name, const std::string& value);

        uint32_t getHash() const;
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
         * Invalidates the default StateBlock.
         *
         * Only call it if you are calling GL calls directly. Invoke this function
         * at the end of your custom draw call.
         * This function restores the default render state its defaults values.
         * Since this function might call GL calls, it must be called in a GL context is present.
         *
         * @param stateBits Bitwise-OR of the states that needs to be invalidated
         */
        static void invalidate(long stateBits);

        /**
         * Restores the global Render State to the default state
         *
         * The difference between `invalidate()` and `restore()`, is that `restore()` will
         * restore the global Render State based on its current state. Only the
         * states that were changed will be restored.
         *
         * Rule of thumb:
         
         - call `restore()` if you want to restore to the default state after using `StateBlock`.
         - call `invalidate()` if you want to restore to the default state after calling manual GL calls.

         */
        static void restore(long stateOverrideBits);

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

NS_CC_END

#endif /* defined(__cocos2d_libs__CCRenderState__) */
