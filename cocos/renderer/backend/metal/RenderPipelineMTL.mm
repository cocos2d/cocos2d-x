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
#include "xxhash.h"

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
    
    MTLColorWriteMask toMTLColorWriteMask(ColorWriteMask mask)
    {
        switch (mask) {
            case ColorWriteMask::NONE:
                return MTLColorWriteMaskNone;
            case ColorWriteMask::RED:
                return MTLColorWriteMaskRed;
            case ColorWriteMask::GREEN:
                return MTLColorWriteMaskGreen;
            case ColorWriteMask::BLUE:
                return MTLColorWriteMaskBlue;
            case ColorWriteMask::ALPHA:
                return MTLColorWriteMaskAlpha;
            case ColorWriteMask::ALL:
                return MTLColorWriteMaskAll;
        }
    }
    
    MTLBlendFactor toMTLBlendFactor(BlendFactor factor)
    {
        switch (factor) {
            case BlendFactor::ZERO:
                return MTLBlendFactorZero;
            case BlendFactor::ONE:
                return MTLBlendFactorOne;
            case BlendFactor::SRC_COLOR:
                return MTLBlendFactorSourceColor;
            case BlendFactor::ONE_MINUS_SRC_COLOR:
                return MTLBlendFactorOneMinusSourceColor;
            case BlendFactor::SRC_ALPHA:
                return MTLBlendFactorSourceAlpha;
            case BlendFactor::ONE_MINUS_SRC_ALPHA:
                return MTLBlendFactorOneMinusSourceAlpha;
            case BlendFactor::DST_COLOR:
                return MTLBlendFactorDestinationColor;
            case BlendFactor::ONE_MINUS_DST_COLOR:
                return MTLBlendFactorOneMinusDestinationColor;
            case BlendFactor::DST_ALPHA:
                return MTLBlendFactorDestinationAlpha;
            case BlendFactor::ONE_MINUS_DST_ALPHA:
                return MTLBlendFactorOneMinusDestinationAlpha;
            case BlendFactor::SRC_ALPHA_SATURATE:
                return MTLBlendFactorSourceAlphaSaturated;
            case BlendFactor::BLEND_CLOLOR:
                return MTLBlendFactorBlendColor;
            default:
                return MTLBlendFactorZero;
        }
    }
    
    MTLBlendOperation toMTLBlendOperation(BlendOperation operation)
    {
        switch (operation) {
            case BlendOperation::ADD:
                return MTLBlendOperationAdd;
            case BlendOperation::SUBTRACT:
                return MTLBlendOperationSubtract;
            case BlendOperation::RESERVE_SUBTRACT:
                return MTLBlendOperationReverseSubtract;
            default:
                return MTLBlendOperationAdd;
        }
    }
}

RenderPipelineMTL::RenderPipelineMTL(id<MTLDevice> mtlDevice)
: _mtlDevice(mtlDevice)
{
    _mtlRenderPipelineStateCache = [NSMutableDictionary dictionaryWithCapacity:100];
    [_mtlRenderPipelineStateCache retain];
}

