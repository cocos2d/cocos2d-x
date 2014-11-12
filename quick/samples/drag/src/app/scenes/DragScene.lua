local c1 = cc.c3b(55,55,55)
local c2 = cc.c3b(255,51,103)
local c3 = cc.c3b(166,222,249)
local c4 = cc.c3b(100,100,100)

local boxSize = cc.size(90,90)
local objSize = cc.size(80,80)

local DragScene = class("DragScene", function()
    return display.newScene("DragScene")
end)

function DragScene:ctor()
    --背包格子数据
    self.t_data = {}
    --拖拽对象
    self.drag = nil
    --索引
    self._index = 0
    self._indexMax = 3
    --加载ui
    self:initUI()
    self:_addUI()
    --加载拖拽1
    self:loadDrag1()
    
end

function DragScene:_addUI()
    cc.ui.UIPushButton.new("close.png")
        :align(display.RIGHT_BOTTOM, display.width, display.bottom)
        :addTo(self, 0)
        :onButtonClicked(function()
            os.exit()
        end)

    self._prevBtn = cc.ui.UIPushButton.new({normal="b1.png",pressed="b2.png"})
        :align(display.BOTTOM_CENTER, display.cx-100, display.bottom)
        :addTo(self, 0)
        :onButtonClicked(function() 
            self._index = self._index-1  
            if self._index < 0 then self._index = self._indexMax end
            self:changeLayer() end
            )
    self._resetBtn = cc.ui.UIPushButton.new({normal="r1.png",pressed="r2.png"})
        :align(display.BOTTOM_CENTER, display.cx, display.bottom)
        :addTo(self, 0)
        :onButtonClicked(function() self:changeLayer() end)
    
    self._nextBtn = cc.ui.UIPushButton.new({normal="f1.png",pressed="f2.png"})
        :align(display.BOTTOM_CENTER, display.cx+100, display.bottom)
        :addTo(self, 0)
        :onButtonClicked(function() 
            self._index = self._index+1  
            if self._index > self._indexMax then self._index = 0 end
            self:changeLayer() end
            )

    self._title = cc.ui.UILabel.new({
        UILabelType = 2,
        text="Filters test",
    })
        :align(display.CENTER, display.cx, display.top-40)
        :addTo(self, 10)
end

function DragScene:changeLayer()
    if self._index == 0 then
        self:loadDrag1()
    elseif self._index == 1 then
        self:loadDrag2()
    elseif self._index == 2 then
        self:loadDrag3()
    elseif self._index == 3 then
        self:loadDrag4()
--    
--    elseif self._index == 0 then
--    
--    elseif self._index == 0 then
--    
    end
    
end

--[[--
创建一个装备
]]
function DragScene:createEquipement(text)
    local obj1 = cc.LayerColor:create(cc.c4b(55,55,55,255),objSize.width,objSize.height)
    --当作图片处理
    obj1:ignoreAnchorPointForPosition(false)
    local lab_o1 = display.newTTFLabel({text=text,color=c2,align=cc.ui.TEXT_ALIGN_CENTER,size=28})
    lab_o1:setPosition(cc.p(obj1:getContentSize().width/2,obj1:getContentSize().height/2))
    obj1:addChild(lab_o1)
    return obj1
end

