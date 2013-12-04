//
// Created by NiTe Luo on 11/8/13.
//



#ifndef _CC_CUSTOMCOMMAND_H_
#define _CC_CUSTOMCOMMAND_H_

#include "RenderCommand.h"
#include "RenderCommandPool.h"

NS_CC_BEGIN
using namespace std;

class CustomCommand : public RenderCommand
{
protected:
    CustomCommand();
    ~CustomCommand();
    
public:
    void init(int viewport, int32_t depth);

    // +----------+----------+-----+-----------------------------------+
    // |          |          |     |                |                  |
    // | ViewPort | Transluc |     |      Depth     |                  |
    // |   3 bits |    1 bit |     |    24 bits     |                  |
    // +----------+----------+-----+----------------+------------------+
    virtual int64_t generateID();

    void execute();

    inline bool isTranslucent() { return true; }
    virtual void releaseToCommandPool() override;

public:
    function<void()> func;

protected:
    int _viewport;

    int32_t _depth;
    
public:
    friend class RenderCommandPool<CustomCommand>;
    static RenderCommandPool<CustomCommand>& getCommandPool() { return _commandPool; }
protected:
    static RenderCommandPool<CustomCommand> _commandPool;

};

NS_CC_END

#endif //_CC_CUSTOMCOMMAND_H_
