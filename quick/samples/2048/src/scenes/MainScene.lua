--[[=============================================================================
#     FileName: MainScene.lua
#         Desc: mainScene for 2048 game
#               full edition in https://github.com/hanxi/quick-cocos2d-x-2048/tree/release
#       Author: hanxi
#        Email: hanxi.info@gmail.com
#     HomePage: http://www.hanxi.info
#      Version: 0.0.1
#   LastChange: 2014-05-09 09:13:11
#      History:
=============================================================================]]

local totalScore = 0
local bestScore = 0
local WINSTR = ""
local touchStart={0,0}
local configFile = device.writablePath.."hxgame.config"

local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

local function doOpList(op_list)
    for _,op in ipairs(op_list or {}) do
        local o = op[1]
        if o=='setnum' then
            local i,j,num = op[2],op[3],op[4]
            setnum(gridShow[i][j],num,i,j)
        end
    end
end

function getPosFormIdx(mx,my)
    local cellsize=150   -- cell size
    local cdis = 2*cellsize-cellsize/2
    local origin = {x=display.cx-cdis,y=display.cy+cdis}
    local x = (my-1)*cellsize+origin.x
    local y = -(mx-1)*cellsize+origin.y - 100
    return x,y
end

function MainScene:show(cell,mx,my)
    local x,y = getPosFormIdx(mx,my)
    local bsz = cell.backgroundsize/2
    cell.background:setPosition(cc.p(x-bsz,y-bsz))
    self:addChild(cell.background)
    cell.num:align(display.CENTER,x,y):addTo(self)
end

local colors = {
    [-1]   = cc.c4b(0xee, 0xe4, 0xda, 100),
    [0]    = cc.c3b(0xee, 0xe4, 0xda),
    [2]    = cc.c3b(0xee, 0xe4, 0xda),
    [4]    = cc.c3b(0xed, 0xe0, 0xc8),
    [8]    = cc.c3b(0xf2, 0xb1, 0x79),
    [16]   = cc.c3b(0xf5, 0x95, 0x63),
    [32]   = cc.c3b(0xf6, 0x7c, 0x5f),
    [64]   = cc.c3b(0xf6, 0x5e, 0x3b),
    [128]  = cc.c3b(0xed, 0xcf, 0x72),
    [256]  = cc.c3b(0xed, 0xcc, 0x61),
    [512]  = cc.c3b(0xed, 0xc8, 0x50),
    [1024] = cc.c3b(0xed, 0xc5, 0x3f),
    [2048] = cc.c3b(0xed, 0xc2, 0x2e),
    [4096] = cc.c3b(0x3c, 0x3a, 0x32),
}
local numcolors = {
    [0] = cc.c3b(0x77,0x6e,0x65),
    [2] = cc.c3b(0x77,0x6e,0x65),
    [4] = cc.c3b(0x77,0x6e,0x65),
    [8] = cc.c3b(0x77,0x6e,0x65),
    [16] = cc.c3b(0x77,0x6e,0x65),
    [32] = cc.c3b(0x77,0x6e,0x65),
    [64] = cc.c3b(0x77,0x6e,0x65),
    [128] = cc.c3b(0x77,0x6e,0x65),
}

function setnum(self,num,i,j)
    local s = tostring(num)
    --s = s.."("..i..","..j..")"
    if s=='0' then 
        s=''
        self.background:setOpacity(100)
    else
        self.background:setOpacity(255)
    end
    local c=colors[num]
    if not c then
        c=colors[4096]
    end
    self.num:setString(s)
    self.background:setColor(c)
    local nc = numcolors[num]
    if not nc then
        nc = numcolors[128]
    end
    self.num:setColor(nc)
end

function saveStatus()
    local gridstr = serialize(grid)
    local isOverstr = "false"
    if isOver then isOverstr = "true" end
    local str = string.format("do local grid,bestScore,totalScore,WINSTR,isOver \
                              =%s,%d,%d,\'%s\',%s return grid,bestScore,totalScore,WINSTR,isOver end",
                              gridstr,bestScore,totalScore,WINSTR,isOverstr)
    io.writefile(configFile,str)
end

function MainScene:loadStatus()
    if io.exists(configFile) then
        local str = io.readfile(configFile)
        if str then
            local f = loadstring(str)
            local _grid,_bestScore,_totalScore,_WINSTR,_isOver = f()
            if _grid and _bestScore and _totalScore and _WINSTR then
                grid,bestScore,totalScore,WINSTR,isOver = _grid,_bestScore,_totalScore,_WINSTR,_isOver
            end
        end
    end
    self:reLoadGame()
