#pragma once

#include "../RenderPipeline.h"
#include "../RenderPipelineDescriptor.h"
#include "BlendStateMTL.h"
#include <string>
#include <vector>
#include <memory>
#import <Metal/Metal.h>

CC_BACKEND_BEGIN

class RenderPipelineMTL : public RenderPipeline
{
public:
    RenderPipelineMTL(id<MTLDevice> mtlDevice, const RenderPipelineDescriptor& descriptor);
    ~RenderPipelineMTL();
        
    inline id<MTLRenderPipelineState> getMTLRenderPipelineState() const { return _mtlRenderPipelineState; }
    
    inline const std::shared_ptr<uint8_t>& getVertexUniformBuffer() const { return _vertexUniformBuffer; }
    inline const std::shared_ptr<uint8_t>& getFragmentUniformBuffer() const { return _fragementUniformBuffer; }
    
private:
    void setVertexLayout(MTLRenderPipelineDescriptor*, const RenderPipelineDescriptor&);
    void setBlendState(MTLRenderPipelineColorAttachmentDescriptor*);
    void setShaderModules(const RenderPipelineDescriptor&);
    void setBlendStateAndFormat(const RenderPipelineDescriptor&);
    
    id<MTLRenderPipelineState> _mtlRenderPipelineState = nil;
    id<MTLDevice> _mtlDevice = nil;
    
    std::shared_ptr<uint8_t> _vertexUniformBuffer = nullptr;
    std::shared_ptr<uint8_t> _fragementUniformBuffer = nullptr;
    
    MTLRenderPipelineDescriptor* _mtlRenderPipelineDescriptor = nil;
    BlendDescriptorMTL _blendDescriptorMTL;
};

CC_BACKEND_END
