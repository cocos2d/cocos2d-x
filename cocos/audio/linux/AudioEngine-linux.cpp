/**
 * @author cesarpachon
 */ 
#include "AudioEngine-linux.h"

#include "AudioPlayer.h"
#include "FmodAudioPlayer.h"

using namespace cocos2d;
using namespace cocos2d::experimental;
using namespace CocosDenshion;


static AudioPlayer* oAudioPlayer;

AudioEngineImpl::AudioEngineImpl(){
};

AudioEngineImpl::~AudioEngineImpl(){
  if(oAudioPlayer)
  {
      oAudioPlayer->close();
  }
};

    
bool AudioEngineImpl::init(){
  oAudioPlayer= FmodAudioPlayer::sharedPlayer();
  return true;
};

int AudioEngineImpl::play2d(const std::string &fileFullPath ,bool loop ,float volume){
  return oAudioPlayer->playEffect(fileFullPath.c_str(), loop, 1.0f, 0.0f, volume);
};

void AudioEngineImpl::setVolume(int audioID,float volume){
 /*@todo: we are not affecting each effect independently! we should be using audioid*/
  oAudioPlayer->setEffectsVolume(volume);
  
};

void AudioEngineImpl::setLoop(int audioID, bool loop){
  /*@todo: unimplemented!*/
};

bool AudioEngineImpl::pause(int audioID){
  oAudioPlayer->pauseEffect(audioID);
  return true;
};

bool AudioEngineImpl::resume(int audioID){
  oAudioPlayer->resumeEffect(audioID);
  return true;
};

bool AudioEngineImpl::stop(int audioID){
  oAudioPlayer->stopEffect(audioID);
  return true;
};

void AudioEngineImpl::stopAll(){
  oAudioPlayer->stopAllEffects();
};

float AudioEngineImpl::getDuration(int audioID){
  /*@todo: unimplemented*/
  return -1.0f;
};

float AudioEngineImpl::getCurrentTime(int audioID){
  /*@todo: unimplemented*/
  return -1.0f;
};

bool AudioEngineImpl::setCurrentTime(int audioID, float time){
  /*@todo: unimplemented*/
  return false; 
};

void AudioEngineImpl::setFinishCallback(int audioID, const std::function<void (int, const std::string &)> &callback){
  /*@todo: unimplemented*/
};

    
void AudioEngineImpl::uncache(const std::string& filePath){
  /*@todo: unimplemented*/
};

void AudioEngineImpl::uncacheAll(){
  /*@todo: unimplemented*/
};

    
/**
* other implementations return AudioCache, but that value is unused in main AudioEngine.cpp
*/ 
void AudioEngineImpl::preload(const std::string& filePath){
  /*@todo: unimplemented*/
};

    
void AudioEngineImpl::update(float dt){
  /*@todo: unimplemented*/
};
