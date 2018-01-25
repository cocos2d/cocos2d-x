/****************************************************************************
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#include "platform/CCFileUtils.h"
#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "base/ccUtils.h"

#include "tinyxml2.h"

#include "editor-support/cocostudio/CCDataReaderHelper.h"
#include "editor-support/cocostudio/CCArmatureDataManager.h"
#include "editor-support/cocostudio/CCTransformHelp.h"
#include "editor-support/cocostudio/CCUtilMath.h"
#include "editor-support/cocostudio/CCArmatureDefine.h"
#include "editor-support/cocostudio/CCDatas.h"

#include "editor-support/cocostudio/CocoLoader.h"


using namespace cocos2d;


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
static const char *A_EASING_PARAM = "twEP";
static const char *A_TWEEN_ROTATE = "twR";
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


static std::string readFileContent(const std::string& filename, bool binary) {
    auto fs = FileUtils::getInstance();
    std::string s;
    if (binary)
        fs->getContents(filename, &s);
    else
        s = fs->getStringFromFile(filename);
    return s;
};

namespace cocostudio {



float s_PositionReadScale = 1;

std::vector<std::string> DataReaderHelper::_configFileList;

DataReaderHelper *DataReaderHelper::_dataReaderHelper = nullptr;



//! Async load
void DataReaderHelper::loadData()
{
    AsyncStruct *pAsyncStruct = nullptr;

    while (true)
    {
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

        // generate data info
        DataInfo *pDataInfo = new (std::nothrow) DataInfo();
        pDataInfo->asyncStruct = pAsyncStruct;
        pDataInfo->filename = pAsyncStruct->filename;
        pDataInfo->baseFilePath = pAsyncStruct->baseFilePath;

        if (pAsyncStruct->configType == DragonBone_XML)
        {
            DataReaderHelper::addDataFromCache(pAsyncStruct->fileContent, pDataInfo);
        }
        else if(pAsyncStruct->configType == CocoStudio_JSON)
        {
            DataReaderHelper::addDataFromJsonCache(pAsyncStruct->fileContent, pDataInfo);
        }
        else if(pAsyncStruct->configType == CocoStudio_Binary)
        {
            DataReaderHelper::addDataFromBinaryCache(pAsyncStruct->fileContent.c_str(),pDataInfo);
        }

        // put the image info into the queue
        _dataInfoMutex.lock();
        _dataQueue->push(pDataInfo);
        _dataInfoMutex.unlock();
    }

    if( _asyncStructQueue != nullptr )
    {
        delete _asyncStructQueue;
        _asyncStructQueue = nullptr;
        delete _dataQueue;
        _dataQueue = nullptr;
    }
}


DataReaderHelper *DataReaderHelper::getInstance()
{
    if(!_dataReaderHelper)
    {
        _dataReaderHelper = new (std::nothrow) DataReaderHelper();
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
    _configFileList.clear();
    CC_SAFE_RELEASE_NULL(_dataReaderHelper);
}


DataReaderHelper::DataReaderHelper()
	: _loadingThread(nullptr)
	, _asyncRefCount(0)
	, _asyncRefTotalCount(0)
	, need_quit(false)
	, _asyncStructQueue(nullptr)
	, _dataQueue(nullptr)
{

}

DataReaderHelper::~DataReaderHelper()
{
    need_quit = true;

	_sleepCondition.notify_one();
	if (_loadingThread) _loadingThread->join();

	CC_SAFE_DELETE(_loadingThread);
	_dataReaderHelper = nullptr;
}

void DataReaderHelper::addDataFromFile(const std::string& filePath)
{
    /*
    * Check if file is already added to ArmatureDataManager, if then return.
    */
    for(unsigned int i = 0; i < _configFileList.size(); i++)
    {
        if (_configFileList[i] == filePath)
        {
            return;
        }
    }
    _configFileList.push_back(filePath);


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

    std::string fileExtension = cocos2d::FileUtils::getInstance()->getFileExtension(filePath);

    // Read content from file
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filePath);
    bool isbinaryfilesrc = fileExtension == ".csb";

    _dataReaderHelper->_getFileMutex.lock();
    std::string contentStr(readFileContent(fullPath, isbinaryfilesrc));
    _dataReaderHelper->_getFileMutex.unlock();

    DataInfo dataInfo;
    dataInfo.filename = filePath;
    dataInfo.asyncStruct = nullptr;
    dataInfo.baseFilePath = basefilePath;
    if (fileExtension == ".xml")
    {
        DataReaderHelper::addDataFromCache(contentStr, &dataInfo);
    }
    else if(fileExtension == ".json" || fileExtension == ".exportjson")
    {
        DataReaderHelper::addDataFromJsonCache(contentStr, &dataInfo);
    }
    else if(isbinaryfilesrc)
    {
        DataReaderHelper::addDataFromBinaryCache(contentStr.c_str(),&dataInfo);
    }
}

void DataReaderHelper::addDataFromFileAsync(const std::string& imagePath, const std::string& plistPath, const std::string& filePath, Ref *target, SEL_SCHEDULE selector)
{
    /*
    * Check if file is already added to ArmatureDataManager, if then return.
    */
    for(unsigned int i = 0; i < _configFileList.size(); i++)
    {
        if (_configFileList[i] == filePath)
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
    _configFileList.push_back(filePath);

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
    if (_asyncStructQueue == nullptr)
    {
        _asyncStructQueue = new std::queue<AsyncStruct *>();
        _dataQueue = new (std::nothrow) std::queue<DataInfo *>();

		// create a new thread to load images
		_loadingThread = new std::thread(&DataReaderHelper::loadData, this);

        need_quit = false;
    }

    if (0 == _asyncRefCount)
    {
        Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(DataReaderHelper::addDataAsyncCallBack), this, 0, false);
    }

    ++_asyncRefCount;
    ++_asyncRefTotalCount;

    if (target)
    {
        target->retain();
    }

    // generate async struct
    AsyncStruct *data = new (std::nothrow) AsyncStruct();
    data->filename = filePath;
    data->baseFilePath = basefilePath;
    data->target = target;
    data->selector = selector;
    data->autoLoadSpriteFile = ArmatureDataManager::getInstance()->isAutoLoadSpriteFile();

    data->imagePath = imagePath;
    data->plistPath = plistPath;

    std::string fileExtension = cocos2d::FileUtils::getInstance()->getFileExtension(filePath);
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filePath);

    bool isbinaryfilesrc = fileExtension == ".csb";

    // This only read exportJson file, it takes only a little time.
    // Large image files are loaded in DataReaderHelper::addDataFromJsonCache(dataInfo) asynchronously.
    _dataReaderHelper->_getFileMutex.lock();
    data->fileContent.assign(readFileContent(fullPath, isbinaryfilesrc));
    _dataReaderHelper->_getFileMutex.unlock();

    if (fileExtension == ".xml")
    {
        data->configType = DragonBone_XML;
    }
    else if(fileExtension == ".json" || fileExtension == ".exportjson")
    {
        data->configType = CocoStudio_JSON;
    }
    else if(isbinaryfilesrc)
    {
        data->configType = CocoStudio_Binary;
    }


    // add async struct into queue
    _asyncStructQueueMutex.lock();
    _asyncStructQueue->push(data);
    _asyncStructQueueMutex.unlock();

    _sleepCondition.notify_one();
}

void DataReaderHelper::addDataAsyncCallBack(float /*dt*/)
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


        if (pAsyncStruct->imagePath != "" && pAsyncStruct->plistPath != "")
        {
            _getFileMutex.lock();
            ArmatureDataManager::getInstance()->addSpriteFrameFromFile(pAsyncStruct->plistPath, pAsyncStruct->imagePath, pDataInfo->filename);
            _getFileMutex.unlock();
        }

        while (!pDataInfo->configFileQueue.empty())
        {
            std::string configPath = pDataInfo->configFileQueue.front();
            _getFileMutex.lock();
            ArmatureDataManager::getInstance()->addSpriteFrameFromFile((pAsyncStruct->baseFilePath + configPath + ".plist"), (pAsyncStruct->baseFilePath + configPath + ".png"), pDataInfo->filename);
            _getFileMutex.unlock();
            pDataInfo->configFileQueue.pop();
        }


        Ref* target = pAsyncStruct->target;
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
            Director::getInstance()->getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(DataReaderHelper::addDataAsyncCallBack), this);
        }
    }
}


