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

#ifndef __CCSHADERCACHE_H__
#define __CCSHADERCACHE_H__

#include "CCRef.h"

#include <string>
#include <unordered_map>

NS_CC_BEGIN

class GLProgram;

/**
 * @addtogroup shaders
 * @{
 */

/** ShaderCache
 Singleton that stores manages GL shaders
 @since v2.0
 */
class CC_DLL ShaderCache : public Ref 
{
public:
    /**
     * @js ctor
     */
    ShaderCache();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ShaderCache();

    /** returns the shared instance */
    static ShaderCache* getInstance();

    /** purges the cache. It releases the retained instance. */
    static void destroyInstance();

    /** @deprecated Use getInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static ShaderCache* sharedShaderCache();

    /** @deprecated Use destroyInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static void purgeSharedShaderCache();

    /** loads the default shaders */
    void loadDefaultShaders();
    
    /** reload the default shaders */
    void reloadDefaultShaders();

    /** returns a GL program for a given key 
     */
    GLProgram * getProgram(const std::string &key);
    /** @deprecated Use getProgram() instead
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE GLProgram * programForKey(const std::string &key){ return getProgram(key); }

    /** adds a GLProgram to the cache for a given name */
    void addProgram(GLProgram* program, const std::string &key);

private:
    bool init();
    void loadDefaultShader(GLProgram *program, int type);

//    Dictionary* _programs;
    std::unordered_map<std::string, GLProgram*> _programs;
};

// end of shaders group
/// @}

NS_CC_END

#endif /* __CCSHADERCACHE_H__ */
