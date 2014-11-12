
--[[--

    --version 1.0

拖拽项数据类
拖拽的核心是基于一对逻辑数据，分别为，盒子和拖拽物，好比是背包的一个小格子是盒子，而格子里的道具就是拖拽物

@param box 绑定的盒子，此参数必须有。盒子是已经存在在其它容器里对象。 type:node
@param obj 拖拽物 type:node    --可选
@param z  拖拽物对于盒子z的加成。 type:int --可选
@param tag 标记，用于拖拽事件的逻辑判定 type:int  --可选

]]

UIDragItem = class("UIDragItem")

function UIDragItem:ctor(box,obj,z,tag)
    --拖拽物
    self.dragObj = nil
    --拖拽物在盒子内坐标,默认为盒子中间
    --  self.dragPoint = cc.p.ZERO
    --拖拽盒
    self.dragBox = box
    --拖拽对象
    self.dragObj = nil
    --拖拽对象生成方法
    self.dragObjFun = nil
    --拖拽标记
    self._group = -1
    --拖拽物如果在盒子上面则为1，在下面为-1
    self._z = 1

    if type(z) == "number" then
        self._z = z
    end
    if type(tag) == "number" then
        self._group = tag
    end
    if(obj)then
        self:setDragObj(obj)
    end
end

function UIDragItem:setGroup(group)
    self._group = group
end

function UIDragItem:getGroup()
    return self._group
end

function UIDragItem:setZ(z)
    self._z = z
end

--[[--
把一个对象设置在盒子里面，对象会以居中的方式显示在盒子内。
对象的显示层级是通过设置z来实现的
]]
function UIDragItem:setDragObj(obj)
    if obj then
        self.dragObj = obj

        self.dragBox:getParent():addChild(self.dragObj)
        local lz = self.dragBox:getLocalZOrder()
        lz = lz+self._z
        self.dragObj:setLocalZOrder(lz)
        --找到盒子的中心点
        local x = X(self.dragBox);
        local y = Y(self.dragBox);

        --盒子坐标转换
        if self.dragBox:isIgnoreAnchorPointForPosition() then
            x = x + W2(self.dragBox)
            y = y + H2(self.dragBox)
        else
            x = x + W(self.dragBox) * (0.5 - AX(self.dragBox))
            y = y + H(self.dragBox) * (0.5 - AY(self.dragBox))
        end

        --把拖拽物坐标转换
        if self.dragObj:isIgnoreAnchorPointForPosition() then
            x = x - W2(self.dragObj)
            y = y - H2(self.dragObj)
        else
            x = x - W(self.dragObj) * (0.5 - AX(self.dragObj))
            y = y - H(self.dragObj) * (0.5 - AY(self.dragObj))
        end

        S_XY(self.dragObj , x , y)

    elseif self.dragObj then
        --        if self.dragBox and self.dragBox:getParent() then
        self.dragObj:removeFromParent()
        --        end
        self.dragObj = nil
    end
    return self
end

--[[--
通过设置一个动态创建拖拽对象的匿名对象来设置拖拽对象
用此设置可以实现高级的复合拖拽对象功能。
@param fun Function 创建拖拽对象的匿名函数
]]
function UIDragItem:setDragObjFun(fun)
    self.dragObjFun = fun
    local obj = self.dragObjFun()
    self:setDragObj(nil)
    self:setDragObj(obj)
end

--[[--
返回一个拖拽对象的复制对象。必须先设置setDragObjFun
@return #Node 拖拽对克隆
]]
function UIDragItem:cloneDragObj()
    return self.dragObjFun()
end

--[[--

拖拽是基于一个大触摸层，在触摸层里响应拖拽，而此对象是建立这样一个触摸层。
所以要把这个触摸层放到一个合适的位置，然然后注册相对的要响应触摸的对象。

@param list 一组UIDragItem类型数据，{UIDragItem1,UIDragItem2,UIDragItem3}
]]

