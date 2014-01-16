require "CocoStudio"

local ConfigType = 
{
    NONE = 0,
    COCOSTUDIO = 1,
}

function __onParseConfig(configType,jasonStr)
    if configType == ConfigType.COCOSTUDIO then
        TriggerMng.getInstance():parse(jasonStr)
    end
end
