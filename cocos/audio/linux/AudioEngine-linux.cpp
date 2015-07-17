/**
 * @author cesarpachon
 */ 
#include <cstring>
#include "AudioEngine-linux.h"
#include "cocos2d.h"
using namespace cocos2d;
using namespace cocos2d::experimental;
//using namespace CocosDenshion;


void ERRCHECKWITHEXIT(FMOD_RESULT result) {
	if (result != FMOD_OK) {
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
//		exit(-1);
	}
}

bool ERRCHECK(FMOD_RESULT result) {
	if (result != FMOD_OK) {
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		return true;
	}
	return false;
}


AudioEngineImpl::AudioEngineImpl(){
};

AudioEngineImpl::~AudioEngineImpl(){
  FMOD_RESULT result;
  result = pSystem->close();
  ERRCHECKWITHEXIT(result);
  result = pSystem->release();
  ERRCHECKWITHEXIT(result);
};

    
bool AudioEngineImpl::init(){
  FMOD_RESULT result;
  /*
  Create a System object and initialize.
  */
  result = FMOD::System_Create(&pSystem);
  ERRCHECKWITHEXIT(result);
  
  result = pSystem->setOutput(FMOD_OUTPUTTYPE_ALSA);
  ERRCHECKWITHEXIT(result);

  result = pSystem->init(32, FMOD_INIT_NORMAL, 0);
  ERRCHECKWITHEXIT(result);

  mapEffectSound.clear();
  printf("DEBUG: AudioEngineImpl::system initialized\n"); 

  return true;
};

int AudioEngineImpl::play2d(const std::string &fileFullPath ,bool loop ,float volume){
  int id = preload(fileFullPath); 
  printf("DEBUG: AudioEngineImpl::play2d with id %d\n", id); 
  if(id > 0) 
    resume(id); 
  return id; 
};

void AudioEngineImpl::setVolume(int audioID,float volume){
  try{
    mapEffectSound[audioID]->setMusicChannelVolume(0, volume);
  }catch(const std::out_of_range& oor){
      printf("AudioEngineImpl::setVolume: invalid audioID: %d\n", audioID);
  }
};

void AudioEngineImpl::setLoop(int audioID, bool loop){
 printf("AudioEngineImpl::setLoop: UNIMPLEMENTED! audioID: %d\n", audioID);
  /*@todo: unimplemented!*/
};

bool AudioEngineImpl::pause(int audioID){
 printf("AudioEngineImpl::pause: audioID: %d\n", audioID);
  try{
    FMOD::Sound * sound = mapEffectSound[audioID]; 
    FMOD::Channel *channel = getChannel(sound);
    channel->setPaused(true); 
    AudioEngine::_audioIDInfoMap[audioID].state = AudioEngine::AudioState::PAUSED;
    return true; 
  }catch(const std::out_of_range& oor){
      printf("AudioEngineImpl::pause: invalid audioID: %d\n", audioID);
      return false;
  }
};

bool AudioEngineImpl::resume(int audioID){
   printf("AudioEngineImpl::resume: audioID: %d\n", audioID);
try{
    FMOD::Sound * sound = mapEffectSound[audioID]; 
    FMOD::Channel *channel = getChannel(sound);

    if(!channel){
    printf("DEBUG: AudioEngineImpl::resume no channel\n"); 
      //starts the sound in pause mode, use the channel to unpause
      FMOD_RESULT result = pSystem->playSound(FMOD_CHANNEL_FREE, sound, true, &channel);
      if(ERRCHECK(result)){
	return false; 
      }
      sound->setUserData(channel); 
    }
    
    //channel->setLoopCount(0);
    channel->setPaused(false); 
     AudioEngine::_audioIDInfoMap[audioID].state = AudioEngine::AudioState::PLAYING;
    printf("DEBUG: AudioEngineImpl::resume done\n"); 
    
    return true; 
  }catch(const std::out_of_range& oor){
      printf("AudioEngineImpl::resume: invalid audioID: %d\n", audioID);
      return false;
  }
};

bool AudioEngineImpl::stop(int audioID){
   printf("AudioEngineImpl::stop: audioID: %d\n", audioID);

  try{
    FMOD::Sound * sound = mapEffectSound[audioID]; 
    FMOD::Channel *channel = getChannel(sound);
    channel->stop(); 
    return true; 
  }catch(const std::out_of_range& oor){
      printf("AudioEngineImpl::stop: invalid audioID: %d\n", audioID);
      return false;
  }
};

void AudioEngineImpl::stopAll(){
};

float AudioEngineImpl::getDuration(int audioID){
  /*@todo: unimplemented*/
  return AudioEngine::TIME_UNKNOWN;
};

float AudioEngineImpl::getCurrentTime(int audioID){
  /*@todo: unimplemented*/
  return AudioEngine::TIME_UNKNOWN;
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
int AudioEngineImpl::preload(const std::string& filePath){
  int id = find(filePath); 
  if(id < 0){
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filePath);
    FMOD::Sound* pSound = NULL;
    FMOD_RESULT result = pSystem->createSound(fullPath.c_str(), FMOD_LOOP_NORMAL, 0, &pSound);
    if (ERRCHECK(result)){
      printf("sound effect in %s could not be preload\n", filePath.c_str());
      return -1;
    }
    id = mapEffectSound.size() + 1;
    //we are going to use UserData to store pointer to Channel when playing
    pSound->setUserData(nullptr);
    mapEffectSound[id] = pSound; 
  }
  return id; 
};

    
void AudioEngineImpl::update(float dt){
  pSystem->update();
};

int AudioEngineImpl::find(const std::string &path){
  static const int buffSize = 200;
  static char cBuffer[buffSize]; 
  std::string fullPath = FileUtils::getInstance()->fullPathForFilename(path);  
  int id = -1; 
  for (auto it = mapEffectSound.cbegin(); it != mapEffectSound.cend(); ++it) {
    it->second->getName(cBuffer, buffSize);
    if(std::strcmp(cBuffer, fullPath.c_str())== 0){
      return it->first; 
    }
  }
  return id; 
}


FMOD::Channel * AudioEngineImpl::getChannel(FMOD::Sound *sound){
  FMOD::Channel *channel = nullptr;
  void * data; 
  sound->getUserData(&data);
  if(data){
    channel = (FMOD::Channel *) data; 
  }
  return channel; 
};
