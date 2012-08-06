#include "OpenSLEngine.h"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,"OPENSL_ENGINE.CPP", __VA_ARGS__)

using namespace std;


OpenSLEngine::OpenSLEngine()
 :m_musicVolume(0),
  m_effectVolume(0)
{}

OpenSLEngine::~OpenSLEngine()
{
	closeEngine();
}

/**********************************************************************************
 *   jni
 **********************************************************************************/
#define  CLASS_NAME "org/cocos2dx/lib/Cocos2dxActivity"

typedef struct JniMethodInfo_
{
	JNIEnv *    env;
	jclass      classID;
	jmethodID   methodID;
} JniMethodInfo;

extern "C" {
	static JNIEnv* getJNIEnv(void)
	{

		JavaVM* jvm = cocos2d::JniHelper::getJavaVM();
		if (NULL == jvm) {
			LOGD("Failed to get JNIEnv. JniHelper::getJavaVM() is NULL");
			return NULL;
		}

		JNIEnv *env = NULL;
		// get jni environment
		jint ret = jvm->GetEnv((void**)&env, JNI_VERSION_1_4);

		switch (ret) {
		case JNI_OK :
			// Success!
			return env;

		case JNI_EDETACHED :
			// Thread not attached

			// TODO : If calling AttachCurrentThread() on a native thread
			// must call DetachCurrentThread() in future.
			// see: http://developer.android.com/guide/practices/design/jni.html

			if (jvm->AttachCurrentThread(&env, NULL) < 0)
			{
				LOGD("Failed to get the environment using AttachCurrentThread()");
				return NULL;
			} else {
				// Success : Attached and obtained JNIEnv!
				return env;
			}

		case JNI_EVERSION :
			// Cannot recover from this error
			LOGD("JNI interface version 1.4 not supported");
		default :
			LOGD("Failed to get the environment using GetEnv()");
			return NULL;
		}
	}

	static jclass getClassID(JNIEnv *pEnv)
	{
		jclass ret = pEnv->FindClass(CLASS_NAME);
		if (! ret)
		{
			LOGD("Failed to find class of %s", CLASS_NAME);
		}

		return ret;
	}

	static bool getStaticMethodInfo(JniMethodInfo &methodinfo, const char *methodName, const char *paramCode)
	{
		jmethodID methodID = 0;
		JNIEnv *pEnv = 0;
		bool bRet = false;

		do 
		{
			pEnv = getJNIEnv();
			if (! pEnv)
			{
				break;
			}

			jclass classID = getClassID(pEnv);

			methodID = pEnv->GetStaticMethodID(classID, methodName, paramCode);
			if (! methodID)
			{
				LOGD("Failed to find static method id of %s", methodName);
				break;
			}

			methodinfo.classID = classID;
			methodinfo.env = pEnv;
			methodinfo.methodID = methodID;

			bRet = true;
		} while (0);

		return bRet;
	}
};


/*********************************************************************************
 *   helper
 ********************************************************************************/
#define PLAYSTATE_UNKNOWN 0
#define FILE_NOT_FOUND -1

#define ASSET_MANAGER_GETTER "getAssetManager"

#define MIN_VOLUME_MILLIBEL -4000
#define MAX_VOLUME_MILLIBEL 0
#define RANGE_VOLUME_MILLIBEL 4000

struct AudioPlayer
{
	SLDataSource audioSrc;
	SLObjectItf fdPlayerObject;
	SLPlayItf fdPlayerPlay;
	SLSeekItf fdPlayerSeek;
	SLVolumeItf fdPlayerVolume;
} musicPlayer; /* for background music */

typedef map<unsigned int, vector<AudioPlayer*>* > EffectList;
typedef pair<unsigned int, vector<AudioPlayer*>* > Effect;

static EffectList& sharedList()
{
	static EffectList s_List;
	return s_List;
}

unsigned int _Hash(const char *key)
{
	unsigned int len = strlen(key);
	const char *end=key+len;
	unsigned int hash;

	for (hash = 0; key < end; key++)
	{
		hash *= 16777619;
		hash ^= (unsigned int) (unsigned char) toupper(*key);
	}
	return (hash);
}