UIDrag = class("UIDrag",function()
    return display.newNode()
end)
function UIDrag:ctor(list)

    ---属性
    --放置框
    self._dragItems = {}
    --遮挡集合
    self._hinderList = {}
    --当前拖拽项
    self._currentDragItem = nil
    --当前拖拽物
    self._currentDragObj = nil
    --拖拽替换功能
    self.isExchangeModel = false
    --拖拽对象镜像模型
    self.isISOModel = false
    --    self._isBean = false
    --标记第一次移动
    self._isOnBean = false
    self._beanPoint = cc.p(0,0)

    if list then
        self._dragItems = list
    end

    --事件
    --拖拽之前
    self._onDragUpBeforeEvent = function(currentItem,point) return true end
    --拖拽之后
    self._onDragUpAfterEvent = function(currentItem,point) end
    --拖拽移动之前
    self._onDragMoveBeforeEvent = function(currentItem,point) end
    --拖拽移动
    self._onDragMoveEvent = function(currentItem,dragObj,worldPoint,dragPoint) end
    --拖拽放下之前
    self._onDragDownBeforeEvent = function(currentItem,targetItem,point) return true end
    --拖拽放下之后
    self._onDragDownAfterEvent = function(currentItem,targetItem,point) end

    S_SIZE(self,display.width,display.height)
    self:setTouchEnabled(true)
    --    self:setTouchSwallowEnabled(true)
    self:addNodeEventListener(cc.NODE_TOUCH_EVENT,function(event)
        if event.name == "began" then

            if self:onTouchBegan(cc.p(event.x,event.y)) then
                return true
            end
            return false

        elseif event.name == "moved" then
            self:onTouchMoved(cc.p(event.x,event.y))
        elseif event.name == "ended" then
            self:onTouchEnded(cc.p(event.x,event.y))
        end

    end)

end

function UIDrag:getInnerPoint()
    return self._beanPoint
end

function UIDrag:setOnDragUpBeforeEvent(fun)
    self._onDragUpBeforeEvent = fun
end

function UIDrag:setOnDragUpAfterEvent(fun)
    self._onDragUpAfterEvent = fun
end

function UIDrag:setOnDragMoveBeforeEvent(fun)
    self._onDragMoveBeforeEvent = fun
end

function UIDrag:setOnDragMoveEvent(fun)
    self._onDragMoveEvent = fun
end

function UIDrag:setOnDragDownBeforeEvent(fun)
    self._onDragDownBeforeEvent = fun
end

function UIDrag:setOnDragDownAfterEvent(fun)
    self._onDragDownAfterEvent = fun
end

--[[--
@brief  处理拖拽在scrollview里面存在的问题，因为scroll有容器的原因，导致会拖拽到scrollview外，但却在容器内
，此方法用于判定是否真正拖拽了scrollview里面的元素
@param  view UIScrollview  scrollview对象
@return #bool return  是否正常拖拽
static bool Handler_DragUp_ScrollView(ui::ScrollView* view,cocos2d::Touch *t)
@brief  添加一组拖拽项
@param  _dragItems   拖拽项

]]

