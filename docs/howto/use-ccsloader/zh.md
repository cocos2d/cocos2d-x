

CCSLoader 用法说明
================

CCSLoader 是 quick 中的一个功能库。

CCSLoader 读取 Cocos Studio 输出的场景和 UI 布局 JSON 文件，并用 quick 自带的 Lua UI 控件渲染出来。

相比使用 Cocos Studio C++ UI 控件来渲染，使用 quick 自带的 Lua UI 控件有以下好处：

-   由于只使用了标准的 Node 和 Sprite 等对象，渲染效率更高
-   支持 quick 的三阶段触摸事件机制
-   Lua UI 控件更容易理解和扩展



## 基本用法

解析 JSON 文件并显示：

~~~lua

local node = cc.uiloader:load("test.ExportJson")

-- 解析成功后，会返回场景/UI的根节点，将其加入场景即可显示
if node then
    node:setPosition(0, 0)
    scene:addChild(node)
end

~~~



按名字查找节点：

~~~lua

local node = cc.uiloader:load("test.ExportJson")

-- 假设布局中有一个名字为 "DragPanel" 的滚动控件
-- seekNodeByName() 从成功加载的根节点中查找指定名字的节点
local scrollView = cc.uiloader:seekNodeByName(node, "DragPanel")

-- 滚动控件在 Lua UI 中的类型是 cc.ui.UIScrollView
-- 在 scrollView 上注册滚动回调事件
scrollView:onScroll(function(event)
    print("CCSSample3Scene scroll")
end)

~~~



按名字顺序查找节点：

~~~lua

local node = cc.uiloader:load("test.ExportJson")

-- seekComponents() 可以查找同名节点中指定次序的节点
-- 查找所有名为 "hero" 的节点，并返回第 1 个
local hero = cc.uiloader:seekComponents(node, "hero", 1)

-- 假设 hero 是一个 Armature 对象，可以用 play 方法播放指定的动作
hero:getAnimation():play("attack")

~~~

~

更多用法参见样例 samples/ccsloader。

