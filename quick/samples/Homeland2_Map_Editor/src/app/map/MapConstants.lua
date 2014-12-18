
local MapConstants = {}

MapConstants.SIDE_BAR_WIDTH         = 110

MapConstants.PLAY_DEFAULT_SCALE     = 0.7
MapConstants.ZOOM_TIME              = 0.1
MapConstants.FIRE_RANGE_SIZE        = 128
MapConstants.FIRE_RANGE_SCALE_Y     = 0.8

MapConstants.FIRE_RANGE_ZORDER      = 150
MapConstants.DEFAULT_OBJECT_ZORDER  = 100
MapConstants.MAX_OBJECT_ZORDER      = 20000
MapConstants.BULLET_ZORDER          = 21000
MapConstants.NORMAL_TRACKING_SPEED  = 3
MapConstants.FAST_TRACKING_SPEED    = 12
MapConstants.SET_FAST_TRACKING_DIST = display.height / 3

MapConstants.CROSS_POINT_TAP_RADIUS = 50
MapConstants.HP_BAR_ZORDER          = 30000
MapConstants.HP_BAR_OFFSET_Y        = 20
MapConstants.RADIUS_CIRCLE_SCALE_Y  = 0.85

MapConstants.LEVEL_LABEL_OFFSET_Y   = 26
MapConstants.LEVEL_LABEL_FONT       = display.DEFAULT_TTF_FONT
MapConstants.LEVEL_LABEL_FONT_SIZE  = 16

MapConstants.PLAYER_CAMP            = 1
MapConstants.ENEMY_CAMP             = 2

return MapConstants
