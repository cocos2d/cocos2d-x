require "extern"
require "Cocos2d"

VisibleRect = class("VisibleRect")
VisibleRect.__index = VisibleRect


VisibleRect.s_visibleRect = cc.rect(0,0,0,0)

function VisibleRect:lazyInit()
    if (self.s_visibleRect.width == 0.0 and self.s_visibleRect.height == 0.0) then
        --[[
        local pEGLView = cc.EGLView:getInstance()
        local origin   = pEGLView:getVisibleOrigin()
        ]]--
        self.s_visibleRect.x = 0
        self.s_visibleRect.y = 0
        local size  = cc.Director:getInstance():getWinSize()
        self.s_visibleRect.width  = size.width
        self.s_visibleRect.height = size.height
    end
end

function VisibleRect:getVisibleRect()
    self:lazyInit()
    return cc.rect(self.s_visibleRect.x, self.s_visibleRect.y, self.s_visibleRect.width, self.s_visibleRect.height)
end

function VisibleRect:left()
    self:lazyInit()
    return cc.p(self.s_visibleRect.x, self.s_visibleRect.y+self.s_visibleRect.height/2)
end

function VisibleRect:right()
    self:lazyInit()
    return cc.p(self.s_visibleRect.x+self.s_visibleRect.width, self.s_visibleRect.y+self.s_visibleRect.height/2)
end

function VisibleRect:top()
    self:lazyInit()
    return cc.p(self.s_visibleRect.x+self.s_visibleRect.width/2, self.s_visibleRect.y+self.s_visibleRect.height)
end

function VisibleRect:bottom()
    self:lazyInit()
    return cc.p(self.s_visibleRect.x+self.s_visibleRect.width/2, self.s_visibleRect.y)
end

function VisibleRect:center()
    self:lazyInit()
    return cc.p(self.s_visibleRect.x+self.s_visibleRect.width/2, self.s_visibleRect.y+self.s_visibleRect.height/2)
end

function VisibleRect:leftTop()
    self:lazyInit()
    return cc.p(self.s_visibleRect.x, self.s_visibleRect.y+self.s_visibleRect.height)
end

function VisibleRect:rightTop()
    self:lazyInit()
    return cc.p(self.s_visibleRect.x+self.s_visibleRect.width, self.s_visibleRect.y+self.s_visibleRect.height)
end

function VisibleRect:leftBottom()
    self:lazyInit()
    return cc.p(self.s_visibleRect.x,self.s_visibleRect.y)
end

function VisibleRect:rightBottom()
    self:lazyInit()
    return cc.p(self.s_visibleRect.x+self.s_visibleRect.width, self.s_visibleRect.y)
end
