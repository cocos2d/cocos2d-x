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

// static const char *A_VERT = "vert";
// static const char *A_FRAG = "frag";
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
static const char *A_TWEEN_FRAME = "tweenFrame";
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

static const char *CONFIG_FILE_PATH = "config_file_path";


NS_CC_EXT_ARMATURE_BEGIN


	std::vector<std::string> s_arrConfigFileList;
float s_PositionReadScale = 1;
static float s_FlashToolVersion = VERSION_2_0;
static float s_CocoStudioVersion = VERSION_COMBINED;

static std::string s_BasefilePath = "";

DataReaderHelper *DataReaderHelper::_dataReaderHelper = NULL;



//! Async load
void DataReaderHelper::loadData()
{
    AsyncStruct *pAsyncStruct = NULL;

    while (true)
    {
        // create autorelease pool for iOS
        Thread thread;
        thread.createAutoreleasePool();

        std::queue<AsyncStruct *> *pQueue = _asyncStructQueue;
        _asyncStructQueueMutex.lock(); // get async struct from queue
        if (pQueue->empty())
        {
            _asyncStructQueueMutex.unlock();
            if (need_quit)
            {
                break;
            }
            else
            {
				std::unique_lock<std::mutex> lk(_sleepMutex);
				_sleepCondition.wait(lk);
                continue;
            }
        }
        else
        {
            pAsyncStruct = pQueue->front();
            pQueue->pop();
            _asyncStructQueueMutex.unlock();
        }

        // generate image info
        DataInfo *pDataInfo = new DataInfo();
        pDataInfo->asyncStruct = pAsyncStruct;

        if (pAsyncStruct->configType == DragonBone_XML)
        {
            DataReaderHelper::addDataFromCache(pAsyncStruct->fileContent.c_str(), pDataInfo);
        }
        else if(pAsyncStruct->configType == CocoStudio_JSON)
        {
            DataReaderHelper::addDataFromJsonCache(pAsyncStruct->fileContent.c_str(), pDataInfo);
        }

        // put the image info into the queue
        _dataInfoMutex.lock();
        _dataQueue->push(pDataInfo);
        _dataInfoMutex.unlock();
    }

    if( _asyncStructQueue != NULL )
    {
        delete _asyncStructQueue;
        _asyncStructQueue = NULL;
        delete _dataQueue;
        _dataQueue = NULL;
    }
}


DataReaderHelper *DataReaderHelper::getInstance()
{
    if(!_dataReaderHelper)
    {
        _dataReaderHelper = new DataReaderHelper();
    }

    return _dataReaderHelper;
}

void DataReaderHelper::setPositionReadScale(float scale)
{
    s_PositionReadScale = scale;
}

float DataReaderHelper::getPositionReadScale()
{
    return s_PositionReadScale;
}


void DataReaderHelper::purge()
{
    DataReaderHelper::clear();
    CC_SAFE_RELEASE_NULL(_dataReaderHelper);
}

void DataReaderHelper::clear()
{
    s_arrConfigFileList.clear();
}

DataReaderHelper::DataReaderHelper()
	: _loadingThread(nullptr)
	, _asyncStructQueue(nullptr)
	, _dataQueue(nullptr)
	, need_quit(false)
	, _asyncRefCount(0)
	, _asyncRefTotalCount(0)
{

}

DataReaderHelper::~DataReaderHelper()
{
    need_quit = true;

	_sleepCondition.notify_one();
	if (_loadingThread) _loadingThread->join();

	CC_SAFE_DELETE(_loadingThread);
	_dataReaderHelper = NULL;
}

