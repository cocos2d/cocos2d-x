//
//  CCScissorCommand.cpp
//  cocos2d_libs
//
//  Created by Justin Graham on 11/11/14.
//
//

#include "CCScissorCommand.h"
#include "CCDirector.h"

NS_CC_BEGIN

int ScissorCommand::_scissorCount = 0;
ScissorCommand::tClippingRegions ScissorCommand::_clippingRegions;

BeginScissorCommand::BeginScissorCommand()
{
    _type = RenderCommand::Type::BEGIN_SCISSOR_COMMAND;
}

void BeginScissorCommand::init(float depth, const Rect& clippingRegion, bool respectPreviousScissor)
{
    _globalOrder = depth;
    _clippingRegion = clippingRegion;
    _respectPreviousScissor = respectPreviousScissor;
}

void BeginScissorCommand::execute()
{
    if (0 == _scissorCount)
        glEnable(GL_SCISSOR_TEST);
    
    if (0 < _scissorCount)
    {
        if (_respectPreviousScissor)
        {
            const auto previousClippingRegion = _clippingRegions.top();
            
            //set the intersection of _parentScissorRect and frame as the new scissor rect
            if (_clippingRegion.intersectsRect(previousClippingRegion))
            {
                float x = MAX(_clippingRegion.origin.x, previousClippingRegion.origin.x);
                float y = MAX(_clippingRegion.origin.y, previousClippingRegion.origin.y);
                float xx = MIN(_clippingRegion.origin.x+_clippingRegion.size.width, previousClippingRegion.origin.x+previousClippingRegion.size.width);
                float yy = MIN(_clippingRegion.origin.y+_clippingRegion.size.height, previousClippingRegion.origin.y+previousClippingRegion.size.height);
                _clippingRegion = Rect(x, y, xx-x, yy-y);
            }
        }
    }
    
    _clippingRegions.push(_clippingRegion);

    GLView* glView = Director::getInstance()->getOpenGLView();
    glView->setScissorInPoints(_clippingRegion.origin.x, _clippingRegion.origin.y, _clippingRegion.size.width, _clippingRegion.size.height);
    ++_scissorCount;
}


EndScissorCommand::EndScissorCommand()
{
    _type = RenderCommand::Type::END_SCISSOR_COMMAND;
}

void EndScissorCommand::init(float depth)
{
    _globalOrder = depth;
}

void EndScissorCommand::execute()
{
    --_scissorCount;
    if (0 == _scissorCount)
        glDisable(GL_SCISSOR_TEST);
    else
    {
        _clippingRegions.pop();
        const auto previousClippingRegion = _clippingRegions.top();
        GLView* glView = Director::getInstance()->getOpenGLView();
        glView->setScissorInPoints(previousClippingRegion.origin.x, previousClippingRegion.origin.y, previousClippingRegion.size.width, previousClippingRegion.size.height);
    }
}

NS_CC_END