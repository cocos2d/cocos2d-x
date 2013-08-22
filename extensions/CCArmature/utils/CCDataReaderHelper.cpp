/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

#include "support/tinyxml2/tinyxml2.h"
#include "CCDataReaderHelper.h"
#include "CCArmatureDataManager.h"
#include "CCTransformHelp.h"
#include "CCUtilMath.h"
#include "CCArmatureDefine.h"
#include "../datas/CCDatas.h"
#include <errno.h>
#include <stack>
#include <string>
#include <cctype>
#include <queue>
#include <list>
#include <pthread.h>

static const char *VERSION = "version";
static const float VERSION_2_0 = 2.0f;

static const char *ARMATURES = "armatures";
static const char *ARMATURE = "armature";
static const char *BONE = "b";
static const char *DISPLAY = "d";

static const char *ANIMATIONS = "animations";
static const char *ANIMATION = "animation";
static const char *MOVEMENT = "mov";
static const char *FRAME = "f";

static const char *TEXTURE_ATLAS = "TextureAtlas";
static const char *SUB_TEXTURE = "SubTexture";

static const char *A_NAME = "name";
static const char *A_DURATION = "dr";
static const char *A_FRAME_INDEX = "fi";
static const char *A_DURATION_TO = "to";
static const char *A_DURATION_TWEEN = "drTW";
static const char *A_LOOP = "lp";
static const char *A_MOVEMENT_SCALE = "sc";
static const char *A_MOVEMENT_DELAY = "dl";
static const char *A_DISPLAY_INDEX = "dI";

static const char *A_VERT = "vert";
static const char *A_FRAG = "frag";
static const char *A_PLIST = "plist";

static const char *A_PARENT = "parent";
static const char *A_SKEW_X = "kX";
static const char *A_SKEW_Y = "kY";
static const char *A_SCALE_X = "cX";
static const char *A_SCALE_Y = "cY";
static const char *A_Z = "z";
static const char *A_EVENT = "evt";
static const char *A_SOUND = "sd";
static const char *A_SOUND_EFFECT = "sdE";
static const char *A_TWEEN_EASING = "twE";
//static const char *A_TWEEN_ROTATE = "twR";
static const char *A_IS_ARMATURE = "isArmature";
static const char *A_DISPLAY_TYPE = "displayType";
static const char *A_MOVEMENT = "mov";

static const char *A_X = "x";
static const char *A_Y = "y";

static const char *A_COCOS2DX_X = "cocos2d_x";
static const char *A_COCOS2DX_Y = "cocos2d_y";

static const char *A_WIDTH = "width";
static const char *A_HEIGHT = "height";
static const char *A_PIVOT_X = "pX";
static const char *A_PIVOT_Y = "pY";

static const char *A_COCOS2D_PIVOT_X = "cocos2d_pX";
static const char *A_COCOS2D_PIVOT_Y = "cocos2d_pY";

static const char *A_BLEND_TYPE = "bd";

static const char *A_ALPHA = "a";
static const char *A_RED = "r";
static const char *A_GREEN = "g";
static const char *A_BLUE = "b";
static const char *A_ALPHA_OFFSET = "aM";
static const char *A_RED_OFFSET = "rM";
static const char *A_GREEN_OFFSET = "gM";
static const char *A_BLUE_OFFSET = "bM";
static const char *A_COLOR_TRANSFORM = "colorTransform";
//static const char *A_ROTATION = "rotation";
//static const char *A_USE_COLOR_INFO = "uci";



static const char *CONTOUR = "con";
static const char *CONTOUR_VERTEX = "con_vt";

//static const char *MOVEMENT_EVENT_FRAME = "movementEventFrame";
//static const char *SOUND_FRAME = "soundFrame";


static const char *FL_NAN = "NaN";


static const char *FRAME_DATA = "frame_data";
static const char *MOVEMENT_BONE_DATA = "mov_bone_data";
static const char *MOVEMENT_DATA = "mov_data";
static const char *ANIMATION_DATA = "animation_data";
static const char *DISPLAY_DATA = "display_data";
static const char *SKIN_DATA = "skin_data";
static const char *BONE_DATA = "bone_data";
static const char *ARMATURE_DATA = "armature_data";
static const char *CONTOUR_DATA = "contour_data";
static const char *TEXTURE_DATA = "texture_data";
static const char *VERTEX_POINT = "vertex";
static const char *COLOR_INFO = "color";

static const char *CONFIG_FILE_PATH= "config_file_path";


NS_CC_EXT_BEGIN


std::vector<std::string> s_arrConfigFileList;
float s_PositionReadScale = 1;
static float s_FlashToolVersion = VERSION_2_0;
static float s_CocoStudioVersion = VERSION_COMBINED;

static std::string s_BasefilePath = "";

CCDataReaderHelper *CCDataReaderHelper::s_DataReaderHelper = NULL;

enum ConfigType
{
	DragonBone_XML,
	CocoStudio_JSON
};


//! Async load

typedef struct _AsyncStruct
{
	std::string    filename;
	std::string    fileContent;
	ConfigType     configType;
	std::string    baseFilePath;
	CCObject       *target;
	SEL_SCHEDULE   selector;
	bool           autoLoadSpriteFile;
} AsyncStruct;

typedef struct _DataInfo
{
	AsyncStruct *asyncStruct;
	std::queue<std::string>      configFileQueue;
} DataInfo;

static pthread_t s_loadingThread;

static pthread_mutex_t		s_SleepMutex;
static pthread_cond_t		s_SleepCondition;

static pthread_mutex_t      s_asyncStructQueueMutex;
static pthread_mutex_t      s_DataInfoMutex;

static pthread_mutex_t      s_addDataMutex;
static pthread_mutex_t      s_ReadFileMutex;

#ifdef EMSCRIPTEN
// Hack to get ASM.JS validation (no undefined symbols allowed).
#define pthread_cond_signal(_)
#endif // EMSCRIPTEN

static unsigned long s_nAsyncRefCount = 0;
static unsigned long s_nAsyncRefTotalCount = 0;

static bool need_quit = false;

static std::queue<AsyncStruct*>* s_pAsyncStructQueue = NULL;
static std::queue<DataInfo*>*   s_pDataQueue = NULL;

