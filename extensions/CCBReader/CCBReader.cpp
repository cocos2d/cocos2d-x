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
, mActionManagers(NULL)
, mAnimatedProps(NULL)
, mOwnerOutletNodes(NULL)
, mNodesWithAnimationManagers(NULL)
, mAnimationManagersForNodes(NULL)
, mOwnerCallbackNodes(NULL)
, hasScriptingOwner(false)
{
    this->mCCNodeLoaderLibrary = pCCNodeLoaderLibrary;
    this->mCCNodeLoaderLibrary->retain();
    this->mCCBMemberVariableAssigner = pCCBMemberVariableAssigner;
    this->mCCBSelectorResolver = pCCBSelectorResolver;
    this->mCCNodeLoaderListener = pCCNodeLoaderListener;
    init();
}

CCBReader::CCBReader(CCBReader * pCCBReader) 
: mData(NULL)
, mBytes(NULL)
, mCurrentByte(-1)
, mCurrentBit(-1)
, mOwner(NULL)
, mActionManager(NULL)
, mActionManagers(NULL)
, mAnimatedProps(NULL)
, mOwnerOutletNodes(NULL)
, mNodesWithAnimationManagers(NULL)
, mAnimationManagersForNodes(NULL)
, mOwnerCallbackNodes(NULL)
, hasScriptingOwner(false)
{
    this->mLoadedSpriteSheets = pCCBReader->mLoadedSpriteSheets;
    this->mCCNodeLoaderLibrary = pCCBReader->mCCNodeLoaderLibrary;
    this->mCCNodeLoaderLibrary->retain();

    this->mCCBMemberVariableAssigner = pCCBReader->mCCBMemberVariableAssigner;
    this->mCCBSelectorResolver = pCCBReader->mCCBSelectorResolver;
    this->mCCNodeLoaderListener = pCCBReader->mCCNodeLoaderListener;

    this->mOwnerCallbackNames = pCCBReader->mOwnerCallbackNames;
    this->mOwnerCallbackNodes = pCCBReader->mOwnerCallbackNodes;
    this->mOwnerCallbackNodes->retain();
    this->mOwnerOutletNames = pCCBReader->mOwnerOutletNames;
    this->mOwnerOutletNodes = pCCBReader->mOwnerOutletNodes;
    this->mOwnerOutletNodes->retain();
    init();
}

CCBReader::CCBReader()
: mData(NULL)
, mBytes(NULL)
, mCurrentByte(-1)
, mCurrentBit(-1)
, mOwner(NULL)
, mActionManager(NULL)
, mActionManagers(NULL)
, mCCNodeLoaderLibrary(NULL)
, mCCNodeLoaderListener(NULL)
, mCCBMemberVariableAssigner(NULL)
, mCCBSelectorResolver(NULL)
, mNodesWithAnimationManagers(NULL)
, mAnimationManagersForNodes(NULL)
, hasScriptingOwner(false)
{
    init();
}

CCBReader::~CCBReader() {
    CC_SAFE_RELEASE_NULL(mOwner);
    CC_SAFE_RELEASE_NULL(mData);

    this->mCCNodeLoaderLibrary->release();

    CC_SAFE_RELEASE(mOwnerOutletNodes);
    mOwnerOutletNames.clear();
    CC_SAFE_RELEASE(mOwnerCallbackNodes);
    mOwnerCallbackNames.clear();

    // Clear string cache.

    this->mStringCache.clear();
    CC_SAFE_RELEASE(mNodesWithAnimationManagers);
    CC_SAFE_RELEASE(mAnimationManagersForNodes);

    setAnimationManager(NULL);
}

void CCBReader::setCCBRootPath(const char* pCCBRootPath)
{
    CCAssert(pCCBRootPath != NULL, "");
    mCCBRootPath = pCCBRootPath;
}

const std::string& CCBReader::getCCBRootPath() const
{
    return mCCBRootPath;
}

