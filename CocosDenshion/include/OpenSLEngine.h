#ifndef _OPENSL_ENGINE_H_
#define _OPENSL_ENGINE_H_

#include "OpenSL.h"

class OpenSLEngine
{
public:
    OpenSLEngine();
    ~OpenSLEngine();

	bool initEngine();

    static OpenSLEngine* sharedEngine();

    static void end();

    float getEffectsVolume();

    void setEffectsVolume(float volume);

    unsigned int playEffect(const char* pszFilePath, bool bLoop = false);

    void pauseEffect(unsigned int nSoundId);

    void pauseAllEffects();

    void resumeEffect(unsigned int nSoundId);

    void resumeAllEffects();

    void stopEffect(unsigned int nSoundId);

    void stopAllEffects();

    void preloadEffect(const char* pszFilePath);

    void unloadEffect(const char* pszFilePath);
};


#endif
