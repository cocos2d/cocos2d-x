
local BugBase = import(".BugBase")

local BugAnt = class("BugAnt", BugBase)

function BugAnt:ctor()
    BugAnt.super.ctor(self)
    self.type_ = BugBase.BUG_TYPE_ANT
    self.speed_ = 1.0
    self.touchRange_ = 70
end

return BugAnt
