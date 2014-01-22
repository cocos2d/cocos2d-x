/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "OpenSLEngine.h"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,"OPENSL_ENGINE.CPP", __VA_ARGS__)

using namespace std;


OpenSLEngine::OpenSLEngine()
 :_musicVolume(0),
  _effectVolume(0)
{}

OpenSLEngine::~OpenSLEngine()
{
	closeEngine();
}

/**********************************************************************************
 *   jni
 **********************************************************************************/
#define  CLASS_NAME "org/cocos2dx/lib/Cocos2dxHelper"

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
#define LIBANDROID "libandroid.so"

#define MIN_VOLUME_MILLIBEL -4000
#define MAX_VOLUME_MILLIBEL 0
#define RANGE_VOLUME_MILLIBEL 4000

class AudioPlayer
{
public:
	SLDataSource audioSrc;
	SLObjectItf fdPlayerObject;
	SLPlayItf fdPlayerPlay;
	SLSeekItf fdPlayerSeek;
    SLVolumeItf fdPlayerVolume;
    SLPlaybackRateItf fdPlaybackRate;

    /// Applies global effects volume, takes effect gain into account.
    /// @param volume In range 0..1.
    void applyEffectsVolume(float volume)
    {
        SLmillibel finalVolume = int (RANGE_VOLUME_MILLIBEL * (volume * _gain)) + MIN_VOLUME_MILLIBEL;
        SLresult result = (*fdPlayerVolume)->SetVolumeLevel(fdPlayerVolume, finalVolume);
        assert(SL_RESULT_SUCCESS == result);
    }

    void applyParameters(bool isLooping, float pitch, float pan, float gain, float effectsVolume)
    {
        SLresult result = (*fdPlayerSeek)->SetLoop(fdPlayerSeek, (SLboolean) isLooping, 0, SL_TIME_UNKNOWN);
        assert(SL_RESULT_SUCCESS == result);

        SLpermille stereo = SLpermille(1000 * pan);
        result = (*fdPlayerVolume)->EnableStereoPosition(fdPlayerVolume, SL_BOOLEAN_TRUE);
        assert(SL_RESULT_SUCCESS == result);
        result = (*fdPlayerVolume)->SetStereoPosition(fdPlayerVolume, stereo);
        assert(SL_RESULT_SUCCESS == result);

        SLpermille playbackRate = SLpermille(1000 * pitch);
        if (fdPlaybackRate)
            result = (*fdPlaybackRate)->SetRate(fdPlaybackRate, playbackRate);
        assert(SL_RESULT_SUCCESS == result);

        _gain = gain;
        applyEffectsVolume(effectsVolume);
    }

private:
    float _gain;
};

static AudioPlayer s_musicPlayer; /* for background music */

typedef map<unsigned int, vector<AudioPlayer*>* > EffectList;
typedef pair<unsigned int, vector<AudioPlayer*>* > Effect;

void* s_pAndroidHandle  = NULL;
void* s_pOpenSLESHandle = NULL;

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

SLInterfaceID getInterfaceID(const char *value)
{
	// clear the error stack
	dlerror();
	SLInterfaceID* IID = (SLInterfaceID*)dlsym(s_pOpenSLESHandle, value);
	const char* errorInfo = dlerror();
	if (errorInfo)
	{
		LOGD("Get interface id: %s from OpenSL failed", errorInfo);
		IID = NULL;
	}
	return *IID;
}

void* getFuncPtr(const char *value)
{
	// clear the error stack
	dlerror();
	void* funcPtr = dlsym(s_pOpenSLESHandle, value);
	const char* errorInfo = dlerror();
	if (errorInfo)
	{
		LOGD("Get function from OpenSL failed: %s", errorInfo);
		funcPtr = NULL;
	}
	return funcPtr;
}

int getFileDescriptor(const char * filename, off_t & start, off_t & length)
{
	JniMethodInfo methodInfo;
	if (! getStaticMethodInfo(methodInfo, ASSET_MANAGER_GETTER, "()Landroid/content/res/AssetManager;"))
	{
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
		return FILE_NOT_FOUND;
	}
	jobject assetManager = methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);

	AAssetManager* (*AAssetManager_fromJava)(JNIEnv* env, jobject assetManager);
	AAssetManager_fromJava = (AAssetManager* (*)(JNIEnv* env, jobject assetManager))
		dlsym(s_pAndroidHandle, "AAssetManager_fromJava");
	AAssetManager* mgr = AAssetManager_fromJava(methodInfo.env, assetManager);
	assert(NULL != mgr);

	AAsset* (*AAssetManager_open)(AAssetManager* mgr, const char* filename, int mode);
	AAssetManager_open = (AAsset* (*)(AAssetManager* mgr, const char* filename, int mode))
		dlsym(s_pAndroidHandle, "AAssetManager_open");
	AAsset* Asset = AAssetManager_open(mgr, filename, AASSET_MODE_UNKNOWN);
	if (NULL == Asset)
	{
		//LOGD("file not found! Stop preload file: %s", filename);
		return FILE_NOT_FOUND;
	}

	// open asset as file descriptor
	int (*AAsset_openFileDescriptor)(AAsset* asset, off_t* outStart, off_t* outLength);
	AAsset_openFileDescriptor = (int (*)(AAsset* asset, off_t* outStart, off_t* outLength))
		dlsym(s_pAndroidHandle, "AAsset_openFileDescriptor");
	int fd = AAsset_openFileDescriptor(Asset, &start, &length);
	assert(0 <= fd);

	void (*AAsset_close)(AAsset* asset);
	AAsset_close = (void (*)(AAsset* asset))
		dlsym(s_pAndroidHandle, "AAsset_close");
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
	const SLInterfaceID ids[3] = {
		getInterfaceID("SL_IID_SEEK"), getInterfaceID("SL_IID_MUTESOLO"), getInterfaceID("SL_IID_VOLUME")};
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
	result = (*(player->fdPlayerObject))->GetInterface(player->fdPlayerObject, getInterfaceID("SL_IID_PLAY"), &(player->fdPlayerPlay));
	assert(SL_RESULT_SUCCESS == result);

	// get the volume interface
	result = (*(player->fdPlayerObject))->GetInterface(player->fdPlayerObject, getInterfaceID("SL_IID_VOLUME"), &(player->fdPlayerVolume));
	assert(SL_RESULT_SUCCESS == result);

	// get the seek interface
	result = (*(player->fdPlayerObject))->GetInterface(player->fdPlayerObject, getInterfaceID("SL_IID_SEEK"), &(player->fdPlayerSeek));
	assert(SL_RESULT_SUCCESS == result);

    // get the playback rate interface, if available
    (*(player->fdPlayerObject))->GetInterface(player->fdPlayerObject, getInterfaceID("SL_IID_PLAYBACKRATE"), &(player->fdPlaybackRate));

	return true;
}

