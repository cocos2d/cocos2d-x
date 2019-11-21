#pragma once
#include "Macros.h"
#include "base/CCRef.h"
#include "platform/CCPlatformMacros.h"
#include "Program.h"
#include "ProgramState.h"

#include <string>
#include <unordered_map>

namespace std
{
    template <>
    struct hash<cocos2d::backend::ProgramType>
    {
        typedef cocos2d::backend::ProgramType argument_type;
        typedef std::size_t result_type;
        result_type operator()(argument_type const& v) const
        {
            return hash<int>()(static_cast<int>(v));
        }
    };
};

CC_BACKEND_BEGIN
/**
 * @addtogroup _backend
 * @{
 * #todo: Rename to ProgramStateRegistry
 */
class ProgramStateRegistry : public Ref {
public:
    /** returns the shared instance */
    static ProgramStateRegistry* getInstance();

    /** purges the cache. It releases the retained instance. */
    static void destroyInstance();

    bool init();
    void clearPrograms();

    void registerProgram(ProgramType programType, int textureFormatEXT, Program*);

    ProgramState* getProgramState(ProgramType programType, int textureFormatEXT);
    ProgramType getProgramType(ProgramType programType, int textureFormatEXT);

protected:

    std::unordered_map<uint32_t, Program*> _registry;
};

//end of _backend group
/// @}
CC_BACKEND_END