void DataReaderHelper::addDataFromFile(const char *filePath)
{
    /*
    * Check if file is already added to ArmatureDataManager, if then return.
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
        s_BasefilePath = s_BasefilePath.substr(0, pos + 1);
    }
    else
    {
        s_BasefilePath = "";
    }


    std::string filePathStr =  filePath;
    size_t startPos = filePathStr.find_last_of(".");
    std::string str = &filePathStr[startPos];

    unsigned long size;
    std::string fullPath = CCFileUtils::getInstance()->fullPathForFilename(filePath);
    const char *pFileContent = (char *)CCFileUtils::getInstance()->getFileData(fullPath.c_str() , "r", &size);

    if (str.compare(".xml") == 0)
    {
        DataReaderHelper::addDataFromCache(pFileContent);
    }
    else if(str.compare(".json") == 0 || str.compare(".ExportJson") == 0)
    {
        DataReaderHelper::addDataFromJsonCache(pFileContent);
    }
}

void DataReaderHelper::addDataFromFileAsync(const char *filePath, Object *target, SEL_SCHEDULE selector)
{
    /*
    * Check if file is already added to ArmatureDataManager, if then return.
    */
    for(unsigned int i = 0; i < s_arrConfigFileList.size(); i++)
    {
        if (s_arrConfigFileList[i].compare(filePath) == 0)
        {
            if (target && selector)
            {
                if (_asyncRefTotalCount == 0 && _asyncRefCount == 0)
                {
                    (target->*selector)(1);
                }
                else
                {
                    (target->*selector)((_asyncRefTotalCount - _asyncRefCount) / (float)_asyncRefTotalCount);
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
        s_BasefilePath = s_BasefilePath.substr(0, pos + 1);
    }
    else
    {
        s_BasefilePath = "";
    }


    // lazy init
    if (_asyncStructQueue == NULL)
    {
        _asyncStructQueue = new std::queue<AsyncStruct *>();
        _dataQueue = new std::queue<DataInfo *>();

		// create a new thread to load images
		_loadingThread = new std::thread(&DataReaderHelper::loadData, this);

        need_quit = false;
    }

    if (0 == _asyncRefCount)
    {
		Director::getInstance()->getScheduler()->scheduleSelector(schedule_selector(DataReaderHelper::addDataAsyncCallBack), this, 0, false);
    }

    ++_asyncRefCount;
    ++_asyncRefTotalCount;

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
    data->autoLoadSpriteFile = ArmatureDataManager::getInstance()->isAutoLoadSpriteFile();


    std::string filePathStr =  filePath;
    size_t startPos = filePathStr.find_last_of(".");
    std::string str = &filePathStr[startPos];

    std::string fullPath = CCFileUtils::getInstance()->fullPathForFilename(filePath);
    unsigned long size;
    data->fileContent = (char *)CCFileUtils::getInstance()->getFileData(fullPath.c_str() , "r", &size);

    if (str.compare(".xml") == 0)
    {
        data->configType = DragonBone_XML;
    }
    else if(str.compare(".json") == 0 || str.compare(".ExportJson") == 0)
    {
        data->configType = CocoStudio_JSON;
    }


    // add async struct into queue
    _asyncStructQueueMutex.lock();
    _asyncStructQueue->push(data);
    _asyncStructQueueMutex.unlock();

    _sleepCondition.notify_one();
}

void DataReaderHelper::addDataAsyncCallBack(float dt)
{
    // the data is generated in loading thread
    std::queue<DataInfo *> *dataQueue = _dataQueue;

    _dataInfoMutex.lock();
    if (dataQueue->empty())
    {
        _dataInfoMutex.unlock();
    }
    else
    {
        DataInfo *pDataInfo = dataQueue->front();
        dataQueue->pop();
        _dataInfoMutex.unlock();

        AsyncStruct *pAsyncStruct = pDataInfo->asyncStruct;

        while (!pDataInfo->configFileQueue.empty())
        {
            std::string configPath = pDataInfo->configFileQueue.front();
            ArmatureDataManager::getInstance()->addSpriteFrameFromFile((pAsyncStruct->baseFilePath + configPath + ".plist").c_str(), (pAsyncStruct->baseFilePath + configPath + ".png").c_str());
            pDataInfo->configFileQueue.pop();
        }


        Object *target = pAsyncStruct->target;
        SEL_SCHEDULE selector = pAsyncStruct->selector;

        --_asyncRefCount;

        if (target && selector)
        {
            (target->*selector)((_asyncRefTotalCount - _asyncRefCount) / (float)_asyncRefTotalCount);
            target->release();
        }


        delete pAsyncStruct;
        delete pDataInfo;

        if (0 == _asyncRefCount)
        {
            _asyncRefTotalCount = 0;
            CCDirector::getInstance()->getScheduler()->unscheduleSelector(schedule_selector(DataReaderHelper::addDataAsyncCallBack), this);
        }
    }
}






void DataReaderHelper::addDataFromCache(const char *pFileContent, DataInfo *dataInfo)
{
    tinyxml2::XMLDocument document;
    document.Parse(pFileContent);

    tinyxml2::XMLElement *root = document.RootElement();
    CCASSERT(root, "XML error  or  XML is empty.");

    root->QueryFloatAttribute(VERSION, &s_FlashToolVersion);


    /*
    * Begin decode armature data from xml
    */
    tinyxml2::XMLElement *armaturesXML = root->FirstChildElement(ARMATURES);
    tinyxml2::XMLElement *armatureXML = armaturesXML->FirstChildElement(ARMATURE);
    while(armatureXML)
    {
        ArmatureData *armatureData = DataReaderHelper::decodeArmature(armatureXML);

        if (dataInfo)
        {
            _dataReaderHelper->_addDataMutex.lock();
        }
        ArmatureDataManager::getInstance()->addArmatureData(armatureData->name.c_str(), armatureData);
        armatureData->release();
        if (dataInfo)
        {
            _dataReaderHelper->_addDataMutex.unlock();
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
        AnimationData *animationData = DataReaderHelper::decodeAnimation(animationXML);
        if (dataInfo)
        {
            _dataReaderHelper->_addDataMutex.lock();
        }
        ArmatureDataManager::getInstance()->addAnimationData(animationData->name.c_str(), animationData);
        animationData->release();
        if (dataInfo)
        {
            _dataReaderHelper->_addDataMutex.unlock();
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
        TextureData *textureData = DataReaderHelper::decodeTexture(textureXML);

        if (dataInfo)
        {
            _dataReaderHelper->_addDataMutex.lock();
        }
        ArmatureDataManager::getInstance()->addTextureData(textureData->name.c_str(), textureData);
        textureData->release();
        if (dataInfo)
        {
            _dataReaderHelper->_addDataMutex.unlock();
        }
        textureXML = textureXML->NextSiblingElement(SUB_TEXTURE);
    }
}

ArmatureData *DataReaderHelper::decodeArmature(tinyxml2::XMLElement *armatureXML)
{
    ArmatureData *armatureData = new ArmatureData();
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

        BoneData *boneData = decodeBone(boneXML, parentXML);
        armatureData->addBoneData(boneData);
        boneData->release();

        boneXML = boneXML->NextSiblingElement(BONE);
    }

    return armatureData;
}

BoneData *DataReaderHelper::decodeBone(tinyxml2::XMLElement *boneXML, tinyxml2::XMLElement *parentXml)
{
    BoneData *boneData = new BoneData();
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
        DisplayData *displayData = decodeBoneDisplay(displayXML);
        boneData->addDisplayData(displayData);
        displayData->release();

        displayXML = displayXML->NextSiblingElement(DISPLAY);
    }

    return boneData;
}

DisplayData *DataReaderHelper::decodeBoneDisplay(tinyxml2::XMLElement *displayXML)
{
    int _isArmature = 0;

    DisplayData *displayData;

    if( displayXML->QueryIntAttribute(A_IS_ARMATURE, &(_isArmature)) == tinyxml2::XML_SUCCESS )
    {
        if(!_isArmature)
        {
            displayData = new SpriteDisplayData();
            displayData->displayType  = CS_DISPLAY_SPRITE;
        }
        else
        {
            displayData = new ArmatureDisplayData();
            displayData->displayType  = CS_DISPLAY_ARMATURE;
        }

    }
    else
    {
        displayData = new SpriteDisplayData();
        displayData->displayType  = CS_DISPLAY_SPRITE;
    }


    if(displayXML->Attribute(A_NAME) != NULL )
    {
        if(!_isArmature)
        {
            ((SpriteDisplayData *)displayData)->displayName = displayXML->Attribute(A_NAME);
        }
        else
        {
            ((ArmatureDisplayData *)displayData)->displayName = displayXML->Attribute(A_NAME);
        }

    }

    return displayData;
}

AnimationData *DataReaderHelper::decodeAnimation(tinyxml2::XMLElement *animationXML)
{
    AnimationData *aniData =  new AnimationData();

    const char	*name = animationXML->Attribute(A_NAME);

    ArmatureData *armatureData = ArmatureDataManager::getInstance()->getArmatureData(name);

    aniData->name = name;

    tinyxml2::XMLElement *movementXML = animationXML->FirstChildElement(MOVEMENT);

    while( movementXML )
    {
        MovementData *movementData = decodeMovement(movementXML, armatureData);
        aniData->addMovement(movementData);
        movementData->release();

        movementXML = movementXML->NextSiblingElement(MOVEMENT);

    }

    return aniData;
}

MovementData *DataReaderHelper::decodeMovement(tinyxml2::XMLElement *movementXML, ArmatureData *armatureData)
{
    MovementData *movementData = new MovementData();

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


        BoneData *boneData = (BoneData *)armatureData->getBoneData(boneName);

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

        MovementBoneData *moveBoneData = decodeMovementBone(movBoneXml, parentXml, boneData);
        movementData->addMovementBoneData(moveBoneData);
        moveBoneData->release();

        movBoneXml = movBoneXml->NextSiblingElement(BONE);
    }

    return movementData;
}


MovementBoneData *DataReaderHelper::decodeMovementBone(tinyxml2::XMLElement *movBoneXml, tinyxml2::XMLElement *parentXml, BoneData *boneData)
{
    MovementBoneData *movBoneData = new MovementBoneData();
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

        FrameData *frameData = decodeFrame( frameXML, parentFrameXML, boneData);
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
    FrameData *frameData = new FrameData();
    frameData->copy((FrameData *)movBoneData->frameList.getLastObject());
    frameData->frameID = movBoneData->duration;
    movBoneData->addFrameData(frameData);
    frameData->release();

    return movBoneData;
}

FrameData *DataReaderHelper::decodeFrame(tinyxml2::XMLElement *frameXML,  tinyxml2::XMLElement *parentFrameXml, BoneData *boneData)
{
    float x, y, scale_x, scale_y, skew_x, skew_y = 0;
    int duration, displayIndex, zOrder, tweenEasing, blendType = 0;

    FrameData *frameData = new FrameData();

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
        frameData->blendType = (BlendType)blendType;
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
        BaseData helpNode;
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

        TransformHelp::transformFromParent(*frameData, helpNode);
    }
    return frameData;
}

TextureData *DataReaderHelper::decodeTexture(tinyxml2::XMLElement *textureXML)
{
    TextureData *textureData = new TextureData();
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
        ContourData *contourData = decodeContour(contourXML);
        textureData->addContourData(contourData);
        contourData->release();

        contourXML = contourXML->NextSiblingElement(CONTOUR);
    }

    return textureData;
}

