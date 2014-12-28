
local BugBase = import(".BugBase")

local BugSpider = class("BugSpider", BugBase)

function BugSpider:ctor()
    BugSpider.super.ctor(self)
    self.type_ = BugBase.BUG_TYPE_SPIDER
    self.speed_ = 1.5
    self.touchRange_ = 50
end

return BugSpider
