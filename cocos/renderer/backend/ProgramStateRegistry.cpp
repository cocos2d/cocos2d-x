#pragma once

#include "ProgramStateRegistry.h"

CC_BACKEND_BEGIN

static ProgramStateRegistry* _sharedStateRegistry = nullptr;
/** returns the shared instance */
ProgramStateRegistry* ProgramStateRegistry::getInstance()
{
    if (_sharedStateRegistry)
        return _sharedStateRegistry;

    _sharedStateRegistry = new (std::nothrow) ProgramStateRegistry();
    if (!_sharedStateRegistry->init())
    {
        CC_SAFE_RELEASE_NULL(_sharedStateRegistry);
    }

    return _sharedStateRegistry;
}

/** purges the cache. It releases the retained instance. */
void ProgramStateRegistry::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(_sharedStateRegistry);
}

bool ProgramStateRegistry::init()
{
    return true;
}

void ProgramStateRegistry::registerProgram(ProgramType programType, int textureFormatEXT, Program* program)
{
    uint32_t key = (static_cast<uint32_t>(programType) << 16) | textureFormatEXT;
    auto it = this->_registry.find(key);
    if (it == this->_registry.end())
        this->_registry.emplace(key, program).first;
    else
        it->second = program;
}

void ProgramStateRegistry::clearPrograms() {
    this->_registry.clear();
}

ProgramState* ProgramStateRegistry::getProgramState(ProgramType programType, int textureFormatEXT)
{
    uint32_t key = (static_cast<uint32_t>(programType) << 16) | textureFormatEXT;
    auto it = this->_registry.find(key);
    if (it != this->_registry.end()) {
        auto fallback = it->second;
        if (fallback)
            return new(std::nothrow) ProgramState(fallback);
    }

    return new(std::nothrow) ProgramState(Program::getBuiltinProgram((ProgramType)programType));
}

ProgramType ProgramStateRegistry::getProgramType(ProgramType programType, int textureFormatEXT)
{
    uint32_t key = (static_cast<uint32_t>(programType) << 16) | textureFormatEXT;
    auto it = this->_registry.find(key);
    if (it != this->_registry.end()) {
        auto fallback = it->second;
        if (fallback)
            return fallback->getProgramType();
    }
    return programType;
}
//end of _backend group
/// @}
CC_BACKEND_END
