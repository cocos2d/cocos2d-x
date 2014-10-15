-- This is the DeprecatedExtensionClass

DeprecatedExtensionClass = {} or DeprecatedExtensionClass

--tip
local function deprecatedTip(old_name,new_name)
    print("\n********** \n"..old_name.." was deprecated please use ".. new_name .. " instead.\n**********")
end

--CCArmature class will be Deprecated,begin
function DeprecatedExtensionClass.CCArmature()
    deprecatedTip("CCArmature","ccs.Armature")
    return ccs.Armature
end
_G["CCArmature"] = DeprecatedExtensionClass.CCArmature()
--CCArmature class will be Deprecated,end

--CCArmatureAnimation class will be Deprecated,begin
function DeprecatedExtensionClass.CCArmatureAnimation()
    deprecatedTip("CCArmatureAnimation","ccs.ArmatureAnimation")
    return ccs.ArmatureAnimation
end
_G["CCArmatureAnimation"] = DeprecatedExtensionClass.CCArmatureAnimation()
--CCArmatureAnimation class will be Deprecated,end

--CCSkin class will be Deprecated,begin
function DeprecatedExtensionClass.CCSkin()
    deprecatedTip("CCSkin","ccs.Skin")
    return ccs.Skin
end
_G["CCSkin"] = DeprecatedExtensionClass.CCSkin()
--CCSkin class will be Deprecated,end

--CCBone class will be Deprecated,begin
function DeprecatedExtensionClass.CCBone()
    deprecatedTip("CCBone","ccs.Bone")
    return ccs.Bone
end
_G["CCBone"] = DeprecatedExtensionClass.CCBone()
--CCBone class will be Deprecated,end

--CCArmatureDataManager class will be Deprecated,begin
function DeprecatedExtensionClass.CCArmatureDataManager()
    deprecatedTip("CCArmatureDataManager","ccs.ArmatureDataManager")
    return ccs.ArmatureDataManager
end
_G["CCArmatureDataManager"] = DeprecatedExtensionClass.CCArmatureDataManager()
--CCArmatureDataManager class will be Deprecated,end

--CCBatchNode class will be Deprecated,begin
function DeprecatedExtensionClass.CCBatchNode()
    deprecatedTip("CCBatchNode","ccs.BatchNode")
    return ccs.BatchNode
end
_G["CCBatchNode"] = DeprecatedExtensionClass.CCBatchNode()
--CCBatchNode class will be Deprecated,end

--CCTween class will be Deprecated,begin
function DeprecatedExtensionClass.CCTween()
    deprecatedTip("CCTween","ccs.Tween")
    return ccs.Tween
end
_G["CCTween"] = DeprecatedExtensionClass.CCTween()
--CCTween class will be Deprecated,end

--CCBaseData class will be Deprecated,begin
function DeprecatedExtensionClass.CCBaseData()
    deprecatedTip("CCBaseData","ccs.BaseData")
    return ccs.BaseData
end
_G["CCBaseData"] = DeprecatedExtensionClass.CCBaseData()
--CCBaseData class will be Deprecated,end

--CCDisplayManager class will be Deprecated,begin
function DeprecatedExtensionClass.CCDisplayManager()
    deprecatedTip("CCDisplayManager","ccs.DisplayManager")
    return ccs.DisplayManager
end
_G["CCDisplayManager"] = DeprecatedExtensionClass.CCDisplayManager()
--CCDisplayManager class will be Deprecated,end

--UIHelper class will be Deprecated,begin
function DeprecatedExtensionClass.UIHelper()
    deprecatedTip("UIHelper","ccs.UIHelper")
    return ccs.UIHelper
end
_G["UIHelper"] = DeprecatedExtensionClass.UIHelper()
--UIHelper class will be Deprecated,end

--UILayout class will be Deprecated,begin
function DeprecatedExtensionClass.UILayout()
    deprecatedTip("UILayout","ccs.UILayout")
    return ccs.UILayout
end
_G["UILayout"] = DeprecatedExtensionClass.UILayout()
--UILayout class will be Deprecated,end

--UIWidget class will be Deprecated,begin
function DeprecatedExtensionClass.UIWidget()
    deprecatedTip("UIWidget","ccs.UIWidget")
    return ccs.UIWidget
