--[[

Copyright (c) 2011-2014 chukong-inc.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

]]

--[[--

定义 cocos2dx 中的全局函数

]]

local c = cc

c.LuaLog                        = CCLuaLog
c.MessageBox                    = CCMessageBox
c.LoadChunksFromZIP             = CCLuaLoadChunksFromZIP
c.StackSnapshot                 = CCLuaStackSnapshot

c.Color3B                       = ccColor3B
c.Color4B                       = ccColor4B
c.Color4F                       = ccColor4F
c.Color3BMake                   = ccc3
c.Color4BMake                   = ccc4
c.Color4FMake                   = ccc4f
c.Color3BEqual                  = ccc3BEqual
c.Color4FEqual                  = ccc4FEqual
c.Color4FFromColor3B            = ccc4FFromccc3B
c.Color4FFromColor4B            = ccc4FFromccc4B
c.Color4BFromColor4F            = ccc4BFromccc4F
c.c3                            = ccc3
c.c4                            = ccc4
c.c4f                           = ccc4f

-- support
c.timeval                       = cc_timeval
c.BezierConfig                  = ccBezierConfig
c.BlendFunc                     = ccBlendFunc

c.TargetWindows                 = kTargetWindows
c.TargetLinux                   = kTargetLinux
c.TargetMacOS                   = kTargetMacOS
c.TargetAndroid                 = kTargetAndroid
c.TargetIphone                  = kTargetIphone
c.TargetIpad                    = kTargetIpad
c.TargetBlackBerry              = kTargetBlackBerry
c.TargetNaCl                    = kTargetNaCl
c.TargetEmscripten              = kTargetEmscripten
c.TargetTizen                   = kTargetTizen

c.LanguageEnglish               = kLanguageEnglish
c.LanguageChinese               = kLanguageChinese
c.LanguageFrench                = kLanguageFrench
c.LanguageItalian               = kLanguageItalian
c.LanguageGerman                = kLanguageGerman
c.LanguageSpanish               = kLanguageSpanish
c.LanguageRussian               = kLanguageRussian
c.LanguageKorean                = kLanguageKorean
c.LanguageJapanese              = kLanguageJapanese
c.LanguageHungarian             = kLanguageHungarian
c.LanguagePortuguese            = kLanguagePortuguese
c.LanguageArabic                = kLanguageArabic
c.LanguageChineseTW             = kLanguageChineseTW


c.ResolutionExactFit            = kResolutionExactFit
c.ResolutionNoBorder            = kResolutionNoBorder
c.ResolutionShowAll             = kResolutionShowAll
c.ResolutionFixedHeight         = kResolutionFixedHeight
c.ResolutionFixedWidth          = kResolutionFixedWidth
c.ResolutionUnKnown             = kResolutionUnKnown

-- touch
c.TouchesAllAtOnce              = kCCTouchesAllAtOnce
c.TouchesOneByOne               = kCCTouchesOneByOne
c.TOUCH_MODE_ALL_AT_ONCE        = c.TouchesAllAtOnce
c.TOUCH_MODE_ONE_BY_ONE         = c.TouchesOneByOne

-- keypad
c.KeypadBackClicked             = kTypeBackClicked
c.KeypadMenuClicked             = kTypeMenuClicked

-- label
c.LabelAutomaticWidth           = kCCLabelAutomaticWidth
c.VerticalTextAlignmentTop      = kCCVerticalTextAlignmentTop
c.VerticalTextAlignmentCenter   = kCCVerticalTextAlignmentCenter
c.VerticalTextAlignmentBottom   = kCCVerticalTextAlignmentBottom
c.TextAlignmentLeft             = kCCTextAlignmentLeft
c.TextAlignmentCenter           = kCCTextAlignmentCenter
c.TextAlignmentRight            = kCCTextAlignmentRight
c.FontDefinition                = ccFontDefinition

-- misc nodes
c.ProgressTimerTypeRadial       = kCCProgressTimerTypeRadial
c.ProgressTimerTypeBar          = kCCProgressTimerTypeBar

-- image format
c.ImageFormatJpg                = kFmtJpg
c.ImageFormatPng                = kFmtPng
c.ImageFormatTiff               = kFmtTiff
c.ImageFormatWebp               = kFmtWebp
c.ImageFormatRawData            = kFmtRawData
c.ImageFormatUnKnown            = kFmtUnKnown

-- texture
c.Texture2DPixelFormat_RGBA8888 = kCCTexture2DPixelFormat_RGBA8888
c.Texture2DPixelFormat_RGB888   = kCCTexture2DPixelFormat_RGB888
c.Texture2DPixelFormat_RGB565   = kCCTexture2DPixelFormat_RGB565
c.Texture2DPixelFormat_A8       = kCCTexture2DPixelFormat_A8
c.Texture2DPixelFormat_I8       = kCCTexture2DPixelFormat_I8
c.Texture2DPixelFormat_AI88     = kCCTexture2DPixelFormat_AI88
c.Texture2DPixelFormat_RGBA4444 = kCCTexture2DPixelFormat_RGBA4444
c.Texture2DPixelFormat_RGB5A1   = kCCTexture2DPixelFormat_RGB5A1
c.Texture2DPixelFormat_PVRTC4   = kCCTexture2DPixelFormat_PVRTC4
c.Texture2DPixelFormat_PVRTC2   = kCCTexture2DPixelFormat_PVRTC2
c.Texture2DPixelFormat_Default  = kCCTexture2DPixelFormat_RGBA8888
c.TextureParams                 = ccTexParams

-- tilemap parallax nodes
c.TMXOrientationOrtho           = CCTMXOrientationOrtho
c.TMXOrientationHex             = CCTMXOrientationHex
c.TMXOrientationIso             = CCTMXOrientationIso
c.TMXLayerAttribNone            = TMXLayerAttribNone
c.TMXLayerAttribBase64          = TMXLayerAttribBase64
c.TMXLayerAttribGzip            = TMXLayerAttribGzip
c.TMXLayerAttribZlib            = TMXLayerAttribZlib
c.TMXPropertyNone               = TMXPropertyNone
c.TMXPropertyMap                = TMXPropertyMap
c.TMXPropertyLayer              = TMXPropertyLayer
c.TMXPropertyObjectGroup        = TMXPropertyObjectGroup
c.TMXPropertyObject             = TMXPropertyObject
c.TMXPropertyTile               = TMXPropertyTile
c.TMXTileHorizontalFlag         = kCCTMXTileHorizontalFlag
c.TMXTileVerticalFlag           = kCCTMXTileVerticalFlag
c.TMXTileDiagonalFlag           = kCCTMXTileDiagonalFlag
c.TMXFlipedAll                  = kCCFlipedAll
c.TMXFlippedMask                = kCCFlippedMask
