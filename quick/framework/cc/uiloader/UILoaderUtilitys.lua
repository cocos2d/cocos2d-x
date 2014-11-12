
local UILoaderUtilitys = {}

function UILoaderUtilitys.loadTexture(plist, png)
	if UILoaderUtilitys.isNil(plist) then
		return
	end

	local fileUtil
	fileUtil = cc.FileUtils:getInstance()
	local fullPath = fileUtil:fullPathForFilename(plist)
	local fullPng = fileUtil:fullPathForFilename(png)
	-- UILoaderUtilitys.addSearchPathIf(io.pathinfo(fullPath).dirname, fileUtil)
	local spCache
	spCache = cc.SpriteFrameCache:getInstance()
	-- print("UILoaderUtilitys - loadTexture plist:" .. plist)
	if png then
		spCache:addSpriteFrames(fullPath, fullPng)
	else
		spCache:addSpriteFrames(fullPath)
	end
end

function UILoaderUtilitys.isNil(str)
	if not str or 0 == string.utf8len(str) then
		return true
	else
		return false
	end
end

function UILoaderUtilitys.addSearchPathIf(dir, fileUtil)
	if not UILoaderUtilitys.searchDirs then
		UILoaderUtilitys.searchDirs = {}
	end

	if not UILoaderUtilitys.isSearchExist(dir) then
		table.insert(UILoaderUtilitys.searchDirs, dir)
		if not fileUtil then
			fileUtil = cc.FileUtils:getInstance()
		end
		fileUtil:addSearchPath(dir)
	end
end

function UILoaderUtilitys.isSearchExist(dir)
	local bExist = false
	for i,v in ipairs(UILoaderUtilitys.searchDirs) do
		if v == dir then
			bExist = true
			break
		end
	end

	return bExist
end

function UILoaderUtilitys.clearPath(fileUtil)
	if not UILoaderUtilitys.searchDirs then
		return
	end

	fileUtil = fileUtil or cc.FileUtils:getInstance()
	local paths = fileUtil:getSearchPaths()
	local removeIdxTabel

	local luaSearchCount = #UILoaderUtilitys.searchDirs

	for i=luaSearchCount, 1, -1 do
		for key, path in ipairs(paths) do
			if path == UILoaderUtilitys.searchDirs[i] then
				table.remove(paths, key)
				break
			end
		end
		table.remove(UILoaderUtilitys.searchDirs, i)
	end

	paths = table.unique(paths, true)

	fileUtil:setSearchPaths(paths)
end

function UILoaderUtilitys.getFileFullName(filename)
	local fileUtil = fileUtil or cc.FileUtils:getInstance()

	return fileUtil:fullPathForFilename(filename)
end

return UILoaderUtilitys

