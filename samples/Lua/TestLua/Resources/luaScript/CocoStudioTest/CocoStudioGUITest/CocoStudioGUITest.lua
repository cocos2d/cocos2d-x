local cocoStudioGuiArray = 
{
    {
        title = "UIButtonTest",
        func  = function () 
            --return new UIButtonTest()
            print("come in UIButtonTest")
            return cc.Scene:create()
        end
    },
    {
        title = "UIButtonTest_Scale9",
        func = function () 
            --return new UIButtonTest_Scale9();
        end
    },
    -- {
    --     title: "UIButtonTest_PressedAction",
    --     -- func: function () {
    --     --     return new UIButtonTest_PressedAction();
    --     -- }
    -- },
    -- {
    --     title: "UITextButtonTest",
    --     -- func: function () {
    --     --     return new UITextButtonTest();
    --     -- }
    -- },
    -- {
    --     title: "UITextButtonTest_Scale9",
    --     -- func: function () {
    --     --     return new UITextButtonTest_Scale9();
    --     -- }
    -- },
    -- {
    --     title: "UICheckBoxTest",
    --     -- func: function () {
    --     --     return new UICheckBoxTest();
    --     -- }
    -- },
    -- {
    --     title: "UISliderTest",
    --     -- func: function () {
    --     --     return new UISliderTest();
    --     -- }
    -- },
    -- {
    --     title: "UIButtonTest",
    --     -- func: function () {
    --     --     return new UISliderTest_Scale9();
    --     -- }
    -- },
    -- {
    --     title: "UIImageViewTest",
    --     -- func: function () {
    --     --     return new UIImageViewTest();
    --     -- }
    -- },
    -- {
    --     title: "UIImageViewTest_Scale9",
    --     -- func: function () {
    --     --     return new UIImageViewTest_Scale9();
    --     -- }
    -- },
    -- {
    --     title: "UILoadingBarTest_Left",
    --     -- func: function () {
    --     --     return new UILoadingBarTest_Left();
    --     -- }
    -- },
    -- {
    --     title: "UILoadingBarTest_Right",
    --     -- func: function () {
    --     --     return new UILoadingBarTest_Right();
    --     -- }
    -- },
    -- {
    --     title: "UILoadingBarTest_Left_Scale9",
    --     -- func: function () {
    --     --     return new UILoadingBarTest_Left_Scale9();
    --     -- }
    -- },
    -- {
    --     title: "UILoadingBarTest_Right_Scale9",
    --     -- func: function () {
    --     --     return new UILoadingBarTest_Right_Scale9();
    --     -- }
    -- },
    -- {
    --     title: "UILabelAtlasTest",
    --     -- func: function () {
    --     --     return new UILabelAtlasTest();
    --     -- }
    -- },
    -- {
    --     title: "UILabelTest",
    --     -- func: function () {
    --     --     return new UILabelTest();
    --     -- }
    -- },
    -- {
    --     title: "UITextAreaTest",
    --     -- func: function () {
    --     --     return new UITextAreaTest();
    --     -- }
    -- },
    -- {
    --     title: "UILabelBMFontTest",
    --     -- func: function () {
    --     --     return new UILabelBMFontTest();
    --     -- }
    -- },
    -- {
    --     title: "UITextFieldTest",
    --     -- func: function () {
    --     --     return new UITextFieldTest();
    --     -- }
    -- },
    -- {
    --     title: "UITextFieldTest_MaxLength",
    --     -- func: function () {
    --     --     return new UITextFieldTest_MaxLength();
    --     -- }
    -- },
    -- {
    --     title: "UITextFieldTest_Password",
    --     -- func: function () {
    --     --     return new UITextFieldTest_Password();
    --     -- }
    -- },
    -- {
    --     title: "UIPanelTest",
    --     -- func: function () {
    --     --     return new UIPanelTest();
    --     -- }
    -- },
    -- {         title: "UIPanelTest_Color", 
    --     -- func: function () {
    --     -- return new UIPanelTest_Color();
    --     -- }
    -- },
    -- {
    --     title: "UIPanelTest_Gradient", 
    --     -- func: function () {
    --     -- return new UIPanelTest_Gradient();
    --     -- }
    -- },
    -- {
    --     title: "UIPanelTest_BackGroundImage",
    --     -- func: function () {
    --     --     return new UIPanelTest_BackGroundImage();
    --     -- }
    -- },
    -- {
    --     title: "UIPanelTest_BackGroundImage_Scale9",
    --     -- func: function () {
    --     --     return new UIPanelTest_BackGroundImage_Scale9();
    --     -- }
    -- },
    -- {
    --     title: "UIPanelTest_Layout_Linear_Vertical",
    --     -- func: function () {
    --     --     return new UIPanelTest_Layout_Linear_Vertical();
    --     -- }
    -- },
    -- {
    --     title: "UIPanelTest_Layout_Linear_Horizontal",
    --     -- func: function () {
    --     --     return new UIPanelTest_Layout_Linear_Horizontal();
    --     -- }
    -- },
    -- {
    --     title: "UIScrollViewTest_Vertical",
    --     -- func: function () {
    --     --     return new UIScrollViewTest_Vertical();
    --     -- }
    -- },
    -- {
    --     title: "UIScrollViewTest_Horizontal",
    --     -- func: function () {
    --     --     return new UIScrollViewTest_Horizontal();
    --     -- }
    -- },
    -- {
    --     title: "UIPageViewTest",
    --     -- func: function () {
    --     --     return new UIPageViewTest();
    --     -- }
    -- },
    -- {
    --     title: "UIListViewTest_Vertical",
    --     -- func: function () {
    --     --     return new UIListViewTest_Vertical();
    --     -- }
    -- },
    -- {
    --     title: "UIListViewTest_Horizontal",
    --     -- func: function () {
    --     --     return new UIListViewTest_Horizontal();
    --     -- }
    -- },
    -- {
    --     title: "UIDragPanelTest",
    --     -- func: function () {
    --     --     return new UIDragPanelTest();
    --     -- }
    -- },
    -- {
    --     title: "UIDragPanelTest_Bounce",
    --     -- func: function () {
    --     --     return new UIDragPanelTest_Bounce();
    --     -- }
    -- },
    -- {
    --     title: "UINodeContainerTest",
    --     -- func: function () {
    --     --     return new UINodeContainerTest();
    --     -- }
    -- }
}

