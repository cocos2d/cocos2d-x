#include "CCBReader.h"

#include <algorithm>

#include "CCNodeLoader.h"
#include "CCNodeLoaderLibrary.h"
#include "CCNodeLoaderListener.h"
#include "CCBMemberVariableAssigner.h"
#include "CCBSelectorResolver.h"
#include "CCData.h"
#include "CCBAnimationManager.h"
#include "CCBSequenceProperty.h"
#include "CCBKeyframe.h"
#include "CCBValue.h"

#include <ctype.h>

#ifdef __CC_PLATFORM_IOS
#include <UIKit/UIDevice.h>
#endif

using namespace std;

NS_CC_EXT_BEGIN;

/*************************************************************************
 Implementation of CCBFile
 *************************************************************************/

CCBFile::CCBFile():mCCBFileNode(NULL) {}

CCBFile* CCBFile::create()
{
    CCBFile *ret = new CCBFile();
    
    if (ret)
    {
        ret->autorelease();
    }
    
    return ret;
}

CCNode* CCBFile::getCCBFileNode()
{
    return mCCBFileNode;
}

void CCBFile::setCCBFileNode(CCNode *pNode)
{
    CC_SAFE_RELEASE(mCCBFileNode);
    mCCBFileNode = pNode;
    CC_SAFE_RETAIN(mCCBFileNode);
}

/*************************************************************************
 Implementation of CCBReader
 *************************************************************************/

CCBReader::CCBReader(CCNodeLoaderLibrary * pCCNodeLoaderLibrary, CCBMemberVariableAssigner * pCCBMemberVariableAssigner, CCBSelectorResolver * pCCBSelectorResolver, CCNodeLoaderListener * pCCNodeLoaderListener) 
: mData(NULL)
, mBytes(NULL)
, mCurrentByte(-1)
, mCurrentBit(-1)
, mOwner(NULL)
, mActionManager(NULL)
, mAnimatedProps(NULL)
, hasScriptingOwner(false)
{
    this->mCCNodeLoaderLibrary = pCCNodeLoaderLibrary;
    this->mCCNodeLoaderLibrary->retain();
    this->mCCBMemberVariableAssigner = pCCBMemberVariableAssigner;
    this->mCCBSelectorResolver = pCCBSelectorResolver;
    this->mCCNodeLoaderListener = pCCNodeLoaderListener;
}

CCBReader::CCBReader(CCBReader * pCCBReader) 
: mData(NULL)
, mBytes(NULL)
, mCurrentByte(-1)
, mCurrentBit(-1)
, mOwner(NULL)
, mActionManager(NULL)
, mAnimatedProps(NULL)
, hasScriptingOwner(false)
{
    this->mLoadedSpriteSheets = pCCBReader->mLoadedSpriteSheets;
    this->mCCNodeLoaderLibrary = pCCBReader->mCCNodeLoaderLibrary;
    this->mCCNodeLoaderLibrary->retain();

    this->mCCBMemberVariableAssigner = pCCBReader->mCCBMemberVariableAssigner;
    this->mCCBSelectorResolver = pCCBReader->mCCBSelectorResolver;
    this->mCCNodeLoaderListener = pCCBReader->mCCNodeLoaderListener;
}

CCBReader::CCBReader()
: mData(NULL)
, mBytes(NULL)
, mCurrentByte(-1)
, mCurrentBit(-1)
, mOwner(NULL)
, mActionManager(NULL)
, mCCNodeLoaderLibrary(NULL)
, mCCNodeLoaderListener(NULL)
, mCCBMemberVariableAssigner(NULL)
, mCCBSelectorResolver(NULL)
, mAnimatedProps(NULL)
, hasScriptingOwner(false)
{}

CCBReader::~CCBReader() {
    CC_SAFE_RELEASE_NULL(mOwner);
    CC_SAFE_RELEASE_NULL(mData);

    this->mCCNodeLoaderLibrary->release();

    // Clear string cache.
    std::vector<CCString *>::iterator stringCacheIterator;
    for (stringCacheIterator = this->mStringCache.begin(); stringCacheIterator != this->mStringCache.end(); stringCacheIterator++) {
        (*stringCacheIterator)->release();
    }
    this->mStringCache.clear();
    
    setAnimationManager(NULL);
}

bool CCBReader::initWithData(CCData *pData, CCObject *pOwner)
{
    // Setup action manager
    CCBAnimationManager *pActionManager = new CCBAnimationManager();
    setAnimationManager(pActionManager);
    pActionManager->release();
    
    // Setup byte array
    mData = pData;
    CC_SAFE_RETAIN(mData);
    mBytes = mData->getBytes();
    mCurrentByte = 0;
    mCurrentBit = 0;
    
    mOwner = pOwner;
    CC_SAFE_RETAIN(mOwner);
    
    // Setup resolution scale and container size
    mActionManager->setRootContainerSize(CCDirector::sharedDirector()->getWinSize());
    
    return true;
}

