
require "cocos.cocos2d.Cocos2d"
require "cocos.cocos2d.Cocos2dConstants"
require "cocos.cocos2d.extern"

-- opengl
require "cocos.cocos2d.Opengl"
require "cocos.cocos2d.OpenglConstants"

-- cocosdenshion
require "cocos.cocosdenshion.AudioEngine"

-- cocosstudio
require "cocos.cocosstudio.CocosStudio"

-- ui
require "cocos.ui.GuiConstants"

-- extensions
require "cocos.extension.ExtensionConstants"

-- network
require "cocos.network.NetworkConstants"

if CC_USE_DEPRECATED_API then
    -- CCLuaEngine
    require "cocos.cocos2d.DeprecatedCocos2dClass"
    require "cocos.cocos2d.DeprecatedCocos2dEnum"
    require "cocos.cocos2d.DeprecatedCocos2dFunc"

    -- register_cocostudio_module
    require "cocos.cocosstudio.DeprecatedCocoStudioClass"
    require "cocos.cocosstudio.DeprecatedCocoStudioFunc"

    -- register_cocosbuilder_module
    require "cocos.cocosbuilder.DeprecatedCocosBuilderClass"

    -- register_cocosdenshion_module
    require "cocos.cocosdenshion.DeprecatedCocosDenshionClass"
    require "cocos.cocosdenshion.DeprecatedCocosDenshionFunc"

    -- register_extension_module
    require "cocos.extension.DeprecatedExtensionClass"
    require "cocos.extension.DeprecatedExtensionEnum"
    require "cocos.extension.DeprecatedExtensionFunc"

    -- register_network_module
    require "cocos.network.DeprecatedNetworkClass"
    require "cocos.network.DeprecatedNetworkEnum"
    require "cocos.network.DeprecatedNetworkFunc"

    -- register_ui_moudle
    require "cocos.ui.DeprecatedUIEnum"
    require "cocos.ui.DeprecatedUIFunc"
end