guiSceneManager = guiSceneManager or {}
guiSceneManager.currentUISceneIdx = 1

function guiSceneManager.nextUIScene()
    guiSceneManager.currentUISceneIdx = (guiSceneManager.currentUISceneIdx + 1) % table.getn(cocoStudioGuiArray)
    if 1 == guiSceneManager.currentUISceneIdx  then
        guiSceneManager.currentUISceneIdx  = table.getn(cocoStudioGuiArray)
    end

    return cocoStudioGuiArray[guiSceneManager.currentUISceneIdx].func()
end

function guiSceneManager.previousUIScene()

    guiSceneManager.currentUISceneIdx = guiSceneManager.currentUISceneIdx - 1
    if guiSceneManager.currentUISceneIdx <= 0 then
        guiSceneManager.currentUISceneIdx = guiSceneManager.currentUISceneIdx + table.getn(cocoStudioGuiArray)
    end

    return cocoStudioGuiArray[guiSceneManager.currentUISceneIdx].func()
end

function guiSceneManager.currentUIScene()
    return cocoStudioGuiArray[guiSceneManager.currentUISceneIdx].func()
end

function guiSceneManager:getInstance()  
    local gsMgr = _G.guiSceneManager  
    if gsMgr then return gsMgr end  
      
    gsMgr = {}  
    _G.guiSceneManager = gsMgr  
    setmetatable(o, self)  
    self.__index = self  
    return gsMgr  
end  
  
function guiSceneManager:purge()  
    _G.guiSceneManager = nil  
end

function runCocosGUITestScene()
   local scene = guiSceneManager:getInstance().currentUIScene()
   cc.Director:getInstance():replaceScene(scene)
end