--[[--
初始化装备
]]
function DragScene:createEquipements()
    local equList = {}
    --屠龙
    local obj1 = self:createEquipement("屠龙")
    --设置拖拽对象的tag,或者设置userData也可以。
    obj1:setTag(1)
    equList[#equList+1] = obj1

    --圣战宝甲
    local obj2 = self:createEquipement("圣战\n宝甲")
    --设置拖拽对象的tag,或者设置userData也可以。
    obj2:setTag(2)
    equList[#equList+1] = obj2

    --圣战头盔
    local obj3 = self:createEquipement("圣战\n头盔")
    --设置拖拽对象的tag,或者设置userData也可以。
    obj3:setTag(3)
    equList[#equList+1] = obj3

    --圣战鞋子
    local obj4 = self:createEquipement("圣战\n鞋子")
    --设置拖拽对象的tag,或者设置userData也可以。
    obj4:setTag(4)
    equList[#equList+1] = obj4

    --圣战腰带
    local obj5 = self:createEquipement("圣战\n腰带")
    --设置拖拽对象的tag,或者设置userData也可以。
    obj5:setTag(5)
    equList[#equList+1] = obj5
    return equList
end

--[[--
创建一个装备box
]]
function DragScene:createEquipmentBox(text,point)
    local box1 = cc.LayerColor:create(cc.c4b(c4.r,c4.g,c4.b,255),boxSize.width,boxSize.height)
    box1:setPosition(point)
    local lab1 = display.newTTFLabel({text=text,color=c3,align=cc.ui.TEXT_ALIGN_CENTER,size=30})
    lab1:setPosition(cc.p(box1:getContentSize().width/2,box1:getContentSize().height/2))
    box1:addChild(lab1)
    return box1
end

function DragScene:initUI()
    self.box1 = self:createEquipmentBox("武器",cc.p(display.width/2/2-boxSize.width/2,display.height/10*7))
    self:addChild(self.box1)

    --衣服
    self.box2 = self:createEquipmentBox("衣服",cc.p(display.width/2/2/3-boxSize.width/2,display.height/10*4))
    self:addChild(self.box2)

    --头盔
    self.box3 = self:createEquipmentBox("头盔",cc.p(display.width/2/2*1.6666-boxSize.width/2,display.height/10*4))
    self:addChild(self.box3)

    --鞋子
    self.box4 = self:createEquipmentBox("鞋子",cc.p(display.width/2/2/2-boxSize.width/2,display.height/10))
    self:addChild(self.box4)

    --腰带
    self.box5 = self:createEquipmentBox("腰带",cc.p(display.width/2/2*1.5-boxSize.width/2,display.height/10))
    self:addChild(self.box5)

    --人物
    local lab6 = display.newTTFLabel({text="人物",color=c3,size=60})
    lab6:setPosition(cc.p(self.box1:getPositionX()+self.box1:getContentSize().width/2,self.box2:getPositionY()+self.box2:getContentSize().height/2))
    self:addChild(lab6)

    --背包
    local bg = cc.LayerColor:create(cc.c4b(100,100,100,255),400,500)
    self:addChild(bg)
    bg:setPosition(cc.p(display.width/2+(display.width/2-400)/2,(display.height-500)/2))

    self.view =  cc.ui.UIScrollView.new(
        {viewRect = cc.rect(0,0, bg:getContentSize().width, bg:getContentSize().height), direction = 1})
    bg:addChild(self.view);
    self.t_data = {}
    for i = 1, 100 do
        local png = cc.LayerColor:create(cc.c4b(160,160,160,255),boxSize.width,boxSize.height)
        png:setTouchSwallowEnabled(false)
        --把layer当作精灵来处理
        png:ignoreAnchorPointForPosition(false)
        self.t_data[#self.t_data+1] = png
        display.newTTFLabel({text = i, size = 30, color = cc.c3b(100,100,100)})
            :align(display.CENTER, png:getContentSize().width/2, png:getContentSize().height/2)
            :addTo(png)
    end
    self.view:fill(self.t_data, {itemSize = (self.t_data[#self.t_data]):getContentSize()})
    SCROLL_HANDLER_SLIDE(self.view)
    S_XY(self.view:getScrollNode(),0,self.view:getViewRect().height-H(self.view:getScrollNode()))

end

--基本拖拽分组判定
function DragScene:loadDrag1()
    self._title:setString("拖拽项group的运用,以及在scroll之类裁剪容器的运用")

    if self.drag then
        self.drag:removeDragAll()
        self.drag:removeFromParent()
    end
    --创建拖拽对象
    self.drag = UIDrag.new()
    self.drag:setTouchSwallowEnabled(false)
    self:addChild(self.drag,999)
    --拖拽前事件
    self.drag:setOnDragUpBeforeEvent(function(currentItem,point)
        --判定是否真正的触摸到scroll的内部窗体
        if self.drag:handler_ScrollView(self.view,point) then return end
        return true
    end)
    --拖拽放下之前
    self.drag:setOnDragDownBeforeEvent(function(currentItem,targetItem,point)
        --判定是否真正的触摸到scroll的内部窗体
        if self.drag:handler_ScrollView(self.view,point) then return end

        if targetItem then
            --背包可以随意拖放
            if targetItem:getGroup() == 1000 then
                return true
            end
            --背包里对应的装备只能装备到指定的位置上
            if currentItem.dragObj:getTag() ~= targetItem:getGroup()  then
                return false
            end
        end

        return true
    end)
    --拖拽放下之后
    self.drag:setOnDragDownAfterEvent(function(currentItem,targetItem,point)
        print("放下成功")
    end)

    --让盒子box1具备拖拽属性,设置盒子的属性标记tag
    self.drag:addDragItem(self.box1):setGroup(1)
    self.drag:addDragItem(self.box2):setGroup(2)
    self.drag:addDragItem(self.box3):setGroup(3)
    self.drag:addDragItem(self.box4):setGroup(4)
    self.drag:addDragItem(self.box5):setGroup(5)

    --让背包具备拖拽属性
    for i = 1 , #self.t_data do
        self.drag:addDragItem(self.t_data[i]):setGroup(1000)
    end

    --装备放到背包里
    local equList = self:createEquipements()
    self.drag:find(self.t_data[1]):setDragObj(equList[1])
    self.drag:find(self.t_data[2]):setDragObj(equList[2])
    self.drag:find(self.t_data[3]):setDragObj(equList[3])
    self.drag:find(self.t_data[4]):setDragObj(equList[4])
    self.drag:find(self.t_data[5]):setDragObj(equList[5])

end

function DragScene:loadDrag2()
    self._title:setString("交换拖拽")

    if self.drag then
        self.drag:removeDragAll()
        self.drag:removeFromParent()
    end
    --创建拖拽对象
    self.drag = UIDrag.new()
    --支持交换拖拽
    self.drag.isExchangeModel = true
    self.drag:setTouchSwallowEnabled(false)
    self:addChild(self.drag,999)
    --拖拽前事件
    self.drag:setOnDragUpBeforeEvent(function(currentItem,point)
        --判定是否真正的触摸到scroll的内部窗体
        if self.drag:handler_ScrollView(self.view,point) then return end
        return true
    end)
    --拖拽放下之前
    self.drag:setOnDragDownBeforeEvent(function(currentItem,targetItem,point)
        --判定是否真正的触摸到scroll的内部窗体
        if self.drag:handler_ScrollView(self.view,point) then return end

        if targetItem then
            --背包内部操作
            if currentItem:getGroup() == 1000 and targetItem:getGroup() == 1000 then
                --物品交换只允许在背包内部
                if currentItem.dragObj and targetItem.dragObj then
                    return true
                elseif not targetItem.dragObj then
                    --背包空拖拽
                    return true
                end
            end

            --装备栏操作,只有一种操作，就是放入空的背包格
            if currentItem:getGroup() ~= 1000 and targetItem:getGroup() == 1000 and not targetItem.dragObj then
                return true
            end

            --背包里对应的装备只能装备到指定的位置上
            if currentItem:getGroup() == 1000 and targetItem:getGroup() ~= 1000  
                and currentItem.dragObj:getTag() == targetItem:getGroup()  then
                return true
            end
        end

        return false
    end)
    --拖拽放下之后
    self.drag:setOnDragDownAfterEvent(function(currentItem,targetItem,point)
        print("放下成功")
    end)

    --让盒子box1具备拖拽属性,设置盒子的属性标记tag
    self.drag:addDragItem(self.box1):setGroup(1)
    self.drag:addDragItem(self.box2):setGroup(2)
    self.drag:addDragItem(self.box3):setGroup(3)
    self.drag:addDragItem(self.box4):setGroup(4)
    self.drag:addDragItem(self.box5):setGroup(5)

    --让背包具备拖拽属性
    for i = 1 , #self.t_data do
        self.drag:addDragItem(self.t_data[i]):setGroup(1000)
    end

    --装备放到背包里
    local equList = self:createEquipements()
    self.drag:find(self.t_data[1]):setDragObj(equList[1])
    self.drag:find(self.t_data[2]):setDragObj(equList[2])
    self.drag:find(self.t_data[3]):setDragObj(equList[3])
    self.drag:find(self.t_data[4]):setDragObj(equList[4])
    self.drag:find(self.t_data[5]):setDragObj(equList[5])

end

function DragScene:loadDrag3()
    self._title:setString("残影拖拽")

    if self.drag then
        self.drag:removeDragAll()
        self.drag:removeFromParent()
    end
    --创建拖拽对象
    self.drag = UIDrag.new()
    --支持交换拖拽
    self.drag.isExchangeModel = true
    --镜像模式
    self.drag.isISOModel = true
    self.drag:setTouchSwallowEnabled(false)
    self:addChild(self.drag,999)
    --拖拽前事件
    self.drag:setOnDragUpBeforeEvent(function(currentItem,point)
        --判定是否真正的触摸到scroll的内部窗体
        if self.drag:handler_ScrollView(self.view,point) then return end
        return true
    end)

    --拖拽放下之前
    self.drag:setOnDragDownBeforeEvent(function(currentItem,targetItem,point)
        --判定是否真正的触摸到scroll的内部窗体
        if self.drag:handler_ScrollView(self.view,point) then return end

        if targetItem then
            --背包内部操作
            if currentItem:getGroup() == 1000 and targetItem:getGroup() == 1000 then
                --物品交换只允许在背包内部
                if currentItem.dragObj and targetItem.dragObj then
                    return true
                elseif not targetItem.dragObj then
                    --背包空拖拽
                    return true
                end
            end

            --装备栏操作,只有一种操作，就是放入空的背包格
            if currentItem:getGroup() ~= 1000 and targetItem:getGroup() == 1000 and not targetItem.dragObj then
                return true
            end

            --背包里对应的装备只能装备到指定的位置上
            if currentItem:getGroup() == 1000 and targetItem:getGroup() ~= 1000  
                and currentItem.dragObj:getTag() == targetItem:getGroup()  then
                return true
            end
        end

        return false
    end)
    --拖拽放下之后
    self.drag:setOnDragDownAfterEvent(function(currentItem,targetItem,point)
        print("放下成功")
    end)

    --让盒子box1具备拖拽属性,设置盒子的属性标记tag
    self.drag:addDragItem(self.box1):setGroup(1)
    self.drag:addDragItem(self.box2):setGroup(2)
    self.drag:addDragItem(self.box3):setGroup(3)
    self.drag:addDragItem(self.box4):setGroup(4)
    self.drag:addDragItem(self.box5):setGroup(5)

    --让背包具备拖拽属性
    for i = 1 , #self.t_data do
        self.drag:addDragItem(self.t_data[i]):setGroup(1000)
    end

    --装备放到背包里
    self.drag:find(self.t_data[1]):setDragObjFun(function()
        local obj = self:createEquipement("裁决")
        obj:setTag(1)
        return obj
    end)
    self.drag:find(self.t_data[2]):setDragObjFun(function()
        local obj = self:createEquipement("圣战\n宝甲")
        obj:setTag(2)
        return obj
    end)
    self.drag:find(self.t_data[3]):setDragObjFun(function()
        local obj = self:createEquipement("圣战\n头盔")
        obj:setTag(3)
        return obj
    end)
    self.drag:find(self.t_data[4]):setDragObjFun(function()
        local obj = self:createEquipement("圣战\n鞋子")
        obj:setTag(4)
        return obj
    end)
    self.drag:find(self.t_data[5]):setDragObjFun(function()
        local obj = self:createEquipement("圣战\n腰带")
        obj:setTag(5)
        return obj
    end)

end

function DragScene:loadDrag4()
    self._title:setString("拖拽区域判定")

    if self.drag then
        self.drag:removeDragAll()
        self.drag:removeFromParent()
    end
    --创建拖拽对象
    self.drag = UIDrag.new()
    --镜像模式
    self.drag.isISOModel = true
    self.drag:setTouchSwallowEnabled(false)
    self:addChild(self.drag,999)
    --拖拽前事件
    self.drag:setOnDragUpBeforeEvent(function(currentItem,point)
        --判定是否真正的触摸到scroll的内部窗体
        if self.drag:handler_ScrollView(self.view,point) then return end
        return true
    end)
    --拖拽移动
    self.drag:setOnDragMoveEvent(function(currentItem,dragObj,worldPoint,dragPoint)
        --判定是否真正的触摸到scroll的内部窗体\
        local rect = self.view:getViewRect()
        local lp = self.view:convertToWorldSpace(cc.p(0,0))
        local rect = cc.rect(lp.x,lp.y,rect.width,rect.height)
        
        dragObj:setPosition(cc.p(dragPoint.x,dragPoint.y))
        
        local x = dragPoint.x
        local y = dragPoint.y
        if (dragObj:getPositionX()-dragObj:getContentSize().width/2) <= rect.x then
            x = rect.x+dragObj:getContentSize().width/2
        end
        if (dragObj:getPositionX()+dragObj:getContentSize().width/2) >= rect.x+rect.width then
            x = rect.x+rect.width-dragObj:getContentSize().width/2
        end
        if (dragObj:getPositionY()-dragObj:getContentSize().height/2) <= rect.y then
            y = rect.y+dragObj:getContentSize().height/2
        end
        if (dragObj:getPositionY()+dragObj:getContentSize().height/2) >= rect.y+rect.height then
            y = rect.y+rect.height-dragObj:getContentSize().height/2
        end
        dragObj:setPosition(cc.p(x,y))
    end)
    --拖拽放下之前
    self.drag:setOnDragDownBeforeEvent(function(currentItem,targetItem,point)
        --判定是否真正的触摸到scroll的内部窗体
        if self.drag:handler_ScrollView(self.view,point) then return end
        return true
    end)
    --拖拽放下之后
    self.drag:setOnDragDownAfterEvent(function(currentItem,targetItem,point)
        print("放下成功")
    end)

    --让背包具备拖拽属性
    for i = 1 , #self.t_data do
        self.drag:addDragItem(self.t_data[i]):setGroup(1000)
    end

    --装备放到背包里
    self.drag:find(self.t_data[1]):setDragObj(self:createEquipement("雷裂"))
end

function DragScene:onEnter()
end

function DragScene:onExit()
end

return DragScene
