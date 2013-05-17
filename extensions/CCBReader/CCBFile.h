#ifndef _CCB_CCBFILE_H_
#define _CCB_CCBFILE_H_

#include "cocos2d.h"
#include "ExtensionMacros.h"
#include "CCBNodeWrapper.h"

NS_CC_EXT_BEGIN

/**
 * @addtogroup cocosbuilder
 * @{
 */

class CCBFile : public CCNode, public CCBNodeWrapper
{
private:
    CCNode *mCCBFileNode;
    
public:
    CCBFile();
    virtual ~CCBFile();
    
    static CCBFile* create();
    
    CCNode* getCCBFileNode();
    void setCCBFileNode(CCNode *pNode); // retain

    virtual CCNode *unwrapNode();
};

// end of effects group
/// @}

NS_CC_EXT_END

#endif