ContourData *DataReaderHelper::decodeContour(tinyxml2::XMLElement *contourXML)
{
    ContourData *contourData = new ContourData();
    contourData->init();

    tinyxml2::XMLElement *vertexDataXML = contourXML->FirstChildElement(CONTOUR_VERTEX);

    while (vertexDataXML)
    {
        ContourVertex2 *vertex = new ContourVertex2(0, 0);
        vertex->release();

        vertexDataXML->QueryFloatAttribute(A_X, &vertex->x);
        vertexDataXML->QueryFloatAttribute(A_Y, &vertex->y);

        vertex->y = -vertex->y;
        contourData->vertexList.addObject(vertex);

        vertexDataXML = vertexDataXML->NextSiblingElement(CONTOUR_VERTEX);
    }

    return contourData;
}



void DataReaderHelper::addDataFromJsonCache(const char *fileContent, DataInfo *dataInfo)
{
    cs::JsonDictionary json;
    json.initWithDescription(fileContent);

    // Decode armatures
    int length = json.getArrayItemCount(ARMATURE_DATA);
    for (int i = 0; i < length; i++)
    {
        cs::JsonDictionary *armatureDic = json.getSubItemFromArray(ARMATURE_DATA, i);
        ArmatureData *armatureData = decodeArmature(*armatureDic);

        if (dataInfo)
        {
            _dataReaderHelper->_addDataMutex.lock();
        }
        ArmatureDataManager::getInstance()->addArmatureData(armatureData->name.c_str(), armatureData);
        armatureData->release();
        if (dataInfo)
        {
            _dataReaderHelper->_addDataMutex.unlock();
        }
        delete armatureDic;
    }

    // Decode animations
    length = json.getArrayItemCount(ANIMATION_DATA);
    for (int i = 0; i < length; i++)
    {
        cs::JsonDictionary *animationDic = json.getSubItemFromArray(ANIMATION_DATA, i);
        AnimationData *animationData = decodeAnimation(*animationDic);

        if (dataInfo)
        {
            _dataReaderHelper->_addDataMutex.lock();
        }
        ArmatureDataManager::getInstance()->addAnimationData(animationData->name.c_str(), animationData);
        animationData->release();
        if (dataInfo)
        {
            _dataReaderHelper->_addDataMutex.unlock();
        }
        delete animationDic;
    }

    // Decode textures
    length = json.getArrayItemCount(TEXTURE_DATA);
    for (int i = 0; i < length; i++)
    {
        cs::JsonDictionary *textureDic = json.getSubItemFromArray(TEXTURE_DATA, i);
        TextureData *textureData = decodeTexture(*textureDic);

        if (dataInfo)
        {
            _dataReaderHelper->_addDataMutex.lock();
        }
        ArmatureDataManager::getInstance()->addTextureData(textureData->name.c_str(), textureData);
        textureData->release();
        if (dataInfo)
        {
            _dataReaderHelper->_addDataMutex.unlock();
        }
        delete textureDic;
    }

    // Auto load sprite file
    bool autoLoad = dataInfo == NULL ? ArmatureDataManager::getInstance()->isAutoLoadSpriteFile() : dataInfo->asyncStruct->autoLoadSpriteFile;
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

                ArmatureDataManager::getInstance()->addSpriteFrameFromFile((s_BasefilePath + plistPath).c_str(), (s_BasefilePath + pngPath).c_str());
            }
        }
    }
}