void RenderPipelineMTL::update(const PipelineDescriptor & pipelineDescirptor,
                               const RenderPassDescriptor& renderPassDescriptor)
{
    struct
    {
        size_t vertexShaderHash;
        size_t fragmentShaderHash;
        unsigned int vertexLayoutInfo[32];
        backend::PixelFormat colorAttachment;
        backend::PixelFormat depthAttachment;
        backend::PixelFormat stencilAttachment;
        bool blendEnabled;
        unsigned int writeMask;
        unsigned int rgbBlendOperation;
        unsigned int alphaBlendOperation;
        unsigned int sourceRGBBlendFactor;
        unsigned int destinationRGBBlendFactor;
        unsigned int sourceAlphaBlendFactor;
        unsigned int destinationAlphaBlendFactor;
    }hashMe;
    
    memset(&hashMe, 0, sizeof(hashMe));
    const auto& blendDescriptor = pipelineDescirptor.blendDescriptor;
    getAttachmentFormat(renderPassDescriptor, _colorAttachmentsFormat[0], _depthAttachmentFormat, _stencilAttachmentFormat);
    auto program = static_cast<ProgramMTL*>(pipelineDescirptor.programState->getProgram());
    hashMe.vertexShaderHash = program->getVertexShader()->getHashValue();
    hashMe.fragmentShaderHash = program->getFragmentShader()->getHashValue();
    hashMe.colorAttachment = _colorAttachmentsFormat[0];
    hashMe.depthAttachment = _depthAttachmentFormat;
    hashMe.stencilAttachment =_stencilAttachmentFormat;
    hashMe.blendEnabled = blendDescriptor.blendEnabled;
    hashMe.writeMask = (unsigned int)blendDescriptor.writeMask;
    hashMe.rgbBlendOperation = (unsigned int)blendDescriptor.rgbBlendOperation;
    hashMe.alphaBlendOperation = (unsigned int)blendDescriptor.alphaBlendOperation;
    hashMe.sourceRGBBlendFactor = (unsigned int)blendDescriptor.sourceRGBBlendFactor;
    hashMe.destinationRGBBlendFactor = (unsigned int)blendDescriptor.destinationRGBBlendFactor;
    hashMe.sourceAlphaBlendFactor = (unsigned int)blendDescriptor.sourceAlphaBlendFactor;
    hashMe.destinationAlphaBlendFactor = (unsigned int)blendDescriptor.destinationAlphaBlendFactor;
    int index = 0;
    auto vertexLayout = pipelineDescirptor.programState->getVertexLayout();
    const auto& attributes = vertexLayout->getAttributes();
    for (const auto& it : attributes)
    {
        auto &attribute = it.second;
        /*
         stepFunction:1     stride:15       offest:10       format:5        needNormalized:1
         bit31           bit30 ~ bit16   bit15 ~ bit6    bit5 ~ bit1     bit0
         */
        hashMe.vertexLayoutInfo[index++] =
        ((unsigned int)vertexLayout->getVertexStepMode() & 0x1) << 31 |
        ((unsigned int)(vertexLayout->getStride() & 0x7FFF)) << 16 |
        ((unsigned int)attribute.offset & 0x3FF) << 6 |
        ((unsigned int)attribute.format & 0x1F) << 1 |
        ((unsigned int)attribute.needToBeNormallized & 0x1);
    }
    
    unsigned int hash = XXH32((const void*)&hashMe, sizeof(hashMe), 0);
    NSNumber* key = @(hash);
    id obj = [_mtlRenderPipelineStateCache objectForKey:key];
    if (obj != nil)
    {
        _mtlRenderPipelineState = obj;
        return;
    }
    
    _mtlRenderPipelineDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    
    setShaderModules(pipelineDescirptor);
    setVertexLayout(_mtlRenderPipelineDescriptor, pipelineDescirptor);
    
    setBlendStateAndFormat(pipelineDescirptor.blendDescriptor, renderPassDescriptor);
    
    NSError *error = nil;
    _mtlRenderPipelineState = [_mtlDevice newRenderPipelineStateWithDescriptor:_mtlRenderPipelineDescriptor error:&error];
    if (error)
        NSLog(@"Can not create renderpipeline state: %@", error);
    
    [_mtlRenderPipelineDescriptor release];
    [_mtlRenderPipelineStateCache setObject:_mtlRenderPipelineState forKey:key];
}

RenderPipelineMTL::~RenderPipelineMTL()
{
    NSArray* values = [_mtlRenderPipelineStateCache allValues];
    for(id value in values)
    {
        [value release];
    }
    [_mtlRenderPipelineStateCache release];
}

void RenderPipelineMTL::setVertexLayout(MTLRenderPipelineDescriptor* mtlDescriptor, const PipelineDescriptor& descriptor)
{
    int vertexIndex = 0;
    auto vertexLayout = descriptor.programState->getVertexLayout();
    if (!vertexLayout->isValid())
        return;
    
    mtlDescriptor.vertexDescriptor.layouts[vertexIndex].stride = vertexLayout->getStride();
    mtlDescriptor.vertexDescriptor.layouts[vertexIndex].stepFunction = toMTLVertexStepFunction(vertexLayout->getVertexStepMode());
    
    const auto& attributes = vertexLayout->getAttributes();
    for (const auto& it : attributes)
    {
        auto attribute = it.second;
        mtlDescriptor.vertexDescriptor.attributes[attribute.index].format = toMTLVertexFormat(attribute.format, attribute.needToBeNormallized);
        mtlDescriptor.vertexDescriptor.attributes[attribute.index].offset = attribute.offset;
        // Buffer index will always be 0;
        mtlDescriptor.vertexDescriptor.attributes[attribute.index].bufferIndex = 0;
    }
     
}

