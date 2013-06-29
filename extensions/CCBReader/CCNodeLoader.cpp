#include "CCNodeLoader.h"
#include "CCBSelectorResolver.h"
#include "CCBMemberVariableAssigner.h"
#include "CCBAnimationManager.h"
#include "CCNode+CCBRelativePositioning.h"

using namespace std;

NS_CC_EXT_BEGIN

NodeLoader::NodeLoader()
{
    _customProperties = new Dictionary();
}

NodeLoader::~NodeLoader()
{
    CC_SAFE_RELEASE(_customProperties);
}

Dictionary* NodeLoader::getCustomProperties()
{
    return _customProperties;
}

Node * NodeLoader::loadNode(Node * pParent, CCBReader * pCCBReader) {
    Node * ccNode = this->createNode(pParent, pCCBReader);

    //this->parseProperties(ccNode, pParent, pCCBReader);

    return ccNode;
}

void NodeLoader::parseProperties(Node * pNode, Node * pParent, CCBReader * pCCBReader) {
    int numRegularProps = pCCBReader->readInt(false);
    int numExturaProps = pCCBReader->readInt(false);
    int propertyCount = numRegularProps + numExturaProps;

    for(int i = 0; i < propertyCount; i++) {
        bool isExtraProp = (i >= numRegularProps);
        int type = pCCBReader->readInt(false);
        std::string propertyName = pCCBReader->readCachedString();

        // Check if the property can be set for this platform
        bool setProp = false;
        
        int platform = pCCBReader->readByte();
        if(platform == kCCBPlatformAll) 
        {
            setProp = true;
        }
        // Cocos2d-x is using touch event callback for all platforms,
        // it's different from cocos2d-iphone which uses mouse event for Mac port.
        // So we just need to touch event by using kCCBPlatformIOS.
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        if(platform == kCCBPlatformIOS)
        {
            setProp = true;
        }
// #elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
//         if(platform == kCCBPlatformMac)
//         {
//             setProp = true;
//         }
// #endif
        
        // Forward properties for sub ccb files
        if (dynamic_cast<CCBFile*>(pNode) != NULL)
        {
            CCBFile *ccbNode = (CCBFile*)pNode;
            if (ccbNode->getCCBFileNode() && isExtraProp)
            {
                pNode = ccbNode->getCCBFileNode();
                
                // Skip properties that doesn't have a value to override
                Array *extraPropsNames = (Array*)pNode->getUserObject();
                Object* pObj = NULL;
                bool bFound = false;
                CCARRAY_FOREACH(extraPropsNames, pObj)
                {
                    String* pStr = (String*)pObj;
                    if (0 == pStr->compare(propertyName.c_str()))
                    {
                        bFound = true;
                        break;
                    }
                }
                setProp &= bFound;
            }
        }
        else if (isExtraProp && pNode == pCCBReader->getAnimationManager()->getRootNode())
        {
            Array *extraPropsNames = (Array*)pNode->getUserObject();
            if (! extraPropsNames)
            {
                extraPropsNames = Array::create();
                pNode->setUserObject(extraPropsNames);
            }
            
            extraPropsNames->addObject(String::create(propertyName));
        }

        switch(type) 
        {
            case kCCBPropTypePosition: 
            {
                Point position = this->parsePropTypePosition(pNode, pParent, pCCBReader, propertyName.c_str());
                if (setProp) 
                {
                    this->onHandlePropTypePosition(pNode, pParent, propertyName.c_str(), position, pCCBReader);
                }
                break;
            }
            case kCCBPropTypePoint: 
            {
                Point point = this->parsePropTypePoint(pNode, pParent, pCCBReader);
                if (setProp) 
                {
                    this->onHandlePropTypePoint(pNode, pParent, propertyName.c_str(), point, pCCBReader);
                }
                break;
            }
            case kCCBPropTypePointLock: 
            {
                Point pointLock = this->parsePropTypePointLock(pNode, pParent, pCCBReader);
                if (setProp) 
                {
                    this->onHandlePropTypePointLock(pNode, pParent, propertyName.c_str(), pointLock, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeSize: {
                Size size = this->parsePropTypeSize(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeSize(pNode, pParent, propertyName.c_str(), size, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeScaleLock: 
            {
                float * scaleLock = this->parsePropTypeScaleLock(pNode, pParent, pCCBReader, propertyName.c_str());
                if(setProp) 
                {
                    this->onHandlePropTypeScaleLock(pNode, pParent, propertyName.c_str(), scaleLock, pCCBReader);
                }
                CC_SAFE_DELETE_ARRAY(scaleLock);
                break;
            }
            case kCCBPropTypeFloat: 
            {
                float f = this->parsePropTypeFloat(pNode, pParent, pCCBReader);
                if(setProp) 
                {
                    this->onHandlePropTypeFloat(pNode, pParent, propertyName.c_str(), f, pCCBReader);
                }
                break;
            }
	    case kCCBPropTypeFloatXY:
	      {
                float * xy =  this->parsePropTypeFloatXY(pNode, pParent, pCCBReader);
                if(setProp)
                {
                    this->onHandlePropTypeFloatXY(pNode, pParent, propertyName.c_str(), xy, pCCBReader);
                }
                CC_SAFE_DELETE_ARRAY(xy);
                break;
	      }

            case kCCBPropTypeDegrees: 
            {
                float degrees = this->parsePropTypeDegrees(pNode, pParent, pCCBReader, propertyName.c_str());
                if(setProp) 
                {
                    this->onHandlePropTypeDegrees(pNode, pParent, propertyName.c_str(), degrees, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeFloatScale: 
            {
                float floatScale = this->parsePropTypeFloatScale(pNode, pParent, pCCBReader);
                if(setProp) 
                {
                    this->onHandlePropTypeFloatScale(pNode, pParent, propertyName.c_str(), floatScale, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeInteger: 
            {
                int integer = this->parsePropTypeInteger(pNode, pParent, pCCBReader);
                if(setProp) 
                {
                    this->onHandlePropTypeInteger(pNode, pParent, propertyName.c_str(), integer, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeIntegerLabeled: 
            {
                int integerLabeled = this->parsePropTypeIntegerLabeled(pNode, pParent, pCCBReader);
                if(setProp) 
                {
                    this->onHandlePropTypeIntegerLabeled(pNode, pParent, propertyName.c_str(), integerLabeled, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeFloatVar: 
            {
                float * floatVar = this->parsePropTypeFloatVar(pNode, pParent, pCCBReader);
                if(setProp) 
                {
                    this->onHandlePropTypeFloatVar(pNode, pParent, propertyName.c_str(), floatVar, pCCBReader);
                }
                CC_SAFE_DELETE_ARRAY(floatVar);
                break;
            }
            case kCCBPropTypeCheck: 
            {
                bool check = this->parsePropTypeCheck(pNode, pParent, pCCBReader, propertyName.c_str());
                if(setProp) 
                {
                    this->onHandlePropTypeCheck(pNode, pParent, propertyName.c_str(), check, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeSpriteFrame: {
                SpriteFrame * ccSpriteFrame = this->parsePropTypeSpriteFrame(pNode, pParent, pCCBReader, propertyName.c_str());
                if(setProp) 
                {
                    this->onHandlePropTypeSpriteFrame(pNode, pParent, propertyName.c_str(), ccSpriteFrame, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeAnimation: 
            {
                Animation * ccAnimation = this->parsePropTypeAnimation(pNode, pParent, pCCBReader);
                if(setProp) 
                {
                    this->onHandlePropTypeAnimation(pNode, pParent, propertyName.c_str(), ccAnimation, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeTexture: 
            {
                Texture2D * ccTexture2D = this->parsePropTypeTexture(pNode, pParent, pCCBReader);
                if(setProp) 
                {
                    this->onHandlePropTypeTexture(pNode, pParent, propertyName.c_str(), ccTexture2D, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeByte: 
            {
                unsigned char byte = this->parsePropTypeByte(pNode, pParent, pCCBReader, propertyName.c_str());
                if(setProp) 
                {
                    this->onHandlePropTypeByte(pNode, pParent, propertyName.c_str(), byte, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeColor3: 
            {
                ccColor3B color3B = this->parsePropTypeColor3(pNode, pParent, pCCBReader, propertyName.c_str());
                if(setProp) 
                {
                    this->onHandlePropTypeColor3(pNode, pParent, propertyName.c_str(), color3B, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeColor4FVar: 
            {
                ccColor4F * color4FVar = this->parsePropTypeColor4FVar(pNode, pParent, pCCBReader);
                if(setProp) 
                {
                    this->onHandlePropTypeColor4FVar(pNode, pParent, propertyName.c_str(), color4FVar, pCCBReader);
                }
                CC_SAFE_DELETE_ARRAY(color4FVar);
                break;
            }
            case kCCBPropTypeFlip: {
                bool * flip = this->parsePropTypeFlip(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeFlip(pNode, pParent, propertyName.c_str(), flip, pCCBReader);
                }
                CC_SAFE_DELETE_ARRAY(flip);
                break;
            }
            case kCCBPropTypeBlendmode: 
            {
                ccBlendFunc blendFunc = this->parsePropTypeBlendFunc(pNode, pParent, pCCBReader);
                if(setProp) 
                {
                    this->onHandlePropTypeBlendFunc(pNode, pParent, propertyName.c_str(), blendFunc, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeFntFile: 
            {
                std::string fntFile = pCCBReader->getCCBRootPath() + this->parsePropTypeFntFile(pNode, pParent, pCCBReader);
                if(setProp) 
                {
                    this->onHandlePropTypeFntFile(pNode, pParent, propertyName.c_str(), fntFile.c_str(), pCCBReader);
                }
                break;
            }
            case kCCBPropTypeFontTTF: {
                std::string fontTTF = this->parsePropTypeFontTTF(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeFontTTF(pNode, pParent, propertyName.c_str(), fontTTF.c_str(), pCCBReader);
                }
                break;
            }
            case kCCBPropTypeString: {
                std::string string = this->parsePropTypeString(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeString(pNode, pParent, propertyName.c_str(), string.c_str(), pCCBReader);
                }
                break;
            }
            case kCCBPropTypeText: {
                std::string text = this->parsePropTypeText(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeText(pNode, pParent, propertyName.c_str(), text.c_str(), pCCBReader);
                }
                break;
            }
            case kCCBPropTypeBlock: {
                BlockData * blockData = this->parsePropTypeBlock(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeBlock(pNode, pParent, propertyName.c_str(), blockData, pCCBReader);
                }
                CC_SAFE_DELETE(blockData);
                break;
            }
            case kCCBPropTypeBlockControl: {
                BlockControlData * blockControlData = this->parsePropTypeBlockControl(pNode, pParent, pCCBReader);
                if(setProp && blockControlData != NULL) {
                    this->onHandlePropTypeBlockControl(pNode, pParent, propertyName.c_str(), blockControlData, pCCBReader);
                }
                CC_SAFE_DELETE(blockControlData);
                break;
            }
            case kCCBPropTypeCCBFile: {
                Node * ccbFileNode = this->parsePropTypeCCBFile(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeCCBFile(pNode, pParent, propertyName.c_str(), ccbFileNode, pCCBReader);
                }
                break;
            }
            default:
                ASSERT_FAIL_UNEXPECTED_PROPERTYTYPE(type);
                break;
        }
    }
}

Point NodeLoader::parsePropTypePosition(Node * pNode, Node * pParent, CCBReader * pCCBReader, const char *pPropertyName) {
    float x = pCCBReader->readFloat();
    float y = pCCBReader->readFloat();
    
    int type = pCCBReader->readInt(false);
    
    Size containerSize = pCCBReader->getAnimationManager()->getContainerSize(pParent);
    
    Point pt = getAbsolutePosition(ccp(x,y), type, containerSize, pPropertyName);
    pNode->setPosition(pt);
    
    if (pCCBReader->getAnimatedProperties()->find(pPropertyName) != pCCBReader->getAnimatedProperties()->end())
    {
        Array *baseValue = Array::create(CCBValue::create(x),
                                             CCBValue::create(y),
                                             CCBValue::create(type),
                                             NULL);
        pCCBReader->getAnimationManager()->setBaseValue(baseValue, pNode, pPropertyName);
    }

    return pt;
}

Point NodeLoader::parsePropTypePoint(Node * pNode, Node * pParent, CCBReader * pCCBReader) 
{
    float x = pCCBReader->readFloat();
    float y = pCCBReader->readFloat();

    return Point(x, y);
}

Point NodeLoader::parsePropTypePointLock(Node * pNode, Node * pParent, CCBReader * pCCBReader) {
    float x = pCCBReader->readFloat();
    float y = pCCBReader->readFloat();

    return Point(x, y);
}

Size NodeLoader::parsePropTypeSize(Node * pNode, Node * pParent, CCBReader * pCCBReader) {
    float width = pCCBReader->readFloat();
    float height = pCCBReader->readFloat();

    int type = pCCBReader->readInt(false);

    Size containerSize = pCCBReader->getAnimationManager()->getContainerSize(pParent);

    switch (type) 
    {
        case kCCBSizeTypeAbsolute: 
        {
            /* Nothing. */
            break;
        }
        case kCCBSizeTypeRelativeContainer: 
        {
            width = containerSize.width - width;
            height = containerSize.height - height;
            break;
        }
        case kCCBSizeTypePercent: 
        {
            width = (int)(containerSize.width * width / 100.0f);
            height = (int)(containerSize.height * height / 100.0f);
            break;
        }
        case kCCBSizeTypeHorizontalPercent: 
        {
            width = (int)(containerSize.width * width / 100.0f);
            break;
        }
        case kCCBSizeTypeVerticalPercent: 
        {
            height = (int)(containerSize.height * height / 100.0f);
            break;
        }
        case kCCBSizeTypeMultiplyResolution:
        {
            float resolutionScale = CCBReader::getResolutionScale();
            
            width *= resolutionScale;
            height *= resolutionScale;
            break;
        }
        default:
        {
            CCLog("Unknown CCB type.");
        }
            break;
    }
    
    return Size(width, height);
}



float * NodeLoader::parsePropTypeFloatXY(Node * pNode, Node * pParent, CCBReader * pCCBReader) {
    float x = pCCBReader->readFloat();
    float y = pCCBReader->readFloat();

    float * floatXY = new float[2];
    floatXY[0] = x;
    floatXY[1] = y;

    return floatXY;
}

float * NodeLoader::parsePropTypeScaleLock(Node * pNode, Node * pParent, CCBReader * pCCBReader, const char *pPropertyName) {
    float x = pCCBReader->readFloat();
    float y = pCCBReader->readFloat();
    
    int type = pCCBReader->readInt(false);
    
    setRelativeScale(pNode, x, y, type, pPropertyName);
    
    if (pCCBReader->getAnimatedProperties()->find(pPropertyName) != pCCBReader->getAnimatedProperties()->end())
    {
        Array *baseValue = Array::create(CCBValue::create(x),
                                             CCBValue::create(y),
                                             CCBValue::create(type),
                                             NULL);
        pCCBReader->getAnimationManager()->setBaseValue(baseValue, pNode, pPropertyName);
    }
    
    if (type == kCCBScaleTypeMultiplyResolution) 
    {
        x *= pCCBReader->getResolutionScale();
        y *= pCCBReader->getResolutionScale();
    }
    
    float * scaleLock = new float[2];
    scaleLock[0] = x;
    scaleLock[1] = y;

    return scaleLock;
}

float NodeLoader::parsePropTypeFloat(Node * pNode, Node * pParent, CCBReader * pCCBReader) {
    return pCCBReader->readFloat();
}

float NodeLoader::parsePropTypeDegrees(Node * pNode, Node * pParent, CCBReader * pCCBReader, const char *pPropertyName) {
    float ret = pCCBReader->readFloat();
    if (pCCBReader->getAnimatedProperties()->find(pPropertyName) != pCCBReader->getAnimatedProperties()->end())
    {
        CCBValue *value = CCBValue::create(ret);
        pCCBReader->getAnimationManager()->setBaseValue(value, pNode, pPropertyName);
    }
    
    return ret;
}

float NodeLoader::parsePropTypeFloatScale(Node * pNode, Node * pParent, CCBReader * pCCBReader) 
{
    float f = pCCBReader->readFloat();

    int type = pCCBReader->readInt(false);
    
    if(type == kCCBScaleTypeMultiplyResolution) 
    {
        f *= pCCBReader->getResolutionScale();
    }

    return f;
}

int NodeLoader::parsePropTypeInteger(Node * pNode, Node * pParent, CCBReader * pCCBReader) 
{
    return pCCBReader->readInt(true);
}

int NodeLoader::parsePropTypeIntegerLabeled(Node * pNode, Node * pParent, CCBReader * pCCBReader) 
{
    return pCCBReader->readInt(true);
}

float * NodeLoader::parsePropTypeFloatVar(Node * pNode, Node * pParent, CCBReader * pCCBReader) 
{
    float f = pCCBReader->readFloat();
    float fVar = pCCBReader->readFloat();
    
    float * arr = new float[2];
    arr[0] = f;
    arr[1] = fVar;
    
    return arr;
}

bool NodeLoader::parsePropTypeCheck(Node * pNode, Node * pParent, CCBReader * pCCBReader, const char *pPropertyName) 
{
    bool ret = pCCBReader->readBool();
    
    if (pCCBReader->getAnimatedProperties()->find(pPropertyName) != pCCBReader->getAnimatedProperties()->end())
    {
        CCBValue *value = CCBValue::create(ret);
        pCCBReader->getAnimationManager()->setBaseValue(value, pNode, pPropertyName);
    }
    
    return ret;
}


SpriteFrame * NodeLoader::parsePropTypeSpriteFrame(Node * pNode, Node * pParent, CCBReader * pCCBReader, const char *pPropertyName) 
{
    std::string spriteSheet = pCCBReader->readCachedString();
    std::string spriteFile = pCCBReader->readCachedString();
    
    SpriteFrame *spriteFrame = NULL;
    if (spriteFile.length() != 0)
    {
        if (spriteSheet.length() == 0)
        {
            spriteFile = pCCBReader->getCCBRootPath() + spriteFile;
            Texture2D * texture = TextureCache::sharedTextureCache()->addImage(spriteFile.c_str());
            if(texture != NULL) {
                Rect bounds = CCRectMake(0, 0, texture->getContentSize().width, texture->getContentSize().height);
                spriteFrame = SpriteFrame::createWithTexture(texture, bounds);
            }
        }
        else 
        {
            SpriteFrameCache * frameCache = SpriteFrameCache::sharedSpriteFrameCache();
            spriteSheet = pCCBReader->getCCBRootPath() + spriteSheet;   
            // Load the sprite sheet only if it is not loaded
            if (pCCBReader->getLoadedSpriteSheet().find(spriteSheet) == pCCBReader->getLoadedSpriteSheet().end())
            {
                frameCache->addSpriteFramesWithFile(spriteSheet.c_str());
                pCCBReader->getLoadedSpriteSheet().insert(spriteSheet);
            }
            
            spriteFrame = frameCache->spriteFrameByName(spriteFile.c_str());
        }
        
        if (pCCBReader->getAnimatedProperties()->find(pPropertyName) != pCCBReader->getAnimatedProperties()->end())
        {
            pCCBReader->getAnimationManager()->setBaseValue(spriteFrame, pNode, pPropertyName);
        }
    }
    
    return spriteFrame;
}

Animation * NodeLoader::parsePropTypeAnimation(Node * pNode, Node * pParent, CCBReader * pCCBReader) {
    std::string animationFile = pCCBReader->getCCBRootPath() + pCCBReader->readCachedString();
    std::string animation = pCCBReader->readCachedString();
    
    Animation * ccAnimation = NULL;
    
    // Support for stripping relative file paths, since ios doesn't currently
    // know what to do with them, since its pulling from bundle.
    // Eventually this should be handled by a client side asset manager
    // interface which figured out what resources to load.
    // TODO Does this problem exist in C++?
    animation = CCBReader::lastPathComponent(animation.c_str());
    animationFile = CCBReader::lastPathComponent(animationFile.c_str());
    
    if (animation.length() > 0) 
    {
        AnimationCache * animationCache = AnimationCache::sharedAnimationCache();
        animationCache->addAnimationsWithFile(animationFile.c_str());
        
        ccAnimation = animationCache->animationByName(animation.c_str());
    }
    return ccAnimation;
}

Texture2D * NodeLoader::parsePropTypeTexture(Node * pNode, Node * pParent, CCBReader * pCCBReader) {
    std::string spriteFile = pCCBReader->getCCBRootPath() + pCCBReader->readCachedString();
    
    if (spriteFile.length() > 0)
    {
        return TextureCache::sharedTextureCache()->addImage(spriteFile.c_str());
    }
    else 
    {
        return NULL;
    }
}

unsigned char NodeLoader::parsePropTypeByte(Node * pNode, Node * pParent, CCBReader * pCCBReader, const char *pPropertyName) 
{
    unsigned char ret = pCCBReader->readByte();
    
    if (pCCBReader->getAnimatedProperties()->find(pPropertyName) != pCCBReader->getAnimatedProperties()->end())
    {
        pCCBReader->getAnimationManager()->setBaseValue(CCBValue::create(ret), pNode, pPropertyName);
    }
    
    return ret;
}

ccColor3B NodeLoader::parsePropTypeColor3(Node * pNode, Node * pParent, CCBReader * pCCBReader, const char *pPropertyName) {
    unsigned char red = pCCBReader->readByte();
    unsigned char green = pCCBReader->readByte();
    unsigned char blue = pCCBReader->readByte();
    
    ccColor3B color = { red, green, blue };
    if (pCCBReader->getAnimatedProperties()->find(pPropertyName) != pCCBReader->getAnimatedProperties()->end())
    {
        ccColor3BWapper *value = ccColor3BWapper::create(color);
        pCCBReader->getAnimationManager()->setBaseValue(value, pNode, pPropertyName);
    }
    return color;
}

ccColor4F * NodeLoader::parsePropTypeColor4FVar(Node * pNode, Node * pParent, CCBReader * pCCBReader) {
    float red = pCCBReader->readFloat();
    float green = pCCBReader->readFloat();
    float blue = pCCBReader->readFloat();
    float alpha = pCCBReader->readFloat();
    float redVar = pCCBReader->readFloat();
    float greenVar = pCCBReader->readFloat();
    float blueVar = pCCBReader->readFloat();
    float alphaVar = pCCBReader->readFloat();
    
    ccColor4F * colors = new ccColor4F[2];
    colors[0].r = red;
    colors[0].g = green;
    colors[0].b = blue;
    colors[0].a = alpha;
    
    colors[1].r = redVar;
    colors[1].g = greenVar;
    colors[1].b = blueVar;
    colors[1].a = alphaVar;
    
    return colors;
}

bool * NodeLoader::parsePropTypeFlip(Node * pNode, Node * pParent, CCBReader * pCCBReader) {
    bool flipX = pCCBReader->readBool();
    bool flipY = pCCBReader->readBool();

    bool * arr = new bool[2];
    arr[0] = flipX;
    arr[1] = flipY;

    return arr;
}

ccBlendFunc NodeLoader::parsePropTypeBlendFunc(Node * pNode, Node * pParent, CCBReader * pCCBReader) 
{
    int source = pCCBReader->readInt(false);
    int destination = pCCBReader->readInt(false);
    
    ccBlendFunc blendFunc;
    blendFunc.src = source;
    blendFunc.dst = destination;
    
    return blendFunc;
}

std::string NodeLoader::parsePropTypeFntFile(Node * pNode, Node * pParent, CCBReader * pCCBReader) 
{
    return pCCBReader->readCachedString();
}

std::string NodeLoader::parsePropTypeString(Node * pNode, Node * pParent, CCBReader * pCCBReader) {
    return pCCBReader->readCachedString();
}

std::string NodeLoader::parsePropTypeText(Node * pNode, Node * pParent, CCBReader * pCCBReader) {
    return pCCBReader->readCachedString();
}

std::string NodeLoader::parsePropTypeFontTTF(Node * pNode, Node * pParent, CCBReader * pCCBReader) {
    std::string fontTTF = pCCBReader->readCachedString();

    // String * ttfEnding = String::create(".ttf");

    // TODO Fix me if it is wrong
    /* If the fontTTF comes with the ".ttf" extension, prepend the absolute path. 
     * System fonts come without the ".ttf" extension and do not need the path prepended. */
    /*
    if(CCBReader::endsWith(CCBReader::toLowerCase(fontTTF), ttfEnding)){
        fontTTF = CCBReader::concat(pCCBReader->getCCBRootPath(), fontTTF);
    }
     */

    return fontTTF;
}

BlockData * NodeLoader::parsePropTypeBlock(Node * pNode, Node * pParent, CCBReader * pCCBReader) {
    std::string selectorName = pCCBReader->readCachedString();
    int selectorTarget = pCCBReader->readInt(false);

    if(selectorTarget != kCCBTargetTypeNone) {
        Object * target = NULL;
        if(!pCCBReader->isJSControlled()) {
            
            if(selectorTarget == kCCBTargetTypeDocumentRoot) {
                target = pCCBReader->getAnimationManager()->getRootNode();
            } else if(selectorTarget == kCCBTargetTypeOwner) {
                target = pCCBReader->getOwner();
            }
            
            if(target != NULL) {
                if(selectorName.length() > 0) {
                    SEL_MenuHandler selMenuHandler = 0;
                    
                    CCBSelectorResolver * targetAsCCBSelectorResolver = dynamic_cast<CCBSelectorResolver *>(target);
                    
                    if(targetAsCCBSelectorResolver != NULL) {
                        selMenuHandler = targetAsCCBSelectorResolver->onResolveCCBMenuItemSelector(target, selectorName.c_str());
                    }
                    if(selMenuHandler == 0) {
                        CCBSelectorResolver * ccbSelectorResolver = pCCBReader->getCCBSelectorResolver();
                        if(ccbSelectorResolver != NULL) {
                            selMenuHandler = ccbSelectorResolver->onResolveCCBMenuItemSelector(target, selectorName.c_str());
                        }
                    }
                    
                    if(selMenuHandler == 0) {
                        CCLOG("Skipping selector '%s' since no CCBSelectorResolver is present.", selectorName.c_str());
                    } else {
                        BlockData * blockData = new BlockData();
                        blockData->mSELMenuHandler = selMenuHandler;
                        
                        blockData->mTarget = target;
                        
                        return blockData;
                    }
                } else {
                    CCLOG("Unexpected empty selector.");
                }
            } else {
                CCLOG("Unexpected NULL target for selector.");
            }
        } else {
            if(selectorTarget == kCCBTargetTypeDocumentRoot) {
                pCCBReader->addDocumentCallbackNode(pNode);
                pCCBReader->addDocumentCallbackName(selectorName);
                
            } else {
                pCCBReader->addOwnerCallbackNode(pNode);
                pCCBReader->addOwnerCallbackName(selectorName);
            }
        }
    }

    return NULL;
}

BlockControlData * NodeLoader::parsePropTypeBlockControl(Node * pNode, Node * pParent, CCBReader * pCCBReader) {
    std::string selectorName = pCCBReader->readCachedString();
    int selectorTarget = pCCBReader->readInt(false);
    int controlEvents = pCCBReader->readInt(false);

    if(selectorTarget != kCCBTargetTypeNone) {
        
        if(!pCCBReader->isJSControlled()) {
            Object * target = NULL;
            if(selectorTarget == kCCBTargetTypeDocumentRoot) {
                target = pCCBReader->getAnimationManager()->getRootNode();
            } else if(selectorTarget == kCCBTargetTypeOwner) {
                target = pCCBReader->getOwner();
            }
            
            if(target != NULL) {
                if(selectorName.length() > 0) {
                    SEL_CCControlHandler selControlHandler = 0;
                    
                    CCBSelectorResolver * targetAsCCBSelectorResolver = dynamic_cast<CCBSelectorResolver *>(target);
                    
                    if(targetAsCCBSelectorResolver != NULL) {
                        selControlHandler = targetAsCCBSelectorResolver->onResolveCCBControlSelector(target, selectorName.c_str());
                    }
                    if(selControlHandler == 0) {
                        CCBSelectorResolver * ccbSelectorResolver = pCCBReader->getCCBSelectorResolver();
                        if(ccbSelectorResolver != NULL) {
                            selControlHandler = ccbSelectorResolver->onResolveCCBControlSelector(target, selectorName.c_str());
                        }
                    }
                    
                    if(selControlHandler == 0) {
                        CCLOG("Skipping selector '%s' since no CCBSelectorResolver is present.", selectorName.c_str());
                    } else {
                        BlockControlData * blockControlData = new BlockControlData();
                        blockControlData->mSELControlHandler = selControlHandler;
                        
                        blockControlData->mTarget = target;
                        blockControlData->mControlEvents = controlEvents;
                        
                        return blockControlData;
                    }
                } else {
                    CCLOG("Unexpected empty selector.");
                }
            } else {
                CCLOG("Unexpected NULL target for selector.");
            }
        } else {
            if(selectorTarget == kCCBTargetTypeDocumentRoot) {
                pCCBReader->addDocumentCallbackNode(pNode);
                pCCBReader->addDocumentCallbackName(selectorName);
                
            } else {
                pCCBReader->addOwnerCallbackNode(pNode);
                pCCBReader->addOwnerCallbackName(selectorName);
            }
        }
    }

    return NULL;
}

Node * NodeLoader::parsePropTypeCCBFile(Node * pNode, Node * pParent, CCBReader * pCCBReader) {
    std::string ccbFileName = pCCBReader->getCCBRootPath() + pCCBReader->readCachedString();

    /* Change path extension to .ccbi. */
    std::string ccbFileWithoutPathExtension = CCBReader::deletePathExtension(ccbFileName.c_str());
    ccbFileName = ccbFileWithoutPathExtension + ".ccbi";
    
    // Load sub file
    std::string path = FileUtils::sharedFileUtils()->fullPathForFilename(ccbFileName.c_str());
    unsigned long size = 0;
    unsigned char * pBytes = FileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb", &size);

    CCBReader * ccbReader = new CCBReader(pCCBReader);
    ccbReader->autorelease();
    ccbReader->getAnimationManager()->setRootContainerSize(pParent->getContentSize());
    
    Data *data = new Data(pBytes, size);
    CC_SAFE_DELETE_ARRAY(pBytes);

    data->retain();
    ccbReader->mData = data;
    ccbReader->mBytes = data->getBytes();
    ccbReader->mCurrentByte = 0;
    ccbReader->mCurrentBit = 0;
    CC_SAFE_RETAIN(pCCBReader->mOwner);
    ccbReader->mOwner = pCCBReader->mOwner;
    
    ccbReader->getAnimationManager()->mOwner = ccbReader->mOwner;

    // The assignments below are done in the CCBReader constructor.
//     ccbReader->mOwnerOutletNames = pCCBReader->mOwnerOutletNames;
//     ccbReader->mOwnerOutletNodes = pCCBReader->mOwnerOutletNodes;
//     ccbReader->mOwnerOutletNodes->retain();
//     ccbReader->mOwnerCallbackNames = pCCBReader->mOwnerCallbackNames;
//     ccbReader->mOwnerCallbackNodes = pCCBReader->mOwnerCallbackNodes;
//     ccbReader->mOwnerCallbackNodes->retain();

    data->release();
    
    Node * ccbFileNode = ccbReader->readFileWithCleanUp(false, pCCBReader->getAnimationManagers());
    
    if (ccbFileNode && ccbReader->getAnimationManager()->getAutoPlaySequenceId() != -1)
    {
        // Auto play animations
        ccbReader->getAnimationManager()->runAnimationsForSequenceIdTweenDuration(ccbReader->getAnimationManager()->getAutoPlaySequenceId(), 0);
    }
    
    if (ccbReader->isJSControlled() && pCCBReader->isJSControlled() && NULL != ccbReader->mOwner)
    {
        //set variables and callback to owner
        //set callback
        Array *ownerCallbackNames = ccbReader->getOwnerCallbackNames();
        Array *ownerCallbackNodes = ccbReader->getOwnerCallbackNodes();
        if (NULL != ownerCallbackNames && ownerCallbackNames->count() > 0 &&
            NULL != ownerCallbackNodes && ownerCallbackNodes->count() > 0)
        {
            assert(ownerCallbackNames->count() == ownerCallbackNodes->count());
            int nCount = ownerCallbackNames->count();
            for (int i = 0 ; i < nCount; i++) {
                pCCBReader->addOwnerCallbackName((dynamic_cast<String*>(ownerCallbackNames->objectAtIndex(i)))->getCString());
                pCCBReader->addOwnerCallbackNode(dynamic_cast<Node*>(ownerCallbackNames->objectAtIndex(i)) );
            }
        }
        //set variables
        Array *ownerOutletNames = ccbReader->getOwnerOutletNames();
        Array *ownerOutletNodes = ccbReader->getOwnerOutletNodes();
        if (NULL != ownerOutletNames && ownerOutletNames->count() > 0 &&
            NULL != ownerOutletNodes && ownerOutletNodes->count() > 0)
        {
            assert(ownerOutletNames->count() == ownerOutletNodes->count());
            int nCount = ownerOutletNames->count();
            for (int i = 0 ; i < nCount; i++) {
                pCCBReader->addOwnerOutletName((dynamic_cast<String*>(ownerOutletNames->objectAtIndex(i)))->getCString());
                pCCBReader->addOwnerOutletNode(dynamic_cast<Node*>(ownerOutletNodes->objectAtIndex(i)) );
            }
        }
    }
    return ccbFileNode;
}



void NodeLoader::onHandlePropTypePosition(Node * pNode, Node * pParent, const char* pPropertyName, Point pPosition, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_POSITION) == 0) {
        pNode->setPosition(pPosition);
    } else {
        ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    }
}

void NodeLoader::onHandlePropTypePoint(Node * pNode, Node * pParent, const char* pPropertyName, Point pPoint, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_ANCHORPOINT) == 0) {
        pNode->setAnchorPoint(pPoint);
    } else {
        ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    }
}

void NodeLoader::onHandlePropTypePointLock(Node * pNode, Node * pParent, const char* pPropertyName, Point pPointLock, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void NodeLoader::onHandlePropTypeSize(Node * pNode, Node * pParent, const char* pPropertyName, Size pSize, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_CONTENTSIZE) == 0) {
        pNode->setContentSize(pSize);
    } else {
        ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    }
}

void NodeLoader::onHandlePropTypeFloatXY(Node * pNode, Node * pParent, const char* pPropertyName, float * pFloat, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_SKEW) == 0) {
        pNode->setSkewX(pFloat[0]);
        pNode->setSkewY(pFloat[1]);
    } else {
        ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    }
}


void NodeLoader::onHandlePropTypeScaleLock(Node * pNode, Node * pParent, const char* pPropertyName, float * pScaleLock, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_SCALE) == 0) {
        pNode->setScaleX(pScaleLock[0]);
        pNode->setScaleY(pScaleLock[1]);
    } else {
        ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    }
}

void NodeLoader::onHandlePropTypeFloat(Node * pNode, Node * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader) {
//    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    // It may be a custom property, add it to custom property dictionary.
    _customProperties->setObject(CCBValue::create(pFloat), pPropertyName);
}


void NodeLoader::onHandlePropTypeDegrees(Node * pNode, Node * pParent, const char* pPropertyName, float pDegrees, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_ROTATION) == 0) {
        pNode->setRotation(pDegrees);
    } else if(strcmp(pPropertyName, PROPERTY_ROTATIONX) == 0) {
        pNode->setRotationX(pDegrees);
    } else if(strcmp(pPropertyName, PROPERTY_ROTATIONY) == 0) {
        pNode->setRotationY(pDegrees);
    }
    else {
        ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    }
}

void NodeLoader::onHandlePropTypeFloatScale(Node * pNode, Node * pParent, const char* pPropertyName, float pFloatScale, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void NodeLoader::onHandlePropTypeInteger(Node * pNode, Node * pParent, const char* pPropertyName, int pInteger, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_TAG) == 0) {
        pNode->setTag(pInteger);
    } else {
 //       ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
        // It may be a custom property, add it to custom property dictionary.
        _customProperties->setObject(CCBValue::create(pInteger), pPropertyName);
    }
}

void NodeLoader::onHandlePropTypeIntegerLabeled(Node * pNode, Node * pParent, const char* pPropertyName, int pIntegerLabeled, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void NodeLoader::onHandlePropTypeFloatVar(Node * pNode, Node * pParent, const char* pPropertyName, float * pFloatVar, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void NodeLoader::onHandlePropTypeCheck(Node * pNode, Node * pParent, const char* pPropertyName, bool pCheck, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_VISIBLE) == 0) {
        pNode->setVisible(pCheck);
    } else if(strcmp(pPropertyName, PROPERTY_IGNOREANCHORPOINTFORPOSITION) == 0) {
        pNode->ignoreAnchorPointForPosition(pCheck);
    } else {
        //ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
        // It may be a custom property, add it to custom property dictionary.
        _customProperties->setObject(CCBValue::create(pCheck), pPropertyName);
    }
}

void NodeLoader::onHandlePropTypeSpriteFrame(Node * pNode, Node * pParent, const char* pPropertyName, SpriteFrame * pSpriteFrame, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void NodeLoader::onHandlePropTypeAnimation(Node * pNode, Node * pParent, const char* pPropertyName, Animation * pAnimation, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void NodeLoader::onHandlePropTypeTexture(Node * pNode, Node * pParent, const char* pPropertyName, Texture2D * pTexture2D, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void NodeLoader::onHandlePropTypeByte(Node * pNode, Node * pParent, const char* pPropertyName, unsigned char pByte, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void NodeLoader::onHandlePropTypeColor3(Node * pNode, Node * pParent, const char* pPropertyName, ccColor3B pColor3B, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void NodeLoader::onHandlePropTypeColor4FVar(Node * pNode, Node * pParent, const char* pPropertyName, ccColor4F * pColor4FVar, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void NodeLoader::onHandlePropTypeFlip(Node * pNode, Node * pParent, const char* pPropertyName, bool * pFlip, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void NodeLoader::onHandlePropTypeBlendFunc(Node * pNode, Node * pParent, const char* pPropertyName, ccBlendFunc pBlendFunc, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void NodeLoader::onHandlePropTypeFntFile(Node * pNode, Node * pParent, const char* pPropertyName, const char* pFntFile, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void NodeLoader::onHandlePropTypeString(Node * pNode, Node * pParent, const char* pPropertyName, const char * pString, CCBReader * pCCBReader) {
//    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    // It may be a custom property, add it to custom property dictionary.
    _customProperties->setObject(CCBValue::create(pString), pPropertyName);
}

void NodeLoader::onHandlePropTypeText(Node * pNode, Node * pParent, const char* pPropertyName, const char * pText, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void NodeLoader::onHandlePropTypeFontTTF(Node * pNode, Node * pParent, const char* pPropertyName, const char * pFontTTF, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void NodeLoader::onHandlePropTypeBlock(Node * pNode, Node * pParent, const char* pPropertyName, BlockData * pBlockData, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void NodeLoader::onHandlePropTypeBlockControl(Node * pNode, Node * pParent, const char* pPropertyName, BlockControlData * pBlockControlData, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void NodeLoader::onHandlePropTypeCCBFile(Node * pNode, Node * pParent, const char* pPropertyName, Node * pCCBFileNode, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

NS_CC_EXT_END
