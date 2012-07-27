#include "CCBReader.h"

#include <algorithm>

#include "CCNodeLoader.h"
#include "CCNodeLoaderLibrary.h"
#include "CCNodeLoaderListener.h"
#include "CCBMemberVariableAssigner.h"
#include "CCBSelectorResolver.h"

#ifdef __CC_PLATFORM_IOS
#include <UIKit/UIDevice.h>
#endif

USING_NS_CC;
NS_CC_EXT_BEGIN;

CCBReader::CCBReader(CCNodeLoaderLibrary * pCCNodeLoaderLibrary, CCBMemberVariableAssigner * pCCBMemberVariableAssigner, CCBSelectorResolver * pCCBSelectorResolver, CCNodeLoaderListener * pCCNodeLoaderListener) {
    this->mRootNode = NULL;
    this->mRootCCBReader = true;

    this->mCCNodeLoaderLibrary = pCCNodeLoaderLibrary;
    this->mCCNodeLoaderLibrary->retain();
    this->mCCBMemberVariableAssigner = pCCBMemberVariableAssigner;
    this->mCCBSelectorResolver = pCCBSelectorResolver;
    this->mCCNodeLoaderListener = pCCNodeLoaderListener;

    this->mResolutionScale = 1;

#ifdef __CC_PLATFORM_IOS
    /* iPad */
    if(UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
        this->mResolutionScale = 2;
    }
#endif
}

CCBReader::CCBReader(CCBReader * pCCBReader) {
    this->mRootNode = NULL;
    this->mRootCCBReader = false;

    /* Borrow data from the 'parent' CCBReader. */
    this->mResolutionScale = pCCBReader->mResolutionScale;
    this->mLoadedSpriteSheets = pCCBReader->mLoadedSpriteSheets;
    this->mCCNodeLoaderLibrary = pCCBReader->mCCNodeLoaderLibrary;
    this->mCCNodeLoaderLibrary->retain();

    this->mCCBMemberVariableAssigner = pCCBReader->mCCBMemberVariableAssigner;
    this->mCCBSelectorResolver = pCCBReader->mCCBSelectorResolver;
    this->mCCNodeLoaderListener = pCCBReader->mCCNodeLoaderListener;
}

CCBReader::~CCBReader() {
    CC_SAFE_DELETE_ARRAY(this->mBytes);

    this->mCCNodeLoaderLibrary->release();

    /* Clear string cache. */
    std::vector<CCString *>::iterator stringCacheIterator;
    for (stringCacheIterator = this->mStringCache.begin(); stringCacheIterator != this->mStringCache.end(); stringCacheIterator++) {
        (*stringCacheIterator)->release();
    }
    this->mStringCache.clear();
    
    if(this->mRootCCBReader) {
        /* Clear loaded spritesheets. */
        this->mLoadedSpriteSheets.clear();
    }
}