static void *loadData(void *)
{
	AsyncStruct *pAsyncStruct = NULL;

	while (true)
	{
		// create autorelease pool for iOS
		CCThread thread;
		thread.createAutoreleasePool();

		std::queue<AsyncStruct*> *pQueue = s_pAsyncStructQueue;
		pthread_mutex_lock(&s_asyncStructQueueMutex);// get async struct from queue
		if (pQueue->empty())
		{
			pthread_mutex_unlock(&s_asyncStructQueueMutex);
			if (need_quit) {
				break;
			}
			else {
				pthread_cond_wait(&s_SleepCondition, &s_SleepMutex);
				continue;
			}
		}
		else
		{
			pAsyncStruct = pQueue->front();
			pQueue->pop();
			pthread_mutex_unlock(&s_asyncStructQueueMutex);
		}        

		// generate image info
		DataInfo *pDataInfo = new DataInfo();
		pDataInfo->asyncStruct = pAsyncStruct;

		if (pAsyncStruct->configType == DragonBone_XML)
		{
			CCDataReaderHelper::addDataFromCache(pAsyncStruct->fileContent.c_str(), pDataInfo);
		}
		else if(pAsyncStruct->configType == CocoStudio_JSON)
		{
			CCDataReaderHelper::addDataFromJsonCache(pAsyncStruct->fileContent.c_str(), pDataInfo);
		}

		// put the image info into the queue
		pthread_mutex_lock(&s_DataInfoMutex);
		s_pDataQueue->push(pDataInfo);
		pthread_mutex_unlock(&s_DataInfoMutex);    
	}

	if( s_pAsyncStructQueue != NULL )
	{
		delete s_pAsyncStructQueue;
		s_pAsyncStructQueue = NULL;
		delete s_pDataQueue;
		s_pDataQueue = NULL;

		pthread_mutex_destroy(&s_asyncStructQueueMutex);
		pthread_mutex_destroy(&s_DataInfoMutex);
		pthread_mutex_destroy(&s_SleepMutex);
		pthread_mutex_destroy(&s_addDataMutex);
		pthread_mutex_destroy(&s_ReadFileMutex);
		pthread_cond_destroy(&s_SleepCondition);
	}

	return NULL;
}


CCDataReaderHelper *CCDataReaderHelper::sharedDataReaderHelper()
{
	if(!s_DataReaderHelper)
	{
		s_DataReaderHelper = new CCDataReaderHelper();
	}

	return s_DataReaderHelper;
}

void CCDataReaderHelper::setPositionReadScale(float scale)
{
	s_PositionReadScale = scale;
}

float CCDataReaderHelper::getPositionReadScale()
{
	return s_PositionReadScale;
}


void CCDataReaderHelper::purge()
{
	CCDataReaderHelper::clear();
	CC_SAFE_RELEASE_NULL(s_DataReaderHelper);
}

void CCDataReaderHelper::clear()
{
	s_arrConfigFileList.clear();
}

CCDataReaderHelper::~CCDataReaderHelper()
{
	need_quit = true;
	pthread_cond_signal(&s_SleepCondition);
}

void CCDataReaderHelper::addDataFromFile(const char *filePath)
{
	/*
	* Check if file is already added to CCArmatureDataManager, if then return.
	*/
	for(unsigned int i = 0; i < s_arrConfigFileList.size(); i++)
	{
		if (s_arrConfigFileList[i].compare(filePath) == 0)
		{
			return;
		}
	}
	s_arrConfigFileList.push_back(filePath);


	//! find the base file path
	s_BasefilePath = filePath;
	size_t pos = s_BasefilePath.find_last_of("/");
	if (pos != std::string::npos)
	{
		s_BasefilePath = s_BasefilePath.substr(0, pos+1);
	}
	else
	{
		s_BasefilePath = "";
	}


	std::string filePathStr =  filePath;
	size_t startPos = filePathStr.find_last_of(".");
	std::string str = &filePathStr[startPos];

	unsigned long size;
	std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(filePath);
	const char *pFileContent = (char *)CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str() , "r", &size);

	if (str.compare(".xml") == 0)
	{
		CCDataReaderHelper::addDataFromCache(pFileContent);
	}
	else if(str.compare(".json") == 0 || str.compare(".ExportJson") == 0)
	{
		CCDataReaderHelper::addDataFromJsonCache(pFileContent);
	}
}

void CCDataReaderHelper::addDataFromFileAsync(const char *filePath, CCObject *target, SEL_SCHEDULE selector)
{
#ifdef EMSCRIPTEN
	CCLOGWARN("Cannot load data %s asynchronously in Emscripten builds.", path);
	return;
#endif // EMSCRIPTEN

	/*
	* Check if file is already added to CCArmatureDataManager, if then return.
	*/
	for(unsigned int i = 0; i < s_arrConfigFileList.size(); i++)
	{
		if (s_arrConfigFileList[i].compare(filePath) == 0)
		{
			if (target && selector)
			{
				if (s_nAsyncRefTotalCount == 0 && s_nAsyncRefCount == 0)
				{
					(target->*selector)(1);
				}
				else
				{
					(target->*selector)((s_nAsyncRefTotalCount - s_nAsyncRefCount) / (float)s_nAsyncRefTotalCount);
				}
			}
			return;
		}
	}
	s_arrConfigFileList.push_back(filePath);

	//! find the base file path
	s_BasefilePath = filePath;
	size_t pos = s_BasefilePath.find_last_of("/");
	if (pos != std::string::npos)
	{
		s_BasefilePath = s_BasefilePath.substr(0, pos+1);
	}
	else
	{
		s_BasefilePath = "";
	}


	// lazy init
	if (s_pAsyncStructQueue == NULL)
	{             
		s_pAsyncStructQueue = new std::queue<AsyncStruct*>();
		s_pDataQueue = new std::queue<DataInfo*>();        

		pthread_mutex_init(&s_asyncStructQueueMutex, NULL);
		pthread_mutex_init(&s_DataInfoMutex, NULL);
		pthread_mutex_init(&s_SleepMutex, NULL);
		pthread_mutex_init(&s_addDataMutex, NULL);
		pthread_mutex_init(&s_ReadFileMutex, NULL);
		pthread_cond_init(&s_SleepCondition, NULL);
		pthread_create(&s_loadingThread, NULL, loadData, NULL);

		need_quit = false;
	}

	if (0 == s_nAsyncRefCount)
	{
		CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(CCDataReaderHelper::addDataAsyncCallBack), this, 0, false);
	}

	++s_nAsyncRefCount;
	++s_nAsyncRefTotalCount;

	if (target)
	{
		target->retain();
	}

	// generate async struct
	AsyncStruct *data = new AsyncStruct();
	data->filename = filePath;
	data->baseFilePath = s_BasefilePath;
	data->target = target;
	data->selector = selector;
	data->autoLoadSpriteFile = CCArmatureDataManager::sharedArmatureDataManager()->isAutoLoadSpriteFile();


	std::string filePathStr =  filePath;
	size_t startPos = filePathStr.find_last_of(".");
	std::string str = &filePathStr[startPos];

	std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(filePath);
	unsigned long size;
	data->fileContent = (char *)CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str() , "r", &size);

	if (str.compare(".xml") == 0)
	{
		data->configType = DragonBone_XML;
	}
	else if(str.compare(".json") == 0 || str.compare(".ExportJson") == 0)
	{
		data->configType = CocoStudio_JSON;
	}


	// add async struct into queue
	pthread_mutex_lock(&s_asyncStructQueueMutex);
	s_pAsyncStructQueue->push(data);
	pthread_mutex_unlock(&s_asyncStructQueueMutex);

	pthread_cond_signal(&s_SleepCondition);
}

