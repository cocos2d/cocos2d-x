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

#ifndef __CCDATAREADERHELPER_H__
#define __CCDATAREADERHELPER_H__

#include "CCArmatureDefine.h"
#include "../datas/CCDatas.h"
#include "../CCArmature.h"
#include "../../Json/CSContentJsonDictionary.h"

#include <string>
#include <queue>
#include <list>
#include <mutex>
#include <thread>

namespace tinyxml2
{
    class XMLElement;
}

NS_CC_EXT_ARMATURE_BEGIN


class  DataReaderHelper : Object
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
		Object       *target;
		SEL_SCHEDULE   selector;
		bool           autoLoadSpriteFile;
	} AsyncStruct;

	typedef struct _DataInfo
	{
		AsyncStruct *asyncStruct;
		std::queue<std::string>      configFileQueue;
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
    static void clear();
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

    void addDataFromFile(const char *filePath);
    void addDataFromFileAsync(const char *filePath, Object *target, SEL_SCHEDULE selector);

    void addDataAsyncCallBack(float dt);

public:

    /**
     * Translate XML export from Dragon Bone flash tool to datas, and save them.
     * When you add a new xml, the data already saved will be keeped.
     *
     * @param xmlPath The cache of the xml
     */
    static void addDataFromCache(const char *pFileContent, DataInfo *dataInfo = NULL);



    /**
     * Decode Armature Datas from xml export from Dragon Bone flash tool
     */
    static ArmatureData *decodeArmature(tinyxml2::XMLElement *armatureXML);
    static BoneData *decodeBone(tinyxml2::XMLElement *boneXML, tinyxml2::XMLElement *parentXML);
    static DisplayData *decodeBoneDisplay(tinyxml2::XMLElement *displayXML);


    /**
     * Decode ArmatureAnimation Datas from xml export from Dragon Bone flash tool
     */
    static AnimationData *decodeAnimation(tinyxml2::XMLElement *animationXML);
    static MovementData *decodeMovement(tinyxml2::XMLElement *movementXML, ArmatureData *armatureData);
    static MovementBoneData *decodeMovementBone(tinyxml2::XMLElement *movBoneXml, tinyxml2::XMLElement *parentXml, BoneData *boneData);
    static FrameData *decodeFrame(tinyxml2::XMLElement *frameXML, tinyxml2::XMLElement *parentFrameXml, BoneData *boneData);


    /**
     * Decode Texture Datas from xml export from Dragon Bone flash tool
     */
    static TextureData *decodeTexture(tinyxml2::XMLElement *textureXML);

    /**
     * Decode Contour Datas from xml export from Dragon Bone flash tool
     */
    static ContourData *decodeContour(tinyxml2::XMLElement *contourXML);

public:
    static void addDataFromJsonCache(const char *fileContent, DataInfo *dataInfo = NULL);

    static ArmatureData *decodeArmature(cs::JsonDictionary &json);
    static BoneData *decodeBone(cs::JsonDictionary &json);
    static DisplayData *decodeBoneDisplay(cs::JsonDictionary &json);

    static AnimationData *decodeAnimation(cs::JsonDictionary &json);
    static MovementData *decodeMovement(cs::JsonDictionary &json);
    static MovementBoneData *decodeMovementBone(cs::JsonDictionary &json);
    static FrameData *decodeFrame(cs::JsonDictionary &json);

    static TextureData *decodeTexture(cs::JsonDictionary &json);

    static ContourData *decodeContour(cs::JsonDictionary &json);

    static void decodeNode(BaseData *node, cs::JsonDictionary &json);

protected:
	void loadData();




	std::condition_variable		_sleepCondition;

	std::thread     *_loadingThread;

	std::mutex      _sleepMutex;

	std::mutex      _asyncStructQueueMutex;
	std::mutex      _dataInfoMutex;

	std::mutex      _addDataMutex;

	  
	unsigned long _asyncRefCount;
	unsigned long _asyncRefTotalCount;

	bool need_quit;

	std::queue<AsyncStruct *> *_asyncStructQueue;
	std::queue<DataInfo *>   *_dataQueue;


    static DataReaderHelper *_dataReaderHelper;
};

NS_CC_EXT_ARMATURE_END

#endif /*__CCDATAREADERHELPER_H__*/
