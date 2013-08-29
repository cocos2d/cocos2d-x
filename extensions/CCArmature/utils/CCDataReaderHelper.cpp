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
static const char *BONE_DATA = "bone_data";
static const char *ARMATURE_DATA = "armature_data";
static const char *CONTOUR_DATA = "contour_data";
static const char *TEXTURE_DATA = "texture_data";
static const char *VERTEX_POINT = "vertex";
static const char *COLOR_INFO = "color";


NS_CC_EXT_BEGIN

std::vector<std::string> s_arrConfigFileList;
float s_PositionReadScale = 1;
static float s_FlashToolVersion = VERSION_2_0;

void CCDataReaderHelper::setPositionReadScale(float scale)
{
    s_PositionReadScale = scale;
}

float CCDataReaderHelper::getPositionReadScale()
{
    return s_PositionReadScale;
}

void CCDataReaderHelper::clear()
{
    s_arrConfigFileList.clear();
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


    std::string filePathStr = filePath;
    size_t startPos = filePathStr.find_last_of(".");
    std::string str = &filePathStr[startPos];

    if (str.compare(".xml") == 0)
    {
        CCDataReaderHelper::addDataFromXML(filePathStr.c_str());
    }
    else if(str.compare(".json") == 0 || str.compare(".ExportJson") == 0)
    {
        CCDataReaderHelper::addDataFromJson(filePathStr.c_str());
    }
}



void CCDataReaderHelper::addDataFromXML(const char *xmlPath)
{
    /*
    *  Need to get the full path of the xml file, or the Tiny XML can't find the xml at IOS
    */
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(xmlPath);

    /*
    *  Need to read the tiny xml into memory first, or the Tiny XML can't find the xml at IOS
    */
    unsigned long size;
    const char *pFileContent = (char *)CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str() , "r", &size);

    if (pFileContent)
    {
        addDataFromCache(pFileContent);
    }
}

void CCDataReaderHelper::addDataFromXMLPak(const char *xmlPakPath)
{
    // #if CS_TOOL_PLATFORM
    //
    // 	char *_pFileContent = NULL;
    // 	JsonReader::getFileBuffer(xmlPakPath, &_pFileContent);
    //
    // 	if (_pFileContent)
    // 	{
    // 		addDataFromCache(_pFileContent);
    // 	}
    // #endif
}

void CCDataReaderHelper::addDataFromCache(const char *pFileContent)
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
        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureData(armatureData->name.c_str(), armatureData);

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
        CCArmatureDataManager::sharedArmatureDataManager()->addAnimationData(animationData->name.c_str(), animationData);

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
        CCArmatureDataManager::sharedArmatureDataManager()->addTextureData(textureData->name.c_str(), textureData);

        textureXML = textureXML->NextSiblingElement(SUB_TEXTURE);
    }

}

CCArmatureData *CCDataReaderHelper::decodeArmature(tinyxml2::XMLElement *armatureXML)
{
    const char	*name = armatureXML->Attribute(A_NAME);


    CCArmatureData *armatureData = CCArmatureData::create();
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

        boneXML = boneXML->NextSiblingElement(BONE);
    }

    return armatureData;
}

CCBoneData *CCDataReaderHelper::decodeBone(tinyxml2::XMLElement *boneXML, tinyxml2::XMLElement *parentXml)
{

    std::string name = boneXML->Attribute(A_NAME);

    CCAssert(name.length() != 0, "");

    CCBoneData *boneData = CCBoneData::create();

    boneData->name = name;

    if( boneXML->Attribute(A_PARENT) != NULL )
    {
        boneData->parentName = boneXML->Attribute(A_PARENT);
    }

    tinyxml2::XMLElement *displayXML = boneXML->FirstChildElement(DISPLAY);
    while(displayXML)
    {
        CCDisplayData *displayData = decodeBoneDisplay(displayXML);
        boneData->addDisplayData(displayData);

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
            displayData = CCSpriteDisplayData::create();
            displayData->displayType  = CS_DISPLAY_SPRITE;
        }
        else
        {
            displayData = CCArmatureDisplayData::create();
            displayData->displayType  = CS_DISPLAY_ARMATURE;
        }

    }
    else
    {
        displayData = CCSpriteDisplayData::create();
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
    const char	*name = animationXML->Attribute(A_NAME);


    CCAnimationData *aniData =  CCAnimationData::create();

    CCArmatureData *armatureData = CCArmatureDataManager::sharedArmatureDataManager()->getArmatureData(name);

    aniData->name = name;

    tinyxml2::XMLElement *movementXML = animationXML->FirstChildElement(MOVEMENT);

    while( movementXML )
    {
        CCMovementData *movementData = decodeMovement(movementXML, armatureData);
        aniData->addMovement(movementData);

        movementXML = movementXML->NextSiblingElement(MOVEMENT);

    }

    return aniData;
}