CCBAnimationManager* CCBReader::getAnimationManager()
{
    return mActionManager;
}

void CCBReader::setAnimationManager(CCBAnimationManager *pAnimationManager)
{
    CC_SAFE_RELEASE(mActionManager);
    mActionManager = pAnimationManager;
    CC_SAFE_RETAIN(mActionManager);
}

CCBMemberVariableAssigner * CCBReader::getCCBMemberVariableAssigner() {
    return this->mCCBMemberVariableAssigner;
}

CCBSelectorResolver * CCBReader::getCCBSelectorResolver() {
    return this->mCCBSelectorResolver;
}

set<string>* CCBReader::getAnimatedProperties()
{
    return mAnimatedProps;
}

set<string>& CCBReader::getLoadedSpriteSheet()
{
    return mLoadedSpriteSheets;
}

CCObject* CCBReader::getOwner()
{
    return mOwner;
}

CCNode* CCBReader::readNodeGraphFromFile(const char *pCCBFileName)
{
    return this->readNodeGraphFromFile(pCCBFileName, NULL);
}

CCNode* CCBReader::readNodeGraphFromFile(const char* pCCBFileName, CCObject* pOwner) 
{
    return this->readNodeGraphFromFile(pCCBFileName, pOwner, CCDirector::sharedDirector()->getWinSize());
}

CCNode * CCBReader::readNodeGraphFromFile(const char * pCCBFileName, CCObject *pOwner, const CCSize &parentSize) 
{
    return this->readNodeGraphFromFile(pCCBFileName, pOwner, parentSize, NULL);
}

CCNode* CCBReader::readNodeGraphFromFile(const char *pCCBFileName, CCObject *pOwner, CCBAnimationManager **ppAnimationManager)
{
    return this->readNodeGraphFromFile(pCCBFileName, pOwner, CCDirector::sharedDirector()->getWinSize(), ppAnimationManager);
}

CCNode* CCBReader::readNodeGraphFromFile(const char *pCCBFileName, CCObject *pOwner, const CCSize &parentSize, CCBAnimationManager **ppAnimationManager)
{
    const char *pPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(pCCBFileName);
    unsigned long size;

    unsigned char * pBytes = CCFileUtils::sharedFileUtils()->getFileData(pPath, "rb", &size);
    CCData *data = new CCData(pBytes, size);

    CCNode *ret =  this->readNodeGraphFromData(data, pOwner, parentSize, ppAnimationManager);
    
    data->release();
    
    return ret;
}

CCNode* CCBReader::readNodeGraphFromData(CCData *pData, CCObject *pOwner, const CCSize &parentSize)
{
    return this->readNodeGraphFromData(pData, pOwner, parentSize, NULL);
}

CCNode* CCBReader::readNodeGraphFromData(CCData *pData, CCObject *pOwner, const CCSize &parentSize, CCBAnimationManager **ppAnimationManager)
{
    initWithData(pData, pOwner);
    mActionManager->setRootContainerSize(parentSize);
    
    CCNode *pNodeGraph = readFileWithCleanUp(true);
    
    if (pNodeGraph && mActionManager->getAutoPlaySequenceId() != -1)
    {
        // Auto play animations
        mActionManager->runAnimations(mActionManager->getAutoPlaySequenceId(), 0);
    }
    
    // Return action manager by reference
    if (ppAnimationManager)
    {
        *ppAnimationManager = mActionManager;
    }
    
    return pNodeGraph;
}

CCScene* CCBReader::createSceneWithNodeGraphFromFile(const char *pCCBFileName)
{
    return createSceneWithNodeGraphFromFile(pCCBFileName, NULL);
}

CCScene* CCBReader::createSceneWithNodeGraphFromFile(const char *pCCBFileName, CCObject *pOwner)
{
    return createSceneWithNodeGraphFromFile(pCCBFileName, pOwner, CCDirector::sharedDirector()->getWinSize());
}

CCScene* CCBReader::createSceneWithNodeGraphFromFile(const char *pCCBFileName, CCObject *pOwner, const CCSize &parentSize)
{
    return createSceneWithNodeGraphFromFile(pCCBFileName, pOwner, parentSize, NULL);
}

