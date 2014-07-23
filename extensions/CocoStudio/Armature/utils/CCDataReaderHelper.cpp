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
#include "CCBReader/CCData.h"
#include "../datas/CCDatas.h"
#include <errno.h>
#include <stack>
#include <string>
#include <cctype>
#include <queue>
#include <list>
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
#include <pthread.h>
#else
#include "CCPThreadWinRT.h"
#include <ppl.h>
#include <ppltasks.h>
using namespace concurrency;
#endif

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
static const char *A_TWEEN_ROTATION = "twR";
static const char *A_EASING_PARAM = "twEP";
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
static const char *A_BLEND_SRC = "bd_src";
static const char *A_BLEND_DST = "bd_dst";


static const char *A_ALPHA = "a";
static const char *A_RED = "r";
static const char *A_GREEN = "g";
static const char *A_BLUE = "b";
static const char *A_ALPHA_OFFSET = "aM";
static const char *A_RED_OFFSET = "rM";
static const char *A_GREEN_OFFSET = "gM";
static const char *A_BLUE_OFFSET = "bM";
static const char *A_COLOR_TRANSFORM = "colorTransform";
static const char *A_TWEEN_FRAME = "tweenFrame";



static const char *CONTOUR = "con";
static const char *CONTOUR_VERTEX = "con_vt";


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

static const char *CONFIG_FILE_PATH = "config_file_path";
static const char *CONTENT_SCALE = "content_scale";

NS_CC_EXT_BEGIN



float s_PositionReadScale = 1;

std::vector<std::string> CCDataReaderHelper::s_arrConfigFileList;
CCDataReaderHelper *CCDataReaderHelper::s_DataReaderHelper = NULL;

enum ConfigType
{
    DragonBone_XML,
    CocoStudio_JSON,
	CocoStudio_Binary
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
    
    std::string    imagePath;
    std::string    plistPath;
} AsyncStruct;

typedef struct _DataInfo
{
    AsyncStruct *asyncStruct;
    std::queue<std::string>      configFileQueue;
    float contentScale;
    std::string    filename;
    std::string    baseFilePath;
    float flashToolVersion;
    float cocoStudioVersion;
} DataInfo;


static pthread_t s_loadingThread;

static pthread_mutex_t		s_SleepMutex;
static pthread_cond_t		s_SleepCondition;

static pthread_mutex_t      s_asyncStructQueueMutex;
static pthread_mutex_t      s_DataInfoMutex;

static pthread_mutex_t      s_addDataMutex;
static pthread_mutex_t      s_ReadFileMutex;

static pthread_mutex_t      s_GetFileDataMutex;

#ifdef EMSCRIPTEN
// Hack to get ASM.JS validation (no undefined symbols allowed).
#define pthread_cond_signal(_)
#endif // EMSCRIPTEN

static unsigned long s_nAsyncRefCount = 0;
static unsigned long s_nAsyncRefTotalCount = 0;

static bool need_quit = false;

static std::queue<AsyncStruct *> *s_pAsyncStructQueue = NULL;
static std::queue<DataInfo *>   *s_pDataQueue = NULL;

static void addData(AsyncStruct *pAsyncStruct)
{
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(pAsyncStruct->filename.c_str());
    unsigned long size;
    pthread_mutex_lock(&s_GetFileDataMutex);
	std::string readmode = "r";
	bool isbinary = pAsyncStruct->configType == CocoStudio_Binary;
	if(isbinary)
		readmode += "b";
	unsigned char *pBytes = CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str() , readmode.c_str(), &size);
	CCData data(pBytes, size);
    CC_SAFE_DELETE_ARRAY(pBytes);
	pAsyncStruct->fileContent = std::string((const char*)data.getBytes(), data.getSize());
    pthread_mutex_unlock(&s_GetFileDataMutex);

    // generate data info
    DataInfo *pDataInfo = new DataInfo();
    pDataInfo->asyncStruct = pAsyncStruct;
    pDataInfo->filename = pAsyncStruct->filename;
    pDataInfo->baseFilePath = pAsyncStruct->baseFilePath;

    if (pAsyncStruct->configType == DragonBone_XML)
    {
        CCDataReaderHelper::addDataFromCache(pAsyncStruct->fileContent.c_str(), pDataInfo);
    }
    else if(pAsyncStruct->configType == CocoStudio_JSON)
    {
        CCDataReaderHelper::addDataFromJsonCache(pAsyncStruct->fileContent.c_str(), pDataInfo);
    }
	else if(isbinary)
	{
		CCDataReaderHelper::addDataFromBinaryCache(pAsyncStruct->fileContent.c_str(),pDataInfo);
	}

    // put the image info into the queue
    pthread_mutex_lock(&s_DataInfoMutex);
    s_pDataQueue->push(pDataInfo);
    pthread_mutex_unlock(&s_DataInfoMutex);
}

static void *loadData(void *)
{
    while (true)
    {
        // create autorelease pool for iOS
        CCThread thread;
        thread.createAutoreleasePool();

        std::queue<AsyncStruct *> *pQueue = s_pAsyncStructQueue;
        pthread_mutex_lock(&s_asyncStructQueueMutex);// get async struct from queue
        if (pQueue->empty())
        {
            pthread_mutex_unlock(&s_asyncStructQueueMutex);
            if (need_quit)
            {
                break;
            }
            else
            {
                pthread_cond_wait(&s_SleepCondition, &s_SleepMutex);
                continue;
            }
        }
        else
        {
            AsyncStruct *pAsyncStruct = pQueue->front();
            pQueue->pop();
            pthread_mutex_unlock(&s_asyncStructQueueMutex);
            addData(pAsyncStruct);
       }
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
        pthread_mutex_destroy(&s_GetFileDataMutex);
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
    s_arrConfigFileList.clear();
    CC_SAFE_RELEASE_NULL(s_DataReaderHelper);
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
    std::string basefilePath = filePath;
    size_t pos = basefilePath.find_last_of("/");
    if (pos != std::string::npos)
    {
        basefilePath = basefilePath.substr(0, pos + 1);
    }
    else
    {
        basefilePath = "";
    }


    std::string filePathStr =  filePath;
    size_t startPos = filePathStr.find_last_of(".");
    std::string str = &filePathStr[startPos];

    unsigned long size;
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(filePath);
    unsigned char *pBytes = NULL;
    if ( 0 == str.compare(".csb"))
	{
		pBytes = CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str() , "rb", &size);
		
	}
	else
	{
		pBytes = CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str() , "r", &size);
	}


    DataInfo dataInfo;
    dataInfo.filename = filePathStr;
    dataInfo.asyncStruct = NULL;
    dataInfo.baseFilePath = basefilePath;

	std::string load_str = std::string((const char*)pBytes, size);
    if (str.compare(".xml") == 0)
    {
        CCDataReaderHelper::addDataFromCache(load_str.c_str(), &dataInfo);
    }
    else if(str.compare(".json") == 0 || str.compare(".ExportJson") == 0)
    {
        CCDataReaderHelper::addDataFromJsonCache(load_str.c_str(), &dataInfo);
    }
	else if(str.compare(".csb") == 0)
	{
		CCDataReaderHelper::addDataFromBinaryCache(load_str.c_str(), &dataInfo);
	}
	CC_SAFE_DELETE_ARRAY(pBytes);
}