CCMovementData *CCDataReaderHelper::decodeMovement(tinyxml2::XMLElement *movementXML, CCArmatureData *armatureData)
{
    const char *movName = movementXML->Attribute(A_NAME);

    CCMovementData *movementData = CCMovementData::create();

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

        CCMovementBoneData *_moveBoneData = decodeMovementBone(movBoneXml, parentXml, boneData);
        movementData->addMovementBoneData(_moveBoneData);

        movBoneXml = movBoneXml->NextSiblingElement(BONE);
    }

    return movementData;
}


CCMovementBoneData *CCDataReaderHelper::decodeMovementBone(tinyxml2::XMLElement *movBoneXml, tinyxml2::XMLElement *parentXml, CCBoneData *boneData)
{
    CCMovementBoneData *movBoneData = CCMovementBoneData::create();
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

        totalDuration += frameData->duration;

        frameXML = frameXML->NextSiblingElement(FRAME);
    }


    return movBoneData;
}

CCFrameData *CCDataReaderHelper::decodeFrame(tinyxml2::XMLElement *frameXML,  tinyxml2::XMLElement *parentFrameXml, CCBoneData *boneData)
{
    float _x, _y, _scale_x, _scale_y, _skew_x, _skew_y = 0;
    int _duration, _displayIndex, _zOrder, _tweenEasing = 0;

    CCFrameData *frameData = CCFrameData::create();


    if(frameXML->Attribute(A_MOVEMENT) != NULL)
    {
        frameData->m_strMovement = frameXML->Attribute(A_MOVEMENT);
    }
    if(frameXML->Attribute(A_EVENT) != NULL)
    {
        frameData->m_strEvent = frameXML->Attribute(A_EVENT);
    }
    if(frameXML->Attribute(A_SOUND) != NULL)
    {
        frameData->m_strSound = frameXML->Attribute(A_SOUND);
    }
    if(frameXML->Attribute(A_SOUND_EFFECT) != NULL)
    {
        frameData->m_strSoundEffect = frameXML->Attribute(A_SOUND_EFFECT);
    }



    if (s_FlashToolVersion >= VERSION_2_0)
    {
        if(frameXML->QueryFloatAttribute(A_COCOS2DX_X, &_x) == tinyxml2::XML_SUCCESS)
        {
            frameData->x = _x;
            frameData->x *= s_PositionReadScale;
        }
        if(frameXML->QueryFloatAttribute(A_COCOS2DX_Y, &_y) == tinyxml2::XML_SUCCESS)
        {
            frameData->y = -_y;
            frameData->y *= s_PositionReadScale;
        }
    }
    else
    {
        if(frameXML->QueryFloatAttribute(A_X, &_x) == tinyxml2::XML_SUCCESS)
        {
            frameData->x = _x;
            frameData->x *= s_PositionReadScale;
        }
        if(frameXML->QueryFloatAttribute(A_Y, &_y) == tinyxml2::XML_SUCCESS)
        {
            frameData->y = -_y;
            frameData->y *= s_PositionReadScale;
        }
    }

    if( frameXML->QueryFloatAttribute(A_SCALE_X, &_scale_x) == tinyxml2::XML_SUCCESS )
    {
        frameData->scaleX = _scale_x;
    }
    if( frameXML->QueryFloatAttribute(A_SCALE_Y, &_scale_y) == tinyxml2::XML_SUCCESS )
    {
        frameData->scaleY = _scale_y;
    }
    if( frameXML->QueryFloatAttribute(A_SKEW_X, &_skew_x) == tinyxml2::XML_SUCCESS )
    {
        frameData->skewX = CC_DEGREES_TO_RADIANS(_skew_x);
    }
    if( frameXML->QueryFloatAttribute(A_SKEW_Y, &_skew_y) == tinyxml2::XML_SUCCESS )
    {
        frameData->skewY = CC_DEGREES_TO_RADIANS(-_skew_y);
    }
    if( frameXML->QueryIntAttribute(A_DURATION, &_duration) == tinyxml2::XML_SUCCESS )
    {
        frameData->duration = _duration;
    }
    if(  frameXML->QueryIntAttribute(A_DISPLAY_INDEX, &_displayIndex) == tinyxml2::XML_SUCCESS )
    {
        frameData->displayIndex = _displayIndex;
    }
    if(  frameXML->QueryIntAttribute(A_Z, &_zOrder) == tinyxml2::XML_SUCCESS )
    {
        frameData->zOrder = _zOrder;
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
            if( frameXML->QueryIntAttribute(A_TWEEN_EASING, &(_tweenEasing)) == tinyxml2::XML_SUCCESS)
            {
                frameData->tweenEasing = (CCTweenType)_tweenEasing;
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
    CCTextureData *textureData = CCTextureData::create();

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

        contourXML = contourXML->NextSiblingElement(CONTOUR);
    }

    return textureData;
}

CCContourData *CCDataReaderHelper::decodeContour(tinyxml2::XMLElement *contourXML)
{
    CCContourData *contourData = CCContourData::create();

    tinyxml2::XMLElement *vertexDataXML = contourXML->FirstChildElement(CONTOUR_VERTEX);

    while (vertexDataXML)
    {
        CCContourVertex2 *vertex = new CCContourVertex2(0, 0);
        vertex->autorelease();

        vertexDataXML->QueryFloatAttribute(A_X, &vertex->x);
        vertexDataXML->QueryFloatAttribute(A_Y, &vertex->y);

        vertex->y = -vertex->y;
        contourData->vertexList.addObject(vertex);

        vertexDataXML = vertexDataXML->NextSiblingElement(CONTOUR_VERTEX);
    }

    return contourData;

}



void CCDataReaderHelper::addDataFromJson(const char *filePath)
{
    unsigned long size;
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(filePath);
    const char *pFileContent = (char *)CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str() , "r", &size);

    addDataFromJsonCache(pFileContent);
}

