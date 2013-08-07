require "luaScript/extern"

VisibleRect = class("VisibleRect")
VisibleRect.__index = VisibleRect


VisibleRect.s_visibleRect = CCRect:new()

function VisibleRect:lazyInit()
    if (self.s_visibleRect.size.width == 0.0 and self.s_visibleRect.size.height == 0.0) then
        local pEGLView = CCEGLView:sharedOpenGLView();
        self.s_visibleRect.origin = pEGLView:getVisibleOrigin();
        self.s_visibleRect.size = pEGLView:getVisibleSize();
    end
end

function VisibleRect:getVisibleRect()
    self:lazyInit();
    return CCRectMake(self.s_visibleRect.origin.x, self.s_visibleRect.origin.y, self.s_visibleRect.size.width, self.s_visibleRect.size.height);
end

function VisibleRect:left()
    self:lazyInit();
    return ccp(self.s_visibleRect.origin.x, self.s_visibleRect.origin.y+self.s_visibleRect.size.height/2);
end

function VisibleRect:right()
    self:lazyInit();
    return ccp(self.s_visibleRect.origin.x+self.s_visibleRect.size.width, self.s_visibleRect.origin.y+self.s_visibleRect.size.height/2);
end

function VisibleRect:top()
    self:lazyInit();
    return ccp(self.s_visibleRect.origin.x+self.s_visibleRect.size.width/2, self.s_visibleRect.origin.y+self.s_visibleRect.size.height);
end

function VisibleRect:bottom()
    self:lazyInit();
    return ccp(self.s_visibleRect.origin.x+self.s_visibleRect.size.width/2, self.s_visibleRect.origin.y);
end

function VisibleRect:center()
    self:lazyInit();
    return ccp(self.s_visibleRect.origin.x+self.s_visibleRect.size.width/2, self.s_visibleRect.origin.y+self.s_visibleRect.size.height/2);
end

function VisibleRect:leftTop()
    self:lazyInit();
    return ccp(self.s_visibleRect.origin.x, self.s_visibleRect.origin.y+self.s_visibleRect.size.height);
end

function VisibleRect:rightTop()
    self:lazyInit();
    return ccp(self.s_visibleRect.origin.x+self.s_visibleRect.size.width, self.s_visibleRect.origin.y+self.s_visibleRect.size.height);
end

function VisibleRect:leftBottom()
    self:lazyInit();
    return self.s_visibleRect.origin;
end

function VisibleRect:rightBottom()
    self:lazyInit();
    return ccp(self.s_visibleRect.origin.x+self.s_visibleRect.size.width, self.s_visibleRect.origin.y);
end