void CCDataReaderHelper::addDataFromFileAsync(const char *imagePath, const char *plistPath, const char *filePath, CCObject *target, SEL_SCHEDULE selector)
{
#ifdef EMSCRIPTEN
    CCLOGWARN("Cannot load data %s asynchronously in Emscripten builds.", filePath);
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
    std::string basefilePath = filePath;
    size_t pos = basefilePath.find_last_of("/");
    if (pos != std::string::npos)
    {
        basefilePath = basefilePath.substr(0, pos + 1);
    }
    else
    {
        basefilePath = "";
    }


    // lazy init
    if (s_pAsyncStructQueue == NULL)
    {
        s_pAsyncStructQueue = new std::queue<AsyncStruct *>();
        s_pDataQueue = new std::queue<DataInfo *>();

        pthread_mutex_init(&s_asyncStructQueueMutex, NULL);
        pthread_mutex_init(&s_DataInfoMutex, NULL);
        pthread_mutex_init(&s_SleepMutex, NULL);
        pthread_mutex_init(&s_addDataMutex, NULL);
        pthread_mutex_init(&s_ReadFileMutex, NULL);
        pthread_mutex_init(&s_GetFileDataMutex, NULL);
        pthread_cond_init(&s_SleepCondition, NULL);
 #if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
        pthread_create(&s_loadingThread, NULL, loadData, NULL);
#endif
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
    data->baseFilePath = basefilePath;
    data->target = target;
    data->selector = selector;
    data->autoLoadSpriteFile = CCArmatureDataManager::sharedArmatureDataManager()->isAutoLoadSpriteFile();

    data->imagePath = imagePath;
    data->plistPath = plistPath;

    std::string filePathStr =  filePath;
    size_t startPos = filePathStr.find_last_of(".");
    std::string str = &filePathStr[startPos];

    if (str.compare(".xml") == 0)
    {
        data->configType = DragonBone_XML;
    }
    else if(str.compare(".json") == 0 || str.compare(".ExportJson") == 0)
    {
        data->configType = CocoStudio_JSON;
    }
	else if( 0 == str.compare(".csb"))
	{
		data->configType = CocoStudio_Binary;
	}

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
    // add async struct into queue
    pthread_mutex_lock(&s_asyncStructQueueMutex);
    s_pAsyncStructQueue->push(data);
    pthread_mutex_unlock(&s_asyncStructQueueMutex);

    pthread_cond_signal(&s_SleepCondition);
#else
    // WinRT uses an Async Task to load the image since the ThreadPool has a limited number of threads
    create_task([this, data] {
        addData(data);
    });
#endif
}



void CCDataReaderHelper::addDataAsyncCallBack(float dt)
{
    // the data is generated in loading thread
    std::queue<DataInfo *> *dataQueue = s_pDataQueue;

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

        if (pAsyncStruct->imagePath != "" && pAsyncStruct->plistPath != "")
        {
            pthread_mutex_lock(&s_GetFileDataMutex);
            CCArmatureDataManager::sharedArmatureDataManager()->addSpriteFrameFromFile(pAsyncStruct->plistPath.c_str(), pAsyncStruct->imagePath.c_str());
            pthread_mutex_unlock(&s_GetFileDataMutex);
        }

        while (!pDataInfo->configFileQueue.empty())
        {
            std::string configPath = pDataInfo->configFileQueue.front();
            pthread_mutex_lock(&s_GetFileDataMutex);
            CCArmatureDataManager::sharedArmatureDataManager()->addSpriteFrameFromFile((pAsyncStruct->baseFilePath + configPath + ".plist").c_str(), (pAsyncStruct->baseFilePath + configPath + ".png").c_str());
            pthread_mutex_unlock(&s_GetFileDataMutex);
            pDataInfo->configFileQueue.pop();
        }


        CCObject *target = pAsyncStruct->target;
        SEL_SCHEDULE selector = pAsyncStruct->selector;

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

void CCDataReaderHelper::removeConfigFile(const char *configFile)
{
    std::vector<std::string>::iterator it = s_arrConfigFileList.end();
    for (std::vector<std::string>::iterator i = s_arrConfigFileList.begin(); i != s_arrConfigFileList.end(); i++)
    {
        if (*i == configFile)
        {
            it = i;
        }
    }

    if (it != s_arrConfigFileList.end())
    {
        s_arrConfigFileList.erase(it);
    }
}




void CCDataReaderHelper::addDataFromCache(const char *pFileContent, DataInfo *dataInfo)
{
    tinyxml2::XMLDocument document;
    document.Parse(pFileContent);

    tinyxml2::XMLElement *root = document.RootElement();
    CCAssert(root, "XML error  or  XML is empty.");

    root->QueryFloatAttribute(VERSION, &dataInfo->flashToolVersion);


    /*
    * Begin decode armature data from xml
    */
    tinyxml2::XMLElement *armaturesXML = root->FirstChildElement(ARMATURES);
    tinyxml2::XMLElement *armatureXML = armaturesXML->FirstChildElement(ARMATURE);
    while(armatureXML)
    {
        CCArmatureData *armatureData = CCDataReaderHelper::decodeArmature(armatureXML, dataInfo);

        if (dataInfo->asyncStruct)
        {
            pthread_mutex_lock(&s_addDataMutex);
        }
        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureData(armatureData->name.c_str(), armatureData, dataInfo->filename.c_str());
        armatureData->release();
        if (dataInfo->asyncStruct)
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
        CCAnimationData *animationData = CCDataReaderHelper::decodeAnimation(animationXML, dataInfo);
        if (dataInfo->asyncStruct)
        {
            pthread_mutex_lock(&s_addDataMutex);
        }
        CCArmatureDataManager::sharedArmatureDataManager()->addAnimationData(animationData->name.c_str(), animationData, dataInfo->filename.c_str());
        animationData->release();
        if (dataInfo->asyncStruct)
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
        CCTextureData *textureData = CCDataReaderHelper::decodeTexture(textureXML, dataInfo);

        if (dataInfo->asyncStruct)
        {
            pthread_mutex_lock(&s_addDataMutex);
        }
        CCArmatureDataManager::sharedArmatureDataManager()->addTextureData(textureData->name.c_str(), textureData, dataInfo->filename.c_str());
        textureData->release();
        if (dataInfo->asyncStruct)
        {
            pthread_mutex_unlock(&s_addDataMutex);
        }
        textureXML = textureXML->NextSiblingElement(SUB_TEXTURE);
    }
}

CCArmatureData *CCDataReaderHelper::decodeArmature(tinyxml2::XMLElement *armatureXML, DataInfo *dataInfo)
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

        CCBoneData *boneData = decodeBone(boneXML, parentXML, dataInfo);
        armatureData->addBoneData(boneData);
        boneData->release();

        boneXML = boneXML->NextSiblingElement(BONE);
    }

    return armatureData;
}

CCBoneData *CCDataReaderHelper::decodeBone(tinyxml2::XMLElement *boneXML, tinyxml2::XMLElement *parentXml, DataInfo *dataInfo)
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
        CCDisplayData *displayData = decodeBoneDisplay(displayXML, dataInfo);
        boneData->addDisplayData(displayData);
        displayData->release();

        displayXML = displayXML->NextSiblingElement(DISPLAY);
    }

    return boneData;
}

CCDisplayData *CCDataReaderHelper::decodeBoneDisplay(tinyxml2::XMLElement *displayXML, DataInfo *dataInfo)
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

CCAnimationData *CCDataReaderHelper::decodeAnimation(tinyxml2::XMLElement *animationXML, DataInfo *dataInfo)
{
    CCAnimationData *aniData =  new CCAnimationData();

    const char	*name = animationXML->Attribute(A_NAME);

    CCArmatureData *armatureData = CCArmatureDataManager::sharedArmatureDataManager()->getArmatureData(name);

    aniData->name = name;

    tinyxml2::XMLElement *movementXML = animationXML->FirstChildElement(MOVEMENT);

    while( movementXML )
    {
        CCMovementData *movementData = decodeMovement(movementXML, armatureData, dataInfo);
        aniData->addMovement(movementData);
        movementData->release();

        movementXML = movementXML->NextSiblingElement(MOVEMENT);

    }

    return aniData;
}

CCMovementData *CCDataReaderHelper::decodeMovement(tinyxml2::XMLElement *movementXML, CCArmatureData *armatureData, DataInfo *dataInfo)
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
                movementData->tweenEasing = tweenEasing == 2 ? Sine_EaseInOut : (CCTweenType)tweenEasing;
            }
        }
        else
        {
            movementData->tweenEasing  = Linear;
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

        CCMovementBoneData *moveBoneData = decodeMovementBone(movBoneXml, parentXml, boneData, dataInfo);
        movementData->addMovementBoneData(moveBoneData);
        moveBoneData->release();

        movBoneXml = movBoneXml->NextSiblingElement(BONE);
    }

    return movementData;
}


