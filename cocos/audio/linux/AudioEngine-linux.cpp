/**
 * @author cesarpachon
 */ 
#include <cstring>
#include "AudioEngine-linux.h"
#include "cocos2d.h"
using namespace cocos2d;
using namespace cocos2d::experimental;
//using namespace CocosDenshion;

AudioEngineImpl * g_instance = nullptr;


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


/**
 * 
 */
FMOD_RESULT F_CALLBACK channelCallback(FMOD_CHANNEL *channel, FMOD_CHANNEL_CALLBACKTYPE controlType, void *commandData1, void *commandData2)
{
	if(controlType == FMOD_CHANNEL_CALLBACKTYPE_END){
		printf("channelCallback\n");
		g_instance->onSoundFinished((FMOD::Channel *)channel);
	}else{
		printf("other callback mode\n");
	}
    return FMOD_OK;
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
  
   auto scheduler = cocos2d::Director::getInstance()->getScheduler();
   scheduler->schedule(schedule_selector(AudioEngineImpl::update), this, 0.05f, false);

  
  g_instance = this; 
  
  return true;
};

int AudioEngineImpl::play2d(const std::string &fileFullPath ,bool loop ,float volume){
  int id = preload(fileFullPath); 
  //mapEffectSound[id].channel->setMode();  
  mapEffectSound[id].channel->setLoopCount(loop?-1:0); 
    mapEffectSound[id].channel->setPaused(true); 
    mapEffectSound[id].channel->setVolume(volume);
    AudioEngine::_audioIDInfoMap[id].state = AudioEngine::AudioState::PAUSED;
  printf("DEBUG: AudioEngineImpl::play2d with id %d loop %d volume %.3f\n", id, loop, volume); 
  if(id >= 0) 
    resume(id); 
  return id; 
};

void AudioEngineImpl::setVolume(int audioID,float volume){
  try{
	mapEffectSound[audioID].channel->setVolume(volume);
  }catch(const std::out_of_range& oor){
      printf("AudioEngineImpl::setVolume: invalid audioID: %d\n", audioID);
  }
};

void AudioEngineImpl::setLoop(int audioID, bool loop){
 printf("AudioEngineImpl::setLoop: audioID: %d\n", audioID);
  try{
    mapEffectSound[audioID].channel->setLoopCount(loop?-1:0); 
    //AudioEngine::_audioIDInfoMap[audioID].state = AudioEngine::AudioState::PAUSED;
  }catch(const std::out_of_range& oor){
      printf("AudioEngineImpl::setLoop: invalid audioID: %d\n", audioID);
  }
};

bool AudioEngineImpl::pause(int audioID){
 printf("AudioEngineImpl::pause: audioID: %d\n", audioID);
  try{
    mapEffectSound[audioID].channel->setPaused(true); 
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

    if(!mapEffectSound[audioID].channel){
    printf("DEBUG: AudioEngineImpl::resume no channel\n"); 
		FMOD::Channel *channel = nullptr;
      //starts the sound in pause mode, use the channel to unpause
      FMOD_RESULT result = pSystem->playSound(FMOD_CHANNEL_FREE, mapEffectSound[audioID].sound, true, &channel);
      if(ERRCHECK(result)){
		return false; 
      }
      channel->setUserData((void *)mapEffectSound[audioID].id);
      mapEffectSound[audioID].channel = channel; 
    }
    
    mapEffectSound[audioID].channel->setPaused(false); 
     AudioEngine::_audioIDInfoMap[audioID].state = AudioEngine::AudioState::PLAYING;
    printf("DEBUG: AudioEngineImpl::resume done\n"); 
    
    return true; 
  }catch(const std::out_of_range& oor){
      printf("AudioEngineImpl::resume: invalid audioID: %d\n", audioID);
      return false;
  }
};

bool AudioEngineImpl::stop(int audioID){
  try{
    mapEffectSound[audioID].channel->stop(); 
	mapEffectSound[audioID].channel = nullptr; 
    return true; 
  }catch(const std::out_of_range& oor){
      printf("AudioEngineImpl::stop: invalid audioID: %d\n", audioID);
      return false;
  }
};

void AudioEngineImpl::stopAll(){
};

