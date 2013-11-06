//
// Created by NiTe Luo on 11/6/13.
//



#ifndef _CC_QUADCOMMAND_H_
#define _CC_QUADCOMMAND_H_

#include "RenderCommand.h"

NS_CC_BEGIN


// +----------+----------+-----+-----------------------------------+
// |          |          |     |                |                  |
// | ViewPort | Transluc | Cmd |      Depth     |  Material ID     |
// |   3 bits |    1 bit |  1  |    24 bits     |      24 bit2     |
// +----------+----------+-----+----------------+------------------+
class QuadCommandID : public RenderCommandID
{

};

class QuadCommand : public RenderCommand
{

};

NS_CC_END

#endif //_CC_QUADCOMMAND_H_
