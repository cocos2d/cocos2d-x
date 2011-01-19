#ifndef __SIMPLE_AUDIO_ENGINE_JNI__
#define __SIMPLE_AUDIO_ENGINE_JNI__

#include <jni.h>

extern "C"
{
    extern void playBackgroundMusicJNI(const char *path, bool isLoop);
}

#endif // __SIMPLE_AUDIO_ENGINE_JNI__