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
    inline id<MTLDepthStencilState> getMTLDepthStencilState() const { return _mtlDepthStencilState; }
    
    inline const std::shared_ptr<uint8_t>& getVertexUniformBuffer() const { return _vertexUniformBuffer; }
    inline const std::shared_ptr<uint8_t>& getFragmentUniformBuffer() const { return _fragementUniformBuffer; }
    inline const std::vector<std::string>& getVertexUniforms() const { return _vertexUniforms; }
    inline const std::vector<std::string>& getFragmentUniforms() const { return _fragmentUniforms; }
    inline const std::vector<std::string>& getVertexTextures() const { return _vertexTextures; }
    inline const std::vector<std::string>& getFragmentTextures() const { return _fragmentTextures; }
    
private:
    void setVertexLayout(MTLRenderPipelineDescriptor*, const RenderPipelineDescriptor&);
    void setBlendState(MTLRenderPipelineColorAttachmentDescriptor*);
    void setShaderModules(const RenderPipelineDescriptor&);
    void setBlendStateAndFormat(const RenderPipelineDescriptor&);
    
    id<MTLRenderPipelineState> _mtlRenderPipelineState = nil;
    id<MTLDepthStencilState> _mtlDepthStencilState = nil;
    id<MTLDevice> _mtlDevice = nil;
    
    std::shared_ptr<uint8_t> _vertexUniformBuffer = nullptr;
    std::vector<std::string> _vertexUniforms;
    std::vector<std::string> _vertexTextures;
    
    std::shared_ptr<uint8_t> _fragementUniformBuffer = nullptr;
    std::vector<std::string> _fragmentUniforms;
    std::vector<std::string> _fragmentTextures;
    
    MTLRenderPipelineDescriptor* _mtlRenderPipelineDescriptor = nil;
    BlendDescriptorMTL _blendDescriptorMTL;
};

CC_BACKEND_END