bool initAudioPlayer(AudioPlayer* player, const char* filename) 
{
	// configure audio source
	off_t start, length;
	int fd = getFileDescriptor(filename, start, length);
	if (FILE_NOT_FOUND == fd)
	{
		FILE* fp = fopen(filename , "rb");
		if(fp){
			SLDataLocator_URI loc_fd = {SL_DATALOCATOR_URI , (SLchar*)filename};
			SLDataFormat_MIME format_mime = {SL_DATAFORMAT_MIME, NULL, SL_CONTAINERTYPE_UNSPECIFIED};
			player->audioSrc.pLocator = &loc_fd;
			player->audioSrc.pFormat = &format_mime;
			return createAudioPlayerBySource(player);
		}
		LOGD("file not found! Stop preload file: %s", filename);
		return false;
	}
	SLDataLocator_AndroidFD loc_fd = {SL_DATALOCATOR_ANDROIDFD, fd, start, length};
	SLDataFormat_MIME format_mime = {SL_DATAFORMAT_MIME, NULL, SL_CONTAINERTYPE_UNSPECIFIED};
	player->audioSrc.pLocator = &loc_fd;
	player->audioSrc.pFormat = &format_mime;

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
        player->fdPlaybackRate = NULL;
	}
}

void OpenSLEngine::createEngine(void* pHandle)
{
	assert(pHandle != NULL);
	s_pOpenSLESHandle = pHandle;

	// clear the error stack
	dlerror();
	s_pAndroidHandle = dlopen(LIBANDROID, RTLD_LAZY);
	const char* errorInfo = dlerror();
	if (errorInfo)
	{
		LOGD("%s", errorInfo);
		return;
	}

	SLresult result;
	if (s_pEngineObject == NULL)
	{
		// create engine
		SLresult (*slCreateEngine)(SLObjectItf *pEngine, SLuint32 numOptions, const SLEngineOption *pEngineOptions, SLuint32 numInterfaces, const SLInterfaceID *pInterfaceIds, const SLboolean * pInterfaceRequired );
		slCreateEngine = (SLresult (*)(SLObjectItf *pEngine, SLuint32 numOptions, const SLEngineOption *pEngineOptions, SLuint32 numInterfaces, const SLInterfaceID *pInterfaceIds, const SLboolean * pInterfaceRequired ))
			getFuncPtr("slCreateEngine");
		result = slCreateEngine(&s_pEngineObject, 0, NULL, 0, NULL, NULL);
		assert(SL_RESULT_SUCCESS == result);

		// realize the engine
		result = (*s_pEngineObject)->Realize(s_pEngineObject, SL_BOOLEAN_FALSE);
		assert(SL_RESULT_SUCCESS == result);

		// get the engine interface, which is needed in order to create other objects
		result = (*s_pEngineObject)->GetInterface(s_pEngineObject, getInterfaceID("SL_IID_ENGINE"), &s_pEngineEngine);
		assert(SL_RESULT_SUCCESS == result);

		// create output mix
		const SLInterfaceID ids[1] = {getInterfaceID("SL_IID_ENVIRONMENTALREVERB")};
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
    destroyAudioPlayer(&s_musicPlayer);

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
    newPlayer->applyEffectsVolume(_effectVolume);
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
    player->applyEffectsVolume(_effectVolume);

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

void OpenSLEngine::setEffectParameters(unsigned int effectID, bool isLooping,
                                       float pitch, float pan, float gain)
{
	vector<AudioPlayer*>* vec = sharedList()[effectID];
	assert(NULL != vec);

	// get the first effect player that to be set loop config
	vector<AudioPlayer*>::iterator iter = vec->begin();
	AudioPlayer * player = *iter;

	if (player && player->fdPlayerSeek) 
	{
        player->applyParameters(isLooping, pitch, pan, gain, _effectVolume);
	}
}

void OpenSLEngine::setEffectsVolume(float volume)
{
	assert(volume <= 1.0f && volume >= 0.0f);
    _effectVolume = volume;

	EffectList::iterator p;
	AudioPlayer * player;
	for (p = sharedList().begin() ; p != sharedList().end() ; ++ p)
	{
		vector<AudioPlayer*>* vec = p->second;
		for (vector<AudioPlayer*>::iterator iter = vec->begin() ; iter != vec->end() ; ++ iter)
		{
			player = *iter;
            player->applyEffectsVolume(_effectVolume);
		}
	}
}

float OpenSLEngine::getEffectsVolume()
{
	float volume = (_effectVolume - MIN_VOLUME_MILLIBEL) / (1.0f * RANGE_VOLUME_MILLIBEL);
	return volume;
}
