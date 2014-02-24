/****************************************************************************
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

#ifndef __CCDATAREADERHELPER_H__
#define __CCDATAREADERHELPER_H__

#include "cocostudio/CCArmatureDefine.h"
#include "cocostudio/CCDatas.h"
#include "cocostudio/CCArmature.h"
#include "cocostudio/DictionaryHelper.h"

#include <string>
#include <queue>
#include <list>
#include <mutex>
#include <thread>
#include <condition_variable>

namespace tinyxml2
{
    class XMLElement;
}

namespace cocostudio {

/**
 *  @js NA
 *  @lua NA
 */
class  DataReaderHelper : cocos2d::Ref
{
protected:

	enum ConfigType
	{
		DragonBone_XML,
		CocoStudio_JSON
	};

	typedef struct _AsyncStruct
	{
		std::string    filename;
		std::string    fileContent;
		ConfigType     configType;
		std::string    baseFilePath;
		cocos2d::Ref       *target;
		cocos2d::SEL_SCHEDULE   selector;
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

public:

	/** @deprecated Use getInstance() instead */
	CC_DEPRECATED_ATTRIBUTE static DataReaderHelper *sharedDataReaderHelper() { return DataReaderHelper::getInstance(); }

	static DataReaderHelper *getInstance();

    /**
     * Scale the position data, used for multiresolution adapter
     * It won't effect the data already read.
     */
    static void setPositionReadScale(float scale);
    static float getPositionReadScale();

    static void purge();
public:
	/**
     * @js ctor
     */
	DataReaderHelper();
    /**
     * @js NA
     * @lua NA
     */
    ~DataReaderHelper();

    void addDataFromFile(const std::string& filePath);
    void addDataFromFileAsync(const std::string& imagePath, const std::string& plistPath, const std::string& filePath, cocos2d::Ref *target, cocos2d::SEL_SCHEDULE selector);

    void addDataAsyncCallBack(float dt);

    void removeConfigFile(const std::string& configFile);
public:

    /**
     * Translate XML export from Dragon Bone flash tool to datas, and save them.
     * When you add a new xml, the data already saved will be keeped.
     *
     * @param xmlPath The cache of the xml
     */
    static void addDataFromCache(const std::string& pFileContent, DataInfo *dataInfo = nullptr);



    /**
     * Decode Armature Datas from xml export from Dragon Bone flash tool
     */
    static ArmatureData *decodeArmature(tinyxml2::XMLElement *armatureXML, DataInfo *dataInfo);
    static BoneData *decodeBone(tinyxml2::XMLElement *boneXML, tinyxml2::XMLElement *parentXML, DataInfo *dataInfo);
    static DisplayData *decodeBoneDisplay(tinyxml2::XMLElement *displayXML, DataInfo *dataInfo);


    /**
     * Decode ArmatureAnimation Datas from xml export from Dragon Bone flash tool
     */
    static AnimationData *decodeAnimation(tinyxml2::XMLElement *animationXML, DataInfo *dataInfo);
    static MovementData *decodeMovement(tinyxml2::XMLElement *movementXML, ArmatureData *armatureData, DataInfo *dataInfo);
    static MovementBoneData *decodeMovementBone(tinyxml2::XMLElement *movBoneXml, tinyxml2::XMLElement *parentXml, BoneData *boneData, DataInfo *dataInfo);
    static FrameData *decodeFrame(tinyxml2::XMLElement *frameXML, tinyxml2::XMLElement *parentFrameXml, BoneData *boneData, DataInfo *dataInfo);


    /**
     * Decode Texture Datas from xml export from Dragon Bone flash tool
     */
    static TextureData *decodeTexture(tinyxml2::XMLElement *textureXML, DataInfo *dataInfo);

    /**
     * Decode Contour Datas from xml export from Dragon Bone flash tool
     */
    static ContourData *decodeContour(tinyxml2::XMLElement *contourXML, DataInfo *dataInfo);

public:
    static void addDataFromJsonCache(const std::string& fileContent, DataInfo *dataInfo = nullptr);

    static ArmatureData *decodeArmature(const rapidjson::Value& json, DataInfo *dataInfo);
    static BoneData *decodeBone(const rapidjson::Value& json, DataInfo *dataInfo);
    static DisplayData *decodeBoneDisplay(const rapidjson::Value& json, DataInfo *dataInfo);

    static AnimationData *decodeAnimation(const rapidjson::Value& json, DataInfo *dataInfo);
    static MovementData *decodeMovement(const rapidjson::Value& json, DataInfo *dataInfo);
    static MovementBoneData *decodeMovementBone(const rapidjson::Value& json, DataInfo *dataInfo);
    static FrameData *decodeFrame(const rapidjson::Value& json, DataInfo *dataInfo);

    static TextureData *decodeTexture(const rapidjson::Value& json);

    static ContourData *decodeContour(const rapidjson::Value& json);

    static void decodeNode(BaseData *node, const rapidjson::Value& json, DataInfo *dataInfo);

protected:
	void loadData();




	std::condition_variable		_sleepCondition;

	std::thread     *_loadingThread;

	std::mutex      _sleepMutex;

	std::mutex      _asyncStructQueueMutex;
	std::mutex      _dataInfoMutex;

	std::mutex      _addDataMutex;

    std::mutex      _getFileMutex;

	  
	unsigned long _asyncRefCount;
	unsigned long _asyncRefTotalCount;

	bool need_quit;

	std::queue<AsyncStruct *> *_asyncStructQueue;
	std::queue<DataInfo *>   *_dataQueue;

    static std::vector<std::string> _configFileList;

    static DataReaderHelper *_dataReaderHelper;
};

}

#endif /*__CCDATAREADERHELPER_H__*/