void CCDataReaderHelper::addDataAsyncCallBack(float dt)
{
	// the data is generated in loading thread
	std::queue<DataInfo*> *dataQueue = s_pDataQueue;

	pthread_mutex_lock(&s_DataInfoMutex);
	if (dataQueue->empty())
	{
		pthread_mutex_unlock(&s_DataInfoMutex);
	}
	else
	{
		DataInfo *pDataInfo = dataQueue->front();
		dataQueue->pop();
		pthread_mutex_unlock(&s_DataInfoMutex);

		AsyncStruct *pAsyncStruct = pDataInfo->asyncStruct;

		while (!pDataInfo->configFileQueue.empty())
		{
			std::string configPath = pDataInfo->configFileQueue.front();
			CCArmatureDataManager::sharedArmatureDataManager()->addSpriteFrameFromFile((pAsyncStruct->baseFilePath + configPath + ".plist").c_str(), (pAsyncStruct->baseFilePath + configPath + ".png").c_str());
			pDataInfo->configFileQueue.pop();
		}


		CCObject *target = pAsyncStruct->target;
		SEL_SCHEDULE selector = pAsyncStruct->selector;
		const char* filename = pAsyncStruct->filename.c_str();

		--s_nAsyncRefCount;

		if (target && selector)
		{
			(target->*selector)((s_nAsyncRefTotalCount - s_nAsyncRefCount) / (float)s_nAsyncRefTotalCount);
			target->release();
		} 


		delete pAsyncStruct;
		delete pDataInfo;

		if (0 == s_nAsyncRefCount)
		{
			s_nAsyncRefTotalCount = 0;
			CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(CCDataReaderHelper::addDataAsyncCallBack), this);
		}
	}
}






void CCDataReaderHelper::addDataFromCache(const char *pFileContent, DataInfo *dataInfo)
{
	tinyxml2::XMLDocument document;
	document.Parse(pFileContent);

	tinyxml2::XMLElement *root = document.RootElement();
	CCAssert(root, "XML error  or  XML is empty.");

	root->QueryFloatAttribute(VERSION, &s_FlashToolVersion);


	/*
	* Begin decode armature data from xml
	*/
	tinyxml2::XMLElement *armaturesXML = root->FirstChildElement(ARMATURES);
	tinyxml2::XMLElement *armatureXML = armaturesXML->FirstChildElement(ARMATURE);
	while(armatureXML)
	{
		CCArmatureData *armatureData = CCDataReaderHelper::decodeArmature(armatureXML);

		if (dataInfo)
		{
			pthread_mutex_lock(&s_addDataMutex);
		}
		CCArmatureDataManager::sharedArmatureDataManager()->addArmatureData(armatureData->name.c_str(), armatureData);
		armatureData->release();
		if (dataInfo)
		{
			pthread_mutex_unlock(&s_addDataMutex);
		}

		armatureXML = armatureXML->NextSiblingElement(ARMATURE);
	}


	/*
	* Begin decode animation data from xml
	*/
	tinyxml2::XMLElement *animationsXML = root->FirstChildElement(ANIMATIONS);
	tinyxml2::XMLElement *animationXML = animationsXML->FirstChildElement(ANIMATION);
	while(animationXML)
	{
		CCAnimationData *animationData = CCDataReaderHelper::decodeAnimation(animationXML);
		if (dataInfo)
		{
			pthread_mutex_lock(&s_addDataMutex);
		}
		CCArmatureDataManager::sharedArmatureDataManager()->addAnimationData(animationData->name.c_str(), animationData);
		animationData->release();
		if (dataInfo)
		{
			pthread_mutex_unlock(&s_addDataMutex);
		}
		animationXML = animationXML->NextSiblingElement(ANIMATION);
	}


	/*
	* Begin decode texture data from xml
	*/
	tinyxml2::XMLElement *texturesXML = root->FirstChildElement(TEXTURE_ATLAS);
	tinyxml2::XMLElement *textureXML = texturesXML->FirstChildElement(SUB_TEXTURE);
	while(textureXML)
	{
		CCTextureData *textureData = CCDataReaderHelper::decodeTexture(textureXML);

		if (dataInfo)
		{
			pthread_mutex_lock(&s_addDataMutex);
		}
		CCArmatureDataManager::sharedArmatureDataManager()->addTextureData(textureData->name.c_str(), textureData);
		textureData->release();
		if (dataInfo)
		{
			pthread_mutex_unlock(&s_addDataMutex);
		}
		textureXML = textureXML->NextSiblingElement(SUB_TEXTURE);
	}
}

CCArmatureData *CCDataReaderHelper::decodeArmature(tinyxml2::XMLElement *armatureXML)
{
	CCArmatureData *armatureData = new CCArmatureData();
	armatureData->init();

	const char	*name = armatureXML->Attribute(A_NAME);
	armatureData->name = name;


	tinyxml2::XMLElement *boneXML = armatureXML->FirstChildElement(BONE);

	while( boneXML )
	{
		/*
		*  If this bone have parent, then get the parent bone xml
		*/
		const char *parentName = boneXML->Attribute(A_PARENT);
		tinyxml2::XMLElement *parentXML = NULL;
		if (parentName)
		{
			parentXML = armatureXML->FirstChildElement(BONE);
			std::string name = parentName;
			while (parentXML)
			{
				if (name.compare(parentXML->Attribute(A_NAME)) == 0)
				{
					break;
				}
				parentXML = parentXML->NextSiblingElement(BONE);
			}
		}

		CCBoneData *boneData = decodeBone(boneXML, parentXML);
		armatureData->addBoneData(boneData);
		boneData->release();

		boneXML = boneXML->NextSiblingElement(BONE);
	}

	return armatureData;
}

