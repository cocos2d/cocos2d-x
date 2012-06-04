#include "CCBReader.h"

#include "CCNodeLoader.h"
#include "CCLayerLoader.h"
#include "CCLayerColorLoader.h"
#include "CCLayerGradientLoader.h"
#include "CCLabelBMFontLoader.h"
#include "CCLabelTTFLoader.h"
#include "CCSpriteLoader.h"
#include "CCScale9SpriteLoader.h"
#include "CCBFileLoader.h"
#include "CCMenuLoader.h"
#include "CCMenuItemLoader.h"
#include "CCMenuItemImageLoader.h"
#include "CCControlButtonLoader.h"
#include "CCParticleSystemQuadLoader.h"

#ifdef __CC_PLATFORM_IOS
#import <UIKit/UIDevice.h>
#endif

using namespace cocos2d;
using namespace cocos2d::extension;

CCBReader::CCBReader(CCBMemberVariableAssigner * pCCBMemberVariableAssigner, CCBSelectorResolver * pCCBSelectorResolver) {
    this->mCCBMemberVariableAssigner = pCCBMemberVariableAssigner;
    this->mCCBSelectorResolver = pCCBSelectorResolver;

    this->mResolutionScale = 1;
    
#ifdef __CC_PLATFORM_IOS
    /* iPad */
    if(UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
        this->mResolutionScale = 2;
    }
#endif

    this->registerCCNodeLoader("CCNode", new CCNodeLoader());
    this->registerCCNodeLoader("CCLayer", new CCLayerLoader());
    this->registerCCNodeLoader("CCLayerColor", new CCLayerColorLoader());
    this->registerCCNodeLoader("CCLayerGradient", new CCLayerGradientLoader());
    this->registerCCNodeLoader("CCSprite", new CCSpriteLoader());
    this->registerCCNodeLoader("CCLabelBMFont", new CCLabelBMFontLoader());
    this->registerCCNodeLoader("CCLabelTTF", new CCLabelTTFLoader());
    this->registerCCNodeLoader("CCScale9Sprite", new CCScale9SpriteLoader());
    this->registerCCNodeLoader("CCBFile", new CCBFileLoader());
    this->registerCCNodeLoader("CCMenu", new CCMenuLoader());
    this->registerCCNodeLoader("CCMenuItemImage", new CCMenuItemImageLoader());
    this->registerCCNodeLoader("CCControlButton", new CCControlButtonLoader());
    this->registerCCNodeLoader("CCParticleSystemQuad", new CCParticleSystemQuadLoader());
}

CCBReader::~CCBReader() {
    if(this->mBytes) {
        delete this->mBytes;
        this->mBytes = NULL;
    }

    // TODO Also delete mCCNodeLoaders, mLoadedSpritesheets, etc... ? (Keep in mind they might be copied/inherited from another CCBReader through the copy constructor!)
}

CCBReader::CCBReader(CCBReader * pCCBReader) {
    /* Borrow data from the 'parent' CCBLoader. */
    this->mResolutionScale = pCCBReader->mResolutionScale;
    this->mLoadedSpriteSheets = pCCBReader->mLoadedSpriteSheets;
    this->mCCNodeLoaders = pCCBReader->mCCNodeLoaders;
    this->mCCBMemberVariableAssigner = pCCBReader->mCCBMemberVariableAssigner;
    this->mCCBSelectorResolver = pCCBReader->mCCBSelectorResolver;
}

void CCBReader::registerCCNodeLoader(std::string pClassName, CCNodeLoader * pCCNodeLoader) {
    this->mCCNodeLoaders.insert(std::pair<std::string, CCNodeLoader *>(pClassName, pCCNodeLoader));
}

CCBMemberVariableAssigner * CCBReader::getCCBMemberVariableAssigner() {
    return this->mCCBMemberVariableAssigner;
}

CCBSelectorResolver * CCBReader::getCCBSelectorResolver() {
    return this->mCCBSelectorResolver;
}

float CCBReader::getResolutionScale() {
    return this->mResolutionScale;
}

