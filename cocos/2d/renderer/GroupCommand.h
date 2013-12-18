//
// Created by NiTe Luo on 11/13/13.
//



#ifndef _CC_GROUPCOMMAND_H_
#define _CC_GROUPCOMMAND_H_

#include "CCPlatformMacros.h"
#include "RenderCommand.h"
#include "RenderCommandPool.h"
#include <map>

NS_CC_BEGIN
using namespace std;

class GroupCommandManager : public Object
{
public:
    static GroupCommandManager* getInstance();

    ~GroupCommandManager();

    bool init();

    int getGroupID();
    void releaseGroupID(int groupID);

protected:
    GroupCommandManager();
    map<int, bool> _groupMapping;
};

class GroupCommand : public RenderCommand
{
protected:
    GroupCommand();
    ~GroupCommand();
public:
    void init(int viewport, float depth);

    // +----------+----------+-----+-----------------------------------+
    // |          |          |     |                |                  |
    // | ViewPort | Transluc |     |      Depth     |                  |
    // |   3 bits |    1 bit |     |    24 bits     |                  |
    // +----------+----------+-----+----------------+------------------+
    virtual int64_t generateID() override;

    inline bool isTranslucent() {return true;}
    inline int getRenderQueueID() {return _renderQueueID;}
    virtual void releaseToCommandPool() override;
    
protected:
    int _renderQueueID;
    
public:
    friend class RenderCommandPool<GroupCommand>;
    static RenderCommandPool<GroupCommand>& getCommandPool() { return _commandPool; }
protected:
    static RenderCommandPool<GroupCommand> _commandPool;
};

NS_CC_END

#endif //_CC_GROUPCOMMAND_H_