CCBoneData *CCDataReaderHelper::decodeBone(tinyxml2::XMLElement *boneXML, tinyxml2::XMLElement *parentXml)
{
	CCBoneData *boneData = new CCBoneData();
	boneData->init();

	std::string name = boneXML->Attribute(A_NAME);
	boneData->name = name;

	if( boneXML->Attribute(A_PARENT) != NULL )
	{
		boneData->parentName = boneXML->Attribute(A_PARENT);
	}

	boneXML->QueryIntAttribute(A_Z, &boneData->zOrder);

	tinyxml2::XMLElement *displayXML = boneXML->FirstChildElement(DISPLAY);
	while(displayXML)
	{
		CCDisplayData *displayData = decodeBoneDisplay(displayXML);
		boneData->addDisplayData(displayData);
		displayData->release();

		displayXML = displayXML->NextSiblingElement(DISPLAY);
	}

	return boneData;
}

CCDisplayData *CCDataReaderHelper::decodeBoneDisplay(tinyxml2::XMLElement *displayXML)
{
	int _isArmature = 0;

	CCDisplayData *displayData;

	if( displayXML->QueryIntAttribute(A_IS_ARMATURE, &(_isArmature)) == tinyxml2::XML_SUCCESS )
	{
		if(!_isArmature)
		{
			displayData = new CCSpriteDisplayData();
			displayData->displayType  = CS_DISPLAY_SPRITE;
		}
		else
		{
			displayData = new CCArmatureDisplayData();
			displayData->displayType  = CS_DISPLAY_ARMATURE;
		}

	}
	else
	{
		displayData = new CCSpriteDisplayData();
		displayData->displayType  = CS_DISPLAY_SPRITE;
	}


	if(displayXML->Attribute(A_NAME) != NULL )
	{
		if(!_isArmature)
		{
			((CCSpriteDisplayData *)displayData)->displayName = displayXML->Attribute(A_NAME);
		}
		else
		{
			((CCArmatureDisplayData *)displayData)->displayName = displayXML->Attribute(A_NAME);
		}

	}

	return displayData;
}

CCAnimationData *CCDataReaderHelper::decodeAnimation(tinyxml2::XMLElement *animationXML)
{
	CCAnimationData *aniData =  new CCAnimationData();

	const char	*name = animationXML->Attribute(A_NAME);

	CCArmatureData *armatureData = CCArmatureDataManager::sharedArmatureDataManager()->getArmatureData(name);

	aniData->name = name;

	tinyxml2::XMLElement *movementXML = animationXML->FirstChildElement(MOVEMENT);

	while( movementXML )
	{
		CCMovementData *movementData = decodeMovement(movementXML, armatureData);
		aniData->addMovement(movementData);
		movementData->release();

		movementXML = movementXML->NextSiblingElement(MOVEMENT);

	}

	return aniData;
}

CCMovementData *CCDataReaderHelper::decodeMovement(tinyxml2::XMLElement *movementXML, CCArmatureData *armatureData)
{
	CCMovementData *movementData = new CCMovementData();

	const char *movName = movementXML->Attribute(A_NAME);
	movementData->name = movName;


	int duration, durationTo, durationTween, loop, tweenEasing = 0;

	if( movementXML->QueryIntAttribute(A_DURATION, &(duration)) == tinyxml2::XML_SUCCESS)
	{
		movementData->duration  = duration;
	}
	if( movementXML->QueryIntAttribute(A_DURATION_TO, &(durationTo)) == tinyxml2::XML_SUCCESS)
	{
		movementData->durationTo = durationTo;
	}
	if( movementXML->QueryIntAttribute(A_DURATION_TWEEN, &(durationTween)) == tinyxml2::XML_SUCCESS)
	{
		movementData->durationTween = durationTween;
	}
	if( movementXML->QueryIntAttribute(A_LOOP, &(loop)) == tinyxml2::XML_SUCCESS)
	{
		movementData->loop = (bool)loop;
	}

	const char *_easing = movementXML->Attribute(A_TWEEN_EASING);
	if(_easing != NULL)
	{
		std::string str = _easing;
		if(str.compare(FL_NAN) != 0)
		{
			if( movementXML->QueryIntAttribute(A_TWEEN_EASING, &(tweenEasing)) == tinyxml2::XML_SUCCESS)
			{
				movementData->tweenEasing = (CCTweenType)tweenEasing;
			}
		}
		else
		{
			movementData->tweenEasing  = TWEEN_EASING_MAX;
		}
	}

	tinyxml2::XMLElement *movBoneXml = movementXML->FirstChildElement(BONE);
	while(movBoneXml)
	{
		const char *boneName = movBoneXml->Attribute(A_NAME);

		if (movementData->getMovementBoneData(boneName))
		{
			movBoneXml = movBoneXml->NextSiblingElement();
			continue;
		}


		CCBoneData *boneData = (CCBoneData *)armatureData->getBoneData(boneName);

		std::string parentName = boneData->parentName;


		tinyxml2::XMLElement *parentXml = NULL;
		if (parentName.length() != 0)
		{
			parentXml = movementXML->FirstChildElement(BONE);

			while (parentXml)
			{
				if (parentName.compare(parentXml->Attribute(A_NAME)) == 0)
				{
					break;
				}
				parentXml = parentXml->NextSiblingElement(BONE);
			}
		}

		CCMovementBoneData *moveBoneData = decodeMovementBone(movBoneXml, parentXml, boneData);
		movementData->addMovementBoneData(moveBoneData);
		moveBoneData->release();

		movBoneXml = movBoneXml->NextSiblingElement(BONE);
	}

	return movementData;
}