CCString * CCBReader::getCCBRootPath() {
    return this->mCCBRootPath;
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

CCNode * CCBReader::readNodeGraphFromFile(const char * pCCBRootPath, const char * pCCBFileName, CCObject * pOwner) {
    return this->readNodeGraphFromFile(pCCBRootPath, pCCBFileName, pOwner, CCDirector::sharedDirector()->getWinSize());
}

CCNode * CCBReader::readNodeGraphFromFile(CCString * pCCBRootPath, CCString * pCCBFileName, CCObject * pOwner) {
    return this->readNodeGraphFromFile(pCCBRootPath, pCCBFileName, pOwner, CCDirector::sharedDirector()->getWinSize());
}

CCNode * CCBReader::readNodeGraphFromFile(const char * pCCBRootPath, const char * pCCBFileName, CCObject * pOwner, CCSize pRootContainerSize) {
    return this->readNodeGraphFromFile(CCString::create(pCCBRootPath), CCString::create(pCCBFileName), pOwner, pRootContainerSize);
}

CCNode * CCBReader::readNodeGraphFromFile(CCString * pCCBRootPath, CCString * pCCBFileName, CCObject * pOwner, CCSize pRootContainerSize) {
    this->mCCBRootPath = pCCBRootPath;
    this->mCCBRootPath->retain();

    CCString * ccbFullFilePath = CCBReader::concat(pCCBRootPath, pCCBFileName);

    const char * path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(ccbFullFilePath->getCString());

    unsigned long size = 0;
    this->mBytes = CCFileUtils::sharedFileUtils()->getFileData(path, "rb", &size);

    this->mCurrentByte = 0;
    this->mCurrentBit = 0;

    this->mOwner = pOwner;
    this->mOwner->retain();
    this->mRootContainerSize = pRootContainerSize;

    CCNode * node = NULL;
    if(this->readHeader() && this->readStringCache()) {
        node = this->readNodeGraph();
    }

    CC_SAFE_RELEASE(this->mOwner);
    CC_SAFE_RELEASE(this->mCCBRootPath);
    CC_SAFE_RELEASE(this->mRootNode);

    return node;
}

bool CCBReader::readHeader() {
	/* If no bytes loaded, don't crash about it. */
	if(this->mBytes == NULL) {
        return false;
    }

    /* Read magic bytes */
    int magicBytes = *((int*)(this->mBytes + this->mCurrentByte));
    this->mCurrentByte += 4;

    if(CC_SWAP_INT32_LITTLE_TO_HOST(magicBytes) != 'ccbi') {
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
        this->readStringCacheEntry();
    }

    return true;
}

void CCBReader::readStringCacheEntry() {
    int b0 = this->readByte();
    int b1 = this->readByte();

    int numBytes = b0 << 8 | b1;

    const unsigned char * src = (const unsigned char *) (this->mBytes + this->mCurrentByte);
    CCString * string = CCString::createWithData(src, (unsigned long)numBytes);
    string->retain();

    this->mCurrentByte += numBytes;

    this->mStringCache.push_back(string);
}

unsigned char CCBReader::readByte() {
    unsigned char byte = this->mBytes[this->mCurrentByte];
    this->mCurrentByte++;
    return byte;
}

bool CCBReader::readBool() {
    return 0 == this->readByte() ? false : true;
}

int CCBReader::readInt(bool pSigned) {
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
    if(pSigned) {
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
            return (float)this->readInt(true);
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

CCString * CCBReader::readCachedString() {
    int i = this->readInt(false);
    return this->mStringCache[i];
}

CCNode * CCBReader::readNodeGraph(CCNode * pParent) {
    /* Read class name. */
    CCString * className = this->readCachedString();

    int memberVarAssignmentType = this->readInt(false);
    CCString * memberVarAssignmentName;
    if(memberVarAssignmentType != kCCBTargetTypeNone) {
        memberVarAssignmentName = this->readCachedString();
    }

    CCNodeLoader * ccNodeLoader = this->mCCNodeLoaderLibrary->getCCNodeLoader(className);
    CCNode * node = ccNodeLoader->loadCCNode(pParent, this);

    /* Set root node, if not set yet. */
    if(this->mRootNode == NULL) {
        this->mRootNode = node;
        this->mRootNode->retain();
    }

    if(memberVarAssignmentType != kCCBTargetTypeNone) {
        CCObject * target = NULL;
        if(memberVarAssignmentType == kCCBTargetTypeDocumentRoot) {
            target = this->mRootNode;
        } else if(memberVarAssignmentType == kCCBTargetTypeOwner) {
            target = this->mOwner;
        }

        if(target != NULL) {
            bool assigned = false;

            CCBMemberVariableAssigner * targetAsCCBMemberVariableAssigner = dynamic_cast<CCBMemberVariableAssigner *>(target);

            if(targetAsCCBMemberVariableAssigner != NULL) {
                assigned = targetAsCCBMemberVariableAssigner->onAssignCCBMemberVariable(target, memberVarAssignmentName, node);
            }

            if(!assigned && this->mCCBMemberVariableAssigner != NULL) {
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

    CCNodeLoaderListener * nodeAsCCNodeLoaderListener = dynamic_cast<CCNodeLoaderListener *>(node);
    if(nodeAsCCNodeLoaderListener != NULL) {
        nodeAsCCNodeLoaderListener->onNodeLoaded(node, ccNodeLoader);
    } else if(this->mCCNodeLoaderListener != NULL) {
        this->mCCNodeLoaderListener->onNodeLoaded(node, ccNodeLoader);
    }

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

bool CCBReader::isSpriteSheetLoaded(CCString * pSpriteSheet) {
    return this->mLoadedSpriteSheets.find(pSpriteSheet->m_sString) != this->mLoadedSpriteSheets.end();
}

void CCBReader::addLoadedSpriteSheet(CCString * pSpriteSheet) {
    // Since std::set<string> will copy the string from pSpriteSheet, we needn't to retain 'pSpriteSheet'.
    //    pSpriteSheet->retain();
    this->mLoadedSpriteSheets.insert(pSpriteSheet->m_sString);
}

CCString * CCBReader::lastPathComponent(CCString * pPath) {
    std::string path(pPath->getCString());
    int slashPos = path.find_last_of("/");
    if(slashPos != std::string::npos) {
        return CCString::create(path.substr(slashPos + 1, path.length() - slashPos).c_str());
    }
    return CCString::create(path.c_str());
}

CCString * CCBReader::deletePathExtension(CCString * pPath) {
    std::string path(pPath->getCString());
    int dotPos = path.find_last_of(".");
    if(dotPos != std::string::npos) {
        return CCString::create(path.substr(0, dotPos).c_str());
    }
    return CCString::create(path.c_str());
}

CCString * CCBReader::toLowerCase(CCString * pString) {
    std::string copy(pString->getCString());
    std::transform(copy.begin(), copy.end(), copy.begin(), ::tolower);
    return CCString::create(copy.c_str());
}

CCString * CCBReader::concat(CCString * pStringA, CCString * pStringB) {
    int concatenatedLength = pStringA->length() + pStringB->length();
    char* concatenated = (char*) malloc(concatenatedLength+1);
    CCString* pRet = NULL;
    strcpy(concatenated, pStringA->getCString());
    strcat(concatenated, pStringB->getCString());

    concatenated[concatenatedLength] = '\0';
    pRet = CCString::create(concatenated);
    CC_SAFE_FREE(concatenated);
    return pRet;
}

bool CCBReader::endsWith(CCString * pString, CCString * pEnding) {
    std::string string(pString->getCString());
    std::string ending(pEnding->getCString());
    if(string.length() >= ending.length()) {
        return (string.compare(string.length() - ending.length(), ending.length(), ending) == 0);
    } else {
        return false;
    }
}

NS_CC_EXT_END;