int getFileDescriptor(const char * filename, off_t & start, off_t & length)
{
	JniMethodInfo methodInfo;
	if (! getStaticMethodInfo(methodInfo, ASSET_MANAGER_GETTER, "()Landroid/content/res/AssetManager;"))
	{
		return FILE_NOT_FOUND;
	}
	jobject assetManager = methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);

	AAssetManager* mgr = AAssetManager_fromJava(methodInfo.env, assetManager);
	assert(NULL != mgr);

	AAsset* Asset = AAssetManager_open(mgr, filename, AASSET_MODE_UNKNOWN);
	if (NULL == Asset)
	{
		LOGD("file not found! Stop preload file: %s", filename);
		return FILE_NOT_FOUND;
	}

	// open asset as file descriptor
	int fd = AAsset_openFileDescriptor(Asset, &start, &length);
	assert(0 <= fd);
	AAsset_close(Asset);

	return fd;
}


/**********************************************************************************
 *   engine
 **********************************************************************************/
static SLObjectItf s_pEngineObject = NULL;
static SLEngineItf s_pEngineEngine = NULL;
static SLObjectItf s_pOutputMixObject = NULL;

bool createAudioPlayerBySource(AudioPlayer* player)
{
	// configure audio sink
	SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, s_pOutputMixObject};
	SLDataSink audioSnk = {&loc_outmix, NULL};

	// create audio player
	const SLInterfaceID ids[3] = {SL_IID_SEEK, SL_IID_MUTESOLO, SL_IID_VOLUME};
	const SLboolean req[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
	SLresult result = (*s_pEngineEngine)->CreateAudioPlayer(s_pEngineEngine, &(player->fdPlayerObject), &(player->audioSrc), &audioSnk, 3, ids, req);
	if (SL_RESULT_MEMORY_FAILURE == result)
	{
		return false;
	}

	// realize the player
	result = (*(player->fdPlayerObject))->Realize(player->fdPlayerObject, SL_BOOLEAN_FALSE);
	assert(SL_RESULT_SUCCESS == result);

	// get the play interface
	result = (*(player->fdPlayerObject))->GetInterface(player->fdPlayerObject, SL_IID_PLAY, &(player->fdPlayerPlay));
	assert(SL_RESULT_SUCCESS == result);

	// get the volume interface
	result = (*(player->fdPlayerObject))->GetInterface(player->fdPlayerObject, SL_IID_VOLUME, &(player->fdPlayerVolume));
	assert(SL_RESULT_SUCCESS == result);

	// get the seek interface
	result = (*(player->fdPlayerObject))->GetInterface(player->fdPlayerObject, SL_IID_SEEK, &(player->fdPlayerSeek));
	assert(SL_RESULT_SUCCESS == result);

	return true;
}

bool initAudioPlayer(AudioPlayer* player, const char* filename) 
{
	// configure audio source
	off_t start, length;
	int fd = getFileDescriptor(filename, start, length);
	if (FILE_NOT_FOUND == fd)
	{
		return false;
	}
	SLDataLocator_AndroidFD loc_fd = {SL_DATALOCATOR_ANDROIDFD, fd, start, length};
	SLDataFormat_MIME format_mime = {SL_DATAFORMAT_MIME, NULL, SL_CONTAINERTYPE_UNSPECIFIED};
	(player->audioSrc) = {&loc_fd, &format_mime};

	return createAudioPlayerBySource(player);
}

void destroyAudioPlayer(AudioPlayer * player)
{
	if (player && player->fdPlayerObject != NULL)
	{
		SLresult result;
		result = (*(player->fdPlayerPlay))->SetPlayState(player->fdPlayerPlay, SL_PLAYSTATE_STOPPED);
		assert(SL_RESULT_SUCCESS == result);

		(*(player->fdPlayerObject))->Destroy(player->fdPlayerObject);
		player->fdPlayerObject = NULL;
		player->fdPlayerPlay = NULL;
		player->fdPlayerSeek = NULL;
		player->fdPlayerVolume = NULL;
	}
}

void OpenSLEngine::createEngine()
{
	SLresult result;
	if (s_pEngineObject == NULL)
	{
		// create engine
		result = slCreateEngine(&s_pEngineObject, 0, NULL, 0, NULL, NULL);
		assert(SL_RESULT_SUCCESS == result);

		// realize the engine
		result = (*s_pEngineObject)->Realize(s_pEngineObject, SL_BOOLEAN_FALSE);
		assert(SL_RESULT_SUCCESS == result);

		// get the engine interface, which is needed in order to create other objects
		result = (*s_pEngineObject)->GetInterface(s_pEngineObject, SL_IID_ENGINE, &s_pEngineEngine);
		assert(SL_RESULT_SUCCESS == result);

		// create output mix
		const SLInterfaceID ids[1] = {SL_IID_ENVIRONMENTALREVERB};
		const SLboolean req[1] = {SL_BOOLEAN_FALSE};
		result = (*s_pEngineEngine)->CreateOutputMix(s_pEngineEngine, &s_pOutputMixObject, 1, ids, req);
		assert(SL_RESULT_SUCCESS == result);

		// realize the output mix object in sync. mode
		result = (*s_pOutputMixObject)->Realize(s_pOutputMixObject, SL_BOOLEAN_FALSE);
		assert(SL_RESULT_SUCCESS == result);
	}
}