void DataReaderHelper::removeConfigFile(const std::string& configFile)
{
    auto it_end = _configFileList.end();
    for (auto it = _configFileList.begin(); it != it_end; ++it)
    {
        if (*it == configFile)
        {
            _configFileList.erase(it);
            break;
        }
    }
}


void DataReaderHelper::addDataFromCache(const std::string& pFileContent, DataInfo *dataInfo)
{
    tinyxml2::XMLDocument document;
    document.Parse(pFileContent.c_str());

    tinyxml2::XMLElement *root = document.RootElement();
    CCASSERT(root, "XML error  or  XML is empty.");

    root->QueryFloatAttribute(VERSION, &dataInfo->flashToolVersion);


    /*
    * Begin decode armature data from xml
    */
    tinyxml2::XMLElement *armaturesXML = root->FirstChildElement(ARMATURES);
    tinyxml2::XMLElement *armatureXML = armaturesXML->FirstChildElement(ARMATURE);
    while(armatureXML)
    {
        ArmatureData *armatureData = DataReaderHelper::decodeArmature(armatureXML, dataInfo);

        if (dataInfo->asyncStruct)
        {
            _dataReaderHelper->_addDataMutex.lock();
        }
        ArmatureDataManager::getInstance()->addArmatureData(armatureData->name, armatureData, dataInfo->filename);
        armatureData->release();
        if (dataInfo->asyncStruct)
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
        AnimationData *animationData = DataReaderHelper::decodeAnimation(animationXML, dataInfo);
        if (dataInfo->asyncStruct)
        {
            _dataReaderHelper->_addDataMutex.lock();
        }
        ArmatureDataManager::getInstance()->addAnimationData(animationData->name, animationData, dataInfo->filename);
        animationData->release();
        if (dataInfo->asyncStruct)
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
        TextureData *textureData = DataReaderHelper::decodeTexture(textureXML, dataInfo);

        if (dataInfo->asyncStruct)
        {
            _dataReaderHelper->_addDataMutex.lock();
        }
        ArmatureDataManager::getInstance()->addTextureData(textureData->name, textureData, dataInfo->filename);
        textureData->release();
        if (dataInfo->asyncStruct)
        {
            _dataReaderHelper->_addDataMutex.unlock();
        }
        textureXML = textureXML->NextSiblingElement(SUB_TEXTURE);
    }
}

ArmatureData *DataReaderHelper::decodeArmature(tinyxml2::XMLElement *armatureXML, DataInfo *dataInfo)
{
    ArmatureData *armatureData = new (std::nothrow) ArmatureData();
    armatureData->init();

    armatureData->name = armatureXML->Attribute(A_NAME);


    tinyxml2::XMLElement *boneXML = armatureXML->FirstChildElement(BONE);

    while( boneXML )
    {
        /*
        *  If this bone have parent, then get the parent bone xml
        */
        const char *parentName = boneXML->Attribute(A_PARENT);
        tinyxml2::XMLElement *parentXML = nullptr;
        if (parentName)
        {
            parentXML = armatureXML->FirstChildElement(BONE);
            std::string parentNameStr = parentName;
            while (parentXML)
            {
                if (parentNameStr == parentXML->Attribute(A_NAME))
                {
                    break;
                }
                parentXML = parentXML->NextSiblingElement(BONE);
            }
        }

        BoneData *boneData = decodeBone(boneXML, parentXML, dataInfo);
        armatureData->addBoneData(boneData);
        boneData->release();

        boneXML = boneXML->NextSiblingElement(BONE);
    }

    return armatureData;
}

BoneData *DataReaderHelper::decodeBone(tinyxml2::XMLElement *boneXML, tinyxml2::XMLElement* /*parentXml*/, DataInfo *dataInfo)
{
    BoneData *boneData = new (std::nothrow) BoneData();
    boneData->init();

    std::string name = boneXML->Attribute(A_NAME);
    boneData->name = name;

    if( boneXML->Attribute(A_PARENT) != nullptr )
    {
        boneData->parentName = boneXML->Attribute(A_PARENT);
    }

    boneXML->QueryIntAttribute(A_Z, &boneData->zOrder);

    tinyxml2::XMLElement *displayXML = boneXML->FirstChildElement(DISPLAY);
    while(displayXML)
    {
        DisplayData *displayData = decodeBoneDisplay(displayXML, dataInfo);
        boneData->addDisplayData(displayData);
        displayData->release();

        displayXML = displayXML->NextSiblingElement(DISPLAY);
    }

    return boneData;
}

DisplayData *DataReaderHelper::decodeBoneDisplay(tinyxml2::XMLElement *displayXML, DataInfo* /*dataInfo*/)
{
    int _isArmature = 0;

    DisplayData *displayData;

    if( displayXML->QueryIntAttribute(A_IS_ARMATURE, &(_isArmature)) == tinyxml2::XML_SUCCESS )
    {
        if(!_isArmature)
        {
            displayData = new (std::nothrow) SpriteDisplayData();
            displayData->displayType  = CS_DISPLAY_SPRITE;
        }
        else
        {
            displayData = new (std::nothrow) ArmatureDisplayData();
            displayData->displayType  = CS_DISPLAY_ARMATURE;
        }

    }
    else
    {
        displayData = new (std::nothrow) SpriteDisplayData();
        displayData->displayType  = CS_DISPLAY_SPRITE;
    }


    if(displayXML->Attribute(A_NAME) != nullptr )
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

AnimationData *DataReaderHelper::decodeAnimation(tinyxml2::XMLElement *animationXML, DataInfo *dataInfo)
{
    AnimationData *aniData =  new AnimationData();

    const char	*name = animationXML->Attribute(A_NAME);

    ArmatureData *armatureData = ArmatureDataManager::getInstance()->getArmatureData(name);

    aniData->name = name;

    tinyxml2::XMLElement *movementXML = animationXML->FirstChildElement(MOVEMENT);

    while( movementXML )
    {
        MovementData *movementData = decodeMovement(movementXML, armatureData, dataInfo);
        aniData->addMovement(movementData);
        movementData->release();

        movementXML = movementXML->NextSiblingElement(MOVEMENT);

    }

    return aniData;
}

MovementData *DataReaderHelper::decodeMovement(tinyxml2::XMLElement *movementXML, ArmatureData *armatureData, DataInfo *dataInfo)
{
    MovementData *movementData = new (std::nothrow) MovementData();

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
        movementData->loop = (loop != 0);
    }

    const char *_easing = movementXML->Attribute(A_TWEEN_EASING);
    if(_easing != nullptr)
    {
        std::string str = _easing;
        if(str != FL_NAN)
        {
            if( movementXML->QueryIntAttribute(A_TWEEN_EASING, &(tweenEasing)) == tinyxml2::XML_SUCCESS)
            {
                movementData->tweenEasing = tweenEasing == 2 ? cocos2d::tweenfunc::Sine_EaseInOut : (TweenType)tweenEasing;
            }
        }
        else
        {
            movementData->tweenEasing  = cocos2d::tweenfunc::Linear;
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


        tinyxml2::XMLElement *parentXml = nullptr;
        if (!parentName.empty())
        {
            parentXml = movementXML->FirstChildElement(BONE);

            while (parentXml)
            {
                if (parentName == parentXml->Attribute(A_NAME))
                {
                    break;
                }
                parentXml = parentXml->NextSiblingElement(BONE);
            }
        }

        MovementBoneData *moveBoneData = decodeMovementBone(movBoneXml, parentXml, boneData, dataInfo);
        movementData->addMovementBoneData(moveBoneData);
        moveBoneData->release();

        movBoneXml = movBoneXml->NextSiblingElement(BONE);
    }

    return movementData;
}


MovementBoneData *DataReaderHelper::decodeMovementBone(tinyxml2::XMLElement *movBoneXml, tinyxml2::XMLElement *parentXml, BoneData *boneData, DataInfo *dataInfo)
{
    MovementBoneData *movBoneData = new (std::nothrow) MovementBoneData();
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

    unsigned long length = 0;
    unsigned long index = 0;
    int parentTotalDuration = 0;
    int currentDuration = 0;

    tinyxml2::XMLElement *parentFrameXML = nullptr;

    std::vector<tinyxml2::XMLElement *> parentXmlList;

    /*
    *  get the parent frame xml list, we need get the origin data
    */
    if( parentXml != nullptr )
    {
        parentFrameXML = parentXml->FirstChildElement(FRAME);
        while (parentFrameXML)
        {
            parentXmlList.push_back(parentFrameXML);
            parentFrameXML = parentFrameXML->NextSiblingElement(FRAME);
        }

        parentFrameXML = nullptr;

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
            while(index < length && (parentFrameXML ? (totalDuration < parentTotalDuration || totalDuration >= parentTotalDuration + currentDuration) : true))
            {
                parentFrameXML = parentXmlList[index];
                parentTotalDuration += currentDuration;
                parentFrameXML->QueryIntAttribute(A_DURATION, &currentDuration);
                index++;
            }
        }

        FrameData *frameData = decodeFrame( frameXML, parentFrameXML, boneData, dataInfo);
        movBoneData->addFrameData(frameData);
        frameData->release();

        frameData->frameID = totalDuration;
        totalDuration += frameData->duration;
        movBoneData->duration = totalDuration;

        frameXML = frameXML->NextSiblingElement(FRAME);
    }


	//! Change rotation range from (-180 -- 180) to (-infinity -- infinity)
	auto frames = movBoneData->frameList;
	for (long j = movBoneData->frameList.size() - 1; j >= 0; j--)
	{
		if (j > 0)
		{
			float difSkewX = frames.at(j)->skewX -  frames.at(j-1)->skewX;
			float difSkewY = frames.at(j)->skewY -  frames.at(j-1)->skewY;

			if (difSkewX < -M_PI || difSkewX > M_PI)
			{
				frames.at(j-1)->skewX = difSkewX < 0 ? frames.at(j-1)->skewX - 2 * M_PI : frames.at(j-1)->skewX + 2 * M_PI;
			}

			if (difSkewY < -M_PI || difSkewY > M_PI)
			{
				frames.at(j-1)->skewY = difSkewY < 0 ? frames.at(j-1)->skewY - 2 * M_PI : frames.at(j-1)->skewY + 2 * M_PI;
			}
		}
	}


    //
    FrameData *frameData = new (std::nothrow) FrameData();
    frameData->copy((FrameData *)movBoneData->frameList.back());
    frameData->frameID = movBoneData->duration;
    movBoneData->addFrameData(frameData);
    frameData->release();

    return movBoneData;
}