CCMovementBoneData *CCDataReaderHelper::decodeMovementBone(tinyxml2::XMLElement *movBoneXml, tinyxml2::XMLElement *parentXml, CCBoneData *boneData)
{
	CCMovementBoneData *movBoneData = new CCMovementBoneData();
	movBoneData->init();

	float scale, delay;

	if( movBoneXml )
	{
		if( movBoneXml->QueryFloatAttribute(A_MOVEMENT_SCALE, &scale) == tinyxml2::XML_SUCCESS )
		{
			movBoneData->scale = scale;
		}
		if( movBoneXml->QueryFloatAttribute(A_MOVEMENT_DELAY, &delay) == tinyxml2::XML_SUCCESS )
		{
			if(delay > 0)
			{
				delay -= 1;
			}
			movBoneData->delay = delay;
		}
	}

	int length = 0;
	int i = 0;
	int parentTotalDuration = 0;
	int currentDuration = 0;

	tinyxml2::XMLElement *parentFrameXML = NULL;

	std::vector<tinyxml2::XMLElement *> parentXmlList;

	/*
	*  get the parent frame xml list, we need get the origin data
	*/
	if( parentXml != NULL )
	{
		parentFrameXML = parentXml->FirstChildElement(FRAME);
		while (parentFrameXML)
		{
			parentXmlList.push_back(parentFrameXML);
			parentFrameXML = parentFrameXML->NextSiblingElement(FRAME);
		}

		parentFrameXML = NULL;

		length = parentXmlList.size();
	}


	int totalDuration = 0;

	std::string name = movBoneXml->Attribute(A_NAME);

	movBoneData->name = name;

	tinyxml2::XMLElement *frameXML = movBoneXml->FirstChildElement(FRAME);

	while( frameXML )
	{
		if(parentXml)
		{
			/*
			*  in this loop we get the corresponding parent frame xml
			*/
			while(i < length && (parentFrameXML ? (totalDuration < parentTotalDuration || totalDuration >= parentTotalDuration + currentDuration) : true))
			{
				parentFrameXML = parentXmlList[i];
				parentTotalDuration += currentDuration;
				parentFrameXML->QueryIntAttribute(A_DURATION, &currentDuration);
				i++;

			}
		}

		CCFrameData *frameData = decodeFrame( frameXML, parentFrameXML, boneData);
		movBoneData->addFrameData(frameData);
		frameData->release();

		frameData->frameID = totalDuration;
		totalDuration += frameData->duration;
		movBoneData->duration = totalDuration;

		frameXML = frameXML->NextSiblingElement(FRAME);
	}


	//
	CCFrameData *frameData = new CCFrameData();
	frameData->copy((CCFrameData*)movBoneData->frameList.lastObject());
	frameData->frameID = movBoneData->duration;
	movBoneData->addFrameData(frameData);
	frameData->release();

	return movBoneData;
}

CCFrameData *CCDataReaderHelper::decodeFrame(tinyxml2::XMLElement *frameXML,  tinyxml2::XMLElement *parentFrameXml, CCBoneData *boneData)
{
	float x, y, scale_x, scale_y, skew_x, skew_y = 0;
	int duration, displayIndex, zOrder, tweenEasing, blendType = 0;

	CCFrameData *frameData = new CCFrameData();

	if(frameXML->Attribute(A_MOVEMENT) != NULL)
	{
		frameData->strMovement = frameXML->Attribute(A_MOVEMENT);
	}
	if(frameXML->Attribute(A_EVENT) != NULL)
	{
		frameData->strEvent = frameXML->Attribute(A_EVENT);
	}
	if(frameXML->Attribute(A_SOUND) != NULL)
	{
		frameData->strSound = frameXML->Attribute(A_SOUND);
	}
	if(frameXML->Attribute(A_SOUND_EFFECT) != NULL)
	{
		frameData->strSoundEffect = frameXML->Attribute(A_SOUND_EFFECT);
	}



	if (s_FlashToolVersion >= VERSION_2_0)
	{
		if(frameXML->QueryFloatAttribute(A_COCOS2DX_X, &x) == tinyxml2::XML_SUCCESS)
		{
			frameData->x = x;
			frameData->x *= s_PositionReadScale;
		}
		if(frameXML->QueryFloatAttribute(A_COCOS2DX_Y, &y) == tinyxml2::XML_SUCCESS)
		{
			frameData->y = -y;
			frameData->y *= s_PositionReadScale;
		}
	}
	else
	{
		if(frameXML->QueryFloatAttribute(A_X, &x) == tinyxml2::XML_SUCCESS)
		{
			frameData->x = x;
			frameData->x *= s_PositionReadScale;
		}
		if(frameXML->QueryFloatAttribute(A_Y, &y) == tinyxml2::XML_SUCCESS)
		{
			frameData->y = -y;
			frameData->y *= s_PositionReadScale;
		}
	}

	if( frameXML->QueryFloatAttribute(A_SCALE_X, &scale_x) == tinyxml2::XML_SUCCESS )
	{
		frameData->scaleX = scale_x;
	}
	if( frameXML->QueryFloatAttribute(A_SCALE_Y, &scale_y) == tinyxml2::XML_SUCCESS )
	{
		frameData->scaleY = scale_y;
	}
	if( frameXML->QueryFloatAttribute(A_SKEW_X, &skew_x) == tinyxml2::XML_SUCCESS )
	{
		frameData->skewX = CC_DEGREES_TO_RADIANS(skew_x);
	}
	if( frameXML->QueryFloatAttribute(A_SKEW_Y, &skew_y) == tinyxml2::XML_SUCCESS )
	{
		frameData->skewY = CC_DEGREES_TO_RADIANS(-skew_y);
	}
	if( frameXML->QueryIntAttribute(A_DURATION, &duration) == tinyxml2::XML_SUCCESS )
	{
		frameData->duration = duration;
	}
	if(  frameXML->QueryIntAttribute(A_DISPLAY_INDEX, &displayIndex) == tinyxml2::XML_SUCCESS )
	{
		frameData->displayIndex = displayIndex;
	}
	if(  frameXML->QueryIntAttribute(A_Z, &zOrder) == tinyxml2::XML_SUCCESS )
	{
		frameData->zOrder = zOrder;
	}
	if (  frameXML->QueryIntAttribute(A_BLEND_TYPE, &blendType) == tinyxml2::XML_SUCCESS )
	{
		frameData->blendType = (CCBlendType)blendType;
	}

	tinyxml2::XMLElement *colorTransformXML = frameXML->FirstChildElement(A_COLOR_TRANSFORM);
	if (colorTransformXML)
	{
		int alpha, red, green, blue = 100;
		int alphaOffset, redOffset, greenOffset, blueOffset = 0;

		colorTransformXML->QueryIntAttribute(A_ALPHA, &alpha);
		colorTransformXML->QueryIntAttribute(A_RED, &red);
		colorTransformXML->QueryIntAttribute(A_GREEN, &green);
		colorTransformXML->QueryIntAttribute(A_BLUE, &blue) ;

		colorTransformXML->QueryIntAttribute(A_ALPHA_OFFSET, &alphaOffset);
		colorTransformXML->QueryIntAttribute(A_RED_OFFSET, &redOffset);
		colorTransformXML->QueryIntAttribute(A_GREEN_OFFSET, &greenOffset);
		colorTransformXML->QueryIntAttribute(A_BLUE_OFFSET, &blueOffset) ;

		frameData->a = 2.55 * alphaOffset + alpha;
		frameData->r = 2.55 * redOffset + red;
		frameData->g = 2.55 * greenOffset + green;
		frameData->b = 2.55 * blueOffset + blue;

		frameData->isUseColorInfo = true;
	}


	const char *_easing = frameXML->Attribute(A_TWEEN_EASING);
	if(_easing != NULL)
	{
		std::string str = _easing;
		if(str.compare(FL_NAN) != 0)
		{
			if( frameXML->QueryIntAttribute(A_TWEEN_EASING, &(tweenEasing)) == tinyxml2::XML_SUCCESS)
			{
				frameData->tweenEasing = (CCTweenType)tweenEasing;
			}
		}
		else
		{
			frameData->tweenEasing  = TWEEN_EASING_MAX;
		}
	}

	if(parentFrameXml)
	{
		/*
		*  recalculate frame data from parent frame data, use for translate matrix
		*/
		CCBaseData helpNode;
		if (s_FlashToolVersion >= VERSION_2_0)
		{
			parentFrameXml->QueryFloatAttribute(A_COCOS2DX_X, &helpNode.x);
			parentFrameXml->QueryFloatAttribute(A_COCOS2DX_Y, &helpNode.y);
		}
		else
		{
			parentFrameXml->QueryFloatAttribute(A_X, &helpNode.x);
			parentFrameXml->QueryFloatAttribute(A_Y, &helpNode.y);
		}


		parentFrameXml->QueryFloatAttribute(A_SKEW_X, &helpNode.skewX);
		parentFrameXml->QueryFloatAttribute(A_SKEW_Y, &helpNode.skewY);

		helpNode.y = -helpNode.y;
		helpNode.skewX = CC_DEGREES_TO_RADIANS(helpNode.skewX);
		helpNode.skewY = CC_DEGREES_TO_RADIANS(-helpNode.skewY);

		CCTransformHelp::transformFromParent(*frameData, helpNode);
	}
	return frameData;
}

