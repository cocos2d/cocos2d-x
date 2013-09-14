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


class  CCDataReaderHelper : Object
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

	static CCDataReaderHelper *sharedDataReaderHelper();

    /**
     * Scale the position data, used for multiresolution adapter
     * It won't effect the data already read.
     */
    static void setPositionReadScale(float scale);
    static float getPositionReadScale();

    static void purge();
    static void clear();
public:
	CCDataReaderHelper();
    ~CCDataReaderHelper();

    void addDataFromFile(const char *filePath);
    void addDataFromFileAsync(const char *filePath, Object *target, SEL_SCHEDULE selector);

    void addDataAsyncCallBack(float dt);

public:

    /**
     * Translate XML export from Dragon CCBone flash tool to datas, and save them.
     * When you add a new xml, the data already saved will be keeped.
     *
     * @param xmlPath The cache of the xml
     */
    static void addDataFromCache(const char *pFileContent, DataInfo *dataInfo = NULL);



    /**
     * Decode CCArmature Datas from xml export from Dragon CCBone flash tool
     */
    static CCArmatureData *decodeArmature(tinyxml2::XMLElement *armatureXML);
    static CCBoneData *decodeBone(tinyxml2::XMLElement *boneXML, tinyxml2::XMLElement *parentXML);
    static CCDisplayData *decodeBoneDisplay(tinyxml2::XMLElement *displayXML);


    /**
     * Decode CCArmatureAnimation Datas from xml export from Dragon CCBone flash tool
     */
    static CCAnimationData *decodeAnimation(tinyxml2::XMLElement *animationXML);
    static CCMovementData *decodeMovement(tinyxml2::XMLElement *movementXML, CCArmatureData *armatureData);
    static CCMovementBoneData *decodeMovementBone(tinyxml2::XMLElement *movBoneXml, tinyxml2::XMLElement *parentXml, CCBoneData *boneData);
    static CCFrameData *decodeFrame(tinyxml2::XMLElement *frameXML, tinyxml2::XMLElement *parentFrameXml, CCBoneData *boneData);


    /**
     * Decode Texture Datas from xml export from Dragon CCBone flash tool
     */
    static CCTextureData *decodeTexture(tinyxml2::XMLElement *textureXML);

    /**
     * Decode Contour Datas from xml export from Dragon CCBone flash tool
     */
    static CCContourData *decodeContour(tinyxml2::XMLElement *contourXML);

public:
    static void addDataFromJsonCache(const char *fileContent, DataInfo *dataInfo = NULL);

    static CCArmatureData *decodeArmature(cs::JsonDictionary &json);
    static CCBoneData *decodeBone(cs::JsonDictionary &json);
    static CCDisplayData *decodeBoneDisplay(cs::JsonDictionary &json);

    static CCAnimationData *decodeAnimation(cs::JsonDictionary &json);
    static CCMovementData *decodeMovement(cs::JsonDictionary &json);
    static CCMovementBoneData *decodeMovementBone(cs::JsonDictionary &json);
    static CCFrameData *decodeFrame(cs::JsonDictionary &json);

    static CCTextureData *decodeTexture(cs::JsonDictionary &json);

    static CCContourData *decodeContour(cs::JsonDictionary &json);

    static void decodeNode(CCBaseData *node, cs::JsonDictionary &json);

protected:
	void loadData();




	std::condition_variable		s_SleepCondition;

	std::thread     *s_LoadingThread;

	std::mutex      s_SleepMutex;

	std::mutex      s_AsyncStructQueueMutex;
	std::mutex      s_DataInfoMutex;

	std::mutex      s_AddDataMutex;
	std::mutex      s_ReadFileMutex;


	unsigned long s_nAsyncRefCount;
	unsigned long s_nAsyncRefTotalCount;

	bool need_quit;

	std::queue<AsyncStruct *> *s_pAsyncStructQueue;
	std::queue<DataInfo *>   *s_pDataQueue;


    static CCDataReaderHelper *s_DataReaderHelper;
};

NS_CC_EXT_ARMATURE_END

#endif /*__CCDATAREADERHELPER_H__*/
