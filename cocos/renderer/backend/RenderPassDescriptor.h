#pragma once

#include "Macros.h"
#include "Types.h"

#include <array>
#include <vector>

CC_BACKEND_BEGIN

class Texture;
class RenderPass;

struct RenderPassColorAttachments
{
    RenderPassColorAttachments() = default;
    RenderPassColorAttachments(const RenderPassColorAttachments& rhs);
    ~RenderPassColorAttachments();
    RenderPassColorAttachments& operator=(const RenderPassColorAttachments& rhs);
    void setTexture(uint32_t attachment, Texture* texture);
    bool operator==(const RenderPassColorAttachments& colorAttachment) const;
    
    std::vector<Texture*> textures;
    
    std::array<float, 4> clearColor = {0.f, 0.f, 0.f, 0.f};
    bool needClearColor = false;
    
private:
    void releaseTextures() const;
    void retainTextures() const;
};

struct RenderPassDepthStencilAttachment
{
    RenderPassDepthStencilAttachment() = default;
    RenderPassDepthStencilAttachment(const RenderPassDepthStencilAttachment& rhs);
    ~RenderPassDepthStencilAttachment();
    RenderPassDepthStencilAttachment& operator =(const RenderPassDepthStencilAttachment& rhs);
    bool operator==(const RenderPassDepthStencilAttachment& renderAttachment) const;
    
    float clearDepth = 1.f;
    bool needClearDepth = false;
    
    uint32_t clearStencil = 0;
    bool needClearStencil = false;
    
    Texture *texture = nullptr;
};

class RenderPassDescriptor
{
public:    
    void setColorAttachment(uint32_t attachment, Texture* texture);
    void setClearColor(float r, float g, float b, float a);
    void setDepthStencilAttachment(Texture* texture);
    void setClearDepth(float clearValue);
    void setClearStencil(uint32_t clearValue);
    
    bool hasStencil() const;
    bool needGenerateRenderPassState() const;
    
    inline const RenderPassDepthStencilAttachment& getDepthStencilAttachment() const { return _depthStencilAttachment; }
    inline const RenderPassColorAttachments& getColorAttachments() const { return _colorAttachments; }
    inline bool getColorAttachmentSet() const {return _colorAttachmentsSet;}
    inline bool getDepthStencilAttachmentSet() const {return _depthStencilAttachmentSet;}
    
private:
    bool _colorAttachmentsSet = false;
    RenderPassColorAttachments _colorAttachments;
    
    bool _depthStencilAttachmentSet = false;
    struct RenderPassDepthStencilAttachment _depthStencilAttachment;
    
    friend class RenderPass;
};

CC_BACKEND_END
