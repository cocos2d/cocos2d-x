

#include "KJAudioEngine.h"
#include "audio/include/AudioEngine.h"

KJAudioEngine *KJAudioEngine::_instance = nullptr;

KJAudioEngine *KJAudioEngine::getInstance() {
    if (!_instance) {
        _instance = new KJAudioEngine();
    }
    
    return _instance;
}
KJAudioEngine::KJAudioEngine() {

}

int KJAudioEngine::playEffect(const std::string& filePath, bool loop, float volume ){

    return   experimental::AudioEngine::play2d(filePath,loop,volume*_effectsVolume);
}
int KJAudioEngine::playMusic(const std::string& filePath, bool loop , float volume ){
    experimental::AudioEngine::stop(_musicID);

    _musicID=experimental::AudioEngine::play2d(filePath,loop,volume*_musicsVolume);
    return  _musicID;
    
}
void KJAudioEngine::preload(){
  //  experimental::AudioEngine::uncacheAll();
    experimental::AudioEngine::preload("sounds/music-1.mp3");
    experimental::AudioEngine::preload("sounds/Click.caf");
    experimental::AudioEngine::preload("sounds/drift-1.caf");
    experimental::AudioEngine::preload("sounds/drift-2.caf");
    experimental::AudioEngine::preload("sounds/Explosion1.caf");
    experimental::AudioEngine::preload("sounds/Hide-Banner.caf");
    experimental::AudioEngine::preload("sounds/hit-1.caf");
    experimental::AudioEngine::preload("sounds/hit-2.caf");
    experimental::AudioEngine::preload("sounds/hit-3.caf");
    experimental::AudioEngine::preload("sounds/iteamCol.caf");
    experimental::AudioEngine::preload("sounds/locked.caf");
    experimental::AudioEngine::preload("sounds/nitro.caf");
    experimental::AudioEngine::preload("sounds/Show-Banner.caf");
    experimental::AudioEngine::preload("sounds/Speed.caf");
    experimental::AudioEngine::preload("sounds/Star-1.caf");
    experimental::AudioEngine::preload("sounds/Star-2.caf");
    experimental::AudioEngine::preload("sounds/switch.caf");
    experimental::AudioEngine::preload("sounds/starOff.caf");
    experimental::AudioEngine::preload("sounds/poof.caf");
    experimental::AudioEngine::preload("sounds/Train.mp3");
    experimental::AudioEngine::preload("sounds/Star-3.caf");
   // experimental::AudioEngine::end();

}
void KJAudioEngine::setVolume(int audioID,float value)
{
    experimental::AudioEngine::setVolume(audioID, value*_effectsVolume);
}


void KJAudioEngine::setMusicVolume(float value){
    _musicsVolume=value;
    experimental::AudioEngine::setVolume(_musicID, _musicsVolume);
}
void KJAudioEngine::setEffectsVolume(float value){
    _effectsVolume=value;
}