end

function MainScene:createLabel(title)
    cc.ui.UILabel.new({text = "== " .. title .. " ==", size = 20, color = display.COLOR_BLACK})
        :align(display.CENTER, display.cx, display.top - 20)
        :addTo(self)
    self.scoreLabel = cc.ui.UILabel.new({
        text = "SCORE:0",
        size = 30,
        color = display.COLOR_BLUE,
    })
    self.scoreLabel:align(display.CENTER,display.cx,display.top - 100):addTo(self)
end

function MainScene:onTouch(event, x, y)
    if isOver then
        return true
    end

    if event=='began' then
        touchStart={x,y}
    elseif event=='ended' then
        local tx,ty=x-touchStart[1],y-touchStart[2]
        if tx==0 then
            tx = tx+1
            ty = ty+1
        end
        local dis = tx*tx+ty*ty
        if dis<3 then   -- touch move too short will ignore
            return true
        end
        local dt = ty/tx
        local op_list,score,win
        if dt>=-1 and dt<=1 then
            if tx>0 then
                op_list,score,win = touch_op(grid,'right')
            else
                op_list,score,win = touch_op(grid,'left')
            end
        else
            if ty>0 then
                op_list,score,win = touch_op(grid,'up')
            else
                op_list,score,win = touch_op(grid,'down')
            end
        end
        doOpList(op_list)
        if win then
            WINSTR = "YOUR ARE WINER"
        end
        totalScore = totalScore + score
        if totalScore>bestScore then
            bestScore = totalScore
        end
        self.scoreLabel:setString(string.format("BEST:%d     \nSCORE:%d    \n%s",bestScore,totalScore,WINSTR or ""))
        isOver = not canMove(grid)
        saveStatus()
    end
    return true
end

function MainScene:createGridShow()
    gridShow = {}
    for tmp=0,15 do
        local i,j = math.floor(tmp/4)+1,math.floor(tmp%4)+1
        local num = grid[i][j]
        local s = tostring(num)
        --s = s.."("..i..","..j..")"
        if s=='0' then
            s=''
        end
        if not gridShow[i] then
            gridShow[i] = {}
        end
        local cell = {
            backgroundsize = 140,
            background = cc.LayerColor:create(colors[-1], 140, 140),
            num = cc.ui.UILabel.new({
                text = s,
                size = 40,
                color = numcolors[0],
            }),
        }
        gridShow[i][j] = cell
        self:show(gridShow[i][j],i,j)
    end

end

function MainScene:reLoadGame()
    local m = #grid
    local n = #grid[1]
    for i=1,m do
        for j=1,n do
            setnum(gridShow[i][j],grid[i][j],i,j)
        end
    end
    self.scoreLabel:setString(string.format("BEST:%d     \nSCORE:%d    \n%s",bestScore,totalScore,WINSTR or ""))
end

function MainScene:restartGame()
    grid = initGrid(4,4)
    totalScore = 0
    WINSTR = ""
    isOver = false
    self:reLoadGame()
    saveStatus()
end

function MainScene:createButtons()
    local images = {
        normal = "GreenButton.png",
        pressed = "GreenScale9Block.png",
        disabled = "GreenButton.png",
    }
    cc.ui.UIPushButton.new(images, {scale9 = true})
        :setButtonSize(200, 60)
        :setButtonLabel("normal", cc.ui.UILabel.new({
            UILabelType = 2,
            text = "New Game",
            size = 32
        }))
        :onButtonClicked(function(event)
            self:restartGame()
        end)
        :align(display.CENTER_TOP, display.left+display.width/2, display.top - 170)
        :addTo(self)
end

function MainScene:ctor()
    WINSTR = ""
    display.newColorLayer(cc.c4b(0xfa,0xf8,0xef, 255)):addTo(self)
    grid = initGrid(4,4)

    self:createLabel("2048")
    self:createGridShow()
    self:createButtons()

    self:loadStatus()
    if isOver then
        self:restartGame()
    end
end

function MainScene:onEnter()
    local layer = display.newNode()
    layer:setContentSize(display.width, display.height)

    layer:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(event)
        return self:onTouch(event.name, event.x, event.y)
    end)
    layer:setTouchEnabled(true)
    layer:setTouchSwallowEnabled(false)
    self:addChild(layer)
end

return MainScene
