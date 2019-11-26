
local TextInput = {}

function TextInput.create()
    cclog("TextInput.create")
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    TextInput.layer = layer

    local res = "Images/CyanSquare.png"
    local width = 200
    local height = 40
    local back = ccui.Scale9Sprite:create(res)
    local edit = ccui.EditBox:create(cc.size(width,height),back)
    layer:addChild(edit)
    edit:setPosition( cc.p(250,200) )
    edit:setPlaceHolder("click to input text")

    local editPasswd = ccui.EditBox:create(cc.size(width,height),res)
    editPasswd:setInputFlag(cc.EDITBOX_INPUT_FLAG_PASSWORD)
    layer:addChild(editPasswd)
    editPasswd:setPosition( cc.p(250,100) )
    editPasswd:setPlaceHolder("click to input password")
    editPasswd:setInputMode(cc.EDITBOX_INPUT_MODE_SINGLELINE);
    return layer
end

function TextInputTestMain()
    cclog("TextInputTestMain")
    local scene = cc.Scene:create()
    Helper.createFunctionTable = {
        TextInput.create,
    }
    Helper.index = 1
    
    scene:addChild(TextInput.create())
    scene:addChild(CreateBackMenuItem())
    return scene
end