void OpenSLEngine::closeEngine()
{
	// destroy background players
	destroyAudioPlayer(&musicPlayer);

	// destroy effect players
	vector<AudioPlayer*>* vec;
	EffectList::iterator p = sharedList().begin();
	while (p != sharedList().end())
	{
		vec = p->second;
		for (vector<AudioPlayer*>::iterator iter = vec->begin() ; iter != vec->end() ; ++ iter)
		{
			destroyAudioPlayer(*iter);
		}
		vec->clear();
		p++;
	}
	sharedList().clear();

	// destroy output mix interface
	if (s_pOutputMixObject)
	{
		(*s_pOutputMixObject)->Destroy(s_pOutputMixObject);
		s_pOutputMixObject = NULL;
	}

	// destroy opensl engine
	if (s_pEngineObject)
	{
		(*s_pEngineObject)->Destroy(s_pEngineObject);
		s_pEngineObject = NULL;
		s_pEngineEngine = NULL;
	}

	LOGD("engine destory");
}


/**********************************************************************************
 *   background music
 **********************************************************************************/
bool OpenSLEngine::preloadBackgroundMusic(const char * filename)
{
	if (musicPlayer.fdPlayerPlay != NULL)
	{
		SLresult result = (*(musicPlayer.fdPlayerPlay))->SetPlayState(musicPlayer.fdPlayerPlay, SL_PLAYSTATE_STOPPED);
		assert(SL_RESULT_SUCCESS == result);
	}

	return initAudioPlayer(&musicPlayer, filename);
}

void OpenSLEngine::setBackgroundMusicState(int state)
{
	SLresult result;
	if (NULL != musicPlayer.fdPlayerPlay)
	{
		result = (*(musicPlayer.fdPlayerPlay))->SetPlayState(musicPlayer.fdPlayerPlay, state);
		assert(SL_RESULT_SUCCESS == result);
	}
}

int OpenSLEngine::getBackgroundMusicState()
{
	SLresult result;
	SLuint32 state;
	if (musicPlayer.fdPlayerPlay != NULL)
	{
		result = (*(musicPlayer.fdPlayerPlay))->GetPlayState(musicPlayer.fdPlayerPlay, &state);
		assert(result == SL_RESULT_SUCCESS);
	}

	return (int)state;
}

void OpenSLEngine::rewindBackgroundMusic()
{
	SLresult result;

	result = (*(musicPlayer.fdPlayerSeek))->SetPosition(musicPlayer.fdPlayerSeek, 0, SL_SEEKMODE_FAST);
	assert(SL_RESULT_SUCCESS == result);

	result = (*(musicPlayer.fdPlayerPlay))->SetPlayState(musicPlayer.fdPlayerPlay, SL_PLAYSTATE_PLAYING);
	assert(SL_RESULT_SUCCESS == result);
}

void OpenSLEngine::setBackgroundMusicLooping(bool isLooping)
{
    SLresult result;
    if (NULL != musicPlayer.fdPlayerSeek) 
	{
        result = (*(musicPlayer.fdPlayerSeek))->SetLoop(musicPlayer.fdPlayerSeek, (SLboolean) isLooping, 0, SL_TIME_UNKNOWN);
        assert(SL_RESULT_SUCCESS == result);
    }
}

void OpenSLEngine::setBackgroundVolume(int volume)
{
	m_musicVolume = volume;

    SLresult result;
    if (NULL != musicPlayer.fdPlayerVolume)
	{
        result = (*(musicPlayer.fdPlayerVolume))->SetVolumeLevel(musicPlayer.fdPlayerVolume, m_musicVolume);
        assert(SL_RESULT_SUCCESS == result);
    }
}

int OpenSLEngine::getBackgroundVolume()
{
	return m_musicVolume;
}


/**********************************************************************************
 *   sound effect
 **********************************************************************************/
typedef struct _CallbackContext
{
	vector<AudioPlayer*>* vec;
	AudioPlayer* player;
} CallbackContext;