CCScene* CCBReader::createSceneWithNodeGraphFromFile(const char *pCCBFileName, CCObject *pOwner, const CCSize &parentSize, CCBAnimationManager **ppAnimationManager)
{
    CCNode *pNode = readNodeGraphFromFile(pCCBFileName, pOwner, parentSize, ppAnimationManager);
    CCScene *pScene = CCScene::create();
    pScene->addChild(pNode);
    
    return pScene;
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

void CCBReader::cleanUpNodeGraph(CCNode *pNode)
{
    pNode->setUserObject(NULL);
    
    CCObject *pChild = NULL;
    CCARRAY_FOREACH(pNode->getChildren(), pChild)
    {
        cleanUpNodeGraph((CCNode*)pChild);
    }
}

CCNode* CCBReader::readFileWithCleanUp(bool bCleanUp)
{
    if (! readHeader())
    {
        return NULL;
    }
    
    if (! readStringCache())
    {
        return NULL;
    }
    
    if (! readSequences())
    {
        return NULL;
    }
    
    CCNode *pNode = readNodeGraph();
    
    if (bCleanUp)
    {
        cleanUpNodeGraph(pNode);
    }
    
    return pNode;
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
            current |= 1LL << a;
        }
    }
    current |= 1LL << numBits;
    
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

    // Read assignment type and name
    int memberVarAssignmentType = this->readInt(false);
    CCString * memberVarAssignmentName;
    if(memberVarAssignmentType != kCCBTargetTypeNone) {
        memberVarAssignmentName = this->readCachedString();
    }

    CCNodeLoader *ccNodeLoader = this->mCCNodeLoaderLibrary->getCCNodeLoader(className);
    if (! ccNodeLoader)
    {
        CCLog("no corresponding node loader for %s", className->getCString());
        return NULL;
    }

    CCNode *node = ccNodeLoader->loadCCNode(pParent, this);

    // Set root node
    if (! mActionManager->getRootNode())
    {
        mActionManager->setRootNode(node);
    }
    
    // Read animated properties
    CCDictionary *seqs = CCDictionary::create();
    mAnimatedProps = new set<string>();
    
    int numSequence = readInt(false);
    for (int i = 0; i < numSequence; ++i)
    {
        int seqId = readInt(false);
        CCDictionary *seqNodeProps = CCDictionary::create();
        
        int numProps = readInt(false);
        
        for (int j = 0; j < numProps; ++j)
        {
            CCBSequenceProperty *seqProp = new CCBSequenceProperty();
            seqProp->autorelease();
            
            seqProp->setName(readCachedString()->getCString());
            seqProp->setType(readInt(false));
            mAnimatedProps->insert(seqProp->getName());
            
            int numKeyframes = readInt(false);
            
            for (int k = 0; k < numKeyframes; ++k)
            {
                CCBKeyframe *keyframe = readKeyframe(seqProp->getType());
                
                seqProp->getKeyframes()->addObject(keyframe);
            }
            
            seqNodeProps->setObject(seqProp, seqProp->getName());
        }
        
        seqs->setObject(seqNodeProps, seqId);
    }
    
    if (seqs->count() > 0)
    {
        mActionManager->addNode(node, seqs);
    }
    
    // Read properties
    ccNodeLoader->parseProperties(node, pParent, this);
    
    // Handle sub ccb files (remove middle node)
    if (dynamic_cast<CCBFile*>(node))
    {
        CCBFile *ccbFileNode = (CCBFile*)node;
        
        CCNode *embeddedNode = ccbFileNode->getCCBFileNode();
        embeddedNode->setPosition(ccbFileNode->getPosition());
        embeddedNode->setRotation(ccbFileNode->getRotation());
        embeddedNode->setScale(ccbFileNode->getScale());
        embeddedNode->setTag(ccbFileNode->getTag());
        embeddedNode->setVisible(true);
        embeddedNode->ignoreAnchorPointForPosition(ccbFileNode->isIgnoreAnchorPointForPosition());
        
        ccbFileNode->setCCBFileNode(NULL);
        
        node = embeddedNode;
    }

#ifdef CCB_ENABLE_JAVASCRIPT
    /*
     if (memberVarAssignmentType && memberVarAssignmentName && ![memberVarAssignmentName isEqualToString:@""])
     {
     [[JSCocoa sharedController] setObject:node withName:memberVarAssignmentName];
     }*/