CCMovementBoneData *CCDataReaderHelper::decodeMovementBone(tinyxml2::XMLElement *movBoneXml, tinyxml2::XMLElement *parentXml, CCBoneData *boneData, DataInfo *dataInfo)
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

        CCFrameData *frameData = decodeFrame( frameXML, parentFrameXML, boneData, dataInfo);
        movBoneData->addFrameData(frameData);
        frameData->release();

        frameData->frameID = totalDuration;
        totalDuration += frameData->duration;
        movBoneData->duration = totalDuration;

        frameXML = frameXML->NextSiblingElement(FRAME);
    }


    //! Change rotation range from (-180 -- 180) to (-infinity -- infinity)

    CCFrameData **frames = (CCFrameData **)movBoneData->frameList.data->arr;
    for (int i = movBoneData->frameList.count() - 1; i >= 0; i--)
    {
        if (i > 0)
        {
            float difSkewX = frames[i]->skewX -  frames[i - 1]->skewX;
            float difSkewY = frames[i]->skewY -  frames[i - 1]->skewY;

            if (difSkewX < -M_PI || difSkewX > M_PI)
            {
                frames[i - 1]->skewX = difSkewX < 0 ? frames[i - 1]->skewX - 2 * M_PI : frames[i - 1]->skewX + 2 * M_PI;
            }

            if (difSkewY < -M_PI || difSkewY > M_PI)
            {
                frames[i - 1]->skewY = difSkewY < 0 ? frames[i - 1]->skewY - 2 * M_PI : frames[i - 1]->skewY + 2 * M_PI;
            }
        }
    }

    //
    CCFrameData *frameData = new CCFrameData();
    frameData->copy((CCFrameData *)movBoneData->frameList.lastObject());
    frameData->frameID = movBoneData->duration;
    movBoneData->addFrameData(frameData);
    frameData->release();

    return movBoneData;
}

CCFrameData *CCDataReaderHelper::decodeFrame(tinyxml2::XMLElement *frameXML,  tinyxml2::XMLElement *parentFrameXml, CCBoneData *boneData, DataInfo *dataInfo)
{
    float x = 0, y = 0, scale_x = 0, scale_y = 0, skew_x = 0, skew_y, tweenRotate = 0;
    int duration = 0, displayIndex = 0, zOrder = 0, tweenEasing = 0, blendType = 0;

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

    bool tweenFrame = false;
    if (frameXML->QueryBoolAttribute(A_TWEEN_FRAME, &tweenFrame) == tinyxml2::XML_SUCCESS)
    {
        frameData->isTween = tweenFrame;
    }

    if (dataInfo->flashToolVersion >= VERSION_2_0)
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
	if(  frameXML->QueryFloatAttribute(A_TWEEN_ROTATION, &tweenRotate) == tinyxml2::XML_SUCCESS )
	{
		frameData->tweenRotate = tweenRotate;
	}
    if (  frameXML->QueryIntAttribute(A_BLEND_TYPE, &blendType) == tinyxml2::XML_SUCCESS )
    {
        switch (blendType)
        {
        case BLEND_NORMAL:
            {
                frameData->blendFunc.src = CC_BLEND_SRC;
                frameData->blendFunc.dst = CC_BLEND_DST;
            }
            break;
        case BLEND_ADD:
            {
                frameData->blendFunc.src = GL_SRC_ALPHA;
                frameData->blendFunc.dst = GL_ONE;
            }
            break;
        case BLEND_MULTIPLY:
            {
                frameData->blendFunc.src = GL_DST_COLOR;
                frameData->blendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
            }
            break;
        case BLEND_SCREEN:
            {
                frameData->blendFunc.src = GL_ONE;
                frameData->blendFunc.dst = GL_ONE_MINUS_SRC_COLOR;
            }
            break;
        default:
            {
                frameData->blendFunc.src = CC_BLEND_SRC;
                frameData->blendFunc.dst = CC_BLEND_DST;
            }
            break;
        }
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
                frameData->tweenEasing = tweenEasing == 2 ? Sine_EaseInOut : (CCTweenType)tweenEasing;
            }
        }
        else
        {
            frameData->tweenEasing  = Linear;
        }
    }

    if(parentFrameXml)
    {
        /*
        *  recalculate frame data from parent frame data, use for translate matrix
        */
        CCBaseData helpNode;
        if (dataInfo->flashToolVersion >= VERSION_2_0)
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

CCTextureData *CCDataReaderHelper::decodeTexture(tinyxml2::XMLElement *textureXML, DataInfo *dataInfo)
{
    CCTextureData *textureData = new CCTextureData();
    textureData->init();

    if( textureXML->Attribute(A_NAME) != NULL)
    {
        textureData->name = textureXML->Attribute(A_NAME);
    }

    float px, py, width, height = 0;

    if(dataInfo->flashToolVersion >= VERSION_2_0)
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
        CCContourData *contourData = decodeContour(contourXML, dataInfo);
        textureData->addContourData(contourData);
        contourData->release();

        contourXML = contourXML->NextSiblingElement(CONTOUR);
    }

    return textureData;
}

CCContourData *CCDataReaderHelper::decodeContour(tinyxml2::XMLElement *contourXML, DataInfo *dataInfo)
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
	rapidjson::Document json;
	
	json.Parse<0>(fileContent);

    if (json.HasParseError()) {
        CCLOG("GetParseError %s\n",json.GetParseError());
    }
	
	dataInfo->contentScale = DICTOOL->getFloatValue_json(json, CONTENT_SCALE, 1.0f); 
	
    // Decode armatures
	int length = DICTOOL->getArrayCount_json(json, ARMATURE_DATA); 
	for (int i = 0; i < length; i++)
    {
		const rapidjson::Value &armatureDic = DICTOOL->getSubDictionary_json(json, ARMATURE_DATA, i); 
        CCArmatureData *armatureData = decodeArmature(armatureDic, dataInfo);

        if (dataInfo->asyncStruct)
        {
            pthread_mutex_lock(&s_addDataMutex);
        }
        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureData(armatureData->name.c_str(), armatureData, dataInfo->filename.c_str());
        armatureData->release();
        if (dataInfo->asyncStruct)
        {
            pthread_mutex_unlock(&s_addDataMutex);
        }
        //delete armatureDic;
    }

    // Decode animations
	length = DICTOOL->getArrayCount_json(json, ANIMATION_DATA); 
    for (int i = 0; i < length; i++)
    {
		const rapidjson::Value &animationDic = DICTOOL->getSubDictionary_json(json, ANIMATION_DATA, i);
        CCAnimationData *animationData = decodeAnimation(animationDic, dataInfo);

        if (dataInfo->asyncStruct)
        {
            pthread_mutex_lock(&s_addDataMutex);
        }
        CCArmatureDataManager::sharedArmatureDataManager()->addAnimationData(animationData->name.c_str(), animationData, dataInfo->filename.c_str());
        animationData->release();
        if (dataInfo->asyncStruct)
        {
            pthread_mutex_unlock(&s_addDataMutex);
        }
    }

    // Decode textures
    length = DICTOOL->getArrayCount_json(json, TEXTURE_DATA);
    for (int i = 0; i < length; i++)
    {
        const rapidjson::Value &textureDic =  DICTOOL->getSubDictionary_json(json, TEXTURE_DATA, i); 
        CCTextureData *textureData = decodeTexture(textureDic);

        if (dataInfo->asyncStruct)
        {
            pthread_mutex_lock(&s_addDataMutex);
        }
        CCArmatureDataManager::sharedArmatureDataManager()->addTextureData(textureData->name.c_str(), textureData, dataInfo->filename.c_str());
        textureData->release();
        if (dataInfo->asyncStruct)
        {
            pthread_mutex_unlock(&s_addDataMutex);
        }
        //delete textureDic;
    }

    // Auto load sprite file
    bool autoLoad = dataInfo->asyncStruct == NULL ? CCArmatureDataManager::sharedArmatureDataManager()->isAutoLoadSpriteFile() : dataInfo->asyncStruct->autoLoadSpriteFile;
    if (autoLoad)
    {
        length =  DICTOOL->getArrayCount_json(json, CONFIG_FILE_PATH); 
        for (int i = 0; i < length; i++)
        {
			const char *path = DICTOOL->getStringValueFromArray_json(json, CONFIG_FILE_PATH, i); 
			if( NULL == path)
            {
                CCLOG("load CONFIG_FILE_PATH error.");
                return;
            }

            std::string filePath = path;
            filePath = filePath.erase(filePath.find_last_of("."));

            if (dataInfo->asyncStruct)
            {
                dataInfo->configFileQueue.push(filePath);
            }
            else
            {
                std::string plistPath = filePath + ".plist";
                std::string pngPath =  filePath + ".png";

                CCArmatureDataManager::sharedArmatureDataManager()->addSpriteFrameFromFile((dataInfo->baseFilePath + plistPath).c_str(), (dataInfo->baseFilePath + pngPath).c_str(), dataInfo->filename.c_str());
            }
        }
    }
}