FrameData *DataReaderHelper::decodeFrame(tinyxml2::XMLElement *frameXML,  tinyxml2::XMLElement *parentFrameXml, BoneData* /*boneData*/, DataInfo *dataInfo)
{
    float x = 0, y = 0, scale_x = 0, scale_y = 0, skew_x = 0, skew_y = 0, tweenRotate = 0;
    int duration = 0, displayIndex = 0, zOrder = 0, tweenEasing = 0, blendType = 0;

    FrameData *frameData = new (std::nothrow) FrameData();

    if(frameXML->Attribute(A_MOVEMENT) != nullptr)
    {
        frameData->strMovement = frameXML->Attribute(A_MOVEMENT);
    }
    if(frameXML->Attribute(A_EVENT) != nullptr)
    {
        frameData->strEvent = frameXML->Attribute(A_EVENT);
    }
    if(frameXML->Attribute(A_SOUND) != nullptr)
    {
        frameData->strSound = frameXML->Attribute(A_SOUND);
    }
    if(frameXML->Attribute(A_SOUND_EFFECT) != nullptr)
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
    if(  frameXML->QueryFloatAttribute(A_TWEEN_ROTATE, &tweenRotate) == tinyxml2::XML_SUCCESS )
    {
        frameData->tweenRotate = tweenRotate;
    }
    if (  frameXML->QueryIntAttribute(A_BLEND_TYPE, &blendType) == tinyxml2::XML_SUCCESS )
    {
        switch (blendType)
        {
        case BLEND_NORMAL:
            {
                frameData->blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
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
    if(_easing != nullptr)
    {
        std::string str = _easing;
        if(str != FL_NAN)
        {
            if( frameXML->QueryIntAttribute(A_TWEEN_EASING, &(tweenEasing)) == tinyxml2::XML_SUCCESS)
            {
                frameData->tweenEasing = tweenEasing == 2 ? cocos2d::tweenfunc::Sine_EaseInOut : (cocos2d::tweenfunc::TweenType)tweenEasing;
            }
        }
        else
        {
            frameData->tweenEasing  = cocos2d::tweenfunc::Linear;
        }
    }

    if(parentFrameXml)
    {
        /*
        *  recalculate frame data from parent frame data, use for translate matrix
        */
        BaseData helpNode;
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

        TransformHelp::transformFromParent(*frameData, helpNode);
    }
    return frameData;
}

TextureData *DataReaderHelper::decodeTexture(tinyxml2::XMLElement *textureXML, DataInfo *dataInfo)
{
    TextureData *textureData = new (std::nothrow) TextureData();
    textureData->init();

    if( textureXML->Attribute(A_NAME) != nullptr)
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
        ContourData *contourData = decodeContour(contourXML, dataInfo);
        textureData->addContourData(contourData);
        contourData->release();

        contourXML = contourXML->NextSiblingElement(CONTOUR);
    }

    return textureData;
}

ContourData *DataReaderHelper::decodeContour(tinyxml2::XMLElement *contourXML, DataInfo* /*dataInfo*/)
{
    ContourData *contourData = new (std::nothrow) ContourData();
    contourData->init();

    tinyxml2::XMLElement *vertexDataXML = contourXML->FirstChildElement(CONTOUR_VERTEX);

    while (vertexDataXML)
    {
        Vec2 vertex;

        vertexDataXML->QueryFloatAttribute(A_X, &vertex.x);
        vertexDataXML->QueryFloatAttribute(A_Y, &vertex.y);

        vertex.y = -vertex.y;
        contourData->vertexList.push_back(vertex);

        vertexDataXML = vertexDataXML->NextSiblingElement(CONTOUR_VERTEX);
    }

    return contourData;
}



void DataReaderHelper::addDataFromJsonCache(const std::string& fileContent, DataInfo *dataInfo)
{
	rapidjson::Document json;
    rapidjson::StringStream stream(fileContent.c_str());

    if (fileContent.size() >= 3) {
        // Skip BOM if exists
        const unsigned char* c = (const unsigned char *)fileContent.c_str();
	    unsigned bom = c[0] | (c[1] << 8) | (c[2] << 16);

        if (bom == 0xBFBBEF)  // UTF8 BOM
        {
            stream.Take();
            stream.Take();
            stream.Take();
        }
    }

    json.ParseStream<0>(stream);
    if (json.HasParseError()) {
        CCLOG("GetParseError %d\n",json.GetParseError());
    }

	dataInfo->contentScale = DICTOOL->getFloatValue_json(json, CONTENT_SCALE, 1.0f);

    // Decode armatures
	int length = DICTOOL->getArrayCount_json(json, ARMATURE_DATA);
	for (int i = 0; i < length; i++)
    {
		const rapidjson::Value &armatureDic = DICTOOL->getSubDictionary_json(json, ARMATURE_DATA, i);
        ArmatureData *armatureData = decodeArmature(armatureDic, dataInfo);

        if (dataInfo->asyncStruct)
        {
            _dataReaderHelper->_addDataMutex.lock();
        }
        ArmatureDataManager::getInstance()->addArmatureData(armatureData->name, armatureData, dataInfo->filename);
        armatureData->release();
        if (dataInfo->asyncStruct)
        {
            _dataReaderHelper->_addDataMutex.unlock();
        }
    }

    // Decode animations
	length = DICTOOL->getArrayCount_json(json, ANIMATION_DATA); //json[ANIMATION_DATA].IsNull() ? 0 : json[ANIMATION_DATA].Size();
    for (int i = 0; i < length; i++)
    {
		const rapidjson::Value &animationDic = DICTOOL->getSubDictionary_json(json, ANIMATION_DATA, i);
        AnimationData *animationData = decodeAnimation(animationDic, dataInfo);

        if (dataInfo->asyncStruct)
        {
            _dataReaderHelper->_addDataMutex.lock();
        }
        ArmatureDataManager::getInstance()->addAnimationData(animationData->name, animationData, dataInfo->filename);
        animationData->release();
        if (dataInfo->asyncStruct)
        {
            _dataReaderHelper->_addDataMutex.unlock();
        }
    }

    // Decode textures
    length = DICTOOL->getArrayCount_json(json, TEXTURE_DATA);
    for (int i = 0; i < length; i++)
    {
        const rapidjson::Value &textureDic =  DICTOOL->getSubDictionary_json(json, TEXTURE_DATA, i);
        TextureData *textureData = decodeTexture(textureDic);

        if (dataInfo->asyncStruct)
        {
            _dataReaderHelper->_addDataMutex.lock();
        }
        ArmatureDataManager::getInstance()->addTextureData(textureData->name, textureData, dataInfo->filename);
        textureData->release();
        if (dataInfo->asyncStruct)
        {
            _dataReaderHelper->_addDataMutex.unlock();
        }
    }

    // Auto load sprite file
    bool autoLoad = dataInfo->asyncStruct == nullptr ? ArmatureDataManager::getInstance()->isAutoLoadSpriteFile() : dataInfo->asyncStruct->autoLoadSpriteFile;
    if (autoLoad)
    {
        length =  DICTOOL->getArrayCount_json(json, CONFIG_FILE_PATH); // json[CONFIG_FILE_PATH].IsNull() ? 0 : json[CONFIG_FILE_PATH].Size();
        for (int i = 0; i < length; i++)
        {
			const char *path = DICTOOL->getStringValueFromArray_json(json, CONFIG_FILE_PATH, i); // json[CONFIG_FILE_PATH][i].IsNull() ? nullptr : json[CONFIG_FILE_PATH][i].GetString();
            if (path == nullptr)
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
                if (FileUtils::getInstance()->isFileExist(dataInfo->baseFilePath + plistPath) && FileUtils::getInstance()->isFileExist(dataInfo->baseFilePath + pngPath))
                {
                    ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(dataInfo->baseFilePath + plistPath);
                    if (dict.find("particleLifespan") != dict.end()) continue;

                    ArmatureDataManager::getInstance()->addSpriteFrameFromFile((dataInfo->baseFilePath + plistPath), (dataInfo->baseFilePath + pngPath), dataInfo->filename);
                }
            }
        }
    }
}

ArmatureData *DataReaderHelper::decodeArmature(const rapidjson::Value& json, DataInfo *dataInfo)
{
    ArmatureData *armatureData = new (std::nothrow) ArmatureData();
    armatureData->init();

	const char *name = DICTOOL->getStringValue_json(json, A_NAME);
    if(name != nullptr)
    {
        armatureData->name = name;
    }

	dataInfo->cocoStudioVersion = armatureData->dataVersion = DICTOOL->getFloatValue_json(json, VERSION, 0.1f);

	int length = DICTOOL->getArrayCount_json(json, BONE_DATA, 0);
    for (int i = 0; i < length; i++)
    {
        const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(json, BONE_DATA, i); //json[BONE_DATA][i];
        BoneData *boneData = decodeBone(dic, dataInfo);
        armatureData->addBoneData(boneData);
        boneData->release();

    }

    return armatureData;
}

BoneData *DataReaderHelper::decodeBone(const rapidjson::Value& json, DataInfo *dataInfo)
{
    BoneData *boneData = new (std::nothrow) BoneData();
    boneData->init();

    decodeNode(boneData, json, dataInfo);

	const char *str = DICTOOL->getStringValue_json(json, A_NAME);
    if(str != nullptr)
    {
        boneData->name = str;
    }

    str = DICTOOL->getStringValue_json(json, A_PARENT);
    if(str != nullptr)
    {
        boneData->parentName = str;
    }

	int length = DICTOOL->getArrayCount_json(json, DISPLAY_DATA);

    for (int i = 0; i < length; i++)
    {
        const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(json, DISPLAY_DATA, i);
        DisplayData *displayData = decodeBoneDisplay(dic, dataInfo);
        boneData->addDisplayData(displayData);
        displayData->release();

    }

    return boneData;
}

DisplayData *DataReaderHelper::decodeBoneDisplay(const rapidjson::Value& json, DataInfo *dataInfo)
{
	DisplayType displayType =  (DisplayType)(DICTOOL->getIntValue_json(json, A_DISPLAY_TYPE, CS_DISPLAY_SPRITE));

    DisplayData *displayData = nullptr;

    switch (displayType)
    {
    case CS_DISPLAY_SPRITE:
    {
        displayData = new (std::nothrow) SpriteDisplayData();

        const char *name =  DICTOOL->getStringValue_json(json, A_NAME);
        if(name != nullptr)
        {
            ((SpriteDisplayData *)displayData)->displayName = name;
        }
        if(json.HasMember(SKIN_DATA))
        {
            const rapidjson::Value &dicArray = DICTOOL->getSubDictionary_json(json, SKIN_DATA);
            if(!dicArray.IsNull())
            {
                rapidjson::SizeType index = 0;
                const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(dicArray, index);
                if (!dic.IsNull())
                {
                    SpriteDisplayData *sdd = (SpriteDisplayData *)displayData;
                    sdd->skinData.x = DICTOOL->getFloatValue_json(dic, A_X) * s_PositionReadScale;
                    sdd->skinData.y = DICTOOL->getFloatValue_json(dic, A_Y) * s_PositionReadScale;
                    sdd->skinData.scaleX = DICTOOL->getFloatValue_json(dic, A_SCALE_X, 1.0f);
                    sdd->skinData.scaleY = DICTOOL->getFloatValue_json(dic, A_SCALE_Y, 1.0f);
                    sdd->skinData.skewX = DICTOOL->getFloatValue_json(dic, A_SKEW_X, 1.0f);
                    sdd->skinData.skewY = DICTOOL->getFloatValue_json(dic, A_SKEW_Y, 1.0f);

                    sdd->skinData.x *= dataInfo->contentScale;
                    sdd->skinData.y *= dataInfo->contentScale;
                }
            }

        }
    }

    break;
    case CS_DISPLAY_ARMATURE:
    {
        displayData = new (std::nothrow) ArmatureDisplayData();

        const char *name = DICTOOL->getStringValue_json(json, A_NAME);
        if(name != nullptr)
        {
            ((ArmatureDisplayData *)displayData)->displayName = name;
        }
    }
    break;
    case CS_DISPLAY_PARTICLE:
    {
        displayData = new (std::nothrow) ParticleDisplayData();

        const char *plist = DICTOOL->getStringValue_json(json, A_PLIST);
        if(plist != nullptr)
        {
            if (dataInfo->asyncStruct)
            {
                static_cast<ParticleDisplayData *>(displayData)->displayName = dataInfo->asyncStruct->baseFilePath + plist;
            }
            else
            {
                static_cast<ParticleDisplayData *>(displayData)->displayName = dataInfo->baseFilePath + plist;
            }
        }
    }
    break;
    default:
        displayData = new (std::nothrow) SpriteDisplayData();

        break;
    }


    displayData->displayType = displayType;

    return displayData;
}

AnimationData *DataReaderHelper::decodeAnimation(const rapidjson::Value& json, DataInfo *dataInfo)
{
    AnimationData *aniData = new (std::nothrow) AnimationData();

    const char *name = DICTOOL->getStringValue_json(json, A_NAME);
    if(name != nullptr)
    {
        aniData->name = name;
    }

    int length =  DICTOOL->getArrayCount_json(json, MOVEMENT_DATA);

    for (int i = 0; i < length; i++)
    {
        const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(json, MOVEMENT_DATA, i);
        MovementData *movementData = decodeMovement(dic, dataInfo);
        aniData->addMovement(movementData);
        movementData->release();

    }

    return aniData;
}

MovementData *DataReaderHelper::decodeMovement(const rapidjson::Value& json, DataInfo *dataInfo)
{
    MovementData *movementData = new (std::nothrow) MovementData();

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
	movementData->tweenEasing =  (TweenType)(DICTOOL->getIntValue_json(json, A_TWEEN_EASING, cocos2d::tweenfunc::Linear));

    const char *name = DICTOOL->getStringValue_json(json, A_NAME);
    if(name != nullptr)
    {
        movementData->name = name;
    }

	int length = DICTOOL->getArrayCount_json(json, MOVEMENT_BONE_DATA);
    for (int i = 0; i < length; i++)
    {
		const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(json, MOVEMENT_BONE_DATA, i);
        MovementBoneData *movementBoneData = decodeMovementBone(dic, dataInfo);
        movementData->addMovementBoneData(movementBoneData);
        movementBoneData->release();
    }

    return movementData;
}

MovementBoneData *DataReaderHelper::decodeMovementBone(const rapidjson::Value& json, DataInfo *dataInfo)
{
    MovementBoneData *movementBoneData = new (std::nothrow) MovementBoneData();
    movementBoneData->init();

	movementBoneData->delay = DICTOOL->getFloatValue_json(json, A_MOVEMENT_DELAY);

    const char *name = DICTOOL->getStringValue_json(json, A_NAME);
    if(name != nullptr)
    {
        movementBoneData->name = name;
    }

	rapidjson::SizeType length = DICTOOL->getArrayCount_json(json, FRAME_DATA);
    for (rapidjson::SizeType i = 0; i < length; i++)
    {
        const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(json, FRAME_DATA, i);
        FrameData *frameData = decodeFrame(dic, dataInfo);

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
		auto frames = movementBoneData->frameList;
		for (long i = frames.size() - 1; i >= 0; i--)
		{
			if (i > 0)
			{
				float difSkewX = frames.at(i)->skewX -  frames.at(i-1)->skewX;
				float difSkewY = frames.at(i)->skewY -  frames.at(i-1)->skewY;

				if (difSkewX < -M_PI || difSkewX > M_PI)
				{
					frames.at(i-1)->skewX = difSkewX < 0 ? frames.at(i-1)->skewX - 2 * M_PI : frames.at(i-1)->skewX + 2 * M_PI;
				}

				if (difSkewY < -M_PI || difSkewY > M_PI)
				{
					frames.at(i-1)->skewY = difSkewY < 0 ? frames.at(i-1)->skewY - 2 * M_PI : frames.at(i-1)->skewY + 2 * M_PI;
				}
			}
		}
	}

    if (dataInfo->cocoStudioVersion < VERSION_COMBINED)
    {
        if (movementBoneData->frameList.size() > 0)
        {
            FrameData *frameData = new (std::nothrow) FrameData();
            frameData->copy((FrameData *)movementBoneData->frameList.back());
            movementBoneData->addFrameData(frameData);
            frameData->release();

            frameData->frameID = movementBoneData->duration;
        }
    }

    return movementBoneData;
}

FrameData *DataReaderHelper::decodeFrame(const rapidjson::Value& json, DataInfo *dataInfo)
{
    FrameData *frameData = new (std::nothrow) FrameData();

    decodeNode(frameData, json, dataInfo);

	frameData->tweenEasing = (TweenType)(DICTOOL->getIntValue_json(json, A_TWEEN_EASING, cocos2d::tweenfunc::Linear));
	frameData->displayIndex = DICTOOL->getIntValue_json(json, A_DISPLAY_INDEX);
	frameData->blendFunc.src = (GLenum)(DICTOOL->getIntValue_json(json, A_BLEND_SRC, BlendFunc::ALPHA_PREMULTIPLIED.src));
	frameData->blendFunc.dst = (GLenum)(DICTOOL->getIntValue_json(json, A_BLEND_DST, BlendFunc::ALPHA_PREMULTIPLIED.dst));
	frameData->isTween = DICTOOL->getBooleanValue_json(json, A_TWEEN_FRAME, true);

	const char *event =  DICTOOL->getStringValue_json(json, A_EVENT);
    if (event != nullptr)
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
        frameData->easingParams = new (std::nothrow) float[length];
        frameData->easingParamNumber = length;

        for (int i = 0; i < length; i++)
        {
            frameData->easingParams[i] = DICTOOL->getFloatValueFromArray_json(json, A_EASING_PARAM, i);
        }
    }

    return frameData;
}