bool CCBReader::init()
{
    // Setup action manager
    CCBAnimationManager *pActionManager = new CCBAnimationManager();
    setAnimationManager(pActionManager);
    pActionManager->release();
    
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

CCDictionary* CCBReader::getAnimationManagers()
{
    return mActionManagers;
}

void CCBReader::setAnimationManagers(CCDictionary* x)
{
    mActionManagers = x;
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

CCNode* CCBReader::readNodeGraphFromFile(const char *pCCBFileName, CCObject *pOwner, const CCSize &parentSize)
{
    if (NULL == pCCBFileName || strlen(pCCBFileName) == 0)
    {
        return NULL;
    }

    std::string strCCBFileName(pCCBFileName);
    std::string strSuffix(".ccbi");
    // Add ccbi suffix
    if (!CCBReader::endsWith(strCCBFileName.c_str(), strSuffix.c_str()))
    {
        strCCBFileName += strSuffix;
    }

    std::string strPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(strCCBFileName.c_str());
    unsigned long size = 0;

    unsigned char * pBytes = CCFileUtils::sharedFileUtils()->getFileData(strPath.c_str(), "rb", &size);
    CCData *data = new CCData(pBytes, size);
    CC_SAFE_DELETE_ARRAY(pBytes);

    CCNode *ret =  this->readNodeGraphFromData(data, pOwner, parentSize);
    
    data->release();
    
    return ret;
}

CCNode* CCBReader::readNodeGraphFromData(CCData *pData, CCObject *pOwner, const CCSize &parentSize)
{
    mData = pData;
    CC_SAFE_RETAIN(mData);
    mBytes = mData->getBytes();
    mCurrentByte = 0;
    mCurrentBit = 0;
    mOwner = pOwner;
    CC_SAFE_RETAIN(mOwner);

    mActionManager->setRootContainerSize(parentSize);
    mActionManager->mOwner = mOwner;
    mOwnerOutletNodes = new CCArray();
    mOwnerCallbackNodes = new CCArray();
    
    CCDictionary* animationManagers = CCDictionary::create();
    CCNode *pNodeGraph = readFileWithCleanUp(true, animationManagers);
    
    if (pNodeGraph && mActionManager->getAutoPlaySequenceId() != -1 && !jsControlled)
    {
        // Auto play animations
        mActionManager->runAnimationsForSequenceIdTweenDuration(mActionManager->getAutoPlaySequenceId(), 0);
    }
    // Assign actionManagers to userObject
    if(jsControlled) {
        mNodesWithAnimationManagers = new CCArray();
        mAnimationManagersForNodes = new CCArray();
    }
    
    CCDictElement* pElement = NULL;
    CCDICT_FOREACH(animationManagers, pElement)
    {
        CCNode* pNode = (CCNode*)pElement->getIntKey();
        CCBAnimationManager* manager = (CCBAnimationManager*)animationManagers->objectForKey((intptr_t)pNode);
        pNode->setUserObject(manager);

        if (jsControlled)
        {
            mNodesWithAnimationManagers->addObject(pNode);
            mAnimationManagersForNodes->addObject(manager);
        }
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
    CCNode *pNode = readNodeGraphFromFile(pCCBFileName, pOwner, parentSize);
    CCScene *pScene = CCScene::create();
    pScene->addChild(pNode);
    
    return pScene;
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

CCNode* CCBReader::readFileWithCleanUp(bool bCleanUp, CCDictionary* am)
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
    
    setAnimationManagers(am);

    CCNode *pNode = readNodeGraph(NULL);

    mActionManagers->setObject(mActionManager, intptr_t(pNode));

    if (bCleanUp)
    {
        cleanUpNodeGraph(pNode);
    }
    
    return pNode;
}

bool CCBReader::readStringCache() {
    int numStrings = this->readInt(false);

    for(int i = 0; i < numStrings; i++) {
        this->mStringCache.push_back(this->readUTF8());
    }

    return true;
}

bool CCBReader::readHeader()
{
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

    // Read JS check
    jsControlled = this->readBool();
    mActionManager->jsControlled = jsControlled;

    return true;
}

unsigned char CCBReader::readByte() {
    unsigned char byte = this->mBytes[this->mCurrentByte];
    this->mCurrentByte++;
    return byte;
}

bool CCBReader::readBool() {
    return 0 == this->readByte() ? false : true;
}

std::string CCBReader::readUTF8()
{
    std::string ret;

    int b0 = this->readByte();
    int b1 = this->readByte();

    int numBytes = b0 << 8 | b1;

    char* pStr = (char*)malloc(numBytes+1);
    memcpy(pStr, mBytes+mCurrentByte, numBytes);
    pStr[numBytes] = '\0';
    ret = pStr;
    free(pStr);

    mCurrentByte += numBytes;

    return ret;
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

int CCBReader::readInt(bool pSigned) {
    // Read encoded int
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
            {
                /* using a memcpy since the compiler isn't
                 * doing the float ptr math correctly on device.
                 * TODO still applies in C++ ? */
                unsigned char* pF = (this->mBytes + this->mCurrentByte);
                float f = 0;
                
                // N.B - in order to avoid an unaligned memory access crash on 'memcpy()' the the (void*) casts of the source and
                // destination pointers are EXTREMELY important for the ARM compiler.
                //
                // Without a (void*) cast, the ARM compiler makes the assumption that the float* pointer is naturally aligned
                // according to it's type size (aligned along 4 byte boundaries) and thus tries to call a more optimized
                // version of memcpy() which makes this alignment assumption also. When reading back from a file of course our pointers
                // may not be aligned, hence we need to avoid the compiler making this assumption. The (void*) cast serves this purpose,
                // and causes the ARM compiler to choose the slower, more generalized (unaligned) version of memcpy()
                //
                // For more about this compiler behavior, see:
                // http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.faqs/ka3934.html
                memcpy((void*) &f, (const void*) pF, sizeof(float));
                
                this->mCurrentByte += sizeof(float);
                return f;
            }
    }
}

std::string CCBReader::readCachedString() {
    int n = this->readInt(false);
    return this->mStringCache[n];
}

CCNode * CCBReader::readNodeGraph(CCNode * pParent) {
    /* Read class name. */
    std::string className = this->readCachedString();

    std::string jsControlledName;
    
    if(jsControlled) {
        jsControlledName = this->readCachedString();
    }
    
    // Read assignment type and name
    int memberVarAssignmentType = this->readInt(false);
    std::string memberVarAssignmentName;
    if(memberVarAssignmentType != kCCBTargetTypeNone) {
        memberVarAssignmentName = this->readCachedString();
    }

    CCNodeLoader *ccNodeLoader = this->mCCNodeLoaderLibrary->getCCNodeLoader(className.c_str());
    if (! ccNodeLoader)
    {
        CCLog("no corresponding node loader for %s", className.c_str());
        return NULL;
    }

    CCNode *node = ccNodeLoader->loadCCNode(pParent, this);

    // Set root node
    if (! mActionManager->getRootNode())
    {
        mActionManager->setRootNode(node);
    }
    
    // Assign controller
    if(jsControlled && node == mActionManager->getRootNode())
    {
        mActionManager->setDocumentControllerName(jsControlledName);
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
            
            seqProp->setName(readCachedString().c_str());
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
    
    bool isCCBFileNode = dynamic_cast<CCBFile*>(node);
    // Handle sub ccb files (remove middle node)
    if (isCCBFileNode)
    {
        CCBFile *ccbFileNode = (CCBFile*)node;
        
        CCNode *embeddedNode = ccbFileNode->getCCBFileNode();
        embeddedNode->setPosition(ccbFileNode->getPosition());
        embeddedNode->setRotation(ccbFileNode->getRotation());
        embeddedNode->setScaleX(ccbFileNode->getScaleX());
        embeddedNode->setScaleY(ccbFileNode->getScaleY());
        embeddedNode->setTag(ccbFileNode->getTag());
        embeddedNode->setVisible(true);
        embeddedNode->ignoreAnchorPointForPosition(ccbFileNode->isIgnoreAnchorPointForPosition());
        
        mActionManager->moveAnimationsFromNode(ccbFileNode, embeddedNode);

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
    if (memberVarAssignmentType != kCCBTargetTypeNone)
    {
        if(!jsControlled)
        {
            CCObject * target = NULL;
            if(memberVarAssignmentType == kCCBTargetTypeDocumentRoot) 
            {
                target = mActionManager->getRootNode();
            } 
            else if(memberVarAssignmentType == kCCBTargetTypeOwner) 
            {
                target = this->mOwner;
            }
            
            if(target != NULL)
            {
                CCBMemberVariableAssigner * targetAsCCBMemberVariableAssigner = dynamic_cast<CCBMemberVariableAssigner *>(target);
                
                bool assigned = false;
                if (memberVarAssignmentType != kCCBTargetTypeNone)
                {
                    if(targetAsCCBMemberVariableAssigner != NULL) {
                        assigned = targetAsCCBMemberVariableAssigner->onAssignCCBMemberVariable(target, memberVarAssignmentName.c_str(), node);
                    }
                    
                    if(!assigned && this->mCCBMemberVariableAssigner != NULL) {
                        assigned = this->mCCBMemberVariableAssigner->onAssignCCBMemberVariable(target, memberVarAssignmentName.c_str(), node);
                    }
                }
            }
        }
        else
        {
            if(memberVarAssignmentType == kCCBTargetTypeDocumentRoot) {
                mActionManager->addDocumentOutletName(memberVarAssignmentName);
                mActionManager->addDocumentOutletNode(node);
            } else {
                mOwnerOutletNames.push_back(memberVarAssignmentName);
                mOwnerOutletNodes->addObject(node);
            }
        }
    }
    
    // Assign custom properties.
    if (ccNodeLoader->getCustomProperties()->count() > 0) {
            
        bool customAssigned = false;
        
        if(!jsControlled)
        {
            CCObject * target = node;
            if(target != NULL)
            {
                CCBMemberVariableAssigner * targetAsCCBMemberVariableAssigner = dynamic_cast<CCBMemberVariableAssigner *>(target);
                if(targetAsCCBMemberVariableAssigner != NULL) {
                    
                    CCDictionary* pCustomPropeties = ccNodeLoader->getCustomProperties();
                    CCDictElement* pElement;
                    CCDICT_FOREACH(pCustomPropeties, pElement)
                    {
                        customAssigned = targetAsCCBMemberVariableAssigner->onAssignCCBCustomProperty(target, pElement->getStrKey(), (CCBValue*)pElement->getObject());

                        if(!customAssigned && this->mCCBMemberVariableAssigner != NULL)
                        {
                            customAssigned = this->mCCBMemberVariableAssigner->onAssignCCBCustomProperty(target, pElement->getStrKey(), (CCBValue*)pElement->getObject());
                        }
                    }
                }
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

    // FIX ISSUE #1860: "onNodeLoaded will be called twice if ccb was added as a CCBFile".
    // If it's a sub-ccb node, skip notification to CCNodeLoaderListener since it will be
    // notified at LINE #734: CCNode * child = this->readNodeGraph(node);
    if (!isCCBFileNode) {
        // Call onNodeLoaded
        CCNodeLoaderListener * nodeAsCCNodeLoaderListener = dynamic_cast<CCNodeLoaderListener *>(node);
        if(nodeAsCCNodeLoaderListener != NULL) {
            nodeAsCCNodeLoaderListener->onNodeLoaded(node, ccNodeLoader);
        } else if(this->mCCNodeLoaderListener != NULL) {
            this->mCCNodeLoaderListener->onNodeLoaded(node, ccNodeLoader);
        }
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
    else if (type == kCCBPropTypeScaleLock || type == kCCBPropTypePosition
	     || type == kCCBPropTypeFloatXY)
    {
        float a = readFloat();
        float b = readFloat();
        
        value = CCArray::create(CCBValue::create(a),
                                CCBValue::create(b),
                                NULL);
    }
    else if (type == kCCBPropTypeSpriteFrame)
    {
        std::string spriteSheet = readCachedString();
        std::string spriteFile = readCachedString();
        
        CCSpriteFrame* spriteFrame;

        if (spriteSheet.length() == 0)
        {
            spriteFile = mCCBRootPath + spriteFile;
            CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(spriteFile.c_str());
            CCRect bounds = CCRectMake(0, 0, texture->getContentSize().width, texture->getContentSize().height);
            spriteFrame = CCSpriteFrame::createWithTexture(texture, bounds);
        }
        else
        {
            spriteSheet = mCCBRootPath + spriteSheet;
            CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
            
            // Load the sprite sheet only if it is not loaded            
            if (mLoadedSpriteSheets.find(spriteSheet) == mLoadedSpriteSheets.end())
            {
                frameCache->addSpriteFramesWithFile(spriteSheet.c_str());
                mLoadedSpriteSheets.insert(spriteSheet);
            }
            
            spriteFrame = frameCache->spriteFrameByName(spriteFile.c_str());
        }
        value = spriteFrame;
    }
    
    keyframe->setValue(value);
    
    return  keyframe;
}


bool CCBReader::readCallbackKeyframesForSeq(CCBSequence* seq) {
    int numKeyframes = readInt(false);
    if(!numKeyframes) return true;
    
    CCBSequenceProperty* channel = new CCBSequenceProperty();
    channel->autorelease();

    for(int i = 0; i < numKeyframes; ++i) {
      
        float time = readFloat();
        std::string callbackName = readCachedString();
      
        int callbackType = readInt(false);
      
        CCArray* value = CCArray::create();
        value->addObject(CCString::create(callbackName));
        value->addObject(CCString::createWithFormat("%d", callbackType));
        
        CCBKeyframe* keyframe = new CCBKeyframe();
        keyframe->autorelease();
        
        keyframe->setTime(time);
        keyframe->setValue(value);
        
        if(jsControlled) {
            string callbackIdentifier;
            mActionManager->getKeyframeCallbacks()->addObject(CCString::createWithFormat("%d:%s",callbackType, callbackName.c_str()));
        }
    
        channel->getKeyframes()->addObject(keyframe);
    }
    
    seq->setCallbackChannel(channel);
    
    return true;
}

bool CCBReader::readSoundKeyframesForSeq(CCBSequence* seq) {
    int numKeyframes = readInt(false);
    if(!numKeyframes) return true;
    
    CCBSequenceProperty* channel = new CCBSequenceProperty();
    channel->autorelease();

    for(int i = 0; i < numKeyframes; ++i) {
        
        float time = readFloat();
        std::string soundFile = readCachedString();
        float pitch = readFloat();
        float pan = readFloat();
        float gain = readFloat();
                
        CCArray* value = CCArray::create();
        
        value->addObject(CCString::create(soundFile));
        value->addObject(CCString::createWithFormat("%f", pitch));
        value->addObject(CCString::createWithFormat("%f", pan));
        value->addObject(CCString::createWithFormat("%f", gain));
        
        CCBKeyframe* keyframe = new CCBKeyframe();
        keyframe->setTime(time);
        keyframe->setValue(value);
        channel->getKeyframes()->addObject(keyframe);
        keyframe->release();
    }
    
    seq->setSoundChannel(channel);
    
    return true;
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
        seq->setName(readCachedString().c_str());
        seq->setSequenceId(readInt(false));
        seq->setChainedSequenceId(readInt(true));
        
        if(!readCallbackKeyframesForSeq(seq)) return false;
        if(!readSoundKeyframesForSeq(seq)) return false;
        
        sequences->addObject(seq);
    }
    
    mActionManager->setAutoPlaySequenceId(readInt(true));
    return true;
}

std::string CCBReader::lastPathComponent(const char* pPath) {
    std::string path(pPath);
    size_t slashPos = path.find_last_of("/");
    if(slashPos != std::string::npos) {
        return path.substr(slashPos + 1, path.length() - slashPos);
    }
    return path;
}

std::string CCBReader::deletePathExtension(const char* pPath) {
    std::string path(pPath);
    size_t dotPos = path.find_last_of(".");
    if(dotPos != std::string::npos) {
        return path.substr(0, dotPos);
    }
    return path;
}

std::string CCBReader::toLowerCase(const char* pString) {
    std::string copy(pString);
    std::transform(copy.begin(), copy.end(), copy.begin(), ::tolower);
    return copy;
}

bool CCBReader::endsWith(const char* pString, const char* pEnding) {
    std::string string(pString);
    std::string ending(pEnding);
    if(string.length() >= ending.length()) {
        return (string.compare(string.length() - ending.length(), ending.length(), ending) == 0);
    } else {
        return false;
    }
}

bool CCBReader::isJSControlled() {
    return jsControlled;
}

void CCBReader::addOwnerCallbackName(std::string name) {
    mOwnerCallbackNames.push_back(name);
}

void CCBReader::addOwnerCallbackNode(CCNode *node) {
    mOwnerCallbackNodes->addObject(node);
}


void CCBReader::addDocumentCallbackName(std::string name) {
    mActionManager->addDocumentCallbackName(name);
}

void CCBReader::addDocumentCallbackNode(CCNode *node) {
    mActionManager->addDocumentCallbackNode(node);
}


CCArray* CCBReader::getOwnerCallbackNames() {
    CCArray* pRet = CCArray::createWithCapacity(mOwnerCallbackNames.size());
    std::vector<std::string>::iterator it = mOwnerCallbackNames.begin();
    for (; it != mOwnerCallbackNames.end(); ++it)
    {
        pRet->addObject(CCString::create(*it));
    }
    
    return pRet;
}

CCArray* CCBReader::getOwnerCallbackNodes() {
    return mOwnerCallbackNodes;
}

CCArray* CCBReader::getOwnerOutletNames() {
    CCArray* pRet = CCArray::createWithCapacity(mOwnerOutletNames.size());
    std::vector<std::string>::iterator it = mOwnerOutletNames.begin();
    for (; it != mOwnerOutletNames.end(); ++it)
    {
        pRet->addObject(CCString::create(*it));
    }
    return pRet;
}

CCArray* CCBReader::getOwnerOutletNodes() {
    return mOwnerOutletNodes;
}

CCArray* CCBReader::getNodesWithAnimationManagers() {
    return mNodesWithAnimationManagers;
}

CCArray* CCBReader::getAnimationManagersForNodes() {
    return mAnimationManagersForNodes;
}

/************************************************************************
 Static functions
 ************************************************************************/

static float __ccbResolutionScale = 1.0f;

float CCBReader::getResolutionScale()
{
    return __ccbResolutionScale;
}

void CCBReader::setResolutionScale(float scale)
{
    __ccbResolutionScale = scale;
}

NS_CC_EXT_END;
