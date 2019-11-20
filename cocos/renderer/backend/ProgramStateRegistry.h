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
/*
  Group by programType and texIndex
  default, we register:
    programType = positionTextureColor, texIndex = 0 ---> positionTextureColorDefault
    programType = positionTextureColor, texIndex = 1 ---> positionTextureColorDualETC1

*/
class ProgramStateRegistry : public Ref {
public:
    /** returns the shared instance */
    static ProgramStateRegistry* getInstance();

    /** purges the cache. It releases the retained instance. */
    static void destroyInstance();

    bool init();

    void registerProgram(ProgramType programType, int maxCount, Program*);
    void clearPrograms();
    ProgramState* getProgramState(ProgramType programType, int maxCount);

    ProgramType getProgramType(ProgramType programType, TextureBackend* texture2d);
    ProgramType getProgramType(ProgramType programType, int maxCount);

protected:

    std::unordered_map<ProgramType, std::vector<Program*>> _registry;
};

//end of _backend group
/// @}
CC_BACKEND_END
