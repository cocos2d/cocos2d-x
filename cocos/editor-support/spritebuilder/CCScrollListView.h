#ifndef _CCB_CCSCROLLLISTVIEW_H_
#define _CCB_CCSCROLLLISTVIEW_H_

#include "ui/UIListView.h"
#include "SpriteBuilder.h"
#include "base/CCRef.h"

NS_CC_BEGIN
namespace spritebuilder {

class CC_DLL ScrollListView : public ui::ListView
{
public:
    static ScrollListView *create(NodeLoader *templateLoader, float mainScale, float additionalScale);
    
    /**
     * Push back custom item into listview.
     */
    ui::Widget* pushBackElement(spritebuilder::CCBXReaderOwner * owner);
    
    /**
     * Insert custom item into listview.
     */
    ui::Widget* insertElement(ssize_t index, spritebuilder::CCBXReaderOwner * owner);
    
CC_CONSTRUCTOR_ACCESS:
    ScrollListView(NodeLoader *templateLoader, float mainScale, float additionalScale);
    ~ScrollListView();
    
private:
    NodeLoader * _template;
    float _mainScale = 1.0f;
    float _additionalScale = 1.0f;
};

}

NS_CC_END

#endif
