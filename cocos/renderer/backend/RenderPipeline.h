#pragma once

#include "Macros.h"
#include "Types.h"

#include "base/CCRef.h"

#include <memory>

CC_BACKEND_BEGIN

class RenderPipeline : public cocos2d::Ref
{
public:
    inline const std::shared_ptr<std::vector<VertexLayout>> getVertexLayouts() const { return _vertexLayouts; }
    void updateVertexLayouts(const std::shared_ptr<std::vector<VertexLayout>> &layout) { _vertexLayouts = layout; }
protected:
    virtual ~RenderPipeline() = default;
    std::shared_ptr<std::vector<VertexLayout>> _vertexLayouts;
};

CC_BACKEND_END
