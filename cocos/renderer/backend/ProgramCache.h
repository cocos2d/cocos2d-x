#pragma once

#include "Macros.h"
#include "base/CCRef.h"
#include "platform/CCPlatformMacros.h"
#include "Program.h"

#include <string>
#include <unordered_map>

CC_BACKEND_BEGIN

class ProgramCache : public Ref
{
public:
    /** returns the shared instance */
    static ProgramCache* getInstance();
    
    /** purges the cache. It releases the retained instance. */
    static void destroyInstance();
   
    backend::Program* newProgram(const std::string& vertexShader, const std::string& fragmentShader);
    void removeProgram(backend::Program* program);
    void removeUnusedProgram();
    void removeAllProgram();
    
protected:
    ProgramCache() = default;
    virtual ~ProgramCache();
    
    bool init();
    void addProgram(const std::string& vertexShader, const std::string& fragmentShader);
    
    static std::unordered_map<std::size_t, backend::Program*> _cachedPrograms;
    static ProgramCache *_sharedProgramCache;
};

CC_BACKEND_END
