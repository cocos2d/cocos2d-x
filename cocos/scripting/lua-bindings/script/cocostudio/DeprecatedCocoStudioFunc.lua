if nil == ccs then
    return
end

--tip
local function deprecatedTip(old_name,new_name)
    print("\n********** \n"..old_name.." was deprecated please use ".. new_name .. " instead.\n**********")
end


--functions of ccs.GUIReader will be deprecated begin
local CCSGUIReaderDeprecated = { }
function CCSGUIReaderDeprecated.purgeGUIReader()
    deprecatedTip("ccs.GUIReader:purgeGUIReader","ccs.GUIReader:destroyInstance")
    return ccs.GUIReader:destroyInstance()
end
ccs.GUIReader.purgeGUIReader = CCSGUIReaderDeprecated.purgeGUIReader
--functions of ccs.GUIReader will be deprecated end