void RenderPipelineMTL::setBlendState(MTLRenderPipelineColorAttachmentDescriptor* colorAttachmentDescriptor,
                                      const BlendDescriptor& blendDescriptor)
{
    colorAttachmentDescriptor.blendingEnabled = blendDescriptor.blendEnabled;
    colorAttachmentDescriptor.writeMask = toMTLColorWriteMask(blendDescriptor.writeMask);
    
    colorAttachmentDescriptor.rgbBlendOperation = toMTLBlendOperation(blendDescriptor.rgbBlendOperation);
    colorAttachmentDescriptor.alphaBlendOperation = toMTLBlendOperation(blendDescriptor.alphaBlendOperation);
    
    colorAttachmentDescriptor.sourceRGBBlendFactor = toMTLBlendFactor(blendDescriptor.sourceRGBBlendFactor);
    colorAttachmentDescriptor.destinationRGBBlendFactor = toMTLBlendFactor(blendDescriptor.destinationRGBBlendFactor);
    colorAttachmentDescriptor.sourceAlphaBlendFactor = toMTLBlendFactor(blendDescriptor.sourceAlphaBlendFactor);
    colorAttachmentDescriptor.destinationAlphaBlendFactor = toMTLBlendFactor(blendDescriptor.destinationAlphaBlendFactor);
}

void RenderPipelineMTL::setShaderModules(const PipelineDescriptor& descriptor)
{
    auto vertexShaderModule = static_cast<ProgramMTL*>(descriptor.programState->getProgram())->getVertexShader();
    _mtlRenderPipelineDescriptor.vertexFunction = vertexShaderModule->getMTLFunction();
    
    auto fragShaderModule = static_cast<ProgramMTL*>(descriptor.programState->getProgram())->getFragmentShader();
    _mtlRenderPipelineDescriptor.fragmentFunction = fragShaderModule->getMTLFunction();
}

void RenderPipelineMTL::getAttachmentFormat(const RenderPassDescriptor& descriptor,
                                            PixelFormat& colorFormat,
                                            PixelFormat& depthFormat,
                                            PixelFormat& stencilFormat)
{
    if (descriptor.needColorAttachment)
    {
        // FIXME: now just handle color attachment 0.
        if (descriptor.colorAttachmentsTexture[0])
            colorFormat = descriptor.colorAttachmentsTexture[0]->getTextureFormat();
        else
            colorFormat = PixelFormat::DEFAULT;
    }
    else
    {
        colorFormat = PixelFormat::DEFAULT;
    }
    
    if (descriptor.needDepthStencilAttachment())
    {
        if(descriptor.depthAttachmentTexture)
        {
            depthFormat = descriptor.depthAttachmentTexture->getTextureFormat();
        }
        else
        {
            depthFormat = PixelFormat::D24S8;
        }
        
        if (descriptor.stencilAttachmentTexture)
        {
            stencilFormat = descriptor.stencilAttachmentTexture->getTextureFormat();
        }
        else
        {
            stencilFormat = PixelFormat::D24S8;
        }
    }
    else
    {
        depthFormat = stencilFormat = PixelFormat::NONE;
    }
}

void RenderPipelineMTL::setBlendStateAndFormat(const BlendDescriptor& blendDescriptor,
                                               const RenderPassDescriptor& renderPassDescriptor)
{
    for (int i = 0; i < MAX_COLOR_ATTCHMENT; ++i)
    {
        if (PixelFormat::NONE == _colorAttachmentsFormat[i])
            continue;
        
        _mtlRenderPipelineDescriptor.colorAttachments[i].pixelFormat = Utils::toMTLPixelFormat(_colorAttachmentsFormat[i]);
        setBlendState(_mtlRenderPipelineDescriptor.colorAttachments[i], blendDescriptor);
    }
    _mtlRenderPipelineDescriptor.depthAttachmentPixelFormat = Utils::toMTLPixelFormat(_depthAttachmentFormat);
    _mtlRenderPipelineDescriptor.stencilAttachmentPixelFormat = Utils::toMTLPixelFormat(_stencilAttachmentFormat);
}

CC_BACKEND_END
