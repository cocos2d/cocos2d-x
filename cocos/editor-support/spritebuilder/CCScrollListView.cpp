//
//  RjScrollListView.cpp
//  inferno
//
//  Created by user-i121 on 03.07.13.
//
//

#include "CCScrollListView.h"
#include "platform/CCFileUtils.h"
#include "2d/CCActionInterval.h"
#include "2d/CCActionInstant.h"
#include "base/CCDirector.h"
#include "CCBXNodeLoader.h"

NS_CC_BEGIN
namespace spritebuilder {
    
    ScrollListView* ScrollListView::create(NodeLoader *templateLoader, float mainScale, float additionalScale)
{
    ScrollListView* widget = new (std::nothrow) ScrollListView(templateLoader, mainScale, additionalScale);
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

ScrollListView::ScrollListView(NodeLoader *templateLoader, float mainScale, float additionalScale):_template(templateLoader), _mainScale(mainScale), _additionalScale(additionalScale)
{
    CC_SAFE_RETAIN(_template);
}
    
ScrollListView::~ScrollListView()
{
    CC_SAFE_RELEASE(_template);
}
    
ui::Widget* ScrollListView::pushBackElement(spritebuilder::CCBXReaderOwner * owner)
{
    Node * node =_template->createNode(getContentSize(), _mainScale, _additionalScale, owner);
    ui::Widget *ret = static_cast<ui::Widget*>(node);
    assert(dynamic_cast<ui::Widget*>(node));
    pushBackCustomItem(ret);
    return ret;
}

ui::Widget* ScrollListView::insertElement(ssize_t index, spritebuilder::CCBXReaderOwner * owner)
{
    Node * node =_template->createNode(getContentSize(), _mainScale, _additionalScale, owner);
    ui::Widget *ret = static_cast<ui::Widget*>(node);
    assert(dynamic_cast<ui::Widget*>(node));
    insertCustomItem(ret, index);
    return ret;
}
    
}

NS_CC_END
