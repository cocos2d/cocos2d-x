/****************************************************************************
Copyright (c) 2011      Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
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

#ifndef __CCGLPROGRAMCACHE_H__
#define __CCGLPROGRAMCACHE_H__

#include <string>
#include <unordered_map>

#include "base/CCRef.h"

/**
 * @addtogroup renderer
 * @{
 */

NS_CC_BEGIN

class GLProgram;

/** @class GLProgramCache
@brief
@~english Singleton that stores manages GLProgram objects (shaders)
 * @~chinese GLProgramCache
 * 单例对象,用于存储和管理GLProgram(shaders)。
 @since v2.0
 */
class CC_DLL GLProgramCache : public Ref
{
public:
    /**@~english
    Constructor.
     * @~chinese 
     * 构造函数。
     * @js ctor
     */
    GLProgramCache();
    /**@~english
    Destructor.
     * @~chinese 
     * 析构函数。
     * @js NA
     * @lua NA
     */
    ~GLProgramCache();

    /** @~english returns the shared instance  @~chinese 返回单例对象。*/
    static GLProgramCache* getInstance();

    /** @~english purges the cache. It releases the retained instance.  @~chinese 清理单例对象。*/
    static void destroyInstance();

    /**
    @~english Deprecated function, get the instance, Use getInstance() instead. 
    @~chinese Deprecate函数，用于返回单例，请使用getInstance()函数。
    */
    CC_DEPRECATED_ATTRIBUTE static GLProgramCache* sharedShaderCache();

    /**
    @~english Deprecated function, destroy the instance, Use destroyInstance() instead.
    @~chinese Deprecate函数，用于清理单例，请使用destroyInstance()函数。
     */
    CC_DEPRECATED_ATTRIBUTE static void purgeSharedShaderCache();

    /** 
    @~english loads the default shaders.
    @~chinese 加载默认的着色器。
    */
    void loadDefaultGLPrograms();
    CC_DEPRECATED_ATTRIBUTE void loadDefaultShaders() { loadDefaultGLPrograms(); }

    /** 
    @~english reload the default shaders.
    @~chinese 重新加载默认的着色器。
    */
    void reloadDefaultGLPrograms();
    CC_DEPRECATED_ATTRIBUTE void reloadDefaultShaders() { reloadDefaultGLPrograms(); }

    /** @~english returns a GL program for a given key.
     * @~chinese 按照名字获得对应的GLProgram。
     @param key @~english The name of GLProgram. @~chinese GLProgram的名字。
     @return @~english The GLProgram. @~chinese 对应的GLProgram。
     */
    GLProgram * getGLProgram(const std::string &key);
    CC_DEPRECATED_ATTRIBUTE GLProgram * getProgram(const std::string &key) { return getGLProgram(key); }
    CC_DEPRECATED_ATTRIBUTE GLProgram * programForKey(const std::string &key){ return getGLProgram(key); }

    /** 
    @~english adds a GLProgram to the cache for a given name.
    @~chinese 用给定名字在cache中添加一个GLProgram。
    @param key @~english The name of GLProgram. @~chinese GLProgram的名字。
    @param program @~english GLProgram. @~chinese GLProgram。
    */
    void addGLProgram(GLProgram* program, const std::string &key);
    CC_DEPRECATED_ATTRIBUTE void addProgram(GLProgram* program, const std::string &key) { addGLProgram(program, key); }
    
    /** reload default programs these are relative to light */
    void reloadDefaultGLProgramsRelativeToLights();

private:
    /**
        Init and load predefined shaders.
    */
    bool init();
    void loadDefaultGLProgram(GLProgram *program, int type);

    /** Get macro define for lights in current openGL driver.*/
    std::string getShaderMacrosForLight() const;

    /** Predefined shaders. */
    std::unordered_map<std::string, GLProgram*> _programs;
};

NS_CC_END
// end of shaders group
/// @}

#endif /* __CCGLPROGRAMCACHE_H__ */
