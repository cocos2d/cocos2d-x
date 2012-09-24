#include "CCNodeLoader.h"
#include "CCBSelectorResolver.h"
#include "CCBMemberVariableAssigner.h"
#include "CCBAnimationManager.h"
#include "CCData.h"
#include "CCNode+CCBRelativePositioning.h"

using namespace std;

NS_CC_EXT_BEGIN

CCNode * CCNodeLoader::loadCCNode(CCNode * pParent, CCBReader * pCCBReader) {
    CCNode * ccNode = this->createCCNode(pParent, pCCBReader);

    //this->parseProperties(ccNode, pParent, pCCBReader);

    return ccNode;
}

void CCNodeLoader::parseProperties(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    int numRegularProps = pCCBReader->readInt(false);
    int numExturaProps = pCCBReader->readInt(false);
    int propertyCount = numRegularProps + numExturaProps;

    for(int i = 0; i < propertyCount; i++) {
        bool isExtraProp = (i >= numRegularProps);
        int type = pCCBReader->readInt(false);
        CCString * propertyName = pCCBReader->readCachedString();

        // Check if the property can be set for this platform
        bool setProp = false;
        
        int platform = pCCBReader->readByte();
        if(platform == kCCBPlatformAll) 
        {
            setProp = true;
        }
#ifdef __CC_PLATFORM_IOS
        if(platform == kCCBPlatformIOS) 
        {
            setProp = true;
        }
#elif defined(__CC_PLATFORM_MAC)
        if(platform == kCCBPlatformMac) 
        {
            setProp = true;
        }
#endif
        
        // Forward properties for sub ccb files
        if (dynamic_cast<CCBFile*>(pNode) != NULL)
        {
            CCBFile *ccbNode = (CCBFile*)pNode;
            if (ccbNode->getCCBFileNode() && isExtraProp)
            {
                pNode = ccbNode->getCCBFileNode();
                
                // Skip properties that doesn't have a value to override
                CCArray *extraPropsNames = (CCArray*)pNode->getUserObject();
                setProp &= extraPropsNames->containsObject(propertyName);
            }
        }
        else if (isExtraProp && pNode == pCCBReader->getAnimationManager()->getRootNode())
        {
            CCArray *extraPropsNames = (CCArray*)pNode->getUserObject();
            if (! extraPropsNames)
            {
                extraPropsNames = CCArray::create();
                pNode->setUserObject(extraPropsNames);
            }
            
            extraPropsNames->addObject(propertyName);
        }

        switch(type) 
        {
            case kCCBPropTypePosition: 
            {
                CCPoint position = this->parsePropTypePosition(pNode, pParent, pCCBReader, propertyName->getCString());
                if (setProp) 
                {
                    this->onHandlePropTypePosition(pNode, pParent, propertyName, position, pCCBReader);
                }
                break;
            }
            case kCCBPropTypePoint: 
            {
                CCPoint point = this->parsePropTypePoint(pNode, pParent, pCCBReader);
                if (setProp) 
                {
                    this->onHandlePropTypePoint(pNode, pParent, propertyName, point, pCCBReader);
                }
                break;
            }
            case kCCBPropTypePointLock: 
            {
                CCPoint pointLock = this->parsePropTypePointLock(pNode, pParent, pCCBReader);
                if (setProp) 
                {
                    this->onHandlePropTypePointLock(pNode, pParent, propertyName, pointLock, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeSize: {
                CCSize size = this->parsePropTypeSize(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeSize(pNode, pParent, propertyName, size, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeScaleLock: 
            {
                float * scaleLock = this->parsePropTypeScaleLock(pNode, pParent, pCCBReader, propertyName->getCString());
                if(setProp) 
                {
                    this->onHandlePropTypeScaleLock(pNode, pParent, propertyName, scaleLock, pCCBReader);
                }
                CC_SAFE_DELETE_ARRAY(scaleLock);
                break;
            }
            case kCCBPropTypeFloat: 
            {
                float f = this->parsePropTypeFloat(pNode, pParent, pCCBReader);
                if(setProp) 
                {
                    this->onHandlePropTypeFloat(pNode, pParent, propertyName, f, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeDegrees: 
            {
                float degrees = this->parsePropTypeDegrees(pNode, pParent, pCCBReader, propertyName->getCString());
                if(setProp) 
                {
                    this->onHandlePropTypeDegrees(pNode, pParent, propertyName, degrees, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeFloatScale: 
            {
                float floatScale = this->parsePropTypeFloatScale(pNode, pParent, pCCBReader);
                if(setProp) 
                {
                    this->onHandlePropTypeFloatScale(pNode, pParent, propertyName, floatScale, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeInteger: 
            {
                int integer = this->parsePropTypeInteger(pNode, pParent, pCCBReader);
                if(setProp) 
                {
                    this->onHandlePropTypeInteger(pNode, pParent, propertyName, integer, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeIntegerLabeled: 
            {
                int integerLabeled = this->parsePropTypeIntegerLabeled(pNode, pParent, pCCBReader);
                if(setProp) 
                {
                    this->onHandlePropTypeIntegerLabeled(pNode, pParent, propertyName, integerLabeled, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeFloatVar: 
            {
                float * floatVar = this->parsePropTypeFloatVar(pNode, pParent, pCCBReader);
                if(setProp) 
                {
                    this->onHandlePropTypeFloatVar(pNode, pParent, propertyName, floatVar, pCCBReader);
                }
                CC_SAFE_DELETE_ARRAY(floatVar);
                break;
            }
            case kCCBPropTypeCheck: 
            {
                bool check = this->parsePropTypeCheck(pNode, pParent, pCCBReader, propertyName->getCString());
                if(setProp) 
                {
                    this->onHandlePropTypeCheck(pNode, pParent, propertyName, check, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeSpriteFrame: {
                CCSpriteFrame * ccSpriteFrame = this->parsePropTypeSpriteFrame(pNode, pParent, pCCBReader, propertyName->getCString());
                if(setProp) 
                {
                    this->onHandlePropTypeSpriteFrame(pNode, pParent, propertyName, ccSpriteFrame, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeAnimation: 
            {
                CCAnimation * ccAnimation = this->parsePropTypeAnimation(pNode, pParent, pCCBReader);
                if(setProp) 
                {
                    this->onHandlePropTypeAnimation(pNode, pParent, propertyName, ccAnimation, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeTexture: 
            {
                CCTexture2D * ccTexture2D = this->parsePropTypeTexture(pNode, pParent, pCCBReader);
                if(setProp) 
                {
                    this->onHandlePropTypeTexture(pNode, pParent, propertyName, ccTexture2D, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeByte: 
            {
                unsigned char byte = this->parsePropTypeByte(pNode, pParent, pCCBReader, propertyName->getCString());
                if(setProp) 
                {
                    this->onHandlePropTypeByte(pNode, pParent, propertyName, byte, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeColor3: 
            {
                ccColor3B color3B = this->parsePropTypeColor3(pNode, pParent, pCCBReader, propertyName->getCString());
                if(setProp) 
                {
                    this->onHandlePropTypeColor3(pNode, pParent, propertyName, color3B, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeColor4FVar: 
            {
                ccColor4F * color4FVar = this->parsePropTypeColor4FVar(pNode, pParent, pCCBReader);
                if(setProp) 
                {
                    this->onHandlePropTypeColor4FVar(pNode, pParent, propertyName, color4FVar, pCCBReader);
                }
                CC_SAFE_DELETE_ARRAY(color4FVar);
                break;
            }
            case kCCBPropTypeFlip: {
                bool * flip = this->parsePropTypeFlip(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeFlip(pNode, pParent, propertyName, flip, pCCBReader);
                }
                CC_SAFE_DELETE_ARRAY(flip);
                break;
            }
            case kCCBPropTypeBlendmode: 
            {
                ccBlendFunc blendFunc = this->parsePropTypeBlendFunc(pNode, pParent, pCCBReader);
                if(setProp) 
                {
                    this->onHandlePropTypeBlendFunc(pNode, pParent, propertyName, blendFunc, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeFntFile: 
            {
                CCString * fntFile = this->parsePropTypeFntFile(pNode, pParent, pCCBReader);
                if(setProp) 
                {
                    this->onHandlePropTypeFntFile(pNode, pParent, propertyName, fntFile, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeFontTTF: {
                CCString * fontTTF = this->parsePropTypeFontTTF(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeFontTTF(pNode, pParent, propertyName, fontTTF, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeString: {
                CCString * string = this->parsePropTypeString(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeString(pNode, pParent, propertyName, string, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeText: {
                CCString * text = this->parsePropTypeText(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeText(pNode, pParent, propertyName, text, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeBlock: {
                BlockData * blockData = this->parsePropTypeBlock(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeBlock(pNode, pParent, propertyName, blockData, pCCBReader);
                }
                CC_SAFE_DELETE(blockData);
                break;
            }
            case kCCBPropTypeBlockCCControl: {
                BlockCCControlData * blockCCControlData = this->parsePropTypeBlockCCControl(pNode, pParent, pCCBReader);
                if(setProp && blockCCControlData != NULL) {
                    this->onHandlePropTypeBlockCCControl(pNode, pParent, propertyName, blockCCControlData, pCCBReader);
                }
                CC_SAFE_DELETE(blockCCControlData);
                break;
            }
            case kCCBPropTypeCCBFile: {
                CCNode * ccbFileNode = this->parsePropTypeCCBFile(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeCCBFile(pNode, pParent, propertyName, ccbFileNode, pCCBReader);
                }
                break;
            }
            default:
                ASSERT_FAIL_UNEXPECTED_PROPERTYTYPE(type);
                break;
        }
    }
}

CCPoint CCNodeLoader::parsePropTypePosition(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader, const char *pPropertyName) {
    float x = pCCBReader->readFloat();
    float y = pCCBReader->readFloat();
    
    int type = pCCBReader->readInt(false);
    
    CCSize containerSize = pCCBReader->getAnimationManager()->getContainerSize(pParent);
    
    CCPoint pt = getAbsolutePosition(ccp(x,y), type, containerSize, pPropertyName);
    pNode->setPosition(getAbsolutePosition(pt, type, containerSize, pPropertyName));;
    
    if (pCCBReader->getAnimatedProperties()->find(pPropertyName) != pCCBReader->getAnimatedProperties()->end())
    {
        CCArray *baseValue = CCArray::create(CCBValue::create(x),
                                             CCBValue::create(y),
                                             CCBValue::create(type),
                                             NULL);
        pCCBReader->getAnimationManager()->setBaseValue(baseValue, pNode, pPropertyName);
    }

    return pt;
}

CCPoint CCNodeLoader::parsePropTypePoint(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) 
{
    float x = pCCBReader->readFloat();
    float y = pCCBReader->readFloat();

    return CCPoint(x, y);
}

CCPoint CCNodeLoader::parsePropTypePointLock(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    float x = pCCBReader->readFloat();
    float y = pCCBReader->readFloat();

    return CCPoint(x, y);
}

CCSize CCNodeLoader::parsePropTypeSize(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    float width = pCCBReader->readFloat();
    float height = pCCBReader->readFloat();

    int type = pCCBReader->readInt(false);

    CCSize containerSize = pCCBReader->getAnimationManager()->getContainerSize(pParent);

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
        }
        default:
            break;
    }
    
    return CCSize(width, height);
}

float * CCNodeLoader::parsePropTypeScaleLock(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader, const char *pPropertyName) {
    float x = pCCBReader->readFloat();
    float y = pCCBReader->readFloat();
    
    int type = pCCBReader->readInt(false);
    
    setRelativeScale(pNode, x, y, type, pPropertyName);
    
    if (pCCBReader->getAnimatedProperties()->find(pPropertyName) != pCCBReader->getAnimatedProperties()->end())
    {
        CCArray *baseValue = CCArray::create(CCBValue::create(x),
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

float CCNodeLoader::parsePropTypeFloat(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    return pCCBReader->readFloat();
}

float CCNodeLoader::parsePropTypeDegrees(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader, const char *pPropertyName) {
    float ret = pCCBReader->readFloat();
    if (pCCBReader->getAnimatedProperties()->find(pPropertyName) != pCCBReader->getAnimatedProperties()->end())
    {
        CCBValue *value = CCBValue::create(ret);
        pCCBReader->getAnimationManager()->setBaseValue(value, pNode, pPropertyName);
    }
    
    return ret;
}

float CCNodeLoader::parsePropTypeFloatScale(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) 
{
    float f = pCCBReader->readFloat();

    int type = pCCBReader->readInt(false);
    
    if(type == kCCBScaleTypeMultiplyResolution) 
    {
        f *= pCCBReader->getResolutionScale();
    }

    return f;
}

int CCNodeLoader::parsePropTypeInteger(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) 
{
    return pCCBReader->readInt(true);
}

int CCNodeLoader::parsePropTypeIntegerLabeled(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) 
{
    return pCCBReader->readInt(true);
}

float * CCNodeLoader::parsePropTypeFloatVar(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) 
{
    float f = pCCBReader->readFloat();
    float fVar = pCCBReader->readFloat();
    
    float * arr = new float[2];
    arr[0] = f;
    arr[1] = fVar;
    
    return arr;
}

bool CCNodeLoader::parsePropTypeCheck(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader, const char *pPropertyName) 
{
    bool ret = pCCBReader->readBool();
    
    if (pCCBReader->getAnimatedProperties()->find(pPropertyName) != pCCBReader->getAnimatedProperties()->end())
    {
        CCBValue *value = CCBValue::create(ret);
        pCCBReader->getAnimationManager()->setBaseValue(value, pNode, pPropertyName);
    }
    
    return ret;
}


CCSpriteFrame * CCNodeLoader::parsePropTypeSpriteFrame(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader, const char *pPropertyName) 
{
    CCString * spriteSheet = pCCBReader->readCachedString();
    CCString * spriteFile = pCCBReader->readCachedString();
    
    CCSpriteFrame *spriteFrame = NULL;
    if (spriteFile->length() != 0)
    {
        if (spriteSheet->length() == 0)
        {
            CCTexture2D * texture = CCTextureCache::sharedTextureCache()->addImage(spriteFile->getCString());
            CCRect bounds = CCRectMake(0, 0, texture->getContentSize().width, texture->getContentSize().height);
            spriteFrame = CCSpriteFrame::createWithTexture(texture, bounds);
        }
        else 
        {
            CCSpriteFrameCache * frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
            
            // Load the sprite sheet only if it is not loaded
            if (pCCBReader->getLoadedSpriteSheet().find(spriteSheet->getCString()) == pCCBReader->getLoadedSpriteSheet().end())
            {
                frameCache->addSpriteFramesWithFile(spriteSheet->getCString());
                pCCBReader->getLoadedSpriteSheet().insert(spriteSheet->getCString());
            }
            
            spriteFrame = frameCache->spriteFrameByName(spriteFile->getCString());
        }
        
        if (pCCBReader->getAnimatedProperties()->find(pPropertyName) != pCCBReader->getAnimatedProperties()->end())
        {
            pCCBReader->getAnimationManager()->setBaseValue(spriteFrame, pNode, pPropertyName);
        }
    }
    
    return spriteFrame;
}

CCAnimation * CCNodeLoader::parsePropTypeAnimation(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    CCString * animationFile = pCCBReader->readCachedString();
    CCString * animation = pCCBReader->readCachedString();
    
    CCAnimation * ccAnimation = NULL;
    
    // Support for stripping relative file paths, since ios doesn't currently
    // know what to do with them, since its pulling from bundle.
    // Eventually this should be handled by a client side asset manager
    // interface which figured out what resources to load.
    // TODO Does this problem exist in C++?
    animation = CCBReader::lastPathComponent(animation);
    animationFile = CCBReader::lastPathComponent(animationFile);
    
    if (animation != NULL && animation->compare("") != 0) 
    {
        CCAnimationCache * animationCache = CCAnimationCache::sharedAnimationCache();
        animationCache->addAnimationsWithFile(animationFile->getCString());
        
        ccAnimation = animationCache->animationByName(animation->getCString());
    }
    return ccAnimation;
}

CCTexture2D * CCNodeLoader::parsePropTypeTexture(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    CCString * spriteFile = pCCBReader->readCachedString();
    
    if (spriteFile->compare("") != 0)
    {
        return CCTextureCache::sharedTextureCache()->addImage(spriteFile->getCString());
    }
    else 
    {
        return NULL;
    }
}

unsigned char CCNodeLoader::parsePropTypeByte(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader, const char *pPropertyName) 
{
    unsigned char ret = pCCBReader->readByte();
    
    if (pCCBReader->getAnimatedProperties()->find(pPropertyName) != pCCBReader->getAnimatedProperties()->end())
    {
        pCCBReader->getAnimationManager()->setBaseValue(CCBValue::create(ret), pNode, pPropertyName);
    }
    
    return ret;
}

ccColor3B CCNodeLoader::parsePropTypeColor3(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader, const char *pPropertyName) {
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

ccColor4F * CCNodeLoader::parsePropTypeColor4FVar(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
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

bool * CCNodeLoader::parsePropTypeFlip(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    bool flipX = pCCBReader->readBool();
    bool flipY = pCCBReader->readBool();

    bool * arr = new bool[2];
    arr[0] = flipX;
    arr[1] = flipY;

    return arr;
}

ccBlendFunc CCNodeLoader::parsePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) 
{
    int source = pCCBReader->readInt(false);
    int destination = pCCBReader->readInt(false);
    
    ccBlendFunc blendFunc;
    blendFunc.src = source;
    blendFunc.dst = destination;
    
    return blendFunc;
}

CCString * CCNodeLoader::parsePropTypeFntFile(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) 
{
    return pCCBReader->readCachedString();
}

CCString * CCNodeLoader::parsePropTypeString(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    return pCCBReader->readCachedString();
}

CCString * CCNodeLoader::parsePropTypeText(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    return pCCBReader->readCachedString();
}

CCString * CCNodeLoader::parsePropTypeFontTTF(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    CCString * fontTTF = pCCBReader->readCachedString();

    // CCString * ttfEnding = CCString::create(".ttf");

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

BlockData * CCNodeLoader::parsePropTypeBlock(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    CCString * selectorName = pCCBReader->readCachedString();
    int selectorTarget = pCCBReader->readInt(false);

    if(selectorTarget != kCCBTargetTypeNone) {
        CCObject * target = NULL;
        if(selectorTarget == kCCBTargetTypeDocumentRoot) {
            target = pCCBReader->getAnimationManager()->getRootNode();
        } else if(selectorTarget == kCCBTargetTypeOwner) {
            target = pCCBReader->getOwner();
            
            /* Scripting specific code because selector function is common for all callbacks.
             * So if we had 1 target and 1 selector function, the context (callback function name)
             * would get lost. Hence the need for a new target for each callback.
             */
            if(pCCBReader->hasScriptingOwner) {
                CCBScriptOwnerProtocol *proxy = dynamic_cast<CCBScriptOwnerProtocol *>(pCCBReader->getOwner());
                if(proxy) {
                    target = dynamic_cast<CCObject *>(proxy->createNew());
                }
            }
        }

        if(target != NULL) {
            if(selectorName->length() > 0) {
                SEL_MenuHandler selMenuHandler = 0;

                CCBSelectorResolver * targetAsCCBSelectorResolver = dynamic_cast<CCBSelectorResolver *>(target);

                if(targetAsCCBSelectorResolver != NULL) {
                    selMenuHandler = targetAsCCBSelectorResolver->onResolveCCBCCMenuItemSelector(target, selectorName);
                }
                if(selMenuHandler == 0) {
                    CCBSelectorResolver * ccbSelectorResolver = pCCBReader->getCCBSelectorResolver();
                    if(ccbSelectorResolver != NULL) {
                        selMenuHandler = ccbSelectorResolver->onResolveCCBCCMenuItemSelector(target, selectorName);
                    }
                }

                if(selMenuHandler == 0) {
                    CCLOG("Skipping selector '%s' since no CCBSelectorResolver is present.", selectorName->getCString());
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
    }

    return NULL;
}

BlockCCControlData * CCNodeLoader::parsePropTypeBlockCCControl(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    CCString * selectorName = pCCBReader->readCachedString();
    int selectorTarget = pCCBReader->readInt(false);
    int controlEvents = pCCBReader->readInt(false);

    if(selectorTarget != kCCBTargetTypeNone) {
        CCObject * target = NULL;
        if(selectorTarget == kCCBTargetTypeDocumentRoot) {
            target = pCCBReader->getAnimationManager()->getRootNode();
        } else if(selectorTarget == kCCBTargetTypeOwner) {
            target = pCCBReader->getOwner();
        }

        if(target != NULL) {
            if(selectorName->length() > 0) {
                SEL_CCControlHandler selCCControlHandler = 0;

                CCBSelectorResolver * targetAsCCBSelectorResolver = dynamic_cast<CCBSelectorResolver *>(target);

                if(targetAsCCBSelectorResolver != NULL) {
                    selCCControlHandler = targetAsCCBSelectorResolver->onResolveCCBCCControlSelector(target, selectorName);
                }
                if(selCCControlHandler == 0) {
                    CCBSelectorResolver * ccbSelectorResolver = pCCBReader->getCCBSelectorResolver();
                    if(ccbSelectorResolver != NULL) {
                        selCCControlHandler = ccbSelectorResolver->onResolveCCBCCControlSelector(target, selectorName);
                    }
                }

                if(selCCControlHandler == 0) {
                    CCLOG("Skipping selector '%s' since no CCBSelectorResolver is present.", selectorName->getCString());
                } else {
                    BlockCCControlData * blockCCControlData = new BlockCCControlData();
                    blockCCControlData->mSELCCControlHandler = selCCControlHandler;

                    blockCCControlData->mTarget = target;
                    blockCCControlData->mControlEvents = controlEvents;

                    return blockCCControlData;
                }
            } else {
                CCLOG("Unexpected empty selector.");
            }
        } else {
            CCLOG("Unexpected NULL target for selector.");
        }
    }

    return NULL;
}

CCNode * CCNodeLoader::parsePropTypeCCBFile(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    CCString * ccbFileName = pCCBReader->readCachedString();

    /* Change path extension to .ccbi. */
    CCString * ccbFileWithoutPathExtension = CCBReader::deletePathExtension(ccbFileName);
    ccbFileName = CCBReader::concat(ccbFileWithoutPathExtension, CCString::create(".ccbi"));
    
    // Load sub file
    const char *path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(ccbFileName->getCString());
    CCBReader * ccbReader = new CCBReader(pCCBReader);
    ccbReader->autorelease();

    unsigned long size;
    
    unsigned char * pBytes = CCFileUtils::sharedFileUtils()->getFileData(path, "rb", &size);
    CCData *data = new CCData(pBytes, size);
    ccbReader->initWithData(data, pCCBReader->getOwner());
    data->release();
    ccbReader->getAnimationManager()->setRootContainerSize(pParent->getContentSize());

    CCNode * ccbFileNode = ccbReader->readFileWithCleanUp(false);
    
    if (ccbFileNode && ccbReader->getAnimationManager()->getAutoPlaySequenceId() != -1)
    {
        // Auto play animations
        ccbReader->getAnimationManager()->runAnimations(ccbReader->getAnimationManager()->getAutoPlaySequenceId(), 0);
    }
    
    return ccbFileNode;
}



void CCNodeLoader::onHandlePropTypePosition(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCPoint pPosition, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_POSITION) == 0) {
        pNode->setPosition(pPosition);
    } else {
        ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    }
}

void CCNodeLoader::onHandlePropTypePoint(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCPoint pPoint, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_ANCHORPOINT) == 0) {
        pNode->setAnchorPoint(pPoint);
    } else {
        ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    }
}

void CCNodeLoader::onHandlePropTypePointLock(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCPoint pPointLock, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeSize(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCSize pSize, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_CONTENTSIZE) == 0) {
        pNode->setContentSize(pSize);
    } else {
        ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    }
}

void CCNodeLoader::onHandlePropTypeScaleLock(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, float * pScaleLock, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_SCALE) == 0) {
        pNode->setScaleX(pScaleLock[0]);
        pNode->setScaleY(pScaleLock[1]);
    } else {
        ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    }
}

void CCNodeLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, float pFloat, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeDegrees(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, float pDegrees, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_ROTATION) == 0) {
        pNode->setRotation(pDegrees);
    } else {
        ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    }
}

void CCNodeLoader::onHandlePropTypeFloatScale(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, float pFloatScale, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeInteger(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, int pInteger, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_TAG) == 0) {
        pNode->setTag(pInteger);
    } else {
        ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    }
}

void CCNodeLoader::onHandlePropTypeIntegerLabeled(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, int pIntegerLabeled, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeFloatVar(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, float * pFloatVar, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, bool pCheck, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_VISIBLE) == 0) {
        pNode->setVisible(pCheck);
    } else if(pPropertyName->compare(PROPERTY_IGNOREANCHORPOINTFORPOSITION) == 0) {
        pNode->ignoreAnchorPointForPosition(pCheck);
    } else {
        ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    }
}

void CCNodeLoader::onHandlePropTypeSpriteFrame(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCSpriteFrame * pCCSpriteFrame, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeAnimation(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCAnimation * pCCAnimation, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeTexture(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCTexture2D * pCCTexture2D, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeByte(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, unsigned char pByte, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, ccColor3B pCCColor3B, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeColor4FVar(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, ccColor4F * pCCColor4FVar, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeFlip(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, bool * pFlip, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, ccBlendFunc pCCBlendFunc, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeFntFile(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCString * pFntFile, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeString(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCString * pString, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeText(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCString * pText, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeFontTTF(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCString * pFontTTF, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeBlock(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, BlockData * pBlockData, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeBlockCCControl(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, BlockCCControlData * pBlockCCControlData, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeCCBFile(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCNode * pCCBFileNode, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

NS_CC_EXT_END