void PlayOverEvent(SLPlayItf caller, void* pContext, SLuint32 playEvent)
{
	CallbackContext* context = (CallbackContext*)pContext;
	if (playEvent == SL_PLAYEVENT_HEADATEND)
	{
		vector<AudioPlayer*>::iterator iter;
		for (iter = (context->vec)->begin() ; iter != (context->vec)->end() ; ++ iter)
		{
			if (*iter == context->player)
			{
				(context->vec)->erase(iter);
				break;
			}
		}
		destroyAudioPlayer(context->player);
		free(context);
	}
}

void setSingleEffectVolume(AudioPlayer* player, SLmillibel volume)
{
	SLresult result;
	result = (*(player->fdPlayerVolume))->SetVolumeLevel(player->fdPlayerVolume, volume);
	assert(result == SL_RESULT_SUCCESS);
}

int getSingleEffectState(AudioPlayer * player)
{
	SLuint32 state = 0;
	SLresult result;
	result = (*(player->fdPlayerPlay))->GetPlayState(player->fdPlayerPlay, &state);
	assert(result == SL_RESULT_SUCCESS);

	return (int)state;
}

void setSingleEffectState(AudioPlayer * player, int state)
{
	SLresult result;
	if (player->fdPlayerPlay != NULL)
	{
		// don't set to PAUSED state if it's already set to STOPPED state
		int oldState = getSingleEffectState(player);
		if (oldState == SL_PLAYSTATE_STOPPED && state == SL_PLAYSTATE_PAUSED)
		{
			return;
		}
		result = (*(player->fdPlayerPlay))->SetPlayState(player->fdPlayerPlay, state);
		assert(SL_RESULT_SUCCESS == result);
	}
}

void resumeSingleEffect(AudioPlayer * player)
{
	int state = getSingleEffectState(player);
	// only resume the effect that has been paused
	if (state == SL_PLAYSTATE_PAUSED)
	{
		setSingleEffectState(player, SL_PLAYSTATE_PLAYING);
	}
}

bool OpenSLEngine::recreatePlayer(const char* filename)
{
	unsigned int effectID = _Hash(filename);
	EffectList::iterator p = sharedList().find(effectID);
	vector<AudioPlayer*>* vec = p->second;
	AudioPlayer* newPlayer = new AudioPlayer();
	if (!initAudioPlayer(newPlayer, filename))
	{
		LOGD("failed to recreate");
		return false;
	}
	vec->push_back(newPlayer);

	// set callback
	SLresult result;
	CallbackContext* context = new CallbackContext();
	context->vec = vec;
	context->player = newPlayer;
	result = (*(newPlayer->fdPlayerPlay))->RegisterCallback(newPlayer->fdPlayerPlay, PlayOverEvent, (void*)context);
	assert(SL_RESULT_SUCCESS == result);

	result = (*(newPlayer->fdPlayerPlay))->SetCallbackEventsMask(newPlayer->fdPlayerPlay, SL_PLAYEVENT_HEADATEND);
	assert(SL_RESULT_SUCCESS == result);

	// set volume 
	setSingleEffectVolume(newPlayer, m_effectVolume);
	setSingleEffectState(newPlayer, SL_PLAYSTATE_STOPPED);
	setSingleEffectState(newPlayer, SL_PLAYSTATE_PLAYING);

	// LOGD("vec count is %d of effectID %d", vec->size(), effectID);
	return true;
}

unsigned int OpenSLEngine::preloadEffect(const char * filename)
{
	unsigned int nID = _Hash(filename);
	// if already exists
	EffectList::iterator p = sharedList().find(nID);
	if (p != sharedList().end())
	{
		return nID;
	}

	AudioPlayer* player = new AudioPlayer();
	if (!initAudioPlayer(player, filename))
	{
		free(player);
		return FILE_NOT_FOUND;
	}
	
	// set the new player's volume as others'
	setSingleEffectVolume(player, m_effectVolume);

	vector<AudioPlayer*>* vec = new vector<AudioPlayer*>;
	vec->push_back(player);
	sharedList().insert(Effect(nID, vec));
	return nID;
}

void OpenSLEngine::unloadEffect(const char * filename)
{
	unsigned int nID = _Hash(filename);

	EffectList::iterator p = sharedList().find(nID);
	if (p != sharedList().end())
	{
		vector<AudioPlayer*>* vec = p->second;
		for (vector<AudioPlayer*>::iterator iter = vec->begin() ; iter != vec->end() ; ++ iter)
		{
			destroyAudioPlayer(*iter);
		}
		vec->clear();
		sharedList().erase(nID);
	}
}

