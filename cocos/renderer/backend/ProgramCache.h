/****************************************************************************
 Copyright (c) 2018-2019 Xiamen Yaji Software Co., Ltd.

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
 
#pragma once

#include "Macros.h"
#include "base/CCRef.h"
#include "platform/CCPlatformMacros.h"
#include "Program.h"

#include <string>
#include <unordered_map>

CC_BACKEND_BEGIN
/**
 * @addtogroup _backend
 * @{
 */

/**
 * Cache and reuse program object.
 */
class ProgramCache : public Ref
{
public:
    /** returns the shared instance */
    static ProgramCache* getInstance();
    
    /** purges the cache. It releases the retained instance. */
    static void destroyInstance();
   
   /**
     * @param vertexShader Specifes the vertex shader source.
     * @param fragmentShader Specifes the fragment shader source.
     */
    backend::Program* newProgram(const std::string& vertexShader, const std::string& fragmentShader);
    
    /// get built-in program
    backend::Program* newBuiltinProgram(ProgramType type);
    
    /**
     * Remove a program object from cache.
     * @param program Specifies the program object to move.
     */
    void removeProgram(backend::Program* program);

    /**
     * Remove all unused program objects from cache.
     */
    void removeUnusedProgram();

    /**
     * Remove all program objects from cache.
     */
    void removeAllPrograms();
    
protected:
    ProgramCache() = default;
    virtual ~ProgramCache();
    
    /**
     * Pre-load programs into cache.
     */
    bool init();

    /**
     * @param vertexShader Specifes the vertex shader source.
     * @param fragmentShader Specifes the fragment shader source.
     */
    void addProgram(const std::string& vertexShader, const std::string& fragmentShader);
    
    /// Add built-in program
    void addProgram(ProgramType type);
    
    static std::unordered_map<std::size_t, backend::Program*> _cachedPrograms; ///< The cached program object.
    static ProgramCache *_sharedProgramCache; ///< A shared instance of the program cache.
};

//end of _backend group
/// @}
CC_BACKEND_END
