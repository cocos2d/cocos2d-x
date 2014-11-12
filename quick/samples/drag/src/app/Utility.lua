
---获取大小宽高，或者宽高的一半
--常用代码段，用于返回不需要处理的node , #if not node then return nil end#
--获取大小的方法对于gui也适用。
SIZE = function(node) 
if not node then return nil end 
local size = node:getContentSize()
if size.width == 0 and size.height == 0 then
    local w,h = node:getLayoutSize()
    return cc.size(w,h)
else 
    return size
end
end
W = function(node) if not node then return nil end  return SIZE(node).width; end
W2 = function(node) if not node then return nil end  return W(node)/2;end
H = function(node) if not node then return nil end  return SIZE(node).height; end
H2 = function(node) if not node then return nil end  return H(node)/2;end
S_SIZE = function(node,w,h) if not node then return nil end  return node:setContentSize(cc.size(w,h)); end
S_W = function(node,w) if not node then return nil end  return node:setContentSize(cc.size(w,H(node))); end
S_H = function(node,h) if not node then return nil end  return node:setContentSize(cc.size(W(node),h)); end

---获取坐标及设置坐标
X = function(node) if not node then return nil end  return node:getPositionX(); end
Y = function(node) if not node then return nil end  return node:getPositionY(); end
XY = function(node) if not node then return nil end  return node:getPosition(); end
S_X = function(node,x) if not node then return nil end  node:setPosition(cc.p(x,Y(node))); end
S_Y = function(node,y) if not node then return nil end  node:setPosition(cc.p(X(node),y)); end
S_XY = function(node,x,y) if not node then return nil end  node:setPosition(x,y); end

--居中A显示。A的描点为0,0     set point center
S_XY_C = function(a)
    S_XY(a,W2(a:getParent())-W2(a),H2(a:getParent())-H2(a))
end
--见SET_POINT_CENTER。    set point center
S_XY_C0 = S_P_CENTER
--居中A显示。A的描点为0.5,0.5    set point center
S_XY_C5 = function(a)
    S_XY(a,W2(a:getParent()),H2(a:getParent()))
end

---描点相关方法。
AX = function(node) if not node then return nil end  return node:getAnchorPoint().x; end
AY = function(node) if not node then return nil end  return node:getAnchorPoint().y; end
AXY = function(node) if not node then return nil end  return node:getAnchorPoint(); end
S_AX = function(node,x) if not node then return nil end  node:setAnchorPoint(cc.p(x,AY(node))); end
S_AY = function(node,y) if not node then return nil end  node:setAnchorPoint(cc.p(AX(node),y)); end
S_AXY = function(node,x,y) if not node then return nil end  node:setAnchorPoint(x,y); end

--为node扩展一个判断点击区域的方法,此方法来自 2dx 3.x Widget 方法
function cc.Node:hitTest(point)
    local nsp = self:convertToNodeSpace(point)
    local bb = cc.rect(0,0,W(self),H(self))
    if (cc.rectContainsPoint(bb,nsp)) then
        return true
    end
    return false
end

---按钮事件标记状态，用于标记scroll是否滑动之类的状态。
SCROLL_EVENT_STATUS = 0;
--[[--
处理node之类的在scroll滑动事件的处理，在node是回调里第一行加上，if HANDLER_NODE_IN_SCROLL(event) then return true end。
然后如果scroll滑动，则不会执行回调里的东西，会通过if给true掉。

~~lua用法
house1:addNodeEventListener(cc.NODE_TOUCH_EVENT,function(event)
if NODE_HANDLER_SCROLL_SLIDE(event) then return true end
print(i)
end)

]]
NODE_EVENT_SCROLL_SLIDE = function(event)
    if event.name ~= "ended" or (event.name == "ended" and SCROLL_EVENT_STATUS == -1) then
        --        SCROLL_EVENT_STATUS = 0;
        return true;
    end
end
--[[--
解决scroll滑动和里面node事件的兼容性，只需在scroll回调里上HANDLER_SCROLL_IN_EVENT(event)即可。

~~lua用法
function BodyScene_1:scrollListener(event)
--在scroll事件里调用这个方法才行。
SCROLL_HANDLER_SLIDE(event)
end

]]
SCROLL_EVENT_SLIDE =  function(event)
    if event.name == "began" then
        return true
    elseif event.name == "moved" then SCROLL_EVENT_STATUS = -1
    elseif event.name == "ended" then SCROLL_EVENT_STATUS = 0 end
end

---这个方法用于扩展node对象在scroll里接收事件的情况
function cc.Node:addEventInScroll(fun)
    self:addNodeEventListener(cc.NODE_TOUCH_EVENT,function(event)
        if NODE_EVENT_SCROLL_SLIDE(event) then return true end
        fun(event)
    end)
end

---为node注册一个点击事件
function cc.Node:addOnClick(fun)
    self:addNodeEventListener(cc.NODE_TOUCH_EVENT,function(event)
        if event.name == "began" then
            return true
        elseif event.name == "ended" then
            if self:hitTest(cc.p(event.x,event.y)) then
                fun(event)
            end
        end
    end)
end

---增加处理滚动事件的处理
SCROLL_HANDLER_SLIDE = function(scvollView)
    scvollView.scrollListener_ = SCROLL_EVENT_SLIDE
end

---多参数的继承用法,把param2的参数增加覆盖到param1中。
EXTEND = function(param1,param2)
    if not param2 then
        return param1;
    end
    for k , v in pairs(param2) do
        param1[k] = param2[k];
    end
    return param1;
end

---三元运算符
CALC_3 = function(exp, result1, result2) if(exp==true)then return result1; else return result2; end end