end
_G["UIWidget"] = DeprecatedExtensionClass.UIWidget()
--UIWidget class will be Deprecated,end

--UILayer class will be Deprecated,begin
function DeprecatedExtensionClass.UILayer()
    deprecatedTip("UILayer","ccs.UILayer")
    return ccs.UILayer
end
_G["UILayer"] = DeprecatedExtensionClass.UILayer()
--UILayer class will be Deprecated,end

--UIButton class will be Deprecated,begin
function DeprecatedExtensionClass.UIButton()
    deprecatedTip("UIButton","ccs.UIButton")
    return ccs.UIButton
end
_G["UIButton"] = DeprecatedExtensionClass.UIButton()
--UIButton class will be Deprecated,end

--UICheckBox class will be Deprecated,begin
function DeprecatedExtensionClass.UICheckBox()
    deprecatedTip("UICheckBox","ccs.UICheckBox")
    return ccs.UICheckBox
end
_G["UICheckBox"] = DeprecatedExtensionClass.UICheckBox()
--UICheckBox class will be Deprecated,end

--UIImageView class will be Deprecated,begin
function DeprecatedExtensionClass.UIImageView()
    deprecatedTip("UIImageView","ccs.UIImageView")
    return ccs.UIImageView
end
_G["UIImageView"] = DeprecatedExtensionClass.UIImageView()
--UIImageView class will be Deprecated,end

--UILabel class will be Deprecated,begin
function DeprecatedExtensionClass.UILabel()
    deprecatedTip("UILabel","ccs.UILabel")
    return ccs.UILabel
end
_G["UILabel"] = DeprecatedExtensionClass.UILabel()
--UILabel class will be Deprecated,end

--UILabelAtlas class will be Deprecated,begin
function DeprecatedExtensionClass.UILabelAtlas()
    deprecatedTip("UILabelAtlas","ccs.UILabelAtlas")
    return ccs.UILabelAtlas
end
_G["UILabelAtlas"] = DeprecatedExtensionClass.UILabelAtlas()
--UILabelAtlas class will be Deprecated,end

--UILabelBMFont class will be Deprecated,begin
function DeprecatedExtensionClass.UILabelBMFont()
    deprecatedTip("UILabelBMFont","ccs.UILabelBMFont")
    return ccs.UILabelBMFont
end
_G["UILabelBMFont"] = DeprecatedExtensionClass.UILabelBMFont()
--UILabelBMFont class will be Deprecated,end

--UILoadingBar class will be Deprecated,begin
function DeprecatedExtensionClass.UILoadingBar()
    deprecatedTip("UILoadingBar","ccs.UILoadingBar")
    return ccs.UILoadingBar
end
_G["UILoadingBar"] = DeprecatedExtensionClass.UILoadingBar()
--UILoadingBar class will be Deprecated,end

--UISlider class will be Deprecated,begin
function DeprecatedExtensionClass.UISlider()
    deprecatedTip("UISlider","ccs.UISlider")
    return ccs.UISlider
end
_G["UISlider"] = DeprecatedExtensionClass.UISlider()
--UISlider class will be Deprecated,end

--UITextField class will be Deprecated,begin
function DeprecatedExtensionClass.UITextField()
    deprecatedTip("UITextField","ccs.UITextField")
    return ccs.UITextField
end
_G["UITextField"] = DeprecatedExtensionClass.UITextField()
--UITextField class will be Deprecated,end

--UIScrollView class will be Deprecated,begin
function DeprecatedExtensionClass.UIScrollView()
    deprecatedTip("UIScrollView","ccs.UIScrollView")
    return ccs.UIScrollView
end
_G["UIScrollView"] = DeprecatedExtensionClass.UIScrollView()
--UIScrollView class will be Deprecated,end

--UIPageView class will be Deprecated,begin
function DeprecatedExtensionClass.UIPageView()
    deprecatedTip("UIPageView","ccs.UIPageView")
    return ccs.UIPageView
end
_G["UIPageView"] = DeprecatedExtensionClass.UIPageView()
--UIPageView class will be Deprecated,end

--UIListView class will be Deprecated,begin
function DeprecatedExtensionClass.UIListView()
    deprecatedTip("UIListView","ccs.UIListView")
    return ccs.UIListView
end
_G["UIListView"] = DeprecatedExtensionClass.UIListView()
--UIListView class will be Deprecated,end

