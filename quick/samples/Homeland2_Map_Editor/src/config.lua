
-- 0 - disable debug info, 1 - less debug info, 2 - verbose debug info
DEBUG = 1
DEBUG_FPS = true
DEBUG_MEM = false

-- auto encapsulation C++ object
AUTO_CC = false

-- auto binding short methods when encapsulation C++ object
AUTO_CC_SHORTCODES = true

-- load deprecated API
LOAD_DEPRECATED_API = true

-- screen orientation
CONFIG_SCREEN_ORIENTATION = "landscape"

-- design resolution
CONFIG_SCREEN_WIDTH  = 960
CONFIG_SCREEN_HEIGHT = 640

-- auto scale mode
CONFIG_SCREEN_AUTOSCALE = "FIXED_HEIGHT"

-- auto scale callback function
CONFIG_SCREEN_AUTOSCALE_CALLBACK = function(screenWidthInPixels, screenHeightInPixels, deviceModel)
    if (device.platform == "ios" and device.model == "iphone") or device.platform == "android" then
        return nil, nil
    end

    CONFIG_SCREEN_WIDTH = screenWidthInPixels
    CONFIG_SCREEN_HEIGHT = screenHeightInPixels
    return 1, 1
end