CCNodeLoader * CCBReader::getCCNodeLoader(std::string pClassName) {
    std::map<std::string, CCNodeLoader *>::iterator ccNodeLoadersIterator = this->mCCNodeLoaders.find(pClassName);
    assert(ccNodeLoadersIterator != this->mCCNodeLoaders.end());
    return ccNodeLoadersIterator->second;
}

CCNode * CCBReader::readNodeGraphFromFile(const char * pCCBFileName, CCObject * pOwner) {
    return this->readNodeGraphFromFile(pCCBFileName, pOwner, CCDirector::sharedDirector()->getWinSize());
}

CCNode * CCBReader::readNodeGraphFromFile(const char * pCCBFileName, CCObject * pOwner, CCSize pRootContainerSize) {
    const char * path = CCFileUtils::fullPathFromRelativePath(pCCBFileName);
    
    unsigned long size = 0;
    this->mBytes = CCFileUtils::getFileData(path, "r", &size);

    this->mCurrentByte = 0;
    this->mCurrentBit = 0;
    this->mOwner = pOwner;
    this->mRootContainerSize = pRootContainerSize;
    
    if(!this->readHeader()) {
        return NULL;
    }
    
    if(!this->readStringCache()) {
        return NULL;
    }
    
    return this->readNodeGraph();
}

bool CCBReader::readHeader() {
	/* If no bytes loaded, don't crash about it. */
	if(this->mBytes == NULL) {
        return false;
    }

    /* Read magic bytes */
    int magicBytes = *((int*)(this->mBytes + this->mCurrentByte));
    this->mCurrentByte += 4;

    if(magicBytes != 'ccbi') {
        return false; 
    }

    /* Read version. */
    int version = this->readInt(false);
    if(version != kCCBVersion) {
        CCLog("WARNING! Incompatible ccbi file version (file: %d reader: %d)", version, kCCBVersion);
        return false;
    }

    return true;
}

bool CCBReader::readStringCache() {
    int numStrings = this->readInt(false);

    for(int i = 0; i < numStrings; i++) {
        std::string string = this->readUTF8();
        this->mStringCache.push_back(string);
    }

    return true;
}

std::string CCBReader::readUTF8() {
    int b0 = this->readByte();
    int b1 = this->readByte();

    int numBytes = b0 << 8 | b1;

    const char * ptr = (const char*) (this->mBytes + this->mCurrentByte);
    std::string str(ptr, numBytes);

    this->mCurrentByte += numBytes;

    return str;
}

unsigned char CCBReader::readByte() {
    unsigned char byte = this->mBytes[this->mCurrentByte];
    this->mCurrentByte++;
    return byte;
}

bool CCBReader::readBool() {
    return this->readByte();
}

int CCBReader::readInt(bool pSign) {
    int numBits = 0;
    while(!this->getBit()) {
        numBits++;
    }
    
    long long current = 0;
    for(int a = numBits - 1; a >= 0; a--) {
        if(this->getBit()) {
            current |= 1 << a;
        }
    }
    current |= 1 << numBits;
    
    int num;
    if(pSign) {
        int s = current % 2;
        if(s) {
            num = (int)(current / 2);
        } else {
            num = (int)(-current / 2);
        }
    } else {
        num = current - 1;
    }
    
    this->alignBits();
    
    return num;
}


float CCBReader::readFloat() {
    unsigned char type = this->readByte();
    
    switch (type) {
        case kCCBFloat0:
            return 0;    
        case kCCBFloat1:
            return 1;
        case kCCBFloatMinus1:
            return -1;
        case kCCBFloat05:
            return 0.5f;
        case kCCBFloatInteger:
            return this->readInt(true);
        default:
            /* using a memcpy since the compiler isn't
             * doing the float ptr math correctly on device.
             * TODO still applies in C++ ? */
            float * pF = (float*)(this->mBytes + this->mCurrentByte);
            float f = 0;
            memcpy(&f, pF, sizeof(float));
            this->mCurrentByte += 4;
            return f;
    }
}