ArmatureData *DataReaderHelper::decodeArmature(cs::JsonDictionary &json)
{
    ArmatureData *armatureData = new ArmatureData();
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
        cs::JsonDictionary *dic = json.getSubItemFromArray(BONE_DATA, i);
        BoneData *boneData = decodeBone(*dic);
        armatureData->addBoneData(boneData);
        boneData->release();

        delete dic;
    }

    return armatureData;
}

BoneData *DataReaderHelper::decodeBone(cs::JsonDictionary &json)
{
    BoneData *boneData = new BoneData();
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
        cs::JsonDictionary *dic = json.getSubItemFromArray(DISPLAY_DATA, i);
        DisplayData *displayData = decodeBoneDisplay(*dic);
        boneData->addDisplayData(displayData);
        displayData->release();

        delete dic;
    }

    return boneData;
}

DisplayData *DataReaderHelper::decodeBoneDisplay(cs::JsonDictionary &json)
{
    DisplayType displayType = (DisplayType)json.getItemIntValue(A_DISPLAY_TYPE, CS_DISPLAY_SPRITE);

    DisplayData *displayData = NULL;

    switch (displayType)
    {
    case CS_DISPLAY_SPRITE:
    {
        displayData = new SpriteDisplayData();

        const char *name = json.getItemStringValue(A_NAME);
        if(name != NULL)
        {
            ((SpriteDisplayData *)displayData)->displayName = name;
        }

        cs::JsonDictionary *dic = json.getSubItemFromArray(SKIN_DATA, 0);
        if (dic != NULL)
        {
            SpriteDisplayData *sdd = (SpriteDisplayData *)displayData;
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
        displayData = new ArmatureDisplayData();

        const char *name = json.getItemStringValue(A_NAME);
        if(name != NULL)
        {
            ((ArmatureDisplayData *)displayData)->displayName = name;
        }
    }
    break;
    case CS_DISPLAY_PARTICLE:
    {
        displayData = new ParticleDisplayData();

        const char *plist = json.getItemStringValue(A_PLIST);
        if(plist != NULL)
        {
            ((ParticleDisplayData *)displayData)->plist = s_BasefilePath + plist;
        }
    }
    break;
    default:
        displayData = new SpriteDisplayData();

        break;
    }


    displayData->displayType = displayType;

    return displayData;
}

AnimationData *DataReaderHelper::decodeAnimation(cs::JsonDictionary &json)
{
    AnimationData *aniData = new AnimationData();

    const char *name = json.getItemStringValue(A_NAME);
    if(name != NULL)
    {
        aniData->name = name;
    }

    int length = json.getArrayItemCount(MOVEMENT_DATA);

    for (int i = 0; i < length; i++)
    {
        cs::JsonDictionary *dic = json.getSubItemFromArray(MOVEMENT_DATA, i);
        MovementData *movementData = decodeMovement(*dic);
        aniData->addMovement(movementData);
        movementData->release();

        delete dic;
    }

    return aniData;
}

MovementData *DataReaderHelper::decodeMovement(cs::JsonDictionary &json)
{
    MovementData *movementData = new MovementData();

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
        cs::JsonDictionary *dic = json.getSubItemFromArray(MOVEMENT_BONE_DATA, i);
        MovementBoneData *movementBoneData = decodeMovementBone(*dic);
        movementData->addMovementBoneData(movementBoneData);
        movementBoneData->release();

        delete dic;
    }

    return movementData;
}