TextureData *DataReaderHelper::decodeTexture(const rapidjson::Value& json)
{
    TextureData *textureData = new (std::nothrow) TextureData();
    textureData->init();

	const char *name = DICTOOL->getStringValue_json(json, A_NAME);
    if(name != nullptr)
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
        ContourData *contourData = decodeContour(dic);
        textureData->contourDataList.pushBack(contourData);
        contourData->release();
    }

    return textureData;
}

ContourData *DataReaderHelper::decodeContour(const rapidjson::Value& json)
{
    ContourData *contourData = new (std::nothrow) ContourData();
	contourData->init();

	int length = DICTOOL->getArrayCount_json(json, VERTEX_POINT);
    for (int i = length - 1; i >= 0; i--)
    {
        const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(json, VERTEX_POINT, i);

        Vec2 vertex;

        vertex.x = DICTOOL->getFloatValue_json(dic, A_X);
        vertex.y = DICTOOL->getFloatValue_json(dic, A_Y);

        contourData->vertexList.push_back(vertex);

    }

    return contourData;
}

void DataReaderHelper::decodeNode(BaseData *node, const rapidjson::Value& json, DataInfo *dataInfo)
{
    node->x = DICTOOL->getFloatValue_json(json, A_X) * s_PositionReadScale;
    node->y = DICTOOL->getFloatValue_json(json, A_Y) * s_PositionReadScale;

    node->x *= dataInfo->contentScale;
    node->y *= dataInfo->contentScale;

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
            const rapidjson::Value &colorDic =  DICTOOL->getSubDictionary_json(json, COLOR_INFO); //json.getSubDictionary(COLOR_INFO);
            node->a = DICTOOL->getIntValue_json(colorDic, A_ALPHA, 255);
            node->r = DICTOOL->getIntValue_json(colorDic, A_RED, 255);
            node->g = DICTOOL->getIntValue_json(colorDic, A_GREEN, 255);
            node->b = DICTOOL->getIntValue_json(colorDic, A_BLUE, 255);

            node->isUseColorInfo = true;
        }
    }

}

    void DataReaderHelper::addDataFromBinaryCache(const char *fileContent, DataInfo *dataInfo)
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
                        dataInfo->contentScale = utils::atof(value.c_str());
                    }
                    else if ( 0 == key.compare(ARMATURE_DATA))
                    {
                        pDataArray = tpChildArray[i].GetChildArray(&tCocoLoader);
                        length = tpChildArray[i].GetChildNum();
                        ArmatureData * armatureData;
                        for (int ii = 0; ii < length; ++ii)
                        {
                            armatureData = decodeArmature(&tCocoLoader, &pDataArray[ii], dataInfo);
                            if (dataInfo->asyncStruct)
                            {
                                _dataReaderHelper->_addDataMutex.lock();
                            }
                            ArmatureDataManager::getInstance()->addArmatureData(armatureData->name, armatureData, dataInfo->filename);
                            armatureData->release();
                            if (dataInfo->asyncStruct)
                            {
                                _dataReaderHelper->_addDataMutex.unlock();
                            }
                        }
                    }
                    else if ( 0 == key.compare(ANIMATION_DATA))
                    {
                        pDataArray = tpChildArray[i].GetChildArray(&tCocoLoader);
                        length = tpChildArray[i].GetChildNum();
                        AnimationData *animationData;
                        for (int ii = 0; ii < length; ++ii)
                        {
                            animationData = decodeAnimation(&tCocoLoader, &pDataArray[ii], dataInfo);
                            if (dataInfo->asyncStruct)
                            {
                                _dataReaderHelper->_addDataMutex.lock();
                            }
                            ArmatureDataManager::getInstance()->addAnimationData(animationData->name, animationData, dataInfo->filename);
                            animationData->release();
                            if (dataInfo->asyncStruct)
                            {
                                _dataReaderHelper->_addDataMutex.unlock();
                            }
                        }
                    }
                    else if (key.compare(TEXTURE_DATA) == 0)
                    {
                        pDataArray = tpChildArray[i].GetChildArray(&tCocoLoader);
                        length = tpChildArray[i].GetChildNum();
                        for (int ii = 0; ii < length; ++ii)
                        {
                            TextureData *textureData = decodeTexture(&tCocoLoader, &pDataArray[ii]);
                            if (dataInfo->asyncStruct)
                            {
                                _dataReaderHelper->_addDataMutex.lock();
                            }
                            ArmatureDataManager::getInstance()->addTextureData(textureData->name, textureData, dataInfo->filename);
                            textureData->release();
                            if (dataInfo->asyncStruct)
                            {
                                _dataReaderHelper->_addDataMutex.unlock();
                            }
                        }
                    }
                }
                // Auto losprite file
                bool autoLoad = dataInfo->asyncStruct == nullptr ? ArmatureDataManager::getInstance()->isAutoLoadSpriteFile() : dataInfo->asyncStruct->autoLoadSpriteFile;
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
                        for (int ii = 0; ii < length; ii++)
                        {
                            const char *path = pConfigFilePath[ii].GetValue(&tCocoLoader);
                            if (path == nullptr)
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

                                ArmatureDataManager::getInstance()->addSpriteFrameFromFile((dataInfo->baseFilePath + plistPath), (dataInfo->baseFilePath + pngPath), dataInfo->filename);
                            }
                        }
                    }
                }
            }
        }
    }

    ArmatureData* DataReaderHelper::decodeArmature(CocoLoader *cocoLoader, stExpCocoNode *cocoNode, DataInfo *dataInfo)
    {
        ArmatureData *armatureData = new (std::nothrow) ArmatureData();
        armatureData->init();
        stExpCocoNode *pAramtureDataArray = cocoNode->GetChildArray(cocoLoader);
        const char *name = pAramtureDataArray[2].GetValue(cocoLoader); //DICTOOL->getStringValue_json(json, A_NAME);
        if(name != nullptr)
        {
            armatureData->name = name;
        }

        float version = utils::atof(pAramtureDataArray[1].GetValue(cocoLoader));
        dataInfo->cocoStudioVersion = armatureData->dataVersion = version; //DICTOOL->getFloatValue_json(json, VERSION, 0.1f);

        int length = pAramtureDataArray[3].GetChildNum(); //DICTOOL->getArrayCount_json(json, BONE_DATA, 0);
        stExpCocoNode *pBoneChildren = pAramtureDataArray[3].GetChildArray(cocoLoader);
        stExpCocoNode* child;
        for (int i = 0; i < length; i++)
        {
            //const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(json, BONE_DATA, i); //json[BONE_DATA][i];
            child = &pBoneChildren[i];
            BoneData *boneData = decodeBone(cocoLoader, child, dataInfo);
            armatureData->addBoneData(boneData);
            boneData->release();
        }

        return armatureData;
    }

    BoneData* DataReaderHelper::decodeBone(CocoLoader *cocoLoader, stExpCocoNode *cocoNode, DataInfo *dataInfo)
    {
        BoneData *boneData = new (std::nothrow) BoneData();
        boneData->init();

        decodeNode(boneData, cocoLoader, cocoNode, dataInfo);

        int length = cocoNode->GetChildNum();
        stExpCocoNode *pBoneChildren = cocoNode->GetChildArray(cocoLoader);
        stExpCocoNode* child;
        const char *str = nullptr;
        std::string key;
        for (int i = 0; i < length; ++i)
        {
            child = &pBoneChildren[i];
            key = child->GetName(cocoLoader);
            str = child->GetValue(cocoLoader);
            if (key.compare(A_NAME) == 0)
            {
                //DICTOOL->getStringValue_json(json, A_NAME);
                if(str != nullptr)
                {
                    boneData->name = str;
                }
            }
            else if (key.compare(A_PARENT) == 0)
            {
                //DICTOOL->getStringValue_json(json, A_PARENT);
                if(str != nullptr)
                {
                    boneData->parentName = str;
                }
            }
            else if (key.compare(DISPLAY_DATA) == 0)
            {
                int count = child->GetChildNum();
                stExpCocoNode *pDisplayData = child->GetChildArray(cocoLoader);
                for (int ii = 0; ii < count; ++ii)
                {
                    DisplayData *displayData = decodeBoneDisplay(cocoLoader, &pDisplayData[ii], dataInfo);
                    if(displayData == nullptr)
                        continue;
                    boneData->addDisplayData(displayData);
					displayData->release();
                }
            }
        }

        return boneData;
    }

    DisplayData* DataReaderHelper::decodeBoneDisplay(CocoLoader *cocoLoader, stExpCocoNode *cocoNode, DataInfo *dataInfo)
    {
        stExpCocoNode* children = cocoNode->GetChildArray(cocoLoader);
        stExpCocoNode* child = &children[1];

        std::string key = child->GetName(cocoLoader);
        const char *str = child->GetValue(cocoLoader);
        DisplayData *displayData = nullptr;
        if (key.compare(A_DISPLAY_TYPE) == 0)
        {
            str = child->GetValue(cocoLoader);
            DisplayType displayType = (DisplayType)(atoi(str));

            int length = 0;
            switch (displayType)
            {
                case CS_DISPLAY_SPRITE:
                {
                    displayData = new (std::nothrow) SpriteDisplayData();

                    const char *name =  children[0].GetValue(cocoLoader);
                    if(name != nullptr)
                    {
                        ((SpriteDisplayData *)displayData)->displayName = name;
                    }
                    stExpCocoNode *pSkinDataArray = children[2].GetChildArray(cocoLoader);
                    if (pSkinDataArray != nullptr)
                    {
                        stExpCocoNode *pSkinData = &pSkinDataArray[0];
                        if (pSkinData != nullptr)
                        {
                            SpriteDisplayData *sdd = (SpriteDisplayData *)displayData;
                            length = pSkinData->GetChildNum();
                            stExpCocoNode *SkinDataValue = pSkinData->GetChildArray(cocoLoader);
                            for (int i = 0; i < length; ++i)
                            {
                                key = SkinDataValue[i].GetName(cocoLoader);
                                str = SkinDataValue[i].GetValue(cocoLoader);
                                if (key.compare(A_X) == 0)
                                {
                                    sdd->skinData.x = utils::atof(str) * s_PositionReadScale;
                                }
                                else if (key.compare(A_Y) == 0)
                                {
                                    sdd->skinData.y = utils::atof(str) * s_PositionReadScale;
                                }
                                else if (key.compare(A_SCALE_X) == 0)
                                {
                                    sdd->skinData.scaleX = utils::atof(str);
                                }
                                else if (key.compare(A_SCALE_Y) == 0)
                                {
                                    sdd->skinData.scaleY = utils::atof(str);
                                }
                                else if (key.compare(A_SKEW_X) == 0)
                                {
                                    sdd->skinData.skewX = utils::atof(str);
                                }
                                else if (key.compare(A_SKEW_Y) == 0)
                                {
                                    sdd->skinData.skewY = utils::atof(str);
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
                    displayData = new (std::nothrow) ArmatureDisplayData();

                    const char *name = cocoNode[0].GetValue(cocoLoader);
                    if(name != nullptr)
                    {
                        ((ArmatureDisplayData *)displayData)->displayName = name;
                    }
                }
                    break;
                case CS_DISPLAY_PARTICLE:
                {
                    displayData = new (std::nothrow) ParticleDisplayData();
                    length = cocoNode->GetChildNum();
                    stExpCocoNode *pDisplayData = cocoNode->GetChildArray(cocoLoader);
                    for (int i = 0; i < length; ++i)
                    {
                        key = pDisplayData[i].GetName(cocoLoader);
                        str = pDisplayData[i].GetValue(cocoLoader);
                        if (key.compare(A_PLIST) == 0)
                        {
                            const char *plist = str;
                            if(plist != nullptr)
                            {
                                if (dataInfo->asyncStruct)
                                {
                                    ((ParticleDisplayData *)displayData)->displayName = dataInfo->asyncStruct->baseFilePath + plist;
                                }
                                else
                                {
                                    ((ParticleDisplayData *)displayData)->displayName = dataInfo->baseFilePath + plist;
                                }
                            }
                        }
                    }
                }
                    break;
                default:
                    displayData = new (std::nothrow) SpriteDisplayData();

                    break;
            }
            displayData->displayType = displayType;
        }
        return displayData;
    }

    AnimationData* DataReaderHelper::decodeAnimation(CocoLoader *cocoLoader, stExpCocoNode *cocoNode, DataInfo *dataInfo)
    {
        AnimationData *aniData = new (std::nothrow) AnimationData();

        int length = cocoNode->GetChildNum();
        stExpCocoNode *pAnimationData = cocoNode->GetChildArray(cocoLoader);
        const char *str = nullptr;
        std::string key;
        stExpCocoNode* child;
        MovementData *movementData;
        for (int i = 0; i < length; ++i)
        {
            child = &pAnimationData[i];
            key = child->GetName(cocoLoader);
            str = child->GetValue(cocoLoader);
            if (key.compare(A_NAME) == 0)
            {
                if(str != nullptr)
                {
                    aniData->name = str;
                }
            }
            else if (key.compare(MOVEMENT_DATA) == 0)
            {
                int movcount = child->GetChildNum();
                stExpCocoNode* movArray =  child->GetChildArray(cocoLoader);
                for( int movnum =0; movnum <movcount; movnum++)
                {
                    movementData = decodeMovement(cocoLoader, &movArray[movnum], dataInfo);
                    aniData->addMovement(movementData);
                    movementData->release();
                }
            }
        }
        return aniData;
    }

    MovementData* DataReaderHelper::decodeMovement(CocoLoader *cocoLoader, stExpCocoNode *cocoNode, DataInfo *dataInfo)
    {
        MovementData *movementData = new (std::nothrow) MovementData();
        movementData->scale = 1.0f;

        int length =  cocoNode->GetChildNum();
        stExpCocoNode *pMoveDataArray = cocoNode->GetChildArray(cocoLoader);

        const char *str = nullptr;
        std::string key;
        stExpCocoNode* child;
        for (int i = 0; i < length; ++i)
        {
            child = &pMoveDataArray[i];
            key = child->GetName(cocoLoader);
            str = child->GetValue(cocoLoader);
            if (key.compare(A_NAME) == 0)
            {
                if(str != nullptr)
                {
                    movementData->name = str;
                }
            }
            else if (key.compare(A_LOOP) == 0)
            {
                movementData->loop = true;
                if(str != nullptr)
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
                if(str != nullptr)
                {
                    movementData->durationTween = atoi(str);
                }
            }
            else if (key.compare(A_DURATION_TO) == 0)
            {
                movementData->durationTo = 0;
                if(str != nullptr)
                {
                    movementData->durationTo = atoi(str);
                }
            }
            else if (key.compare(A_DURATION) == 0)
            {
                movementData->duration = 0;
                if(str != nullptr)
                {
                    movementData->duration = atoi(str);
                }
            }
            else if (key.compare(A_MOVEMENT_SCALE) == 0)
            {
                movementData->scale = 1.0;
                if(str != nullptr)
                {
                    movementData->scale = utils::atof(str);
                }
            }
            else if (key.compare(A_TWEEN_EASING) == 0)
            {
                movementData->tweenEasing = cocos2d::tweenfunc::Linear;
                if(str != nullptr)
                {
                    movementData->tweenEasing = (TweenType)(atoi(str));
                }
            }
            else if (key.compare(MOVEMENT_BONE_DATA) == 0)
            {
                int count = child->GetChildNum();
                stExpCocoNode *pMoveBoneData = child->GetChildArray(cocoLoader);
                MovementBoneData *movementBoneData;
                for (int ii = 0; ii < count; ++ii)
                {
                    movementBoneData = decodeMovementBone(cocoLoader, &pMoveBoneData[ii],dataInfo);
                    movementData->addMovementBoneData(movementBoneData);
                    movementBoneData->release();
                }
            }
        }
        return movementData;
    }

    MovementBoneData* DataReaderHelper::decodeMovementBone(CocoLoader *cocoLoader, stExpCocoNode *cocoNode, DataInfo *dataInfo)
    {
        MovementBoneData *movementBoneData = new (std::nothrow) MovementBoneData();
        movementBoneData->init();

        int length = cocoNode->GetChildNum();
        stExpCocoNode *pMovementBoneDataArray = cocoNode->GetChildArray(cocoLoader);
        stExpCocoNode* movebonechild;
        const char *str = nullptr;
        for (int i = 0; i < length; ++i)
        {
            movebonechild = &pMovementBoneDataArray[i];
            std::string key = movebonechild->GetName(cocoLoader);
            str = movebonechild->GetValue(cocoLoader);
            if (key.compare(A_NAME) == 0)
            {
                if(str != nullptr)
                {
                    movementBoneData->name = str;
                }
            }
            else if (key.compare(A_MOVEMENT_DELAY) == 0)
            {
                if(str != nullptr)
                {
                    movementBoneData->delay = utils::atof(str);
                }
            }
            else if (key.compare(FRAME_DATA) == 0)
            {
                int count =movebonechild->GetChildNum();
                stExpCocoNode *pFrameDataArray = movebonechild->GetChildArray(cocoLoader);
                for (int ii = 0; ii < count; ++ii)
                {
                    FrameData *frameData = decodeFrame(cocoLoader, &pFrameDataArray[ii], dataInfo);
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



        const ssize_t framesizemusone = movementBoneData->frameList.size()-1;
        if (dataInfo->cocoStudioVersion < VERSION_CHANGE_ROTATION_RANGE)
        {
            //! Change rotation range from (-180 -- 180) to (-infinity -- infinity)
            cocos2d::Vector<FrameData*> frames =movementBoneData->frameList;

            ssize_t imusone =0;
            ssize_t i =0;
            for (i = framesizemusone; i >= 0; i--)
            {
                if (i > 0)
                {
                    imusone = i-1;
                    float difSkewX = frames.at(i)->skewX -  frames.at(imusone)->skewX;
                    float difSkewY = frames.at(i)->skewY -  frames.at(imusone)->skewY;

                    if (difSkewX < -M_PI || difSkewX > M_PI)
                    {
                        frames.at(imusone)->skewX = difSkewX < 0 ? frames.at(imusone)->skewX - 2 * M_PI : frames.at(imusone)->skewX + 2 * M_PI;
                    }

                    if (difSkewY < -M_PI || difSkewY > M_PI)
                    {
                        frames.at(imusone)->skewY = difSkewY < 0 ? frames.at(imusone)->skewY - 2 * M_PI : frames.at(imusone)->skewY + 2 * M_PI;
                    }
                }
            }
        }


        if (dataInfo->cocoStudioVersion < VERSION_COMBINED)
        {
            if (movementBoneData->frameList.size() > 0)
            {
                auto frameData = movementBoneData->frameList.at(framesizemusone);
                movementBoneData->addFrameData(frameData);
                frameData->release();
                frameData->frameID = movementBoneData->duration;
            }
        }

        return movementBoneData;
    }

    FrameData* DataReaderHelper::decodeFrame(CocoLoader *cocoLoader, stExpCocoNode *cocoNode, DataInfo *dataInfo)
    {
        FrameData *frameData = new (std::nothrow) FrameData();

        decodeNode(frameData, cocoLoader, cocoNode, dataInfo);

        int length = cocoNode->GetChildNum();
        stExpCocoNode *pFrameDataArray = cocoNode->GetChildArray(cocoLoader);
        const char *str = nullptr;
        for (int i = 0; i < length; ++i)
        {
            std::string key = pFrameDataArray[i].GetName(cocoLoader);
            str = pFrameDataArray[i].GetValue(cocoLoader);
            if (key.compare(A_TWEEN_EASING) == 0)
            {
                frameData->tweenEasing = cocos2d::tweenfunc::Linear;
                if(str != nullptr)
                {
                    frameData->tweenEasing = (TweenType)(atoi(str));
                }
            }
            else if (key.compare(A_DISPLAY_INDEX) == 0)
            {
                if(str != nullptr)
                {
                    frameData->displayIndex = atoi(str);
                }
            }
            else if (key.compare(A_BLEND_SRC) == 0)
            {
                if(str != nullptr)
                {
                    frameData->blendFunc.src = (GLenum)(atoi(str));
                }
            }
            else if (key.compare(A_BLEND_DST) == 0)
            {
                if(str != nullptr)
                {
                    frameData->blendFunc.dst = (GLenum)(atoi(str));
                }
            }
            else if (key.compare(A_TWEEN_FRAME) == 0)
            {
                frameData->isTween = true;
                if(str != nullptr)
                {
                    if (strcmp("1", str) != 0)
                    {
                        frameData->isTween = false;
                    }
                }
            }
            else if (key.compare(A_EVENT) == 0)
            {
                if(str != nullptr)
                {
                    frameData->strEvent = str;
                }
            }
            else if (key.compare(A_DURATION) == 0)
            {
                if (dataInfo->cocoStudioVersion < VERSION_COMBINED)
                {
                    frameData->duration = 1;
                    if(str != nullptr)
                    {
                        frameData->duration = atoi(str);
                    }
                }
            }
            else if (key.compare(A_FRAME_INDEX) == 0)
            {
                if (dataInfo->cocoStudioVersion >= VERSION_COMBINED)
                {
                    if(str != nullptr)
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
                    frameData->easingParams = new (std::nothrow) float[count];
                    stExpCocoNode *pFrameData = pFrameDataArray[i].GetChildArray(cocoLoader);
                    for (int ii = 0; ii < count; ++ii)
                    {
                        str = pFrameData[ii].GetValue(cocoLoader);
                        if (str != nullptr)
                        {
                            frameData->easingParams[ii] = utils::atof(str);
                        }
                    }
                }

            }
        }

        return frameData;
    }

    TextureData* DataReaderHelper::decodeTexture(CocoLoader *cocoLoader, stExpCocoNode *cocoNode)
    {
        TextureData *textureData = new (std::nothrow) TextureData();
        textureData->init();

        if(cocoNode == nullptr)
        {
            return textureData;
        }

        int length =  cocoNode->GetChildNum();
        stExpCocoNode *pTextureDataArray = cocoNode->GetChildArray(cocoLoader);
        const char *str = nullptr;
        for (int i = 0; i < length; ++i)
        {
            std::string key = pTextureDataArray[i].GetName(cocoLoader);
            str = pTextureDataArray[i].GetValue(cocoLoader);
            if (key.compare(A_NAME) == 0)
            {
                if(str != nullptr)
                {
                    textureData->name = str;
                }
            }
            else if (key.compare(A_WIDTH) == 0)
            {
                if(str != nullptr)
                {
                    textureData->width = utils::atof(str);
                }
            }
            else if (key.compare(A_HEIGHT) == 0)
            {
                if(str != nullptr)
                {
                    textureData->height = utils::atof(str);
                }
            }
            else if (key.compare(A_PIVOT_X) == 0)
            {
                if(str != nullptr)
                {
                    textureData->pivotX = utils::atof(str);
                }
            }
            else if (key.compare(A_PIVOT_Y) == 0)
            {
                if(str != nullptr)
                {
                    textureData->pivotY = utils::atof(str);
                }
            }
            else if (key.compare(CONTOUR_DATA) == 0)
            {
                int count = pTextureDataArray[i].GetChildNum();
                stExpCocoNode *pContourArray = pTextureDataArray[i].GetChildArray(cocoLoader);
                for (int ii = 0; ii < count; ++ii)
                {
                    ContourData *contourData = decodeContour(cocoLoader, &pContourArray[ii]);
                    textureData->contourDataList.pushBack(contourData);
                    contourData->release();
                }
            }
        }
        return textureData;
    }

    ContourData* DataReaderHelper::decodeContour(CocoLoader *cocoLoader, stExpCocoNode *cocoNode)
    {
        ContourData *contourData = new (std::nothrow) ContourData();
        contourData->init();

        int length = cocoNode->GetChildNum();
        stExpCocoNode *verTexPointArray = cocoNode->GetChildArray(cocoLoader);
        const char *str = nullptr;
        for (int i = 0; i < length; ++i)
        {
            std::string key = verTexPointArray[i].GetName(cocoLoader);
            str = verTexPointArray[i].GetValue(cocoLoader);
            if (key.compare(VERTEX_POINT) == 0)
            {
                int count = verTexPointArray[i].GetChildNum();
                stExpCocoNode *pVerTexPointArray = verTexPointArray[i].GetChildArray(cocoLoader);
                stExpCocoNode *pVerTexPoint;
                for (int ii = count - 1; ii >= 0; --ii)
                {
                    pVerTexPoint = pVerTexPointArray[ii].GetChildArray(cocoLoader);
                    Vec2 vertex;
                    vertex.x = utils::atof(pVerTexPoint[0].GetValue(cocoLoader));
                    vertex.y = utils::atof(pVerTexPoint[1].GetValue(cocoLoader));
                    contourData->vertexList.push_back(vertex);                }
                break;
            }
        }
        return contourData;
    }

    void DataReaderHelper::decodeNode(BaseData *node, CocoLoader *cocoLoader, stExpCocoNode* cocoNode, DataInfo *dataInfo)
    {
        int length = cocoNode->GetChildNum();
        stExpCocoNode *NodeArray = cocoNode->GetChildArray(cocoLoader);
        const char *str = nullptr;

        bool isVersionL = dataInfo->cocoStudioVersion < VERSION_COLOR_READING;
        stExpCocoNode* child;
        for (int i = 0; i < length; ++i)
        {
            child = &NodeArray[i];
            std::string key = child->GetName(cocoLoader);
            str = child->GetValue(cocoLoader);
            if (key.compare(A_X) == 0)
            {
                node->x = utils::atof(str) * dataInfo->contentScale;
            }
            else if (key.compare(A_Y) == 0)
            {
                node->y = utils::atof(str) * dataInfo->contentScale;
            }
            else if (key.compare(A_Z) == 0)
            {
                node->zOrder = atoi(str);
            }
            else if (key.compare(A_SKEW_X) == 0)
            {
                node->skewX = utils::atof(str);
            }
            else if (key.compare(A_SKEW_Y) == 0)
            {
                node->skewY = utils::atof(str);
            }
            else if (key.compare(A_SCALE_X) == 0)
            {
                node->scaleX = utils::atof(str);
            }
            else if (key.compare(A_SCALE_Y) == 0)
            {
                node->scaleY = utils::atof(str);
            }
            else if (key.compare(COLOR_INFO) == 0)
            {
                if (!isVersionL)
                {
                    if (child->GetType(cocoLoader) == rapidjson::kObjectType)
                    {
                        if(child->GetChildNum() == 4)
                        {
                            stExpCocoNode *ChildArray = child->GetChildArray(cocoLoader);

                            node->a = atoi(ChildArray[0].GetValue(cocoLoader));
                            node->r = atoi(ChildArray[1].GetValue(cocoLoader));
                            node->g = atoi(ChildArray[2].GetValue(cocoLoader));
                            node->b = atoi(ChildArray[3].GetValue(cocoLoader));
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

                if (NodeArray[0].GetType(cocoLoader) == rapidjson::kObjectType)
                {
                    if(NodeArray[0].GetChildNum() == 4)
                    {
                        stExpCocoNode *ChildArray = NodeArray[0].GetChildArray(cocoLoader);

                        node->a = atoi(ChildArray[0].GetValue(cocoLoader));
                        node->r = atoi(ChildArray[1].GetValue(cocoLoader));
                        node->g = atoi(ChildArray[2].GetValue(cocoLoader));
                        node->b = atoi(ChildArray[3].GetValue(cocoLoader));
                    }
                }

                node->isUseColorInfo = true;
            }
        }
    }

}