float AudioEngineImpl::getDuration(int audioID){
  try{
    FMOD::Sound * sound = mapEffectSound[audioID].sound; 
	unsigned int length; 
	FMOD_RESULT result = sound->getLength(&length, FMOD_TIMEUNIT_MS);
	ERRCHECK(result);
	float duration = (float)length / 1000.0f; 
	printf("AudioEngineImpl::getDuration audioid %d: %.3f\n", audioID, duration);
	return duration;
    }catch(const std::out_of_range& oor){
      printf("AudioEngineImpl::getDuration: invalid audioID: %d\n", audioID);
	return AudioEngine::TIME_UNKNOWN;
  }
};

float AudioEngineImpl::getCurrentTime(int audioID){
 try{
	unsigned int position; 
	FMOD_RESULT result = mapEffectSound[audioID].channel->getPosition(&position, FMOD_TIMEUNIT_MS);
	ERRCHECK(result);
	float currenttime = position /1000.0f;
	//printf("AudioEngineImpl::getCurrentTime %d %.3f\n", audioID, currenttime);
	return currenttime; 
    }catch(const std::out_of_range& oor){
      printf("AudioEngineImpl::getCurrentTime: invalid audioID: %d\n", audioID);
	return AudioEngine::TIME_UNKNOWN;
  }
};

bool AudioEngineImpl::setCurrentTime(int audioID, float time){
 try{
	unsigned int position = (unsigned int)(time * 1000.0f); 
	printf("AudioEngineImpl::setCurrentTime %d %d\n", audioID, position);
    FMOD_RESULT result = mapEffectSound[audioID].channel->setPosition(position, FMOD_TIMEUNIT_MS);
    ERRCHECK(result);
	}catch(const std::out_of_range& oor){
      printf("AudioEngineImpl::setCurrentTime: invalid audioID: %d\n", audioID);
  }
};

void AudioEngineImpl::setFinishCallback(int audioID, const std::function<void (int, const std::string &)> &callback){
 try{
	 printf("AUdioEngineImpl::setFInishCallback %d\n", audioID);
	FMOD::Channel * channel = mapEffectSound[audioID].channel;
	mapEffectSound[audioID].callback = callback; 
	FMOD_RESULT result = channel->setCallback(channelCallback);
	ERRCHECK(result);
	}catch(const std::out_of_range& oor){
      printf("AudioEngineImpl::setFinishCallback: invalid audioID: %d\n", audioID);
  }
};


void AudioEngineImpl::onSoundFinished(FMOD::Channel * channel){
	size_t id; 
	try{
	printf("AudioEngineImpl::OnSoundFinished ");
	void * data;
	channel->getUserData(&data);
	id = (size_t) data; 
	if(mapEffectSound[id].callback){
	 mapEffectSound[id].callback(id, mapEffectSound[id].path);
	}
	}catch(const std::out_of_range& oor){
      printf("AudioEngineImpl::onSoundFinished: invalid audioID: %d\n", id);
  }
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
	FMOD::Sound * sound = NULL; 
	FMOD_RESULT result = pSystem->createSound(fullPath.c_str(), FMOD_LOOP_NORMAL, 0, &sound);
    if (ERRCHECK(result)){
      printf("sound effect in %s could not be preload\n", filePath.c_str());
      return -1;
    }
    id = mapEffectSound.size() + 1;
	auto& audioRef = mapEffectSound[id];
	audioRef.sound = sound; 
	audioRef.id = (size_t) id; 
	audioRef.channel = nullptr; 
	audioRef.path = filePath;
	audioRef.callback = nullptr; 
    //we are going to use UserData to store pointer to Channel when playing
    audioRef.sound->setUserData((void *)id);
  }
  return id; 
};

    
void AudioEngineImpl::update(float dt){
  pSystem->update();
};

int AudioEngineImpl::find(const std::string &path){
  std::string fullPath = FileUtils::getInstance()->fullPathForFilename(path);  
  for (auto it = mapEffectSound.cbegin(); it != mapEffectSound.cend(); ++it) {
    if(it->second.path == path)
	{
	  return it->first; 
    }
  }
  return -1; 
}


FMOD::Channel * AudioEngineImpl::getChannel(FMOD::Sound *sound){
  size_t id; 
  void * data;
  sound->getUserData(&data);
  id = (size_t) data; 
  return mapEffectSound[id].channel; 
};
