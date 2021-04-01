/****************************************************************************
 Copyright (c) 2015-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
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
#pragma once

#include <string>
#include <functional>
#include <cstdint>

#include "platform/CCPlatformMacros.h"
#include "base/CCRef.h"
#include "base/ccTypes.h"
#include "base/CCVector.h"

#include "renderer/CCPipelineDescriptor.h"
#include "renderer/backend/Types.h"
#include "renderer/CCMeshCommand.h"

NS_CC_BEGIN

class Texture2D;
class Pass;
class MeshCommand;

using CullFaceSide = backend::CullMode;
using FrontFace = backend::Winding;
using DepthFunction = backend::CompareFunction;

/**
 * Defines the rendering state of the graphics device.
 */
class CC_DLL RenderState : public Ref
{
    friend class Material;
    friend class Technique;
    friend class Pass;

public:

    std::string getName() const;

    /**
     * Binds the render state for this RenderState and any of its parents, top-down,
     * for the given pass.
     */
    void bindPass(Pass* pass, MeshCommand *);


    /**
     * Defines a block of fixed-function render states that can be applied to a
     * RenderState object.
     */
    class CC_DLL StateBlock // : public Ref
    {
        friend class RenderState;
        friend class Pass;
        friend class RenderQueue;
        friend class Renderer;
        
    public:
        /**
         * Creates a new StateBlock with default render state settings.
         */
        //static StateBlock* create();

        /** The recommended way to create StateBlocks is by calling `create`.
         * Don't use `new` or `delete` on them.
         * 
         */
        StateBlock() = default;
        ~StateBlock() = default;
        StateBlock(const StateBlock &) = default;
        /**
         * Binds the state in this StateBlock to the renderer.
         *
         * This method handles both setting and restoring of render states to ensure that
         * only the state explicitly defined by this StateBlock is applied to the renderer.
         */
        void bind(PipelineDescriptor *programState);

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
        void setBlendSrc(backend::BlendFactor blend);

        /**
         * Explicitly sets the source used in the blend function for this render state.
         *
         * Note that the blend function is only applied when blending is enabled.
         *
         * @param blend Specifies how the destination blending factors are computed.
         */
        void setBlendDst(backend::BlendFactor blend);

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

    protected:
        
        /**
        * update internal states of ProgramState
        */
        void apply(PipelineDescriptor *pipelineDescriptor);

        static void restoreUnmodifiedStates(long flags, PipelineDescriptor *pipelineDescriptor);


        bool _cullFaceEnabled = false;
        bool _depthTestEnabled = true;
        bool _depthWriteEnabled = false;
        DepthFunction _depthFunction = DepthFunction::LESS;
        bool _blendEnabled = true;
        backend::BlendFactor _blendSrc = backend::BlendFactor::ONE;
        backend::BlendFactor _blendDst = backend::BlendFactor::ZERO;
        CullFaceSide _cullFaceSide = CullFaceSide::BACK;
        FrontFace _frontFace = FrontFace::COUNTER_CLOCK_WISE;
        long _modifiedBits = 0L;

        mutable uint32_t _hash;
        mutable bool _hashDirty;
    };

    StateBlock& getStateBlock() const;

protected:
    RenderState() = default;
    
    mutable uint32_t _hash = 0;
    mutable bool _hashDirty = true;

    /**
     * The StateBlock of fixed-function render states that can be applied to the RenderState.
     */
    mutable StateBlock _state;

    // name, for filtering
    std::string _name;
};

NS_CC_END
