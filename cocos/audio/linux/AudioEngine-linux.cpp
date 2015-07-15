/**
 * @author cesarpachon
 */ 
#include "AudioEngine-linux.h"

using namespace cocos2d;
using namespace cocos2d::experimental;


AudioEngineImpl::AudioEngineImpl(){

};

AudioEngineImpl::~AudioEngineImpl(){
  
};

    
bool AudioEngineImpl::init(){
    return false;
};

int AudioEngineImpl::play2d(const std::string &fileFullPath ,bool loop ,float volume){
  return -1;
};

void AudioEngineImpl::setVolume(int audioID,float volume){
  
};

void AudioEngineImpl::setLoop(int audioID, bool loop){
  
};

bool AudioEngineImpl::pause(int audioID){
  return false;
};

bool AudioEngineImpl::resume(int audioID){
  return false;
};

bool AudioEngineImpl::stop(int audioID){
  return false;
};

void AudioEngineImpl::stopAll(){
  
};

float AudioEngineImpl::getDuration(int audioID){
  return -1.0f;
};

float AudioEngineImpl::getCurrentTime(int audioID){
  return -1.0;
};

bool AudioEngineImpl::setCurrentTime(int audioID, float time){
  return false; 
};

void AudioEngineImpl::setFinishCallback(int audioID, const std::function<void (int, const std::string &)> &callback){
  
};

    
void AudioEngineImpl::uncache(const std::string& filePath){
  
};

void AudioEngineImpl::uncacheAll(){
  
};

    
/**
* other implementations return AudioCache, but that value is unused in main AudioEngine.cpp
*/ 
void AudioEngineImpl::preload(const std::string& filePath){
  
};

    
void AudioEngineImpl::update(float dt){
  
};