#else
    if(memberVarAssignmentType != kCCBTargetTypeNone) {
        CCObject * target = NULL;
        if(memberVarAssignmentType == kCCBTargetTypeDocumentRoot) 
        {
            target = mActionManager->getRootNode();
        } 
        else if(memberVarAssignmentType == kCCBTargetTypeOwner) 
        {
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
#endif // CCB_ENABLE_JAVASCRIPT
    
    delete mAnimatedProps;
    mAnimatedProps = NULL;

    /* Read and add children. */
    int numChildren = this->readInt(false);
    for(int i = 0; i < numChildren; i++) {
        CCNode * child = this->readNodeGraph(node);
        node->addChild(child);
    }

    // Call onNodeLoaded
    CCNodeLoaderListener * nodeAsCCNodeLoaderListener = dynamic_cast<CCNodeLoaderListener *>(node);
    if(nodeAsCCNodeLoaderListener != NULL) {
        nodeAsCCNodeLoaderListener->onNodeLoaded(node, ccNodeLoader);
    } else if(this->mCCNodeLoaderListener != NULL) {
        this->mCCNodeLoaderListener->onNodeLoaded(node, ccNodeLoader);
    }

    return node;
}

CCBKeyframe* CCBReader::readKeyframe(int type)
{
    CCBKeyframe *keyframe = new CCBKeyframe();
    keyframe->autorelease();
    
    keyframe->setTime(readFloat());
    
    int easingType = readInt(false);
    float easingOpt = 0;
    CCObject *value = NULL;
    
    if (easingType == kCCBKeyframeEasingCubicIn
        || easingType == kCCBKeyframeEasingCubicOut
        || easingType == kCCBKeyframeEasingCubicInOut
        || easingType == kCCBKeyframeEasingElasticIn
        || easingType == kCCBKeyframeEasingElasticOut
        || easingType == kCCBKeyframeEasingElasticInOut)
    {
        easingOpt = readFloat();
    }
    keyframe->setEasingType(easingType);
    keyframe->setEasingOpt(easingOpt);
    
    if (type == kCCBPropTypeCheck)
    {
        value = CCBValue::create(readBool());
    }
    else if (type == kCCBPropTypeByte)
    {
        value = CCBValue::create(readByte());
    }
    else if (type == kCCBPropTypeColor3)
    {
        int r = readByte();
        int g = readByte();
        int b = readByte();
        
        ccColor3B c = ccc3(r,g,b);
        value = ccColor3BWapper::create(c);
    }
    else if (type == kCCBPropTypeDegrees)
    {
        value = CCBValue::create(readFloat());
    }
    else if (type == kCCBPropTypeScaleLock || type == kCCBPropTypePosition)
    {
        float a = readFloat();
        float b = readFloat();
        
        value = CCArray::create(CCBValue::create(a),
                                CCBValue::create(b),
                                NULL);
    }
    else if (type == kCCBPropTypeSpriteFrame)
    {
        CCString *spriteSheet = readCachedString();
        CCString *spriteFile = readCachedString();
        
        CCSpriteFrame* spriteFrame;
        CCString empty("");
        if (spriteSheet->isEqual(&empty))
        {
            CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(spriteFile->getCString());
            CCRect bounds = CCRectMake(0, 0, texture->getContentSize().width, texture->getContentSize().height);
            spriteFrame = CCSpriteFrame::createWithTexture(texture, bounds);
        }
        else
        {
            CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
            
            // Load the sprite sheet only if it is not loaded            
            if (mLoadedSpriteSheets.find(spriteSheet->getCString()) == mLoadedSpriteSheets.end())
            {
                frameCache->addSpriteFramesWithFile(spriteSheet->getCString());
                mLoadedSpriteSheets.insert(spriteSheet->getCString());
            }
            
            spriteFrame = frameCache->spriteFrameByName(spriteFile->getCString());
        }
        value = spriteFrame;
    }
    
    keyframe->setValue(value);
    
    return  keyframe;
}

CCNode * CCBReader::readNodeGraph() {
    return this->readNodeGraph(NULL);
}

bool CCBReader::readSequences()
{
    CCArray *sequences = mActionManager->getSequences();
    
    int numSeqs = readInt(false);
    
    for (int i = 0; i < numSeqs; i++)
    {
        CCBSequence *seq = new CCBSequence();
        seq->autorelease();
        
        seq->setDuration(readFloat());
        seq->setName(readCachedString()->getCString());
        seq->setSequenceId(readInt(false));
        seq->setChainedSequenceId(readInt(true));
        
        sequences->addObject(seq);
    }
    
    mActionManager->setAutoPlaySequenceId(readInt(true));
    return true;
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

/************************************************************************
 Static functions
 ************************************************************************/

float CCBReader::getResolutionScale()
{
    // Init resolution scale
    if (CCApplication::sharedApplication()->getTargetPlatform() == kTargetIpad)
    {
        return 2;
    }
    else 
    {
        return 1;
    }
}

NS_CC_EXT_END;
