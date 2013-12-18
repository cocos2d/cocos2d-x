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

//TODO make RenderCommand inherent from Object
class RenderCommand
{
public:

    enum class Type
    {
        QUAD_COMMAND,
        CUSTOM_COMMAND,
        GROUP_COMMAND,
        UNKNOWN_COMMAND,
    };

    virtual int64_t generateID() = 0;

    /** Get Render Command Id */
    virtual inline int64_t getID() { return _id; }
    
    virtual inline Type getType() { return _type; }
    virtual void releaseToCommandPool() =0;

protected:
    RenderCommand();
    virtual ~RenderCommand();

    void printID();

    //Generated IDs
    int64_t _id; /// used for sorting render commands
    Type _type;
};

NS_CC_END

#endif //__CCRENDERCOMMAND_H_