void CCDataReaderHelper::addDataFromJsonCache(const char *fileContent)
{
    cs::CSJsonDictionary json;
    json.initWithDescription(fileContent);

    // Decode armatures
    int length = json.getArrayItemCount(ARMATURE_DATA);
    for (int i = 0; i < length; i++)
    {
        cs::CSJsonDictionary *armatureDic = json.getSubItemFromArray(ARMATURE_DATA, i);
        CCArmatureData *armatureData = decodeArmature(*armatureDic);
        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureData(armatureData->name.c_str(), armatureData);

        delete armatureDic;
    }

    // Decode animations
    length = json.getArrayItemCount(ANIMATION_DATA);
    for (int i = 0; i < length; i++)
    {
        cs::CSJsonDictionary *animationDic = json.getSubItemFromArray(ANIMATION_DATA, i);
        CCAnimationData *animationData = decodeAnimation(*animationDic);
        CCArmatureDataManager::sharedArmatureDataManager()->addAnimationData(animationData->name.c_str(), animationData);

        delete animationDic;
    }

    // Decode textures
    length = json.getArrayItemCount(TEXTURE_DATA);
    for (int i = 0; i < length; i++)
    {
        cs::CSJsonDictionary *textureDic = json.getSubItemFromArray(TEXTURE_DATA, i);
        CCTextureData *textureData = decodeTexture(*textureDic);
        CCArmatureDataManager::sharedArmatureDataManager()->addTextureData(textureData->name.c_str(), textureData);

        delete textureDic;
    }
}

CCArmatureData *CCDataReaderHelper::decodeArmature(cs::CSJsonDictionary &json)
{
    CCArmatureData *armatureData = CCArmatureData::create();

    const char *name = json.getItemStringValue(A_NAME);
    if(name != NULL)
    {
        armatureData->name = name;
    }

    int length = json.getArrayItemCount(BONE_DATA);
    for (int i = 0; i < length; i++)
    {
        cs::CSJsonDictionary *dic = json.getSubItemFromArray(BONE_DATA, i);
        armatureData->addBoneData(decodeBone(*dic));

        delete dic;
    }

    return armatureData;
}

