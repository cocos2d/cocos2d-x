#import "CCNodeLoader.h"

#define PROPERTY_POSITION "position"
#define PROPERTY_CONTENTSIZE "contentSize"
#define PROPERTY_ANCHORPOINT "anchorPoint"
#define PROPERTY_SCALE "scale"
#define PROPERTY_ROTATION "rotation"
#define PROPERTY_TAG "tag"
#define PROPERTY_IGNOREANCHORPOINTFORPOSITION "ignoreAnchorPointForPosition"
#define PROPERTY_VISIBLE "visible"

#define ASSERT_FAIL_UNEXPECTED_PROPERTY(PROPERTY) printf("Unexpected property: '%s'!\n", PROPERTY); assert(false)
#define ASSERT_FAIL_UNEXPECTED_PROPERTYTYPE(PROPERTYTYPE) printf("Unexpected property type: '%d'!\n", PROPERTYTYPE); assert(false)

using namespace cocos2d;
using namespace cocos2d::extension;

CCNode * CCNodeLoader::loadCCNode(CCNode * pParent, CCBReader * pCCBReader) {
    CCNode * ccNode = this->createCCNode(pParent, pCCBReader);

    this->parseProperties(ccNode, pParent, pCCBReader);

    return ccNode;
}

CCNode * CCNodeLoader::createCCNode(CCNode * pParent, CCBReader * pCCBReader) {
    return CCNode::node();
}