int OpenSLEngine::getEffectState(unsigned int effectID)
{
	int state = PLAYSTATE_UNKNOWN;
	EffectList::iterator p = sharedList().find(effectID);
	if (p != sharedList().end())
	{
		vector<AudioPlayer*>* vec = p->second;
		// get the last player's state
		vector<AudioPlayer*>::reverse_iterator r_iter = vec->rbegin();
		state = getSingleEffectState(*r_iter);
	}
	return state;
}

void OpenSLEngine::setEffectState(unsigned int effectID, int state, bool isClear)
{
	EffectList::iterator p = sharedList().find(effectID);
	if (p != sharedList().end())
	{
		vector<AudioPlayer*>* vec = p->second;
		if (state == SL_PLAYSTATE_STOPPED || state == SL_PLAYSTATE_PAUSED)
		{
			// if stopped, clear the recreated players which are unused
			if (isClear)
			{
				setSingleEffectState(*(vec->begin()), state);
				vector<AudioPlayer*>::reverse_iterator r_iter = vec->rbegin();
				for (int i = 1, size = vec->size() ; i < size ; ++ i)
				{
					destroyAudioPlayer(*r_iter);
					r_iter ++;
					vec->pop_back();
				}
			}
			else
			{
				vector<AudioPlayer*>::iterator iter;
				for (iter = vec->begin() ; iter != vec->end() ; ++ iter)
				{
					setSingleEffectState(*iter, state);
				}
			}
		}
		else
		{
			setSingleEffectState(*(vec->rbegin()), state);
		}
	}
}

void OpenSLEngine::setAllEffectState(int state)
{
	EffectList::iterator p;
	for (p = sharedList().begin(); p != sharedList().end(); p ++)
	{
		vector<AudioPlayer*>* vec = p->second;
		for (vector<AudioPlayer*>::iterator iter = vec->begin() ; iter != vec->end() ; ++ iter)
		{
			setSingleEffectState(*iter, state);
		}
	}
}

void OpenSLEngine::resumeEffect(unsigned int effectID)
{
	EffectList::iterator p = sharedList().find(effectID);
	if (p != sharedList().end())
	{
		vector<AudioPlayer*>* vec = p->second;
		for (vector<AudioPlayer*>::iterator iter = vec->begin() ; iter != vec->end() ; ++ iter)
		{
			resumeSingleEffect(*iter);
		}
	}
}

void OpenSLEngine::resumeAllEffects()
{
	int state;
	EffectList::iterator p;
	for (p = sharedList().begin(); p != sharedList().end() ; ++ p)
	{
		vector<AudioPlayer*>* vec = p->second;
		for (vector<AudioPlayer*>::iterator iter = vec->begin() ; iter != vec->end() ; ++ iter)
		{
			resumeSingleEffect(*iter);
		}
	}
}

void OpenSLEngine::setEffectLooping(unsigned int effectID, bool isLooping)
{
	SLresult result;
	vector<AudioPlayer*>* vec = sharedList()[effectID];
	assert(NULL != vec);

	// get the first effect player that to be set loop config
	vector<AudioPlayer*>::iterator iter = vec->begin();
	AudioPlayer * player = *iter;

	if (player && player->fdPlayerSeek) 
	{
		result = (*(player->fdPlayerSeek))->SetLoop(player->fdPlayerSeek, (SLboolean) isLooping, 0, SL_TIME_UNKNOWN);
		assert(SL_RESULT_SUCCESS == result);
	}
}

void OpenSLEngine::setEffectsVolume(float volume)
{
	assert(volume <= 1.0f && volume >= 0.0f);
	m_effectVolume = int (RANGE_VOLUME_MILLIBEL * volume) + MIN_VOLUME_MILLIBEL;
	
	SLresult result;
	EffectList::iterator p;
	AudioPlayer * player;
	for (p = sharedList().begin() ; p != sharedList().end() ; ++ p)
	{
		vector<AudioPlayer*>* vec = p->second;
		for (vector<AudioPlayer*>::iterator iter = vec->begin() ; iter != vec->end() ; ++ iter)
		{
			player = *iter;
			result = (*(player->fdPlayerVolume))->SetVolumeLevel(player->fdPlayerVolume, m_effectVolume);
			assert(SL_RESULT_SUCCESS == result);
		}
	}
}

float OpenSLEngine::getEffectsVolume()
{
	float volume = (m_effectVolume - MIN_VOLUME_MILLIBEL) / (1.0f * RANGE_VOLUME_MILLIBEL);
	LOGD("effect volume: %f", volume);
	return volume;
}