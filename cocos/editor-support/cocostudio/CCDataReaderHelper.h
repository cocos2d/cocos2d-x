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
#include "cocostudio/CocosStudioExport.h"

#include "json/document.h"
#include "DictionaryHelper.h"

#include <string>
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>

namespace tinyxml2
{
    class XMLElement;
}

namespace cocostudio {
    class CocoLoader;
    struct stExpCocoNode;
/**
 *  @js NA
 *  @lua NA
 */
class CC_STUDIO_DLL DataReaderHelper : cocos2d::Ref
{
protected:

	enum ConfigType
	{
		DragonBone_XML,
		CocoStudio_JSON,
        CocoStudio_Binary
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

    /**
    * @~english Get singleton.
    * @~chinese 获取单例。
    * @return @~english Singleton of `DataReaderHelper`.
    * @~chinese 数据读取器的单例。
    */
	static DataReaderHelper *getInstance();

    /**
     * @~english Scale the position data, used for multiresolution adapter
     * It won't effect the data already read.
     * @~chinese 缩放位置数据，作用于多分辨率适配。在已经读取的数据上不起作用。
     * @param scale @~english The scale for position data.
     * @~chinese 位置数据缩放值。
     */
    static void setPositionReadScale(float scale);
    /**
    * @~english Get the scale for the position data, used for multiresolution adapter
    * It won't effect the data already read.
    * @~chinese 获取位置数据的缩放值，作用于多分辨率适配。在已经读取的数据上不起作用。
    * @return @~english The scale for position data.
    * @~chinese 位置数据缩放值。
    */
    static float getPositionReadScale();

    /**
    * @~english Clear and destory singleton.
    * @~chinese 退出并销毁单例。
    */
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

    /**
    * @~english Add data from file.
    * @~chinese 从文件读取并添加数据。
    * @param filePath @~english The path of file.
    * @~chinese 文件的路径。
    */
    void addDataFromFile(const std::string& filePath);

    /**
    * @~english Add data from file asynchronous.
    * @~chinese 异步从文件读取并添加数据。
    * @param filePath @~english The path of file.
    * @~chinese 文件的路径。
    */
    void addDataFromFileAsync(const std::string& imagePath, const std::string& plistPath, const std::string& filePath, cocos2d::Ref *target, cocos2d::SEL_SCHEDULE selector);

    /**
    * @~english Add data callback asynchronous.
    * @~chinese 异步添加数据回调。
    */
    void addDataAsyncCallBack(float dt);

    /**
    * @~english Remove config file.
    * @~chinese 移除控制文件。
    * @param configFile @~english The path of config file.
    * @~chinese 控制文件的路径。
    */
    void removeConfigFile(const std::string& configFile);
public:

    /**
     * @~english Translate XML export from Dragon Bone flash tool to datas, and save them.
     * When you add a new xml, the data already saved will be keeped.
     * @~chinese 把从Dragon Bone flash工具导出的XML转换为数据并保存。添加新的xml时，已保存的数据将保留。
     *
     * @param xmlPath @~english The cache of the xml.
     * @~chinese xml缓存。
     * @param dataInfo @~english data info.
     * @~chinese 数据信息。
     */
    static void addDataFromCache(const std::string& pFileContent, DataInfo *dataInfo = nullptr);



    /**
     * @~english Decode Armature Datas from xml export from Dragon Bone flash tool
     * @~chinese 将Dragon Bone flash工具导出的XML中的骨骼数据解码。
     */
    static ArmatureData *decodeArmature(tinyxml2::XMLElement *armatureXML, DataInfo *dataInfo);
    /**
    * @~english Decode bone Datas from xml export from Dragon Bone flash tool
    * @~chinese 将Dragon Bone flash工具导出的XML中的骨头数据解码。
    */
    static BoneData *decodeBone(tinyxml2::XMLElement *boneXML, tinyxml2::XMLElement *parentXML, DataInfo *dataInfo);
    /**
    * @~english Decode bone display Datas from xml export from Dragon Bone flash tool
    * @~chinese 将Dragon Bone flash工具导出的XML中的骨头显示数据解码。
    */
    static DisplayData *decodeBoneDisplay(tinyxml2::XMLElement *displayXML, DataInfo *dataInfo);
    /**
    * @~english Decode ArmatureAnimation Datas from xml export from Dragon Bone flash tool
    * @~chinese 将Dragon Bone flash工具导出的XML中的骨骼动画数据解码。
    */
    static AnimationData *decodeAnimation(tinyxml2::XMLElement *animationXML, DataInfo *dataInfo);
    static MovementData *decodeMovement(tinyxml2::XMLElement *movementXML, ArmatureData *armatureData, DataInfo *dataInfo);
    static MovementBoneData *decodeMovementBone(tinyxml2::XMLElement *movBoneXml, tinyxml2::XMLElement *parentXml, BoneData *boneData, DataInfo *dataInfo);
    static FrameData *decodeFrame(tinyxml2::XMLElement *frameXML, tinyxml2::XMLElement *parentFrameXml, BoneData *boneData, DataInfo *dataInfo);


    /**
    * @~english Decode Texture Datas from xml export from Dragon Bone flash tool
    * @~chinese 将Dragon Bone flash工具导出的XML中的材质数据解码。
    */
    static TextureData *decodeTexture(tinyxml2::XMLElement *textureXML, DataInfo *dataInfo);

    /**
    * @~english Decode Contour Datas from xml export from Dragon Bone flash tool
    * @~chinese 将Dragon Bone flash工具导出的XML中的轮廓数据解码。
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
    
// for binary decode
public:
	static void addDataFromBinaryCache(const char *fileContent, DataInfo *dataInfo = nullptr);
	static ArmatureData *decodeArmature(CocoLoader *cocoLoader, stExpCocoNode *pCocoNode, DataInfo *dataInfo);
	static BoneData *decodeBone(CocoLoader *cocoLoader, stExpCocoNode *pCocoNode, DataInfo *dataInfo);
	static DisplayData *decodeBoneDisplay(CocoLoader *cocoLoader, stExpCocoNode *pCocoNode, DataInfo *dataInfo);
	static AnimationData *decodeAnimation(CocoLoader *cocoLoader, stExpCocoNode *pCocoNode, DataInfo *dataInfo);
	static MovementData *decodeMovement(CocoLoader *cocoLoader, stExpCocoNode *pCocoNode, DataInfo *dataInfo);
    
	static MovementBoneData *decodeMovementBone(CocoLoader *cocoLoader, stExpCocoNode *pCocoNode, DataInfo *dataInfo);
	static FrameData *decodeFrame(CocoLoader *cocoLoader, stExpCocoNode *pCocoNode, DataInfo *dataInfo);
    
	static TextureData *decodeTexture(CocoLoader *cocoLoader, stExpCocoNode *pCocoNode);
	static ContourData *decodeContour(CocoLoader *cocoLoader, stExpCocoNode *pCocoNode);
    
	static void decodeNode(BaseData *node, CocoLoader *cocoLoader, stExpCocoNode *pCocoNode, DataInfo *dataInfo);
    
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
