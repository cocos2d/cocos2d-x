/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/


#ifndef _CC_GROUPCOMMAND_H_
#define _CC_GROUPCOMMAND_H_

#include <vector>
#include <unordered_map>

#include "base/CCRef.h"
#include "CCRenderCommand.h"

/**
 * @addtogroup renderer
 * @{
 */

NS_CC_BEGIN

//Used for internal
class GroupCommandManager : public Ref
{
public:
    int getGroupID();
    void releaseGroupID(int groupID);

protected:
    friend class Renderer;
    GroupCommandManager();
    ~GroupCommandManager();
    bool init();
    std::unordered_map<int, bool> _groupMapping;
    std::vector<int> _unusedIDs;
};

/**
@class GroupCommand
@brief
@~english
 GroupCommand is used to group several command together, and more, it can be nestd.
 So it is used to generate the hierarchy for the rendcommands. Evey group command will be assigned by a group ID.
 * @~chinese 
 GroupCommand用于将多个渲染命令打包成一个命令，而且可以嵌套。
 所以GroupCommand主要用来构建渲染命令的层级结构。
 每一个GroupCommand会分配到一个组ID。
 */
class CC_DLL GroupCommand : public RenderCommand
{
public:
    /**@~english
     Constructor.
     * @~chinese 
     * 构造函数。
     */
    GroupCommand();
    /**@~english
     Destructor.
     * @~chinese 
     * 析构函数。
     */
    ~GroupCommand();
    
    /**
    @~english Init function for group command.
    @~chinese 初始化GroupCommand。
    @param globalOrder @~english The globalZOrder of render command. @~chinese 命令的globalZOrder。
    */
    void init(float globalOrder);
    
    /**
    @~english called by renderer, get the group ID. 
    @~chinese 被渲染器调用,得到组ID。
    */
    inline int getRenderQueueID() const {return _renderQueueID;}
    
protected:
    int _renderQueueID;
};

NS_CC_END

/**
 end of support group
 @}
 */
#endif //_CC_GROUPCOMMAND_H_