MovementBoneData *DataReaderHelper::decodeMovementBone(cs::JsonDictionary &json)
{
    MovementBoneData *movementBoneData = new MovementBoneData();
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
        cs::JsonDictionary *dic = json.getSubItemFromArray(FRAME_DATA, i);
        FrameData *frameData = decodeFrame(*dic);

        movementBoneData->addFrameData(frameData);
        frameData->release();

        if (s_CocoStudioVersion < VERSION_COMBINED)
        {
            frameData->frameID = movementBoneData->duration;
            movementBoneData->duration += frameData->duration;
        }

        delete dic;
    }


	if (s_CocoStudioVersion < VERSION_CHANGE_ROTATION_RANGE)
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

    if (s_CocoStudioVersion < VERSION_COMBINED)
    {
        if (movementBoneData->frameList.count() > 0)
        {
            FrameData *frameData = new FrameData();
            frameData->copy((FrameData *)movementBoneData->frameList.getLastObject());
            movementBoneData->addFrameData(frameData);
            frameData->release();

            frameData->frameID = movementBoneData->duration;
        }
    }

    return movementBoneData;
}

FrameData *DataReaderHelper::decodeFrame(cs::JsonDictionary &json)
{
    FrameData *frameData = new FrameData();

    decodeNode(frameData, json);

    frameData->tweenEasing = (CCTweenType)json.getItemIntValue(A_TWEEN_EASING, Linear);
    frameData->displayIndex = json.getItemIntValue(A_DISPLAY_INDEX, 0);
    frameData->blendType = (BlendType)json.getItemIntValue(A_BLEND_TYPE, 0);
	frameData->isTween = (bool)json.getItemBoolvalue(A_TWEEN_FRAME, true);

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

TextureData *DataReaderHelper::decodeTexture(cs::JsonDictionary &json)
{
    TextureData *textureData = new TextureData();
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
        cs::JsonDictionary *dic = json.getSubItemFromArray(CONTOUR_DATA, i);
        ContourData *contourData = decodeContour(*dic);
        textureData->contourDataList.addObject(contourData);
        contourData->release();

        delete dic;
    }

    return textureData;
}