CCArmatureData *CCDataReaderHelper::decodeArmature(const rapidjson::Value &json, DataInfo *dataInfo)
{
	CCArmatureData *armatureData = new CCArmatureData();
    armatureData->init();
    
    
	const char *name = DICTOOL->getStringValue_json(json, A_NAME);
    if(name != NULL)
    {
        armatureData->name = name;
    }

	dataInfo->cocoStudioVersion = armatureData->dataVersion = DICTOOL->getFloatValue_json(json, VERSION, 0.1f);

	int length = DICTOOL->getArrayCount_json(json, BONE_DATA, 0); 
	for (int i = 0; i < length; i++)
    {
        const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(json, BONE_DATA, i); //json[BONE_DATA][i];
        CCBoneData *boneData = decodeBone(dic,dataInfo);
        armatureData->addBoneData(boneData);  
        boneData->release();
    }

    return armatureData;
}

CCBoneData *CCDataReaderHelper::decodeBone(const rapidjson::Value &json, DataInfo *dataInfo)
{
	CCBoneData *boneData = new CCBoneData();
    boneData->init();

    decodeNode(boneData, json, dataInfo);

	const char *str = DICTOOL->getStringValue_json(json, A_NAME);
    if(str != NULL)
    {
        boneData->name = str;
    }
	
    str = DICTOOL->getStringValue_json(json, A_PARENT);
    if(str != NULL)
    {
        boneData->parentName = str;
    }

	int length = DICTOOL->getArrayCount_json(json, DISPLAY_DATA);

	for (int i = 0; i < length; ++i)
    {
        const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(json, DISPLAY_DATA, i); 
        CCDisplayData *displayData = decodeBoneDisplay(dic, dataInfo);
        boneData->addDisplayData(displayData);
        displayData->release();
    }

    return boneData;
}


