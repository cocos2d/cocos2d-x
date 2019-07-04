/****************************************************************************
 Copyright (c) 2018-2019 Xiamen Yaji Software Co., Ltd.

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
 
#include "RenderPipelineMTL.h"
#include "DeviceMTL.h"
#include "ShaderModuleMTL.h"
#include "DepthStencilStateMTL.h"
#include "Utils.h"
#include "ProgramMTL.h"

CC_BACKEND_BEGIN

namespace
{
    MTLVertexStepFunction toMTLVertexStepFunction(VertexStepMode vertexStepMode)
    {
        if (VertexStepMode::VERTEX == vertexStepMode)
            return MTLVertexStepFunctionPerVertex;
        else
            return MTLVertexStepFunctionPerInstance;
    }
    
    MTLVertexFormat toMTLVertexFormat(VertexFormat vertexFormat, bool needNormalize)
    {
        MTLVertexFormat ret = MTLVertexFormatFloat4;
        switch (vertexFormat)
        {
            case VertexFormat::FLOAT4:
                ret = MTLVertexFormatFloat4;
                break;
            case VertexFormat::FLOAT3:
                ret = MTLVertexFormatFloat3;
                break;
            case VertexFormat::FLOAT2:
                ret = MTLVertexFormatFloat2;
                break;
            case VertexFormat::FLOAT:
                ret = MTLVertexFormatFloat;
                break;
            case VertexFormat::INT4:
                ret = MTLVertexFormatInt4;
                break;
            case VertexFormat::INT3:
                ret = MTLVertexFormatInt3;
                break;
            case VertexFormat::INT2:
                ret = MTLVertexFormatInt2;
                break;
            case VertexFormat::INT:
                ret = MTLVertexFormatInt;
                break;
            case VertexFormat::USHORT4:
                ret = MTLVertexFormatUShort4;
                break;
            case VertexFormat::USHORT2:
                ret = MTLVertexFormatUShort2;
                break;
            case VertexFormat::UBYTE4:
                if (needNormalize)
                    ret = MTLVertexFormatUChar4Normalized;
                else
                    ret = MTLVertexFormatUChar4;
                break;
            default:
                assert(false);
                break;
        }
        return ret;
    }
}

RenderPipelineMTL::RenderPipelineMTL(id<MTLDevice> mtlDevice, const RenderPipelineDescriptor& descriptor)
: _mtlDevice(mtlDevice)
{
    _mtlRenderPipelineDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    
    setShaderModules(descriptor);
    setVertexLayout(_mtlRenderPipelineDescriptor, descriptor);
    
    auto blendState = static_cast<BlendStateMTL*>(descriptor.blendState);
    if (blendState)
        _blendDescriptorMTL = blendState->getBlendDescriptorMTL();
    
    setBlendStateAndFormat(descriptor);

    NSError *error = nil;
    _mtlRenderPipelineState = [_mtlDevice newRenderPipelineStateWithDescriptor:_mtlRenderPipelineDescriptor error:&error];
    if (error)
        NSLog(@"Can not create renderpipeline state: %@", error);

    [_mtlRenderPipelineDescriptor release];
}

RenderPipelineMTL::~RenderPipelineMTL()
{
    [_mtlRenderPipelineState release];
}

void RenderPipelineMTL::setVertexLayout(MTLRenderPipelineDescriptor* mtlDescriptor, const RenderPipelineDescriptor& descriptor)
{
    const auto& vertexLayouts = *descriptor.vertexLayouts;
    int vertexIndex = 0;
    for (const auto& vertexLayout : vertexLayouts)
    {
        if (!vertexLayout.isValid())
            continue;
        
        mtlDescriptor.vertexDescriptor.layouts[vertexIndex].stride = vertexLayout.getStride();
        mtlDescriptor.vertexDescriptor.layouts[vertexIndex].stepFunction = toMTLVertexStepFunction(vertexLayout.getVertexStepMode());
        
        const auto& attributes = vertexLayout.getAttributes();
        for (const auto& it : attributes)
        {
            auto attribute = it.second;
            mtlDescriptor.vertexDescriptor.attributes[attribute.index].format = toMTLVertexFormat(attribute.format, attribute.needToBeNormallized);
            mtlDescriptor.vertexDescriptor.attributes[attribute.index].offset = attribute.offset;
            // Buffer index will always be 0;
            mtlDescriptor.vertexDescriptor.attributes[attribute.index].bufferIndex = 0;
        }
        
        ++vertexIndex;
    }
}

void RenderPipelineMTL::setBlendState(MTLRenderPipelineColorAttachmentDescriptor* colorAttachmentDescriptor)
{
    colorAttachmentDescriptor.blendingEnabled = _blendDescriptorMTL.blendEnabled;
    colorAttachmentDescriptor.writeMask = _blendDescriptorMTL.writeMask;
    
    colorAttachmentDescriptor.rgbBlendOperation = _blendDescriptorMTL.rgbBlendOperation;
    colorAttachmentDescriptor.alphaBlendOperation = _blendDescriptorMTL.alphaBlendOperation;
    
    colorAttachmentDescriptor.sourceRGBBlendFactor = _blendDescriptorMTL.sourceRGBBlendFactor;
    colorAttachmentDescriptor.destinationRGBBlendFactor = _blendDescriptorMTL.destinationRGBBlendFactor;
    colorAttachmentDescriptor.sourceAlphaBlendFactor = _blendDescriptorMTL.sourceAlphaBlendFactor;
    colorAttachmentDescriptor.destinationAlphaBlendFactor = _blendDescriptorMTL.destinationAlphaBlendFactor;
}

void RenderPipelineMTL::setShaderModules(const RenderPipelineDescriptor& descriptor)
{
    auto vertexShaderModule = static_cast<ProgramMTL*>(descriptor.programState->getProgram())->getVertexShader();
    _mtlRenderPipelineDescriptor.vertexFunction = vertexShaderModule->getMTLFunction();
    
    auto fragShaderModule = static_cast<ProgramMTL*>(descriptor.programState->getProgram())->getFragmentShader();
    _mtlRenderPipelineDescriptor.fragmentFunction = fragShaderModule->getMTLFunction();
}

void RenderPipelineMTL::setBlendStateAndFormat(const RenderPipelineDescriptor& descriptor)
{
    for (int i = 0; i < MAX_COLOR_ATTCHMENT; ++i)
    {
        if (PixelFormat::NONE == descriptor.colorAttachmentsFormat[i])
            continue;
        
        _mtlRenderPipelineDescriptor.colorAttachments[i].pixelFormat = Utils::toMTLPixelFormat(descriptor.colorAttachmentsFormat[i]);
        setBlendState(_mtlRenderPipelineDescriptor.colorAttachments[i]);
    }
    _mtlRenderPipelineDescriptor.depthAttachmentPixelFormat = Utils::toMTLPixelFormat(descriptor.depthAttachmentFormat);
    _mtlRenderPipelineDescriptor.stencilAttachmentPixelFormat = Utils::toMTLPixelFormat(descriptor.stencilAttachmentFormat);
}

CC_BACKEND_END