CCTextureData *CCDataReaderHelper::decodeTexture(tinyxml2::XMLElement *textureXML)
{
	CCTextureData *textureData = new CCTextureData();
	textureData->init();

	if( textureXML->Attribute(A_NAME) != NULL)
	{
		textureData->name = textureXML->Attribute(A_NAME);
	}

	float px, py, width, height = 0;

	if(s_FlashToolVersion >= VERSION_2_0)
	{
		textureXML->QueryFloatAttribute(A_COCOS2D_PIVOT_X, &px);
		textureXML->QueryFloatAttribute(A_COCOS2D_PIVOT_Y, &py);
	}
	else
	{
		textureXML->QueryFloatAttribute(A_PIVOT_X, &px);
		textureXML->QueryFloatAttribute(A_PIVOT_Y, &py);
	}

	textureXML->QueryFloatAttribute(A_WIDTH, &width);
	textureXML->QueryFloatAttribute(A_HEIGHT, &height);

	float anchorPointX = px / width;
	float anchorPointY = (height - py) / height;

	textureData->pivotX = anchorPointX;
	textureData->pivotY = anchorPointY;

	tinyxml2::XMLElement *contourXML = textureXML->FirstChildElement(CONTOUR);

	while (contourXML)
	{
		CCContourData *contourData = decodeContour(contourXML);
		textureData->addContourData(contourData);
		contourData->release();

		contourXML = contourXML->NextSiblingElement(CONTOUR);
	}

	return textureData;
}

CCContourData *CCDataReaderHelper::decodeContour(tinyxml2::XMLElement *contourXML)
{
	CCContourData *contourData = new CCContourData();
	contourData->init();

	tinyxml2::XMLElement *vertexDataXML = contourXML->FirstChildElement(CONTOUR_VERTEX);

	while (vertexDataXML)
	{
		CCContourVertex2 *vertex = new CCContourVertex2(0, 0);
		vertex->release();

		vertexDataXML->QueryFloatAttribute(A_X, &vertex->x);
		vertexDataXML->QueryFloatAttribute(A_Y, &vertex->y);

		vertex->y = -vertex->y;
		contourData->vertexList.addObject(vertex);

		vertexDataXML = vertexDataXML->NextSiblingElement(CONTOUR_VERTEX);
	}

	return contourData;
}



