#include "../RenderPass.h"
#include "../RenderPassDescriptor.h"
#include "platform/CCGL.h"

#include <vector>

CC_BACKEND_BEGIN

class RenderPassGL : public RenderPass
{
public:
    RenderPassGL(const RenderPassDescriptor& descriptor);
    void apply(GLuint defaultFrameBuffer) const;
    
private:
    GLuint _frameBuffer = 0;
    bool _hasStencil = false;
};

CC_BACKEND_END
