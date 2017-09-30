function findChild(node, childName, type)
    local target = node:getChildByName(childName)
    if target ~= nil then
    	return tolua.cast(target, type)
    end

    local children = node:getChildren()
    for i = 1, #children do
    	local child = children[i]
    	local result = findChild(child, childName, type)
    	if result ~= nil then
    		return tolua.cast(result, type)
    	end
    end

    return nil
end