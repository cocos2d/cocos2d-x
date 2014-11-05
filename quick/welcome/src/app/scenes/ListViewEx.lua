local ListViewEx = class("ListViewEx", cc.ui.UIListView)



function ListViewEx:ctor(params)
    params.bgScale9 = true
    ListViewEx.super.ctor(self, params)

    self.currentIndex_ = 0
    self.currentItem_ = nil

    self:onTouch(handler(self, self.touchCallback))
end

function ListViewEx:setHighlightNode(node)
    self.highlightNode_ = node
    
    if node then
        self.container:addChild(node, -1)
    end
end

function ListViewEx:getItemCount()
    return #self.items_
end

function ListViewEx:getCurrentIndex()
    return self.currentIndex_
end

function ListViewEx:currentNode()
    return self.currentItem_
end

function ListViewEx:setCurrentIndex(index)
    if index > 0 and index <= #self.items_ then
        self.currentIndex_ = index
        self.currentItem_ = self.items_[index]

        self:highlightItem_(self.currentItem_)
    end
end

function ListViewEx:setCurrentNode(item)
    local index = self:getItemPos(item)
    if item and index then
        self.currentIndex_ = index
        self.currentItem_ = item

        self:highlightItem_(item)
    end
end

function ListViewEx:removeCurrentItem()
    if self.currentItem_ then
        self:removeItem(self.currentItem_, true)

        self.currentItem_ = nil
        self.currentIndex_ = 0
    end

    if #self.items_ <= 0 and self.highlightNode_ then self.highlightNode_:setVisible(false)  end
end


function ListViewEx:touchCallback(event)
    if not event.listView:isItemInViewRect(event.itemPos) then
        return
    end

    local listView = event.listView
    if "clicked" == event.name then
        self:highlightItem_(event.item)
        self.currentIndex_ = event.itemPos
        self.currentItem_ = event.item
    end
end


-- helper

function ListViewEx:highlightItem_(item)
    if self.highlightNode_ then
        self.highlightNode_:setVisible(true)

        local y = (self:getItemCount() - self:getItemPos(item) +1) * item:getContentSize().height
        transition.moveTo(self.highlightNode_, {time = 0.1, x = 0,
                                                            y = y-4,
                                                            easing = "sineOut",
                                                            onComplete = function()
                                                                self:elasticScroll()
                                                            end})
    end
end

return ListViewEx