CCDisplayData *CCDataReaderHelper::decodeBoneDisplay(const rapidjson::Value &json, DataInfo *dataInfo)
{
	DisplayType displayType =  (DisplayType)(DICTOOL->getIntValue_json(json, A_DISPLAY_TYPE, CS_DISPLAY_SPRITE));

    CCDisplayData *displayData = NULL;

    switch (displayType)
    {
    case CS_DISPLAY_SPRITE:
    {
        displayData = new CCSpriteDisplayData();

		const char *name =  DICTOOL->getStringValue_json(json, A_NAME);
        if(name != NULL)
        {
            ((CCSpriteDisplayData *)displayData)->displayName = name;
        }
		const rapidjson::Value &dicArray = DICTOOL->getSubDictionary_json(json, SKIN_DATA);
		if(!dicArray.IsNull())
		{
			rapidjson::SizeType index = 0;
			const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(dicArray, index);
			if (!dic.IsNull())
			{
				CCSpriteDisplayData *sdd = (CCSpriteDisplayData *)displayData;
				sdd->skinData.x = DICTOOL->getFloatValue_json(dic, A_X) * s_PositionReadScale;
				sdd->skinData.y = DICTOOL->getFloatValue_json(dic, A_Y) * s_PositionReadScale;
				sdd->skinData.scaleX = DICTOOL->getFloatValue_json(dic, A_SCALE_X, 1.0f);
				sdd->skinData.scaleY = DICTOOL->getFloatValue_json(dic, A_SCALE_Y, 1.0f);
				sdd->skinData.skewX = DICTOOL->getFloatValue_json(dic, A_SKEW_X, 0.0f);
				sdd->skinData.skewY = DICTOOL->getFloatValue_json(dic, A_SKEW_Y, 0.0f);

                sdd->skinData.x *= dataInfo->contentScale;
                sdd->skinData.y *= dataInfo->contentScale;
			}
		}
    }

    break;
    case CS_DISPLAY_ARMATURE:
    {
        displayData = new CCArmatureDisplayData();

        const char *name = DICTOOL->getStringValue_json(json, A_NAME);
        if(name != NULL)
        {
            ((CCArmatureDisplayData *)displayData)->displayName = name;
        }
    }
    break;
    case CS_DISPLAY_PARTICLE:
    {
        displayData = new CCParticleDisplayData();

        const char *plist = DICTOOL->getStringValue_json(json, A_PLIST);
        if(plist != NULL)
        {
            if (dataInfo->asyncStruct)
            {
                ((CCParticleDisplayData *)displayData)->displayName = dataInfo->asyncStruct->baseFilePath + plist;
            }
            else
            {
                ((CCParticleDisplayData *)displayData)->displayName = dataInfo->baseFilePath + plist;
            }
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

CCAnimationData *CCDataReaderHelper::decodeAnimation(const rapidjson::Value &json, DataInfo *dataInfo)
{
	CCAnimationData *aniData = new CCAnimationData();

    const char *name = DICTOOL->getStringValue_json(json, A_NAME);
    if(name != NULL)
    {
        aniData->name = name;
    }
	
    int length =  DICTOOL->getArrayCount_json(json, MOVEMENT_DATA);

	for (int i = 0; i < length; ++i)
    {
        const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(json, MOVEMENT_DATA, i);
        CCMovementData *movementData = decodeMovement(dic,dataInfo);
        aniData->addMovement(movementData);
        movementData->release();

    }

    return aniData;
}

CCMovementData *CCDataReaderHelper::decodeMovement(const rapidjson::Value &json, DataInfo *dataInfo)
{
	CCMovementData *movementData = new CCMovementData();

	movementData->loop = DICTOOL->getBooleanValue_json(json, A_LOOP, true);
	movementData->durationTween = DICTOOL->getIntValue_json(json, A_DURATION_TWEEN, 0);
    movementData->durationTo = DICTOOL->getIntValue_json(json, A_DURATION_TO, 0);
    movementData->duration = DICTOOL->getIntValue_json(json, A_DURATION, 0);
    if (!DICTOOL->checkObjectExist_json(json, A_DURATION))
    {
        movementData->scale = 1.0f;
    }
    else
    {
        movementData->scale = DICTOOL->getFloatValue_json(json, A_MOVEMENT_SCALE, 1.0f);
    }
    
	movementData->tweenEasing =  (CCTweenType)(DICTOOL->getIntValue_json(json, A_TWEEN_EASING, Linear));
    const char *name = DICTOOL->getStringValue_json(json, A_NAME);
    if(name != NULL)
    {
        movementData->name = name;
    }

	int length = DICTOOL->getArrayCount_json(json, MOVEMENT_BONE_DATA);
    for (int i = 0; i < length; i++)
    {
		const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(json, MOVEMENT_BONE_DATA, i);
        CCMovementBoneData *movementBoneData = decodeMovementBone(dic,dataInfo);
        movementData->addMovementBoneData(movementBoneData);
        movementBoneData->release();
    }

    return movementData;
}

CCMovementBoneData *CCDataReaderHelper::decodeMovementBone(const rapidjson::Value &json, DataInfo *dataInfo)
{
	CCMovementBoneData *movementBoneData = new CCMovementBoneData();
    movementBoneData->init();

	movementBoneData->delay = DICTOOL->getFloatValue_json(json, A_MOVEMENT_DELAY);
    const char *name = DICTOOL->getStringValue_json(json, A_NAME);
    if(name != NULL)
    {
        movementBoneData->name = name;
    }

	rapidjson::SizeType length = DICTOOL->getArrayCount_json(json, FRAME_DATA);
    for (rapidjson::SizeType i = 0; i < length; i++)
    {
        const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(json, FRAME_DATA, i);
        CCFrameData *frameData = decodeFrame(dic,dataInfo);

        movementBoneData->addFrameData(frameData);
        frameData->release();
		
        if (dataInfo->cocoStudioVersion < VERSION_COMBINED)
        {
            frameData->frameID = movementBoneData->duration;
            movementBoneData->duration += frameData->duration;
        }
    }

    if (dataInfo->cocoStudioVersion < VERSION_CHANGE_ROTATION_RANGE)
    {
        //! Change rotation range from (-180 -- 180) to (-infinity -- infinity)
        CCFrameData **frames = (CCFrameData **)movementBoneData->frameList.data->arr;
        for (int i = movementBoneData->frameList.count() - 1; i >= 0; i--)
        {
            if (i > 0)
            {
                float difSkewX = frames[i]->skewX -  frames[i - 1]->skewX;
                float difSkewY = frames[i]->skewY -  frames[i - 1]->skewY;

                if (difSkewX < -M_PI || difSkewX > M_PI)
                {
                    frames[i - 1]->skewX = difSkewX < 0 ? frames[i - 1]->skewX - 2 * M_PI : frames[i - 1]->skewX + 2 * M_PI;
                }

                if (difSkewY < -M_PI || difSkewY > M_PI)
                {
                    frames[i - 1]->skewY = difSkewY < 0 ? frames[i - 1]->skewY - 2 * M_PI : frames[i - 1]->skewY + 2 * M_PI;
                }
            }
        }
    }


    if (dataInfo->cocoStudioVersion < VERSION_COMBINED)
    {
        if (movementBoneData->frameList.count() > 0)
        {
            CCFrameData *frameData = new CCFrameData();
            frameData->copy((CCFrameData *)movementBoneData->frameList.lastObject());
            movementBoneData->addFrameData(frameData);
            frameData->release();

            frameData->frameID = movementBoneData->duration;
        }
    }

    return movementBoneData;
}

CCFrameData *CCDataReaderHelper::decodeFrame(const rapidjson::Value &json, DataInfo *dataInfo)
{
	CCFrameData *frameData = new CCFrameData();

    decodeNode(frameData, json, dataInfo);

	frameData->tweenEasing = (CCTweenType)(DICTOOL->getIntValue_json(json, A_TWEEN_EASING, Linear));
	frameData->displayIndex = DICTOOL->getIntValue_json(json, A_DISPLAY_INDEX);
    frameData->blendFunc.src = (GLenum)(DICTOOL->getIntValue_json(json, A_BLEND_SRC, CC_BLEND_SRC));
    frameData->blendFunc.dst = (GLenum)(DICTOOL->getIntValue_json(json, A_BLEND_DST, CC_BLEND_DST));
	frameData->isTween = DICTOOL->getBooleanValue_json(json, A_TWEEN_FRAME, true);
	const char *event =  DICTOOL->getStringValue_json(json, A_EVENT);
    
    if (event != NULL)
    {
        frameData->strEvent = event;
    }

    if (dataInfo->cocoStudioVersion < VERSION_COMBINED)
    {
		frameData->duration = DICTOOL->getIntValue_json(json, A_DURATION, 1);
    }
    else
    {
        frameData->frameID = DICTOOL->getIntValue_json(json, A_FRAME_INDEX);
    }

    int length = DICTOOL->getArrayCount_json(json, A_EASING_PARAM);
    if (length != 0)
    {
        frameData->easingParams = new float[length];

        for (int i = 0; i < length; i++)
        {
            frameData->easingParams[i] = DICTOOL->getFloatValueFromArray_json(json, A_EASING_PARAM, i);
        }
    }
    

    return frameData;
}

CCTextureData *CCDataReaderHelper::decodeTexture(const rapidjson::Value &json)
{
	CCTextureData *textureData = new CCTextureData();
    textureData->init();

	const char *name = DICTOOL->getStringValue_json(json, A_NAME);
    if(name != NULL)
    {
        textureData->name = name;
    }

	textureData->width = DICTOOL->getFloatValue_json(json, A_WIDTH);
    textureData->height = DICTOOL->getFloatValue_json(json, A_HEIGHT);
    textureData->pivotX = DICTOOL->getFloatValue_json(json, A_PIVOT_X);
    textureData->pivotY = DICTOOL->getFloatValue_json(json, A_PIVOT_Y);

	int length = DICTOOL->getArrayCount_json(json, CONTOUR_DATA);
	for (int i = 0; i < length; i++)
    {
        const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(json, CONTOUR_DATA, i);
        CCContourData *contourData = decodeContour(dic);
        textureData->contourDataList.addObject(contourData);
        contourData->release();

    }

    return textureData;
}

CCContourData *CCDataReaderHelper::decodeContour(const rapidjson::Value &json)
{
	CCContourData *contourData = new CCContourData();
    contourData->init();

	int length = DICTOOL->getArrayCount_json(json, VERTEX_POINT);
    
	for (int i = length - 1; i >= 0; --i)
    {
        const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(json, VERTEX_POINT, i);
        CCContourVertex2 *vertex = new CCContourVertex2(0, 0);
		vertex->x = DICTOOL->getFloatValue_json(dic, A_X);
        vertex->y = DICTOOL->getFloatValue_json(dic, A_Y);

        contourData->vertexList.addObject(vertex);
        vertex->release();
    }

    return contourData;
}

void CCDataReaderHelper::decodeNode(CCBaseData *node, const rapidjson::Value &json, DataInfo *dataInfo)
{
	node->x =  DICTOOL->getFloatValue_json(json, A_X) * dataInfo->contentScale;
    node->y = DICTOOL->getFloatValue_json(json, A_Y) * dataInfo->contentScale;
	node->zOrder = DICTOOL->getIntValue_json(json, A_Z);

    node->skewX = DICTOOL->getFloatValue_json(json, A_SKEW_X);
    node->skewY = DICTOOL->getFloatValue_json(json, A_SKEW_Y);
    node->scaleX = DICTOOL->getFloatValue_json(json, A_SCALE_X, 1.0f);
    node->scaleY = DICTOOL->getFloatValue_json(json, A_SCALE_Y, 1.0f);

    if (dataInfo->cocoStudioVersion < VERSION_COLOR_READING)
    { 
        if (DICTOOL->checkObjectExist_json(json, 0))
        {
            const rapidjson::Value &colorDic = DICTOOL->getSubDictionary_json(json, 0); 
            node->a = DICTOOL->getIntValue_json(colorDic, A_ALPHA, 255);   
            node->r = DICTOOL->getIntValue_json(colorDic, A_RED, 255);  
            node->g = DICTOOL->getIntValue_json(colorDic, A_GREEN, 255); 
            node->b = DICTOOL->getIntValue_json(colorDic, A_BLUE, 255); 

            node->isUseColorInfo = true;
        }
    }
    else
    {
        if (DICTOOL->checkObjectExist_json(json, COLOR_INFO))
        {
            const rapidjson::Value &colorDic =  DICTOOL->getSubDictionary_json(json, COLOR_INFO); 
            node->a = DICTOOL->getIntValue_json(colorDic, A_ALPHA, 255);   
            node->r = DICTOOL->getIntValue_json(colorDic, A_RED, 255);  
            node->g = DICTOOL->getIntValue_json(colorDic, A_GREEN, 255); 
            node->b = DICTOOL->getIntValue_json(colorDic, A_BLUE, 255); 

            node->isUseColorInfo = true;
        }
    }
}


void CCDataReaderHelper::addDataFromBinaryCache(const char *fileContent, DataInfo *dataInfo)
{
	CocoLoader tCocoLoader;
	if (tCocoLoader.ReadCocoBinBuff((char*)fileContent))
	{
		stExpCocoNode *tpRootCocoNode = tCocoLoader.GetRootCocoNode();
		rapidjson::Type tType = tpRootCocoNode->GetType(&tCocoLoader);
		if (rapidjson::kObjectType  == tType)
		{
			stExpCocoNode *tpChildArray = tpRootCocoNode->GetChildArray(&tCocoLoader);
			int nCount = tpRootCocoNode->GetChildNum();

			dataInfo->contentScale = 1.0f;
			int length = 0;
			std::string key;
			stExpCocoNode* pDataArray; 
			for (int i = 0; i < nCount; ++i)
			{
			    key = tpChildArray[i].GetName(&tCocoLoader);
				if (key.compare(CONTENT_SCALE) == 0)
				{
					std::string value = tpChildArray[i].GetValue(&tCocoLoader);
					dataInfo->contentScale = atof(value.c_str());
				}
				else if ( 0 == key.compare(ARMATURE_DATA))
				{
					pDataArray = tpChildArray[i].GetChildArray(&tCocoLoader);
					length = tpChildArray[i].GetChildNum();
					CCArmatureData * armatureData;
					for (int i = 0; i < length; ++i)
					{
						armatureData = decodeArmature(&tCocoLoader, &pDataArray[i], dataInfo);
						if (dataInfo->asyncStruct)
						{
							pthread_mutex_lock(&s_addDataMutex);
						}
						CCArmatureDataManager::sharedArmatureDataManager()->addArmatureData(armatureData->name.c_str(), armatureData, dataInfo->filename.c_str());
						armatureData->release();
						if (dataInfo->asyncStruct)
						{
							pthread_mutex_unlock(&s_addDataMutex);
						}
					}
				}
				else if ( 0 == key.compare(ANIMATION_DATA))
				{
					pDataArray = tpChildArray[i].GetChildArray(&tCocoLoader);
					length = tpChildArray[i].GetChildNum();
					CCAnimationData *animationData;
					for (int i = 0; i < length; ++i)
					{
						animationData = decodeAnimation(&tCocoLoader, &pDataArray[i], dataInfo);
						if (dataInfo->asyncStruct)
						{
							pthread_mutex_lock(&s_addDataMutex);
						}
						CCArmatureDataManager::sharedArmatureDataManager()->addAnimationData(animationData->name.c_str(), animationData, dataInfo->filename.c_str());
						animationData->release();
						if (dataInfo->asyncStruct)
						{
							pthread_mutex_unlock(&s_addDataMutex);
						}
					}
				}
				else if (key.compare(TEXTURE_DATA) == 0)
				{
					pDataArray = tpChildArray[i].GetChildArray(&tCocoLoader);
					length = tpChildArray[i].GetChildNum();
					for (int i = 0; i < length; ++i)
					{
						CCTextureData *textureData = decodeTexture(&tCocoLoader, &pDataArray[i]);
						if (dataInfo->asyncStruct)
						{
							pthread_mutex_lock(&s_addDataMutex);
						}
						CCArmatureDataManager::sharedArmatureDataManager()->addTextureData(textureData->name.c_str(), textureData, dataInfo->filename.c_str());
						textureData->release();
						if (dataInfo->asyncStruct)
						{
							pthread_mutex_unlock(&s_addDataMutex);
						}
					}
				}
			}
			// Auto losprite file
			bool autoLoad = dataInfo->asyncStruct == NULL ? CCArmatureDataManager::sharedArmatureDataManager()->isAutoLoadSpriteFile() : dataInfo->asyncStruct->autoLoadSpriteFile;
			if (autoLoad)
			{
				for (int i = 0; i < nCount; ++i)
				{
					key = tpChildArray[i].GetName(&tCocoLoader);
					if( 0 != key.compare(CONFIG_FILE_PATH))
					{
						continue;
					}
					length = tpChildArray[i].GetChildNum();
					stExpCocoNode *pConfigFilePath = tpChildArray[i].GetChildArray(&tCocoLoader);
					for (int i = 0; i < length; i++)
					{
						const char *path = pConfigFilePath[i].GetValue(&tCocoLoader);
						if (path == NULL)
						{
							CCLOG("load CONFIG_FILE_PATH error.");
							return;
						}

						std::string filePath = path;
						filePath = filePath.erase(filePath.find_last_of("."));

						if (dataInfo->asyncStruct)
						{
							dataInfo->configFileQueue.push(filePath);
						}
						else
						{
							std::string plistPath = filePath + ".plist";
							std::string pngPath =  filePath + ".png";

							CCArmatureDataManager::sharedArmatureDataManager()->addSpriteFrameFromFile((dataInfo->baseFilePath + plistPath).c_str(), (dataInfo->baseFilePath + pngPath).c_str(), dataInfo->filename.c_str());
						}
					}
				}
			}
		}
	}
}

CCArmatureData* CCDataReaderHelper::decodeArmature(CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode, DataInfo *dataInfo)
{
	CCArmatureData *armatureData = new CCArmatureData();
	armatureData->init();
	stExpCocoNode *pAramtureDataArray = pCocoNode->GetChildArray(pCocoLoader);
	const char *name = pAramtureDataArray[2].GetValue(pCocoLoader); //DICTOOL->getStringValue_json(json, A_NAME);
	if(name != NULL)
	{
		armatureData->name = name;
	}

	float version = atof(pAramtureDataArray[1].GetValue(pCocoLoader));
	dataInfo->cocoStudioVersion = armatureData->dataVersion = version; //DICTOOL->getFloatValue_json(json, VERSION, 0.1f);

	int length = pAramtureDataArray[3].GetChildNum(); //DICTOOL->getArrayCount_json(json, BONE_DATA, 0); 
	stExpCocoNode *pBoneChildren = pAramtureDataArray[3].GetChildArray(pCocoLoader);
	stExpCocoNode* child;
	for (int i = 0; i < length; i++)
	{
		//const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(json, BONE_DATA, i); //json[BONE_DATA][i];
		child = &pBoneChildren[i];
		CCBoneData *boneData = decodeBone(pCocoLoader, child, dataInfo);
		armatureData->addBoneData(boneData);  
		boneData->release();
	}

	return armatureData;
}

CCBoneData* CCDataReaderHelper::decodeBone(CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode, DataInfo *dataInfo)
{
	CCBoneData *boneData = new CCBoneData();
	boneData->init();

	decodeNode(boneData, pCocoLoader, pCocoNode, dataInfo);

	int length = pCocoNode->GetChildNum();
	stExpCocoNode *pBoneChildren = pCocoNode->GetChildArray(pCocoLoader);
	stExpCocoNode* child;
	const char *str = NULL;
	std::string key;
	for (int i = 0; i < length; ++i)
	{
		child = &pBoneChildren[i];
		key = child->GetName(pCocoLoader);
		str = child->GetValue(pCocoLoader);
		if (key.compare(A_NAME) == 0)
		{
			 //DICTOOL->getStringValue_json(json, A_NAME);
			if(str != NULL)
			{
				boneData->name = str;
			}
		}
		else if (key.compare(A_PARENT) == 0)
		{
			 //DICTOOL->getStringValue_json(json, A_PARENT);
			if(str != NULL)
			{
				boneData->parentName = str;
			}
		}
		else if (key.compare(DISPLAY_DATA) == 0)
		{
			int count = child->GetChildNum();
			stExpCocoNode *pDisplayData = child->GetChildArray(pCocoLoader);
			for (int i = 0; i < count; ++i)
			{
				CCDisplayData *displayData = decodeBoneDisplay(pCocoLoader, &pDisplayData[i], dataInfo);
				if(displayData == NULL)
					continue;
				boneData->addDisplayData(displayData);
					displayData->release();
			}
		}
	}

	return boneData;
}

CCDisplayData* CCDataReaderHelper::decodeBoneDisplay(CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode, DataInfo *dataInfo)
{
	stExpCocoNode* children = pCocoNode->GetChildArray(pCocoLoader);
	stExpCocoNode* child = &children[1];
	const char *str = NULL;

	std::string key = child->GetName(pCocoLoader);
	str = child->GetValue(pCocoLoader);
	CCDisplayData *displayData = NULL;
	DisplayType displayType = CS_DISPLAY_SPRITE;

	if (key.compare(A_DISPLAY_TYPE) == 0)
	{
		str = child->GetValue(pCocoLoader);
		DisplayType displayType = (DisplayType)(atoi(str));

		int length = 0;
		switch (displayType)
		{
		case CS_DISPLAY_SPRITE:
			{
				displayData = new CCSpriteDisplayData();

				const char *name =  children[0].GetValue(pCocoLoader); 
				if(name != NULL)
				{
					((CCSpriteDisplayData *)displayData)->displayName = name;
				}
				stExpCocoNode *pSkinDataArray = children[2].GetChildArray(pCocoLoader);
				if (pSkinDataArray != NULL)
				{
					stExpCocoNode *pSkinData = &pSkinDataArray[0];
					if (pSkinData != NULL)
					{
						CCSpriteDisplayData *sdd = (CCSpriteDisplayData *)displayData;
						int length = pSkinData->GetChildNum();
						stExpCocoNode *SkinDataValue = pSkinData->GetChildArray(pCocoLoader);
						for (int i = 0; i < length; ++i)
						{
							key = SkinDataValue[i].GetName(pCocoLoader);
							str = SkinDataValue[i].GetValue(pCocoLoader);
							if (key.compare(A_X) == 0)
							{
								sdd->skinData.x = atof(str) * s_PositionReadScale; 
							}
							else if (key.compare(A_Y) == 0)
							{
								sdd->skinData.y = atof(str) * s_PositionReadScale; 
							}
							else if (key.compare(A_SCALE_X) == 0)
							{
								sdd->skinData.scaleX = atof(str); 
							}
							else if (key.compare(A_SCALE_Y) == 0)
							{
								sdd->skinData.scaleY = atof(str); 
							}
							else if (key.compare(A_SKEW_X) == 0)
							{
								sdd->skinData.skewX = atof(str); 
							}
							else if (key.compare(A_SKEW_Y) == 0)
							{
								sdd->skinData.skewY = atof(str); 
							}
						}

						sdd->skinData.x *= dataInfo->contentScale;
						sdd->skinData.y *= dataInfo->contentScale;
					}
				}
			}

			break;
		case CS_DISPLAY_ARMATURE:
			{
				displayData = new CCArmatureDisplayData();

				const char *name = pCocoNode[0].GetValue(pCocoLoader);
				if(name != NULL)
				{
					((CCArmatureDisplayData *)displayData)->displayName = name;
				}
			}
			break;
		case CS_DISPLAY_PARTICLE:
			{
				displayData = new CCParticleDisplayData();
				length = pCocoNode->GetChildNum();
				stExpCocoNode *pDisplayData = pCocoNode->GetChildArray(pCocoLoader);
				for (int i = 0; i < length; ++i)
				{
					key = pDisplayData[i].GetName(pCocoLoader);
                    str = pDisplayData[i].GetValue(pCocoLoader);
					if (key.compare(A_PLIST) == 0)
					{
                        const char *plist = str;
                        if(plist != NULL)
                        {
                            if (dataInfo->asyncStruct)
                            {
                                ((CCParticleDisplayData *)displayData)->displayName = dataInfo->asyncStruct->baseFilePath + plist;
                            }
                            else
                            {
                                ((CCParticleDisplayData *)displayData)->displayName = dataInfo->baseFilePath + plist;
                            }
                        }
					}
				}
			}
			break;
		default:
			displayData = new CCSpriteDisplayData();

			break;
		}
		displayData->displayType = displayType;
	}
	return displayData;
}

CCAnimationData* CCDataReaderHelper::decodeAnimation(CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode, DataInfo *dataInfo)
{
	CCAnimationData *aniData = new CCAnimationData();

	int length = pCocoNode->GetChildNum();
	stExpCocoNode *pAnimationData = pCocoNode->GetChildArray(pCocoLoader);
	const char *str = NULL;
	std::string key;
	stExpCocoNode* child;
	CCMovementData *movementData;
	for (int i = 0; i < length; ++i)
	{
		child = &pAnimationData[i];
		key = child->GetName(pCocoLoader);
		str = child->GetValue(pCocoLoader);
		if (key.compare(A_NAME) == 0)
		{
			if(str != NULL)
			{
				aniData->name = str;
			}
		}
		else if (key.compare(MOVEMENT_DATA) == 0)
		{
			int movcount = child->GetChildNum();
			stExpCocoNode* movArray =  child->GetChildArray(pCocoLoader);
			for( int movnum =0; movnum <movcount; movnum++)
			{
				movementData = decodeMovement(pCocoLoader, &movArray[movnum], dataInfo);
				aniData->addMovement(movementData);
				movementData->release();
			}
		}
	}
	return aniData;
}

CCMovementData* CCDataReaderHelper::decodeMovement(CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode, DataInfo *dataInfo)
{
	CCMovementData *movementData = new CCMovementData();
	movementData->scale = 1.0f;
	
	int length = pCocoNode->GetChildNum();
	stExpCocoNode *pMoveDataArray = pCocoNode->GetChildArray(pCocoLoader);

	const char *str = NULL;
	std::string key;
	stExpCocoNode* child;
	for (int i = 0; i < length; ++i)
	{
		child = &pMoveDataArray[i];
		key = child->GetName(pCocoLoader);
		str = child->GetValue(pCocoLoader);
		if (key.compare(A_NAME) == 0)
		{
			if(str != NULL)
			{
				movementData->name = str;
			}
		}
		else if (key.compare(A_LOOP) == 0)
		{
			movementData->loop = true;
			if(str != NULL)
			{
				if (strcmp("1", str) != 0)
				{
					movementData->loop = false;
				}
			}
		}
		else if (key.compare(A_DURATION_TWEEN) == 0)
		{
			movementData->durationTween = 0;
			if(str != NULL)
			{
				movementData->durationTween = atoi(str); 
			}
		}
		else if (key.compare(A_DURATION_TO) == 0)
		{
			movementData->durationTo = 0;
			if(str != NULL)
			{
				movementData->durationTo = atoi(str); 
			}
		}
		else if (key.compare(A_DURATION) == 0)
		{
			movementData->duration = 0;
			if(str != NULL)
			{
				movementData->duration = atoi(str); 
			}
		}
		else if (key.compare(A_MOVEMENT_SCALE) == 0)
		{
			movementData->scale = 1.0;
			if(str != NULL)
			{
				movementData->scale = atof(str); 
			}
		}
		else if (key.compare(A_TWEEN_EASING) == 0)
		{
			movementData->tweenEasing = Linear;
			if(str != NULL)
			{
				movementData->tweenEasing = (CCTweenType)(atoi(str)); 
			}
		}
		else if (key.compare(MOVEMENT_BONE_DATA) == 0)
		{
			int count = child->GetChildNum();
			stExpCocoNode *pMoveBoneData = child->GetChildArray(pCocoLoader);
			CCMovementBoneData *movementBoneData;
			for (int i = 0; i < count; ++i)
			{
				movementBoneData = decodeMovementBone(pCocoLoader, &pMoveBoneData[i],dataInfo);
				movementData->addMovementBoneData(movementBoneData);
				movementBoneData->release();
			}
		}
	}
	return movementData;
}

CCMovementBoneData* CCDataReaderHelper::decodeMovementBone(CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode, DataInfo *dataInfo)
{
	CCMovementBoneData *movementBoneData = new CCMovementBoneData();
	movementBoneData->init();

	int length = pCocoNode->GetChildNum();
	stExpCocoNode *pMovementBoneDataArray = pCocoNode->GetChildArray(pCocoLoader);
	stExpCocoNode* movebonechild;
	const char *str = NULL;
	for (int i = 0; i < length; ++i)
	{
		movebonechild = &pMovementBoneDataArray[i];
		std::string key = movebonechild->GetName(pCocoLoader);
		str = movebonechild->GetValue(pCocoLoader);
		if (key.compare(A_NAME) == 0)
		{
			if(str != NULL)
			{
				movementBoneData->name = str;
			}
		}
		else if (key.compare(A_MOVEMENT_DELAY) == 0)
		{
			if(str != NULL)
			{
				movementBoneData->delay = atof(str); 
			}
		}
		else if (key.compare(FRAME_DATA) == 0)
		{
			int count =movebonechild->GetChildNum();
			stExpCocoNode *pFrameDataArray = movebonechild->GetChildArray(pCocoLoader);
			for (int i = 0; i < count; ++i)
			{
				CCFrameData *frameData = decodeFrame(pCocoLoader, &pFrameDataArray[i], dataInfo);
				movementBoneData->addFrameData(frameData);
				frameData->release();

				if (dataInfo->cocoStudioVersion < VERSION_COMBINED)
				{
					frameData->frameID = movementBoneData->duration;
					movementBoneData->duration += frameData->duration;
				}
			}
		}
	}

	

	if (dataInfo->cocoStudioVersion < VERSION_CHANGE_ROTATION_RANGE)
	{
		//! Change rotation range from (-180 -- 180) to (-infinity -- infinity)
		CCFrameData **frames = (CCFrameData **)movementBoneData->frameList.data->arr;
		for (int i = movementBoneData->frameList.count() - 1; i >= 0; i--)
		{
			if (i > 0)
			{
				float difSkewX = frames[i]->skewX -  frames[i - 1]->skewX;
				float difSkewY = frames[i]->skewY -  frames[i - 1]->skewY;

				if (difSkewX < -M_PI || difSkewX > M_PI)
				{
					frames[i - 1]->skewX = difSkewX < 0 ? frames[i - 1]->skewX - 2 * M_PI : frames[i - 1]->skewX + 2 * M_PI;
				}

				if (difSkewY < -M_PI || difSkewY > M_PI)
				{
					frames[i - 1]->skewY = difSkewY < 0 ? frames[i - 1]->skewY - 2 * M_PI : frames[i - 1]->skewY + 2 * M_PI;
				}
			}
		}
	}


	if (dataInfo->cocoStudioVersion < VERSION_COMBINED)
	{
		if (movementBoneData->frameList.count() > 0)
		{
			CCFrameData *frameData = new CCFrameData();
			frameData->copy((CCFrameData *)movementBoneData->frameList.lastObject());
			movementBoneData->addFrameData(frameData);
			frameData->release();

			frameData->frameID = movementBoneData->duration;
		}
	}

	return movementBoneData;
}

CCFrameData* CCDataReaderHelper::decodeFrame(CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode, DataInfo *dataInfo)
{
	CCFrameData *frameData = new CCFrameData();

	decodeNode(frameData, pCocoLoader, pCocoNode, dataInfo);

	int length = pCocoNode->GetChildNum();
	stExpCocoNode *pFrameDataArray = pCocoNode->GetChildArray(pCocoLoader);
	const char *str = NULL;
	for (int i = 0; i < length; ++i)
	{
		std::string key = pFrameDataArray[i].GetName(pCocoLoader);
		str = pFrameDataArray[i].GetValue(pCocoLoader);
		if (key.compare(A_TWEEN_EASING) == 0)
		{
			frameData->tweenEasing = Linear;
			if(str != NULL)
			{
				frameData->tweenEasing = (CCTweenType)(atoi(str));
			}
		}
		else if (key.compare(A_DISPLAY_INDEX) == 0)
		{
			if(str != NULL)
			{
				frameData->displayIndex = atoi(str); 
			}
		}
		else if (key.compare(A_BLEND_SRC) == 0)
		{
			if(str != NULL)
			{
				frameData->blendFunc.src = (GLenum)(atoi(str));
			}
		}
		else if (key.compare(A_BLEND_DST) == 0)
		{
			if(str != NULL)
			{
				frameData->blendFunc.dst = (GLenum)(atoi(str));
			}
		}
		else if (key.compare(A_TWEEN_FRAME) == 0)
		{
			frameData->isTween = true;
			if(str != NULL)
			{
				if (strcmp("1", str) != 0)
				{
					frameData->isTween = false; 
				}
			}
		}
		else if (key.compare(A_EVENT) == 0)
		{
			if(str != NULL)
			{
				frameData->strEvent = str;
			}
		}
		else if (key.compare(A_DURATION) == 0)
		{
			if (dataInfo->cocoStudioVersion < VERSION_COMBINED)
			{
				frameData->duration = 1;
				if(str != NULL)
				{
					frameData->duration = atoi(str);
				}
			}
		}
		else if (key.compare(A_FRAME_INDEX) == 0)
		{
			if (dataInfo->cocoStudioVersion >= VERSION_COMBINED)
			{
				if(str != NULL)
				{
					frameData->frameID = atoi(str);
				}
			}
		}
		else if (key.compare(A_EASING_PARAM) == 0)
		{
			int count = pFrameDataArray[i].GetChildNum();
			if (count != 0 )
			{
				frameData->easingParams = new float[count];
				stExpCocoNode *pFrameData = pFrameDataArray[i].GetChildArray(pCocoLoader);
				for (int i = 0; i < count; ++i)
				{
					str = pFrameData[i].GetValue(pCocoLoader);
					if (str != NULL)
					{
						frameData->easingParams[i] = atof(str);
					}
				}
			}
			
		}
	}

	return frameData;
}

CCTextureData* CCDataReaderHelper::decodeTexture(CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode)
{
	CCTextureData *textureData = new CCTextureData();
	textureData->init();

	if(pCocoNode == NULL)
	{
		return textureData;
	}

	int length = pCocoNode->GetChildNum();
	stExpCocoNode *pTextureDataArray = pCocoNode->GetChildArray(pCocoLoader);
	const char *str = NULL;
	for (int i = 0; i < length; ++i)
	{
		std::string key = pTextureDataArray[i].GetName(pCocoLoader);
		str = pTextureDataArray[i].GetValue(pCocoLoader);
		if (key.compare(A_NAME) == 0)
		{
			if(str != NULL)
			{
				textureData->name = str;
			}
		}
		else if (key.compare(A_WIDTH) == 0)
		{
			if(str != NULL)
			{
				textureData->width = atof(str);
			}
		}
		else if (key.compare(A_HEIGHT) == 0)
		{
			if(str != NULL)
			{
				textureData->height = atof(str);
			}
		}
		else if (key.compare(A_PIVOT_X) == 0)
		{
			if(str != NULL)
			{
				textureData->pivotX = atof(str);
			}
		}
		else if (key.compare(A_PIVOT_Y) == 0)
		{
			if(str != NULL)
			{
				textureData->pivotY = atof(str);
			}
		}
		else if (key.compare(CONTOUR_DATA) == 0)
		{
			int count = pTextureDataArray[i].GetChildNum();
			stExpCocoNode *pContourArray = pTextureDataArray[i].GetChildArray(pCocoLoader);
			for (int i = 0; i < count; ++i)
			{
				CCContourData *contourData = decodeContour(pCocoLoader, &pContourArray[i]);
				textureData->contourDataList.addObject(contourData);
				contourData->release();
			}
		}
	}
	return textureData;
}

CCContourData* CCDataReaderHelper::decodeContour(CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode)
{
	CCContourData *contourData = new CCContourData();
	contourData->init();

	int length = pCocoNode->GetChildNum();
	stExpCocoNode *verTexPointArray = pCocoNode->GetChildArray(pCocoLoader);
	const char *str = NULL;
	for (int i = 0; i < length; ++i)
	{
		std::string key = verTexPointArray[i].GetName(pCocoLoader);
		str = verTexPointArray[i].GetValue(pCocoLoader);
		if (key.compare(VERTEX_POINT) == 0)
		{
			int count = verTexPointArray[i].GetChildNum();
			stExpCocoNode *pVerTexPointArray = verTexPointArray[i].GetChildArray(pCocoLoader);
			for (int i = count - 1; i >= 0; --i)
			{
				int num = pVerTexPointArray[i].GetChildNum();
				stExpCocoNode *pVerTexPoint = pVerTexPointArray[i].GetChildArray(pCocoLoader);
				CCContourVertex2 *vertex = new CCContourVertex2(0, 0);
				vertex->x = atof(pVerTexPoint[0].GetValue(pCocoLoader));
				vertex->y = atof(pVerTexPoint[1].GetValue(pCocoLoader));
				contourData->vertexList.addObject(vertex);
					vertex->release();
			}
			break;
		}
	}
	return contourData;
}

void CCDataReaderHelper::decodeNode(CCBaseData *node, CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode, DataInfo *dataInfo)
{
	int length = pCocoNode->GetChildNum();
	stExpCocoNode *NodeArray = pCocoNode->GetChildArray(pCocoLoader);
	const char *str = NULL;

	bool isVersionL = dataInfo->cocoStudioVersion < VERSION_COLOR_READING;
	stExpCocoNode* child;
	for (int i = 0; i < length; ++i)
	{
		child = &NodeArray[i];
		std::string key = child->GetName(pCocoLoader);
		str = child->GetValue(pCocoLoader);
		if (key.compare(A_X) == 0)
		{
			node->x = atof(str) * dataInfo->contentScale;
		}
		else if (key.compare(A_Y) == 0)
		{
			node->y = atof(str) * dataInfo->contentScale;
		}
		else if (key.compare(A_Z) == 0)
		{
			node->zOrder = atoi(str);
		}
		else if (key.compare(A_SKEW_X) == 0)
		{
			node->skewX = atof(str);
		}
		else if (key.compare(A_SKEW_Y) == 0)
		{
			node->skewY = atof(str);
		}
		else if (key.compare(A_SCALE_X) == 0)
		{
			node->scaleX = atof(str);
		}
		else if (key.compare(A_SCALE_Y) == 0)
		{
			node->scaleY = atof(str);
		}
		else if (key.compare(COLOR_INFO) == 0)
		{
			if (!isVersionL)
			{
				if (child->GetType(pCocoLoader) == rapidjson::kObjectType)
				{
					if(child->GetChildNum() == 4)
					{
						stExpCocoNode *ChildArray = child->GetChildArray(pCocoLoader);

						node->a = atoi(ChildArray[0].GetValue(pCocoLoader));
						node->r = atoi(ChildArray[1].GetValue(pCocoLoader));
						node->g = atoi(ChildArray[2].GetValue(pCocoLoader));
						node->b = atoi(ChildArray[3].GetValue(pCocoLoader));
					}

				}


				
				node->isUseColorInfo = true;
			}
		}
	}

	if (isVersionL)
	{
		int colorcoount = NodeArray[0].GetChildNum();
		if(colorcoount>0)
		{
			
			if (NodeArray[0].GetType(pCocoLoader) == rapidjson::kObjectType)
			{
				if(NodeArray[0].GetChildNum() == 4)
				{
					stExpCocoNode *ChildArray = NodeArray[0].GetChildArray(pCocoLoader);

					node->a = atoi(ChildArray[0].GetValue(pCocoLoader));
					node->r = atoi(ChildArray[1].GetValue(pCocoLoader));
					node->g = atoi(ChildArray[2].GetValue(pCocoLoader));
					node->b = atoi(ChildArray[3].GetValue(pCocoLoader));
				}
			}

			node->isUseColorInfo = true;
		}
	}
}

NS_CC_EXT_END
