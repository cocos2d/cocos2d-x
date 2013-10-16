//
//  UIListViewEx.h
//  TestCpp
//
//  Created by cai wenzhi on 13-10-14.
//
//

#ifndef __TestCpp__UIListViewEx__
#define __TestCpp__UIListViewEx__

#include "UIScrollView.h"

NS_CC_EXT_BEGIN

class UIListViewEx
{
    
public:

    /**
     * Default constructor
     */
    UIListViewEx();
    
    /**
     * Default destructor
     */
    virtual ~UIListViewEx();
    
    /**
     * Allocates and initializes.
     */
    static UIListViewEx* create();

    void setItemModel(UIWidget* model);

    void pushBackItem();
    void insetItem(int index);

protected:

    UIWidget* m_pModel;
    
};

NS_CC_EXT_END

#endif /* defined(__TestCpp__UIListViewEx__) */
