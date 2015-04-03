local NodeInRect = class("NodeInRect")
NodeInRect._tag  = -1
NodeInRect._origin = nil
NodeInRect._size   = nil

function NodeInRect:ctor()
    self._tag = -1
    self._origin = nil
    self._size   = nil
    self._origin = cc.p(0, 0)
    self._size   = cc.size(0, 0)
end

function NodeInRect:init()
    return true
end

function NodeInRect:detect()
    local node = ccs.SceneReader:getInstance():getNodeByTag(self._tag)
    if nil ~= node and math.abs(node:getPositionX() - self._origin.x) <= self._size.width and math.abs(node:getPositionY() - self._origin.y) <= self._size.height then
        return true
    end

    return false
end

function NodeInRect:serialize(value)
    local dataItems = value["dataitems"]
    if nil ~= dataItems then
        local count = table.getn(dataItems)
        for i = 1, count do
            local subDict =  dataItems[i]
            local key = subDict["key"]
            if key == "Tag" then
                self._tag = subDict["value"]
            elseif key == "originX" then
                self._origin.x = subDict["value"]
            elseif key == "originY" then
                self._origin.y = subDict["value"]
            elseif key == "sizeWidth" then
                self._size.width = subDict["value"]
            elseif key == "sizeHeight" then
                self._size.height = subDict["value"]
            end
        end
    end
end

function NodeInRect:removeAll()
    print("NodeInRect::removeAll")
end

ccs.registerTriggerClass("NodeInRect",NodeInRect.new)