CCBoneData *CCDataReaderHelper::decodeBone(cs::CSJsonDictionary &json)
{
    CCBoneData *boneData = CCBoneData::create();

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
        boneData->addDisplayData(decodeBoneDisplay(*dic));

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
        displayData = CCSpriteDisplayData::create();
        const char *name = json.getItemStringValue(A_NAME);
        if(name != NULL)
        {
            ((CCSpriteDisplayData *)displayData)->displayName = name;
        }
    }

    break;
    case CS_DISPLAY_ARMATURE:
    {
        displayData = CCArmatureDisplayData::create();
        const char *name = json.getItemStringValue(A_NAME);
        if(name != NULL)
        {
            ((CCArmatureDisplayData *)displayData)->displayName = name;
        }
    }
    break;
    case CS_DISPLAY_PARTICLE:
    {
        displayData = CCParticleDisplayData::create();
        const char *plist = json.getItemStringValue(A_PLIST);
        if(plist != NULL)
        {
            ((CCParticleDisplayData *)displayData)->plist = plist;
        }
    }
    break;
    case CS_DISPLAY_SHADER:
    {
        displayData = CCShaderDisplayData::create();
        const char *vert = json.getItemStringValue(A_VERT);
        if(vert != NULL)
        {
            ((CCShaderDisplayData *)displayData)->vert = vert;
        }

        const char *frag = json.getItemStringValue(A_FRAG);
        if(frag != NULL)
        {
            ((CCShaderDisplayData *)displayData)->frag = vert;
        }

    }
    break;
    default:
        displayData = CCSpriteDisplayData::create();
        break;
    }

    displayData->displayType = displayType;

    return displayData;
}

CCAnimationData *CCDataReaderHelper::decodeAnimation(cs::CSJsonDictionary &json)
{
    CCAnimationData *aniData = CCAnimationData::create();

    const char *name = json.getItemStringValue(A_NAME);
    if(name != NULL)
    {
        aniData->name = name;
    }

    int length = json.getArrayItemCount(MOVEMENT_DATA);

    for (int i = 0; i < length; i++)
    {
        cs::CSJsonDictionary *dic = json.getSubItemFromArray(MOVEMENT_DATA, i);
        aniData->addMovement(decodeMovement(*dic));

        delete dic;
    }

    return aniData;
}

CCMovementData *CCDataReaderHelper::decodeMovement(cs::CSJsonDictionary &json)
{
    CCMovementData *movementData = CCMovementData::create();

    movementData->loop = json.getItemBoolvalue(A_LOOP, true);
    movementData->durationTween = json.getItemIntValue(A_DURATION_TWEEN, 0);
    movementData->durationTo = json.getItemIntValue(A_DURATION_TO, 0);
    movementData->duration = json.getItemIntValue(A_DURATION, 0);
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
        movementData->addMovementBoneData(decodeMovementBone(*dic));

        delete dic;
    }

    return movementData;
}

CCMovementBoneData *CCDataReaderHelper::decodeMovementBone(cs::CSJsonDictionary &json)
{
    CCMovementBoneData *movementBoneData = CCMovementBoneData::create();

    movementBoneData->delay = json.getItemFloatValue(A_MOVEMENT_DELAY, 0);
    movementBoneData->scale = json.getItemFloatValue(A_MOVEMENT_SCALE, 1);

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
        //movementBoneData->duration += frameData->duration;

        delete dic;
    }

    return movementBoneData;
}

CCFrameData *CCDataReaderHelper::decodeFrame(cs::CSJsonDictionary &json)
{
    CCFrameData *frameData = CCFrameData::create();

    decodeNode(frameData, json);

    frameData->duration = json.getItemIntValue(A_DURATION, 1);
    frameData->tweenEasing = (CCTweenType)json.getItemIntValue(A_TWEEN_EASING, Linear);
    frameData->displayIndex = json.getItemIntValue(A_DISPLAY_INDEX, 0);

    const char *event = json.getItemStringValue(A_EVENT);
    if (event != NULL)
    {
        frameData->m_strEvent = event;
    }

    return frameData;
}

CCTextureData *CCDataReaderHelper::decodeTexture(cs::CSJsonDictionary &json)
{
    CCTextureData *textureData = CCTextureData::create();

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
        textureData->contourDataList.addObject(decodeContour(*dic));

        delete dic;
    }

    return textureData;
}

CCContourData *CCDataReaderHelper::decodeContour(cs::CSJsonDictionary &json)
{
    CCContourData *contourData = CCContourData::create();

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
