
-- 0 - disable debug info, 1 - less debug info, 2 - verbose debug info
DEBUG = 1

-- display FPS stats on screen
DEBUG_FPS = true

-- dump memory info every 10 seconds
DEBUG_MEM = false

-- load deprecated API
LOAD_DEPRECATED_API = false

-- load shortcodes API
LOAD_SHORTCODES_API = true

-- screen orientation
CONFIG_SCREEN_ORIENTATION = "landscape"

-- design resolution
CONFIG_SCREEN_WIDTH  = 960
CONFIG_SCREEN_HEIGHT = 640

-- auto scale mode
CONFIG_SCREEN_AUTOSCALE = "FIXED_WIDTH"

cc.FileUtils:getInstance():addSearchPath("res/")

require("framework.init")

-- musics
MUSIC = {
    backgroundMusic = "sound/newdali.mp3",
}

-- effects
EFFECT = {}

-- preload all musics
for k, v in pairs(MUSIC) do
    audio.preloadMusic(v)
end

-- preload all effects
for k, v in pairs(EFFECT) do
    audio.preloadSound(v)
end
