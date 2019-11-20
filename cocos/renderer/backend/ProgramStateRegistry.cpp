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

void ProgramStateRegistry::registerProgram(ProgramType programType, int maxCount, Program* program)
{
    auto maxIndex = maxCount - 1;
    auto it = this->_registry.find(programType);
    if (it == this->_registry.end()) {
        it = this->_registry.emplace(programType, std::vector<Program*>{}).first;
        it->second.resize(CC_META_TEXTURES);
    }
    if (maxIndex < it->second.size())
        it->second[maxIndex] = program;
}

void ProgramStateRegistry::clearPrograms() {
    this->_registry.clear();
}

ProgramState* ProgramStateRegistry::getProgramState(ProgramType programType, int maxCount)
{
    auto maxIndex = maxCount - 1;
    auto it = this->_registry.find(programType);
    if (it != this->_registry.end() && it->second.size() > maxIndex) {
        auto fallback = it->second[maxIndex];
        if (fallback)
            return new(std::nothrow) ProgramState(fallback);
    }

    return new(std::nothrow) ProgramState(Program::getBuiltinProgram((ProgramType)programType));
}

ProgramType ProgramStateRegistry::getProgramType(ProgramType programType, TextureBackend* texture2d)
{
    return this->getProgramType(programType, texture2d->getCount());
}

ProgramType ProgramStateRegistry::getProgramType(ProgramType programType, int maxCount)
{
    auto maxIndex = maxCount - 1;
    auto it = this->_registry.find(programType);
    if (it != this->_registry.end() && it->second.size() > maxIndex) {
        auto fallback = it->second[maxIndex];
        if (fallback)
            return fallback->getProgramType();
    }
    return programType;
}
//end of _backend group
/// @}
CC_BACKEND_END