void CCDataReaderHelper::addDataFromJsonCache(const char *fileContent, DataInfo *dataInfo)
{
	cs::CSJsonDictionary json;
	json.initWithDescription(fileContent);

	// Decode armatures
	int length = json.getArrayItemCount(ARMATURE_DATA);
	for (int i = 0; i < length; i++)
	{
		cs::CSJsonDictionary *armatureDic = json.getSubItemFromArray(ARMATURE_DATA, i);
		CCArmatureData *armatureData = decodeArmature(*armatureDic);

		if (dataInfo)
		{
			pthread_mutex_lock(&s_addDataMutex);
		}
		CCArmatureDataManager::sharedArmatureDataManager()->addArmatureData(armatureData->name.c_str(), armatureData);
		armatureData->release();
		if (dataInfo)
		{
			pthread_mutex_unlock(&s_addDataMutex);
		}
		delete armatureDic;
	}

	// Decode animations
	length = json.getArrayItemCount(ANIMATION_DATA);
	for (int i = 0; i < length; i++)
	{
		cs::CSJsonDictionary *animationDic = json.getSubItemFromArray(ANIMATION_DATA, i);
		CCAnimationData *animationData = decodeAnimation(*animationDic);

		if (dataInfo)
		{
			pthread_mutex_lock(&s_addDataMutex);
		}
		CCArmatureDataManager::sharedArmatureDataManager()->addAnimationData(animationData->name.c_str(), animationData);
		animationData->release();
		if (dataInfo)
		{
			pthread_mutex_unlock(&s_addDataMutex);
		}
		delete animationDic;
	}

	// Decode textures
	length = json.getArrayItemCount(TEXTURE_DATA);
	for (int i = 0; i < length; i++)
	{
		cs::CSJsonDictionary *textureDic = json.getSubItemFromArray(TEXTURE_DATA, i);
		CCTextureData *textureData = decodeTexture(*textureDic);

		if (dataInfo)
		{
			pthread_mutex_lock(&s_addDataMutex);
		}
		CCArmatureDataManager::sharedArmatureDataManager()->addTextureData(textureData->name.c_str(), textureData);
		textureData->release();
		if (dataInfo)
		{
			pthread_mutex_unlock(&s_addDataMutex);
		}
		delete textureDic;
	}

	// Auto load sprite file
	bool autoLoad = dataInfo == NULL ? CCArmatureDataManager::sharedArmatureDataManager()->isAutoLoadSpriteFile() : dataInfo->asyncStruct->autoLoadSpriteFile;
	if (autoLoad)
	{
		length = json.getArrayItemCount(CONFIG_FILE_PATH);
		for (int i = 0; i < length; i++)
		{
			const char *path = json.getStringValueFromArray(CONFIG_FILE_PATH, i);
			if (path == NULL)
			{
				CCLOG("load CONFIG_FILE_PATH error.");
				return;
			}

			std::string filePath = path;
			filePath = filePath.erase(filePath.find_last_of("."));

			if (dataInfo != NULL)
			{
				dataInfo->configFileQueue.push(filePath);
			}
			else
			{
				std::string plistPath = filePath + ".plist";
				std::string pngPath =  filePath + ".png";

				CCArmatureDataManager::sharedArmatureDataManager()->addSpriteFrameFromFile((s_BasefilePath + plistPath).c_str(), (s_BasefilePath + pngPath).c_str());
			}
		}
	}
}

CCArmatureData *CCDataReaderHelper::decodeArmature(cs::CSJsonDictionary &json)
{
	CCArmatureData *armatureData = new CCArmatureData();
	armatureData->init();

	const char *name = json.getItemStringValue(A_NAME);
	if(name != NULL)
	{
		armatureData->name = name;
	}

	s_CocoStudioVersion = armatureData->dataVersion = json.getItemFloatValue(VERSION, 0.1f);

	int length = json.getArrayItemCount(BONE_DATA);
	for (int i = 0; i < length; i++)
	{
		cs::CSJsonDictionary *dic = json.getSubItemFromArray(BONE_DATA, i);
		CCBoneData *boneData = decodeBone(*dic);
		armatureData->addBoneData(boneData);
		boneData->release();

		delete dic;
	}

	return armatureData;
}

CCBoneData *CCDataReaderHelper::decodeBone(cs::CSJsonDictionary &json)
{
	CCBoneData *boneData = new CCBoneData();
	boneData->init();

	decodeNode(boneData, json);

	const char *str = json.getItemStringValue(A_NAME);
	if(str != NULL)
	{
		boneData->name = str;
	}

	str = json.getItemStringValue(A_PARENT);
	if(str != NULL)
	{
		boneData->parentName = str;
	}

	int length = json.getArrayItemCount(DISPLAY_DATA);

	for (int i = 0; i < length; i++)
	{
		cs::CSJsonDictionary *dic = json.getSubItemFromArray(DISPLAY_DATA, i);
		CCDisplayData *displayData = decodeBoneDisplay(*dic);
		boneData->addDisplayData(displayData);
		displayData->release();

		delete dic;
	}

	return boneData;
}

CCDisplayData *CCDataReaderHelper::decodeBoneDisplay(cs::CSJsonDictionary &json)
{
	DisplayType displayType = (DisplayType)json.getItemIntValue(A_DISPLAY_TYPE, CS_DISPLAY_SPRITE);

	CCDisplayData *displayData = NULL;

	switch (displayType)
	{
	case CS_DISPLAY_SPRITE:
		{
			displayData = new CCSpriteDisplayData();

			const char *name = json.getItemStringValue(A_NAME);
			if(name != NULL)
			{
				((CCSpriteDisplayData *)displayData)->displayName = name;
			}

			cs::CSJsonDictionary *dic = json.getSubItemFromArray(SKIN_DATA, 0);
			if (dic != NULL)
			{
				CCSpriteDisplayData *sdd = (CCSpriteDisplayData *)displayData;
				sdd->skinData.x = dic->getItemFloatValue(A_X, 0) * s_PositionReadScale;
				sdd->skinData.y = dic->getItemFloatValue(A_Y, 0) * s_PositionReadScale;
				sdd->skinData.scaleX = dic->getItemFloatValue(A_SCALE_X, 1);
				sdd->skinData.scaleY = dic->getItemFloatValue(A_SCALE_Y, 1);
				sdd->skinData.skewX = dic->getItemFloatValue(A_SKEW_X, 0);
				sdd->skinData.skewY = dic->getItemFloatValue(A_SKEW_Y, 0);
				delete dic;
			}
		}

		break;
	case CS_DISPLAY_ARMATURE:
		{
			displayData = new CCArmatureDisplayData();

			const char *name = json.getItemStringValue(A_NAME);
			if(name != NULL)
			{
				((CCArmatureDisplayData *)displayData)->displayName = name;
			}
		}
		break;
	case CS_DISPLAY_PARTICLE:
		{
			displayData = new CCParticleDisplayData();

			const char *plist = json.getItemStringValue(A_PLIST);
			if(plist != NULL)
			{
				((CCParticleDisplayData *)displayData)->plist = s_BasefilePath + plist;
			}
		}
		break;
	default:
		displayData = new CCSpriteDisplayData();

		break;
	}


	displayData->displayType = displayType;

	return displayData;
}

CCAnimationData *CCDataReaderHelper::decodeAnimation(cs::CSJsonDictionary &json)
{
	CCAnimationData *aniData = new CCAnimationData();

	const char *name = json.getItemStringValue(A_NAME);
	if(name != NULL)
	{
		aniData->name = name;
	}

	int length = json.getArrayItemCount(MOVEMENT_DATA);

	for (int i = 0; i < length; i++)
	{
		cs::CSJsonDictionary *dic = json.getSubItemFromArray(MOVEMENT_DATA, i);
		CCMovementData *movementData = decodeMovement(*dic);
		aniData->addMovement(movementData);
		movementData->release();

		delete dic;
	}

	return aniData;
}

