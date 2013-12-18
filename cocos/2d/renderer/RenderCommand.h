//
// Created by NiTe Luo on 10/31/13.
//



#ifndef __CCRENDERCOMMAND_H_
#define __CCRENDERCOMMAND_H_

#include "CCPlatformMacros.h"
#include <stdint.h>
#include "ccTypes.h"
#include "kazmath/GL/matrix.h"

NS_CC_BEGIN

//Currently we use 24 bit for depth, so the max is 2^24=16777216
#define CC_RENDERER_DEPTH_MAX 16777216
#define CC_RENDERER_DEPTH_HALF 8388608
#define CC_RENDERER_DEPTH_MIN 0

enum RenderCommandType
{
    QUAD_COMMAND,
    CUSTOM_COMMAND,
    GROUP_COMMAND,
    UNKNOWN_COMMAND,
};

class RenderCommand
{
protected:
    RenderCommand();
    virtual ~RenderCommand();
public:
    virtual int64_t generateID() = 0;
    void init(int viewport, float depth);
    
    /**
    * Get Render Command Id
    */
    virtual inline int64_t getID() { return _id; }
    
    virtual inline RenderCommandType getType() { return _type; }
    virtual void releaseToCommandPool() =0;
protected:
    void printID();

protected:
    //Generated IDs
    int64_t _id; /// used for sorting render commands
    RenderCommandType  _type;
    
    int _viewport; /// Which view port it belongs to
    int32_t _depth; /// Depth of the render command
};

NS_CC_END

#endif //__CCRENDERCOMMAND_H_