void CCNodeLoader::parseProperties(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    int propertyCount = pCCBReader->readInt(false);
    for(int i = 0; i < propertyCount; i++) {
        int type = pCCBReader->readInt(false);
        const char * propertyName = pCCBReader->readCachedString();

        // Check if the property can be set for this platform
        bool setProp = false;
        
        int platform = pCCBReader->readByte();
        if(platform == kCCBPlatformAll) {
            setProp = true;
        }
#ifdef __CC_PLATFORM_IOS
        if(platform == kCCBPlatformIOS) {
            setProp = true;
        }
#elif defined(__CC_PLATFORM_MAC)
        if(platform == kCCBPlatformMac) {
            setProp = true;
        }
#endif

        switch(type) {
            case kCCBPropTypePosition: {
                CCPoint position = this->parsePropTypePosition(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypePosition(pNode, pParent, propertyName, position, pCCBReader);
                }
                break;
            }
            case kCCBPropTypePoint: {
                CCPoint point = this->parsePropTypePoint(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypePoint(pNode, pParent, propertyName, point, pCCBReader);
                }
                break;
            }
            case kCCBPropTypePointLock: {
                CCPoint pointLock = this->parsePropTypePointLock(pNode, pParent, pCCBReader);
                if(setProp) {
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
            case kCCBPropTypeScaleLock: {
                float * scaleLock = this->parsePropTypeScaleLock(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeScaleLock(pNode, pParent, propertyName, scaleLock, pCCBReader);
                }
                delete scaleLock;
                break;
            }
            case kCCBPropTypeFloat: {
                float f = this->parsePropTypeFloat(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeFloat(pNode, pParent, propertyName, f, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeDegrees: {
                float degrees = this->parsePropTypeDegrees(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeDegrees(pNode, pParent, propertyName, degrees, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeFloatScale: {
                float floatScale = this->parsePropTypeFloatScale(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeFloatScale(pNode, pParent, propertyName, floatScale, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeInteger: {
                int integer = this->parsePropTypeInteger(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeInteger(pNode, pParent, propertyName, integer, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeIntegerLabeled: {
                int integerLabeled = this->parsePropTypeIntegerLabeled(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeIntegerLabeled(pNode, pParent, propertyName, integerLabeled, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeFloatVar: {
                float * floatVar = this->parsePropTypeFloatVar(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeFloatVar(pNode, pParent, propertyName, floatVar, pCCBReader);
                }
                delete floatVar;
                break;
            }
            case kCCBPropTypeCheck: {
                bool check = this->parsePropTypeCheck(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeCheck(pNode, pParent, propertyName, check, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeSpriteFrame: {
                CCSpriteFrame * ccSpriteFrame = this->parsePropTypeSpriteFrame(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeSpriteFrame(pNode, pParent, propertyName, ccSpriteFrame, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeAnimation: {
                CCAnimation * ccAnimation = this->parsePropTypeAnimation(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeAnimation(pNode, pParent, propertyName, ccAnimation, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeTexture: {
                CCTexture2D * ccTexture2D = this->parsePropTypeTexture(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeTexture(pNode, pParent, propertyName, ccTexture2D, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeByte: {
                unsigned char byte = this->parsePropTypeByte(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeByte(pNode, pParent, propertyName, byte, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeColor3: {
                ccColor3B color3B = this->parsePropTypeColor3(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeColor3(pNode, pParent, propertyName, color3B, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeColor4FVar: {
                ccColor4F * color4FVar = this->parsePropTypeColor4FVar(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeColor4FVar(pNode, pParent, propertyName, color4FVar, pCCBReader);
                }
                delete color4FVar;
                break;
            }
            case kCCBPropTypeFlip: {
                bool * flip = this->parsePropTypeFlip(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeFlip(pNode, pParent, propertyName, flip, pCCBReader);
                }
                delete flip;
                break;
            }
            case kCCBPropTypeBlendFunc: {
                ccBlendFunc blendFunc = this->parsePropTypeBlendFunc(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeBlendFunc(pNode, pParent, propertyName, blendFunc, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeFntFile: {
                const char * fntFile = this->parsePropTypeFntFile(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeFntFile(pNode, pParent, propertyName, fntFile, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeFontTTF: {
                const char * fontTTF = this->parsePropTypeFontTTF(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeFontTTF(pNode, pParent, propertyName, fontTTF, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeString: {
                const char * string = this->parsePropTypeString(pNode, pParent, pCCBReader);
                if(setProp) {
                    this->onHandlePropTypeString(pNode, pParent, propertyName, string, pCCBReader);
                }
                break;
            }
            case kCCBPropTypeText: {
                const char * text = this->parsePropTypeText(pNode, pParent, pCCBReader);
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
                delete blockData;
                break;
            }
            case kCCBPropTypeBlockCCControl: {
                BlockCCControlData * blockCCControlData = this->parsePropTypeBlockCCControl(pNode, pParent, pCCBReader);
                if(setProp && blockCCControlData != NULL) {
                    this->onHandlePropTypeBlockCCControl(pNode, pParent, propertyName, blockCCControlData, pCCBReader);
                }
                delete blockCCControlData;
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

CCPoint CCNodeLoader::parsePropTypePosition(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    float x = pCCBReader->readFloat();
    float y = pCCBReader->readFloat();
    
    int type = pCCBReader->readInt(false);
    
    CCSize containerSize = pCCBReader->getContainerSize(pParent);
    
    switch (type) {
        case kCCBPositionTypeRelativeBottomLeft: {
            /* Nothing. */
            break;
        }
        case kCCBPositionTypeRelativeTopLeft: {
            y = containerSize.height - y;
            break;
        }
        case kCCBPositionTypeRelativeTopRight: {
            x = containerSize.width - x;
            y = containerSize.height - y;
            break;
        }
        case kCCBPositionTypeRelativeBottomRight: {
            x = containerSize.width - x;
            break;
        }
        case kCCBPositionTypePercent: {
            x = (int)(containerSize.width * x / 100.0f);
            y = (int)(containerSize.height * y / 100.0f);
            break;
        }
    }

    return CCPoint(x, y);
}

CCPoint CCNodeLoader::parsePropTypePoint(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
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

    CCSize containerSize = pCCBReader->getContainerSize(pParent);

    switch (type) {
        case kCCBSizeTypeAbsolute: {
            /* Nothing. */
            break;
        }
        case kCCBSizeTypeRelativeContainer: {
            width = containerSize.width - width;
            height = containerSize.height - height;
            break;
        }
        case kCCBSizeTypePercent: {
            width = (int)(containerSize.width * width / 100.0f);
            height = (int)(containerSize.height * height / 100.0f);
            break;
        }
        case kCCBSizeTypeHorizontalPercent: {
            width = (int)(containerSize.width * width / 100.0f);
            break;
        }
        case kCCBSzieTypeVerticalPercent: {
            height = (int)(containerSize.height * height / 100.0f);
            break;
        }
        default:
            break;
    }
    
    return CCSize(width, height);
}

float * CCNodeLoader::parsePropTypeScaleLock(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    float x = pCCBReader->readFloat();
    float y = pCCBReader->readFloat();
    
    int type = pCCBReader->readInt(false);
    
    if(type == kCCBScaleTypeMultiplyResolution) {
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

float CCNodeLoader::parsePropTypeDegrees(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    return pCCBReader->readFloat();
}

float CCNodeLoader::parsePropTypeFloatScale(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    float f = pCCBReader->readFloat();

    int type = pCCBReader->readInt(false);
    
    if(type == kCCBScaleTypeMultiplyResolution) {
        f *= pCCBReader->getResolutionScale();
    }

    return f;
}

int CCNodeLoader::parsePropTypeInteger(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    return pCCBReader->readInt(true);
}

int CCNodeLoader::parsePropTypeIntegerLabeled(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    return pCCBReader->readInt(true);
}

float * CCNodeLoader::parsePropTypeFloatVar(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    float f = pCCBReader->readFloat();
    float fVar = pCCBReader->readFloat();
    
    float * arr = new float[2];
    arr[0] = f;
    arr[1] = fVar;
    
    return arr;
}

bool CCNodeLoader::parsePropTypeCheck(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    return pCCBReader->readBool();
}


CCSpriteFrame * CCNodeLoader::parsePropTypeSpriteFrame(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    const char * spriteSheet = pCCBReader->readCachedString();
    const char * spriteFile = pCCBReader->readCachedString();
    
    CCSpriteFrame * spriteFrame;
    if(strcmp(spriteSheet, "") == 0) {
        if(strcmp(spriteFile, "") == 0) {
            return NULL;
        }
        CCTexture2D * texture = CCTextureCache::sharedTextureCache()->addImage(spriteFile);
        CCRect bounds = CCRect::CCRect(0, 0, texture->getContentSize().width, texture->getContentSize().height);
        spriteFrame = CCSpriteFrame::frameWithTexture(texture, bounds);
    } else {
        CCSpriteFrameCache * frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
        
        /* Load the sprite sheet only if it is not loaded. */
        if(!pCCBReader->isSpriteSheetLoaded(spriteSheet)) {
            frameCache->addSpriteFramesWithFile(spriteSheet);
            pCCBReader->addLoadedSpriteSheet(spriteSheet);
        }
        
        spriteFrame = frameCache->spriteFrameByName(spriteFile);
    }
    return spriteFrame;
}

CCAnimation * CCNodeLoader::parsePropTypeAnimation(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    const char * animationFile = pCCBReader->readCachedString();
    const char * animation = pCCBReader->readCachedString();
    
    CCAnimation * ccAnimation = NULL;
    
    // Support for stripping relative file paths, since ios doesn't currently
    // know what to do with them, since its pulling from bundle.
    // Eventually this should be handled by a client side asset manager
    // interface which figured out what resources to load.
    // TODO Does this problem exist in C++?
    animation = pCCBReader->lastPathComponent(animation);
    animationFile = pCCBReader->lastPathComponent(animationFile);
    
    if(strcmp(animation, "") != 0) {
        CCAnimationCache * animationCache = CCAnimationCache::sharedAnimationCache();
        animationCache->addAnimationsWithFile(animationFile);
        
        ccAnimation = animationCache->animationByName(animation);
    }
    return ccAnimation;
}

CCTexture2D * CCNodeLoader::parsePropTypeTexture(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    const char * spriteFile = pCCBReader->readCachedString();

    return CCTextureCache::sharedTextureCache()->addImage(spriteFile);
}

unsigned char CCNodeLoader::parsePropTypeByte(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    return pCCBReader->readByte();
}

ccColor3B CCNodeLoader::parsePropTypeColor3(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    unsigned char red = pCCBReader->readByte();
    unsigned char green = pCCBReader->readByte();
    unsigned char blue = pCCBReader->readByte();
    
    ccColor3B color = { red, green, blue };
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

ccBlendFunc CCNodeLoader::parsePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    int source = pCCBReader->readInt(false);
    int destination = pCCBReader->readInt(false);
    
    ccBlendFunc blendFunc;
    blendFunc.src = source;
    blendFunc.dst = destination;
    
    return blendFunc;
}

const char * CCNodeLoader::parsePropTypeFntFile(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    return pCCBReader->readCachedString();
}

const char * CCNodeLoader::parsePropTypeString(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    return pCCBReader->readCachedString();
}

const char * CCNodeLoader::parsePropTypeText(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    return pCCBReader->readCachedString();
}

const char * CCNodeLoader::parsePropTypeFontTTF(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    const char * fnt = pCCBReader->readCachedString();
    
    const char * ttfEnding("ttf");

    if(pCCBReader->endsWith(pCCBReader->toLowerCase(fnt), ttfEnding)){
        fnt = pCCBReader->deletePathExtension(pCCBReader->lastPathComponent(fnt));
    }

    return fnt;
}

BlockData * CCNodeLoader::parsePropTypeBlock(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader) {
    const char * selectorName = pCCBReader->readCachedString();
    int selectorTarget = pCCBReader->readInt(false);

    if(selectorTarget != kCCBTargetTypeNone) {
        CCObject * target = NULL;
        if(selectorTarget == kCCBTargetTypeDocumentRoot) {
            target = pCCBReader->getRootNode();
        } else if(selectorTarget == kCCBTargetTypeOwner) {
            target = pCCBReader->getOwner();
        }

        if(target != NULL) {
            if(strlen(selectorName) > 0) {
                CCBSelectorResolver * ccbSelectorResolver = pCCBReader->getCCBSelectorResolver();
                if(ccbSelectorResolver != NULL) {
                    BlockData * blockData = new BlockData();
                    blockData->mSELMenuHandler = ccbSelectorResolver->onResolveCCBCCMenuSelector(target, selectorName);

                    blockData->mTarget = target;

                    return blockData;
                } else {
                    CCLOG("Skipping selector '%s' since no CCBSelectorResolver is present.", selectorName);
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
    const char * selectorName = pCCBReader->readCachedString();
    int selectorTarget = pCCBReader->readInt(false);
    int controlEvents = pCCBReader->readInt(false);

    if(selectorTarget != kCCBTargetTypeNone) {
        CCObject * target = NULL;
        if(selectorTarget == kCCBTargetTypeDocumentRoot) {
            target = pCCBReader->getRootNode();
        } else if(selectorTarget == kCCBTargetTypeOwner) {
            target = pCCBReader->getOwner();
        }

        if(target != NULL) {
            if(strlen(selectorName) > 0) {
                CCBSelectorResolver * ccbSelectorResolver = pCCBReader->getCCBSelectorResolver();
                if(ccbSelectorResolver != NULL) {
                    BlockCCControlData * blockCCControlData = new BlockCCControlData();
                    blockCCControlData->mSELCCControlHandler = ccbSelectorResolver->onResolveCCBCCControlSelector(target, selectorName);

                    blockCCControlData->mTarget = target;
                    blockCCControlData->mControlEvents = controlEvents;

                    return blockCCControlData;
                } else {
                    CCLOG("Skipping selector '%s' since no CCBSelectorResolver is present.", selectorName);
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
    const char * ccbFileName = pCCBReader->readCachedString();

    /* Change path extension to .ccbi. */
    const char * ccbFileWithoutPathExtension = pCCBReader->deletePathExtension(ccbFileName);
    int ccbiFileNameLenght = strlen(ccbFileWithoutPathExtension) + strlen(".ccbi");
    char ccbiFileName[ccbiFileNameLenght + 1];
    strcpy(ccbiFileName, ccbFileWithoutPathExtension);
    strcat(ccbiFileName, ".ccbi");
    ccbiFileName[ccbiFileNameLenght] = '\0';

    CCBReader * ccbReader = new CCBReader(pCCBReader);
    ccbReader->autorelease();

    CCNode * ccbFileNode = ccbReader->readNodeGraphFromFile(ccbiFileName, pCCBReader->getOwner(), pParent->getContentSize());

    return ccbFileNode;
}



void CCNodeLoader::onHandlePropTypePosition(CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCPoint pPosition, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_POSITION) == 0) {
        pNode->setPosition(pPosition);
    } else {
        ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    }
}

void CCNodeLoader::onHandlePropTypePoint(CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCPoint pPoint, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_ANCHORPOINT) == 0) {
        pNode->setAnchorPoint(pPoint);
    } else {
        ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    }
}

void CCNodeLoader::onHandlePropTypePointLock(CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCPoint pPointLock, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeSize(CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSize pSize, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_CONTENTSIZE) == 0) {
        pNode->setContentSize(pSize);
    } else {
        ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    }
}

void CCNodeLoader::onHandlePropTypeScaleLock(CCNode * pNode, CCNode * pParent, const char * pPropertyName, float * pScaleLock, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_SCALE) == 0) {
        pNode->setScaleX(pScaleLock[0]);
        pNode->setScaleY(pScaleLock[1]);
    } else {
        ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    }
}

void CCNodeLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char * pPropertyName, float pFloat, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeDegrees(CCNode * pNode, CCNode * pParent, const char * pPropertyName, float pDegrees, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_ROTATION) == 0) {
        pNode->setRotation(pDegrees);
    } else {
        ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    }
}

void CCNodeLoader::onHandlePropTypeFloatScale(CCNode * pNode, CCNode * pParent, const char * pPropertyName, float pFloatScale, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeInteger(CCNode * pNode, CCNode * pParent, const char * pPropertyName, int pInteger, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_TAG) == 0) {
        pNode->setTag(pInteger);
    } else {
        ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    }
}

void CCNodeLoader::onHandlePropTypeIntegerLabeled(CCNode * pNode, CCNode * pParent, const char * pPropertyName, int pIntegerLabeled, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeFloatVar(CCNode * pNode, CCNode * pParent, const char * pPropertyName, float * pFloatVar, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char * pPropertyName, bool pCheck, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_VISIBLE) == 0) {
        pNode->setIsVisible(pCheck);
    } else if(strcmp(pPropertyName, PROPERTY_IGNOREANCHORPOINTFORPOSITION) == 0) {
        pNode->setIgnoreAnchorPointForPosition(pCheck);
    } else {
        ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    }
}

void CCNodeLoader::onHandlePropTypeSpriteFrame(CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSpriteFrame * pCCSpriteFrame, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeAnimation(CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCAnimation * pCCAnimation, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeTexture(CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCTexture2D * pCCTexture2D, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeByte(CCNode * pNode, CCNode * pParent, const char * pPropertyName, unsigned char pByte, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B pCCColor3B, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeColor4FVar(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor4F * pCCColor4FVar, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeFlip(CCNode * pNode, CCNode * pParent, const char * pPropertyName, bool * pFlip, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccBlendFunc pCCBlendFunc, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeFntFile(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pFntFile, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeString(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pString, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeText(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pText, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeFontTTF(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pFontTTF, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeBlock(CCNode * pNode, CCNode * pParent, const char * pPropertyName, BlockData * pBlockData, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeBlockCCControl(CCNode * pNode, CCNode * pParent, const char * pPropertyName, BlockCCControlData * pBlockCCControlData, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void CCNodeLoader::onHandlePropTypeCCBFile(CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCNode * pCCBFileNode, CCBReader * pCCBReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}