--UILayoutParameter class will be Deprecated,begin
function DeprecatedExtensionClass.UILayoutParameter()
    deprecatedTip("UILayoutParameter","ccs.UILayoutParameter")
    return ccs.UILayoutParameter
end
_G["UILayoutParameter"] = DeprecatedExtensionClass.UILayoutParameter()
--UILayoutParameter class will be Deprecated,end

--UILinearLayoutParameter class will be Deprecated,begin
function DeprecatedExtensionClass.UILinearLayoutParameter()
    deprecatedTip("UILinearLayoutParameter","ccs.UILinearLayoutParameter")
    return ccs.UILinearLayoutParameter
end
_G["UILinearLayoutParameter"] = DeprecatedExtensionClass.UILinearLayoutParameter()
--UILinearLayoutParameter class will be Deprecated,end

--UIRelativeLayoutParameter class will be Deprecated,begin
function DeprecatedExtensionClass.UIRelativeLayoutParameter()
    deprecatedTip("UIRelativeLayoutParameter","ccs.UIRelativeLayoutParameter")
    return ccs.UIRelativeLayoutParameter
end
_G["UIRelativeLayoutParameter"] = DeprecatedExtensionClass.UIRelativeLayoutParameter()
--UIRelativeLayoutParameter class will be Deprecated,end

--CCComController class will be Deprecated,begin
function DeprecatedExtensionClass.CCComController()
    deprecatedTip("CCComController","ccs.ComController")
    return ccs.CCComController
end
_G["CCComController"] = DeprecatedExtensionClass.CCComController()
--CCComController class will be Deprecated,end

--CCComAudio class will be Deprecated,begin
function DeprecatedExtensionClass.CCComAudio()
    deprecatedTip("CCComAudio","ccs.ComAudio")
    return ccs.ComAudio
end
_G["CCComAudio"] = DeprecatedExtensionClass.CCComAudio()
--CCComAudio class will be Deprecated,end

--CCComAttribute class will be Deprecated,begin
function DeprecatedExtensionClass.CCComAttribute()
    deprecatedTip("CCComAttribute","ccs.ComAttribute")
    return ccs.ComAttribute
end
_G["CCComAttribute"] = DeprecatedExtensionClass.CCComAttribute()
--CCComAttribute class will be Deprecated,end

--CCComRender class will be Deprecated,begin
function DeprecatedExtensionClass.CCComRender()
    deprecatedTip("CCComRender","ccs.ComRender")
    return ccs.ComRender
end
_G["CCComRender"] = DeprecatedExtensionClass.CCComRender()
--CCComRender class will be Deprecated,end

--ActionManager class will be Deprecated,begin
function DeprecatedExtensionClass.ActionManager()
    deprecatedTip("ActionManager","ccs.ActionManagerEx")
    return ccs.ActionManagerEx
end
_G["ActionManager"] = DeprecatedExtensionClass.ActionManager()
--CCComRender class will be Deprecated,end

--SceneReader class will be Deprecated,begin
function DeprecatedExtensionClass.SceneReader()
    deprecatedTip("SceneReader","ccs.SceneReader")
    return ccs.SceneReader
end
_G["SceneReader"] = DeprecatedExtensionClass.SceneReader()
--SceneReader class will be Deprecated,end

--GUIReader class will be Deprecated,begin
function DeprecatedExtensionClass.GUIReader()
    deprecatedTip("GUIReader","ccs.GUIReader")
    return ccs.GUIReader
end
_G["GUIReader"] = DeprecatedExtensionClass.GUIReader()
--GUIReader class will be Deprecated,end

--UIRootWidget class will be Deprecated,begin
function DeprecatedExtensionClass.UIRootWidget()
    deprecatedTip("UIRootWidget","ccs.UIRootWidget")
    return ccs.UIRootWidget
end
_G["UIRootWidget"] = DeprecatedExtensionClass.UIRootWidget()
--UIRootWidget class will be Deprecated,end

--ActionObject class will be Deprecated,begin
function DeprecatedExtensionClass.ActionObject()
    deprecatedTip("ActionObject","ccs.ActionObject")
    return ccs.ActionObject
end
_G["ActionObject"] = DeprecatedExtensionClass.ActionObject()
--ActionObject class will be Deprecated,end