#include "CCBFile.h"

#include "CCBMemberVariableAssigner.h"
#include "CCBSelectorResolver.h"

NS_CC_EXT_BEGIN;

/*************************************************************************
 Implementation of CCBFile
 *************************************************************************/

CCBFile::CCBFile():mCCBFileNode(NULL) {}

CCBFile::~CCBFile()
{
    CC_SAFE_RELEASE(mCCBFileNode);
}

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

CCNode* CCBFile::unwrapNode()
{
    if( !mCCBFileNode )
        return NULL;

    mCCBFileNode->setPosition(getPosition());
    mCCBFileNode->setRotationX(getRotationX());
    mCCBFileNode->setRotationY(getRotationY());
    mCCBFileNode->setScaleX(getScaleX());
    mCCBFileNode->setScaleY(getScaleY());
    mCCBFileNode->setSkewX(getSkewX());
    mCCBFileNode->setSkewY(getSkewY());
    mCCBFileNode->setTag(getTag());
    mCCBFileNode->setVisible(true);
    //mCCBFileNode->ignoreAnchorPointForPosition(isIgnoreAnchorPointForPosition());

    return mCCBFileNode;
}

NS_CC_EXT_END;
