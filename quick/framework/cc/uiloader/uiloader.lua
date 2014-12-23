
--[[

Copyright (c) 2011-2014 chukong-inc.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

]]

--------------------------------
-- @module uiloader

--[[--

初始化 cc.uiloader,并提供对外统一接口

cc.uiloader 可以将CCS导出的json文件用quick的纯lua控件构建出UI布局

]]

local UILoaderUtilitys = import(".UILoaderUtilitys")
local uiloader = class("uiloader")
local CCSUILoader = import(".CCSUILoader")
local CCSSceneLoader = import(".CCSSceneLoader")

-- start --

--------------------------------
-- 初始化 cc.uiloader,并提供对外统一接口
-- @function [parent=#uiloader] new

-- end --

function uiloader:ctor()
end

-- start --

--------------------------------
-- 解析json文件
-- @function [parent=#uiloader] load
-- @param string jsonFile 要解析的json文件
-- @param table params 解析参数
-- @return node#node  解析后的布局

-- end --

function uiloader:load(jsonFile, params)
	local json
	if not params or not params.bJsonStruct then
		local pathInfo = io.pathinfo(jsonFile)
		if ".csb" == pathInfo.extname then
			return cc.CSLoader:getInstance():createNodeWithFlatBuffersFile(jsonFile)
		else
			json = self:loadFile_(jsonFile)
		end
	else
		json = jsonFile
	end
	if not json then
		print("uiloader - load file fail:" .. jsonFile)
		return
	end

	local node

	if self:isScene_(json) then
		node, w, h = CCSSceneLoader:load(json, params)
	else
		node, w, h = CCSUILoader:load(json, params)
	end

	UILoaderUtilitys.clearPath()

	return node, w, h
end

-- start --

--------------------------------
-- 按tag查找布局中的结点
-- @function [parent=#uiloader] seekNodeByTag
-- @param node parent 要查找布局的结点
-- @param number tag 要查找的tag
-- @return node#node 

-- end --

function uiloader:seekNodeByTag(parent, tag)
	if not parent then
		return
	end

	if tag == parent:getTag() then
		return parent
	end

	local findNode
	local children = parent:getChildren()
	local childCount = parent:getChildrenCount()
	if childCount < 1 then
		return
	end
	for i=1, childCount do
		if "table" == type(children) then
			parent = children[i]
		elseif "userdata" == type(children) then
			parent = children:objectAtIndex(i - 1)
		end

		if parent then
			findNode = self:seekNodeByTag(parent, tag)
			if findNode then
				return findNode
			end
		end
	end

	return
end

-- start --

--------------------------------
-- 按name查找布局中的结点
-- @function [parent=#uiloader] seekNodeByName
-- @param node parent 要查找布局的结点
-- @param string name 要查找的name
-- @return node#node 

-- end --

function uiloader:seekNodeByName(parent, name)
	if not parent then
		return
	end

	if name == parent.name then
		return parent
	end

	local findNode
	local children = parent:getChildren()
	local childCount = parent:getChildrenCount()
	if childCount < 1 then
		return
	end
	for i=1, childCount do
		if "table" == type(children) then
			parent = children[i]
		elseif "userdata" == type(children) then
			parent = children:objectAtIndex(i - 1)
		end

		if parent then
			if name == parent.name then
				return parent
			end
		end
	end

	for i=1, childCount do
		if "table" == type(children) then
			parent = children[i]
		elseif "userdata" == type(children) then
			parent = children:objectAtIndex(i - 1)
		end

		if parent then
			findNode = self:seekNodeByName(parent, name)
			if findNode then
				return findNode
			end
		end
	end

	return
end

-- start --

--------------------------------
-- 按name查找布局中的结点
-- 与seekNodeByName不同之处在于它是通过node的下子结点表来查询,效率更快
-- @function [parent=#uiloader] seekNodeByNameFast
-- @param node parent 要查找布局的结点
-- @param string name 要查找的name
-- @return node#node 

-- end --

function uiloader:seekNodeByNameFast(parent, name)
	if not parent then
		return
	end

	if not parent.subChildren then
		return
	end

	if name == parent.name then
		return parent
	end

	local findNode = parent.subChildren[name]
	if findNode then
		-- find
		return findNode
	end

	for i,v in ipairs(parent.subChildren) do
		findNode = self:seekNodeByName(v, name)
		if findNode then
			return findNode
		end
	end

	return
end

-- start --

--------------------------------
-- 根据路径来查找布局中的结点
-- @function [parent=#uiloader] seekNodeByPath
-- @param node parent 要查找布局的结点
-- @param string path 要查找的path
-- @return node#node 

-- end --

function uiloader:seekNodeByPath(parent, path)
	if not parent then
		return
	end

	local names = string.split(path, '/')

	for i,v in ipairs(names) do
		parent = self:seekNodeByNameFast(parent, v)
		if not parent then
			return
		end
	end

	return parent
end

-- start --

--------------------------------
-- 查找布局中的组件结点
-- @function [parent=#uiloader] seekComponents
-- @param node parent 要查找布局的结点
-- @param string nodeName 要查找的name
-- @param number componentIdx 在查找组件在它的直接父结点的位置
-- @return node#node 


--[[--

查找布局中的组件结点

~~~ lua

-- "hero" 是结点名称
-- 1 是 "hero"这个结点下的第一个组件
local hero = cc.uiloader:seekComponents(parentNode, "hero", 1)

~~~

]]
-- end --

function uiloader:seekComponents(parent, nodeName, componentIdx)
	local node = self:seekNodeByName(parent, nodeName)
	if not node then
		return
	end
	node = self:seekNodeByName(node, "Component" .. componentIdx)
	return node
end






-- private
function uiloader:loadFile_(jsonFile)
	local fileUtil = cc.FileUtils:getInstance()
	local fullPath = fileUtil:fullPathForFilename(jsonFile)

	local pathinfo  = io.pathinfo(fullPath)
	UILoaderUtilitys.addSearchPathIf(pathinfo.dirname)

	local jsonStr = fileUtil:getStringFromFile(fullPath)
	local jsonVal = json.decode(jsonStr)

	return jsonVal
end

function uiloader:isScene_(json)
	if json.components then
		return true
	else
		return false
	end
end

return uiloader
