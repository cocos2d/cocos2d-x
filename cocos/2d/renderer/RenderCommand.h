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

enum RenderCommandType
{
    QUAD_COMMAND,
    CUSTOM_COMMAND,
    GROUP_COMMAND,
    UNKNOWN_COMMAND,
};

//TODO make RenderCommand inherent from Object
class RenderCommand
{
protected:
    RenderCommand();
    virtual ~RenderCommand();
public:
    virtual int64_t generateID() = 0;

    virtual /**
    * Get Render Command Id
    */
    inline int64_t getID() { return _id; }
    
    virtual inline RenderCommandType getType() { return _type; }
    virtual void releaseToCommandPool() =0;
protected:
    void printID();

protected:
    //Generated IDs
    int64_t _id; /// used for sorting render commands
    RenderCommandType  _type;
};

NS_CC_END

#endif //__CCRENDERCOMMAND_H_
