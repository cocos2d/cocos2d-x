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
#include "../utils/CCConstValue.h"
#include "../CCArmature.h"
#include "../external_tool/Json/CSContentJsonDictionary.h"

namespace tinyxml2 { class XMLElement; }

namespace cocos2d { namespace extension { namespace armature {


class  DataReaderHelper
{

public:
    /**
     * Scale the position data, used for multiresolution adapter
     * It won't effect the data already read.
     */
    static void setPositionReadScale(float scale);
    static float getPositionReadScale();

    static void addDataFromFile(const char *filePath);

    static void clear();
public:

    /**
     * Translate XML export from Dragon Bone flash tool to datas, and save them.
     * When you add a new xml, the data already saved will be keeped.
     *
     * @param xmlPath Path of xml file
     */
    static void addDataFromXML(const char *xmlPath);

    /**
     * Translate XML export from Dragon Bone flash tool to datas, and save them.
     * When you add a new xml, the data already saved will be keeped.
     *
     * @param xmlPath Path of pak file
     */
    static void addDataFromXMLPak(const char *xmlPakPath);

    /**
     * Translate XML export from Dragon Bone flash tool to datas, and save them.
     * When you add a new xml, the data already saved will be keeped.
     *
     * @param xmlPath The cache of the xml
     */
    static void addDataFromCache(const char *pFileContent);



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

    static void addDataFromJson(const char *filePath);
    static void addDataFromJsonCache(const char *fileContent);

    static ArmatureData *decodeArmature(cs::CSJsonDictionary &json);
    static BoneData *decodeBone(cs::CSJsonDictionary &json);
    static DisplayData *decodeBoneDisplay(cs::CSJsonDictionary &json);

    static AnimationData *decodeAnimation(cs::CSJsonDictionary &json);
    static MovementData *decodeMovement(cs::CSJsonDictionary &json);
    static MovementBoneData *decodeMovementBone(cs::CSJsonDictionary &json);
    static FrameData *decodeFrame(cs::CSJsonDictionary &json);

    static TextureData *decodeTexture(cs::CSJsonDictionary &json);

    static ContourData *decodeContour(cs::CSJsonDictionary &json);

    static void decodeNode(BaseData *node, cs::CSJsonDictionary &json);
};

}}} // namespace cocos2d { namespace extension { namespace armature {

#endif /*__CCDATAREADERHELPER_H__*/
