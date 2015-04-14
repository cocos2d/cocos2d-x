/****************************************************************************
Copyright 2014 Chukong Technologies Inc.
 
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

#ifndef __CCGLPROGRAMSTATECACHE_H__
#define __CCGLPROGRAMSTATECACHE_H__

#include "base/ccTypes.h"
#include "base/CCVector.h"
#include "base/CCMap.h"
#include "math/Vec2.h"
#include "math/Vec3.h"
#include "math/Vec4.h"

/**
 * @addtogroup support
 * @{
 */

NS_CC_BEGIN

class GLProgram;

class GLProgramState;

/**
 Some GLprogram state could be shared. GLProgramStateCache is used to cache this, and will reuse the
 old GLProgramState, which will accelerate the creation of game objects such as sprites, particles etc.
 */
class CC_DLL GLProgramStateCache
{
public:
    /**Get the GLProgramStateCache singleton instance.*/
    static GLProgramStateCache* getInstance();
    /**Destroy the GLProgramStateCache singleton.*/
    static void destroyInstance();
    
    /**Get the shared GLProgramState by the owner GLProgram.*/
    GLProgramState* getGLProgramState(GLProgram* program);
    /**Remove all the cached GLProgramState.*/
	void removeAllGLProgramState();
    /**Remove unused GLProgramState.*/
    void removeUnusedGLProgramState();

protected:
    GLProgramStateCache();
    ~GLProgramStateCache();
    
    Map<GLProgram*, GLProgramState*> _glProgramStates;
    static GLProgramStateCache* s_instance;
};

NS_CC_END
/**
 end of support group
 @}
 */
#endif /* __CCGLPROGRAMSTATECACHE_H__ */
