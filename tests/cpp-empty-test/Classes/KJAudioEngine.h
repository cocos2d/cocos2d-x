#ifndef __KJAudioEngine_H__
#define __KJAudioEngine_H__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;
class KJAudioEngine : public Node{


public:
    static KJAudioEngine *getInstance();
    KJAudioEngine();
    
    void preload();
    int playEffect(const std::string& filePath, bool loop = false, float volume = 1.0f);
    int playMusic(const std::string& filePath, bool loop = false, float volume = 1.0f);
    void setMusicVolume(float value);
    void setEffectsVolume(float value);
    void setVolume(int audioID,float value);
    float _effectsVolume=1.0f;
    float _musicsVolume=1.0f;
    
private:
    static KJAudioEngine *_instance;

    int _musicID;
};
#endif