--[[--
与UIDraw.new的参数同等。此方法用于后期加入拖拽项
@param list {UIDragItem,UIDragItem,UIDragItem} 一组UIDragItem类型数据
]]
function UIDrag:addDragList(list)
    for i = 1,#list do
        self._dragItems[#self._dragItems+1] = list[i]
    end
end

--[[--
清空所有拖拽物和其盒子的绑定
]]
function UIDrag:removeDragAll()
    for i = 1,#(self._dragItems) do
        self._dragItems[i]:setDragObj(nil)
    end
    self._dragItems = {}
    self._hinderList = {}
    self:removeAllChildren()
end

--[[--

根据绑定的盒子查找拖拽项

@param  box Node 绑定的盒子
@return #UIDragItem 拖拽项

]]
function UIDrag:find(box)
    for i = 1,#(self._dragItems) do
        if(self._dragItems[i].dragBox==box)then
            return self._dragItems[i]
        end
    end
    return nil
end


--[[--

添加一个拖拽项，有三种用法

用法一：
@param  item UIDragItem 拖拽项

用法二：
@param item Node 盒子
@param drag Node 拖拽对象
@param group int group分组标记
@param z    int z

用法三:
@param item Node 盒子
@param drag function 返回拖拽对象的方法
@param group int group分组标记
@param z    int z

]]
function UIDrag:addDragItem(item,drag,group,z)
    if item.__cname == "UIDragItem" then
        self._dragItems[#self._dragItems+1] = item
    else
        local item = UIDragItem.new(item,drag)
        if type(group) == "number" then
            item.group = group
        end

        if type(z) == "number" then
            item._z = z
        end
        self._dragItems[#self._dragItems+1] = item
    end
    return self._dragItems[#self._dragItems]
end

--[[--

添加一个拖拽项

@param  box  绑定的盒子 type:Node
@param  drag 拖拽物  type:Node
@param  tag 标记  type:int
@param  z 拖拽物相对于盒子的z值 type:int

]]
--function UIDrag:addDragItemParams(box,drag,tag,z)
--    local item = UIDragItem:create(box,drag)
--    if type(tag) == "number" then
--        item.tag = tag
--    end
--
--    if type(z) == "number" then
--        item._z = z
--    end
--    self._dragItems[#_dragItems+1] = item
--end

--[[--

由于拖拽的要覆盖所有界面ui（一个界面可能有多个不同的ui），所以z是很大的。
有些层级的按钮在拖拽物上面，如果点击按钮会优先进行拖拽，所以以需要把这个按钮注册成遮挡物
这样的话，如果按钮在盒子上面，点击按钮就可以安心的点击了，而不会触发拖拽

@param  hinder  遮挡物 type:Node

]]
function UIDrag:addHinder(hinder)
    self._hinderList[#_hinderList+1] = hinder
end

--[[--
用于处理拖拽在scroll里的内容益处问题
原理上正常拖拽会拖到scroll视图之外的东西(当然视图之外有东西的话)
那么这时就需要做一个判定只需要拖拽视图内的东西。

~~lua
drag:setOnDragUpBeforeEvent(function(currentItem,targetItem,point)
--判定是否真正的触摸到scroll的内部窗体
if drag:handler_ScrollView(self.view,point) then return end
--逻辑内容
end)

@param scroll   UIScrollView对象
@param point    事件触摸坐标
]]
function UIDrag:handler_ScrollView(scroll,point)
    if scroll:getScrollNode():hitTest(point) then
        local rect = scroll:getViewRect()
        local lp = scroll:convertToWorldSpace(cc.p(0,0))
        local temp = cc.rect(lp.x,lp.y,rect.width,rect.height)
        if not cc.rectContainsPoint(temp,point)  then
            return true
        end
    end
    return false
end

function UIDrag:onTouchBegan(point)
    --遮盖物
    for i = 1,#(self._hinderList) do
        if _hinderList[i] and _hinderList[i]:hitTest(point) then
            return false
        end
    end

    for i = 1, #(self._dragItems) do

        repeat

            local item = self._dragItems[i]
            local box = item.dragBox

            --必须点击盒子，且盒子里要有对象
            if box:hitTest(point) and item.dragObj then

                --拖拽时拦截触摸
                self:setTouchSwallowEnabled(true)
                --事件回调，拖拽前
                if not self._onDragUpBeforeEvent(item,point) then
                    break
                end

                --                self._isBean = true
                self._isOnBean = true
                --当前操作项
                self._currentDragItem = item
                --当前拖拽物
                self._currentDragObj = self._currentDragItem.dragObj

                local p = self._currentDragItem.dragBox:convertToWorldSpaceAR(cc.p(0,0))
                --定位到drag坐标
                p = self:convertToNodeSpaceAR(p)
                --描点计算
                if self._currentDragObj:isIgnoreAnchorPointForPosition() then
                    p.x = p.x - W(self._currentDragObj) * AX(self._currentDragObj)
                    p.y = p.y - H(self._currentDragObj) * AY(self._currentDragObj)
                end
                --计算触摸偏差坐标
                local p2 = self:convertToNodeSpace(point)
                self._beanPoint = cc.p(p2.x-p.x, p2.y-p.y)
                
                --拖拽之后
                self._onDragUpAfterEvent(self._currentDragItem,point)
                return true
            end

        until true
    end
    --穿透
    self:setTouchSwallowEnabled(false)
    return false
end

function UIDrag:onTouchMoved(point)
    local dragPoint = self:convertToNodeSpace(point)
    dragPoint = cc.p(dragPoint.x-self._beanPoint.x, dragPoint.y-self._beanPoint.y)

    if  self._isOnBean then
        --拖拽移动之前
        self._onDragMoveBeforeEvent(self._currentDragItem,point)
        --转换容器
        --强引用
        self._isOnBean = false
        self._currentDragObj:retain()
        self._currentDragObj:removeFromParent()
        self:addChild(self._currentDragObj)
        self._currentDragObj:release()
        
        if self.isISOModel then
            --模拟镜像
            self._currentDragObj:setOpacity(150)
            if self._currentDragItem.dragObjFun then
                self._currentDragItem:setDragObj(self._currentDragItem:cloneDragObj())
            end
        end
        self._currentDragObj:setPosition(dragPoint)
    end

    -- _isbean 暂时不用
    --    if self._isBean and self._currentDragItem.dragObj then
    if self._currentDragItem.dragObj then
        self._currentDragObj:setPosition(dragPoint)
        --拖拽移动
        self._onDragMoveEvent(self._currentDragItem,self._currentDragObj,point,dragPoint)
    end
end

function UIDrag:onTouchEnded(point)
    local result = false
    --拖拽的放下前标记
    local isDownbefore = true

    for i = 1 , #(self._dragItems) do

        repeat

            local target = self._dragItems[i]
            local box = target.dragBox

            --如果没有离开当前物品所在框，则视为不做任何操作和回调
            if self._currentDragItem.dragBox:hitTest(point) then

--                self._currentDragObj:retain()
--                self._currentDragObj:removeFromParent()
--                self._currentDragItem:setDragObj(nil)
--                self._currentDragObj:setOpacity(255)
--                self._currentDragItem:setDragObj(self._currentDragObj)
--                self._currentDragObj:release()
--                --                self._isBean = false
--                self._currentDragItem = nil
                break
            --拖拽离开盒子
            elseif  box:hitTest(point) then

                isDownbefore = false
                --拖拽成功之前
                if not self._onDragDownBeforeEvent(self._currentDragItem,target,point) then
                    break
                end

                --目标框必须没有对象存在。注意，如果拖动的地方存在对象是不做交换的。
                if not target.dragObj then
                    self._currentDragObj:retain()
                    --###ios新加
                    self._currentDragObj:removeFromParent()
                    --当前框设置空
                    self._currentDragItem:setDragObj(nil)
                    --目标框存放
                    self._currentDragObj:setOpacity(255)
                    target:setDragObj(self._currentDragObj)
                    self._currentDragObj:release()
                    --镜像模式需要拷贝克隆函数
                    if self.isISOModel then
                        target.dragObjFun = self._currentDragItem.dragObjFun
                    end
                    
                    result = true

                    --拖拽成功之后
                    self._onDragDownAfterEvent(self._currentDragItem,target,point)
                    break
                else
                    --如果目标框对象存在
                    --做交换处理
                    if self.isExchangeModel then
                        --目标拖拽对象暂存
                        local tempTagObj = target.dragObj
                        target.dragObj:retain()
                        target:setDragObj(nil)

                        self._currentDragObj:retain()
                        --当前框设置空
                        self._currentDragObj:removeFromParent()
                        self._currentDragItem:setDragObj(nil)
                        --目标框存放
                        self._currentDragObj:setOpacity(255)
                        target:setDragObj(self._currentDragObj)
                        self._currentDragObj:release()
                        --当前框置放目标框的对象
                        self._currentDragItem:setDragObj(tempTagObj)
                        tempTagObj:release()
                        
                        if self.isISOModel then
                            local fun = target.dragObjFun
                            target.dragObjFun = self._currentDragItem.dragObjFun
                            self._currentDragItem.dragObjFun = fun
                        end

                        result = true

                        --拖拽成功之后
                        self._onDragDownAfterEvent(self._currentDragItem,target,point)
                    else
                    --不做交换处理，注意：默认为不做交换处理
                    end
                end
            end

        until true

    end
    
    if not result then

        --拖拽成功之前
        if isDownbefore then
            self._onDragDownBeforeEvent(self._currentDragItem,nil,point)
        end
        self._currentDragObj:retain()
        self._currentDragObj:removeFromParent()
        self._currentDragItem:setDragObj(nil)
        self._currentDragObj:setOpacity(255)
        self._currentDragItem:setDragObj(self._currentDragObj)
        self._currentDragObj:release()
    end

    --    self._isBean = false
    self._currentDragItem = nil
    self:setTouchSwallowEnabled(false)
end