CCMovementData *CCDataReaderHelper::decodeMovement(cs::CSJsonDictionary &json)
{
	CCMovementData *movementData = new CCMovementData();

	movementData->loop = json.getItemBoolvalue(A_LOOP, true);
	movementData->durationTween = json.getItemIntValue(A_DURATION_TWEEN, 0);
	movementData->durationTo = json.getItemIntValue(A_DURATION_TO, 0);
	movementData->duration = json.getItemIntValue(A_DURATION, 0);
	movementData->scale = json.getItemFloatValue(A_MOVEMENT_SCALE, 1);
	movementData->tweenEasing = (CCTweenType)json.getItemIntValue(A_TWEEN_EASING, Linear);

	const char *name = json.getItemStringValue(A_NAME);
	if(name != NULL)
	{
		movementData->name = name;
	}

	int length = json.getArrayItemCount(MOVEMENT_BONE_DATA);
	for (int i = 0; i < length; i++)
	{
		cs::CSJsonDictionary *dic = json.getSubItemFromArray(MOVEMENT_BONE_DATA, i);
		CCMovementBoneData *movementBoneData = decodeMovementBone(*dic);
		movementData->addMovementBoneData(movementBoneData);
		movementBoneData->release();

		delete dic;
	}

	return movementData;
}

CCMovementBoneData *CCDataReaderHelper::decodeMovementBone(cs::CSJsonDictionary &json)
{
	CCMovementBoneData *movementBoneData = new CCMovementBoneData();
	movementBoneData->init();

	movementBoneData->delay = json.getItemFloatValue(A_MOVEMENT_DELAY, 0);

	const char *name = json.getItemStringValue(A_NAME);
	if(name != NULL)
	{
		movementBoneData->name = name;
	}

	int length = json.getArrayItemCount(FRAME_DATA);
	for (int i = 0; i < length; i++)
	{
		cs::CSJsonDictionary *dic = json.getSubItemFromArray(FRAME_DATA, i);
		CCFrameData *frameData = decodeFrame(*dic);

		movementBoneData->addFrameData(frameData);
		frameData->release();

		if (s_CocoStudioVersion < VERSION_COMBINED)
		{
			frameData->frameID = movementBoneData->duration;
			movementBoneData->duration += frameData->duration;
		}

		delete dic;
	}

	if (s_CocoStudioVersion < VERSION_COMBINED)
	{
		if (movementBoneData->frameList.count() > 0)
		{
			CCFrameData *frameData = new CCFrameData();
			frameData->copy((CCFrameData*)movementBoneData->frameList.lastObject());
			movementBoneData->addFrameData(frameData);
			frameData->release();

			frameData->frameID = movementBoneData->duration;
		}
	}

	return movementBoneData;
}

CCFrameData *CCDataReaderHelper::decodeFrame(cs::CSJsonDictionary &json)
{
	CCFrameData *frameData = new CCFrameData();

	decodeNode(frameData, json);

	frameData->tweenEasing = (CCTweenType)json.getItemIntValue(A_TWEEN_EASING, Linear);
	frameData->displayIndex = json.getItemIntValue(A_DISPLAY_INDEX, 0);
	frameData->blendType = (CCBlendType)json.getItemIntValue(A_BLEND_TYPE, 0);

	const char *event = json.getItemStringValue(A_EVENT);
	if (event != NULL)
	{
		frameData->strEvent = event;
	}

	if (s_CocoStudioVersion < VERSION_COMBINED)
	{
		frameData->duration = json.getItemIntValue(A_DURATION, 1);
	}
	else
	{
		frameData->frameID = json.getItemIntValue(A_FRAME_INDEX, 0);
	}

	return frameData;
}

CCTextureData *CCDataReaderHelper::decodeTexture(cs::CSJsonDictionary &json)
{
	CCTextureData *textureData = new CCTextureData();
	textureData->init();

	const char *name = json.getItemStringValue(A_NAME);
	if(name != NULL)
	{
		textureData->name = name;
	}

	textureData->width = json.getItemFloatValue(A_WIDTH, 0);
	textureData->height = json.getItemFloatValue(A_HEIGHT, 0);
	textureData->pivotX = json.getItemFloatValue(A_PIVOT_X, 0);
	textureData->pivotY = json.getItemFloatValue(A_PIVOT_Y, 0);

	int length = json.getArrayItemCount(CONTOUR_DATA);
	for (int i = 0; i < length; i++)
	{
		cs::CSJsonDictionary *dic = json.getSubItemFromArray(CONTOUR_DATA, i);
		CCContourData *contourData = decodeContour(*dic);
		textureData->contourDataList.addObject(contourData);
		contourData->release();

		delete dic;
	}

	return textureData;
}

CCContourData *CCDataReaderHelper::decodeContour(cs::CSJsonDictionary &json)
{
	CCContourData *contourData = new CCContourData();

	int length = json.getArrayItemCount(VERTEX_POINT);
	for (int i = length - 1; i >= 0; i--)
	{
		cs::CSJsonDictionary *dic = json.getSubItemFromArray(VERTEX_POINT, i);

		CCContourVertex2 *vertex = new CCContourVertex2(0, 0);

		vertex->x = dic->getItemFloatValue(A_X, 0);
		vertex->y = dic->getItemFloatValue(A_Y, 0);

		contourData->vertexList.addObject(vertex);
		vertex->release();

		delete dic;
	}

	return contourData;
}

void CCDataReaderHelper::decodeNode(CCBaseData *node, cs::CSJsonDictionary &json)
{
	node->x = json.getItemFloatValue(A_X, 0) * s_PositionReadScale;
	node->y = json.getItemFloatValue(A_Y, 0) * s_PositionReadScale;
	node->zOrder = json.getItemIntValue(A_Z, 0);

	node->skewX = json.getItemFloatValue(A_SKEW_X, 0);
	node->skewY = json.getItemFloatValue(A_SKEW_Y, 0);
	node->scaleX = json.getItemFloatValue(A_SCALE_X, 1);
	node->scaleY = json.getItemFloatValue(A_SCALE_Y, 1);

	cs::CSJsonDictionary *colorDic = json.getSubItemFromArray(COLOR_INFO, 0);

	if (colorDic)
	{
		node->a = colorDic->getItemIntValue(A_ALPHA, 255);
		node->r = colorDic->getItemIntValue(A_RED, 255);
		node->g = colorDic->getItemIntValue(A_GREEN, 255);
		node->b = colorDic->getItemIntValue(A_BLUE, 255);

		node->isUseColorInfo = true;

		delete colorDic;
	}

}

NS_CC_EXT_END