bool CCBReader::getBit() {
    bool bit;
    unsigned char byte = *(this->mBytes + this->mCurrentByte);
    if(byte & (1 << this->mCurrentBit)) {
        bit = true;
    } else {
        bit = false;
    }
            
    this->mCurrentBit++;

    if(this->mCurrentBit >= 8) {
        this->mCurrentBit = 0;
        this->mCurrentByte++;
    }
    
    return bit;
}

void CCBReader::alignBits() {
    if(this->mCurrentBit) {
        this->mCurrentBit = 0;
        this->mCurrentByte++;
    }
}

std::string CCBReader::readCachedString() {
    int i = this->readInt(false);
    return this->mStringCache[i];
}

CCNode * CCBReader::readNodeGraph(CCNode * pParent) {
    /* Read class name. */
    std::string className = this->readCachedString();

    int memberVarAssignmentType = this->readInt(false);
    std::string memberVarAssignmentName;
    if(memberVarAssignmentType != kCCBTargetTypeNone) {
        memberVarAssignmentName = this->readCachedString();
    }

    CCNodeLoader * ccNodeLoader = this->getCCNodeLoader(className);
    CCNode * node = ccNodeLoader->loadCCNode(pParent, this);

    /* Set root node, if not set yet. */
    if(this->mRootNode == NULL) {
        this->mRootNode = node; // TODO retain?
    }

    if(memberVarAssignmentType != kCCBTargetTypeNone) {
        CCObject * target = NULL;
        if(memberVarAssignmentType == kCCBTargetTypeDocumentRoot) {
            target = this->getRootNode();
        } else if (memberVarAssignmentType == kCCBTargetTypeOwner) {
            target = this->getOwner();
        }

        if (target != NULL) {
            if(this->mCCBMemberVariableAssigner != NULL) {
                this->mCCBMemberVariableAssigner->onAssignCCBMemberVariable(target, memberVarAssignmentName, node);
            }
        }
    }

    /* Read and add children. */
    int numChildren = this->readInt(false);
    for(int i = 0; i < numChildren; i++) {
        CCNode * child = this->readNodeGraph(node);
        node->addChild(child);
    }
    
    // TODO
    /*
    if([node respondsToSelector:@selector(didLoadFromCCB)]) {
        [node performSelector:@selector(didLoadFromCCB)];
    }
    */

    return node;
}

CCNode * CCBReader::readNodeGraph() {
    return this->readNodeGraph(NULL);
}

CCObject * CCBReader::getOwner() {
    return this->mOwner;
}

CCNode * CCBReader::getRootNode() {
    return this->mRootNode;
}

CCSize CCBReader::getContainerSize(CCNode * pNode) {
    if(pNode) {
        return pNode->getContentSize();
    } else {
        return this->mRootContainerSize;
    }
}

std::string CCBReader::lastPathComponent(std::string pPath) {
    int slashPos = pPath.find_last_of("/");
    if (slashPos != std::string::npos) {
        return pPath.substr(slashPos + 1, pPath.length() - slashPos);
    }
    return pPath;
}

std::string CCBReader::deletePathExtension(std::string pPath) {
    int dotPos = pPath.find_last_of(".");
    if (dotPos != std::string::npos) {
        return pPath.substr(0, dotPos);
    }
    return pPath;
}

bool CCBReader::isSpriteSheetLoaded(std::string pSpriteSheet) {
    return this->mLoadedSpriteSheets.find(pSpriteSheet) != this->mLoadedSpriteSheets.end();
}

void CCBReader::addLoadedSpriteSheet(std::string pSpriteSheet) {
    this->mLoadedSpriteSheets.insert(pSpriteSheet);
}

std::string CCBReader::toLowerCase(std::string pString) {
    std::string copy(pString);
    std::transform(copy.begin(), copy.end(), copy.begin(), ::tolower);
    return copy;
}

bool CCBReader::endsWith(std::string pString, std::string pEnding) {
    if (pString.length() >= pEnding.length()) {
        return (pString.compare(pString.length() - pEnding.length(), pEnding.length(), pEnding) == 0);
    } else {
        return false;
    }
}
