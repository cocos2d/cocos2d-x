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

namespace tinyxml2
{
    class XMLElement;
}

NS_CC_EXT_BEGIN

typedef struct _DataInfo DataInfo;
/**
*   @js NA
*   @lua NA
*/
class  CCDataReaderHelper : CCObject
{
public:
    static CCDataReaderHelper *sharedDataReaderHelper();

    /**
     * Scale the position data, used for multiresolution adapter
     * It won't effect the data already read.
     */
    static void setPositionReadScale(float scale);
    static float getPositionReadScale();

    static void purge();
    
public:
    ~CCDataReaderHelper();

    void addDataFromFile(const char *filePath);
    void addDataFromFileAsync(const char *imagePath, const char *plistPath, const char *filePath, CCObject *target, SEL_SCHEDULE selector);

    void addDataAsyncCallBack(float dt);

    void removeConfigFile(const char *configFile);
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
    static CCArmatureData *decodeArmature(tinyxml2::XMLElement *armatureXML, DataInfo *dataInfo);
    static CCBoneData *decodeBone(tinyxml2::XMLElement *boneXML, tinyxml2::XMLElement *parentXML, DataInfo *dataInfo);
    static CCDisplayData *decodeBoneDisplay(tinyxml2::XMLElement *displayXML, DataInfo *dataInfo);


    /**
     * Decode CCArmatureAnimation Datas from xml export from Dragon CCBone flash tool
     */
    static CCAnimationData *decodeAnimation(tinyxml2::XMLElement *animationXML, DataInfo *dataInfo);
    static CCMovementData *decodeMovement(tinyxml2::XMLElement *movementXML, CCArmatureData *armatureData, DataInfo *dataInfo);
    static CCMovementBoneData *decodeMovementBone(tinyxml2::XMLElement *movBoneXml, tinyxml2::XMLElement *parentXml, CCBoneData *boneData, DataInfo *dataInfo);
    static CCFrameData *decodeFrame(tinyxml2::XMLElement *frameXML, tinyxml2::XMLElement *parentFrameXml, CCBoneData *boneData, DataInfo *dataInfo);


    /**
     * Decode Texture Datas from xml export from Dragon CCBone flash tool
     */
    static CCTextureData *decodeTexture(tinyxml2::XMLElement *textureXML, DataInfo *dataInfo);

    /**
     * Decode Contour Datas from xml export from Dragon CCBone flash tool
     */
    static CCContourData *decodeContour(tinyxml2::XMLElement *contourXML, DataInfo *dataInfo);

public:
    static void addDataFromJsonCache(const char *fileContent, DataInfo *dataInfo = NULL);

    static CCArmatureData *decodeArmature(cs::CSJsonDictionary &json, DataInfo *dataInfo);
    static CCBoneData *decodeBone(cs::CSJsonDictionary &json, DataInfo *dataInfo);
    static CCDisplayData *decodeBoneDisplay(cs::CSJsonDictionary &json, DataInfo *dataInfo);

    static CCAnimationData *decodeAnimation(cs::CSJsonDictionary &json, DataInfo *dataInfo);
    static CCMovementData *decodeMovement(cs::CSJsonDictionary &json, DataInfo *dataInfo);
    static CCMovementBoneData *decodeMovementBone(cs::CSJsonDictionary &json, DataInfo *dataInfo);
    static CCFrameData *decodeFrame(cs::CSJsonDictionary &json, DataInfo *dataInfo);

    static CCTextureData *decodeTexture(cs::CSJsonDictionary &json);

    static CCContourData *decodeContour(cs::CSJsonDictionary &json);

    static void decodeNode(CCBaseData *node, cs::CSJsonDictionary &json, DataInfo *dataInfo);

private:
    static std::vector<std::string> s_arrConfigFileList;

    static CCDataReaderHelper *s_DataReaderHelper;
};

NS_CC_EXT_END

#endif /*__CCDATAREADERHELPER_H__*/