ContourData *DataReaderHelper::decodeContour(cs::JsonDictionary &json)
{
    ContourData *contourData = new ContourData();
	contourData->init();

    int length = json.getArrayItemCount(VERTEX_POINT);
    for (int i = length - 1; i >= 0; i--)
    {
        cs::JsonDictionary *dic = json.getSubItemFromArray(VERTEX_POINT, i);

        ContourVertex2 *vertex = new ContourVertex2(0, 0);

        vertex->x = dic->getItemFloatValue(A_X, 0);
        vertex->y = dic->getItemFloatValue(A_Y, 0);

        contourData->vertexList.addObject(vertex);
        vertex->release();

        delete dic;
    }

    return contourData;
}

void DataReaderHelper::decodeNode(BaseData *node, cs::JsonDictionary &json)
{
    node->x = json.getItemFloatValue(A_X, 0) * s_PositionReadScale;
    node->y = json.getItemFloatValue(A_Y, 0) * s_PositionReadScale;
    node->zOrder = json.getItemIntValue(A_Z, 0);

    node->skewX = json.getItemFloatValue(A_SKEW_X, 0);
    node->skewY = json.getItemFloatValue(A_SKEW_Y, 0);
    node->scaleX = json.getItemFloatValue(A_SCALE_X, 1);
    node->scaleY = json.getItemFloatValue(A_SCALE_Y, 1);

    cs::JsonDictionary *colorDic = json.getSubItemFromArray(COLOR_INFO, 0);

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

NS_CC_EXT_ARMATURE_END
