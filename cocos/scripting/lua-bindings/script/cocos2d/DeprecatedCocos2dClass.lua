-- This is the DeprecatedClass

DeprecatedClass = {} or DeprecatedClass

--tip
local function deprecatedTip(old_name,new_name)
    print("\n********** \n"..old_name.." was deprecated please use ".. new_name .. " instead.\n**********")
end

--NodeRGBA class will be Deprecated,begin
function DeprecatedClass.NodeRGBA()
    deprecatedTip("cc.NodeRGBA","cc.Node")
    return cc.Node
end
_G["cc"]["NodeRGBA"] = DeprecatedClass.NodeRGBA()
--NodeRGBA class will be Deprecated,end


--LayerRGBA class will be Deprecated,begin
function DeprecatedClass.LayerRGBA()
    deprecatedTip("cc.LayerRGBA","cc.Layer")
    return cc.Layer
end
_G["cc"]["LayerRGBA"] = DeprecatedClass.LayerRGBA()
--LayerRGBA class will be Deprecated,end


--EGLViewProtocol class will be Deprecated,begin
function DeprecatedClass.EGLViewProtocol()
    deprecatedTip("cc.EGLViewProtocol","cc.GLViewProtocol")
    return cc.GLViewProtocol
end
_G["cc.EGLViewProtocol"] = DeprecatedClass.EGLViewProtocol()
--EGLViewProtocol class will be Deprecated,end

--EGLView class will be Deprecated,begin
function DeprecatedClass.EGLView()
    deprecatedTip("cc.EGLView","cc.GLView")
    return cc.GLView
end
_G["cc.EGLView"] = DeprecatedClass.EGLView()
--EGLView  class will be Deprecated,end

--EGLView class will be Deprecated,begin
function DeprecatedClass.EGLView()
    deprecatedTip("cc.EGLView","cc.GLView")
    return cc.GLView
end
_G["cc.EGLView"] = DeprecatedClass.EGLView()
--EGLView  class will be Deprecated,end

--ShaderCache class will be Deprecated,begin
function DeprecatedClass.ShaderCache()
    deprecatedTip("cc.ShaderCache","cc.GLProgramCache")
    return cc.GLProgramCache
end
cc.ShaderCache = DeprecatedClass.ShaderCache()
--ShaderCache  class will be Deprecated,end



